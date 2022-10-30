import subprocess
import pipes
import multiprocessing
import os


PIPEFILES_DIR = './tester/pipefiles'
CASE = 50
TL = 5.0

def execute_case(seed):
	input_file_path = f'tools/in/{seed:04}.txt'
	output_file_path = f'tools/out/{seed:04}.txt'
	with open(input_file_path) as fin:
		with open(output_file_path, 'w') as fout:
			subprocess.run(['../../a.exe'], stdin=fin, stdout=fout, stderr=subprocess.DEVNULL, timeout=TL)
			pipefile = f'{PIPEFILES_DIR}/pipefile_{seed:04}'
			with pipes.Template().open(pipefile, 'w') as p:
				subprocess.run(['tools/target/release/vis', input_file_path, output_file_path], stdout=p, timeout=TL)
			output = open(pipefile).read()
			assert output
	return seed, output

def main():
	os.makedirs(PIPEFILES_DIR, exist_ok=True)
	scores = []
	count = 0
	with multiprocessing.Pool(max(1, multiprocessing.cpu_count()-2)) as pool:
		for seed, score in pool.imap_unordered(execute_case, range(101,CASE+101)):
			print(count%10, end='', flush=True)
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
	print()
	scores.sort()
	total = sum([s[0] for s in scores])
	ave = total / CASE
	print(f'total: {total}')
	print(f'max: {scores[-1]}')
	print(f'ave: {ave}')
	print(f'min: {scores[0]}')
	with open('./summary.txt', 'w') as fout:
		fout.write(f'total : {total}\n')
		fout.write(f'ave   : {ave}\n')
		fout.write(f'max   : {scores[-1]}\n')
		fout.write(f'min   : {scores[0]}\n')
		scores.sort(key=lambda x: x[1])
		for s in scores:
			fout.write(f'{s[1]} : {s[0]}\n')


if __name__ == '__main__':
	main()