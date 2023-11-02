import re

# 出力ファイル名
output_file = 'xInfo.txt'

# 正規表現を用いて "# x "に続く3つの数字をマッチング
pattern = re.compile(r'# query usage:  (\d+) (\d+) (\d+)')

# 結果を保存するリスト
lines = []

# 5000のファイルを順番に処理します。
for i in range(5000):
    # ファイル名を生成します。
    file_name = f"tester/out/out_{i:04}"
    
    with open(file_name, 'r', encoding='utf-8') as f:
        for line in f:
            match = pattern.search(line)
            if match:
                # 3つの数字を取り出し、タブで連結
                extracted = "\t".join(match.groups())
                lines.append(extracted)
                break

# getXInfo.txt に結果を出力します。
with open(output_file, 'w', encoding='utf-8') as f:
    for line in lines:
        f.write(line + '\n')