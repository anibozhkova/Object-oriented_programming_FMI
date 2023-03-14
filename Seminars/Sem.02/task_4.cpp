#include <iostream>
#include <fstream>

const int BUFF_SIZE = 1024;
const char FILE_NAME[] = "relation.txt";

struct Pair
{
    int num1 = 0;
    int num2 = 0;
};

void initPair(Pair& pair)
{
    std::cin >> pair.num1 >> pair.num2;
}

Pair createPair()
{
    Pair pair;
    initPair(pair);
    return pair;
}

void readPairFromFile(Pair& pair, std::ifstream& file)
{
    file >> pair.num1 >> pair.num2;
}

void writePairToFile(Pair& pair, std::ofstream& file)
{
    file << pair.num1 << " " << pair.num2 << "\n";
}

struct Relation
{
    Pair pairs[25];
    unsigned int count = 0;
};

void addPairToRelation(Pair pair, Relation& relation)
{
    relation.pairs[relation.count++] = pair;
}

void writeRelationToFile(Relation relation, std::ofstream& file)
{
    if (!file.is_open())
    {
        std::cout << "Cannot open the file where the relation is supposed to be saved in :(\n";
        return;
    }

    for (size_t i = 0; i < relation.count - 1; i++)
    {
        writePairToFile(relation.pairs[i], file);
    }
    file << relation.pairs[relation.count - 1].num1 << " " << relation.pairs[relation.count - 1].num2;
}

void readRelationFromFile(Relation& relation, std::ifstream& file)
{
    if (!file.is_open())
    {
        std::cout << "Cannot open the file to read the relations :(\n";
        return;
    }
    int i = 0;
    while (!file.eof())
    {
        readPairFromFile(relation.pairs[i], file);
        i++;
    }
    relation.count = i;
}

void printRelation(Relation relation)
{
    for (size_t i = 0; i < relation.count; i++)
    {
        std::cout << "(" << relation.pairs[i].num1 << ", " << relation.pairs[i].num2 << ")\n";
    }
}

int main()
{
    std::cout << "Input count of pairs: ";
    int n;
    std::cin >> n;

    Relation relation;

    std::cout << "\nInput your " << n <<" pair(s):\n";
    for (size_t i = 0; i < n; i++)
    {
        addPairToRelation(createPair(), relation);
    }
    std::cout << "\n\nHere are all the pairs of the relation you created:\n\n";
    printRelation(relation);
    std::cout << "\n\n";

    std::ofstream write(FILE_NAME);
    writeRelationToFile(relation, write);
    write.close();

    Relation relationFromFile;
    std::ifstream read(FILE_NAME);
    readRelationFromFile(relationFromFile, read);
    read.close();

    std::cout << "Here are all the pairs of the relation you created but read from a file:\n\n";
    printRelation(relationFromFile);
    std::cout << "\n";
    return 0;
}