# Connect 4 in C

This assignment was originally prepared by Prof. Nandigam.

Use this [GitHub Classroom link](https://classroom.github.com/a/mC2Nf2pv) to create a repo for this project.

This video provides an [introduction to Connect 4 and GitHub Classroom](https://youtu.be/nv1R7XPNneM).

## Overview

For this assignment you will implement the game [Connect 4](https://kevinshannon.dev/connect4) in C. 

You will be adding two additional features:
1. The size of the board will be configurable.
2. The run length needed to win will be configurable.  (So, I guess the game is really "Connect X").

I placed a sample solution on EOS at `/home/kurmasz/public/CIS343/c4demo`.  Your board and workflow need not be identical to mine.  However, I will be using automated "system tests", so your input and output needs to formatted carefully.  In addition, your implementation **must** follow a handful of rules, so **_Be sure to read the Details section below_**!

## Objectives

This assignment has two main objectives
1. Review C
2. Serve as a baseline to which you can compare other languages

In particular, think about the following as you write your code:
1. In what ways does C's static typing make the code more difficult and or verbose than necessary?
2. What features could be added to C to make it easier to reuse code (i.e., better apply the DRY principle)?

## Details

### Interface

When implementing your game, you must use this interface (so I can run automated tests on it):
1. The command line must take two optional parameters:
   1. board size in the form `rowsxcolumns` (e.g., `6x7`)
   2. the number of checkers in a row needed to win (i.e, the _win length_)
   (For example `./c4 9x13 6` will launch a game with 9 rows, 13 columns, and a win length of 6.)
2. If the user doesn't supply one or more optional parameters, the default board size is 6x7 and the default win length is 4.
3. When a player wins, print the message <code>Congratulations, Player <em>x</em>. You win.</code> then exit.
   This message must be the last message printed to the standard output.  Capitalization and spaces are important.
4. The columns will be labeled with letters beginning with `A`.  To make a move, each player enters the letter of the desired column and hits enter.  Your program should accept both upper- and lower-case entries.
5. Given an invalid input (not a letter, letter too large, column is full, etc.), simply print an error message and prompt the user again.  The message need not have a specific format.
6. If the user enters `q`, immediately print `Goodbye.` and terminate the program.  `Goodbye.` must be the final thing printed on the standard output.

### Implementation requirements

**!!! Important #1 !!!**  You may only have one function / block of code that detects "x in a row". The fundamental component of your `winner` function is detecting a streak of _x_ tokens in a row. In order to explore how different programming languages support and/or hinder good software design, we are going to pretend that this "x in a row" algorithm is sufficiently long and complex that it can't (or, rather, shouldn't) be re-implemented in different contexts.  In other words, **don't re-implement this "x in a row" algorithm separately for rows, columns, and diagonals**.  Instead, find a way to call a common helper function.  Off the top of my head, I can think of two approaches:  
   1. Copy a row, column, or diagonal into a separate array.  This is computationally inefficient; but, that's ok for this assignment because we are focusing on the interaction of programming languages and software design.
   2. Use function pointers.  This avoids the copying, but is considerably more difficult.  (When I tried it, I didn't think the code was any better as a result.  Maybe you can come up with a better design.)

**!!! Important #2 !!!** Your game board must be dynamically allocated on the heap (as opposed to statically allocated on the stack). Putting the game board on the heap allows Valgrind to detect if you have any bugs that read and/or write memory outside of the game board.  In order to meet expectations for this assignment, your code will have to run under Valgrind with no memory errors (neither leaks nor out-of-bounds issues).

### Code Quality

Your code must follow standard design principles.  For example, be sure to
   1. Use comments 
   2. Divide your code into appropriately-sized functions and files
   3. Make sure your code is neat, well-organized, and well-organized

## Testing / Test Driven Development

You must use a Test Driven Development (TDD) workflow and write a complete set of tests for your game. You can write either unit tests or system tests (or both). You must submit your initial set of tests by _test_due_date_.  (I'll explain more about TDD in class.)

## Assignment Workflow

1. Begin by following this [GitHub Classroom link](https://classroom.github.com/a/mC2Nf2pv) and cloning the resulting repository.
   1. Your game code will go in the [src](src) directory.  This directory contains shell files that you should put your code in.
      If you use these files, the [Makefile](Makefile) should just work.  If you add/change files, you'll have to also adjust the `Makefile`.
   2. The [spec](spec) directory contains the system tests. These tests use Ruby's [RSpec](https://rspec.info/) framework.  You can add your tests to [c4_student_spec.rb](spec/c4_student_spec.rb), and/or add your own files.
   3. The [test](test) directory is for unit tests. If you are writing 
     unit tests, you may add them to [student_test.c](test/student_test.c).  (If you use different/additional files you will have to adjust the Makefile accordingly.)  The sample student tests use the [Unity](https://github.com/ThrowTheSwitch/Unity) unit test framework. One of the authors (Mike Karlesky) is a GVSU alumnus.

   
2. Write a complete set of tests. Writing tests first is called _Test Driven Development_ (TDD) and will help you write better / less buggy code.  
   1. Add your tests to [student_tests.c](test/student_tests.c) and/or [c4_student_spec.rb](spec/c4_student_spec.rb)
   2. When your tests are complete, implement your Connect 4 game.  If you put your internal functions in [connect4_engine.c](src/connect4_engine.c) and your `main` in [c4.c](src/c4.c), then the Makefile will build your program without any further changes.
      1. `make studentTests` will compile your unit tests against your code.
      2. `make c4` will build your game
      3. Running `rspec` from the root directory of the project will run your system tests.
   4. When your code passes your tests, run it through [Valgrind](https://valgrind.org/) to check for any memory issues (leaks, array overruns, etc.).  (Note:  Valgrind is already installed on EOS.  It will not run on the latest versions of MacOS.)
      1. Use this command to run your system tests through Valgrind: `C4_EXEC='valgrind ./run_c4'`
   5. Use the GitHub Action to test your code using _my_ tests.
      1. Commit and push your code to GitHub.
      2. From the GitHub web page for your repo, go to the "Actions" tab. 
      3. Look under the blue "All workflows" button and click "Connect 4 Check"
      4. A "Run Workflow" button will appear in the middle of the page. Click on the arrow, select the correct branch, and click the green "Run workflow" button.
   7. If the tests don't pass, then your code has a bug your tests failed to detect.
         1. Write a failing test.
         2. Fix your code so your new test passes.
         3. Run my tests again. 

<span style='bgcolor: blue'> Your code should be primarily tested by _**your**_ tests, not mine.  Therefore, you should be running my tests at most a few times.  Specifically, you are allowed to run my tests at most 3 times per day.</span>  In addition, you must prepare a "testing report".  You must document every time your code fails my tests.  For each failure describe
   1. The failing test(s) you added to your test suite.
   2. The specific program feature tested.
   3. What you will do / consider next time to avoid a similar oversight.

## Submission

When your initial tests are complete, check in your code with "[Check Tests]" in the commit message.

When your project is complete (has a complete set of tests, has a working game, passes my automated tests, passes Valgrind, and is well-formatted and well-documented), 
check in your code with "[Grade Me]" in the commit message.

**Important**: Just because your code passes the GitHub tests, does _not_ mean it meets all the requirements. The GitHub tests do not, for example, check the user interface.  They also don't check the completeness of your unit tests or the quality of your code.

## Academic Honesty

One key purpose of the GitHub classroom setup is to automatically verify that submitted code is bug-free.  Attempting to subvert this system and generate a "false positive" (for example, by modifying files such as the Makefile) is a serious violation of Academic Honesty and could result in a failing grade in the course.

Attempting to reverse engineer the sample solution through de-compiling or other means is a serious violation of Academic Honesty and could result in a failing grade in the course.  Similarly, writing tests is an important part of the software development process. The automated tests are a part of this project's "solution".  Attempting to access the specific test cases through means included, but not limited to, de-compiling and print statements is a serious violation of Academic Honesty and could result in a failing grade in the course.

Hiding and/or obfuscating GitHub activity through means such as rebasing, squashing, or outright deleting test runs is a serious violation of Academic Honesty and could result in a failing grade in the course.