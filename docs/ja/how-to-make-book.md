# track Bookの作り方
## 概要
trackのBookはそのほとんどがMarkdownで作成できるように設計されています。
この文書ではBookを構成する各種ファイルの詳細について説明します。

※
ここで説明する仕様はCODEPREP用のブック, track用のブックの両方に対応しています。
(一部、trackでは使用していない機能の説明も含みます。)

## 最小限のBook
説明に先立ってまず最小限のBookの例を示します。

以下は

- book.yml
- chapter1.md

の２ファイルからなる、1チャプター、1セクションのBookの例です。

`contents`ディレクトリの下に適当なディレクトリを作成してこの2つのファイルを作成してください。

book.yml
```
title: はじめてのCODEPREP
detail: CODEPREPのBookのサンプルです。
chapters:
  - chapter1.md
```

chapter1.md
``````
# 最初のチャプター
チャプター定義のサンプルです。

## 最初のセクション
セクション定義のサンプルです。
ブランクを埋めて「Hello World」と出力されるHTMLを完成させてください。

### main(index.html)

```
<p>Hello ${World}</p>
```

``````

この２ファイルをMarineを通して見ると「<p>Hello [     ]</p>」というページが表示されます。

以下それぞれのファイルについて説明していきます。

## book.yml
book.ymlはBook全体の定義が記述されたファイルです。

以下のキーを含みます。

- title: String, 必須
- detail: String, 必須
- chapters: List[String], 一つ以上必須
- cover: String, 任意
- files: List[String], 任意
- images: List[String], 任意
- preview: String, 任意
- download: Boolean, 任意
- playground: Boolean, 任意
- webStorage: Boolean, 任意
- keepSession: Boolean, 任意
- timeInMinutes: Int, 任意
- env: Object, 任意(`keepSession=true`の場合は必須)
- shared: List[String], 任意
- carryOver: List[String], 任意
- initialize: Object, 任意
- sandbox: Object, 任意

### title
titleにはBookのタイトルを指定します。

### detail
detailにはBookの概要説明を指定します。
複数行指定したい場合はYamlのパイプ(|)を使用してください。

```
detail: |
  Bookの説明です。
  パイプ(|)を使用して複数行で記述しています。
```

### chapters
chaptersには各チャプターの定義ファイルを指定します。
指定したファイルは必ずそのパスに存在しなければなりません。

リストの順番がそのままチャプターの順序になります。

便宜的にチャプター定義ファイルの名前は「chapter1.md」のような名前を使用することが多いですが、実際には名前は自由に定義することが出来ます。

### cover
coverにはBookのカバー画像のファイルパスを指定します。
指定したファイルは必ずそのパスに存在しなければなりません。

