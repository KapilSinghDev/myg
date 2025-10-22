#ifndef MY_BUILDER_H
#define MY_BUILDER_H
#include <string>
#include <filesystem>
#include <fstream> // for file I/O
#include "../constants.h"
using namespace std;
namespace fs = std::filesystem;

class Initialise
{
private:
    string branch;
    void init()
    {
        cout << "initiallised branch ->" << branch << endl;
        fs::create_directories(ROOT_DIR);
        fs::create_directories(ROOT_OBJECTS);
        fs::create_directories(ROOT_REF);
        fs::create_directories(ROOT_SUB_HEAD);
        string logs = "ref: refs/heads/" + branch;
        ofstream(ROOT_HEAD_FILE) << logs << endl;
        return;
    }

public:
    Initialise(string branch)
    {
        this->branch = branch;
        init();
    }
};

#endif