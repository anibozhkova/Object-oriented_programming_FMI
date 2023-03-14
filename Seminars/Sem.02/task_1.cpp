#include <iostream>
#include <fstream>

const char FILE_NAME[] = "result.txt";

void writeSumAndMult(const char fileName[], double a, double b, double c)
{
    std::ofstream write(fileName);
    if (!write.is_open())
    {
        std::cout << "Cannot open this file!\n";
        return;
    }

    double sum = a + b + c;
    double multiplyed = a * b * c;
    write << sum << std::endl << multiplyed;

    write.close();
}

void printDiff(const char fileName[])
{
    std::ifstream read(fileName);
    if (!read.is_open())
    {
        std::cout << "Cannot open this file!\n";
        return;
    }

    double sum, multiplyed;
    read >> sum >> multiplyed;
    std::cout << abs(sum - multiplyed) << std::endl;

    read.close();
}

int main()
{
    double a, b, c;
    std::cout << "Enter three numbers: ";
    std::cin >> a >> b >> c;
    
    writeSumAndMult(FILE_NAME, a, b, c);

    printDiff(FILE_NAME);
    
    return 0;
}