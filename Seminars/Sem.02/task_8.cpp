#include <iostream>
#include <fstream>

const int BUFF_SIZE = 1024;

enum Category
{
    OKN, M, PM, PR, Other
};

enum EndExam
{
    Exam, Course_Project, Test, All
};

struct Subject
{
    unsigned int id = 0;
    char name[21];
    Category category;
    unsigned int ects = 0;
    EndExam endExam;
};

struct SubjectList
{
    Subject subjects[50];
    int count = 0;
};

Category textToCategory(const char category[3])
{
    switch (category[0])
    {
    case 'O':
        if (category[1] == 'K')
        {
            return OKN;
        }
        else
        {
            return Other;
        }
        break;
    case 'M':
        return M;
        break;
    case 'P':
        if (category[1] == 'M')
        {
            return PM;
        }
        else
        {
            return PR;
        }
        break;
    default: std::cout << "Such category does not exist\n";
        break;
    }
}

bool fileIsEmpty(const char fileName[])
{
    std::ifstream file(fileName);
    char buffer[2];
    file.getline(buffer, 1);
    file.close();
    return buffer[0] == '\0';
}

Subject subjectFromFile(const char fileName[])
{
    std::ifstream file(fileName);
    Subject subject;
    if (fileIsEmpty(fileName))
    {
        return subject;
    }
    char buffer[BUFF_SIZE + 1];
    file.getline(buffer, BUFF_SIZE);

    int j = 0, k = 0, component = 1;
    char category[3];
    char exam;
    bool done = false;
    while (buffer[j] != '\0' && !done)
    {
        if (buffer[j++] == ',')
        {
            component++;
            k = 0;
            continue;
        }
        switch (component)
        {
        case 1:
            subject.id *= 10;
            subject.id += buffer[j++] - 48;
            break;
        case 2:
            subject.name[k++] = buffer[j++];
            break;
        case 3:
            category[k++] = buffer[j++];
            break;
        case 4:
            subject.ects *= 10;
            subject.ects += buffer[j++] - 48;
            break;
        case 5:
            exam = buffer[j];
            done = true;
            break;
        default:
            break;
        }
    }

    subject.category = textToCategory(category);

    switch (exam)
    {
    case 'E':
        subject.endExam = Exam;
        break;
    case 'C':
        subject.endExam = Course_Project;
        break;
    case 'T':
        subject.endExam = Test;
        break;
    case 'A':
        subject.endExam = All;
        break;
    default:
        break;
    }

    return subject;
}

void loadSubjectList(SubjectList& list, const char fileName[])
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Cannot open file " << fileName;
        return;
    }
    while (!file.eof())
    {
        list.subjects[list.count++] = subjectFromFile(fileName);
    }
    file.close();
}

void printSubjectInfo(Subject subject)
{
    std::cout << "Subject ID: " << subject.id << "\n"
        << "Subject name: " << subject.name << "\n"
        << "Subject category: " << subject.category << "\n"
        << "Subject ECTS: " << subject.ects << "\n"
        << "Subject's form of end exam: " << subject.endExam << "\n\n";
}

void addSubject(const char fileName[])
{
    SubjectList list;
    loadSubjectList(list, fileName);

    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error! Cannot open " << fileName << "\n";
        return;
    }

    char buffer[BUFF_SIZE + 1];
    std::cout << "Enter subject atributes in CVS format:\n";
    std::cin.getline(buffer, BUFF_SIZE);
    int subjectId = 0;
    for (size_t i = 0; buffer[i] != ','; i++)
    {
        (subjectId *= 10) += buffer[i] - 48;
    }

    bool subjectExists = false;
    for (size_t i = 0; i < list.count; i++)
    {
        if (list.subjects[i].id == subjectId)
        {
            std::ofstream temp("temp.txt");
            temp << buffer;
            list.subjects[i] = subjectFromFile("temp.txt");
            remove("temp.txt");
            temp.close();
            subjectExists = true;
            break;
        }
    }
    if (!subjectExists)
    {
        file << buffer << "\n\n";
    }
    else
    {
        for (size_t i = 0; i < list.count; i++)
        {
            file << list.subjects[i].id << ","
                << list.subjects[i].name << ","
                << list.subjects[i].category << ","
                << list.subjects[i].ects << ","
                << list.subjects[i].endExam << "\n\n";
        }
    }
    file.close();
}

