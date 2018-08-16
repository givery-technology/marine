# プレビューセクションの作り方
このチャプターでは解説のみで穴埋めやエクササイズの無いセクションの作り方を解説します。

## 任意のHTMLを表示する
プレビューセクションでは任意のHTMLを画面右側全体に表示させることができます。

プレビューセクションを作成するにはセクション定義に

```
### preview
- chapter1/preview1.html
```

のように表示するHTMLへの参照を定義します。

### preview
- file: chapter1/preview1.html

### hint
HTML内から外部の画像ファイルやjs、cssを参照する場合は参照するファイルを`files`として定義してください。

```
### files
- [js/main.js](chapter1/assets/js/main.js)
- [images/img1.png](chapter1/assets/images/img1.png)
```

`[]`内がHTML内で参照するパス、`()`内が実際にファイルが置かれているパスです。

## プレビューをマークダウンで作成する
プレビューセクションでHTMLファイルの代わりにマークダウンファイル(`.md`)を参照するとマークダウンがHTMLに変換されて表示されます。

### preview
- file: chapter1/preview2.md

### hint
変換後のマークダウンに適用されるCSSは標準で定義されており変更することはできません。
