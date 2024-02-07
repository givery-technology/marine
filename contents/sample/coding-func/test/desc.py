import os
import json

def summarize_inputs(input_dir):
    summaries = []
    # ディレクトリを再帰的に走査
    for root, dirs, files in os.walk(input_dir):
        for file in files:
            if file.endswith(".in.json"):
                input_path = os.path.join(root, file)
                output_path = input_path.replace("in/", "out/").replace(".in.json", ".out")
                input_path = input_path.replace(".in.json", ".in")
                
                # ここではサンプルの説明を使いますが、実際にはファイルから読み込むか、
                # 別の方法で説明を生成する必要があります。
                with open(input_path+".json", 'r') as file:
                    data = json.load(file)
                description = "ここに適切な説明を設定します。"
                description_en = "Set the appropriate description here."

                summary = {
                    "input": input_path.replace("\\", "/"),
                    "output": output_path.replace("\\", "/"),
                    "description": description,
                    "description_en": description_en
                }
                summaries.append(summary)
                
    return summaries

def write_summaries_to_file(summaries, output_file):
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(summaries, f, ensure_ascii=False, indent=3)

# 入力ディレクトリと出力ファイルを指定
input_dir = './in/basic'
output_file = 'summaries.json'

# 要約の生成とファイルへの書き込み
summaries = summarize_inputs(input_dir)
write_summaries_to_file(summaries, output_file)

print(f"Summary written to {output_file}")
