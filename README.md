# C-Projects
Projects that are completed using C programming language

Adventure Game - Text-based console game that prompts user to move towards available direction(s) and explore the forest of thousand truths. However a dangerous snake is also living inside the forest as well. Game continues until the snake is killed by the character or vice versa.

Alphabetic Order - A simple application that orders characters of an input string based on provided alphabetic order using an algorithm. An example is given below:

Enter the alphabetic order: QWERTYUIOPASDFGHJKLZXCVBNM

Enter the input string: ekeelektroniikka

eeeertiioakkkkln

CuTest - As the name says, this is probably one of the simplest C unit-test frameworks having just one .c and one .h file - which you drop into your source tree and enjoy! So, basically I tried to do the following:

a) To understand how CuTest framework (version 1.5) works
b) To add support for testing functions that returns boolean value
c) To carry some unit-tests for my own functions

For point (a) and (b), it was obvious to study the following files:

CuTest.h - This file contains necessary data-structures and function-prototypes used in CuTest framework.

CuTest.c - This file contains necessary function-bodies corresponding to defined prototypes used in CuTest framework.

TestCuTest.c - This file contains necessary examples about how to write unit-tests and aggregate them into test-suit.

AllTests.c - This file contains the MAIN function for running all tests via RunAllTests() function.

/****** HOW TO BUILD THE APPLICATION AND UNIT TEST? *****/
Basically I tried to define following two tasks in tasks.json file -

(1) C: gcc.exe native build - This will build the main application
(2) C: gcc.exe UT build - This will build the unit-test

For details about CuTest and licensing, please visit: http://cutest.sourceforge.net

Network - A simple application that accomplishes the following tasks - 1) read simple graph network from a text file, 2) shows possible paths from source to destination node, 3) shows all node information, 4) shows the network connectivity matrix.
