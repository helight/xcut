Now，this doc is just from [luct](http://code.google.com/p/lcut/wiki/lcut_user_guide)

# Motivation #

In late 2005，the "TDD" concept was so popular and there were many strong and mature unit testing framework available for Java programmers, C# programmers and even python programmers, But there were few for C programmers. I have googled some c unit testing framework and gave me a shot, but eventually none of them made me comfortable. so I decided to implement a new one for my daily work and then lcut born.

## Introduction ##

lcut is short for "Lightweight C Unit Test framework". lightweight means it is very small and easy to learn&use. The framework is inspired by the well-known JUnit which is invented by Kent Beck.The structure of lcut could be illustrated as below:
```
    A logical Test
          |
          |
     +-------------+
    TS-1    ...  TS-N
     |             |
     |             |
  +-------+ ...   +--------+
TC-1   TC-N     TC-1     TC-N
TS - Test Suite，TC - Test Case
```
A unit test using lcut is divided into three levels: logical test, test suite and test case. A logical test contains several test suites and each test suite also contains several test cases. test case is the most basic and the smallest unit in this framework. And the three-level concept is helpful for you to organize your unit testing well.

## Feature list ##
small and easy to learn&use
inspired by xUnit
three-level concepts to help organizing your test well and each level could have independent setup and teardown fixtures
provide mock support (inspired by cmockery)
For more information, please open and read the lcut\_user\_guide.