G++ = g++ -Wall -Werror -ansi -pedantic
  
all:
	if [ ! -d "./bin" ];\
	then mkdir bin;\
	fi
	$(G++) src/main.cpp -o bin/rshell
	$(G++) src/cp.cpp -o bin/cp
	$(G++) src/ls.cpp -o bin/ls
rshell:
	if [ ! -d "./bin" ];\
	then mkdir bin;\
	fi
	$(G++) src/main.cpp -o bin/rshell
cd:
	if [ ! -d "./bin" ];\
	then mkdir bin;\
	fi
	$(G++) src/cp.cpp -o bin/cp
ls:
	if [ ! -d "./bin" ];\
	then mkdir bin;\
	fi
	$(G++) src/ls.cpp -o bin/ls
