#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;

void copy(string input, string output) {
	ofstream out(output.c_str());
	ifstream in(input.c_str());

	char c = in.get();

	while(in.good()) {
		if(in.good()) {
			out.put(c);
			c = in.get();
		}
	}
}
void readwrite(string ifile, string ofile) {
	char *buf[1];
	
	int desci = open(ifile.c_str(), O_RDONLY);
	int desco = open(ofile.c_str(), O_WRONLY);
	
	int red;
	while(red = read(desci, buf, 1) != '\0') {
		if(red == -1) {
			perror("reading error");
		}
		if(write(desco, buf, 1) == -1) {
			perror("writing error");
		}
	}
}
void rwbuf(string ifile, string ofile) {
	char *buf[BUFSIZ];

	int desci = open(ifile.c_str(), O_RDONLY);
	int desco = open(ofile.c_str(), O_WRONLY);
	int red;

	if(read(desci, buf, BUFSIZ) == -1) {
		perror("reading error");
	}
	if(write(desco, buf, 1) == -1) {
		perror("writing error");
	}
}
int main() {	

	string ifile, ofile;
	cout << "Enter a file to get copied: " ;
	cin >> ifile;
	cout << "Enter a filename to copy into: ";
	cin >> ofile;	
//	copy(ifile, ofile);
	readwrite(ifile, ofile);	



	return 0;
}
