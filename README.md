# Abaco-PreWork
Pre-work given by Christopher before starting

## 1. Arduino Under the Hood

- Lights with interrupts  
https://www.tinkercad.com/things/8EbRhI4tiAr
- PORTB  
https://www.tinkercad.com/things/fBwBnV4xrR7
- Serial  
https://www.tinkercad.com/things/2wDOUTknOxj

Done using TinkerCAD online circuit simulator

https://www.tinkercad.com/login  
xoswqzskbuptatjqkr@awdrt.net  
[Banana's valhala] (then finish)

## 2. Jenkins Automation
Test program made to compile and run C programs.  
Assumes Jenkins installed and configured.  
Assumes gcc (GNU C compiler) installed.

GNU Compiler Collection(gcc) names the file as 'a' if not specified(.out or .exe depends on OS)

1. change directory to where you want the output to be
2. compile with absolute path (or just name if output folder is also source folder)
3. run program

```
cd "C:\Users\bawoa.000\Desktop\Jenkins"
C:\MinGW\bin\gcc helloJenkinsC.c
a
```

**_NOTE: Can specify an filename for the output_**

```
cd "C:\Users\bawoa.000\Desktop\Jenkins"
C:\MinGW\bin\gcc helloJenkinsC.c -o hello
hello
```

*__NOTE: Output filename can be absolute or relative so it's placed in a different folder__*

```
cd "C:\Users\bawoa.000\Desktop\Jenkins"
C:\MinGW\bin\gcc helloJenkinsC.c -o tests\hello
tests\hello
```

_**FYI: Might try running Jenkins and working on files fom GitHub**_

## 3. Word Search Puzzle
* level0 - 1D solver
* level1 - 2D solver that writes output into new file (can also find words written backwards)
* level2 - Detects verical words (changed from treating each line as string to treating the grid like an actual 2D array)
  - level2_5 - Reorganised some code into functions
  * *(Not on of the actual levels given)*
* level3 - Detects diagonal words (given restriction of going downwards)
* level5 - Detects orthogonal words (given restriction of 3-letter words)





