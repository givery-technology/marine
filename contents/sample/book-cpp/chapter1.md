# C++ Book

C++ ブックのテンプレートです。

## Hello World

画面に「Hello World」と出力するプログラムを作ってみましょう。

### main(main.cpp)

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
  std::${cout} << "Hello World" << std::endl;
  return 0;
}

```

### hint

標準出力に対する出力ストリームオブジェクトは `cout` です。

### tips

`cout` 関数は `std` 名前空間で定義されています。

### remote
- build: c++ -std=c++11 -o main *.cpp
- command: ./main

## 章末問題

### exercise
- mode: CLI
- reference: ./chapter1/exercise