# validation-tool
validation-toolはコマンドラインから指定のディレクトリにあるチャレンジまたはブックの検証を行うツールです。

MarineのUI上で `Validate`ボタンをクリックした時と同等の検証を行います。

```
$ scripts/validation-tool algorithm/air-conditioner
```

引数として、検証対象のディレクトリを `contents`ディレクトリからの相対パスで指定します。


## validation-toolの検証内容
チャレンジでは以下の検証を行います。

- チャレンジのコンパイル
- OpenTestcaseのみでの実行
- SecretTestcaseを含む実行
- 定義済みsolutionの実行(複数言語でのsolutionがある場合は全言語で実行されます。)
- [オプション]英語チャレンジでファイルまたはコンソール出力に日本語が含まれていないかの検証

ブックの場合は、全ページに対して順次

- 穴埋めページの場合は正答コードの実行
- Exercise、またはSandboxページの場合はそのページのコードを実行

を行います。

※ ブックの検証はまだ完全ではないので、参考程度にとどめ厳密な検証はMarineのUIで行ってください。

## 標準入力での対象ディレクトリの指定
検証対象のディレクトリを引数で指定する代わりに標準入力で指定することもできます。

この場合、標準入力で複数のディレクトリが改行区切りで指定されていればすべてのディレクトリが順次検証されます。

また、scriptsディレクトリにあるlist-contents.jsは指定のディレクトリ以下のtrack.ymlまたはbook.ymlをリストアップしてくれるので組み合わせて指定ディレクトリ以下の全コンテンツを検証することも可能です。

```
$ node scripts/list-contents.js | scripts/validation-tool
```

## 処理の中断について
docker上で動かしているため、validation-tool.shはCTRL+Cでは止まりません。
処理を中断したい場合は `docker ps`でコンテナIDを調べて

```
$ docker rm -f <CONTAINER ID>
```

としてください。

## validation-toolのオプション
コマンドラインで指定できるオプションには以下があります。

- `--lang` または `-l`: チャレンジを検証する際の言語を指定します。指定可能な値は以下です。(Default: `auto`)
  - `ja`: 日本語版として検証します
  - `en`: 英語版として検証します
  - `auto`: README.mdに日本語が含まれている場合は `ja`、それ以外の場合は `en`として検証します。
  - `all`: README_ja.md または README_en.md が存在する場合は両方検証します。ない場合は `auto`と同様です。
- `--ja-check` または `-j`: 指定された場合、英語版検証の際にファイルまたはコンソールチェックに日本語が含まれているかをチェックします。

## Marine UIからのValidate
Marine UI上で `Validate`ボタンをクリックした場合の検証では現在表示中の言語が`lang`として使用されます。

(言語は右上のMenuから切り替えられます。)

英語版の検証の際には日本語チェックも行われます。