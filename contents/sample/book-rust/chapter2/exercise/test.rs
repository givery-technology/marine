#[path = "main.rs"]
mod solution;

fn check(index: u32, name: &str, expected: &str) {
    let actual = solution::greet(name);

    if actual == expected {
        println!("ok {} - greet({:?}) が {:?} を返すこと", index, name, expected);
    } else {
        println!(
            "not ok {} - greet({:?}) が {:?} を返すこと (実際の値: {:?})",
            index, name, expected, actual
        );
    }
}

fn main() {
    check(1, "World", "Hello, World!");
    check(2, "Rust", "Hello, Rust!");
}