※ ブックカバーは[CODEPREP](https://codeprep.jp)では使用されていましたが、trackでは使用されません。

### files
book.ymlのfilesにはすべてのチャプター、セクションで横断的に使用するファイルを指定します。
ここで指定されたファイルはBookReaderのエディタ部でタブとして表示されます。
指定したファイルは必ずそのパスに存在しなければなりません。

以下のような場合にはbook.ymlではなく、個別のセクションのfilesサブセクションで指定するようにしてください。

- ファイル(例: main.css)が1章では参照されないが、2章以降で参照される場合
- ファイルの内容が途中で変わる場合

以下のようにマークダウンのリンク形式で記述することにより実際のファイルパスと表示上のファイル名を変更することができます。

```
- [main.css](files/something.css)
```

### images
imagesには説明文中で使用する画像ファイルを指定します。

filesに指定したファイルはBookReaderのワークスペース上でタブとして表示されますが、imagesに指定してたものは表示されません。

別の言い方をすれば、filesで指定したファイルは各セクションで使用するソースコードの一部となります。例えばHTMLファイルの`img`タグから画像を参照する場合はfiles(または各セクション定義内のfiles)を使用します。

imagesはあくまで説明文中で使用するための画像です。

### preview
previewにはブックの詳細ページで表示されるプレビューページを指定します。
指定の方法は以下のいずれかです。

#### ファイルを指定する

```
preview: preview.html
```

この場合は、指定したファイルは必ずそのパスになければなりません。
css, scriptを使用する場合は外部ファイルとはせず、HTML内にインラインで定義してください。

#### sectionを指定する(aliasでの指定)
各チャプター定義ファイルのセクション定義に`alias`が定義されている場合は、その値を指定することができます。

```
preview:
  - section: mysection1
```

この場合、指定されたセクションのプレビューがブックのプレビューとして使用されます。

#### sectionを指定する(indexでの指定)
チャプターとセクションのインデックスを指定して、セクションを指定することもできます。

```
preview:
  - chapter: 2-1
```

previewを指定しなかった場合は、最後のセクションの内容がプレビューとなります。
remoteブック(Java, Rubyなど)の場合はセクションのソースコードがプレビューとなります。

※ trackではプレビューは使用されていません。

### download
ブックの各セクションがダウンロード可能かどうかを指定します。
省略した場合のデフォルト値は`true`です。
特に理由がない限り`false`にする必要はありません。

### playground
ブックの各セクションがプレイグラウンド化可能かどうかを指定します。
省略した場合のデフォルト値は`true`です。
特に理由がない限り`false`にする必要はありません。

### webStorage
HTMLブックでWebStorage(sessionStorage or localStorage)を使用する場合は、`true`を指定します。
`false`の場合はWebStorageは使用できません。

省略時のデフォルト値は`false`です。

### keepSession
JavaやRubyなどのRemote環境で処理を行うBookで、Remote環境との接続を維持したい場合は、`true`を指定します。
`false`の場合はRemote環境でのコマンド実行は毎回、コマンド実行後に切断されます。

省略時のデフォルト値は`false`です。

### timeInMinutes
Bookを解き終わるまでの目安時間を分単位で指定します。
省略時にはセクション数から自動計算されます。

自動計算は穴埋め問題を基準に計算しています。
エクササイズのあるBookでは自動計算される値と実際の目安時間が大きく乖離するのでできるだけ指定するようにしてください。

※ trackではこの項目はUI上での設定項目となるので使用されません。

### env
RubyやJavaなどのプログラミング言語を実行する場合にその環境を指定します。

HTMLやjs/cssのみを扱う場合フロントエンドのみで完結するのでenvの指定は不要です。

ここで環境を指定した場合はBook内のすべてのセクションで使用されますが、セクション毎に異なる環境を指定することも可能です。(`keepSession=true`の場合は、各セクションで`env`を指定することはできません。言い換えればKeepSession時はBook内で使用できる`env`は一つだけであり途中で切り替えることはできません。)

省略時のデフォルト値は`givery/codecheck:latest`となります。
これは多くの言語をオールインワンで含んだDockerイメージですが、既にメンテナンスは終了しており含まれる各言語のバージョンが古いので、原則明示的に環境を指定するようにしてください。

詳細な指定内容は[env.md](env.md)を参照してください。

### answerSection
各セクションで定義した`answer`をまとめたセクションを作成するかどうかを指定します。
以下の3つの値のいずれかを指定します。

- none: answerをまとめたセクションを生成しない
- each: 各チャプターの最後にそのチャプター内のanswerをまとめたセクションを追加する
- last: ブックの最後に新規チャプターとしてすべてのanswerをまとめたセクションを追加する

省略時のデフォルト値は`each`です。

### shared
複数のブックで共有するファイル群の置き場所を指定します。
主にexerciseでのファイル指定の際に使用します。
具体的な定義方法および使用例については[how-to-make-challenge.md](how-to-make-challenge.md#shared)を参照してください。

### carryOver
Book内の複数のExerciseで同じファイルを徐々に作り込んでいくような場合にそのファイル名を指定します。

例えばJavascriptでFizzBuzz(fizzbuzz.js)を作成するような場合、

```
carryOver:
  - fizzbuzz.js
```

と指定すれば、

- 1-1. でFizzに対応するコードを作らせる
- 1-2. で1-1で作ったコードを引き継いでBuzzに対応するコードを作らせる
- 1-3. で1-2で作ったコードを引き継いでFizzBuzzに対応するコードを作らせる

というようなことができます。

この機能では同じファイルをすべてのセクションで使用するのではないことに注意してください。
ファイルの保存は各セクション単位になります。

例えば1-3まで進んだ後に1-1に戻った場合、そこで表示される内容は1-1終了時の内容になります。

carryOverを使用する場合はexercise定義には`name`が必須です。

### initialize
`initialize`は`keepSession: true`の場合のみ指定することができます。
ここではRemote環境との接続時に使用するファイルとコマンドのセットを指定することができます。

例えばDatabaseを扱う問題でユーザの処理を実行するよりも前に`CREATE TABLE`や初期データの`INSERT`が必要な場合、この機能を使用することができます。

```
# データベースを扱うBookの初期処理
initialize:
  files:
    - sql/create.sql
    - sql/insert.sql
  commands:
    - sqlite3 user.db < create.sql
    - sqlite3 user.db < insert.sql
```

デフォルトではここで指定した初期化ファイル及びコマンドの実行結果は受講者からは見えませんが、`showConsole: true`を指定した場合は初期化の過程が受験者に表示されます。

※1 KeepSession時でも何らかの理由でRemote環境との接続が切れることはありえます。
その場合、ユーザによるコマンド実行が行われたタイミングで再接続が行われ、その際に`initialize`の処理も実行されます。

※2 KeepSession時にはStateが維持されるので、ユーザの操作によっては環境が不正な状態になることがありえます。
(例えばデータベースBookでユーザが`DELETE`文を発行するなど)
この場合、以降のセクションでの処理が意図した結果とならないことがありますが、ブラウザをリロードすれば接続が切れるのでRemote環境も初期状態に戻ります。

### sandbox
sandboxセクションで使用するファイルを指定します。(sandboxセクションで使用するファイルはすべてここで指定しますが、各セクションで表示するファイルは個別のセクションで指定できます。)
ここで指定できるキーは以下のとおりです。

- files: 配列でsandboxファイルを指定します。書式はトップレベルでのfiles指定と同じです。
- mode: sandboxのファイルの実行方法を指定します
  - `console`: 指定のコマンドをコマンド実行サーバで実行します。
  - `html`: ファイルの編集結果をブラウザ上で表示します。
- allowNewFile: sandboxセクションで新しいファイルを作成できるかどうかを指定します。省略時のデフォルト値はfalseです。


## チャプター定義ファイル
チャプター定義ファイルはMarkdown形式で記述されたチャプターの定義ファイルです。
CODEPREPではひとつのチャプターがひとつのファイルに対応し、その中に複数のセクションを含めることができます。

### チャプター定義ファイルの見出し
チャプター定義ファイルではマークダウンの見出し(#, ##, ###)を各種定義の区切りとして使用しています。
それぞれの見出しは以下の意味を持ちます。

- 見出し1(#)はチャプターのタイトルを示します。
  - チャプタータイトルは自由につけることができます。
  - チャプター定義ファイルは必ず見出し1(#)で始まらなければなりません。
  - 見出し1(#)はチャプター定義ファイル内に複数定義してはいけません。
- 見出し2(##)はセクションのタイトルを示します。
  - セクションタイトルは自由につけることができます。
  - 見出し2(##)はチャプター定義ファイル内で複数定義することができます。
- 見出し3(###)はサブセクションを示します。
  - 見出し3(###)の名前は「main」「hint」「preview」等固定です。
  - 見出し2(##)に続く複数の見出し3(###)がセクションの内容となります。

未定義の名前を持つ見出し3、見出し4-見出し6はチャプター定義ファイルでは使用できません。
存在する場合はコンパイルエラーとなります。

### チャプター定義ファイルのコメント
コードブロック以外で「//」で始まる行はコメントとして扱われるため、Bookの内容には含まれません。

この行はMarkdownの書式上でのコメント行ではないので、GitHub等のMarkdownViewer上ではそのまま表示されます。

例
```
# チャプター１

// ToDo あとで修正する

チャプター1の説明です。

```

逆にMarkdown書式のコメント「`<!-- -->`」はMarkdownViewer上では表示されませんが、Bookのコンパイルの際にはそのままのテキストとして扱われます。

### チャプタータイトルと説明
チャプター定義の先頭には必ず見出し1がきます。
そして、その次に来る見出しは必ず見出し2(セクションタイトル)になります。

チャプタータイトルの下にはMarkdownで自由にチャプターの説明を記述することができます。
(ただし、見出しは使用できません。)

### セクションの構成
セクションタイトルの下にはMarkdownで自由にセクションの説明を記述することができます。
(ただし、見出しは使用できません。)

この説明はBookReaderの画面左に表示される問題文になります。

セクションは以下のサブセクションを持つことができます。

- main
- playground
- exercise
- mcq
- fib
- preview
- hint
- tips
- answer
- files
- remote
- dropdown
- env
- debug
- sandbox

各サブセクションはそれぞれのセクションで一度だけ定義できます。
また、`main`と`exercise`, `playground`, `mcq`, `fib`, `sandbox`のように同時には使用できないサブセクションもあります。

### セクションの種類
CODEPREPのセクションには大きく次の7種類があります。

- 穴埋め問題 - コード(main)
  - セクションで`main`が定義されている
  - 殆どのセクションが穴埋め問題です。
- エクササイズ(exercise)
  - セクションで`exercise`が定義されている
  - エクササイズにはさらにRemote(Ruby, Java等)のエクササイズとClient(HTML/JavaScript)のエクササイズがあり、作成方法が異なります。
- プレイグラウンド(playground)
  - セクションで`playground`が定義されている
  - 自由編集ページ。いくつかのブックの最終セクションはプレイグラウンドになっています。
- プレビュー(preview)
  - セクションで`main`, `exercise`, `playgournd`が定義されておらず`preview`のみが定義されている
  - 説明のみのページ。JavaじゃんけんBookの最初のセクションはこれです。
- 穴埋め問題 - マークダウン(fib)
  - セクションで`fib`が定義されている
  - `main`がプログラムコードの一部を穴埋め化するのに対し、`fib`はマークダウンで記述された文章の一部を穴埋め化します。
  - `fib`ではプレビュー(またはリモートコンソール)は表示されず画面は3分割ではなく2分割となります。
- 選択問題(mcq)
  - セクションで`mcq`が定義されている
  - 問題文と共に単一または複数選択のリストを表示します。
  - MCQの定義方法は[Quiz](how-to-make-quiz.md)と同じです。
- サンドボックス(sandbox)
  - セクションで`sandbox`が定義されている
  - 自由編集ページ。 プレイグラウンドとは違い、sandboxのファイルはセクションをまたがって保持されます。


各セクションでは`main`, `exercise`, `playground`, `fib`, `mcq`, `sandbox`は同時に定義できません。

`preview`は他の定義と同時に使用することもできますが、他の定義がなく`preview`だけが定義されている場合はプレビューセクションとなります。

### mainの定義
mainサブセクションの定義は見出し3(###)で「main(ファイル名)」という形式で行います。

mainサブセクションではコードブロックが必須であり、コードブロック内で一つ以上のAnswer定義が必須です。

``````
### main(index.html)

```
<${p}>Hello World<${\/p}>
```
``````

Answerは通常、`${...}`という形式で定義し、最もシンプルなケースでは{}で囲まれた文字列がそのまま正答となります。(大文字小文字を区別します。)

ただし、大文字小文字の区別をしないなど追加の要件に対応するために{}内の先頭文字によって以下のように解釈が変わります。

#### 先頭が「/」の場合
{}内は正規表現であると解釈されます。

例
- ${/red/i}  - 大文字小文字の区別なしで「red」にマッチ
- ${/abc|def/,abc} - 大文字小文字の区別ありで「abc」または「def」にマッチ。解答例はabc

JavaScriptのRegExがサポートする範囲で自由に正規表現を定義することが可能です。
文字列が正規表現として不正な場合はコンパイルエラーとなります。

##### 正規表現の解答例の定義
正規表現は書き方によっては、パターンから解答例を算出することができなくなります。

以下は解答例を算出できるケースと出来ないケースの例です。

- ${/test/i} -> 可 `test`
- ${/a.*b/i} -> 不可
- ${/red|green/} -> 不可

(解答例を算出できるのは、「大文字小文字を区別しないだけ」のようなごくシンプルなパターンのみです。)

解答例を算出できないケースのために正規表現の後に「,xxxx」のように解答例を付加できます。

- ${/a.*b/i,aab}
- ${/red|green/,red}

解答例が算出できない(与えられていない)正規表現定義はコンパイルエラーとなります。

#### 先頭が「{」の場合
{}内はJSONであると解釈されます。

例
- ${{"text": "hoge", "caseSensitive": true, "defaultValue": "fuga"}}
- ${{"regexp": "hoge|fuga", "flags": "i", "maxLength": 4}}

JSON内で定義できるキーは以下です。

- text: 正答となる文字列。textまたはregexpのいずれかは必須
- regexp: 正答となる正規表現。textまたはregexpのいずれかは必須
- caseSensitive: 大文字小文字を区別するかのフラグ。textの場合のみ有効
- flags: 正規表現のフラグ。例えば大文字小文字を区別しない場合は"i"を指定する。regexpの場合のみ有効
- maxLength: 解答の最大長。regexpの場合のみ有効
- defaultValue: 初期値。指定した場合最初から誤答がブランクに設定される。
- answer: 解答例。regexpの場合のみ有効

上記以外のキーは無視されます。

#### 先頭が「\」の場合
先頭の「\」を飛ばして次の文字以降をシンプルな文字列として解釈します。

例
- ${\/p}
- ${\{}

この設定は文字列が正規表現、あるいはJSONと解釈されるのを防ぎたい場合に有効です。

注.
この機能はエスケープではなくあくまで先頭の「\」をスキップするだけの機能です。
シンプルな文字列と解釈される場合のエスケープ機能はありません。

#### `$`の別の文字への変更
`${xxx}`という書式はES6やScalaでは構文として使用されています。
このようなケースに対応するために、prefixを定義して`$`を別の一文字に変更することができます。

``````
### main(index.html)

- prefix: %

```
<%{p}>Hello World<%{\/p}>
```
``````

prefixに二文字以上の文字列を指定した場合でも有効となるのは最初の一文字のみです。

#### aliasの定義
mainサブセクションではオプションとしてalias(別名)を指定できます。

```
- alias: index1
```

ここで設定したaliasは後述する関数から参照できます。

### hint/tipsの定義
「### hint」または「### tips」という見出し3の下にMarkdownで任意の文章を定義することができます。

hintあるいはtipsはデフォルトでは表示されず、ユーザーアクションによって表示される文字列です。

hintとtipsには機能的な差異は存在しないので用途によって使い分けてください。(両方定義することも可能です。)

### answerの定義
answerには問題に対する解答/解説を定義します。

穴埋め問題では不要ですが、エクササイズ問題では定義しておいた方が親切です。

answerは各セクションで個別に参照することができます。
また、Bookの最後にすべてのanswerをまとめたセクションが追加されます。


### filesの定義
filesには参照する外部ファイルをリスト形式で複数設定できます。
ここで指定したファイルはエディタ部でタブとして表示されます。
指定したファイルが存在しない場合はコンパイルエラーとなります。

例
```
### files

- main.css
- [main.js](chapter1/section1_main.js)
- [images/image1.png](chapter1/image1.png)
```

Markdownのリンク書式を使用して実際のファイル名と表示上のファイル名を変更することも可能です。

HTML内から参照する場合は表示上のファイル名(`[]`内で指定されたファイル名)を使用します。

### mcqの定義
mcqには問題文の文章と選択肢をマークダウン形式で定義します。

マークダウン中には複数の`- [ ]`で始まる選択肢が必要で、そのうちの1つ以上が`- [x]`と、正解の選択肢となっている必要があります。

画面上では正解の選択肢が一つだけの場合は、Radioボタン(単一選択)となり、複数ある場合はCheckbox(複数選択可)として表示されます。

### fibの定義
mcqには`${xxxx}`という穴埋め部分を含む問題文の文章をマークダウン形式で定義します。

穴埋め部分の定義方法は`main`の場合と同じです。

### main, mcq, fibでの外部ファイル参照
main, mcq, fibの各セクションの内容がリストのみであり、リスト内でファイルが参照されている場合はそのファイルの内容が本文として扱われます。

```
### mcq

- file: assets/1-1.md
```

mcqやfibで本文を直接記述する場合は見出し(`#`や`##`など)はブック自体のシンタックスと競合するため使用できませんが、外部ファイルとして定義した場合はこれらの見出しも自由に使用することができます。

### FIBでのドロップダウンサポート
FIBでテキストエリアの代わりにドロップダウンリストを表示することができます。

ドロップダウンを使用するためには、`dropdown`セクションにドロップダウンの名前とリストを定義します。

``````
### fib
特殊なコンピュータを除いては，8ビット (b) = ${@dropdown(byte, 0)} の2進数を単位としたデータが規則正しくメモリに格納されています。
メモリの大きさはバイトを単位として表します。

通常，4バイトを ${@dropdown(word, 0)} ，8バイトを ${@dropdown(word, 2)} と呼びます。

### dropdown
- byte
  - 1バイト
  - 1キロバイト
  - 1メガバイト
  - 1テラバイト
- word
  - 1ワード
  - 2ワード
  - 1ダブルワード
  - 2ダブルワード
``````

この例では`byte`と`word`という名前の2つのドロップダウンを定義しています。
各dropdownのアイテムは一段下のリストとして定義します。

問題文の方では通常の穴埋めと同じ書式でその内容を`@dropdown([名前], 正解のインデックス)`のように定義します。
正解のインデックスは`0`ベースです。


※　現状ドロップダウンが使えるのはBookのみでQuizは未対応です。


### previewの定義
プレビュー(BookReaderの画面右側下半分に表示される)は通常、後述のロジックに従って自動生成されますが独自のプレビューを
別途定義することができます。

previewではリスト形式で

```
- file:chapter1/section1_preview.html
```

のように外部ファイルを参照します。

preview機能は必ずしもmainの内容をそのまま再現する必要はなく、自由にカスタマイズすることができます。
previewの使用例は

- [JavaScriptの配列操作を理解する](https://codeprep.jp/books/54)
- [JavaScriptで正規表現を理解する](https://codeprep.jp/books/56)

などで見ることができるので参考にしてください。

外部ファイルとは別にオプションとして以下が設定できます。

- contentType: プレビューのContent-Type。省略時は text/html
- prefix: キーワード参照に使用するprefix。省略時は$。

例
```
### preview

- contentType: text/plain
- prefix: %
- file: chapter1/preview.html
```

またURLを指定して外部のHTMLを参照することも可能です。

```
### preview

- url: https://s3-ap-northeast-1.amazonaws.com/codeprep-assets/html/about-exercise.html
```

現状、エクササイズBookの先頭セクションには必ず、エクササイズの解き方のセクションを差し込んでいます。
上記の例のURLはその説明のHTMLを指しているので、このURLを参照することで説明セクションを差し込むことができます。

指定のURLのファイルはコピーされず直接参照されます。
このため、参照先のHTMLが修正された場合はその内容はすぐにBookに反映されます。

#### previewにマークダウンファイルを指定する
previewに指定されたファイルの拡張子が「.md」だった場合、そのファイルはマークダウンファイルとして扱われます。

この場合、マークダウンはHTMLに変換され問題文やHINT, TIPSなどと同じスタイルが適用されます。

マークダウンでイメージを使用する場合、通常のマークダウン書式で`title`を記述するパートにCSSを記述することができます。

```
![イメージ1](assets/image1.png "width:300px;")
```

画像のサイズを調整したい場合などに利用できます。

#### previewのマークダウンのスタイルをカスタマイズする
previewに指定されたファイルの拡張子が「.md」だった場合、cssを定義することでスタイルをカスタマイズできます。

```
- css: assets/main.css
```


### remoteの定義
remoteはRubyなどのサーバーサイドの言語を実行する機能です。
commandに実行するコマンドを定義します。

```
### main(ruby.rb)
\```
${puts} "Hello World"
\```

### remote
- command: ruby main.rb
```

上の例ではmainでユーザーが作成したmain.rbを実行しています。(Hello Worldが表示されます。)

またオプションとして以下が設定できます。

- mode: 実行モード。`console`または`html`。省略時はconsole
- file: 実行時に追加でサーバーにコピーするファイル。複数指定可
- build: command実行前に実行する準備のコマンド。複数指定可
- prepare: command, buildよりも先に実行されるコマンド。複数指定可
- cwd: build, command実行時のワーキングディレクトリ。
  - 省略時は`/root/src`
  - 指定する場合は`/root/src/directory1`のようにフルパスで指定する必要がある
- after: command実行後に実行する後処理コマンド。複数指定可
- previewFile: after(無い場合はcommand)実行後に画面に表示するファイル。画像ファイルまたはHTMLファイルが指定可

`build`と`prepare`の違いはコマンドがコンソール上に表示されるか否かです。

`build`コマンドはコンソール上に表示されるので、読者はそのコマンドが実行されていることを画面上で確認できますが、
`prepare`コマンドは表示されないため(そのコマンドが標準入出力に何も出力しないならば)読者はそのコマンドが裏で実行されていることはわかりません。

また、prepareコマンドでは`cwd`は適用されません。
このため、prepareコマンドでなんらかのディレクトリとファイルを作成後にそのディレクトリ上でcommandを実行することも可能です。

`after`の実行はコンソール上には表示されません。

#### remote実行時にコピーされるファイル
remote実行時には以下のファイルが実行サーバーにコピーされます。

- main(mainに指定されたファイル名でコピーされます。)
  - ただしファイル名が`shell`の場合はコピーされません
- book.ymlのfilesに指定されたファイル
- セクションのfilesサブセクションに指定されたファイル
- remoteサブセクションでfileオプションとして指定されたファイル

コピー先のファイル名は別名が定義されている場合はそちらが使用されます。

```
### remote

- build: npm install
- command: node main.js
- file: [package.json](chapter1/package.json)

```

上の例では「npm install」を実行してからnodeが実行されます。

Book定義時に実際にファイルが存在するパスは「chapter1/package.json」ですが、コピー先はコマンドを実行するrootディレクトリ上の「package.json」となります。

(filesサブセクションで指定したファイルはエディタ部でタブとして表示されますが、remoteで指定されたファイルは非表示でユーザーには提示されないという違いがあります。)

画像ファイルなどサイズの大きなファイルを多数転送するとパフォーマンス低下につながるので注意してください。

#### @main
`command`に`@main`を指定した場合、コマンドの内容がmainサブセクションで指定した内容(ユーザが穴埋めで入力した内容)に置き換わります。

この機能はUnixの基本コマンド群や、git, npmなどのコマンドラインツールの解説ブックを書く際に有用です。

通常、`@main`を使用する場合はファイル名を`shell`としてmainの内容がファイルとして実行サーバにコピーされないようにします。

``````
### main(shell)

```
${ls}
```

### remote

- prepare: touch file1.txt
- prepare: mkdir dir1
- command: @main
``````

この例では`touch`と`mkdir`が実行された後に`ls`が実行されますが、`touch`と`mkdir`が実行されていることはユーザにはわかりません。

mainの内容が複数行ある場合は、改行毎で分割されそれぞれの行がコマンドとして実行されます。

#### html mode
PHPのBookなどではコマンドの実行結果がそのままHTMLとなっている場合があります。
その場合は、

```
- mode: html
```

を設定しておくことでコマンド実行後にHTMLでのプレビューを表示させることができます。

### remoteまたはpreviewが未定義の場合のプレビュー
画面右下に表示される内容は以下の優先順位で決定します。

- remoteが定義されている場合はremoteコンソールが表示されます。
- previewが定義されている場合はその内容がpreviewとして表示されます。
- mainのファイル名がindex.htmlの場合はその内容が表示されます。
- filesサブセクションに「index.html」というファイルが指定されている場合はその内容が表示されます。
- いずれにも該当しない場合はmainの内容がtext/plainで表示されます。

なお、mainとfilesで定義されたファイル間でのscript/cssの参照は自動的に解決されます。
また、HTML内で画像ファイルを相対パスで参照する場合はそのファイルはfilesサブセクション(またはbook.ymlのfiles)に設定されている必要があります。

この際の参照関係の解決はファイル名よりもエイリアスが優先されます。

例えば、filesサブセクションに

```
- [image1.png](assets/image1.png)
```

が設定されている場合、 HTML内で定義するimgタグは `<img src="image1.png"/>` とします。

## 高度な機能
ここではBookを作成する上で、さらに便利な機能を紹介します。

### main内での先行セクション、外部ファイルの参照
例として、

- セクション1でh1を定義し、
- セクション2でその下にh2を定義し、
- セクション3でその下にpタグを定義する

というケースを考えてみます。

素直に書くとそれぞれのmainの定義は以下のようになります。

Section1
```
<${h1}>This is H1<${\/h1}>
```

Section2
```
<h1>This is H1</h1>
<${h2}>This is H2<${\/h2}>
```

Section3
```
<h1>This is H1</h1>
<h2>This is H2</h2>
<${p}>This is p<${/p}>
```

前の内容をコピーしながら少しずつ内容を書き足していることがわかります。

これでも問題なく動作しますが、メンテナンス性はかなり悪くなります。(最初の方のセクションを修正してしまうとそれ以降のすべてを修正する羽目になります。)

この場合 `${func:section(prev)}` という関数を使用することで直前のセクションの完成した内容を参照することができます。
この機能によって先の内容は以下のように書き換えることができます。

Section1
```
<${h1}>This is H1<${\/h1}>
```

Section2
```
${func:section(prev)}
<${h2}>This is H2<${\/h2}>
```

Section3
```
${func:section(prev)}
<${p}>This is p<${/p}>
```

このfunc:section関数では引数として`prev`以外に以下を取ることができます。

- 数字: 同一チャプター内のセクション番号。
  - 例: `${func:section(2)}` はセクション2の内容を参照します。
- 任意の文字列: 先行するmainで定義されたaliasを検索し参照します。
  - 例: `${func:section(index1)}` は `- alias: index1` を持つmain定義を参照します。

いずれの場合もそのセクションが見つからない場合はコンパイルエラーとなります。

`prev`はファイル名を考慮します。
例えば、`index.html`と`main.js`を交互に編集するようなブックの場合、`### main(index.html)`からの"prev"の参照はファイル名がindex.htmlのセクションのみが対象となります。

### その他のsectionを参照する関数
先のsection関数は指定のmainの内容をまるごと参照していましたが、追加する内容が前の内容の後ではなく間に挟まることも多々あります。
こうしたケースに対応するため以下の関数があります。

(下記のSYMBOLはsection関数と同じ引数(prev, 数値, alias)のことです。)

- section-before-blank(SYMBOL)
  - main定義中の最初のブランク出現行を検索し、その前の行までを返します。(ブランク行を含まない)
- section-after-blank(SYMBOL)
  - main定義中の最後のブランク出現行を検索し、その後ろの行を返します。(ブランク行を含まない)
- section-to-blank(SYMBOL)
  - main定義中の最後のブランク出現行を検索し、その行までを返します。(ブランク行を含む)
- section-from-blank(SYMBOL)
  - main定義中の最初のブランク出現行を検索し、その行以降を返します。(ブランク行を含む)

また、任意の文字列を検索してその行を基準に内容を分割する関数もあります。

- section-before(SYMBOL, "検索文字列")
  - main定義から指定の文字列のある行を検索し、その前の行までを返します。(検索行を含まない)
- section-after(SYMBOL, "検索文字列")
  - main定義から指定の文字列のある行を検索し、その後ろの行を返します。(検索行を含まない)
- section-to(SYMBOL, "検索文字列")
  - main定義から指定の文字列のある行を検索し、その行までを返します。(検索行を含む)
- section-from(SYMBOL, "検索文字列")
  - main定義から指定の文字列のある行を検索し、その行以降を返します。(検索行を含む)

- section-from-to(SYMBOL, "検索文字列1", "検索文字列2")
  - 検索文字列1を含む行から検索文字列2を含む行までを返します。(検索文字列1、検索文字列2のある行を含みます。)
- section-from-before(SYMBOL, "検索文字列1", "検索文字列2")
  - 検索文字列1を含む行から検索文字列2を含む行までを返します。(検索文字列1のある行を含み、検索文字列2のある行は含みません。)
- section-after-to(SYMBOL, "検索文字列1", "検索文字列2")
  - 検索文字列1を含む行から検索文字列2を含む行までを返します。(検索文字列1のある行は含まず、検索文字列2のある行を含みます。)
- section-after-before(SYMBOL, "検索文字列1", "検索文字列2")
  - 検索文字列1を含む行から検索文字列2を含む行までを返します。(検索文字列1、検索文字列2のある行を含みません。)

これらの関数では指定の文字列を含む行が2行以上ある場合はコンパイルエラーとなります。

例
```
...
<div>
  <${ul}><${\/ul}>
</div>
...
```

```
${func:section-before-blank(prev)}
  <ul>
    <${li}><${\/li}>
    <${li}><${\/li}>
  </ul>
${func:section-after-blank(prev)}
```

### func:mark関数
section-beforeやsection-afterを使用するためには何らかの検索文字列がソースコード内に必要ですが、適当な検索文字列が存在しないケースも多々あります。
このようなケースのために`${func:mark("hoge")}`という書式で検索用の文字列を埋め込むことができます。

```
$(${function}() {
  // ${func:mark("next-position")}
})
```

先行するセクションで上記のようにmainを定義しておけば、次のセクションでは、

```
${func:section-before(prev, "next-position")}
  var ws = ${new} ${WebSocket}("wss://codeprep-ws-chat.herokuapp.com/api/websocket/chat");
  // ${func:mark("next-position")}
${func:section-after(prev, "next-position")}
```

のようにして、`next-position`のある行に次のコードを埋め込むことができます。

ちなみに上の例では`section-after`関数(検索行を含まない)の直前に検索行があるので、`section-from`(検索行を含む)を使用して以下のように書き換えても同じです。

```
${func:section-before(prev, "next-position")}
  var ws = ${new} ${WebSocket}("wss://codeprep-ws-chat.herokuapp.com/api/websocket/chat");
${func:section-from(prev, "next-position")}
```

ただ、状況に応じて`section-after`と`section-from`を使い分けるよりも、常に`section-after`を使用して次の行が入る位置を明示した方が可読性は良くなります。

`func:mark`を含む行はブックの公開時には削除されますが、Marine上では表示するか削除するかを選択することができます。(DevMode)
表示する場合は、その行もソースコードの一部となるので、コンパイルエラー/ランタイムエラーを避けるために対象言語のコメント書式を利用して定義してください。

### fileを参照する関数
セクションではなく外部ファイルを参照する関数もあります。
こちらの関数では第一引数は外部ファイルへのパスとなります。

- ${func:file(filepath)}
- ${func:file-before-blank(filepath)}
- ${func:file-after-blank(filepath)}
- ${func:file-to-blank(filepath)}
- ${func:file-from-blank(filepath)}
- ${func:file-before(filepath, "検索文字列")}
- ${func:file-after(filepath, "検索文字列")}
- ${func:file-to(filepath, "検索文字列")}
- ${func:file-from(filepath, "検索文字列")}
- ${func:file-from-to(filepath, "検索文字列1", "検索文字列2")}
- ${func:file-from-before(filepath, "検索文字列1", "検索文字列2")}
- ${func:file-after-to(filepath, "検索文字列1", "検索文字列2")}
- ${func:file-after-before(filepath, "検索文字列1", "検索文字列2")}

### filesサブセクションでの先行セクションの参照
filesサブセクションでも外部ファイルではなく先行するセクションを参照することができます。

```
### files
- section: prev
```

参照名にはsection関数と同様に

- prev
- 数値(同一チャプターのセクション番号)
- 先行するセクションで定義したalias

が指定できます。

"prev"の参照でファイル名を指定したい場合は`[ファイル名](prev)`のようにマークダウンの記述します。

```
### files

- section: [index.html](prev)
- section: [main.js](prev)
```

この機能をうまく利用すると、例えばHTMLとCSSを交互に編集しながら組み立てるようなBookを一切外部ファイルの参照なしで組み立てることも可能です。

### Playground
リスト形式でファイル(`file:xxxx`)またはセクション参照(`section:xxx`)を使用して、編集可能なファイルを指定します。

リモートプレイグラウンドの場合は、さらにビルドコマンド(`build:xxx`)(複数可)と実行コマンド(`command:xxx`)(必須。一つのみ)を指定します。(必要であれば`prepare`コマンドも複数指定可能です。)


HTMLプレイグラウンド
```
### playground

- mode: client
- file: exercise5/main.js
- file: exercise5/index.html
```

リモートプレイグラウンド
```
### playground

- mode: remote
- file: [main.rb](playground1/main.rb)
- command: ruby main.rb
```

`mode`に指定できる値は`client`または`remote`です。
省略時は`client`となります。

### exercise
エクササイズの定義はリスト形式で必要な情報を定義することで行われます。

エクササイズには以下の3種類があります。

- client - クライアントエクササイズ
  - HTMLやJavascript、CSSなどのフロントエンド技術を扱うエクササイズ
- remote - リモートエクササイズ
  - JavaやRubyなどのプログラミング言語を扱うエクササイズ
- cli - CLIエクササイズ
  - アルゴリズム問題などをユーザが選択した任意の言語で解かせるエクササイズ

それぞれのエクササイズで定義方法は異なります。

#### クライアントエクササイズ
クライアントエクササイズを定義するには`- mode: client`を定義に加えます。
それ以外に定義可能なキーは以下のとおりです。

- name: Book内でユニークなエクササイズの名前(英数のみ)
- file: 1つ以上必須。ユーザが編集可能なファイルを指定します。ファイル自体は外部ファイルとして作成します。
- hidden: 任意。ユーザから不可視のファイルを指定します。(クライアントエクササイズではおそらく使うことはありません。)
- clientTest: 必須。Mochaで書いたテストが書かれたファイル

ユーザーには見えているけれど、編集はさせたくないファイルが存在する場合は`files`サブセクションで定義してください。

```
### exercise
- mode: client
- file: [main.js](assets/1-2.main.js)
- test: assets/1-2.test.js

### files
- [index.html](assets/chapter1.html)
```

以下はjQueryのセレクタテストの例です。

``` javascript
"use strict";

var assert = chai.assert;

describe("セレクタ", function() {

  it("関数 getElementsが定義されている", function() {
    assert.equal(typeof getElements, "function");
  });

  it("関数 getElementsがjQueryオブジェクトを返す", function() {
    let $selected = getElements();
    assert.ok($selected instanceof jQuery);
  });

  it("セレクタによって選択された要素が正しい", function() {
    let $selected = getElements();
    $selected.each(function() {
      $(this).addClass("bingo");
    });
    $(".count").text($selected.length);

    const $answer = $("#one");
    const $bingo = $(".bingo");

    assert.equal($answer.length, $bingo.length);
    assert.equal($answer.filter(".bingo").length, $bingo.length);
  });
});
```

上記のjsがmochaのテストとしてindex.htmlに差し込まれて実行されます。

#### リモートエクササイズ
リモートエクササイズを定義するには`- mode: remote`を定義に加えます。
それ以外に定義可能なキーは以下のとおりです。

- name: Book内でユニークなエクササイズの名前(英数のみ)
- file: 1つ以上必須。ユーザが編集可能なファイルを指定します。ファイル自体は外部ファイルとして作成します。
- hidden: 任意。ユーザから不可視のファイルを指定します。通常テスト本体はhiddenで指定します。
- command: 必須。テストの実行コマンドを指定します。
- build: 任意。`command`の実行前に実行するコマンドがある場合に指定します。複数指定可能です。
- prepare: 任意。`build`の実行前に実行するコマンドがある場合に指定します。複数指定可能です。
- cwd: 任意。`build`および`command`を実行する場合のワーキングディレクトリ。
- after: `command`実行後に実行する後処理コマンド。複数指定可
- previewFile: `after`(無い場合は`command`)実行後に画面に表示するファイル。画像ファイルまたはHTMLファイルが指定可

ユーザーには見えているけれど、編集はさせたくないファイルが存在する場合は`files`サブセクションで定義してください。

例: Javaのテスト
```
### exercise

- build: javac -J-Duser.language=ja *.java
- file: [Main.java](assets/Section1_1.java)
- hidden: [Section1_1_Test.java](assets/Section1_1_Test.java)
- mode: remote
- command: java Section1_1_Test
```

#### リモートテストの書き方
実行結果がTAP形式で出力されるならどのように作成しても構いません。
テストツールの多くはTAP形式をサポートしているので、それらを使っても構いませんしすべて自力で記述しても構いません。

TAP形式とは簡単に言うとコンソールの出力が

- `ok `で始まる場合はテストの成功を表す。
- `not ok `で始まる場合はテストの失敗を表す。

というものです。(厳密に言うともう少し細かいルールがありますが、trackで必要としているのはこの部分だけです。)

リモートエクササイズの結果の判定では

- コンパイルエラー、または実行時エラーになっていない
- `ok `で始まる行が1つ以上ある
- `not ok `で始まる行がない

という条件で正解としています。

簡単なテストの例は以下のようになります。


``` java
// ユーザにMainクラスのhelloというメソッドを定義させる問題
public class Section1_1_Test {

  private static void doTest(int index, String name) {
    try {
      String answer = "Hello " + name;
      String users = Main.hello(name);
      String ret = answer.equals(users) ? "ok " : "not ok ";
      System.out.println(ret + index + " 引数が「" + name + "」の場合の返り値が「" + answer + "」であること");
    } catch (Exception e) {
      System.out.println("not ok " + index + " メソッドの実行に失敗しました: " + e.toString());
      e.printStackTrace();
    }
  }
  public static void main(String[] args) {
    doTest(1, "World");
    doTest(2, "Taro");
  }
}
```

RSpecやJUnitなどのテストフレームワークを使うことも可能ですが、テストフレームワーク自体が実行環境にあらかじめインストールされていない場合は初期化に時間がかかるため、あまり現実的ではありません。

使いたいテストフレームワークがある場合はご相談ください。

#### CLIエクササイズ
CLIエクササイズを定義するには`- mode: cli`を定義に加えます。
それ以外に定義可能なキーは以下のとおりです。

- name: Book内でユニークなエクササイズの名前(英数のみ)
- hidden: 任意。ユーザから不可視のファイルを指定します。通常テスト本体はhiddenで指定します。
- command: 必須。テストの実行コマンドを指定します。
- prepare: 任意。cli-templateの`build`の実行前に実行するコマンドがある場合に指定します。複数指定可能です。
- cwd: 任意。`command`を実行する場合のワーキングディレクトリ。

ユーザーには見えているけれど、編集はさせたくないファイルが存在する場合は`files`サブセクションで定義してください。

例
```
### exercise

- mode: client
- hidden: [test](assets/section1-1/test/*)
- command: mocha -R tap
```

#### CLIテストの書き方
CLIエクササイズでのテストの書き方は[CLIチャレンジのテスト](how-to-make-challenge.md#CLIチャレンジでのテストの書き方)に準じます。

通常はtrack標準のテストランナーである[codecheck](how-to-use-codecheck.md)を使用してテストを作成します。

実際にはchallengeとして作成してエクササイズとしてBookに取り込む方が利便性が高いのでほとんどの場合、次節で紹介するimport機能が使用されます。

#### チャレンジをエクササイズとしてインポートする
任意のcodingチャレンジまたはcliチャレンジをBookのエクササイズとして取り込むことができます。

その方法はtrack.ymlのあるディレクトリを`reference`というキーで参照するだけです。

```
- mode: coding
- reference: ../../challenges/challenge1
```

codingチャレンジはremoteエクササイズとして、cliチャレンジはcliエクササイズとして取り込まれます。

チャレンジとブックでは仕様が異なる部分があるのですべてのチャレンジが取り込めるわけではありません。(または取り込めたとしてもユーザにとって良いUXとはならないこともあります。)

主な違いは以下です。

- Bookでは任意のコマンド実行の仕組みは有りません。
- Challenge側でtestディレクトリ以下に配置されているファイルはhidden扱いになりユーザが内容を確認することはできません。
- Bookにはツリーがないため、すべてのファイルは最初からタブで表示されます。
  - このため編集するファイル数が多いChallengeはBook化には向きません。
  - testディレクトリ以下のファイルは上述の通り表示対象外です。
- `frontend`を使用するChallengeはプレビューする方法がないため事実上インポートできません。
- ユーザが自由にファイルを追加・削除することはできません。

#### エクササイズのコードの一部のみを編集可能とする
通常エクササイズの編集可能対象の指定はファイル単位です。

しかし、あらかじめ定義済みの関数をユーザに提示したいなど、編集可能な領域を制限したい場合もあるでしょう。
この場合、

- `EXERCISE_BEGIN_EDIT`
- `EXERCISE_END_EDIT`

というキーワードで編集可能とする領域を囲むことでその部分以外を編集不可とすることができます。

``` java
public class Main {
  public static void main(String[] args) {
    // EXERCISE_BEGIN_EDIT
    //この部分に解答コードを記述してください。

    // EXERCISE_END_EDIT
  }
}
```

`EXERCISE_BEGIN_EDIT`, `EXERCISE_END_EDIT`を含む行は実行時には削除されるのでブック読者からは見えません。
また、ひとつのファイル内に複数の編集可能領域を定義することも可能です。
(MarineでDevModeにした場合は画面上に表示されます。)

### sandbox
サンドボックスは受講者が自由にコード実行を試すことができるセクションです。
サンドボックスで編集可能なファイルはbook.ymlで指定しますが、各セクションで表示するファイルは`show`というキーで制御できます。

- show: このセクションで表示するサンドボックスファイル。複数指定可能です。
- preview: htmlモードの場合にプレビューとして表示するHTMLファイルを指定します。
- command: 任意。consoleモードの場合にテストの実行コマンドを指定します。
- build: 任意。consoleモードの場合に`command`の実行前に実行するコマンドがある場合に指定します。複数指定可能です。
- prepare: 任意。consoleモードの場合に`build`の実行前に実行するコマンドがある場合に指定します。複数指定可能です。
- cwd: 任意。consoleモードの場合に`build`および`command`を実行する場合のワーキングディレクトリ。
- after: consoleモードの場合に`command`実行後に実行する後処理コマンド。複数指定可
- previewFile: consoleモードの場合に`after`(無い場合は`command`)実行後に画面に表示するファイル。画像ファイルまたはHTMLファイルが指定可


### debug
remoteエクササイズとcliエクササイズではチャレンジと同様のdebug機能を定義することができます。

デバッグ定義の詳細は[Challengeのドキュメント](how-to-make-challenge.md#debug)を参照してください。

Bookでの定義はyamlではないので、定義の書式は以下のようなリスト形式になります。
(inputの`raw`と`file`の定義では`input`を省略して直接`raw`, `file`を指定します。)

```
### debug
- command: cat $f | $c
- raw:[テスト1]a b c
- file:[テスト2]test/in/file1.txt
```

チャレンジからインポートした際にはdebug定義もインポートされます。

### env
book.ymlでenvを定義する代わりに個別のセクションでenvを定義することができます。

定義できる内容はbookと同じです。詳細は[env.md](env.md)を参照してください。

定義の書式は以下のようなリスト形式になります。

```
### env

- imageName: givery/track-java-8
- cacheDirs: /root/.m2
- cacheDirs: /root/.gradle
```

### DevMode
MarineはBook(またはChallenge)の作成を補助するためのツールなので通常モードではエクササイズのエディタ上でユーザが変更した内容はどこにも保存されません。

ここを保存するようにした場合オリジナルのファイルを変更した後に画面をリロードしても、画面にはその変更が反映されない(ユーザファイルとして初期表示状態のファイルが保存されているのでそちらが表示されます)ため、「コンテンツを作成する」という目的にたいしては利便性が良くないためです。

しかし、それではcarryOverの確認などができないため、DevModeを選択した場合は受験者のユーザ体験をエミュレートできます。

DevModeにした場合は以下のような動作になります。

- エクササイズ画面でユーザが変更した内容がリロードしても維持されます。
- 原則そのセクションを解かないと次のセクションに移動できません。
  - ただし、スキップはできます。
- carryOverが機能します。
  - ノーマルモードでは常に定義によって参照されているファイルが表示されます。

DevMode中にメニューから「Clean up user code」を実行した場合は保存されているユーザコードがすべてクリアされます。



