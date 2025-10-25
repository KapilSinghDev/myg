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
#include "tracker/tracker.hpp"
using namespace std;
namespace fs = std::filesystem;
// we will be setting up a command line parser first

int main(int argc, char *argv[])
{
    Initialise initialise;
    string command = argv[1];
    // default mode
    if (command == start)
    {

        if (argc == 2)
        {
            // Default branch
            // Initialise initialise;
            initialise.create_branch(default_branch);
        }
        else if (argc == 3)
        {
            // Custom branch
            // Initialise initialise;
            string custom_default_branch = argv[2];
            initialise.create_branch(custom_default_branch);
        }
        else
        {
            cout << "Invalid number of arguments" << endl;
        }
    }
    else if (command == mount)
    {
        string mount_file_path = argv[2];
        Tracker trace(mount_file_path);
    }
    else
    {
        cout << "no such command exists" << endl;
    }
    return 0;
}
