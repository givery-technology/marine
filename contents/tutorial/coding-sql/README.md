在庫管理を目的としたデータベースがあります。この SQLite データベースに対して、各ステップで示された要求を満たす SQL を作成してください。このチャレンジで取り扱うテーブルは在庫情報を表す `inventories` テーブルのみです。

<details><summary>`inventories` テーブル（**クリックして展開**）</summary>

| カラム名 | 型 | 説明 |
| :- | :- | :- |
| `id` | integer | 在庫ID |
| `name` | varchar | 商品名 |
| `quantity` | integer | 在庫数 |

- `id` カラムがこのテーブルの主キーです。

</details>

### step1
在庫数の一覧情報を `inventories` テーブルから取得し、出力する単一の SQL クエリを [step1.sql](sql/step1.sql) に記載してください。
出力するカラムは以下の通りです。出力するカラムやレコードの順序は問いません。

| カラム名 | 説明 |
| :- | :- |
| `quantity` | 在庫数 |

### step2
在庫 ID が `2` の在庫数を \\(5\\) に変更する単一の SQL クエリを [step2.sql](sql/step2.sql) に記載してください。
