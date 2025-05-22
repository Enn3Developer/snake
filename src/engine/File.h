#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class File{
protected:
    string file_name;
    string text;
public:
    File (string name, string t);
    string read_file();
    void write_file();
};

#endif //FILE_H
