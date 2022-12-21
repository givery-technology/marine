# codecheckを利用したCLIチャレンジのテスト作成
## codecheckとは？
trackのCLIチャレンジのようなCLIの入出力に対するテストを簡単に作成できるようにしたユーティリティライブラリです。  
GitHub上の[public repostiroy](https://github.com/code-check/codecheck)で公開されています。

アルゴリズム問題をCLIアプリケーションで作成させた際のテスト方法のバリエーションはそれほど多くありません。  
それを極力定型化して、テスト作成のコストを抑えることがこのライブラリの目的です。

具体的には

- settings.jsonでテストの手法を規定する
- testcases.jsonにテストケースの一覧を定義する
- TestRunnerでテストを実行する

という流れでテストが行われます。

## settings.json
settings.jsonでは以下のキーが定義できます。

- input: 入力パラメータに関する定義のプレースホルダです。
  - type: 入力パラメータの渡し方を定義します。省略時のデフォルト値は`arguments`です。
    - `arguments` - コマンドライン引数としてパラメータを渡します。
    - `stdin` - 標準入力を利用してパラメータを渡します。
  - source: testcases.jsonでの実際の値の格納場所を定義します。省略時のデフォルト値は`file`です。
    - `file` - testcases.jsonで指定されているのはファイル名で、実際の入力パラメータはファイルのコンテントとして指定されます。
    - `raw` - testcases.jsonで指定されているのは実際のパラメータの内容です。
- output: CLIアプリケーションの出力に関する定義のプレースホルダです。
  - type: 出力の方法を定義します。省略時のデフォルト値は`stdout`です。
    - `stdout` - ユーザが作成するCLIアプリケーションは標準出力に結果を出力します。
    - `file` - ユーザが作成するCLIアプリケーションは標準出力に結果を出力します。
  - source: testcases.jsonでの期待する出力結果の格納場所を定義します。省略時のデフォルト値は`file`です。
    - `file` - testcases.jsonで指定されているのはファイル名で、実際の期待する出力結果はファイルのコンテントとして指定されます。
    - `raw` - testcases.jsonで指定されているのは期待する出力結果の内容です。
  - filename: `type=file`の場合の出力ファイル名です。省略時のデフォルト値は`answer.txt`です。
- judge: 特殊なjudgeアプリケーションを使用する場合にその内容について定義するプレースホルダです。judgeを使用しない場合は省略します。
  - command: judgeを実行するためのコマンドを指定します。
- limitations: エラーメッセージ等の出力に関するプレースホルダです。(ユーザの出力を制限するわけではありません。)
  - maxLines: 最大出力行数。これを超える出力は省略されます。
  - maxCharacters: 最大出力文字数。これを超える出力は省略されます。
- timeout: ひとつのテストケースに対するタイムアウトの時間をミリ秒単位で指定します。省略時のデフォルトは`6000`です。
- tleFactorEnabled: `timeout`の値に対して言語ごとの補正を行うかどうかのフラグ
  - trueの場合は、ユーザが選択したプログラミング言語に応じてタイムアウトの補正がかかります。
  - 言語ごとの補正値は後述
  - 省略時のデフォルトはfalseです。
- baseDirectory: testcases.jsonのベースディレクトリを指定します。省略時のデフォルトは`test`です。
- language: testcase.jsonで使用する言語を指定します。省略時のデフォルトは`ja`です。
- eps: 小数の許容誤差。例えばepsの値が`0.00001`だった場合、トークンの比較時に正解が`1.0`であっても`1.0000099`などの値(正解+/-eps未満の値)は正解となります。より正確には、絶対誤差または相対誤差がeps以下のとき、正解となります。

サンプル
```
{
  "input": {
    "type": "arguments",
    "source": "file"
  },
  "output": {
    "type": "file",
    "source": "file",
    "filename": "answer.txt"
  },
  "judge": {
    "command": "test/judge"
  },
  "limitations": {
    "maxLines" : 20,
    "maxCharacters" : 300
  },
  "timeout": 6000,
  "baseDirectory":  "test"
}
```

`language`はチャレンジの設定によって後から動的に変更するため、通常はsettings.json内では指定しません。

### 旧形式のsettings.jsonの自動変換
2018年以前に作成されたチャレンジではこれとは異なる形式のsettings.jsonが使用されていました。
旧形式のsettings.jsonは新形式に自動的に変換されるので、そのまま使用することができます。

ここではどのような変換が行われるかの詳細については説明しません。

## testcases.jsonの内容
testcases.jsonではトップレベルに個別のtestcaseを表すオブジェクトの配列を定義します。

各testcaseオブジェクトは以下のキーを持ちます。

- input: 入力パラメータの値。または入力パラメータ定義ファイルへのパス
  - settings.jsonの`input/source=raw`の場合は値そのもの、`file`の場合はファイルへのパスとなります。
- output: 出力期待値の値。または出力期待値定義ファイルへのパス
  - settings.jsonの`output/source=raw`の場合は値そのもの、`file`の場合はファイルへのパスとなります。
- description: testcaseの名前
  - 言語ごとに`description_ja`, `description_en`のようなsuffixをつけたキーを並列に定義することもできます。

サンプル
```
[{
  "input": "in/basic/case01.in",
  "output": "out/basic/case01.out",
  "description": "[基礎問題] テストケース1",
  "description_en": "[Basic] Testcase1"
 }]
 ```

suffix付きのdescriptionはsettings.json#languageの設定に応じて選択的に使用されます。

- settings.json#language='ja': `description_ja`があればそれを使用。なければ`description`を使用
- settings.json#language='en': `description_en`があればそれを使用。なければ`description`を使用


## TestRunnerを使用した典型的なテスト
ここまでの内容を踏まえて、TestRunnerを使用するテストの典型的なコードは以下のようになります。

``` javascript
const codecheck = require("codecheck");

const language = process.env.CHALLENGE_LANGUAGE || "ja"; // Challengeの言語設定は環境変数`CHALLENGE_LANGUAGE`で取得できます。
const appCommand = process.env.APP_COMMAND; // 受験者の作成したアプリの実行コマンドは環境変数`APP_COMMAND`で取得できます。

const settings = require("./settings.json"); // settings.jsonを読み込み
settings.language = language; // settings.jsonにlanguageを設定

const testcases = require("./basic_testcases.json"); // testcases.json(testcaseの配列)の読み込み

const testRunner = codecheck.testRunner(settings, appCommand); // TestRunnerの生成。引数はsettings.jsonとユーザアプリの実行コマンド
testRunner.runAll(testcases); // TestRunnerですべてのtestcaseを実行
 ```

単純なチャレンジであれば、上記のコードは１行も変更せずにsettings.jsonとtestcases.jsonの変更だけでテストを作ることができます。

## 出力比較の詳細
多くの場合、testcaseの成否はファイルとして用意した期待出力内容と実際のユーザーアプリケーションの出力を比較することで判断されます。
ただし、この時には単純な全体文字列としての完全一致で比較されるのではありません。

それぞれの文字列を空白および改行文字(\x20, \x08, \x10, \x13)で区切ってトークナイズし、それぞれのトークンごとに比較を行っています。
このため、改行コードの違いや末尾の空白または改行の有無などは結果の比較に影響を与えません。

## tleFactorEnabled
プログラムの実行速度はそれを作成した言語によって大きく異なります。  
例えばRubyで作成したプログラムは同じ処理を行うC言語で作成されたプログラムよりも圧倒的に遅いです。

ユーザの使用する言語によってタイムアウト時間を補正したい場合は、settings.jsonに`tleFactorEnabled: true`を指定します。

これにより選択した言語により以下の補正がかかります。

- C - x1.0
- C++ - x1.0
- Swift - x 1.0
- C# - x1.5
- Go - x2.0
- Java - x2.0
- Kotlin - x2.0
- Rust x2.5
- Scala - x3.5
- Perl - x4.5
- PHP - x4.5
- NodeJS - x5.0
- Python - x5.0
- Ruby - x5.0

## judgeを使用するテスト
チャレンジの内容によっては単純な期待値とユーザ出力の比較では成否を判断できないことがあります。
この場合、カスタムのjudgeアプリケーションを作成する必要があります。

judgeの作成に使用できる言語はC/C++またはNodeJSです。

## judgeアプリケーションの実行
judgeアプリケーションの実行時の引数は以下のようになります。

```
[settings.json/judge/commandで指定されたコマンド] [入力パラメータのファイル名] [出力期待値のファイル名] [ユーザの出力が保存されたファイル名]
```

judgeを使用する場合、[出力期待値のファイル名]は存在しないこともあるので、その場合は`null`という文字列が変わりに渡されます。  
settings.jsonでユーザアプリの出力が`stdout`となっている場合でも、judgeに渡される場合は一度ファイルに保存されてファイル名が渡されます。

## judgeアプリケーションの出力
judgeアプリケーションは内部で入力パラメータとユーザ出力を比較してその成否を出力する必要があります。
その方法は以下のとおりです。

- 結果が正の場合
  - exit_code=0でアプリを終了
- 結果が否の場合
  - エラーメッセージを標準エラー出力に出力
  - exit_code 0以外でアプリを終了

エラーメッセージの国際化が必要な場合はjudgeアプリケーション内で環境変数`CHALLENGE_LANGUAGE`を読んでください。

## judgeアプリケーションの開発言語
受験者にjudgeのソースコード自体が見えても問題ない場合はNodeJSで作成して問題ありません。  
(judgeアプリケーションはtrack.ymlの設定でチャレンジに含める必要があります。)

しかし、judgeの内容が受験者の目に見えるのが不都合な場合はC/C++で作成して、コンパイル後に削除するようにしてください。  
その場合のtrack.ymlの設定は以下のようになります。

```
initialize:
  commands:
    - g++ -std=c++11 -o test/judge test/judge.cpp
    - rm test/judge.cpp
  files:
  - test/judge.cpp
```

`initialize`セクションでjudgeをコンパイル後ソースコードを削除しています。


## TestRunnerのカスタマイズ
TestRunnerはメソッドをオーバーライドすることにより一部の動作を変更可能なように設計されています。

https://github.com/code-check/codecheck/blob/master/src/test_runner/testRunner.js

要件によってはこの拡張によってより柔軟なテストを行うことも可能です。

以下実際に使用しているカスタマイズ例を示します。

- 出力の期待値はひとつの小数
- 出力期待値のファイルにも小数の値が指定されている
- ただし、0.000001以下の誤差は許容する


```
const assert = require("chai").assert;
const codecheck = require("codecheck");

const language = process.env.LANGUAGE || "ja";
const appCommand = process.env.APP_COMMAND;
 
const settings = require("./settings.json");
settings.language = language;
const testcases = require("./testcases.json");
 
const testRunner = codecheck.testRunner(settings, appCommand); // ここまでは通常の場合と同じ

const eps = 0.000001; //許容誤差

async function verifyStdout(testcase, inputData, outputData) {
  const MSG = this.messageBuilder;
  const expected = this.calcExpected(testcase, inputData).tokens(); // 期待値の文字列をトークン化して配列として取得
  const users = outputData.tokens(); // ユーザーの出力トークン化して配列として

  // トークンの数が合わない場合はエラー
  if (expected.length !== users.length) {
    assert.fail(await MSG.invalidDataLength(testcase, inputData, outputData, expected.length, users.length));
  }
  for (let i=0; i<expected.length; i++) {
    // それぞれのトークンを数値化してその差が許容誤差内であるかをチェック
    const expected_token = Number(expected[i]);
    const user_token = Number(users[i]);
    if (Math.abs(expected_token - user_token) > eps) {
      // 誤差の許容範囲外の場合はエラー
      assert.fail(null, null, await MSG.unmatchToken(testcase, outputData, i + 1, expected_token, user_token));
    }
  }
}

testRunner.verifyStdout = verifyStdout; // メソッドの差し替え
testRunner.runAll(testcases); // TestRunnerの実行
```

注) 上記サンプルはsettings.jsonで`eps`をサポートしたことにより標準機能のみで実現できるようになりましたが、カスタマイズのサンプルとして掲載しています。
