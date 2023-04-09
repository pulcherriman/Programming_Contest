import subprocess
import pipes
import multiprocessing
import os


OUTPUTS_DIR = './tester/out'
SCORES_DIR = './tester/scores'
CASE = 1000
TL = 5.0


def execute_case(args):
	seed, suffix = args
	input_file_path = f'tools/in{suffix}/{seed:04}.txt'
	with open(input_file_path) as fin:
		output = f'{OUTPUTS_DIR}/out_{seed:04}'
		with pipes.Template().open(output, 'w') as outputStream:
			subprocess.run(['./../../a.exe'], stdin=fin, stdout=outputStream, timeout=TL)
		result = open(output).read()
	return seed, result

def eval_case(args):
	seed, suffix = args
	input_file_path = f'tools/in{suffix}/{seed:04}.txt'
	output_file_path =f'{OUTPUTS_DIR}/out_{seed:04}'

	output = f'{SCORES_DIR}/score_{seed:04}'
	with pipes.Template().open(output, 'w') as fout:
		subprocess.run(['./tools/vis.exe', input_file_path, output_file_path], stderr=fout)
	result = open(output).read()
	return seed, result

def main(SUFFIX):
	os.makedirs(OUTPUTS_DIR, exist_ok=True)
	os.makedirs(SCORES_DIR, exist_ok=True)

	
	scores = []
	count = 0
	with multiprocessing.Pool(max(1, multiprocessing.cpu_count()-2)) as pool:
		for seed, score in pool.imap_unordered(execute_case, zip(range(0,CASE), [SUFFIX]*CASE)):
			print(count%10, end='', flush=True)
			count += 1
	print()

	count = 0
	with multiprocessing.Pool(max(1, multiprocessing.cpu_count()-2)) as pool:
		for seed, score in pool.imap_unordered(eval_case, zip(range(0,CASE), [SUFFIX]*CASE)):
			print(count%10, end='', flush=True)
			try:
				scores.append((int(score.split()[3]), f'{seed:04}'))
			except ValueError:
				print(seed, "ValueError", flush=True)
				print(score, flush=True)
				exit()
			except IndexError:
				print(seed, "IndexError", flush=True)
				print(f"error: {score}", flush=True)
				exit()
			count += 1
	print()

	scores.sort()
	total = sum([s[0] for s in scores])
	ave = total / CASE
	print(f'total: {total}')
	print(f'max: {scores[-1]}')
	print(f'ave: {ave}')
	print(f'min: {scores[0]}')

	scores.sort(key=lambda x: x[1])
	with open(f'./summary{SUFFIX}.txt', 'w') as fout:
		fout.write(f'ave\t{ave}\n')
		fout.write(f'sum50\t{ave*50}\n')
		for s in scores:
			fout.write(f'{s[1]}\t{s[0]}\n')

if __name__ == '__main__':
	# SUFFIX = ''
	# C = input('C: ')
	# if C != '' and C != '0':
	# 	SUFFIX = f'_C{C}'
	# main(SUFFIX)
	suffixes = [
		'', '_C1', '_C2', '_C4', '_C8', '_C16',
		'_C32', '_C64', '_C128', '_C_11'
	]
	for SUFFIX in suffixes:
		main(SUFFIX)