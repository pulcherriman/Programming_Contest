import subprocess
import pipes
import multiprocessing
import os
from tqdm import tqdm

OUTPUTS_DIR = './tester/out'
SCORES_DIR = './tester/scores'
CASE = 300
TL = 3.0

def execute_case(seed):
	input_file_path = f'tools/in/{seed:04}.txt'
	output_file_path =f'{OUTPUTS_DIR}/out_{seed:04}.txt'
	score_file_path = f'{SCORES_DIR}/score_{seed:04}.txt'

	with open(input_file_path, 'r') as fin:
		with open(output_file_path, 'w') as fout:
			try:
				subprocess.run(['./../../a.exe'], stdin=fin, stdout=fout, stderr=subprocess.DEVNULL, timeout=TL)
			except subprocess.TimeoutExpired as e:
				print(seed, "TimeoutExpired", flush=True)
				raise e 

	with open(score_file_path, 'w') as fscore:
		subprocess.run(['./tools/vis.exe', input_file_path, output_file_path], stdout=fscore, stderr=fscore)
	
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


if __name__ == '__main__':
	main()