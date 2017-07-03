#ifndef LOGFILE_H
#define LOGFILE_H
#include "ImportExport.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class LQN_API LogFile {
public:
	static bool Initialize(string filePath);

	static void Write(string log);
private:
	static ofstream fout;
	static string m_filePath;
};
#endif