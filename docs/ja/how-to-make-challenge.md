# Challengeの作り方
## 概要
Challengeとはユーザに実際にプログラムコードを書かせてその実行結果をユニットテストで検証するタイプのプログラミング問題のことを指します。
チャレンジは大きくは

- 言語非依存のCLIアプリケーションを作成させるCLIチャレンジ(`type: cli`)
- 言語非依存の関数を実行させるFunctionチャレンジ(`type: function`)
- 特定言語向けのプログラミング問題となるCodingチャレンジ(`type: coding`)

の3種類に別れます。

※ track上ではCLIチャレンジはアルゴリズム問題、Functionチャレンジは関数問題、Codingチャレンジは実装問題と表示されています。

### CLIチャレンジ
CLIチャレンジではユーザが作成するプログラムはCLIアプリケーションになります。
すなわち、

- 引数、または標準入力から何かしらの入力パラメータを受け取り、
- 標準出力に何かを出力する

というアプリケーションです。言語はなんであっても構いません。(実際には後述するDockerImageで対応している必要があります。)

### Functionチャレンジ
Functionチャレンジは問題作成者が定義した関数をユーザに実装させるチャレンジです。
引数および返り値には

- string
- int
- float
- boolean
- 上記の型の配列と二重配列

が使用できます。(言語によって対応する型は変わります。)

### Codingチャレンジ
言語依存チャレンジは予め用意されたソースコードの一部をユーザに埋めさせるようなチャレンジです。
典型的な例は以下のようになります。

``` java
public class FizzBuzz {
  public String execute(int n) {
    // ここにFizzBuzzのコードを実装してください
  }
}
```

---
CLIチャレンジとFunctionチャレンジはアルゴリズム等の基礎知識を問う問題に向いており、Codingチャレンジはその言語の習熟度を問う問題に向いています。
(歴史的にはFunctionチャレンジは後から追加実装されました。現在ではCLIチャレンジよりもFunctionチャレンジの方がユーザーフレンドリーなので推奨されます。)

### オフィシャルチャレンジとカスタムチャレンジ
オフィシャルチャレンジとはtrackが公式に作成しているチャレンジのことです。
プランによって使える範囲に違いはありますが、契約企業であれば誰でも使用することができます。

カスタムチャレンジとはtrackの顧客企業が自社で使用するために専用で作成したチャレンジのことです。
自社以外の企業がその問題を使用することはできません。

チャレンジの作り方において、基本的にはオフィシャルとカスタムで違いはありませんが、

- オフィシャルチャレンジはsolutionで満点回答が必須

など、クオリティ担保のための制限がオフィシャルチャレンジの方が多少厳しくなっています。

