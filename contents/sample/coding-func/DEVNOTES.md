# 概要

このサンプルは、厳密に入出力が決まる関数実装プログラムを作成するチャレンジの一例である。このようなチャレンジは、if 文や for 文といった基本的なコーディング能力や、アルゴリズムを構築する能力を問う場合に適している。

このサンプルは以下のようなファイル構造になっており、後述のツールを使ってテストケースなどが生成されている。

# ディレクトリ構造

ディレクトリ構造は以下である。

- README.md : 日本語問題文
- README_en.md : 英語問題文
- solution.cpp : C++ 想定解。solution.言語名の構造を取るものは、想定解として企業に公開されるので注意。
- solution.py : C++ 想定解。solution.言語名の構造を取るものは、想定解として企業に公開されるので注意。
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
      - 00_sample1.in.json : 入力ファイル。
      - 10_small1.in.json
      - ...
    - secret
      - 20_sample1.in.json
      - 30_small1.in.json
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

# basic_testcases.json, secret_testcases.json

テストケース毎に、入力ファイル、出力ファイル、テストケースの日本語説明、テストケースの英語説明を定義することができる。ただし、英語での作問をしない場合には、テストケースの英語説明は省略できる。ファイルの内容の例は以下である。

```plain
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

```plain
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

function: では、受験者が実行すべき関数について、その入出力の変数の型・名前・説明を定義する。type は、int, string, float, boolean、及びその配列と二次元配列を指定することができる。以下が設定例である。

```plain
function:
  name: "getStudentInfo"
  arguments:
    - name: age
      type: int
      description: "Age."
    - name: subjects
      type: string[]
      description: "Array of subjects"
    - name: scores
      type: float[][]
      description: "2D array of scores"
  result:
    type: string[]
    description: "Retern value"
```

現在の関数実装スタイルでは、各入出力の型に下記の制限があることに注意が必要である。

- int は double 型の整数範囲しかサポートできないため、整数の入出力制約を ±10^15 に抑える必要がある。
- 入力において、string 変数に空白文字を含めることはできない。

# 作問フロー
- 問題文 README.md、想定解 solution.拡張子、解説 solution.md、テストケースの入力ファイル`test/in/**/*.in.json`を書く。
- テストケースの入力ファイル`test/in/**/*.in.json`に対応する、出力ファイル`test/in/**/*.out`を作成する。
- track.yml に `test/basic_testcases.json`と`test/secret_testcases.json`にテストケースを追加する
- track.yml に open, secret テストケースの数を記述する。
