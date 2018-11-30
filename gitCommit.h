#ifndef GIT_COMMIT
#define GIT_COMMIT
#include<stdio.h>
#include<string>
#include <openssl/sha.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include <ctime>

using namespace std;
class Commit
{
    public:
        char type[10]="commit";
        char tree[60]= "";
        char parent[60]="";
        char author[200]="";
        char committer[200]="";
        char message[500]="";
        char * content;

        void Print_Type();
        void Print_Content();
        void setContent(char *con);
        char * getContent();
        string createCommit(string tree,string author,string committer,string message);
};

void serializeCommit(string tree,string author,string committer,string message);
void deserializeCommit(string file);
void listdir(const char *name, int indent, vector<string> &lis);
void commitMain(string author,string commiter,string message);

#endif
