#ifndef MY_TRACKER
#define MY_TRACKER
#include <iostream>
#include <filesystem>
#include <openssl/sha.h>
#include <string>
#include "../constants.h"
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
    string calculateSHA1(const string &data)
    {
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1((unsigned char *)data.c_str(), data.length(), hash);

        stringstream ss;
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        return ss.str();
    }
    void save_file()
    {
        ifstream inputfile(path);
        stringstream buffer;
        buffer << inputfile.rdbuf();
        string content = buffer.str();
        string blobData = "blob " + to_string(content.length()) + string(1, '\0') + content;
        // calculate a hash
        string hashstring = calculateSHA1("blob " + to_string(content.length()) + string(1, '\0') + content);
        cout << hashstring << endl;
        // strip first two characters open a sub directory in objects and store the rest in that sub directory
        string object_sub_directory = hashstring.substr(0, 2);
        string hash_object = hashstring.substr(2);
        // search the directory , subdirectory and create a file named hash object and put the entire hash in it
        // when the file is inserted write the whole hash string
        fs::create_directory(ROOT_OBJECTS + object_sub_directory + "/");
        ofstream(ROOT_OBJECTS + object_sub_directory + "/" + hash_object) << blobData;
        cout << " file traced : success " << endl;
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