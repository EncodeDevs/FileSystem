#include "File.h"

File::File(string filename, string path)
{
	this->filename = filename;
	this->path = path;
	
	this->fullpath = this->path + "\\" + this->filename;
}

string File::read()
{
	string content;

	ifstream file(this->fullpath);
	file >> content;
	file.close();

	return content;
}

void File::write(string content)
{
	ofstream file(this->fullpath);
	file << content;
	file.close();
}

vector<string> File::getInfo()
{
	vector<string> res;
	ifstream file(this->fullpath);

	file.seekg(0, ios::end);
	int size = file.tellg();
	file.seekg(0, ios::beg);

	struct stat filestat;
	if (stat(this->fullpath.c_str(), &filestat) != 0)
	{
		return res;
	}

	time_t creationtime = filestat.st_ctime;
	time_t lastmodificationtime = filestat.st_mtime;
	time_t lastaccesstime = filestat.st_atime;

	res.push_back("File: " + this->filename);
	res.push_back("Path: " + this->path);
	res.push_back("Full Path: " + this->fullpath);
	res.push_back("Size: " + to_string(size) + " bytes");
	res.push_back("Creation Time: " + string(ctime(&creationtime)));
	res.push_back("Last Modification Time: " + string(ctime(&lastmodificationtime)));
	res.push_back("Last Access Time: " + string(ctime(&lastaccesstime)));

	file.close();
	return res;
}

bool File::exists()
{
#ifdef _WIN32
	DWORD attributes = GetFileAttributes((LPCWSTR)this->fullpath.c_str());
	return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
#else
	struct stat buffer;
	return (stat(this->fullpath.c_str(), &buffer) == 0);
#endif
}