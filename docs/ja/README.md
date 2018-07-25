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

### reloadボタン
contentsディレクトリを再スキャンします。
track.yml、book.ymlのあるディレクトリを追加した場合はこのボタンをクリックしてください。

### DevMode チェックボックス
コンテンツの表示を開発モード表示にします。
具体的には

- Challengeの場合
  - Hideで指定されたファイルを含めて表示します。
- Bookの場合
  - `${func:mark}`の行を表示します。

となります。

### Language セレクトボックス
CLIチャレンジの場合の言語選択に使用します。

### Download
track.yml(book.yml)を含むコンテンツ一式をzip化してダウンロードします。
(Quizの登録の際に使用します。)

## コンテンツの書き方

- [Challenge](how-to-make-challenge.md)
- [Quiz](how-to-make-quiz.md)
- [Book](how-to-make-book.md)
