# 概要

このサンプルは、 簡単な bash コマンドやシェルスクリプトを記述するチャレンジの一例である。このようなチャレンジは、ファイルの内容を抽出して出力する能力や、効率的にファイル操作する能力を問う場合に適している。

このサンプルは以下のようなファイル構造になっている。

# ディレクトリ構造

ディレクトリ構造は以下である。

- README.md : 日本語問題文。
- README_en.md : 英語問題文。
- solution/script$x.sh : 想定解。solution ディレクトリ以下に存在する .sh ファイルは、想定解として企業に公開されるので注意。
- solution.md : 想定解を説明する文章。企業に公開されるので注意。
- track.yml : チャレンジのメタ情報。後述。
- test
  - basic_test.js : 公開テストケースを定義する。basic ディレクトリ以下に配置するテストケースを参照する。
  - secret_test.js : 非公開テストケースを定義する。secret ディレクトリ以下に配置するテストケースを参照する。
  - (judge.cpp) : カスタムジャッジの場合には実装する。
  - before_init.sh : テストケースを初期化する前に共通で実行される。（編集する必要はありません）
  - recover.sh : ジャッジを実行した後に実行される。（編集する必要はありません）
  - check_diff_stdout.sh : 受験者の標準出力と期待する標準出力を比較して、正誤判定を行う。（編集する必要はありません）
  - check_diff_file.sh : 受験者のファイル出力と期待するファイル出力を比較して、正誤判定を行う。（編集する必要はありません）
  - debug.js : デバッグ機能を使用するときに実行されるファイル（**編集する必要があります**）
  - basic
    - initialize.sh : ジャッジに用いるテストケースを作成する。（**編集する必要があります**）
    - step1
      - (initialize.sh) : Step 毎に個別のテストケースを作成したいときに使用する。（**編集する必要があります**）
      - judge.sh : 受験者のコードの正誤判定を行う。終了コード 2 以上で終了したとき、不正解になる。それ以外の場合、正解になる。（**編集する必要があります**）
    - step2
      - (initialize.sh)
      - judge.sh
    - ...
  - secret
    - initialize.sh
    - step1
      - (initialize.sh)
      - judge.sh
    - ...

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

- check_diff_stdout.sh
  - 受験者の標準出力と期待する標準出力を比較し、正誤判定を行う。誤っている場合、デバッグのための出力も行う。
- check_diff_file.sh
  - 受験者のファイル出力と期待するファイル出力を比較し、正誤判定を行う。誤っている場合、デバッグのための出力も行う。

# 作問フロー
- 問題文 README.md、想定解 solution/script.$x.sh、解説 solution.md、テストケースの初期化 test/basic/initialize.sh、ジャッジ test/basic/judge.sh を書く。
- 必要に応じて `debug.js` を編集する。
- `track-test test .`によってチャレンジの構造が正しいかを確認する。

