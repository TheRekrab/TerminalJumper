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
SCORE: 24
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

### Have fun playing!