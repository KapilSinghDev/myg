#ifndef MY_TRACKER
#define MY_TRACKER
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class Tracker
{
private:
    string path;
    bool track()
    {
        return fs::exists(path) ? true : false;
    }
    void save_file()
    {
        // calculate hash
        // read the entire file
        // get the current branch from head
        // store the hash to that
        cout << "file traced : success" << endl;
        return;
    }

public:
    Tracker(string file)
    {
        path = file;
        if (track())
        {
            save_file();
        }
        else
        {
            cout << " Not found " << file << endl;
        }
    }
};
#endif