Please read DEVNOTES.md for an explanation of the question-creation workflow and file structure.

A given number of integers, \\(n\\), are provided. Implement a function that returns a string concatenated from the integers in ascending order.

## Implementation Details

A function template is provided. Implement a function that takes the integer \\(n\\) and an array \\(a\\) as arguments, and returns a string `result` concatenated from the integers in ascending order.

The constraints are as follows:

- \\(2 \le n \le 10^5\\), integer
- \\(1 \le a_i \le 10^9 (1 \le i \le n) \\), integer

## Examples
### Example 1
Arguments

| n   | a          |
|-----|------------|
| 3   | [ 3, 1, 5 ]|

Return Value

| result |
|--------|
| "135"   |

When arranged in ascending order (1, 3, 5), concatenating them results in "135".

### Example 2
Arguments

| n   | a                  |
|-----|--------------------|
| 8   | [ 1, 43, 6, 2, 7, 83, 2, 6 ] |

Return Value

| result     |
|------------|
| "1226674383" |

Expected arguments and return values for some cases are defined in [test/basic_testcases.json](test/basic_testcases.json). Please refer to it when implementing.
