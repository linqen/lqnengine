#include "../includes/LogFile.h"

string LogFile::m_filePath="DefaultLog.txt";
ofstream LogFile::fout;

bool LogFile::Initialize(string filePath) {
	m_filePath = filePath;
	return true;
}

void LogFile::Write(string log) {
	fout.open(m_filePath, ios::app);
	fout << log << endl;
	fout.close();
}