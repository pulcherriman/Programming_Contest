import subprocess
import pipes
import multiprocessing
import os
from tqdm import tqdm

OUTPUTS_DIR = './tester/out'
SCORES_DIR = './tester/scores'
CASE = 2000
TL = 2.2

def execute_case(seed):
	input_file_path = f'tools/in/{seed:04}.txt'
	output_file_path =f'{OUTPUTS_DIR}/out_{seed:04}.txt'
	score_file_path = f'{SCORES_DIR}/score_{seed:04}.txt'

	with open(input_file_path, 'r') as fin:
		with open(output_file_path, 'w') as fout:
			subprocess.run(['./../../a.exe'], stdin=fin, stdout=fout, stderr=subprocess.DEVNULL, timeout=TL)

	with open(score_file_path, 'w') as fscore:
		subprocess.run(['./tools/vis.exe', input_file_path, output_file_path], stdout=fscore)
	
	with open(score_file_path, 'r') as fscore:
		result = fscore.read()

	return seed, result

def main():
	os.makedirs(OUTPUTS_DIR, exist_ok=True)
	os.makedirs(SCORES_DIR, exist_ok=True)
	scores = []
	count = 0
	with multiprocessing.Pool(max(1, multiprocessing.cpu_count()-2)) as pool:
		with tqdm(total=CASE, desc='exec') as pbar:
			for seed, score in pool.imap(execute_case, range(0,CASE)):
				try:
					scores.append((int(score.split()[2]), f'{seed:04}'))
				except ValueError:
					print(seed, "ValueError", flush=True)
					print(score, flush=True)
					exit()
				except IndexError:
					print(seed, "IndexError", flush=True)
					print(f"error: {score}", flush=True)
					exit()
				count += 1
				pbar.update()
	print()

	scores.sort()
	total = sum([s[0] for s in scores])
	ave = total / CASE

	scores.sort(key=lambda x: x[1])
	with open('./summary.txt', 'w') as fout:
		fout.write(f'ave   : {ave}\n')
		fout.write(f'sum50 : {ave*50}\n')
		fout.write(f'max   : {scores[-1]}\n')
		fout.write(f'min   : {scores[0]}\n')
		for s in scores:
			fout.write(f'{s[1]} : {s[0]}\n')
	subprocess.run('code ./summary.txt', shell=True)


if __name__ == '__main__':
	main()