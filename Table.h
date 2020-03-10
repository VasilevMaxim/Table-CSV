#pragma once

#include <string>
#include <map>
#include <utility>   

using std::string;
using std::wstring;
using std::map;
using std::pair;
using std::make_pair;

class Table
{
private:
	map<pair<int, int>, string> _table;
	string _dataFile;
	int _countRows;
	int _countColumns;


	void OutputFile(const string& pathFile);
	void InitializationTable();
	string ConvertInCSV();

public:

	Table(const string& pathFile);

	string GetValue(int numRow, int numColumn);
	string GetValue(pair<int,int> cell);

	void SetValue(const string& value, int numRow, int numColumn);
	void SetValue(const string& value, pair<int, int> cell);

	void RemoveAt(int numRow, int numColumn);

	void SaveTable(const string& pathFile);

	Table& operator=(const Table& value);
};

