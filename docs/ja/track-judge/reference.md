# 設定ファイル仕様
## settings.json
[Settings.ts](../src/model/Settings.ts)

settings.jsonで使用できるキーは以下の通りです。

- input: 入力データを定義するObject. サブキーとして以下があります。省略時は`type=arguments,source=file`となります。
  - type: 入力データの渡し方。設定可能な値は以下
    - `stdin`: 入力内容はCLIアプリケーションの標準入力に渡されます。
    - `arguments`: 入力内容はCLIアプリケーションの引数として渡されます。入力内容に空白文字がある場合はそこで分割されて複数の引数として渡されます。
    - `single_arguments`: 入力内容はCLIアプリケーションの引数として渡されます。入力内容に空白文字がある場合、空白文字を含む単一の引数として渡されます。
    - `file`: **Deprecated** CLIアプリケーションの引数にファイル名が渡されます。
  - source: 入力データのソース。設定可能な値は以下
    - `raw`: testcase定義のinputで指定した内容がそのまま入力データとなります。
    - `file`: testcase定義のinputで入力データのファイル名を指定します。
- output: 出力データを定義するObject. サブキーとして以下があります。省略時は`type=stdout,source=file,filename=answer.txt`となります。
  - type: 入力データの渡し方。設定可能な値は以下
    - `stdout`: 受講者は標準出力に結果を出力します。
    - `file`: **Deprecated** 受講者がCLIアプリケーション内で自分で指定のファイルを作成します。
  - source: 出力の期待値データのソース。設定可能な値は以下
    - `raw`: testcase定義のoutputで指定した内容がそのまま出力の期待値データとなります。
    - `file`: testcase定義のoutputで出力の期待値データのファイル名を指定します。
  - filename: **Deprecated** 出力データのファイル名。`type: stdout`の場合も標準出力は一旦このファイルにリダイレクトされます。
- compareType: 出力データの比較方法を指定します。設定可能な値は以下。省略時は`token`となります。
  - `token`: 出力データを空白文字区切りのトークン単位で比較します。
  - `json`: 出力データをJSONとしてパースしてから比較します。
- judge: カスタムjudgeを使用する際のjudgeを定義するObject.
  - command: カスタムjudgeを起動するためのコマンド
  - type: **Deprecated** judgeのタイプ。`default`と`aoj`が指定できますが`aoj`はAOJのチャレンジ以外では使用しないので通常は指定する必要はありません。
- eps: 数値のトークンを比較する際の許容誤差を指定します。省略時は完全一致となります。
- timeout: テストケースのタイムアウト時間をms単位で指定します。省略時は`6000`となります。
- tleFactorEnabled: boolean。trueの場合TLE_FACTORを有効にします。(TLE_FACTORは言語によってtimeout値を調整するための係数です。TLE_FACTORは環境変数で指定します。)
- tleFactorExpr: string。TLE_FACTORを計算するための式。
  - `t`(timeoutの値)、`f`(TLE_FACTORの値)の二つの変数を使用してTLE_FACTORの適用式を指定します。
  - 式内で使える文字は `t`, `f`, 数値 `.`, `+`, `-`, `*`, `/`, `(`, `)` のみです。
  - ex. `f * 50 + t`
  - 省略時のデフォルト値は`f * t`です。
- language: テストケース名、エラーメッセージの言語。`en`または`ja`。省略時は環境変数`CHALLENGE_LANGUAGE`の値が使用され、それもない場合は`ja`となります。
- baseDirectory: 設定ファイル内でファイル名を指定する場合の基準ディレクトリ。省略時は`test`になります。
- testcases: テストケース定義ファイル名の配列。ワイルドカードが使えます。省略時は`["testcases.json", "*_testcases.json"]`となります。

## テストケース定義ファイル
[TestcaseDefinition.ts](../src/model/TestcaseDefinition.ts)
[Testcase.ts](../src/model/Testcase.ts)

テストケース定義ファイルはJSONのトップレベルがObjectのパターンと配列のパターンの両方を許容しています。
トップレベルが配列の場合、それはObjectでtestcasesとして定義されているのと同義になります。

トップレベルがObjectの場合に使用できるキーは以下です。

- testcases: テストケースの配列。テストケース定義は後述。
- webServer: テストケースの実行時にローカルでWebServerを起動して実行する場合に指定。サブキーとして以下があります。
  - command: WebServerの起動コマンド。webServerを定義する場合は必須
  - health: URL。指定した場合WebServer起動後にこのURLにアクセスして200が帰るまで待機する。省略可
  - forEach: boolean。trueにした場合、WebServerの起動/停止がテストケース毎に行われます。省略可

テストケース定義のキーは以下

- input: 入力データの定義。settings.json/input/sourceが`file`の場合はファイル名。`raw`の場合は入力値そのもの。
- output: 出力期待値データの定義。settings.json/output/sourceが`file`の場合はファイル名。`raw`の場合は入力値そのもの。
- description: テストケースのタイトル
  - description_ja, またはdescription_enが定義されている場合は、settings.json/languageの値に応じてそちらの内容が使用されます。
- exit_code: 受講者の作成するCLIアプリケーションに期待されるexit_code。省略時は0。負数が指定された場合は0以外という意味になる。

またtestcaseには上記以外の値も指定でき、それらはTestcaseクラスの `option(key: string): string`メソッドで取得できます。

## カスタムjudgeの作成方法
カスタムjudgeはtrackのすべての言語イメージで使用可能な言語(C/C++/NodeJS/Python3)を使って作成することができます。
(C/C++で作成する場合はtrack.ymlのinitializeでbuildしてください。)

カスタムJudgeのコマンドライン引数は以下の3つです。

1. テストケースの入力ファイル名
2. テストケースの期待値データのファイル名。または"null".(テストケースでoutputが定義されていない場合は"null"という文字列が第2引数となります。)
3. 受講者の出力を保存したファイル名

judgeの結果。テストにパスしているのであればexit_code=0でJudgeアプリケーションを終了してください。
テストにパスしていない場合は標準エラー出力にエラーメッセージを出力し、exit_code=2〜125の範囲で終了してください。(exit_code=1, あるいは126以上の場合はJudgeアプリケーション自体の異常終了と判定されます。)

## track-judgeコマンドのオプション
- `--version`: track-judgeのバージョンを表示して終了します。
- `--only [N]`: N番目のテストケースのみを実行します。
- `--from [N]`: N番目のテストケース以降を実行します。
- `--verbose`: 対象アプリケーションの標準出力をそのまま出力します。
- `--command`: 対象アプリケーションの実行コマンドを指定します。
  - `APP_COMMAND="node solution.js" track-judge`と`track-judge --command "node solution.js"`は同じです。(`--command`オプションは環境変数より優先されます。)