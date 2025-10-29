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
#include "commiter/commiter.hpp"
using namespace std;
namespace fs = std::filesystem;
// we will be setting up a command line parser first

bool isInitialized()
{
    return fs::exists(ROOT_DIR);
}

int main(int argc, char *argv[])
{
    string command = argv[1];
    if (command != start && !isInitialized())
    {
        cout << "Error: myg not initialized. Run './myg start' first" << endl;
        return 1;
    }

    Initialise initialise;
    // default mode
    if (command == start)
    {

        if (argc == 2)
        {
            // Default branch
            // Initialise initialise;
            initialise.create_branch(default_branch);
            cout << "initiallised myg tracking" << endl;
        }
        else if (argc == 3)
        {
            // Custom branch
            // Initialise initialise;
            string custom_default_branch = argv[2];
            initialise.create_branch(custom_default_branch);
            cout << "initiallised myg tracking" << endl;
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
    else if (command == commit)
    {
        // Expect: myg commit -m "message"
        if (argc < 4)
        {
            cout << "Usage: myg commit -m \"<message>\"" << endl;
            return 1;
        }

        if (string(argv[2]) == "-m")
        {
            string message = argv[3];
            commit_head_log(message);
            // TODO: create commit
        }
        else
        {
            cout << "Expected -m flag" << endl;
            return 1;
        }
    }
    else if (command == shootoff)
    {
        string new_branch = argv[2];
        initialise.create_branch(new_branch); // current branch is automatically maintained in this function
    }
    else if (command == show)
    {
        initialise.get_current_branch();
    }
    else if (command == eject)
    {
        // delete the entire .myg
        if (filesystem::exists(ROOT_DIR))
        {
            fs::remove_all(ROOT_DIR);
            cout << (!fs::exists(ROOT_DIR) ? "tracker removed successfully" : " Error while untracking : Possibly myg was never initiallised") << endl;
        }
    }
    else if (command == bay)
    {
        cout << "These are the code branches" << endl;
        get_all_branches();
    }
    else
    {
        cout << "no such command exists" << endl;
    }
    return 0;
}
