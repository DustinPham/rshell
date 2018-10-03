RSHELL 
===

Licensing Information: BSD3 
----
Project source can be downloaded from https://github.com/DustinPham/rshell.git
-----

Author & Contributor List
-----------
Dustin Pham

How to run
------------
1. `git clone https://github.com/DustinPham/rshell.git`
2. `cd rshell`
3. `make`
4. Run either RShell or ls

Running RShell:
* `bin/rshell`

Running ls:
* `bin/ls`

Using RShell
-------------
* Multiple commands can be used together on the same line using `;`,`&&`, or `||` as connectors.

* Connecting multiple commands with `;` will execute every command on their own regardless of the prior command's success or failure.

* Connecting multiple commands with `&&` will execute each command in order until one fails.

* Connecting multiple commands with `||` will only execute the command if the prior command failed.

* Allows the changing of directories with `cd`.

* Does NOT support multiple types of connectors on one line.

* Extra connectors in front of and after commands do nothing.

* Anything after a `#` will be ignored.

* Works with I/O redirection and single pipes.

* To exit RShell, use the command `exit`.


Using ls
------------
* Run `bin/ls` to view files in the current directory.
* Use optional flags `-a`, `-l`, and `-R` to show hidden files, use long listing format, and recursively go through directories respectively.
* `bin/ls` can be used with optional file or directory parameters.
* Directories are displayed in blue, executables are displayed in green, and hidden files are displayed with a gray background. Directories and executable colors can be combined with the hidden file color background.

Bugs/Limitations
-----------------
RShell:
* Cannot do multiple pipes or pipes with I/O redirection.

* Using `cd` with pipes causes rshell to stall.

* Running `make` within rshell causes a `g++` error.

* Can only do up to 1 Input and 1 Output redirection on the same line.

* `<<<` prints an extra space at the beginning.

* `&` is not interpreted by the program and will cause a fail.

* Still has some possible memory leaks when non-sense commands are inputted such as `asd`.


ls:

* Total for the `-l` flag is incorrect.
* Files and directories are not printed in alphabetical order.
* `-R` flag sometimes has awkward newline spacing.
* Formatting is set to 4 files/directories per line, resulting in no more than 4 columns.
* Calling `bin/ls` on files or directories that do not exist results in a stat error.



