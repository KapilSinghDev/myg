#ifndef MY_TRACKER
#define MY_TRACKER
#include <iostream>
#include <filesystem>
#include <openssl/sha.h>
#include <string>
#include "../constants.h"
#include "../commiter/commiter.hpp"
namespace fs = std::filesystem;
using namespace std;

class Tracker
{
private:
    string path;
    string filehash;
    bool track()
    {
        return fs::exists(path) ? true : false;
    }

    void save_file()
    {
        ifstream inputfile(path);
        stringstream buffer;
        buffer << inputfile.rdbuf();
        string content = buffer.str();
        string blobData = "blob " + to_string(content.length()) + string(1, '\0') + content;
        string hashstring = calculateSHA1("blob " + to_string(content.length()) + string(1, '\0') + content);
        this->filehash = hashstring;
        cout << hashstring << endl;
        string object_sub_directory = hashstring.substr(0, 2);
        string hash_object = hashstring.substr(2);
        fs::create_directory(ROOT_OBJECTS + object_sub_directory + "/");
        ofstream(ROOT_OBJECTS + object_sub_directory + "/" + hash_object) << blobData;
        return;
    }
    void index_log()
    {
        ofstream of;
        of.open(ROOT_INDEX_FILE, ios::app); // Add ios::app!
        if (of)
        {
            of << path << " " << filehash << endl;
            of.close();
        }
        return;
    }

public:
    Tracker(string file)
    {
        path = file;
        if (track())
        {
            save_file();
            index_log();
            cout << " file traced : success " << endl;
        }
        else
        {
            cout << " Not found " << file << endl;
        }
    }
};
#endif