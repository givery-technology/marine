# 概要

このサンプルは、厳密に入出力が決まる CLI プログラムを作成するチャレンジの一例である。このようなチャレンジは、if 文や for 文といった基本的なコーディング能力や、アルゴリズムを構築する能力を問う場合に適している。

このサンプルは以下のようなファイル構造になっており、後述のツールを使ってテストケースなどが生成されている。

# ディレクトリ構造

ディレクトリ構造は以下である。

- README.md : 日本語問題文
- README_en.md : 英語問題文
- solution.cpp : C++ 想定解。solution.言語名の構造を取るものは、想定解として企業に公開されるので注意。
- solution.partial.cpp : C++ 部分点解答。命名規則は solution から始まれば自由。
- solution.md : 想定解を説明する文章。企業に公開されるので注意
- track.yml : チャレンジのメタ情報。後述。
- test
  - basic.js : 編集しない。受験者がテスト実行ボタンを押すと、`mocha basic.js`が走る。
  - basic_testcases.json : 公開テストケースを定義する。後述。
  - secret.js : 編集しない。受験者に見えないテストケースをジャッジするため、`mocha secret.js`が裏で走る。
  - secret_testcases.json : 非公開テストケースを定義する。
  - (judge.cpp) : カスタムジャッジの場合には実装する。
  - in
    - basic
      - 00_sample1.in : 入力ファイル。
      - 00_sample1.desc : 入力ファイルの日本語説明。"[EvaluationPoint] 説明文"の構造の文章を一行含む。中間ファイル。
      - 00_sample1.desc_en : 入力ファイルの英語説明。"[EvaluationPoint] Explanation"の構造の文章を一行含む。中間ファイル。
      - 10_small1.in
      - ...
    - secret
      - 20_sample1.in
      - 30_small1.in
      - ...
  - out
    - basic
      - 00_sample1.out : 出力ファイル。
      - 10_small1.out
      - ...
    - secret
      - 20_sample1.out
      - 30_small1.out
      - ...
  - scripts
    - 後述。

# basic_testcases.json, secret_testcases.json

テストケース毎に、入力ファイル、出力ファイル、テストケースの日本語説明、テストケースの英語説明を定義することができる。ただし、英語での作問をしない場合には、テストケースの英語説明は省略できる。ファイルの内容の例は以下である。

```
[
   {
      "input": "in/basic/00_sample1.in",
      "output": "out/basic/00_sample1.out",
      "description": "[基本実装] 入力数列のサイズが3である場合に正答できる (a = [3, 1, 5])",
      "description_en": "[Basic Case] Correct when the size of the input array is 3 (a = [3, 1, 5])"
   },
   {
      "input": "in/basic/00_sample2.in",
      "output": "out/basic/00_sample2.out",
      "description": "[基本実装] 入力数列のサイズが8である場合に正答できる (a = [1, 43, 6, 2, 7, 83, 2, 6])",
      "description_en": "[Basic Case] Correct when the size of the input array is 8 (a = [1, 43, 6, 2, 7, 83, 2, 6])"
   },
```

description, description_en は、`[EvaluationPoint] 説明文` の形式で書かれる。EvaluationPoint は、テストケースの分類を表す。例えば、O(n^2) 解が書けていれば通るテストケースには [Small]、O(n log n) 解を要するテストケースには [Large] と分類するといったことができる。説明文は、受験者にどのようなテストケースで成功/失敗しているのかを教えるため、また企業の採用者がどのようなテストケースで受験者が躓いているのかを把握するために書かれる。

# track.yml
チャレンジのメタ情報を定義する。この中では主に、テストケース数と EvaluationPoint の説明を行う。以下が抜粋である。

```
testcases:
  open: 24
  secret: 22

evaluationPoint:
  "基本実装" : "与えられた数列の最小値、最大値を判定するプログラムとソートアルゴリズムを正しく実装することができます。比較演算子を用いた数値比較、小さい値からのソートプログラム、文字列への変換とデータの連結という基本的なプログラミング能力を持つことがわかります。"
  "Basic Case" : "The examinee can implement a program that returns correct output for small data. He/She has the coding skills to implement a simple sorting, string manipulations and numeral operations."
  "大規模なデータ入力を扱う実装" : "解答する上で必要なプログラミングスキルや解法等を記載致します。"
  "Large Case" : "The examinee can implement a program that returns correct output for small data. He/She has the coding skills to implement a advanced sorting, string manipulations and numeral operations."
```

evaluationPoint: では、basic_testcases.json と secret_testcases.json で定義された全ての EvaluationPoint が説明されていなければならない。この説明は企業に公開されており、この分類に該当するテストケースで正答した受験者がどのようなスキルを持っているのかを定性的に理解させるために書かれている。

# スクリプト

test/scripts には作問に便利なツールが用意されている。

- generate_output.sh
  - それぞれの `test/in/**/*.in` に対応する、`test/out/**/*.out` を生成します。生成のために使うプログラムを変更するには、直接 generate_output.sh を修正して下さい。
- generate_desc.sh
  - それぞれの `test/in/**/*.in` を description_generator.cpp の標準入力に流し、`test/in/**/*.desc` と `test/in/**/*.desc_en` を生成します。description_generator.cpp は、入力ファイルを標準入力から受け取り、日本語の description を標準出力に、英語の description_en を標準エラー出力に出力します。generate_desc.sh は、description_generator.cpp の出力を受け取り、`test/in/**/*.desc`と`test/in/**/*.desc_en`を生成します。
- node generate_json.js
  - 全ての `test/in/**/*.in`, `test/out/**/*.out`, `test/in/**/*.desc`, `test/in/**/*.desc_en` を集めて、basic_testcases.json と secret_testcases.json ファイルに統合します。


# 作問フロー
- 問題文 README.md、想定解 solution.拡張子、解説 solution.md、テストケースの入力ファイル`test/in/**/*.in`を書く。
- test/scripts フォルダに移動する。
- `./generate_output.sh`で`test/out/**/*.out`を生成する。
- description_generator.cpp を完成させる。`./generate_description.sh`を実行して、`test/in/**/*.desc`と`test/in/**/*.desc_en`を生成する。
- `node generate_json.js`を実行して、`test/basic_testcases.json`と`test/secret_testcases.json`が生成されていることを確認する。
- track.yml に open, secret テストケースの数を記述する。
- track.yml に `test/basic_testcases.json`と`test/secret_testcases.json`に含まれる全ての evaluationPoint について、説明文を書く。
- `track-test test .`によってチャレンジの構造が正しいかを確認する。
