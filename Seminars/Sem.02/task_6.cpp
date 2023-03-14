#include <iostream>
#include <fstream>

const int BUFF_SIZE = 1024;
const char FILE_NAME[] = "task_6.cpp";

void printCode(const char fileName[])
{
    std::ifstream read(fileName);
    if (!read.is_open())
    {
        std::cout << "Error! Cannot open the file\n";
        return;
    }

    while (!read.eof())
    {
        char buffer[BUFF_SIZE + 1];
        read.getline(buffer, BUFF_SIZE);
        std::cout << buffer << '\n';
    }
    read.close();
}

int main()
{
    printCode(FILE_NAME);

    return 0;
}