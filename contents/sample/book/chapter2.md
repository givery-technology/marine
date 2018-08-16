# リモートセクションの作り方
このチャプターでは各種言語でのHelloWorldを題材にリモートセクション(バックエンドコンソールでプログラムを実行するセクション)の作り方を説明します。

##　Javascriptで「Hello World!」
JavaScriptで「Hello World」を出力してみましょう。

文字列を出力するには `console.log` を使用します。

リモートセクションの定義では`remote`セクションに実行するコマンドを指定します。

```
### remote
- command: node main.js
```

### main(main.js)

```
${console}.${log}("Hello World!");
```

### env

- imageName: givery/track-nodejs-8

### hint
JavaScript(Node.js)を使用するセクションを作成する際にはDockerイメージとして`givery/track-nodejs-8`を使用します。

このブックではセクション毎に使用する言語が異なるため各セクションで`env`を指定していますが、通常は1つのブックで扱う言語はひとつだけなので、book.ymlで指定します。

### remote
- command: node main.js

##　Rubyで「Hello World!」
Rubyで「Hello World!」を出力してみましょう。

文字列を出力するには `puts` を使用します。

```
### remote
- command: ruby main.rb
```

### main(main.rb)

```
${puts} "Hello World!"
```

### remote
- command: ruby main.rb

### hint
Rubyを使用するセクションを作成する際にはDockerイメージとして`givery/track-ruby-2.5`を使用します。


##　Pythonで「Hello World!」
Pythonで「Hello World!」を出力してみましょう。

文字列を出力するには `print` を使用します。

```
### remote
- command: python main.py
```

### main(main.py)

```
${print}("Hello World!")
```

### remote
- command: python main.py

### hint
Python(Ptyhon3)を使用するセクションを作成する際にはDockerイメージとして`givery/track-python-3.6`を使用します。

`givery/track-python-2.7`を使用してPython2系のブックを書くこともできます。

##　Javaで「Hello World!」
Javaで「Hello World!」を出力してみましょう。

文字列を出力するには `System.out.println` を使用します。

JavaではRubyやPythonなどのスクリプト言語と異なりコンパイルが必要です。
コンパイルなどの前処理は`build`に指定します。

```
### remote
- build: javac Main.java
- command: java Main
```

`build`は複数指定することができます。

### main(Main.java)

```
class Main {
  public static void main(String[] args) {
    ${System}.${out}.${println}("Hello world!");
  }
}
```

### hint
Javaを使用するセクションを作成する際にはDockerイメージとして`givery/track-java-8`を使用します。

### remote
- build: javac Main.java
- command: java Main

## シェルで「Hello World!」
シェルコマンドで「Hello World!」を出力してみましょう。

シェルから文字列を出力するには `echo` を使用します。

ユーザーに穴埋めさせたシェルコマンドを実行する場合は`main`のファイル名を`shell`とした上で、`remote`のコマンドとして`@main`を指定します。

```
### remote
- command: @main
```

### main(shell)

```
${echo} "Hello, World!"
```

### remote

- command: @main

### hint
シェルコマンドはどのDockerイメージでも動作しますが、ubuntuベースの`givery/track-python-3.6`を使用することをおすすめします。

### tips
ブックの各セクションではDockerコンテナは毎回初期化されます。
このため、セクション1でファイルを作成したとしてもセクション2ではそのファイルは見えません。

何らかの前処理をコマンド実行時に行いたい場合は`prepare`を定義します。

```
### remote
- prepare: mkdir test1
- prepare: mkdir test2
- command: @main
```

また、コマンド実行時に毎回カレントディレクトリを指定しているため、`cd`はできません。(正確に言えばDockerコンテナ内では正常にcdが実行されますが、次のコマンド実行時には元のディレクトリに戻っています。)

コマンド実行時のディレクトリを変更する場合は`cwd`を指定してください。

```
### remote
- prepare: mkdir test1
- cwd: /root/src/test1
```

`cwd`を指定しなかった場合のデフォルトのディレクトリは`/root/src`です。
