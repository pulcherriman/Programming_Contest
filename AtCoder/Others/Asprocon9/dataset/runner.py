import sys, threading
from subprocess import Popen, PIPE

if len(sys.argv) < 5:
    print('usage: {} ./judge input-file output-file ./your_solution [args...]'.format(sys.argv[0]))
    exit(0)

judge_command = sys.argv[1:4]
sol_command = sys.argv[4:]

proc_judge = Popen(judge_command, stdin=PIPE, stdout=PIPE, stderr=PIPE, text=True)
proc_sol = Popen(sol_command, stdin=proc_judge.stdout, stdout=proc_judge.stdin, stderr=None)

thread_judge = threading.Thread(target=proc_judge.wait)
thread_sol = threading.Thread(target=proc_sol.wait)

thread_judge.start()
thread_sol.start()
thread_judge.join()
thread_sol.join()
print(*proc_judge.stderr.readlines(), sep='', end='')
