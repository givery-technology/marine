# Javaに特化したコーディング問題の作成 (JUnit版)
JUnitを使用して、Javaのユニットテスト問題を作成するサンプルです。
簡単なユニットテストで十分な場合は、高速に採点できる軽量版の利用を検討してください。

問題の題材はFizzBuzzです。

## 問題作成のポイント
### build.gradle
このサンプルではTestRunnerとしてGradleを使用しています。
[build.gradle](build.gradle)はテストの実行結果を[TAP](https://testanything.org/)形式で出力するようにカスタマイズされています。

Java問題を作成する際にはこのbuild.gradleをそのままコピーして使用してください。

### src/main以下
ここではpackage名として`track`を使用していますが、package名には任意の名前を使用することができます。
この問題では1ファイルのみが編集可能ファイルとして配置されていますが、複数のパッケージにまたがって複数のファイルを配置しても問題ありません。

また、ファイルをtrack.ymlの`editable`ではなく、`readonly`で定義することで受験者が編集できないファイルを配置することも可能です。

ファイル中に`BEGIN_CHALLENGE` 〜 `END_CHALLENGE`で括られた範囲がある場合、その部分は受験者には表示されません。
ただし、MarineのDevModeでは表示されるので、作成したユニットテストの検証に利用してください。

### src/test以下
JUnitを利用したごく普通のユニットテストです。
特に特別なルールは無いのでJUnitを使用したことがある人ならば問題なく理解できると思います。

### track.yml
`envConf`では以下の内容をそのまま使用してください。

```
envConf:
  imageName: java
  cacheDirs:
    - /root/.m2
    - /root/.gradle
```

Java8のDockerイメージを使用し、mavenとgradleのキャッシュディレクトリをキャッシュするように指定しています。

また、`test`に使用するコマンドも基本的には次のコマンドを使用すれば良いので特に変更する必要はありません。

```
test: gradle cleanTest test -q
```
