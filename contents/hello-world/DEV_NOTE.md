# 概要
アルゴリズム問題のテンプレートです。`test/settings.json`で設定できます。

- 問題のタイプ `isSpecial = false/true`
  - 入出力が厳密に決まっている 
  - 出力が複数許容されるので、答えがあっているかを確認する必要がある

入出力の方法を4通り選ぶことができます。

- 入力 `isFileInput = false/true`
  - 引数自体で値を渡す
  - 引数にファイルのパスを与える
- 出力 `isFileOutput = false/true`
  - 標準出力
  - `answer.txt`を作成して、そこに書き込ませる

# テストケース
- 入出力パターンをファイルで保存する
  - 公開テストは`test/in/basic/*.in`と`test/out/basic/*.out`
  - 公開テストは`test/in/secret/*.in`と`test/out/secret/*.out`
- 引数で入力を与える場合
  - `test/in/basic/*.in`を1行に連結した文字列を、引数として与えることになる

- ジャッジにおいて、改行・空白の個数は問わない
  - つまり、余計な改行やスペースが入っていても、値が合っていればOK扱いとなる。

- 誤答時にのみ、入力・ユーザの出力・期待される出力を、要約して出力する

# 作問ツール
- 流れ
  - テストケースジェネレータ`input`を作成
    - 引数を入力として、標準出力に生成したテストケースを出力する
  - `test/script/generate_testcases.sh`を書く
    - `test/in/basic/*.in`, `test/in/secret/*.in`を作成する
  - `test/script/generate_output.sh`を開き、想定解を変数`solution`に設定し、実行する
    - `test/in/basic/*.in`から`test/out/basic/*.out`を自動生成する
    - `test/in/secret/*.in`から`test/out/secret/*.out`を自動生成する
  - `node generate_json.js`を実行する
    - 注意！これは`test/basic_testcases.json, test/secret_testcases.json`を上書きする
  - `test/basic_testcases.json, test/secret_testcases.json`のdescriptionを書く
