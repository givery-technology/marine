# Marineとは
Marineはtrackのコンテンツを作成しながらその動作をリアルタイムで確認できるツールです。

## 基本的な使い方
画面上部のセレクトボックス部分に`contents`ディレクトリ以下で、

- track.yml
- book.yml

の存在するディレクトリが列挙されます。
どれかを選択すると画面下部のワークスペースにそのコンテンツが表示されます。

ワークスペース上の表示はtrackでの表示と同じです。
track上で操作するのと同じようにテストの実行や穴埋めなどが実行できます。

ディレクトリ内のファイルを変更した場合はリロードすることによって変更内容が画面に反映されます。

## ヘッダ部の構成
### Contents セレクトボックス
contentsディレクトリ以下のtrack.yml, book.ymlのあるディレクトリがリストアップされます。
選択することによりワークスペースが切り替わります。

### Language セレクトボックス(cli/function challengeの場合のみ)
CLI/Functionチャレンジの場合の言語選択に使用します。

### solution セレクトボックス(challengeの場合のみ)
表示する解答例の選択に使用します

### validate ボタン(challenge/bookの場合のみ)
contentsがtrackに登録可能な状態であるかを検証します。

### Menu
- relaod content list
  - contentsディレクトリを再スキャンします。
  - track.yml、book.ymlのあるディレクトリを追加した場合はこのボタンをクリックしてください。
- Download
  - track.yml(book.yml)を含むコンテンツ一式をzip化してダウンロードします。
  - TCMでのコンテンツ登録の際に使用します
- DevMode
  - コンテンツの表示を開発モード表示にします。
  - 開発モードでどのように表示が変わるかは各コンテンツの開発者ガイドをご確認ください
- Orca Information
  - 接続先の実行環境を切り替えます。
  - 言語バージョンUpdateの際に新しい言語での動作を検証する場合などに使用します。
- Selected Language
  - READMEやテストケースの日英切り替えで使用します。

## コンテンツの書き方

- [Challenge](how-to-make-challenge.md)
- [Quiz](how-to-make-quiz.md)
- [Book](how-to-make-book.md)
- [AI](how-to-make-ai.md)
- [App](how-to-make-app.md)
