#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""tadashi's PrimeDaihinmin Solver (C) 2019 Fixstars Corp.
"""

import sys
import os
import random
import itertools
import json

VERSION  = "0.07"
REVISION = "a"
VER_DATE = "20191225"

TIME_LIMIT = 10.0
DEBUG_PRINT = False

def debug_print(msg):
    if DEBUG_PRINT:
        print(msg, file=sys.stderr)

# Miller-Rabin primality test
def is_prime(q, k=50):
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

def make_candidate(hand, length):
    h = hand[:]
    if length == 1:
        h = list(set(h) & {2, 3, 5, 7})
        return [random.choice(h)] if h else None
    hh = [x for x in h if x > 0]
    ht = [x for x in h if x in (1, 3, 7, 9)]
    if not ht:
        return None
    tail = random.choice(ht)
    hh.remove(tail)
    if not hh:
        return None
    head = random.choice(hh)
    h.remove(tail)
    h.remove(head)
    remain = length - 2
    m = random.sample(h, remain)
    return [head] + m + [tail]

def solver(hand, number, length):
    if len(hand) < length:
        return None
    for _ in range(10000):
        candidate = make_candidate(hand, length)
        if candidate:
            n = int("".join(map(str, candidate)))
            if n > number and is_prime(n):
                return candidate
    return None

def main(args):
    global TIME_LIMIT

    hand = []
    num_first_cards = 5

    while True:
        text = sys.stdin.readline().strip()
        data = json.loads(text)
        action = data["action"]
        if action == "play":
            name = data["name"]
            hand = data["hand"]
            numbers = list(map(int, data["numbers"]))
            record = data["record"]
            hands = data["hands"]
            debug_print("name: {}".format(name)) ###
            debug_print("hand: {}".format(hand)) ###
            debug_print("record: {}".format(record)) ###
            debug_print("hands: {}".format(hands)) ###
            length = len("".join(map(str, numbers)))
            if length == 0:
                if len(hand) <= num_first_cards:
                    length = len(hand)
                else:
                    length = random.randint(1, num_first_cards)
            cards = solver(hand, numbers[-1] if numbers else 0, length)
            if cards is not None:
                jsondata = json.dumps({"action": "number", "cards": cards})
            else:
                jsondata = json.dumps({"action": "pass"})
            sys.stdout.write("{}\n".format(jsondata))
            sys.stdout.flush()
        elif action == "pass":
            draw = data["draw"]
            hand.extend(draw)
            hand.sort()
            sys.stdout.write("\n")
            sys.stdout.flush()
        elif action == "init":
            uid = data["uid"]
            names = data["names"]
            name = names[uid]
            hand = data["hand"]
            TIME_LIMIT = data["time"]
            sys.stdout.write("\n")
            sys.stdout.flush()
        elif action == "quit":
            sys.stdout.flush()
            break

if __name__ == "__main__":
    main(sys.argv)