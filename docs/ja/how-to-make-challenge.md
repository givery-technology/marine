# track Challengeの作り方
## 概要
Challengeとはユーザに実際にプログラムコードを書かせてその実行結果をユニットテストで検証するタイプのプログラミング問題のことを指します。
チャレンジは大きくは言語非依存のCLIチャレンジと特定言語向けのプログラミング問題となる言語依存チャレンジの2種類に別れます。

言語依存チャレンジの方が作成は簡単ですが、オフィシャル問題の多くは汎用性の観点からCLIチャレンジとなっています。

## CLIチャレンジと通常チャレンジ
CLIチャレンジではユーザが作成するプログラムはCLIアプリケーションになります。
すなわち、

- 引数、または標準入力から何かしらの入力パラメータを受け取り、
- 標準出力に何かを出力する

というアプリケーションです。言語はなんであっても構いません。(実際には後述するDockerImageで対応している必要があります。)

言語依存チャレンジは予め用意されたソースコードの一部をユーザに埋めさせるようなチャレンジです。
典型的な例は以下のようになります。

``` java
public class FizzBuzz {
  public String execute(int n) {
    // ここにFizzBuzzのコードを実装してください
  }
}
```

## テストの枠組み
trackのテストは基本的にUnitテストとして行われます。
一番外側の枠組みとしてはUnitテストに使用するフレームワークは[TAP](https://testanything.org/)に対応しているものであれば何でも使うことができます。(実際にはDockerImageにそのテストフレームワークがインストールされている必要があります。)

TAPとは簡単に言えば、

- Unitテストが成功の場合は「ok x ....」というフォーマットで行を出力
- Unitテストが失敗の場合は「not ok x ....」というフォーマットで行を出力

するテストフォーマットです。

CLIチャレンジの場合はJavaScriptのテストフレームワークである[mocha](https://mochajs.org/)を使用してテストを記述します。


## track.yml
  challengeType: ChallengeType,
  editable: List[String] = Nil,
  readonly: List[String] = Nil,
  hide: List[String] = Nil,
  testExclude: List[String] = Nil,
  images: List[String] = Nil,
  test: Option[String] = None,
  allowNewFile: Boolean = false,
  build: List[String] = Nil,
  mainFile: Option[String] = None,
  languages: List[String] = Nil,
  envConfig: Option[EnvSettings] = None,
  variables: Map[String, String] = Map.empty,
  testcases: Option[Testcases] = None,
  templateType: Option[CLITemplateType] = None,
  initialize: List[String] = Nil

## README
## openTestとsecretTest
openTestとはテストコード、テストケースともにユーザに可視となっているテストです。
それに対してsecretTestはユーザの目に触れることはできません。

track.ymlで言えば

- readonlyに指定されたテスト -> openTest
- hideに指定されたテスト -> secretTest

という対応になります。

典型的な使い方としては

- 簡単で基本的なテストはopenTestで
- 複雑、あるいはエッジケースはsecretTestで

定義します。

ユーザは受験の際にはopenTestを繰り返し実行します。  
そしてすべてのopenTestにパスしたら満点だと思って提出することでしょう。  
しかし、実際には隠されたsecretTestによって部分点しか取れていないということもありえます。  
(ユーザはsecreTestの存在を知ることはできません。)

openTest、secretTest共に必須ではなく、openTestのみでsecretTestなしというチャレンジは作成することができますが、openTest, secretTestいずれもなし、というチャレンジは作成することができません。


実行されるopenTest, secretTestの数はtrack.ymlの`testcases`に定義する必要があります。
ここで定義された数字と実際に実行されたテストケース数が異なる場合はtrack上で警告となります。

## answer.mdとsolution.md

## testについて

## BEGIN_CHALLENGEとEND_CHALLENGE

## cli-templates
## DockerImages
## codecheck CLI
## 無限ループと大量アウトプット対策
