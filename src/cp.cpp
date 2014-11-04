#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "Timer.h" 

using namespace std;

void copy(char input[], char output[]) {
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
	int desco = open(ofile, O_WRONLY);
	
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
	int desco = open(ofile, O_WRONLY);
	if(read(desci, buf, BUFSIZ) != '\0) {
		perror("reading error");
		exit(1);
	}
	if(write(desco, buf, BUFSIZ) == -1) {
		perror("writing error");
		exit(1);
	}
}
	
int main(int argc, char *argv[]) {	
	string first = argv[1];
	string second = argv[2];

	struct stat s;
	if(stat(argv[2], &s) == 0) {
		if(s.st_mode & S_IFREG) {
			cout << "ERROR: This file already exists." << endl;
			exit(1);
		}
		else if(s.st_mode & S_IFDIR) {
			cout << "Second argument is directory." << endl;
		}
		else {
			
			
		}
	}
	else {
		ofstream out(argv[2]);	
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
	}
		
	
			
/*	else if(argc == 4) {

cout << "No third argument, running all methods: " 
<< endl << endl;
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


}*/	

	

	return 0;
}
