## Solution
Concatenating the sequence \\(a\\) from the smallest element can be realized by the following steps:

- Sort \\(a\\)
- Convert each element into a string
- Concatenate them

## Computational Complexity
The sorting requires \\(O(n \log n)\\), and converting a single integer to a string requires \\(O(\log \max(a))\\), so the total computational complexity is \\(O(n (\log n + \log \max(a)))\\).

