#ifndef INDEX_CREATE
#define INDEX_CREATE
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<iostream>

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

#endif