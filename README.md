# QUnit
## Qafir's C unit test framework

### How to use QUnit
#### Test file creation
To write a QUnit test file, you have to do the following:

 * Include the `qunit.h` header file
 * Write at least a test
 * Write a `main()` function to combine tests into cases and run the suite

You can refer to the `samples/` directory for example code.

#### Compilation
Compiling and running QUnit test units does not require any external library but the standard C runtime. An example compilation line could be: `gcc -o mytest.out mytest.c`

#### Reporters
To export the test results you have to use *reporters*. A reporter is a function to which test results are supplied for exporting as soon as a test function ends. At the moment QUnit supports two reporters:
  * Console reporter
  * Text file reporter

More reporters will be added.

### Bugs and feedback
Please report bugs through the [issue tracker](https://github.com/alkafir/qunit/issue).

Feel free to contact me at [my github profile page](http://alkafir.github.io). Any feedback is appreciated.
