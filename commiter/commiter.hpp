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

// void commit_head_log(string commit_user_message) // this fucntion is called manually when the user commits something
// {
//     // this function updates the commit hash in the head file
//     ifstream inputfile_heaed(ROOT_HEAD_FILE); // reading the current content of the head file
//     stringstream headbuffer;
//     headbuffer << inputfile_heaed.rdbuf();
//     string head_branch_content = headbuffer.str();

//     // reading the entire index
//     ifstream inputfile_index(ROOT_INDEX_FILE);
//     stringstream indexbuffer;
//     indexbuffer << inputfile_index.rdbuf();
//     string index_branch_content = indexbuffer.str();

//     // now calculate hash of all the
//     string final_commit_hash = calculateSHA1(index_branch_content + commit_user_message);

//     // saves the directory with name as final_commit_hash
//     string parent_directory = ROOT_OBJECTS + final_commit_hash.substr(0, 2);
//     fs::create_directory(parent_directory);
//     // writes the commit message in this file
//     ofstream(parent_directory + "/" + final_commit_hash.substr(2)) << commit_user_message;

//     int hash_string_starting_point = head_branch_content.find(">") + 1;
//     string updated_content = head_branch_content.substr(0, hash_string_starting_point);
//     // TODO : CHECK IF WE NEED THE OLD FILE HASH OR THE NEW COMMIT CONTENT AND TREE CONTENT
//     //  READS THE ENTIRE INDEX FILE  AND COMMIT MESSAGE AND CREATE A COMBINED HASH THEN
//     //  STORES THE FILE IN THE OBJECTS WITH THIS HASH VALUE AS NAMES
//     //  AMD COMMIT MESSAGE AS CONTENT
//     // AND THEN UPDATES THE HEAD FILE

//     // read the current branch from head
//     ifstream current_head(ROOT_HEAD_FILE);
//     stringstream current_head_stream;
//     current_head_stream << current_head.rdbuf();
//     string current_head_branch = current_head_stream.str();
//     current_head_branch = current_head_branch.substr(16); // the actual branch name starts at index 16 refer connstant  ROOT_HEAD
//     // open the file named with current branch if it does not exits
//     // OPEN SUBDIRECTORY WITH CURRENT HEAD BRANCH
//     string current_ref_branch_directory = ROOT_SUB_HEAD + current_head_branch;
//     fs::create_directories(current_ref_branch_directory);
//     ofstream(current_ref_branch_directory) << updated_content + " " + final_commit_hash; // updating the commit hash to the head file
//     cout << "----------FILE SUCCESSFULLY COMMITED----------" << endl;
//     return;
// }

void commit_head_log(string commit_user_message)
{
    ifstream head_file(ROOT_HEAD_FILE);
    if (!head_file.is_open())
    {
        cout << "Error: HEAD file not found. Run 'myg init' first." << endl;
        return;
    }
    stringstream head_buffer;
    head_buffer << head_file.rdbuf();
    string head_content = head_buffer.str();
    if (!head_content.empty() && head_content.back() == '\n')
        head_content.pop_back();

    const string prefix = "ref: refs/heads/";
    if (head_content.substr(0, prefix.size()) != prefix)
    {
        cout << "Error: HEAD is detached or invalid." << endl;
        return;
    }

    string current_branch = head_content.substr(prefix.size());
    ifstream index_file(ROOT_INDEX_FILE);
    if (!index_file.is_open())
    {
        cout << "Error: No files staged. Use 'myg add' first." << endl;
        return;
    }

    stringstream index_buffer;
    index_buffer << index_file.rdbuf();
    string index_content = index_buffer.str();

    if (index_content.empty())
    {
        cout << "Error: Nothing to commit." << endl;
        return;
    }
    string tree_hash = calculateSHA1(index_content);
    string parent_hash = "";
    string branch_file_path = ROOT_SUB_HEAD + current_branch;
    if (fs::exists(branch_file_path))
    {
        ifstream branch_ref(branch_file_path);
        getline(branch_ref, parent_hash);
        branch_ref.close();
    }
    time_t now = time(nullptr);
    string timestamp = to_string(now);
    string author = "you <you@example.com>";

    string commit_content =
        "tree " + tree_hash + "\n" +
        (parent_hash.empty() ? "" : "parent " + parent_hash + "\n") +
        "author " + author + " " + timestamp + "\n" +
        "committer " + author + " " + timestamp + "\n" +
        "\n" +
        commit_user_message + "\n";

    string final_commit_hash = calculateSHA1(commit_content);
    string obj_dir = ROOT_OBJECTS + final_commit_hash.substr(0, 2);
    string obj_file = final_commit_hash.substr(2);

    fs::create_directories(obj_dir);
    ofstream commit_obj(obj_dir + "/" + obj_file);
    commit_obj << commit_content;
    commit_obj.close();

    fs::create_directories(ROOT_SUB_HEAD); // ensure directory exists

    ofstream branch_file(branch_file_path);
    if (!branch_file.is_open())
    {
        cout << "Error: Could not update branch '" << current_branch << "'" << endl;
        return;
    }
    branch_file << final_commit_hash << "\n";
    branch_file.close();

    ofstream clear_index(ROOT_INDEX_FILE, ios::trunc);
    clear_index.close();
    cout << "---------- COMMIT SUCCESSFUL ----------" << endl;
    cout << "[" << current_branch << "] "
         << final_commit_hash.substr(0, 7) << " "
         << commit_user_message << endl;
}
#endif
