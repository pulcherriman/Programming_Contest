#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""In-house Contest 2019: Prime Daihinmin (C) 2019 Fixstars Corp.
"""

import sys
import os
import time
import subprocess
import threading
import random
import json
import re
from optparse import OptionParser

VERSION  = "0.11"
REVISION = "a"
VER_DATE = "20191225"

TIME_LIMIT = 10.0
SHOW_GAME = False
DEBUG_PRINT = False

def debug_print(msg):
    if DEBUG_PRINT:
        print(msg, file=sys.stderr)

def read_response(player):
    if player.time <= 0.0:
        return None, 0.0
    start_time = time.time()
    class ExecThread(threading.Thread):
        def __init__(self, solver):
            self.solver = solver
            self.response = None
            threading.Thread.__init__(self)
        def run(self):
            self.response = self.solver.stdout.readline().strip()
        def get_response(self):
            return self.response
    t = ExecThread(player.solver)
    t.setDaemon(True)
    t.start()
    if t.isAlive(): t.join(player.time)
    player.time -= time.time() - start_time
    return t.get_response(), player.time

class Player:
    def __init__(self, uid, name, solver, hand, status="OK"):
        self.uid = uid
        self.name = name
        self.solver = solver
        self.time = TIME_LIMIT
        self.hand = hand
        self.status = status

class PrimeDaihinmin:
    """PrimeDaihinmin class
    """

    NORMAL_STATES = ("OK", "MERSENNE", "BELPHEGOR")
    BELPHEGOR_PRIME = 1000000000000066600000000000001

    def __init__(self, players):
        self.num_players = len(players)
        self.num_draw_cards = 5
        self.num_hand = 199  # initial number of cards in a hand
        self.num_first_cards = 5
        self.stock = [i for i in range(10)] * 300 + [0]
        self.max_cards = len(self.stock)
        random.shuffle(self.stock)
        self.players = []
        self.player = None
        for uid, (name, solver) in enumerate(players):
            solver = subprocess.Popen(solver, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
            hand, self.stock = self.stock[:self.num_hand], self.stock[self.num_hand:]
            self.players.append(Player(uid, name, solver, sorted(hand)))
            debug_print("0 in hand: {}".format(hand.count(0))) #####
        self.numbers = []
        self.record = []

        print("players: {}".format(", ".join([player.name for player in self.players])), file=sys.stderr)
        print("solvers: {}".format(", ".join([str(player.solver) for player in self.players])), file=sys.stderr)
        print("stock: {}".format(len(self.stock)), file=sys.stderr)
        print("time limit: {}".format(TIME_LIMIT), file=sys.stderr)

    # Miller-Rabin primality test
    def is_prime(self, q, k=50):
       if q == 2: return True
       if q < 2 or q & 1 == 0: return False
       d = q - 1
       d //= d & -d
       for _ in range(k):
           a = random.randint(1, q - 1)
           t = d
           y = pow(a, t, q)
           while t != q - 1 and y != 1 and y != q - 1: 
               y = pow(y, 2, q)
               t <<= 1
           if y != q - 1 and t & 1 == 0:
               return False
       return True

    def is_Mersenne(self, n):
        while n:
            if n & 1 == 0:
                return False
            n >>= 1
        return True

    def check_TLE(self, player):
        if player.time <= 0.0:
            print("Error: time limit exceeded: {}".format(player.name,), file=sys.stderr)
            return True
        return False

    def record_cards(self, player, msg=""):
        global SHOW_GAME
        if SHOW_GAME:
            print("{} {} {} ({}) [{}]".format(msg, player.name, "".join(map(str, player.hand)), ",".join(map(str, self.numbers)), player.status), file=sys.stderr)
        self.record.append((player.name, player.status, len(player.hand), list(map(str, self.numbers[:]))))

    def clean_players(self):
        for p in self.players:
            if p.status == "PASSED":
                p.status = "OK"

    def next_player(self):
        if not self.player:
            return self.players[0]
        uid = self.player.uid
        cnt = 0
        while True:
            uid += 1
            uid %= self.num_players
            if self.players[uid].status in ("OK", "PASSED"):
               break
            if self.num_players == cnt:
                print("Error: invalid status in next_player", file=sys.stderr)
                break
            cnt += 1
        return self.players[uid]

    def check_finish(self):
        if not self.player.hand:
            print("Winner: {}".format(self.player.name), file=sys.stderr)
            self.clean_players()
            return True
        return False

    def initialize(self):
        names = [player.name for player in self.players]
        for player in self.players:
            print(player.name)
            try:
                data = json.dumps({"action": "init", "uid": player.uid, "names": names, "hand": player.hand, "time": TIME_LIMIT})
                debug_print("{}: {}".format(player.name, data)) ###
                player.solver.stdin.write(("%s\n" % data).encode("utf-8"))
                player.solver.stdin.flush()
                _, player.time = read_response(player)
                if self.check_TLE(player):
                    player.status = "ERROR:TLE in initialize"
            except Exception as e:
                player.status = "ERROR:ERROR in initialize"
                print("{}: {}".format(self.player.name, str(e)), file=sys.stderr)
        for player in self.players:
            self.record_cards(player, "init:")
        return True

    def play(self):
        while True:
            if self.num_players - 1 <= [bool(re.match("ERROR", p.status)) for p in self.players].count(True):
                self.clean_players()
                print("Only one survivor", file=sys.stderr) ###
                return True
            if self.num_players - [p.status not in self.NORMAL_STATES for p in self.players].count(True) == 1 and self.next_player().status in self.NORMAL_STATES:
                self.clean_players()
                self.numbers = []
                continue
            elif self.player and self.player.status in ("MERSENNE", "BELPHEGOR"):
                self.clean_players()
                self.numbers = []
            else:
                self.player = self.next_player()
            if re.match("ERROR", self.player.status):
                continue

            try:
                response = None
                if not re.match("ERROR", self.player.status):
                    data = json.dumps({"action": "play", "name": self.player.name, "hand": self.player.hand, "numbers": list(map(str, self.numbers)), "hands": [(p.name, len(p.hand)) for p in self.players], "record": self.record})
                    #debug_print("{}: {}".format(self.player.name, data)) ##### debug
                    self.player.solver.stdin.write(("{}\n".format(data)).encode("utf-8"))
                    self.player.solver.stdin.flush()
                    response, self.player.time = read_response(self.player)
                    data = json.loads(response.decode("utf-8"))
                    action = data["action"]  # number, pass, draw
                    if action == "number":
                        self.player.status = "OK"
                        cards = data["cards"]

                        # cards in self.players[current_uid].hand -> True
                        if False in [card in self.player.hand for card in cards]:
                            self.player.status = "ERROR:cards in self.players[current_uid].hand -> False"
                            debug_print("{}: {}".format(self.player.name, "cards in self.players[current_uid].hand -> False")) ### debug
                            continue

                        # removes cards from player.hand -> player.hand
                        for card in cards:
                            self.player.hand.remove(card)

                        # check_digits(number) -> True
                        debug_print("debug cards: {}".format(cards)) ##### debug
                        number = "".join(map(str, cards))

                        # check Belphegor prime -> True
                        if int(number) == self.BELPHEGOR_PRIME:
                            self.player.status = "BELPHEGOR"
                            self.numbers.append(int(number))
                            if self.check_finish():
                                return True
                            debug_print("number: {}: {}".format(self.player.name, number)) ##### debug
                            self.record_cards(self.player, "play:")
                            continue

                        if (len(self.numbers) == 0 and len(number) > self.num_first_cards) or (self.numbers and len(number) != len("".join(map(str, self.numbers)))):
                            self.player.status = "ERROR:check_digits(number) -> False"
                            debug_print("{}: {} {} {} {}".format(self.player.name, number, cards, self.numbers, self.player.status)) ### debug
                            continue

                        # cards -> number
                        number = int(number)

                        # prime_check(number) -> False
                        if not self.is_prime(number):
                            self.player.status = "ERROR:prime_check(number) -> False"
                            debug_print("{}: {}".format(self.player.name, self.player.status)) ### debug
                            continue

                        # Mersenne number -> True
                        if self.is_Mersenne(number):
                            self.player.status = "MERSENNE"

                        # numbers[-1] < number -> False
                        if self.numbers and number < self.numbers[-1]:
                            self.player.status = "ERROR:numbers[-1] < number -> False"
                            debug_print("{}: {}".format(self.player.name, self.player.status)) ### debug
                            continue

                        self.numbers.append(number)
                        debug_print("number: {}: {}".format(self.player.name, number)) ##### debug
                        self.record_cards(self.player, "play:")

                        # check passes
                        # len(player.hand) == 0 -> winner
                        if self.check_finish():
                            return True

                    elif action == "pass":
                        draw = []
                        for _ in range(self.num_draw_cards):
                            draw.append(self.stock.pop())
                            if not self.stock:
                                break
                        data = json.dumps({"action": "pass", "name": self.player.name, "draw": draw, "record": self.record})
                        self.player.solver.stdin.write(("{}\n".format(data)).encode("utf-8"))
                        self.player.solver.stdin.flush()
                        _, self.player.time = read_response(self.player)
                        self.player.status = "PASSED"
                        self.player.hand.extend(draw)
                        self.player.hand.sort()
                        debug_print("ctrl-pass: {}: {}, {}".format(self.player.name, draw, self.player.hand)) ##### debug
                        self.record_cards(self.player, "pass:")
                        if not self.stock:
                            print("No stock", file=sys.stderr) ###
                            self.clean_players()
                            return True
                    else:
                        pass

            except Exception as e:
                if self.check_TLE(self.player):
                    self.player.status = "ERROR:TLE in play"
                    debug_print("{}: {}".format(self.player.name, "TLE in play")) ### debug
                else:
                    self.player.status = "ERROR:ERROR in play ({})".format(str(e))
                print("{}: {}".format(self.player.name, str(e)), file=sys.stderr)

        return False

    def quit_game(self):
        for player in self.players:
            try:
                player.solver.stdin.write(("%s\n" % json.dumps({"action": "quit"})).encode("utf-8"))
                player.solver.stdin.flush()
                _, player.times = read_response(player)
            except:
                pass

    def finish(self):
        results = []
        for player in self.players:
            results.append([len(player.hand) if player.status in ("OK", "PASSED", "MERSENNE") else self.max_cards, player.name, player.status, player.time])
        results.sort()

        rank = self.num_players
        order = self.num_players
        prev_score = self.max_cards + 1
        for i in range(len(results)-1, -1, -1):
            if prev_score > results[i][0]:
                rank = order
            prev_score = results[i][0]
            results[i].append(rank)
            order -= 1

        for score, name, status, t, rank in results:
            print("{} : {} {} {} {:.3f}".format(rank, name, score, status, t))
        print("stock: {}".format(len(self.stock)))

        self.quit_game()
        if os.name == "posix":
            for player in self.players:
                pid = player.solver.pid
                #os.system("kill -{}".format(pid))
                os.system("pkill -TERM -P {}".format(pid))

def main():
    global TIME_LIMIT, SHOW_GAME, DEBUG_PRINT

    parser = OptionParser(usage="Usage: %prog [options] name1 command1 name2 command2 [name3 command3 ...]")
    parser.add_option("-s", "--show", action="store_true", dest="show", default=False, help="show game")
    parser.add_option("-t", "--time", action="store", type="float", dest="time", default=10.0, help="time limit")
    parser.add_option("-d", "--debug", action="store_true", dest="debug", default=False, help="print for debug")

    (options, args) = parser.parse_args()

    if len(args) < 4:
        parser.error("incorrect number of arguments")

    SHOW_GAME = options.show
    TIME_LIMIT = options.time
    DEBUG_PRINT = options.debug

    start_time = time.time()
    n = len(args) // 2
    players = [(name, solver) for name, solver in zip(args[0:2*n-1:2], args[1:2*n:2])]
    prime_daihinmin = PrimeDaihinmin(players)
    if prime_daihinmin.initialize():
        prime_daihinmin.play()
        prime_daihinmin.finish()
    print("time (s): {:.3f}".format(time.time() - start_time), file=sys.stderr) ###

if __name__ == "__main__":
    main()