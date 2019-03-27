# Coding Challengeの作り方
## 概要
Challengeとはユーザに実際にプログラムコードを書かせてその実行結果をユニットテストで検証するタイプのプログラミング問題のことを指します。
チャレンジは大きくは言語非依存のCLIチャレンジと特定言語向けのプログラミング問題となる言語依存チャレンジの2種類に別れます。

言語依存チャレンジの方が作成は簡単ですが、オフィシャル問題の多くは汎用性の観点からCLIチャレンジとなっています。

## CLIチャレンジと通常チャレンジ
CLIチャレンジではユーザが作成するプログラムはCLIアプリケーションになります。
すなわち、

- 引数、または標準入力から何かしらの入力パラメータを受け取り、
- 標準出力に何かを出力する

というアプリケーションです。言語はなんであっても構いません。(実際には後述するDockerImageで対応している必要があります。)

言語依存チャレンジは予め用意されたソースコードの一部をユーザに埋めさせるようなチャレンジです。
典型的な例は以下のようになります。

``` java
public class FizzBuzz {
  public String execute(int n) {
    // ここにFizzBuzzのコードを実装してください
  }
}
```

## テストの枠組み
trackのテストは基本的にUnitテストとして行われます。
一番外側の枠組みとしてはUnitテストに使用するフレームワークは[TAP](https://testanything.org/)に対応しているものであれば何でも使うことができます。(実際にはDockerImageにそのテストフレームワークがインストールされている必要があります。)

TAPとは簡単に言えば、

- Unitテストが成功の場合は「ok x ....」というフォーマットで行を出力
- Unitテストが失敗の場合は「not ok x ....」というフォーマットで行を出力

するテストフォーマットです。

CLIチャレンジの場合はJavaScriptのテストフレームワークである[mocha](https://mochajs.org/)を使用してテストを記述します。

## track.yml
基本的にチャレンジに含める内容の定義はtrack.ymlで定義します。
track.ymlでは以下のキーを定義します。

- type: string. 必須. 
  - チャレンジの場合は`coding`固定です
- editable: Array<string>
  - チャレンジに含め、編集可能なファイルを指定します。ワイルドカードが使用できます。
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
  - CLIチャレンジでは常にtrueにしてください。
- build: Array<string>
  - testで指定したコマンドの実行前に実行するビルドコマンドを指定します。(javac, makeなど)
  - CLIチャレンジの場合はCLIテンプレートによって上書きされるため、ここでの指定は無視されます。
- initialize: `commands`と`files`の2つのArray<string>
  - Webエディタでチャレンジを開いた時に一度だけ実行する初期化コマンド群と初期化で使用するファイルを指定します。
  - ここで指定した初期化ファイル及びコマンドの実行結果は受験者からは見えません。
 - mainFile: string
   - Webエディタ上で初期表示するファイルを指定します。
  - CLIチャレンジの場合はCLIテンプレートによって上書きされるため、ここでの指定は無視されます。
- languages: Array<string>
  - CLIチャレンジで使用可能な言語のリストを指定します。
  - `all`とした場合、サポートされているすべての言語が対象となります。
  - `languages`が指定されなかった場合、または単一言語のみが指定されていた場合は言語依存チャレンジとなります。
- templateType: string
  - CLIチャレンジで使用するテンプレート種別を指定します。
  - 現在は指定できる値は`default`、`stdin`の2つで、省略時のデフォルト値は`default`となります。
  - default: 入力パラメータをコマンドライン引数から受け取るタイプのコードテンプレートです。
  - stdin: 入力パラメータを標準入力から受け取るタイプのコードテンプレートです。
- envConf: hash
  - 必要に応じて以下のサブキーを定義します。
  - CLIチャレンジの場合はCLIテンプレートによって上書きされるため、ここでの指定は無視されます。
  - imageName: string. テストで使用するdockerイメージ名を指定します
  - workingDir: string. dockerイメージ内で使用するカレントディレクトリのパスを指定します。(省略時は`/root/src`になります)
  - cacheDirs: Array<string>. Webエディタ実行中にテスト実行サーバでキャッシュするディレクトリを指定します。(Ruby, Javaのライブラリキャッシュ等)
- variables: hash
  - テスト実行時に設定する環境変数を指定します。
- testcases: hash. 必須
  - 以下のサブキーを指定します。
  - open: number. オープンテストケースの数
  - secret: number. シークレットテストケースの数
- evaluationPoint: hash
  - 評価項目のキー名と説明を指定します。
  - 評価項目のキーはテストケースのタイトルの先頭に`[xxx]`のような形式で指定できます。


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

## 国際化対応
trackではチャレンジのコンパイル時にオプションとして言語(ja, en)を指定します。

このオプションによってREADMEを取り込む時のファイル選択のロジックが変わります。

- `ja` -> `README_ja.md`があればそれを使用、なければ`README.md`を使用
- `en` -> `README_en.md`があればそれを使用、なければ`README.md`を使用

国際化する問題の場合は日本語と英語の両方のREADMEを用意することが望まれます。

言語オプションで切り替わるのはREADMEのみでテストコード等は切り替わりませんが、言語オプションはテスト実行時に環境変数`CHALLENGE_LANGUAGE`で参照できます。

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

openTest、secretTest共に必須ではなく、openTestのみでsecretTestなしというチャレンジは作成することができますが、openTest, secretTestいずれもなし、というチャレンジは作成することができません。

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

solution.mdは必須ではありません。(例えばFizzBuzzのような超有名問題では省略しても問題ありません。)
solution.mdはtrack.ymlに含める必要はありません。

## BEGIN_CHALLENGEとEND_CHALLENGE
track.ymlの`editable`または`readonly`で指定したファイルに`BEGIN_CHALLENGE`, `END_CHALLENGE`という対の行が指定されている場合、その範囲はチャレンジ生成時に削除されます。

ただし、MarineでDevModeにチェックした場合はこの部分も残されます。

例

```
// 足し算を実行するメソッドを実装しなさい
function add(a, b) {
  // BEGIN_CHALLENGE
  return a + b;
  // END_CHALLENGE
}
```

上記の場合、受験者の環境では関数`add`の中身は空になっているので受験者自身が実装しない限りエラーとなりますが、MarineのDevModeでは実装が含まれているためテストを実行して結果を確認することができます。

## DockerImages
現在用意されている汎用Dockerイメージは以下のとおりです。
これらのイメージは[DockerHub](https://hub.docker.com/u/givery/dashboard/)で公開されています。

- Perl5: givery/track-perl-5
- Python3.6: givery/track-python-3.6
- Python2.7: givery/track-python-2.7
- C#: givery/track-mono-5
- Scala: givery/track-scala-2.12
- PHP: givery/track-php-7.2
- Go: givery/track-go-1.10
- NodeJS: givery/track-nodejs-10
- Java: givery/track-java-8
- Ruby givery/track-ruby-2.5
- C/C++: givery/track-base2

いずれの環境にもNodeJSとmochaはインストールされています。

## cli-templates
CLIチャレンジのlanguagesで指定できる言語は以下のとおりです。(`all`を除く)

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

それぞれの言語を指定した場合、対応するDockerイメージでテストが実行されます。
Dockerイメージとcli-templateを用意すれば、対応言語を増やすことができます。

## CLIチャレンジでのテストの書き方
CLIチャレンジではユーザの作成したアプリケーションの実行方法は`APP_COMMAND`という環境変数に定義されています。

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

現在サポートされているテンプレートは以下の2つです。

- default: 入力パラメータをコマンドライン引数から受け取るタイプのアプリケーションテンプレート
- stdin: 入力パラメータを標準入力から受け取るタイプのアプリケーションテンプレート

`templateType`がtrack.ymlで指定されなかった場合は`default`のテンプレートが使用されます。

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

`initialize`に指定したファイルやコマンドの実行結果は受験者からは見えません。

### initializeの省略記法
`initialize`セクションを指定する際に`files`の指定が必要ない場合はコマンドのみを直接の子リストとして指定するこができます。

```
initialize:
  - g++ -std=c++11 -o test/judge test/judge.cpp
```

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


