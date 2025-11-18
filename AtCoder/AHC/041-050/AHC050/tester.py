import subprocess
import os
import concurrent.futures
import signal
import sys
from tqdm import tqdm

OUTPUTS_DIR = './tester/out'
SCORES_DIR = './tester/scores'
LOGS_DIR = './tester/log'
CASE = 100
TL = 40.0

running_processes = []
executor = None
def execute_case(seed):
    input_file_path = f'tools/in/{seed:04}.txt'
    output_file_path = f'{OUTPUTS_DIR}/out_{seed:04}.txt'
    score_file_path = f'{SCORES_DIR}/score_{seed:04}.txt'
    log_file_path = f'{LOGS_DIR}/log_{seed:04}.txt'

    with open(input_file_path, 'r') as fin, open(output_file_path, 'w') as fout, open(log_file_path, 'w') as flog:
        proc = None
        try:
            proc = subprocess.Popen(['./../../a.exe'], stdin=fin, stdout=fout, stderr=flog)
            running_processes.append(proc)
            proc.wait(timeout=TL)
            if proc.returncode != 0:
                raise RuntimeError(f"a.exe exited abnormally with code {proc.returncode}")
        except subprocess.TimeoutExpired as e:
            print(seed, "TimeoutExpired", flush=True)
            proc.terminate()
            raise e
        finally:
            if proc in running_processes:
                running_processes.remove(proc)

    with open(score_file_path, 'w') as fscore:
        proc = subprocess.Popen(['./tools/vis.exe', input_file_path, output_file_path], stdout=fscore, stderr=fscore)
        running_processes.append(proc)
        proc.wait()
        running_processes.remove(proc)
    
    with open(score_file_path, 'r') as fscore:
        result = fscore.read()

    if not result:
        raise RuntimeError(f"Score result is empty for seed {seed}")
    
    return seed, result

def getExecuteTime(log_file):
    with open(log_file, 'r') as f:
        lines = f.readlines()
        if lines:
            return int(lines[-1].split(" ")[0])
    return 0

def signal_handler(sig, frame):
    print("\nInterrupted, terminating...")
    for proc in running_processes:
        proc.terminate()
    if executor:
        executor.shutdown(wait=False, cancel_futures=True)
    print("All processes and executor terminated. Exiting...")
    sys.exit(1)

def main():
    global executor
    signal.signal(signal.SIGINT, signal_handler)
    os.makedirs(OUTPUTS_DIR, exist_ok=True)
    os.makedirs(SCORES_DIR, exist_ok=True)
    os.makedirs(LOGS_DIR, exist_ok=True)
    scores = []
    
    executor = concurrent.futures.ThreadPoolExecutor(max_workers=max(2, os.cpu_count() - 2))
    futures = {executor.submit(execute_case, seed): seed for seed in range(CASE)}
    
    try:
        with tqdm(total=CASE, desc='exec') as pbar:
            for future in concurrent.futures.as_completed(futures):
                seed = futures[future]
                try:
                    seed, score = future.result()
                    if score is None:
                        raise RuntimeError(f"Case {seed} returned None")
                    scores.append((int(score.split()[2]), f'{seed:04}'))
                    tqdm.write(str(sum(s[0] for s in scores) / len(scores)))
                except Exception as e:
                    print(f"Error in case {seed}: {e}", flush=True)
                    for f in futures:
                        f.cancel()
                    executor.shutdown(wait=False, cancel_futures=True)
                    sys.exit(1)
                pbar.update()
    except KeyboardInterrupt:
        print("\nKeyboardInterrupt detected, shutting down...")
        for proc in running_processes:
            proc.terminate()
        executor.shutdown(wait=False, cancel_futures=True)
        print("Shutdown complete. Exiting...")
        sys.exit(1)
    finally:
        executor.shutdown(wait=False)
    print()

    scores.sort()
    total = sum(s[0] for s in scores)
    ave = total / CASE

    with open('./summary.txt', 'w') as fout:
        fout.write(f'ave\t{ave}\n')
        fout.write(f'sum150\t{ave*150}\n')
    
        scores.sort(key=lambda x: x[0])
        fout.write(f'max\t{scores[-1][0]}\n')
        fout.write(f'min\t{scores[0][0]}\n')
    
        scores.sort(key=lambda x: x[1])
        for s in scores:
            fout.write(f'{s[1]}\t{s[0]}\n')
    subprocess.run('code ./summary.txt', shell=True)
    
    max_time = 0
    max_file = ""
    for log_file in os.listdir(LOGS_DIR)[:CASE]:
        log_path = os.path.join(LOGS_DIR, log_file)
        exec_time = getExecuteTime(log_path)
        if exec_time > max_time:
            max_time = exec_time
            max_file = os.path.splitext(log_file)[0]
    
    print(f"max execute time: {max_time}ms in Case: {max_file}")

if __name__ == '__main__':
    main()
