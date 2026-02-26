# 既存チャレンジのMigration方法
## Pattern1. テストケース定義の実行のみ
シンプルにsettings.jsonとtestcases.jsonの定義に従ってテストケースを実行するのみの場合、track.ymlのtest定義を変更するだけで動作します。
(webServer定義がある場合やexit_codeのハンドルが必要な場合は一部testcases.jsonを変更する必要があるものもあります。)

Before
```
test: mocha -R track-reporter
```

After
```
test: track-judge
```


この場合、テストはmochaで動くのではなくtrack-judge自体がCLIコマンドとして処理を行います。

これまではtestディレクトリにbasic_test.js/secret_test.jsなどのmocha上でテストを実行するためのjsファイルは不要になります。
残っていても動作に支障はありませんが、ノイズになるのでこれらのファイルは削除してください。
(特に調査目的でGREPをかける際にこれらが残っているとやりにくくなります。)

Marine上で試す場合は、コマンドエリアで

```
$ track-judge
```
を実行してください。(C++やJavaなどのbuildが必要な言語で動かす場合には先にbuildしておく必要があります。)
