## ザ・ミッション
ある任意の文字列 `[string]` が入力されたとき、
```
"Hello [string]!"
```
と返すような関数を実装してください。

例えば、`"World"`が入力された時、`"Hello World!"`と返し、
`"track"`の場合は、`"Hello track!"`と返します。

## 実装の詳細
### CLI
入力値が引数として渡されて、答えを標準出力に表示するCLIアプリケーションを実装してください。
詳細は末尾の「CLI アプリ作成用テンプレート」を参照ください。

### 入力ルール
以下のようにプログラムが実行されます。
```shell
 ./myApp [string]
```

### 出力ルール
以下のフォーマットを満たす標準出力を出力してください。

```text
Hello [string]!
```

## 入出力例
### 例 1
```shell
$ ./myApp World
```
標準出力
```
Hello World!
```

### 例 2
```shell
$ ./myApp track
```
標準出力
```
Hello track!
```


なお、期待する入出力は [test/basic_testcases.json](test/basic_testcases.json) ディレクトリにいくつか定義されています。  
実装する際の参考にしてください。