## テストの枠組み
trackのテストは基本的にUnitテストとして行われます。
一番外側の枠組みとしてはUnitテストに使用するフレームワークは[TAP](https://testanything.org/)に対応しているものであれば何でも使うことができます。

TAPとは簡単に言えば、

- Unitテストが成功の場合は「ok x ....」というフォーマットで行を出力
- Unitテストが失敗の場合は「not ok x ....」というフォーマットで行を出力

するテストフォーマットです。

CLI/Functionチャレンジの場合はJavaScriptのテストフレームワークである[mocha](https://mochajs.org/)を使用してテストを記述します。
Codingチャレンジでは対象の言語用の任意のテストフレームワークを使用することができます。
(実際にはDockerImageにそのテストフレームワークがインストールされている必要があります。)

## track.yml
基本的にチャレンジに含める内容の定義はtrack.ymlで定義します。
track.ymlでは以下のキーを定義します。

- type: string. 必須.
  - `cli`, `functiopn`, `coding`のいずれか
  - AIチャレンジの場合はここに`ai`と指定しますが、この文書では扱いません。
- editable: Array<string>
  - チャレンジに含め、編集可能なファイルを指定します。ワイルドカードが使用できます。
  - 主にCodingチャレンジでユーザに編集させるファイルを指定します。
- readonly: Array<string>
  - チャレンジに含め、編集不可なファイルを指定します。ワイルドカードが使用できます。
  - 主にテストファイルをここで指定します。
- hide: Array<string>
  - チャレンジに含めるが、受験者からは不可視なファイルを指定します。ワイルドカードが使用できます。
  - 主にSecretTestで使用するファイルをここで指定します。
- testExclude: Array<string>
  - editable, readonly, hideに指定されたファイルのうちテスト実行サーバに転送する必要のないファイルを指定します。ワイルドカードが使用できます。
  - サンプル用のデータファイルなどテストの実行に不要なファイルをここで指定することでテスト実行のパフォーマンスが上がります。
- images: Array<string>
  - README.mdから参照する画像ファイルを指定します。ワイルドカードが使用できます。
  - ここで指定されたファイルはREADME.mdから相対パスで参照できますが、Webエディタのツリー上には表示されません。
- test: string. 必須
  - テストの実行コマンドを指定します
- allowNewFile: boolean
  - Webエディタ上で新規ファイルの作成を許すかどうかを指定します。
- build: Array<string>
  - testで指定したコマンドの実行前に実行するビルドコマンドを指定します。(javac, makeなど)
  - CLI/Functionチャレンジの場合はCLIテンプレートによって上書きされるため、ここでの指定は無視されます。
- initialize: `commands`と`files`の2つのArray<string>と、`showConsole`(boolean)
  - Webエディタでチャレンジを開いた時に一度だけ実行する初期化コマンド群と初期化で使用するファイルを指定します。
  - デフォルトではここで指定した初期化ファイル及びコマンドの実行結果は受験者からは見えません。
  - `showConsole: true`を指定した場合は初期化の過程が受験者に表示されます。
- mainFile: string
  - Webエディタ上で初期表示するファイルを指定します。
  - CLI/Functionチャレンジの場合はCLIテンプレートによって上書きされるため、ここでの指定は無視されます。
- languages: Array<string>
  - Codingチャレンジの対象言語を指定します。
  - `html`, `javascript`のように複数指定することもできます。
- templateType: string
  - CLIチャレンジで使用するテンプレート種別を指定します。
  - 現在は指定できる値は`default`、`stdin`、`plain`の3つで、省略時のデフォルト値は`default`となります。
  - default: 入力パラメータをコマンドライン引数から受け取るタイプのコードテンプレートです。
  - stdin: 入力パラメータを標準入力から受け取るタイプのコードテンプレートです。
  - plain: 入力パラメータを受け取らない空のテンプレートです。
- envConf: hash
  - ユーザコードを実行するDockerコンテナの情報を指定します。
  - CLI/Functionチャレンジの場合はテンプレートによって上書きされるため不要です。
  - Codingチャレンジの場合は必須です。
  - 指定内容の詳細は[env.md](env.md)を参照してください。
- testcases: hash. 必須
  - 以下のサブキーを指定します。
  - open: number. オープンテストケースの数
  - secret: number. シークレットテストケースの数
- evaluationPoint: hash
  - 評価項目のキー名と説明を指定します。
  - 評価項目のキーはテストケースのタイトルの先頭に`[xxx]`のような形式で指定できます。
- solutions: Array<string>
  - 問題の解答例を含むファイルを指定します。
  - 言語バージョンの更新を行った際にチャレンジが動作することを検証するためにも使用するので必ず一つ以上作成してください。
  - オフィシャル問題は原則満点解答を作成していますが、カスタム問題では1点以上の得点が取れる(=コード自体が正しく実行できる)解答コードであれば、必ずしも満点回答でなくても構いません。
  - 解答例には後述する自動登録機能を使うこともできます。
- shared: Array<string>
  - 複数のチャレンジで共有するファイル群の置き場所を指定します。
  - 書式及び使い方は後述します。
- debug: hash
  - 一通りのUnitテストとは別に個別に実行する実行パラメータを指定します。
  - 書式及び使い方は後述します。
- watch: Array<string>
  - コマンド実行による更新を監視するファイルのパスを指定します。
  - ここで指定されたファイルはコマンド実行によって更新された内容がエディタに反映されます。
  - 例. `package.json`を指定していた場合、`npm install xxx`によって更新された内容が反映されます。
  - CLI/Functionチャレンジでは選択された言語によって定義されているので指定する必要はありません
- function: hash
  - Functionチャレンジの関数定義を記述します。
  - Functionチャレンジでは必須ですが、それ以外の場合は不要です。
  - 書式および使い方は後述します。
- functionInputDir: Array<string>
  - FunctionチャレンジのtestcaseのJSONを置くディレクトリを指定します。
- systemTag: Array<string>
  - trackおよびその周辺ツールの振る舞いを規定するフラグフィールドを指定します。
  - 使い方は後述します。

未知のキーは無視されます。

例
```
type: coding
allowNewFile: true
test: mocha
editable:
  - answer.md
readonly:
  - test/base.js
  - test/cases.json
hide:
  - test/secret*
testExclude:
  - answer.md
languages: all
solution: solution.js
variables:
  APP_COMMAND: node solution.js
testcases:
  open: 8
  secret: 8
evaluationPoint:
  ファイルIO: ファイル入出力のコードができているかどうかを評価します
  エラー処理: 適切なエラー処理ができているかどうかを評価します
```

## README.md
README.mdには問題の内容をマークダウンで記述します。
フォーマットは任意ですが、オフィシャル問題の場合はある程度テンプレート化されているのでテンプレートに従って記述するようにしてください。

マークダウンの記述ではいくつかの[拡張機能](markdown-extension.md)が使用できます。

README.mdはtrack.ymlに含める必要はありません。

## openTestとsecretTest
openTestとはテストコード、テストケースともにユーザに可視となっているテストです。
それに対してsecretTestはユーザの目に触れることはありません。

track.ymlで言えば

- readonlyに指定されたテスト -> openTest
- hideに指定されたテスト -> secretTest

という対応になります。

典型的な使い方としては

- 簡単で基本的なテストはopenTestで
- 複雑、あるいはエッジケースはsecretTestで

定義します。

ユーザは受験の際にはopenTestを繰り返し実行します。
そしてすべてのopenTestにパスしたら満点だと思って提出することでしょう。
しかし、実際には隠されたsecretTestによって部分点しか取れていないということもありえます。
(ユーザはsecreTestの存在を知ることはできません。)

secretTestは必須ではなく、openTestのみでsecretTestなしというチャレンジは作成することができますが、openTestのないチャレンジは作成することができません。

実行されるopenTest, secretTestの数はtrack.ymlの`testcases`に定義する必要があります。
ここで定義された数字と実際に実行されたテストケース数が異なる場合はtrack上で警告となります。

Marineでは通常、SecretTestはWebエディタ上に表示されませんが、DevModeにチェックを入れた場合は表示されます。

## answer.md
trackではプログラミング問題ごとに、受験者に

- 実装の簡単な説明
- 難しい点はなんだったか？

などを自由記述で記述させることができます。(これを書くための時間はプログラミング問題の制限時間には含まれません)
answer.mdはこの自由記述のためのテンプレートです。

例

```
## 実装内容の詳細を記述してください

## 問題に対する疑問点等あれば記述してください。
```

answer.mdが存在しない場合は白紙のテンプレートがユーザに提示されます。
answer.mdはtrack.ymlに含める必要はありません。

## solution.md
solution.mdは出題者が問題の解き方について、簡単な説明を記述するファイルです。
solution.mdの内容は企業ユーザ(出題側)には提示されますが、受験者が目にすることはありません。

solution.mdはtrack.ymlに含める必要はありません。

## 国際化対応
trackではチャレンジのコンパイル時にオプションとして言語(ja, en)を指定します。

このオプションによってREADME.mdとsolution.mdを取り込む時のファイル選択のロジックが変わります。

- `ja` -> `README_ja.md`があればそれを使用、なければ`README.md`を使用
- `en` -> `README_en.md`があればそれを使用、なければ`README.md`を使用

solution.mdも同様のロジックでで使用されるファイルが切り替わります。
国際化する問題の場合は日本語と英語の両方のREADMEを用意することが望まれます。

また、track.ymlでは指定された言語に応じて、`track_en.yml`または`track_ja.yml`が存在した場合、それがマージされて読み込まれます。

例えばevaluationPointやテストケースのファイルを日英で切り替えたい場合は切り替える定義のみを`track_en.yml`(`track_ja.yml`)に記述することで対応することができます。

※ 正確に言うとtrack.ymlの読み込み時に行われるマージはトップレベルキーの置換です。
例えばtrack.ymlに日本語で`evaluatpionPoint`が定義されており、track_en.ymlに英語で`evaluationPoint`が定義されている場合、`en`でのコンパイル時には`evaluationPoint`は英語に置き換わります。(日本語での定義と英語での定義が両方含まれるリストになるわけではありません。)

このため、

- 日本語での完全な定義をtrack.ymlで行う
- 英語に置換する部分だけをtrack_en.ymlで定義する

という手法も可能であり、必ずしも`track_en.yml`と`track_ja.yml`をセットで用意しなければならないわけではありません。

言語オプションではテストコード等は切り替わりませんが、テスト実行時に環境変数`CHALLENGE_LANGUAGE`で言語オプション(`ja`または`en`)を参照できます。

この環境変数を利用すればテストコード内でメッセージを切り替えることも可能になります。

mochaで外部jSONファイルからtestcaseを読み込んで実行する例

```
const lang = process.env.CHALLENGE_LANGUAGE;
const testcases = require("./testcases.json");

testcases.forEach(case => {
  const title = case.title[lang];
  it(title, () => {
    ...
  });
});

```

## solutions
solutionsには問題の解答例となるファイルを指定します。
solutionsの登録にはファイル名を指定しますが、`:`で区切って実際のファイル名とテスト実行時のファイル名を変更することもできます。

例
``` yaml
solutions:
  - solution.js:js-solution/solution.js
  - package.json:js-solution/package.json
  - extra.js:js-solution/extra.js
```

`:`の前がテスト実行時のファイル名、後ろが実際に問題のディレクトリ内で保存されているファイル名です。

ただし、問題のルートディレクトリにある「solution.xx」という名前のファイル(`.xx`は拡張子。`.md`, `.class`, `.bak`は除く)は指定を省略しても自動的に登録されます。

### CLI／Functionチャレンジの場合
CLI/Functionチャレンジの解答例は各言語に対応した拡張子を使用して「solution.xx」という名前で`solutions`に登録します。

例.

- Ruby用の解答例。 `solution.rb`
- NodeJS用の解答例。 `solution.js`
- Java用の解答例。 `solution.java`

これらのファイルは各言語テンプレートのメインファイルと置き換えられます。
Javaの場合はファイル名は`solution.java`としますが、ファイル内で適宜するクラスはテンプレートにあわせて

- `package track;`
- `public class App`

としてください。

ルートディレクトリにある「solution.xx」というファイルは自動的に`solutions`に登録されるので単純な解答例の場合は実質`solutions`へのキーの登録は省略できます。

メインファイル以外にも必要なファイルがある場合はそのファイルを`solutions`に登録してください。
例えばNodeJSで外部ライブラリが必要な場合、そのための`package.json`をコピーする必要があります。

テスト実行時には実行するCLIテンプレートに応じて、

- 拡張子が対象言語と同じファイル(NodeJSなら`.js`, Rubyなら`.rb`など)
- 指定されたファイルがCLIテンプレート内に存在する場合(Javaの`pom.xml`, Python3の`requirements.txt`など)

がコピーされます。

### Codingチャレンジの場合
Codingチャレンジの場合は`solutions`で指定されたファイルがすべてテスト実行時にコピーされます。
`editable`で指定されているファイルが`solutions`に指定されている場合は上書きされます。

Codingチャレンジでもルートディレクトリにある`solution.xx`というファイルは自動的に登録されますが、そのファイルはtrack.ymlの`mainFile`で指定されたファイルと置き換えられます。

## DockerImages
使用可能なdockerイメージの一覧は[env.md](env.md)を参照してください。

## cli-templates
CLI/Functionチャレンジで使用できる言語は以下のとおりです。

- c
- c++
- c#
- java
- nodejs
- php
- python
- python3
- scala
- perl
- ruby
- go
- swift
- kotlin
- rust

それぞれの言語を指定した場合、対応するDockerイメージでテストが実行されます。
Dockerイメージとcli-templateを用意すれば、対応言語を増やすことができます。

## Functionチャレンジにおける関数定義
Functionチャレンジを作成する場合、track.ymlに`function`というキーで関数を定義します。

function定義は以下のキーを持つ構造体です。

- name: string。関数名。必須
- arguments: 以下の3つのキーを持つ構造体の配列。一つ以上必須
  - name: string。引数名。必須
  - type: string。データ型。必須
  - description: string。説明。省略可
- result: 以下の二つのキーを持つ構造体
  - type: string。データ型。必須
  - description: string。説明。省略可

データ型として使用できる値は以下です。

- int(int[], int[][]): 整数
- string(string[], string[][]): 文字列
- float(float[], float[][]): 小数
- boolean(boolean[], boolean[][]): 整数

データ型名に続く`[]`は配列を表し、二重配列までがサポートされています。

例:
```
function:
  name: myFunction
  arguments:
    - name: a
      type: string
      description: "何かの文字列"
    - name: b
      type: int
      description: "何かの数字"
    - name: c
      type: string[]
      description: "何か文字列の配列"
  result:
    type: string[]
    description: "返り値の配列"
```

関数名と引数名はcamelCaseで定義してください。(選択した言語によってsnake_caseやPascalCaseに変換されます)

descriptionの日英対応が必要な場合は国際化の枠組みに従ってtrack.ymlを分割します。

## CLIチャレンジでのテストの書き方
CLI/Functionチャレンジではユーザの作成したアプリケーションの実行方法は`APP_COMMAND`という環境変数に定義されています。

ここまでの枠組みをおさらいしておくと、

- テストの実行はTAP形式で結果を出力するテストフレームワークで実行する必要がある
- すべての汎用DockerイメージにはNodeJSとmochaがインストールされている

ということで、テストの実装は

- mochaの中から`APP_COMMAND`で定義されたコマンドをキック
- その際に引数または標準入力経由で入力パラメータを渡す
- プロセスから標準出力を取得して結果を検証

とすることで実現できます。

ただし、これをチャレンジ毎に毎回実装するのはしんどいのでNodeJSのライブラリとして[codecheck](https://www.npmjs.com/package/codecheck)というユーティリティライブラリが用意されています。

このライブラリがどのように使えるかは[how-to-use-codecheck.md](how-to-use-codecheck.md)を参照してください。

## templateType
CLIチャレンジではtrack.ymlに`templateType`を指定することで、言語切り替えをした際に最初に表示されるテンプレートファイルを切り替えることができます。

現在サポートされているテンプレートは以下の3つです。

- default: 入力パラメータをコマンドライン引数から受け取るタイプのアプリケーションテンプレート
- stdin: 入力パラメータを標準入力から受け取るタイプのアプリケーションテンプレート
- plain: 入力パラメータを受け取らないタイプのアプリケーションテンプレート

`templateType`がtrack.ymlで指定されなかった場合は`default`のテンプレートが使用されます。

## Functionチャレンジのテストの書き方
Functionチャレンジにおけるテスト実行の大枠はCLIチャレンジと同じです。

標準入力から入力パラメータを読み取り、それを引数として定義された関数に渡してその返り値を標準出力に出力することで結果を検証します。

実行時には入力パラメータはトークン区切りのテキストとして標準入力から渡されますが、このテキストを問題作成者が自分で作成するのはメンテナンス性に難があるので、平文で入力テキストを作成する代わりにJSONで定義したパラメータから生成することができます。

例えば、関数の引数定義が

- a: string
- b: int
- c: string[]

である場合、入力のJSONは以下のように定義します。

input1.in.json
```
{
  "a": "a1",
  "b": 1,
  "c": ["c1", "c2"]
}
```

上記の入力定義はコンパイル時に以下のテキストファイルに変換されます。

input1.in
```
a1
1
2
c1
c2
```

この変換が行われる条件は以下のとおりです。

- 変換を行う入力のJSONが置かれるディレクトリはtrack.yml#functionInputDirで定義されていなければならない
- 定義ファイルの拡張子は`.json`でなければならない
  - 変換後のファイルは同じディレクトリに`.json`を取り除いたファイル名で保存されるのでcodecheckを使用する場合はinputのファイル名は`.json`のないファイル名で指定します。

入力パラメータに文字列を使用する場合、その文字列に空白文字を含めることはできません。

## initialize
track.ymlの`initialize`セクションにはチャレンジの初期化時に使用するファイルとコマンドのセットを指定することができます。

オフィシャル問題ではこの機能を正誤判定を行う専用アプリケーションのコンパイルとソースコードの削除で使っているものがいくつかあります。

```
# C++で作成したjudgeというアプリケーションをコンパイルし、その後ソースコードを削除
initialize:
  files:
    - test/judge.cpp
  commands:
    - g++ -std=c++11 -o test/judge test/judge.cpp
    - rm test/judge.cpp
```

デフォルトではここで指定した初期化ファイル及びコマンドの実行結果は受験者からは見えませんが、`showConsole: true`を指定した場合は初期化の過程が受験者に表示されます。

## evaluationPoint
track.ymlの`evaluationPoint`セクションを利用するとテストケースを評価項目毎に分類することができます。
`evaluationPoint`には以下のように評価項目のキーと説明を記述します。


```
evaluationPoint:
  ファイルIO: ファイル入出力のコードができているかどうかを評価します
  エラー処理: 適切なエラー処理ができているかどうかを評価します
```

そして、テストケースを記述する際に対応する`evaluationPoint`のキーを`[]`で括ってテストケースタイトルの先頭に記述します。
テストケースの記述方法は使用するテストフレームワーク毎に異なるのでここではTAPでの出力を例示します。


```
ok 1 [ファイルIO]入力ファイルが読み込めている
ok 2 [エラー処理]ファイルが存在しないエラーが正しく処理できる
not ok 3 [エラー処理]ファイルの形式が違うエラーが正しく処理できる
ok 4 (その他のテスト...)
...
```

テスト項目に`evaluationPoint`のキーが指定されている場合は、trackの管理画面上で項目ごとに分類されて表示されます。

- すべてのテストケースに`evaluationPoint`の指定が必要なわけではありません。
- 一つのテストケースに複数の`evaluationPoint`を指定することはできません。
  - 2つ目以降は無視されます。

## shared
`shared`とは複数のチャレンジでファイルを共有するための仕組みです。

例えば、SQL関連のチャレンジを作成する場合に複数のチャレンジでデータセット(初期化時に実行するSQL)やユーティリティスクリプトを共有することができます。

### sharedの書式
`shared`の書式は以下の形式となります。

```
- <参照名>:<参照ディレクトリへの相対パス>[:<参照名のエイリアス>]
```

例. 共有のinit.sqlを`sql/init.sql`という名前で参照する

```
readonly:
  - sql/init.sql
shared:
  - sql:../shared/sql
```

参照名のエイリアスを指定した場合、実行時のファイル名が参照名から指定の値に置き換わります。

例. 複数のチャレンジでいくつかのテストを共有する

```
readonly:
  - sharedTest/*.js
shared:
  - sharedTest:../shared/test:test
```

上の定義では`../shared/*.js`ファイルが実行環境の`test`ディレクトリにあるものとして扱われます。
この時、チャレンジのフォルダに`test`ディレクトリ及び共有しているファイルとは異なる`test/*.js`があっても構いませんが、同じファイル名のファイルがある場合はどちらが使われるかは不定です。

参照名のエイリアスに`_`を指定した場合、ルートディレクトリにそのファイルがあるものとして扱われます。

例. package.jsonの共有
```
readonly:
  - sharedJS/package.json
shared:
  - sharedJS:../shared/js:_
```

上の定義では`../shared/js/package.json`が実行環境のルートディレクトリにあるものとして扱われます。

## debug
debugには受験者が自分の書いたコードの動作を確認するための手助けとなるようなコマンドとパラメータのセットを定義します。

ここで定義するのは一つの `command`と複数の`input`です。

### command
`command`には実行に使用するコマンドを定義します。

コマンド定義には以下の3つのプレースホルダが使用できます。

- `$f` - 入力パラメータの内容が保存されたファイル名に置き換わります。
- `$*` - 入力パラメータの内容がコマンドライン引数の形式で展開されます。
- `$c` - CLIチャレンジで選択された言語のプログラムの実行コマンドに置き換わります。

例

- `node test/debug.js $f` - 入力パラメータが保存されたファイルを引数にdebug.jsを実行します
- `cat $f | $c` - CLIチャレンジでユーザが作成したプログラムの標準入力に入力パラメータを流し込んで実行します。


### input
事前定義の入力パラメータを定義します。

入力パラメータの指定の仕方には直接track.ymlに値を指定する方法(`raw`)と入力パラメータの内容が記述されたファイルのファイル名を指定する方法(`file`)の2つがあります。

- `raw:[テスト1]a b c` - 入力パラメータは`a b c`です。
- `file:[テスト2]test/in/file1.txt` - 入力パラメータはfile1.txtの内容です。

`[]`で括られた部分はドロップダウンでの表示名になります。

エディタ上では事前定義のパラメータをユーザが変更して実行することも可能です。

### cliチャレンジの場合の自動定義
[codecheck](how-to-use-codecheck)を使用して、テストケースを設定ファイルで定義している場合はその内容から自動的にdebug定義が作成されます。

## systemTag
systemTagにはtrackおよびその周辺ツールの振る舞いを規定するためのフラグ値を指定します。配列フィールドとなっているので複数指定することが可能です。

指定できる値は以下の3つです。

### alwaysSave
この値が指定されている場合、受講者がテスト実行を行う度に毎回backend側での採点が行われます。(通常はファイル変更を行わずにテスト実行を連続で実行してもbackend側での採点は行われません。)

受講者にAPIサーバをデプロイさせて、その挙動をテストする問題の場合に指定します。

### incompleteSolution
この値が指定されている場合、オフィシャルチャレンジであっても満点回答が必須ではなくなります。(カスタムチャレンジは元々満点回答が必須ではないので指定する必要はありません。)

計算量の効率化を問う問題で、そもそも全てのテストケースを規定時間内にパスすることが難しい場合に指定します。

### simpleBuild
この値が指定されている場合、CLI/Functionチャレンジのbuildプロセスでライブラリインストールを省略してbuildコマンドを簡素化します。

例
- Java
  - default: `gradle build`
  - simpleBuild: `javac`
- NodeJS
  - default: `npm install` あり
  - simpleBuild: `npm instaall`なし

意図的にライブラリを使わせたくないような問題の場合に指定します。
(simpleBuildの場合はheavyなビルドツールを使わないのでbuild時間が短くなるというメリットもあります。)


