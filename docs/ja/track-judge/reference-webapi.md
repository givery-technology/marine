## settings.json
webapiのテストを行う時は以下の設定が必要

- `"kind": "webapi"`
  - この場合デフォルトで読み込むテストケースファイルが`*testcases.json`ではなく`*testcases.yml`となる
- `output/source`の定義は有効。testcase定義の`expected/stdout`の値は`file`の場合はファイル名、`raw`の場合は直接記述と解釈される。(デフォルトは`file`)
  - yamlでのテストケース定義ではserverのgenerateで生成した値を使用することも可能
  - e.g. `stdout: "${state.answer}"`
- `compareType: "json"`を指定した場合はstdoutの比較方法がJSONとなる

## testcases.yml
web-api-test-libraryとほぼ同じだが、testcases.jsonの仕様に寄せて少し変えている。

テストケースの定義では後述するparamsによる置換が使用できる。

- endPoint: テスト対象APIのエンドポイント
- webServer: ローカルでWebServerを起動するための設定。testcases.jsonでの設定と同じ
- testcases: テストケースの配列。テストケース毎の設定は以下の通り
  - title: テストケースのタイトル。サブキーとして `ja`と`en`を分離して定義することもできる
  - exec: 受講者アプリ起動時のコマンドライン引数。
  - expected: テストケースの期待値
    - stdout: 標準出力の内容(file or raw)
    - code: 受講者アプリのexit_code。(省略時は0)
    - requests: 呼び出されるべきAPIリクエスト(正規表現可)の配列
      - 例えば `GET /api/kidnapper/start`と定義されている場合、このAPIが一度もコールされていなければエラーとなる
      - 後述するstatsの仕組みが必要
  - generate: サーバーサイドで準備用のAPIを呼び出す必要がある場合に使用
    - query: API呼び出し時のクエリパラメータ
      - コンテンツ開発者がサーバーサイドを実装する際に任意に定義できる
      - 以下のパラメータはあらかじめ定義されている(サーバー作成者が自分で定義する必要はない)
        - `state: "true"`: APIレスポンスにstateを含めるかどうか(実際のところ値はなんでも良い)
    - APIレスポンスにはセッションを管理するための`token`が含まれ置換文字列として使用可能
    - `state`が指定されている場合はサーバーサイド開発者が用意したstateも置換文字列として使用可能

stateを含めた場合のresponseは以下のようになる

```json
{
  "token": "xxx",
  "state": {
    "answer": "my answer"
  }
}
```

例えばapi-deliver-ransomではサーバーサイドで生成したrandom値が回答となるが、生成した回答をここに含めることで `stdout: "${state.answer}"`のようにそれを標準出力の期待値とすることができる

tokenはHTTPヘッダーの`X-ACCESS-TOKEN`に指定する。(後述の標準サーバーの仕様に乗っかる場合。自分でgenerate等を独自に実装する場合はこの限りではない)

### templateと文字列置換について
- テストケース定義にtemplateというキーがある場合はそこの定義は展開される。
  - 通常はyamlのアンカー(`&hoge`)とエイリアス(`*hoge`)を使用する
- テストケースで`params`を定義している場合、その値は文字列内で `${xxx}`のように参照することで置換される
  - `0`や`false`などはクォーテーションで囲ってください。`bool`に変換した値が`false`だと、エラーとなります。
- generateを定義している場合は`token`と`state.xxx`も置換文字列として使用可能
  - `${state.xxx}`のように参照できるのはstate直下のキーのみ。その下にさらにJSONオブジェクトがある場合はそれはJSON文字列として置換される。
  - 逆に言えば`state.answer`にJSONを差し込んで、それをそのまま `expected/stdout`に指定してJSON比較させることも可能

e.g. api-deliver-ransomから抜粋
```yaml
templates:
  default: &default
    generate:
      query:
        n: '${n}'
        state: "true"
    exec:
      args: ['${token}', '${n}']
    expected:
      stdout: '${state.answer}'
      requests:
        - "GET /api/kidnapper/start"
        - "GET /api/kidnapper/deliver"
  basic_case: &basic_case
    title:
      ja: '[基本実装] /start, /deliver の呼び出し数が ${n} の時、正答できる'
      en: '[Basic Case] Can solve when the number of /start and /deliver calls = ${n}'
    template: *default
testcases:
  - template: *basic_case
    params:
      n: "0"
  - template: *basic_case
    params:
      n: 3
```

## server
サーバーはNodeJSまたはpythonで動くものであれば実際のところはなんでも良い。
ただし、標準化を進めるためtrack-judge組み込みのServerを使ってそこに使用するAPIを組み込むことを強く推奨する。
(testdata/api-deliver-ransom, api-hotels参照)

registerメソッドで登録する個別のAPI定義に含めるべき内容は以下
- name: endpointのベースとなるstring
- generate: `_generate`関数の実装。(任意)
  - 引数はGETリクエストのクエリ
  - 返り値は任意のJSONでこれがstateとしてtoken毎に保存される
  - 指定されなかった場合もtokenのみを生成するgenerateエンドポイントは生成される
- endpoints: HTTPメソッド、パス、実行する関数の3要素の配列
  - 関数はreq, res, stateの3つの引数を取り、stateに加えた変更はtoken毎に保存される
  - 引数にstateが追加されている以外は通常のexpressでのendpointの実装の仕方と同じ
- rateLimit: APIのコール回数制限。(任意)
  - 指定された場合同一tokenでのコール回数がこの値を超えるとエラーとなる

サーバーサイドの実装は受講者に見せたくないのでchallengeに組み込む際には難読化する。(terser CLIで十分)

```sh
$ terser server/src/kidnapper.js --compress --mangle --output server/src/kidnapper.min.js
```
