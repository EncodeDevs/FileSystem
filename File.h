#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <windows.h>

using namespace std;

class File
{
private:
	string filename;
	string path;

	string fullpath;
public:
	File(string filename, string path);

	string read();
	void write(string content);

	vector<string> getInfo();
	bool exists();
};