## envConfについて
envConfとはユーザが記述したコードを実際に実行する環境に関する情報です。

※ Bookでは`env`というキーで指定されますが設定内容は同じです。

## 設定項目(簡易)
通常、envConfで設定する必要のある項目はimageNameのみです。

例
```
envConf:
  imageName: nodejs
```

imageNameで使用できる値は以下です。

- cpp
- dart
- dotnet
- go
- haskell
- java
- kotlin
- nodejs
- perl
- php
- python
  - `python3`でも可。どちらを指定してもpython3系のイメージが使用されます。(python2系は非推奨となりました)
- ruby
- rust
- scala
- swift
- typescript
- sqlite
- postgres

言語ごとに環境が分かれていますが、環境にはclangとnodejsが含まれています。

この方式で指定した場合言語のバージョンが時代とともに変わっていくことに注意してください。
例えば`nodejs`のバージョンは2024年4月現在 v20.10.0ですが、次回の実行環境のUpdate時にはv22.xとなる見込みです。
(実行環境のUpdateは年に1〜2回の頻度で行われます。)

コンテンンツの内容によっては言語バージョンが上がると動かないものがでてくる可能性がありますが、オフィシャルコンテンツに関しては言語Updateがあった場合も動作する(言語Update時に合わせてコンテンツも改修する)ことが保証されます。

カスタムコンテンツについては都度ご相談となります。

## 設定項目(高度)
imageNameにdocker image名を指定することでさらに高度な指定を行うことができます。
その場合の設定項目は以下となります。

- imageName: string. 必須
  - テストで使用するdockerイメージ名を指定します
  - AI以外のコンテンツの場合、imageNameで使用できるのは実行環境にプリインストールされているイメージのみです。
  - AIの場合はdocker hubにある任意のイメージを指定することができます。
    - 自分で作成したdocker imageをpushしてそれを利用することができます。
- baseDir: string
  - ファイルコピーを行う基準ディレクトリのパスを指定します。
  - 省略時は`/root/src`になります。
  - 後述する`username`を指定する場合は省略することはできません。
- workingDir: string.
  - コマンドを実行するディレクトリのパスを指定します。
  - 省略時はbaseDirになります。
- cacheDirs: Array<string>.
  - Webエディタ実行中にテスト実行サーバでキャッシュするディレクトリを指定します。(Ruby, Javaのライブラリキャッシュ等)
  - BookではkeepSessionを有効にしない限りcacheDirsは機能しません。
- variables: hash
  - コンテナのシェルに設定する環境変数を指定します。
- username: string.
  - コンテナで使用するユーザ名を指定します。
  - 指定のユーザはコンテナ内に予め存在する必要があります。
  - usernameを指定する場合は同時にbaseDirも指定する必要があります。

## イメージ一覧
プリインストールされているイメージはgiveryの[DockerHub](https://hub.docker.com/repositories/givery)で公開されています。

imageNameで言語名のみを指定する場合に使用されるイメージは次のようにマッピングされています。
高度な設定を使えばコンテンツ側で同じ設定を行うことができますが、rubyなどのように言語バージョンによってライブラリのインストール先が変わる言語もあるので推奨されません。

<details><summary>イメージのマッピング(クリックして展開)</summary>

```yml
cpp:
  image: givery/track-cli-cpp
dart:
  image: givery/track-cli-dart
dotnet:
  image: givery/track-cli-dotnet
go:
  image: givery/track-cli-go
  workingDir: "/root/src/src/tracks.run/challenge"
  cacheDirs:
    - /go/pkg
haskell:
  image: givery/track-cli-haskell
java:
  image: givery/track-cli-java
  cacheDirs:
    - /root/.m2
kotlin:
  image: givery/track-cli-kotlin
  cacheDirs:
    - /root/.gradle
nodejs:
  image: givery/track-cli-nodejs
perl:
  image: givery/track-cli-perl
  cacheDirs:
    - /root/.cpanm
php:
  image: givery/track-cli-php
python:
  image: givery/track-cli-python3
  cacheDirs:
    - "/usr/local/lib/python3.11"
python3:
  image: givery/track-cli-python3
  cacheDirs:
    - "/usr/local/lib/python3.11"
ruby:
  image: givery/track-cli-ruby
  cacheDirs:
    - "/usr/local/bundle"
    - "/usr/local/lib/ruby/gems/3.2.0"
rust:
  image: givery/track-cli-rust
  cacheDirs:
    - "/root/.cargo/registry"
scala:
  image: givery/track-cli-scala
  cacheDirs:
    - "/root/.ivy2"
    - "/root/.sbt"
    - "/root/.cache"
swift:
  image: givery/track-cli-swift
typescript:
  image: givery/track-cli-typescript
sqlite:
  image: givery/track-sqlite
postgres:
  image: givery/track-postgres
  username: "postgres"
  baseDir: "/home/postgres"
  cacheDirs:
    - "/var/lib/postgresql/data"
```

</details>

### C#の注意事項
C#に使用するcsprojファイルの`PropertyGroup`には以下の設定を記載してください。バージョンが変わっても動作するようにするためです。
```xml
<DOTNET_FRAMEWORK_VERSION Condition=" '$(DOTNET_FRAMEWORK_VERSION)' == '' ">net6.0</DOTNET_FRAMEWORK_VERSION>
<OutputType>Exe</OutputType>
<TargetFramework>$(DOTNET_FRAMEWORK_VERSION)</TargetFramework>
<GenerateRuntimeConfigurationFiles>true</GenerateRuntimeConfigurationFiles>
<AppendTargetFrameworkToOutputPath>false</AppendTargetFrameworkToOutputPath>
<AppendRuntimeIdentifierToOutputPath>false</AppendRuntimeIdentifierToOutputPath>
```
