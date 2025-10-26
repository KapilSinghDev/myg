#ifndef COMMIT_FUCNTIONS
#define COMMIT_FUCNTIONS
#include <iostream>
#include <filesystem>
#include <openssl/sha.h>
#include <string>
#include <fstream>
#include <sstream>
#include "../constants.h"
namespace fs = std::filesystem;
using namespace std;

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

void commit_head_log(string commit_user_message) // this fucntion is called manually when the user commits something
{
    // this function updates the commit hash in the head file
    ifstream inputfile_heaed(ROOT_HEAD_FILE); // reading the current content of the head file
    stringstream headbuffer;
    headbuffer << inputfile_heaed.rdbuf();
    string head_branch_content = headbuffer.str();

    // reading the entire index
    ifstream inputfile_index(ROOT_INDEX_FILE);
    stringstream indexbuffer;
    indexbuffer << inputfile_index.rdbuf();
    string index_branch_content = indexbuffer.str();

    // now calculate hash of all the
    string final_commit_hash = calculateSHA1(index_branch_content + commit_user_message);

    // saves the directory with name as final_commit_hash
    string parent_directory = ROOT_OBJECTS + final_commit_hash.substr(0, 2);
    fs::create_directory(parent_directory);
    // writes the commit message in this file
    ofstream(parent_directory + "/" + final_commit_hash.substr(2)) << commit_user_message;

    int hash_string_starting_point = head_branch_content.find(">") + 1;
    string updated_content = head_branch_content.substr(0, hash_string_starting_point);
    // TODO : CHECK IF WE NEED THE OLD FILE HASH OR THE NEW COMMIT CONTENT AND TREE CONTENT
    //  READS THE ENTIRE INDEX FILE  AND COMMIT MESSAGE AND CREATE A COMBINED HASH THEN
    //  STORES THE FILE IN THE OBJECTS WITH THIS HASH VALUE AS NAMES
    //  AMD COMMIT MESSAGE AS CONTENT
    // AND THEN UPDATES THE HEAD FILE

    ofstream(ROOT_HEAD_FILE) << updated_content << final_commit_hash; // updating the commit hash to the head file
    cout << "----------FILE SUCCESSFULLY COMMITED----------" << endl;
    return;
}
#endif
