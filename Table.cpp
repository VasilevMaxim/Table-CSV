#include "Table.h"
#include <fstream>
#include <iostream>


Table::Table(const string& pathFile)
{
	OutputFile(pathFile);
	InitializationTable();
}

string Table::GetValue(int numRow, int numColumn)
{
	if (numRow < 0)
	{
		throw std::invalid_argument(std::to_string(numRow));
	}
	if (numColumn < 0)
	{
		throw std::invalid_argument(std::to_string(numColumn));
	}

	return _table.at(make_pair(numRow, numColumn));
}

string Table::GetValue(pair<int, int> cell)
{
	return GetValue(cell.first, cell.second);
}

void Table::SetValue(const string& value, int numRow, int numColumn)
{
	if (numRow < 0)
	{
		throw std::invalid_argument(std::to_string(numRow));
	}
	if (numColumn < 0)
	{
		throw std::invalid_argument(std::to_string(numColumn));
	}

	if (numRow > _countRows)
	{
		_countRows = numRow;
	}
	if (numColumn > _countColumns)
	{
		_countColumns = numColumn;
	}

	_table[make_pair(numRow, numColumn)] = value;
}

void Table::SetValue(const string& value, pair<int, int> cell)
{
	SetValue(value, cell.first, cell.second);
}

void Table::RemoveAt(int numRow, int numColumn)
{
	auto iter = _table.begin();

	while (iter != _table.end())
	{
		auto current = iter;
		++iter;
		if (iter->first == make_pair(numRow, numColumn))
		{
			_table.erase(iter);
			break;
		}
	}
}

void Table::SaveTable(const string& pathFile)
{
	std::ofstream file(pathFile);
	if (file.is_open())
	{
		string textTable = ConvertInCSV();
		file << textTable;
	}
	else
	{
		throw std::invalid_argument(pathFile);
	}
	file.close();
}

Table& Table::operator=(const Table& value)
{
	if (this == &value)
	{
		return *this;
	}
	_table = value._table;
	return *this;
}

void Table::OutputFile(const string& pathFile)
{
	string line = "";
	std::fstream file(pathFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			_dataFile += line + '\n';
		}
	}
	else
	{
		throw std::invalid_argument(pathFile);
	}
	file.close();
	_dataFile.pop_back();
}

void Table::InitializationTable()
{
	int row = 0;
	int column = 0;
	string value = "";
	bool isLine = false;

	for (auto& sym : _dataFile)
	{
		if (sym == '"')
		{
			isLine = !isLine;
			continue;
		}
		if (sym == ',' && isLine == false)
		{
			_table[make_pair(row, column)] = value;
			column++;
			value = "";
			continue;
		}
		if (sym == '\n')
		{
			_table[make_pair(row, column)] = value;
			
			row++;

			if (column > _countColumns)
			{
				_countColumns = column;
			}

			column = 0;
			value = "";
			continue;
		}

		value += sym;
	}

	_countRows = row;
}

string Table::ConvertInCSV()
{
	string textAll = "";
	string line = "";
	for (int i = 0; i <= _countRows; ++i)
	{
		for (int j = 0; j <= _countColumns; ++j)
		{
			if (_table[make_pair(i, j)].find(",") != -1)
			{
				line += '"' + _table[make_pair(i, j)] + '"' + ',';
			}
			else
			{
				line += _table[make_pair(i, j)] + ',';
			}
		}
		line.pop_back();
		textAll += line + '\n';
		line = "";
	}

	textAll.pop_back();
	return textAll;
}
