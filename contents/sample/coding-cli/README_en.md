## The mission
There are \\(n\\) unsorted integers.
Please devise a program to solve the following:
- find the minimum and the maximum integer from the \\(n\\) integers given
- sort the given integers in an incremental order and display it as a concatenated string. 

## Implementation

### CLI
Implement a command line application that receives standard input and writes the answer to its standard output.
For details, see the "Command line application template" section at the bottom of the page.

### Input Rules
Your CLI program should receive standard input.

The standard input's format is as below:
```text
n
a[1] a[2] ... a[n]
```

Restrictions:
- \\(2 \le n \le 10^5\\), Integer
- \\(1 \le a_i \le 10^9 (1 \le i \le n) \\), Integer

### Output Rules
Your CLI program should write the answer to its standard output.

The standard output's format is as below:
```text
min max
s
```

- On the \\(1\\)st line, print the minimum and the maximum integer of the given integers, separated by a space.
- On the \\(2\\)nd line, sort the given integers in an incremental order and print it as a concatenated string.

## Input & Output samples
### Sample 1
Sample Input 1 (`00_sample1.in`)
```
3
3 1 5
```
Sample Output 1
```
1 5
135
```
The minimum integer of \\(3, 1, 5\\) is \\(1\\), and the maximum integer is \\(5\\). The incremental sorted order is \\((1, 3, 5)\\), so the concatenated string is \\(135\\).

### Sample 2

```shell
Sample Input 2 (`00_sample2.in`)
```
8
1 43 6 2 7 83 2 6
```
Sample Output 2
```
1 83
1226674383
```

There are other input & output samples defined in this file: [test/basic_testcases.json](test/basic_testcases.json)
You can use it as a reference while working on this exercise.
