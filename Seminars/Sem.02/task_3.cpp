#include <iostream>
#include <fstream>

const int BUFF_SIZE = 1024;
const char INPUT_FILE_NAME[] = "info.txt";
const char OUTPUT_FILE_NAME[] = "placeholders_replaced.txt";

void getInfo(char buffer[BUFF_SIZE])
{
	int i = 0;
	while (buffer[i++] != ' ');
	for (size_t j = 0; ; j++)
	{
		if (buffer[i] == '\0')
		{
			buffer[j] = '\0';
			break;
		}
		buffer[j] = buffer[i++];
	}
}

void replacePlaceholders(const char readFileName[], const char writeFileName[])
{
	std::ifstream read(readFileName);
	std::ofstream write(writeFileName);
	if (!read.is_open())
	{
		std::cout << "Error! Cannot open the info file.";
		return;
	}
	if (!write.is_open())
	{
		std::cout << "Error! Cannot open the placeholders' file.";
		return;
	}

	int placeholderNumber = 0;
	while (!read.eof())
	{
		char buffer[BUFF_SIZE + 1];

		read.getline(buffer, BUFF_SIZE);
		getInfo(buffer);
		if (buffer[0] == '\0')
		{
			continue;
		}

		placeholderNumber++;
		switch (placeholderNumber)
		{
		case 1:
			write << "Dear, " << buffer << " ";
			break;
		case 2:
			write << buffer << ".\n\n";
			break;
		case 3:
			write << buffer << "\n\n";
			break;
		case 4:
			write << "Sincerely,\n" << buffer << "\n\n";
			placeholderNumber = 0;
			break;
		default:
			break;
		}
	}
	read.close();
	write.close();
}

int main()
{
	replacePlaceholders(INPUT_FILE_NAME, OUTPUT_FILE_NAME);

	return 0;
}