# Markdownの作り方
## 概要
MarkdownスタイルはZenn Book形式を採用したコンテンツスタイルです。
この文書ではMarkdownコンテンツを構成する各種ファイルの詳細について説明します。

Markdownスタイルは主にドキュメンテーションや読み物形式の教材作成に適しています。
Bookスタイルと異なり、穴埋め問題やエクササイズを含まない純粋なマークダウンコンテンツに最適化されています。

## 作成から公開までのワークフロー
Markdownコンテンツの作成から公開までの基本的な流れは以下の通りです。

1. **コンテンツの作成**: `contents`ディレクトリ以下に`config.yaml`とチャプターファイル（`.md`）を手動で作成します。
2. **Marineでプレビュー**: Marineを起動し、作成したコンテンツを選択してプレビューで表示を確認します。
3. **Zip Download**: Marineのヘッダにある「Download」ボタンからコンテンツ一式をzipファイルとしてダウンロードします。
4. **TCMへアップロード**: ダウンロードしたzipファイルをTCM（Track Contents Manager）にアップロードします。
   - **新規作成**: 「Add Material」からzipファイルをアップロードします。スタイルは`config.yaml`の存在により自動的にMarkdownと判定されます。
   - **バージョンアップ**: 既存のマテリアルに対して新しいzipファイルをアップロードすることでバージョンアップできます。

## 最小限のMarkdown
説明に先立ってまず最小限のMarkdownの例を示します。

以下は

- config.yaml
- 1.intro.md

の２ファイルからなる、1チャプターのMarkdownの例です。

`contents`ディレクトリの下に以下のようなディレクトリ構造を作成してください。

```
contents/
  └── my-markdown/
      ├── config.yaml
      ├── 1.intro.md
      └── images/
          └── intro/
              └── img_01.png
```

config.yaml
```yaml
title: "はじめてのMarkdown"
summary: "Markdownコンテンツのサンプルです。"
topics: ["tutorial", "sample"]
toc_depth: 2
```

1.intro.md
```markdown
---
title: "イントロダクション"
---

# はじめに
これはMarkdownコンテンツのサンプルです。

## このコンテンツについて
Markdownで自由に文章を記述できます。

### 特徴
- シンプルな構成
- 目次の自動生成
- Zenn形式との互換性
```

この２ファイルをMarineを通して見ると、目次付きのマークダウンページが表示されます。

以下それぞれのファイルについて説明していきます。

## config.yaml
config.yamlはMarkdownコンテンツ全体の定義が記述されたファイルです。

以下のキーを含みます。

- title: String, 必須
- summary: String, 必須
- topics: List[String], 任意
- chapters: List[String], 任意
- toc_depth: Int, 任意

config.yamlの構成は原則Zenn Bookと同じです。
Zenn Book用に作成したコンテンツはそのままtrackに登録することができます。

### title
titleにはコンテンツのタイトルを指定します。

```yaml
title: "RAG入門ガイド"
```

### summary
summaryにはコンテンツの概要説明を指定します。

```yaml
summary: "RAGの基礎から実践までを学ぶガイドです。"
```

### topics
topicsにはコンテンツに関連するタグを指定します。

```yaml
topics: ["RAG", "LangChain", "AI", "Python"]
```

### chapters
chaptersには各チャプターの定義ファイルを指定します。
拡張子`.md`は省略して指定します。

```yaml
chapters:
  - 1.intro
  - 2.basics
  - 3.advanced
```

**注意**: 拡張子`.md`を付けて指定すると、コンパイラが自動的に`.md`を付与するため`1.intro.md.md`のようなファイル名として解釈され、コンパイルエラーとなります。必ず拡張子を省略してください。

chaptersを省略した場合、ディレクトリ内の`.md`ファイルがファイル名順に自動的に検出されます。

自動検出のファイル名規則：
- `{番号}.{名前}.md` 形式（例: `1.intro.md`, `2.basics.md`）
- 番号の昇順にソートされます

### toc_depth
toc_depthには目次（Table of Contents）に表示する見出しの深さを指定します。
省略時のデフォルト値は`2`です。

```yaml
toc_depth: 2
```

toc_depthは各チャプター内の**最小の見出しレベルからの相対値**として動作します。
例えば、チャプター内の見出しが`##`から始まる場合：

