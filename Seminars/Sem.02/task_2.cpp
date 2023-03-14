#include <iostream>
#include <fstream>

const int BUFF_SIZE = 10000;
const char FILE_NAME[] = "text.txt";

int lengthOfFile(const char fileName[])
{
	std::ifstream read(fileName);
	if (!read.is_open())
	{
		std::cout << "Error!";
		return -1;
	}

	read.seekg(0, std::ios::end);
	int length = read.tellg();
	read.close();
	return length;
}

int main()
{
	std::cout << "The length of this file is " << lengthOfFile(FILE_NAME);

	return 0;
}