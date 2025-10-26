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
        string logs = "ref: refs/heads/" + branch + " -> ";
        ofstream(ROOT_HEAD_FILE) << logs << endl;
    }
    void init()
    {
        fs::create_directories(ROOT_DIR);
        fs::create_directories(ROOT_OBJECTS);
        fs::create_directories(ROOT_REF);
        ofstream(ROOT_UNTRACK_FILE);
        ofstream(ROOT_INDEX_FILE);
        return;
    }

public:
    Initialise()
    {
        if (!fs::exists(".myg"))
        {
            init();
        }
    }
    void get_current_branch()
    {
        // read from head file
        ifstream inputfile(ROOT_HEAD_FILE);
        stringstream buffer;
        buffer << inputfile.rdbuf();
        cout << "Current branch - > " << buffer.str() << endl;
        return;
    }
    void create_branch(string branch)
    {
        this->branch = branch;
        string branch_Path = ROOT_REF + this->branch;
        ofstream outputfile(branch_Path);
        maintain_Current_Branch(branch);
        cout << "created a new branch ->" << branch_Path << endl;
        return;
    }
    void delete_current_branch(string name)
    {
    }
    void get_status()
    {
    }
};

#endif