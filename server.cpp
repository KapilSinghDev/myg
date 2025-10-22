// myg - my git
#include <iostream>
#include <fstream> // for file I/O
#include <sstream> // for string streams
#include <string>
#include <vector>
#include <filesystem> // C++17 for directory operations
#include <openssl/sha.h>
#include "constants.h"
#include "builder/init.hpp"
using namespace std;
namespace fs = std::filesystem;
// we will be setting up a command line parser first

int main(int argc, char *argv[])
{
    string command = argv[1];
    // default mode
    if (command == start)
    {

        if (argc == 2)
        {
            // Default branch
            Initialise initialise(default_branch);
            // cout << "tracking started" << endl;
            // fs::create_directory(ROOT_DIR);
            // fs::create_directory(ROOT_OBJECTS);
            // fs::create_directory(ROOT_REF);
            // fs::create_directories(ROOT_SUB_HEAD);
            // ofstream(ROOT_HEAD_FILE);
        }
        else if (argc == 3)
        {
            // Custom branch
            string custom_default_branch = argv[2];
            Initialise initialise(custom_default_branch);
            // cout << "tracking started default branch -> " << custom_default_branch << endl;
        }
        else
        {
            cout << "Invalid number of arguments" << endl;
        }
    }
    else
    {
        cout << "no such command exists" << endl;
    }
    return 0;
}
