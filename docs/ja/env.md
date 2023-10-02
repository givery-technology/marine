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
  - `python3`でも可能です。どちらも同じ `givery/track-cli-python3` のイメージが使用されます。
- python3
- ruby
- rust
- scala
- swift
- typescript
- sqlite
- postgres

これらのイメージは[DockerHub](https://hub.docker.com/u/givery)で公開されているイメージと次のようにマッピングされています。`cacheDirs`などを含んだマッピングではデフォルトでその設定が反映されます。例えば`java`イメージを使用する時、envConfに`cacheDirs`を記載しなくても、自動で`cacheDirs`に`/root/.m2`の設定が反映されます。

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

### イメージのバージョンについて
イメージは自動で最新に保たれます。envConfを逐一更新する必要はありません。

#### バージョンの依存について
バージョンに依存するライブラリを利用している場合はご相談ください。

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
