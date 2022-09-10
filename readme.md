# Terminal Jumper
Terminal Jumper is a fun completely in-terminal TUI (`Terminal User Interface`) game that is based off of Chrome's dinosaur jumping game (`chrome://dino`). It is designed to provide a fun experience all while staying inside of the terminal.

## Install
To install Terminal Jumper, all you need to do is follow these steps:

1. Clone the git repository:
```bash
$ git clone https://github.com/TheRekrab/TerminalJumper
```

2. Use the Makefile provided to add the program onto your path:
```bash
$ make install
```

Presto! Terminal Jumper is now installed on your system.

## Usage
Terminal Jumper is very easy to use and play.

Simply run the command `jump` and you will be greeted with the basic screen:

```
SCORE: 0
+----------->> TERMINAL JUMPER <<---------+
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|             #                           |
+------->> Use SPACE/UP to jump <<--------+
```
You are the hashtag (`#`). You can press space/up/w to jump, and try to avoid hitting '`*`'s. Those are bad.

```
SCORE: 24                     TOP SCORE: 32
+----------->> TERMINAL JUMPER <<---------+
|                                         |
|                                         |
|                                         |
|                                         |
|              #                          |
|                        *                |
|                      * *                |
|                      * **               |
+------->> Use SPACE/UP to jump <<--------+
```
If you hit an obstacle, you lose. 

## Extra Features
If you run the program with the argument `top`, then you will see the top 3 highest scores:
```bash
$ jump top
  TOP SCORES:
  1  :  32
  2  :  28
  3  :  12
```
Each time you play, your score is recorded to `~/.jumplog`, so if you run `wc -l ~/.jumplog`, then you can also see how many times you have played. Also, the program uses the `HOME` environment variable to get the path of the jumplog, so different users on the same system can have different top scores.


### Have fun playing!