- `1`: `##`のみ
- `2`: `##`, `###`まで
- `3`: `##`, `###`, `####`まで

見出しが`#`から始まる場合は：

- `1`: `#`のみ
- `2`: `#`, `##`まで
- `3`: `#`, `##`, `###`まで

Zenn Bookのconfig.yamlにはその他のキーも存在しますが無視されます。

## チャプター定義ファイル
各チャプターは個別のマークダウンファイルとして定義します。

### frontmatter
ファイルの先頭にYAML形式のfrontmatterを記述してチャプターのタイトルを指定します。

```markdown
---
title: "チャプターのタイトル"
---
```

frontmatterは必ず`---`で囲む必要があります。
**注意**: frontmatterでサポートされているキーは`title`のみです。他のキーを記述しても無視されます。

### 本文
frontmatterの後に通常のマークダウン記法で本文を記述します。

```markdown
---
title: "RAGとは何か"
---

# RAGの概要
RAGとは、Retrieval-Augmented Generationの略で...

## RAGのメリット
1. 最新情報を取得できる
2. 社内の専門知識を取得できる

## RAGのデメリット
- 検索時間がかかる
- 検索精度に依存する
```

### 使用可能なマークダウン記法
通常のマークダウン記法に加えて、以下の拡張記法が使用可能です。

#### 画像
```markdown
![画像の説明](images/intro/img_01.png)
```

画像にCSSスタイルを指定したい場合はtitle属性を使用します。
```markdown
![画像の説明](images/intro/img_01.png "width:300px;")
```

#### コードブロック
````markdown
```python
def hello():
    print("Hello, World!")
```
````

言語指定には以下の特殊な値も使用できます。
- `plain`: シンタックスハイライトを無効にします
- `math`: KaTeX数式として表示します

#### 数式（KaTeX）
インラインの数式は`$...$`で、ブロック数式は`$$...$$`で記述します。
コードブロック内で数式を表示する場合は言語に`math`を指定します。

````markdown
```math
E = mc^2
```
````

#### アコーディオン（折りたたみ）/ リンクカード / メッセージ
Zenn独自の記法（`:::details`, `:::message`, リンクカードなど）は、Marine/Trackでは現在**サポートされていません**。
記述しても正しくレンダリングされないため、使用しないでください。

数式以外の拡張マークダウン記法の詳細については、[markdown-extension.md](markdown-extension.md)を参照してください。

## 画像の使い方
マークダウンで画像を使用する場合は、`images/`ディレクトリを作成し、そこへ画像を配置して参照します。

### 画像ディレクトリの配置と参照
コンテンツルート直下に`images/`ディレクトリを作成することを推奨します。

**ディレクトリ構成例**:
```
contents/
  └── my-markdown/
      ├── config.yaml
      ├── 1.intro.md
      └── images/
          ├── img_01.png
          └── img_02.png
```

**参照方法**:
```markdown
![画像の説明](images/img_01.png)
```

### Zenn互換モード
Zennからの移行コンテンツなど、`books/`ディレクトリを使用した階層構造の場合、コンパイラは`../../images`（2階層上）をフォールバックとして検索します。
新規に作成する場合は、上記の推奨構成（フラット構造）を使用してください。

## ディレクトリ構成
推奨されるディレクトリ構成を示します。

### 基本構成
```
contents/
  └── {content-name}/
      ├── config.yaml
      ├── 1.chapter1.md
      ├── 2.chapter2.md
      └── 3.chapter3.md
```

### 画像を含む構成
```
contents/
  └── {content-name}/
      ├── config.yaml
      ├── 1.intro.md
      ├── 2.basics.md
      └── images/
          ├── intro/
          │   └── img_01.png
          └── basics/
              └── img_01.png
```

## Bookスタイルとの違い

| 項目 | Markdown | Book |
|------|----------|------|
| 設定ファイル | config.yaml | book.yml |
| チャプター指定 | 省略可（自動検出） | 必須 |
| frontmatter | 使用する | 使用しない |
| セクション | なし | あり |
| 穴埋め問題 | なし | あり |
| 画像パス | `images/`から参照（相対パス） | imagesキーで指定 |
| 目次 | 自動生成 | なし |

Markdownスタイルは読み物コンテンツに、Bookスタイルはインタラクティブな学習コンテンツにそれぞれ適しています。

