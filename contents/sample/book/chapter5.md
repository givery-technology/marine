# エクササイズの作り方
このチャプターではリモート及びフロントエンドのエクササイズの作成の仕方を説明します。

## リモートエクササイズを作成する
引数`name`をとり、`Hello [name]`を返す関数を作成しなさい。

---
リモートエクササイズを作成するには`exercise`セクションに`mode: remote`と、ユーザに編集させるファイルとテストを指定します。

テストでは`ok xxxxx` または`not ok xxxxxx`という行が複数出力されるようにしてください。
テストの実行によって標準出力が以下の条件を満たす場合にクリアと判定されます。

- コンパイルエラー、または実行時エラーになっていない
- `ok `で始まる行が1つ以上ある
- `not ok `で始まる行がない

### exercise

- build: javac -J-Duser.language=ja *.java
- file: [Main.java](chapter5/Section1_Main.java)
- hidden: [Test.java](chapter5/Section1_Test.java)
- mode: remote
- command: java Test

### env

- imageName: givery/track-java-8

### hint
`ok xxxx`, `not ok xxxxx`という書式は[TAP](https://testanything.org/)というテストプロトコルに基づいたものです。

TAPをサポートしたテストフレームワークを使えばもっと簡単にテストを作成することができますが、ライブラリへの依存度が高まることと現状全てのDockerイメージにテストフレームワークがプリインストールされているわけではないことから、自力で結果を出力する方式を取ることが多いです。

ユーザ要件が固まれば、方式を整備してもう少しエクササイズを簡単に作成できるようになるかもしれません。

## リモートエクササイズの注意点
整数除算を行うメソッド`divide`を実装しなさい。
ただし、除数(`b`)が0の場合の返り値は0とします。

---
前セクションで説明したとおり、テストの判定は

- コンパイルエラー、または実行時エラーになっていない
- `ok `で始まる行が1つ以上ある
- `not ok `で始まる行がない

の3つの条件を満たすことです。

このため、実行時エラーをキャッチした際に`not ok`の出力を忘れると、すべてのテストをパスしていないにも関わらずクリアとなってしまうことがありえます。

実行時エラーが発生すると以降のテストが走らなくなるため、極力実行時エラーはテスト内で処理した方が良いのですが、不正にクリアとならないようにこの点には注意が必要です。


### exercise

- build: javac -J-Duser.language=ja *.java
- file: [Main.java](chapter5/Section2_Main.java)
- hidden: [Test.java](chapter5/Section2_Test.java)
- mode: remote
- command: java Test

### env

- imageName: givery/track-java-8

## Rubyエクササイズの例
整数除算を行うメソッド`divide`を実装しなさい。
ただし、除数(`b`)が0の場合の返り値は0とします。

### exercise

- file: [main.rb](chapter5/Section3_main.rb)
- hidden: [test.rb](chapter5/Section3_test.rb)
- mode: remote
- command: ruby test.rb

### env

- imageName: givery/track-ruby-2.5

## Pythonエクササイズの例
整数除算を行うメソッド`divide`を実装しなさい。
ただし、除数(`b`)が0の場合の返り値は0とします。

### exercise

- file: [main.py](chapter5/Section4_main.py)
- hidden: [test.py](chapter5/Section4_test.py)
- mode: remote
- command: python3 test.py

### env

- imageName: givery/track-python-3.6

## フロントエンドエクササイズの作り方
足し算を行うメソッド`add`を実装しなさい。

---
フロントエンドエクササイズを作成するには`exercise`セクションに`mode: client`と、ユーザに編集させるファイルを指定します。
(ユーザに編集させたくないファイルは`files`セクションで指定します。)

テストコードは[mocha](https://mochajs.org/)と[chai](http://www.chaijs.com/)を使って記述することができ、`exercise`セクションに`test`というキーで指定します。(mochaとchai、およびテストのjsは自動的にindex.htmlに差し込まれます。)

フロントエンドテストではただ単にユニットテストを実行するだけでなく、同時にindex.htmlでの表示やインタラクションの変化も同時にユーザに提示することができます。
(この問題の場合に保存後に「計算」ボタンをクリックして動作を確認することができます。)


### files
- [index.html](chapter5/Section5_index.html)

### exercise
- mode: client
- file: [main.js](chapter5/Section5_main.js)
- test: chapter5/Section5_test.js

## コードの一部のみ編集可能にする
前セクションの例では、`main.js`の下部にはボタンクリック時の処理が記述されていました。
この部分はユーザに変更されたくはない内容です。

この場合、ファイル中に`EXERCISE_BEGIN_EDIT`, `EXERCISE_END_EDIT`という文字列を含む行を挿入することで編集可能な範囲を制限することができます。


### files
- [index.html](chapter5/Section5_index.html)

### exercise
- mode: client
- file: [main.js](chapter5/Section6_main.js)
- test: chapter5/Section5_test.js

### hint
リモートエクササイズでも同様に`EXERCISE_BEGIN_EDIT`, `EXERCISE_END_EDIT`を指定することによって編集可能範囲を制限できます。
