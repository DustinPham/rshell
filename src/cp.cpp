#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "Timer.h" 

using namespace std;

void copy(char input[], char *output) {
	ofstream out(output);
	ifstream in(input);
		
	char c = in.get();

	while(in.good()) {
		out.put(c);
		c = in.get();
	}
	
}
void readwrite(char ifile[], char ofile[]) {
	char *buf[1];
	
	int desci = open(ifile, O_RDONLY);
	if (desci == -1) {
		perror("open");
		exit(1);
	}
	int desco = open(ofile, O_WRONLY);
	if (desco == -1) {
		perror("open");
		exit(1);
	}

	int red;
	while(red = read(desci, buf, 1) != '\0') {
		if(red == -1) {
			perror("reading error");
			exit(1);
		}
		if(write(desco, buf, 1) == -1) {
			perror("writing error");
			exit(1);
		}
	}
}
void rwbuf(char ifile[], char ofile[]) {
	char buf[BUFSIZ];

	int desci = open(ifile, O_RDONLY);
	if (desci == -1) {
		perror("open");
		exit(1);
	}
	int desco = open(ofile, O_WRONLY);
	if (desco == -1) {
		perror("open");
		exit(1);
	}


	if(read(desci, buf, BUFSIZ) == -1) {
		perror("reading error");
		exit(1);
	}
	if(write(desco, buf, BUFSIZ) == -1) {
		perror("writing error");
		exit(1);
	}
	
}

	
int main(int argc, char *argv[]) {	
	string temp;
	char *tmp = 0;
	struct stat s;
	
	if(argv[1][0] == '-' && argv[1][1] == 'f') {
		tmp = argv[1];
		argv[1] = argv[2];
		argv[2] = tmp;
	}
	if(argv[2][0] == '-' && argv[2][1] == 'f') {
		tmp = argv[2];
		argv[2] = argv[3];
		argv[3] = tmp;
	}

	string first = argv[1];
	string second = argv[2];

	if(first.at(0) != '.' && first.at(1) != '/') {
		temp = "./";
		first = temp + first;
	
		if(stat(first.c_str(), &s) == -1) {
			perror("stat");
			exit(1);
		}
		if(s.st_mode & S_IFDIR) {
			cout << "First argument is a directory" << endl;
			exit(1);
		}
	}
	else { 
		if(stat(argv[1], &s) == -1) {
			perror("stat");
			exit(1);
		}
		if(s.st_mode & S_IFDIR) {
			cout << "First argument is a directory." << endl;
		}
	}

	if(ifstream(argv[2])) {
		cout << "Error: Second input is an existing file." << endl;
		exit(1);
	}
	else if(!ifstream(argv[2])) {
		if(argc == 4) {
			if(argv[3][1] != 'f') {
				cout << "Invalid flag." << endl;
				exit(1);
			}
			else if(argv[3][1] == 'f') {
				ofstream make(argv[2]);
				if(!make.good()) {
					cout << "Cannot open file" << endl;
					exit(1);
				}
				make.close();
			}
		}
		else if(argc == 3) {
			ofstream make(argv[2]);
			if(!make.good()) {
				cout << "Cannot open file" << endl;
				exit(1);
			}
			make.close();
		}	
	}
	
	if(second.at(0) != '.' && second.at(1) != '/')  {
		temp = "./";
		second = temp + second;
	
		if(stat(second.c_str(), &s) == -1) {
			perror("stat");
			exit(1);
		}	
		if(s.st_mode & S_IFDIR) {
			cout << "Second argument is a directory" << endl;
			exit(1);
		}
	}
	
	else  {
		if(stat(argv[2], &s) == -1) {
			perror("stat");
			exit(1);
		}
		if(s.st_mode & S_IFDIR) {
			cout << "Second argument is a directory" << endl;
			exit(1);
		}
	}


	if(argc > 4 || argc < 3) {
		cout << "Error: Need 2 or 3 arguments." << endl;
		exit(1);
	}

	Timer t;
	double eTime;

	if(argc == 3) {
		t.start();
		rwbuf(argv[1], argv[2]);

		cout << "Time for Method 3" << endl;
		t.elapsedWallclockTime(eTime);
		cout << "Wallclock time: " << eTime << endl;
		t.elapsedUserTime(eTime);
		cout << "User time: " << eTime << endl;
		t.elapsedSystemTime(eTime);
		cout << "System time: " << eTime << endl;
	}
	else if(argc == 4) {
		
				t.start();
				copy(argv[1], argv[2]);

				cout << "Time for Method 1" << endl;
				t.elapsedWallclockTime(eTime);
				cout << "Wallclock time: " << eTime << endl;
				t.elapsedUserTime(eTime);
				cout << "User time: " << eTime << endl;
				t.elapsedSystemTime(eTime);
				cout << "System time: " << eTime << endl;

				t.start();
				readwrite(argv[1], argv[2]);

				cout << "Time for Method 2" << endl;
				t.elapsedWallclockTime(eTime);
				cout << "Wallclock time: " << eTime << endl;
				t.elapsedUserTime(eTime);
				cout << "User time: " << eTime << endl;
				t.elapsedSystemTime(eTime);
				cout << "System time: " << eTime << endl;

				t.start();
				rwbuf(argv[1], argv[2]);

				cout << "Time for Method 3" << endl;
				t.elapsedWallclockTime(eTime);
				cout << "Wallclock time: " << eTime << endl;
				t.elapsedUserTime(eTime);
				cout << "User time: " << eTime << endl;
				t.elapsedSystemTime(eTime);
				cout << "System time: " << eTime << endl;

	}	
	
	return 0;
}
