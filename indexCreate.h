#ifndef INDEX_CREATE
#define INDEX_CREATE
#include<stdio.h>
#include<string>
#include<cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<map>
using namespace std;

class Index
{
    public:
        char mode[10],path[100],hash[40];    
        int stage,commit;
        
        void init(char* mode,char* hash,int stage,char* path,int commit);
        char* getPath();
        char* getHash();    
        int getCommit();
        void setCommit(int c);
        void display();
};


vector<Index> indexRead();
void indexFill(char* mode,char* hash,int stage,char* path,int commit);
void commitAll();
string newHash(string fileName);
int check(string name, vector<Index> lis,vector<bool> &v);
map< string,vector<string> > getFiles(vector<string> fileList);

#endif
