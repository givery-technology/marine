# 段階的にブックを組み立てる
このチャプターでは前のセクションの内容をふまえながら段階的にプログラムを組み立てていく方法を説明します。

## HTMLを準備する
例として、以下のようなアプリを作成してみます。

- 数値入力用の`input`を2つ持つ
- 実行用のボタンを1つ持つ
  - クリック時に2つの`input`の足し算をして結果を表示する

HTMLの各要素に`id`を設定します。

### main(index.html)

```
<!doctype>
<html>
  <head>
    <meta charset="utf-8">
    <title>Track example</title>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
    <script src="main.js"></script>
  </head>
  <body>
    <h1>足し算アプリケーション</h1>
    <div class="mt-3 ml-3">
      <input type="text" ${id}="num1">
      <span>+</span>
      <input type="text" ${id}="num2">
      <span>=</span>
      <span ${id}="result"></span>
    </di>
    <div class="mt-3 ml-3">
      <button ${id}="calc" class="btn btn-primary">計算!</button>
    </div>
  </body>
</html>
```

### hint
ここでは簡単のためBootstrapとjQueryをCDNから参照しています。

`main.js`はまだ作成されていないので裏では参照エラーが発生していますが、これは次のセクションで作成します。

## main.jsの作成
main.jsを作成します。
まずはdocument#readyのタイミングでコードが実行されるようにjQueryを設定しましょう。

穴埋め部分には`$`を埋めてください。

---
jQueryを使うコードでは`$`というキーワードがコード中で多用されます。
一方でBookの書式でも標準の穴埋めのプレースホルダは`$`であるため、両者が混在すると混乱を招きます。

これを回避するために、

```
- prefix: %
```

のように指定することでBookで使用する記号を差し替えることができます。
(prefixの指定で有効なのは最初の1文字のみで2文字目以降は無視されます。)

---
もう一つのポイントはマークダウンソースの中に

```
  //%{func:mark("next-position")}
```

という行が含まれている点です。
`func:mark`はBookコンパイラが解釈する特別な関数の1つで、他の関数から参照可能なマーク行として機能します。

この関数が含まれる行は実際のBookリーダー上では削除されます。
Marine上でもデフォルトでは削除されますが、ヘッダ部で`DevMode`のチェックを入れると表示されます。

`func:mark`をどのように利用するかは次のセクションで説明します。

> `func:mark`を含む行はプログラムコードとしては無意味です。
> `DevMode`で実行する際に各言語処理系からは無視させたいので、必ず言語処理系でのコメント行として記述してください。

### main(main.js)

- prefix: %

```
%{$}(function() {
  // %{func:mark("next-position")}
});
```

### files

- section: [index.html](prev)

## 前セクションのコード内に別のコードを埋め込む
Bookコンパイラには既存のセクションの内容を参照するための関数が多数用意されています。
ここでは、前セクションで作成したコードの`func:mark("next-position")`の位置に新たなコードを埋め込みます。

穴埋め部分には`var`を埋めてください。

---
マークダウンソースを確認してください。

`func:section-before`は第2引数で指定された文字列よりも前の行を返す関数です。
`func:section-after`は第2引数で指定された文字列よりも後の行を返す関数です。

いずれの関数でも第1関数はどのセクションを参照するかを示すシンボルで、`prev`は`main`で指定されたファイル名が同じである直前のセクションを示します。

第2引数で指定されている`next-position`という文字列は前セクションでは`func:mark`内で使用されていました。
このためこれらの関数は`func:mark("next-position")の前後の行を返します。

言い換えれば、この方法を使えば`func:mark`を宣言した部分に後からコードを差し込むことができます。

### main(main.js)

- prefix: %

```
%{func:section-before(prev, "next-position")}
  %{var} $num1 = $("#num1");
  %{var} $num2 = $("#num2");
  %{var} $result = $("#result");
  // %{func:mark("next-position")}
%{func:section-after(prev, "next-position")}
```

### files

- section: [index.html](prev)

### hint
`section-before`や`section-after`で参照できる文字列は`func:mark`で指定された行だけではありません。
ソースコード上で1度だけ現れる文字列があるならそれを指定することもできます。

例えばソースコード上で`function hoge()`という文字列(空白の個数まで完全に一致)が一度だけしか現れないのであれば、

```
${func:section-before(prev, "function hoge()")}
```

のように書くことができます。(`section-before`はあくまでソースコード上で指定の文字列が現れた行以前を取得する関数なので、`mark`関数とは無関係に評価されます。)

ただし、`function hoge()`という文字列がソースコード上に複数回現れる場合はコンパイルエラーとなります。

実際には次のコードを差し込みたい場所に適当な文字列があることは稀なので、殆どの場合は`func:mark`と組み合わせて使うことになります。

---
`section-after`の代わりに`section-from`を使用すると第2引数の検索で一致した行を含めてコピーされます。

このセクションの例の場合、

```
  // %{func:mark("next-position")}
%{func:section-after(prev, "next-position")}
```

の部分を

```
%{func:section-from(prev, "next-position")}
```

としても同じです。(`section-from`は`func:mark`の部分を含むので再度記述する必要がない)

同様に`section-before`の代わりに`section-to`を使用することもできます。

実際には次にコードを差し込む場所が毎回同じとは限らないので、毎回`func:mark`を記述する方が良いと思います。

例、以下のケースは`secton-to`や`section-from`では対応できない。

```
${func:section-before(prev, "next-position")}
  ${if} (something) {
    // $(func:mark("next-position-then"))
  } ${else} {
    // $(func:mark("next-position-else"))
  }
${func:section-after(prev, "next-position")}
```

## 計算アプリを完成させる
最後に`click`イベントをハンドルして計算アプリを完成させましょう。

穴埋め部分には`click`を埋めてください。

### main(main.js)

- prefix: %

```
%{func:section-before(prev, "next-position")}
  $("#calc").%{click}(function() {
    var num1 = parseInt($num1.val(), 10);
    var num2 = parseInt($num2.val(), 10);
    $result.text(num1 + num2);
  });
%{func:section-after(prev, "next-position")}
```

### files

- section: [index.html](prev)

