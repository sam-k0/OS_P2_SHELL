#include <iostream>
#include "main.h"
#include "string.h"
#define LINELENGTH 32
using namespace std;

int getArgs(string line, char** args, int *directCall)
{
    // Process line
    int argIndex = 0;
    int length = line.size();
    char* currline = &line[0];
    char cchr; // Holds curr char
    string currarg = "";

    for(int i = 0; i < length; i ++)
    {
        cchr = currline[i];
        if(cchr == ' ')
        {
            // deep copy string and save to arg char* array
            char* temp = new char[currarg.size() + 1];
            memcpy(temp, currarg.c_str(), currarg.size() + 1);
            args[argIndex] = temp;
            argIndex ++;
            currarg = "";
        }
        else
        {
            currarg += cchr;
        }


        if(i == length-1 && cchr != ' ') // Nimmt das letzte argument mit, falls nicht mit ' ' beendet wurde
        {
            // deep copy string and save to arg char* array
            char* temp = new char[currarg.size() + 1];
            memcpy(temp, currarg.c_str(), currarg.size() + 1);
            args[argIndex] = temp;
            argIndex ++;
            currarg = "";
        }
    }
    // Determine if directCall
    string firstArg = string(args[0]);
    if(firstArg.at(firstArg.length()-1) == '&')
    {
        cout << "Using directCall!"<<endl;
        *directCall = 1;
        firstArg.pop_back();
        // Deep copy again...
        char* temp = new char[firstArg.size()+1];
        memcpy(temp, firstArg.c_str(), firstArg.size() +1 );
        args[0] = temp;

    }

    return argIndex;
}


void printPids(vector<pid_t> *pidvec)
{
    for(int i = 0; i < pidvec->size(); i ++)
    {
        cout << pidvec->at(i) << endl;
    }

}

void addPidvec(vector <pid_t> *pidvec, pid_t _pid)
{
    pidvec->push_back(_pid);
}

int main()
{
    cout <<"Parent PID: "<<getpid() <<endl;
    pid_t parentpid = getpid();
    /// Setup
    string cmdline;
    char *args[64]; // Cmd line arguments
    int argIndex = 0;
    vector<pid_t> *vec_pids = new vector<pid_t>();
    int directCall = 0;

    while(1)
    {
        argIndex = 0;
        cmdline = "";
        directCall = 0;
        /// User input
        cout << "\nCommand: \n";
        getline(std::cin, cmdline);

        /// Process line
        argIndex = getArgs(cmdline, args, &directCall);

        /// Print pids
        for(int i = 0; i < vec_pids->size(); i ++)
        {
            cout <<"Vec Pos "<< i <<" - " <<vec_pids->at(i) << endl;
        }

        /// check for logout before forking

        if(string(args[0]) == "logout")
        {
            cout << "Do you really want to quit? (y/n)"<<endl;
            char r;
            cin >> r;
            if(r == 'y')
            {
                cout << "Exiting."<<endl;
                exit(0);
            }
            else if(r == 'n')
            {
                cout << "Logout cancelled"<<endl;
            }
        }

        /// Real forking here
        pid_t pid = fork();
        int status;

        /// Pid vec thighs
        if(pid != parentpid)
        {
            vec_pids->push_back(pid);
        }

        /// End pid vec

        if(pid < 0) // Check if forking successful
        {
            // Error, abort
            cout << "ERROR: Could not fork!"<< endl;
            exit(1);
        }
        else if(pid == 0) // Fork success, new process created
        {
            ///Print args array

            /*int _a = 0;
            cout << "Trying to create progress with args:" << endl;
            do
            {
                // Loop all entries
                cout << args[_a] << endl;
                _a ++;

            }
            while(_a != argIndex);*/

            /// Execute shell with args

            cout << "Executing process with pid: " << getpid() << endl;
            if(execvp(*args, args) < 0) // Try to execute shell with argv array
            {
                // Error creating / executing the thing
                cout << "Could not execute shell. "<< endl;
                exit(2);
            }
        }
        else
        {
            if(!directCall)
            {
                while(wait(&status) != pid)
                {
                    // Waitig
                }
            }
        }
        cout << "End of process with Pid " << getpid() <<endl;

    }
    return 0;
}




/*int _a = 0;
            cout << "Trying to create progress with args:" << endl;
            do
            {
                // Loop all entries
                cout << args[_a] << endl;
                _a ++;

            }
            while(_a != argIndex);*/


/***

/
    int argIndex = 0;
    int length = cmdline.size();
    char* currline = &cmdline[0];
    char cchr; // Holds curr char
    string currarg = "";

    for(int i = 0; i < length; i ++)
    {
        cchr = currline[i];
        if(cchr == ' ')
        {
            // deep copy string and save to arg char* array
            char* temp = new char[currarg.size() + 1];
            memcpy(temp, currarg.c_str(), currarg.size() + 1);
            args[argIndex] = temp;
            argIndex ++;
            currarg = "";
        }
        else
        {
            currarg += cchr;
        }


        if(i == length-1 && cchr != ' ') // Nimmt das letzte argument mit, falls nicht mit ' ' beendet wurde
        {
            // deep copy string and save to arg char* array
            char* temp = new char[currarg.size() + 1];
            memcpy(temp, currarg.c_str(), currarg.size() + 1);
            args[argIndex] = temp;
            argIndex ++;
            currarg = "";
        }
    } */












