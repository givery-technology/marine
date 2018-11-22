## The mission

There is an arbitrary [string]. Please implement a function that should return the following,

```
"Hello [string]!"
```

For example, it should return `"Hello World!"` when the input is `"World"`,
and should return `"Hello track!"`  when the input is `"track"`.

## Implementation

### CLI
Implement a command line application that accepts `input.in` file and output the results to stdout.
For details, see the "Command line application template" section at the bottom of the page.

### Input Rules
Your CLI program should accept an input file: `input.in`

The `input.in` file's format is as below:
```text
[string]
```

### Output Rules
Your CLI program should return an output as stdout.

The output's format is as below:
```text
Hello [string]!
```

## Input & Output samples
### Sample 1
```shell
$ ./myApp World
```

stdout

```
Hello World!
```

### Sample 2

```shell
$ ./myApp track
```

stdout

```
Hello track!
```

There are other input & output samples defined in this file: [test/basic_testcases.json](test/basic_testcases.json)
You can use it as a reference while working on this exercise.
