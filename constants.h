#ifndef MYG_CONFIG_H
#define MYG_CONFIG_H

// directory paths
#define ROOT_DIR ".myg"
#define ROOT_OBJECTS ".myg/objects"
#define ROOT_REF ".myg/refs"
#define ROOT_SUB_HEAD ".myg/refs/heads"

// directory files
#define ROOT_HEAD_FILE ".myg/HEAD"

// user commands
#define start "start"             // creates a new directory if a second argument is given then that will be the default branch
#define shootoff "shootoff"       // creates a new branch
#define lock "lock"               // moves to a particular branch
#define splash "splash"           // to merge
#define bay "bay"                 // lists all the branches
#define log "logs"                // list the commit history
#define mount "mount"             // add all the files to mount
#define commit "commit"           // to write a commit messgae
#define release "release"         // to push the changes
#define status "status"           // to check the staged files and code
#define instruments "instruments" // to show and guide the user

// branch access
#define secure "secure" // this means only the root user can access it no one else and if second argument any branch name is give it will secure and lock that instead

// default branches
#define default "production"
#define standby "development"

#endif