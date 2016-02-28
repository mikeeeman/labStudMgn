# Description - Student Management System

**Company**
 :  Bern University of Applied Sciences

**Purpose**
 :  This file contains the project description of the software "Student Management System".

The application is an exercise of course BTF2231 (C programming course). The file is written in Markdown. Open it up in a browser like Google Chromium or Mozilla Firefox (with Markdown Preview Add-On installed).

**Author**
 :  Andreas HABEGGER <andreas.habegger@bfh.ch>

**Date**
 :  17.02.2016

___

Structure of Directory
---
### doc/

This folder contains documentation files. The files are most likely in PDF format.

### src/

This folder contains source code files. Because it is a C programming exercise the source files contain appropriate syntax.

**FILES:**
 - studentMgnSystem.pro : QT creator project settings file
 - studentMgnSystem.c : Main program source file
 - helper.c : Helper module source file
 - helper.h : Helper module interface file (header file)
 - userctrl.c : User control module. Consists functions for simple program control on CLI.
 - userctrl.h : User control module interface file (header)
 - studctrl.c : Student control module. Several functions to manipulate data-set
 - studctrl.h : Student control module interface file (header file)
___

Get Started
---
First of all read the documents in **doc** directory. The documentations gives you an idea what this application is about. Next, go on with compiling it. To do so there you have several options. Read the list below to get the most suitable for you.

1. Compile it on CLI by using gcc (on other systems than Linux follow a tutorial to get GCC up and running)
 - Open CLI and change into the project directory
 - create a work directory called "_sandbox".  The underline is due to an exclude pattern in the ".gitignore" file
 
```bash
mkdir _sandbox
cd _sandbox
export SRC="../src"
```
 - Compile the source step by step.
 
```bash
gcc -L $SRC -I $SRC -o studMgnApp $SRC/*.c
```
 - Run the application
 
```bash
./studMgnApp
```
2. Use a make project
 - Follow the Make tutorial of BTF1230
 - Copy the Makefile from tutorial into the current directory
 - Adapt global settings in the Makefile to fit to current project
 - run make to start compilation process
 
```bash
make clean all
```
 - Run the application
 
```bash
./studMgnApp
``` 
3. Use an IDE (Integrated Development Environment)
  - Download QT creator http://www.qt.io/download-open-source/
  - Open the *.pro file
    - In qtcreator IDE [ctrl]+O
    - On CLI run the command
    
```bash
qtcreator studentMgnSystem.pro
```    
  - Walk through the user specific configuration process (there you will add a build kit)
  - Hit [ctrl]+B to build the application
  - Hit [ctrl]+R to run the application
___






