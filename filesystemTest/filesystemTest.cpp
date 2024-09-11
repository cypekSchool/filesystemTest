#include <iostream>
#include <string>
#include <filesystem>
#include <map>

using namespace std;
using namespace std::filesystem;

string padInt(int num, int length)
{
	string result = to_string(num);

	while (result.length() < length)
	{
		result = ' ' + result;
	}

	return result;
}

string getSpaces(int amount)
{
	string result = "  ";
	for (int i = 0; i < amount; i++)
	{
		result += " ";
	}
	return result;
}


int main()
{
	const path dir = "E:\\xampp";
	unsigned int index = 0;

	unsigned int maxFilenameLength = 0;
	map<int, directory_entry> items;

	for (auto& item : directory_iterator(dir))
	{
		if (item.is_directory() || (item.is_regular_file() && item.path().extension() == ".txt"))
		{
			items.insert({ ++index, item });
			int filenameLength = item.path().filename().string().length();
			if (filenameLength > maxFilenameLength) maxFilenameLength = filenameLength;
		}
	}

	int maxIndexColumnLength = to_string(items.size() - 1).length();

	cout << padInt(0, maxIndexColumnLength) << ' ' << "../" << endl;

	for (auto& pair : items)
	{
		bool isDir = pair.second.is_directory();
		string filename = pair.second.path().filename().string();
		cout << padInt(pair.first, maxIndexColumnLength) 
			<< "  " << filename 
			<< (isDir ? "/" : (getSpaces(maxFilenameLength - filename.length()) + to_string(pair.second.file_size()))) << endl;
	}
}

