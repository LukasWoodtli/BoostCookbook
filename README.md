Examples for ["Boost C++ Application Development Cookbook"](https://www.packtpub.com/mapt/book/All%20Books/9781849514880)

# Build

[![Build Status](https://travis-ci.org/LukasWoodtli/BoostCookbook.svg?branch=master)](https://travis-ci.org/LukasWoodtli/BoostCookbook)

# Contents


## Chapter 1: Starting to Write Your Application (p. 7)

| Section                                                                      | Page | Done |
|------------------------------------------------------------------------------|------|------|
| Introduction                                                                 | 7    |   ✓  |
| Getting configuration options                                                | 8    |   ✓  |
| Storing any value in a container/variable                                    | 13   |   ✓  |
| Storing multiple chosen types in a variable/container                        | 16   |   ✓  |
| Using a safer way to work with a container that stores multiple chosen types | 18   |   ✓  |
| Returning a value or flag where there is no value                            | 22   |   ✓  |
| Returning an array from a function                                           | 25   |   ✓  |
| Combining multiple values into one                                           | 28   |   ✓  |
| Reordering the parameters of function                                        | 30   |   ✓  |
| Binding a value as a function parameter                                      | 34   |      |
| Using the C++11 move emulation                                               | 37   |      |
| Making a noncopyable class                                                   | 40   |      |
| Making a noncopyable but movable class                                       | 42   |      |


## Chapter 2: Converting Data (p. 47)

| Section                                      | Page | Done |
|----------------------------------------------|------|------|
| Introduction                                 | 47   |      |
| Converting strings to numbers                | 48   |      |
| Converting numbers to strings                | 51   |      |
| Converting numbers to numbers                | 53   |      |
| Converting userdefined types to/from strings | 56   |      |
| Casting polymorphic objects                  | 59   |      |
| Parsing simple input                         | 61   |      |
| Parsing input                                | 66   |      |


## Chapter 3: Managing Resources (p. 71)

| Section                                                       | Page | Done |
|---------------------------------------------------------------|------|------|
| Introduction                                                  | 71   |      |
| Managing pointers to classes that do not leave scope          | 72   |      |
| Reference counting of pointers to classes used across methods | 74   |      |
| Managing pointers to arrays that do not leave scope           | 77   |      |
| Reference counting pointers to arrays used across methods     | 79   |      |
| Storing any functional objects in a variable                  | 82   |      |
| Passing a function pointer in a variable                      | 85   |      |
| Passing C++11 lambda functions in a variable                  | 86   |      |
| Containers of pointers                                        | 88   |      |
| Doing something at scope exit                                 | 91   |      |
| Initializing the base class by a member of the derived class  | 93   |      |


## Chapter 4: Compile-time Tricks (p. 97)

| Section                                                      | Page | Done |
|--------------------------------------------------------------|------|------|
| Introduction                                                 | 97   |      |
| Checking sizes at compile time                               | 98   |      |
| Enabling the usage of templated functions for integral types | 102  |      |
| Disabling templated functions' usage for real types          | 106  |      |
| Creating a type from number                                  | 108  |      |
| Implementing a type trait                                    | 111  |      |
| Selecting an optimal operator for a template parameter       | 113  |      |
| Getting a type of expression in C++03                        | 116  |      |


## Chapter 5: Multithreading (p. 121)

| Section                                       | Page | Done |
|-----------------------------------------------|------|------|
| Introduction                                  | 121  |      |
| Creating an execution thread                  | 122  |      |
| Syncing access to a common resource           | 126  |      |
| Fast access to common resource using atomics  | 131  |      |
| Creating a work_queue class                   | 134  |      |
| Multiple-readers-single-writer lock           | 138  |      |
| Creating variables that are unique per thread | 141  |      |
| Interrupting a thread                         | 144  |      |
| Manipulating a group of threads               | 146  |      |


## Chapter 6: Manipulating Tasks (p. 149)

| Section                                                 | Page | Done |
|---------------------------------------------------------|------|------|
| Introduction                                            | 149  |      |
| Registering a task for processing an arbitrary datatype | 150  |      |
| Making timers and processing timer events as tasks      | 154  |      |
| Network communication as a task                         | 157  |      |
| Accepting incoming connections                          | 164  |      |
| Executing different tasks in parallel                   | 169  |      |
| Conveyor tasks processing                               | 171  |      |
| Making a nonblocking barrier                            | 176  |      |
| Storing an exception and making a task from it          | 181  |      |
| Getting and processing system signals as tasks          | 185  |      |


## Chapter 7: Manipulating Strings (p. 189)

| Section                                                   | Page | Done |
|-----------------------------------------------------------|------|------|
| Introduction                                              | 189  |      |
| Changing cases and case-insensitive comparison            | 189  |      |
| Matching strings using regular expressions                | 192  |      |
| Searching and replacing strings using regular expressions | 196  |      |
| Formatting strings using safe printf-like functions       | 199  |      |
| Replacing and erasing strings                             | 201  |      |
| Representing a string with two iterators                  | 203  |      |
| Using a reference to string type                          | 206  |      |


## Chapter 8: Metaprogramming (p. 211)

| Section                                          | Page | Done |
|--------------------------------------------------|------|------|
| Introduction                                     | 211  |      |
| Using type "vector of types"                     | 212  |      |
| Manipulating a vector of types                   | 217  |      |
| Getting a function's result type at compile time | 222  |      |
| Making a higher-order metafunction               | 225  |      |
| Evaluating metafunctions lazily                  | 227  |      |
| Converting all the tuple elements to strings     | 230  |      |
| Splitting tuples                                 | 234  |      |


## Chapter 9: Containers (p. 239)

| Section                                                   | Page | Done |
|-----------------------------------------------------------|------|------|
| Introduction                                              | 239  |      |
| Comparing strings in an ultra-fast manner                 | 240  |      |
| Using an unordered set and map                            | 244  |      |
| Making a map, where value is also a key                   | 248  |      |
| Using multi-index containers                              | 252  |      |
| Getting the bene ts of single-linked list and memory pool | 258  |      |
| Using at associative containers                           | 263  |      |


## Chapter 10: Gathering Platform and Compiler Information (p. 267)

| Section                                                                             | Page | Done |
|-------------------------------------------------------------------------------------|------|------|
| Introduction                                                                        | 267  |      |
| Detecting int128 support                                                            | 268  |      |
| Detecting RTTI support                                                              | 270  |      |
| Speeding up compilation using C++11 extern templates                                | 272  |      |
| Writing metafunctions using simpler methods                                         | 274  |      |
| Reducing code size and increasing performance of user-defined types (UDTs) in C++11 | 276  |      |
| The portable way to export and import functions and classes                         | 279  |      |
| Detecting the Boost version and getting latest features                             | 282  |      |


## Chapter 11: Working with the System (p. 285)

| Section                                                    | Page | Done |
|------------------------------------------------------------|------|------|
| Introduction                                               | 285  |      |
| Listing les in a directory                                 | 286  |      |
| Erasing and creating les and directories                   | 288  |      |
| Passing data quickly from one process to another           | 291  |      |
| Syncing interprocess communications                        | 294  |      |
| Using pointers in shared memory                            | 297  |      |
| The fastest way to read les                                | 300  |      |
| Coroutines - saving the state and postponing the execution | 302  |      |


## Chapter 12: Scratching the Tip of the Iceberg (p. 307)

| Section                                          | Page | Done |
|--------------------------------------------------|------|------|
| Introduction                                     | 307  |      |
| Working with graphs                              | 308  |      |
| Visualizing graphs                               | 312  |      |
| Using a true random number generator             | 315  |      |
| Using portable math functions                    | 317  |      |
| Writing test cases                               | 319  |      |
| Combining multiple test cases in one test module | 321  |      |
| Manipulating images                              | 323  |      |
