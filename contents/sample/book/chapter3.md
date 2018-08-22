# HTMLセクションの作り方
このチャプターではHTMLを表示するセクションの作り方を説明します。

## HTMLで穴埋めする
HTMLの穴埋めセクションを作成するには`main`のファイル名を`index.html`とします。
画面下にはHTMLに対応するレンダリングがリアルタイムに表示されます。

穴埋め部分には`h1`を埋めてください。

### main(index.html)

```
<!doctype>
<html>
  <head>
    <meta charset="utf-8">
    <title>Track example</title>
  </head>
  <body>
    <${h1}>Track Example</${h1}>
  </body>
</html>

```

## HTMLとJS、CSSを組み合わせる
HTMLと外部のJS/CSSを組み合わせるには、参照するJS/CSSを`files`セクションで宣言した上でそれらのファイルをHTMLから参照します。

穴埋め部分には`h1`を埋めてください。

### main(index.html)

```
<!doctype>
<html>
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="main.css">
    <script src="main.js"></script>
    <title>Track example</title>
  </head>
  <body>
    <${h1}>Track Example</${h1}>
  </body>
</html>
```

### files

- [main.js](chapter3/main.js)
- [main.css](chapter3/main.css)

### hint
HTML内からはCDN等のインターネット上にあるjs/cssは自由に参照できます。


## JSで穴埋めする
JSファイルで穴埋めする際には`main`で定義するファイル名を`main.js`のようにjsのファイル名にします。(ファイル名は何でも構いません。)

表示に使用するHTMLファイルを`index.html`というファイル名で`files`セクションに宣言します。(こちらは`index.html`固定です。)
`index.html`内には`main`で定義したjsへの`script`タグでの参照が必要です。

穴埋め部分には`createElement`を埋めてください。

### main(main.js)

```
document.addEventListener("DOMContentLoaded", function(event) {
  var p = document.${createElement}("p");
  p.appendChild(document.createTextNode("This element was made by script."));
  document.body.appendChild(p);
});
```

### files

- [index.html](chapter3/index.html)
- [main.css](chapter3/main.css)

## 穴埋めに正規表現を使用する
CSSでの穴埋めもJSの場合と同様に定義できます。

ここでは穴埋め定義で正規表現を使用してみます。

`${/#fff/i}`のように穴埋め部分で正規表現を使用することができます。
(先頭の文字が`/`の場合、内容が正規表現と解釈され正規表現として不正な場合はエラーとなります。)

穴埋め部分には`#FFF`を埋めてください。(大文字小文字は区別しません。)

### main(main.css)

- alias: css-1

```
h1 {
  background-color: navy;
  color: ${/#fff/i};
  padding: 10px;
}
```

### files

- [index.html](chapter3/index.html)
- [main.js](chapter3/main.js)

## 穴埋めに正規表現を使用する(2)
穴埋めに正規表現を使用する場合には`/a.*b/`や、`/red|white/i`のように長さ不定で正解例が自動的には計算できないケースがあります。

この場合は、`${/red|white/i,white}`のように正規表現の後ろに`,`をつけてその後に正答例を記述します。

穴埋め部分には`red`または`white`を埋めてください。(大文字小文字は区別しません。)

### main(main.css)

```
h1 {
  background-color: navy;
  color: ${/red|white/i,white};
  padding: 10px;
}
```

### files

- [index.html](chapter3/index.html)
- [main.js](chapter3/main.js)

### hint
この場合、穴埋め部分の長さは8文字分となります。


## 過去のセクションを参照する
ここまでのセクションでは`files`の参照にstaticなファイルを指定してきましたが、過去のセクションの内容を指定することもできます。

```
### files

- section: [main.js](prev)
- section: [main.css](css-1)
```

上の例では、

`main.js`としてはmain.jsが`main`セクションで使用された最後のセクションを、
`main.css`としては`alias`として`css-1`が定義されているセクションを、

参照しています。

穴埋め部分には`h1`を埋めてください。

### main(index.html)

```
<!doctype>
<html>
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="main.css">
    <script src="main.js"></script>
    <title>Track example</title>
  </head>
  <body>
    <${h1}>Track Example</${h1}>
  </body>
</html>
```

### files

- section: [main.js](prev)
- section: [main.css](css-1)

### hint
この機能をうまく使えば、html, js, cssが連携するブックを外部ファイル参照なしで、徐々に組み立てていくことができます。
