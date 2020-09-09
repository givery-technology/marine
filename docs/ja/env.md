## envConfについて
envConfとはユーザが記述したコードを実際に実行する環境に関する情報です。

※ Bookでは`env`というキーで指定されますが設定内容は同じです。

## 設定項目
envConfには以下のキーが指定できます
  
- imageName: string. 必須
  - テストで使用するdockerイメージ名を指定します
  - imageNameで使用できるのは以下のdockerイメージです
- baseDir: string
  - ファイルコピーを行う基準ディレクトリのパスを指定します。
  - 省略時は`/root/src`になります。
  - 後述する`username`を指定する場合は省略することはできません。
- workingDir: string. 
  - コマンドを実行するディレクトリのパスを指定します。
  - 省略時はbaseDirになります。
- cacheDirs: Array<string>. 
  - Webエディタ実行中にテスト実行サーバでキャッシュするディレクトリを指定します。(Ruby, Javaのライブラリキャッシュ等)
  - Bookではコマンド実行毎に初期化されるのでcacheDirsは機能しません。
- variables: hash
  - コンテナのシェルに設定する環境変数を指定します。
- username: string.
  - コンテナで使用するユーザ名を指定します。
  - 指定のユーザはコンテナ内に予め存在する必要があります。
  - usernameを指定する場合は同時にbaseDirも指定する必要があります。

## イメージ一覧
使用可能なdockerイメージは以下です。  
これらのイメージは[DockerHub](https://hub.docker.com/u/givery/dashboard/)で公開されています。

すべてのdockerイメージにはclangとnodejsが含まれています。

- givery/track-base2
- givery/track-ruby-2.5
- givery/track-ruby-2.6
- givery/track-ruby-2.7
- givery/track-java-8
- givery/track-java-corretto-11.0
- givery/track-go-1.10
- givery/track-go-1.13
- givery/track-perl-5
- givery/track-python-2.7
- givery/track-python-3.6
- givery/track-python-3.8
- givery/track-php-7.2
- givery/track-php-7.4
- givery/track-scala-2.12
- givery/track-scala-2.13
- givery/track-nodejs-10
- givery/track-nodejs-12.13
- givery/track-nightmare-3.0
- givery/track-mono-5
- givery/track-cpp-googletest
- givery/track-sql
- givery/track-postgres
- givery/track-kotlin
- givery/track-swift-5
- givery/track-swift-5.1
- givery/track-dotnet-2.2
- givery/track-dotnet-3.0
- givery/track-java-corretto-11.0
- givery/track-rust-1.39
- givery/track-haskell-14.11
- givery/track-python3.7-anaconda

postgresのイメージを使用する際にはusernameとbaseDirに以下を指定してください。

```
  username: "postgres"
  baseDir: "/home/postgres"
```