void deleteSubject(int id, const char fileName[])
{
    SubjectList list;
    loadSubjectList(list, fileName);

    bool subjectExists = false;
    for (size_t i = 0; i < list.count; i++)
    {
        if (list.subjects[i].id == id)
        {
            subjectExists = true;
            for (size_t j = i; j < list.count - 1; j++)
            {
                list.subjects[j] = list.subjects[j + 1];
            }
            list.count--;
            
            std::ofstream write(fileName);
            for (size_t j = 0; j < list.count; j++)
            {
                write << list.subjects[j].id << ","
                    << list.subjects[j].name << ","
                    << list.subjects[j].category << ","
                    << list.subjects[j].ects << ","
                    << list.subjects[j].endExam << "\n\n";
            }
            write.close();
            break;
        }
        if (!subjectExists)
        {
            std::cout << "Subject with this ID does not exist\n";
        }
    }
}

void searchSubject(int id, const char fileName[])
{
    SubjectList list;
    loadSubjectList(list, fileName);

    for (size_t i = 0; i < list.count; i++)
    {
        if (list.subjects[i].id == id)
        {
            printSubjectInfo(list.subjects[i]);
            break;
        }
    }
}

void subjectsByCategory(Category category, const char fileName[])
{
    SubjectList list;
    loadSubjectList(list, fileName);

    std::cout << "Subjects from category " << category << ":\n";
    bool subjectsAvailable = false;
    for (size_t i = 0; i < list.count; i++)
    {
        if (list.subjects[i].category == category)
        {
            printSubjectInfo(list.subjects[i]);
            subjectsAvailable = true;
        }
    }

    if (!subjectsAvailable)
    {
        std::cout << "There are no subjects from this category :(\n\n";
    }
}

void ectsInRange(int minC, int maxC, const char fileName[])
{
     SubjectList list;
    loadSubjectList(list, fileName);

    std::cout << "Subjects that give ECTS in the range [" 
        << minC << ", " << maxC << "]:\n";
    for (size_t i = 0; i < list.count; i++)
    {
        if (list.subjects[i].ects >= minC && list.subjects[i].ects <= maxC)
        {
            printSubjectInfo(list.subjects[i]);
        }
    }
}

int main()
{
    char *filePath = new char[256];
    std::cout << "Enter file path: ";
    std::cin.getline(filePath, 256);

    std::cout << "Allowed actions:"
        << "\n1. Add\n2. Delete\n3. Search by subject's ID\n"
        << "4. Print all subjects from a category\n5. Print subjects with ECTS within a range\n6. Exit\n"
        << "-------------------------------------------------------\n";
    bool exit = false;
    int action, id;;
    do
    {
        std::cout << "Input the number of the action you want to execute: ";
        std::cin >> action;
        switch (action)
        {
        case 1:
            addSubject(filePath);
            break;
        case 2:
            std::cout << "Input the ID of the subject you want to delete: ";
            std::cin >> id;
            deleteSubject(id, filePath);
            break;
        case 3:
            std::cout << "Input the ID of the subject you are searching for: ";
            std::cin >> id;
            searchSubject(id, filePath);
            break;
        case 4:
            std::cout << "Input the category of the subjects you want to see:\n";
            char category[3];
            std::cin.ignore();
            std::cin >> category;
            subjectsByCategory(textToCategory(category), filePath);
            break;
        case 5:
            std::cout << "Input the minimum and maximum value of ECTS of the subjects you want to see: ";
            int minC, maxC;
            std::cin >> minC >> maxC;
            minC = abs(minC);
            maxC = abs(maxC);
            if (minC > maxC)
            {
                int temp = minC;
                minC = maxC;
                maxC = temp;
            }
            break;
        case 6:
            exit = true;
            break;
        default: std::cout << "Wrong input\n";
            break;
        }
    } while (!exit);
    
    delete[] filePath;
    return 0;
}