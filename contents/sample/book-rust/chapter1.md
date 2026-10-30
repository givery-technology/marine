# Rust ブックの基本
Rust ブックのテンプレートです。

## Hello World
画面に「Hello World」と出力するプログラムを作ってみましょう。

### main(main.rs)

```rust
fn main() {
    ${println!}("Hello World");
}
```

### hint
標準出力に文字列を出力するには `println!` を使用します。

### tips
実行環境には `rust` イメージを使用します。`book.yml` で指定します。

```yml
env:
  imageName: rust
```

Rust はコンパイルが必要な言語なので、`remote` にはコンパイルコマンド(`build`)と実行コマンド(`command`)の両方を指定します。

```md
### remote
- build: rustc main.rs
- command: ./main
```

### remote
- build: rustc main.rs
- command: ./main


## コンパイルエラーを読ませる
Rust のコンパイラは親切なエラーを出すので、わざとコンパイルを失敗させて、それを読ませるセクションも作れます。

不変の変数に再代入するとどうなるか、確認してみましょう。

### main(main.rs)

```rust
fn main() {
    let age: u32 = 26;

    ${age} += 5;

    println!("{} years old.", age);
}
```

### hint
宣言されている変数は `age` だけです。

`cannot assign twice to immutable variable` というエラーと、`help: consider making this binding mutable` という修正方法が表示されます。
(エラーメッセージの文言は rustc のバージョンによって変わることがあります。)

### tips
`remote` の `exitCode` には、コマンドに期待する終了コードを指定します。省略時は `0`(成功)なので、失敗を期待するセクションでは明示的に指定します。

```md
### remote
- build: rustc main.rs
- command: ./main
- exitCode: 1
```

### remote
- build: rustc main.rs
- command: ./main
- exitCode: 1


## Cargo を使う
実際の Rust の開発では `rustc` を直接呼ばずに Cargo を使います。

穴埋めに `String` を埋めてみましょう。

### main(src/main.rs)

```rust
fn main() {
    let message = ${String}::from("Hello Cargo");
    println!("{}", message);
}
```

### files
- [Cargo.toml](chapter1/Cargo.toml)

### tips
`main` のファイル名にはパスを書けます。Cargo は `Cargo.toml` と `src/main.rs` という構成を前提にしているので、

```md
### main(src/main.rs)
```

と指定してそのまま配置しています。

`files` に指定したファイルはエディタ部にタブとして表示され、実行サーバーにもコピーされます。受講者に見せる必要のないファイルは、`files` ではなく `remote` の `file` で指定します。

```md
### files
- [Cargo.toml](chapter1/Cargo.toml)
```

外部クレートを使わないので、依存の取得を試みないように `--offline` を付けています。`--quiet` は `Compiling` などの進捗表示を抑制するオプションです。

```md
### remote
- build: cargo build --offline
- command: cargo run --offline --quiet
```

### remote
- build: cargo build --offline
- command: cargo run --offline --quiet
