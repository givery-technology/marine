There are many abbreviations in the world.
For example, `PC` stands for `Personal Computer` and `NHK` stands for `Nippon Hoso Kyokai`.

There are several methods for abbreviating a word. The most common method is taking the first character of each string and concatenating them.
The above examples are abbreviated using this method.
Your task is to abbreviate a variety of words using this method.

## Implementation details

Implement a function that receives arguments \\(s_1\\), \\(s_2\\), and \\(s_3\\), and returns the string `result`.
Please store `result` as the first characters of the \\(3\\) strings without any spaces between the characters.

The conditions are as follows:
- \\(1 \le\\) the length of string \\(s_i\\) \\(\le 20\ (1 \le i \le 3)\\)
- Each string consists of letters only

## I/O examples
### Example 1
Arguments

| \\(s_1\\) | \\(s_2\\) | \\(s_3\\) |
|----------|----------|----------|
| "Nippon"  | "Hoso"    | "Kyokai"  |

Return Value

| result |
|--------|
| "NHK" |

The first characters of the strings are `N`, `H`, and `K`.
After concatenating these characters, the abbreviation is `NHK`.

### Example 2
Arguments

| \\(s_1\\) | \\(s_2\\) | \\(s_3\\) |
|----------|----------|----------|
| "for"  | "your"    | "infomation"  |

Return Value

| result |
|--------|
| "fyi" |

Note that the expected arguments and return value are defined in [test/basic_testcases.json](test/basic_testcases.json).
Please refer to this file for implementation.
