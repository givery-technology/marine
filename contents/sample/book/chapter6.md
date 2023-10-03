# プレイグラウンドの作り方
このチャプターではリモート及びフロントエンドのプレイグラウンドの作成の仕方を説明します。
プレイグラウンドは「遊び場」という意味でユーザに自由にコードを編集して実行可能なセクションを提供します。

## リモートプレイグラウンドの作成
プレイグラウンドの作成方法はほとんどエクササイズと同じです。
ただ、内容を定義するセクションの名前を`exercise`ではなく、`playground`とします。

ここでは5章で使用したエクササイズのコードをそのまま使用していますが、プレイグラウンドはテストではないので、ok/not okが出力されたからといって、特になにかがあるわけではありません。


### playground

- mode: remote
- build: javac -J-Duser.language=ja *.java
- file: [Main.java](chapter5/Section1_Main.java)
- file: [Test.java](chapter5/Section1_Test.java)
- command: java Test

### env

- imageName: givery/track-java-8

### hint
ここでは、Main.javaとTest.javaの両方をplaygroundのfileとして指定しているのでどちらも編集可能です。

もしもTest.javaは編集させたくないのであれば、Test.javaを`files`セクションの方で指定します。

## フロントエンドプレイグラウンドの作成
フロントエンドプレイグラウンドの場合も作成方法はほとんど同じです。
プレイグラウンドでは`test`は差し込めません。


### playground

- mode: client
- file: [main.js](chapter5/Section5_main.js)

### files
- file: [index.html](chapter5/Section5_index.html)

### hint
現在プレイグラウンドでは`EXERCISE_BEGIN_EDIT`, `EXERCISE_END_EDIT`は使用できません。
(必要ならば今後実装を検討します。)

## 前のセクションの内容でプレイグラウンドを作成する
プレイグラウンドでは外部ファイルの代わりに以前に作成したセクションの内容を参照することもできます。

### playground
- chapter: [index.html](4-1)
- chapter: [main.js](4-4)

### hint
ここでは`chapter:`を使用してセクション番号で定義済みセクションを参照していますが、内容の追加、修正があった場合に容易にセクション番号は変わってしまうので参照するセクションに`alias`を定義した上でその`alias`を用いて参照する方が望ましいです。

``````
## 4-1
...
### main
- alias: calc-html-final
...

## 4-4
...
### main
- alias: calc-js-final
...
``````

```
### playground
- section: [index.html](calc-html-final)
- section: [main.js](calc-js-final)
```
