#include <iostream>
#include <fstream>

const int BUFF_SIZE = 128;
const char FILE_NAME[] = "users.txt";

struct User
{
    char name[BUFF_SIZE + 1];
    char email[BUFF_SIZE + 1];
    char password[BUFF_SIZE + 1];
};

struct System
{
    User users[100];
    int count = 0;
};


void readUsersFromFile(System& system, const char fileName[])
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error! Cannot open the file\n";
        //User error = {"","",""};
        return;
    }
    User user;
    while (!file.eof())
    {
        char buffer[BUFF_SIZE + 1];
        file.getline(buffer, BUFF_SIZE);
        if (strcmp(buffer, "") == 0)
        {
            continue;
        }
        strcpy_s(user.name, buffer);
        file.getline(user.email, BUFF_SIZE);
        file.getline(user.password, BUFF_SIZE);

        system.users[system.count++] = user;
    }
    file.close();
}

void writeUserToFile(User user, const char fileName[])
{
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "Error! Cannot open the file\n";
        return;
    }

    file << user.name << "\n" 
         << user.email << "\n" 
         << user.password << "\n\n";
    file.close();
}

void registerUser(const char fileName[])
{
    User user;

    std::cout << "Enter name:\n";
    std::cin.getline(user.name, 129);
    std::cout << "Enter email:\n";
    std::cin.getline(user.email, 129);
    std::cout << "Enter password:\n";
    std::cin.getline(user.password, 129);

    writeUserToFile(user, fileName);
}

void login(const char fileName[])
{
    System system;
    readUsersFromFile(system, fileName);
    
    User user;
    std::cout << "Enter email:\n";
    std::cin.getline(user.email, BUFF_SIZE);
    std::cout << "Enter password:\n";
    std::cin.getline(user.password, BUFF_SIZE);

    bool userExists = false;

    for (size_t i = 0; i < system.count; i++)
    {
        if (strcmp(system.users[i].email, user.email) == 0 &&
            strcmp(system.users[i].password, user.password) == 0)
        {
            userExists = true;
            break;
        }
    }

    if (userExists)
    {
        std::cout << "Login successful\n";
    }
    else
    {
        std::cout << "Such user does not exist in the system\n";
    }
}

int main()
{
    char command[20];
    do
    {
        std::cout << "Enter command:\n";
        std::cin.getline(command, 20);
        
        if (strcmp(command, "\\>register") == 0)
        {
            registerUser(FILE_NAME);
            std::cout << "Do you want to continue?(y/n)\n";
            std::cin.getline(command, 20);
        }
        else if (strcmp(command, "\\>login") == 0)
        {
            login(FILE_NAME);
            std::cout << "Do you want to continue?(y/n)\n";
            std::cin.getline(command, 20);
        }
        else
        {
            std::cout << "Invalid command! Type \"\\>register\" or \"\\>login\"\n";
            continue;
        }
        if (command[0] == 'n')
        {
            break;
        }
        while (command[0] != 'y')
        {
            std::cout << "Invalid command!\nDo you want to continue?(y/n)\n";
            std::cin.getline(command, 20);
            if (command[0] == 'n')
            {
                break;
            }
        }

    } while (true);
    
    return 0;
}