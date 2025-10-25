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
    void maintain_Current_Branch(string current)
    {
        this->branch = current;
        string logs = "ref: refs/heads/" + branch;
        ofstream(ROOT_HEAD_FILE) << logs << endl;
    }
    void init()
    {
        cout << "initiallised myg tracking" << endl;
        fs::create_directories(ROOT_DIR);
        fs::create_directories(ROOT_OBJECTS);
        fs::create_directories(ROOT_REF);
        ofstream(ROOT_UNTRACK_FILE);
        return;
    }

public:
    Initialise()
    {
        init();
    }
    void create_branch(string branch)
    {
        // all the branches are stored in side ref directory

        this->branch = branch;
        string branch_Path = ROOT_REF + this->branch;
        ofstream outputfile(branch_Path);
        maintain_Current_Branch(branch);
        cout << "created a new branch ->" << branch_Path << endl;
        return;
    }
};

#endif