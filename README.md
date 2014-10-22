RSHELL
===

Licensing Information: READ LICENSE
----
Project source can be downloaded from https://github.com/DustinPham/rshell.git
-----

Author & Contributor List
-----------
Dustin Pham

File List
---------
```
.:

Makefile

LICENSE

README

./src

./tests
```
```
/src:

main.cpp
```
```
./tests:

exec.script
```

How to run
------------
1. `git clone https://github.com/DustinPham/rshell.git`
2. `cd rshell`
3. `make`
4. `bin/rshell`

Using RShell
-------------
* Multiple commands can be used together on the same line using `;`,`&&`, or `||` as connectors.

* Connecting multiple commands with `;` will execute every command on their own regardless of the prior command's success or failure.

* Connecting multiple commands with `&&` will execute each command in order until one fails.

* Connecting multiple commands with `||` will only execute the command if the prior command failed.

* Does NOT support multiple types of connectors on one line.

* Extra connectors in front of and after commands do nothing.

* Anything after a `#` will be ignored.

* To exit RShell, use the command `exit`.

Bugs/Limitations
-----------------
* Connecting 3 or more commands on 1 line causes subsequent calls to almost any command to fail. However, doing multiple `ls -a` calls may fix RShell and it may continue to work.

* Beginning RShell with a medium-to-long comment will cause the next few commands to fail.

* `&` and `|` are not interpreted by the program and will cause a fail.

* Char pointer pointer passed into execvp is not cleared after certain calls to execvp, causing more frequent command failures as RShell continues to run.

* Multiple connectors in front of and after a command without commands inbetween will cause a segmentation fault.








