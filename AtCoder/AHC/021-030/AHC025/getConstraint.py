# ファイル名のフォーマットを確認し、0埋めの4桁の通し番号として扱います。
output_file = 'constraint.txt'

# 結果を保存するリスト
lines = []

# 5000のファイルを順番に処理します。
for i in range(5000):
    # ファイル名を生成します。
    file_name = f"tools/in/{i:04}.txt"
    
    # ファイルを開いて1行目だけを読みます。
    with open(file_name, 'r', encoding='utf-8') as f:
        line = f.readline().strip()  # 1行だけ読み、改行を削除します。
        lines.append(line)

# constraint.txt に結果を出力します。
with open(output_file, 'w', encoding='utf-8') as f:
    for line in lines:
        f.write(line + '\n')
