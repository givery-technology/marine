# エクササイズ
穴埋めではなく、受講者に自分でコードを書かせるセクションも作れます。


## 章末問題
`greet` 関数を実装してください。

引数で受け取った名前を使って `Hello, <名前>!` という文字列を返します。

```
greet("World") // -> "Hello, World!"
greet("Rust")  // -> "Hello, Rust!"
```

### exercise
- mode: remote
- name: greet
- file: [main.rs](chapter2/exercise/main.rs)
- hidden: [test.rs](chapter2/exercise/test.rs)
- build: rustc -A unused test.rs -o test
- command: ./test

### hint
フォーマットした文字列を `String` として組み立てるには `format!` マクロを使用します。

### answer

```rust
pub fn greet(name: &str) -> String {
    format!("Hello, {}!", name)
}
```

`println!` が標準出力に書き出すのに対して、`format!` は同じ書式で組み立てた `String` を返します。

### tips
エクササイズは、テストの出力が TAP 形式になっていることを前提に判定されます。コンパイルエラー・実行時エラーが無く、`ok ` で始まる行が1つ以上あり、`not ok ` で始まる行が無いときに正解となります。`cargo test` の出力は TAP 形式ではないので、このブックでは `test.rs` が `ok` / `not ok` を自力で出力しています。

```rust
if actual == expected {
    println!("ok {} - greet({:?}) が {:?} を返すこと", index, name, expected);
} else {
    println!(
        "not ok {} - greet({:?}) が {:?} を返すこと (実際の値: {:?})",
        index, name, expected, actual
    );
}
```


`hidden` に指定したファイルは受講者には見せずに実行サーバーへコピーされます。未実装の状態では使われない引数などの警告が出るので、`rustc` には `-A unused` を付けています。

```md
### exercise
- mode: remote
- name: greet
- file: [main.rs](chapter2/exercise/main.rs)
- hidden: [test.rs](chapter2/exercise/test.rs)
- build: rustc -A unused test.rs -o test
- command: ./test
```

解答例と解説は `answer` に書きます。


```md
### answer
```

