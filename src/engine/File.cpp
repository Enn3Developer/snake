#include "File.h"

File::File(string name, string t){
	file_name=name;
	text=t;
}

string File:: read_file(){
	ifstream inputFile;
	inputFile.open(file_name);
	while(!inputFile.eof()){
		text += inputFile.get();
	}
	inputFile.close();
	return text;
}

void File::write_file(){
	ofstream outputFile;
	outputFile.open(file_name);
	outputFile<<text;
	outputFile<<"\n";
	outputFile.close();
	return;
}
