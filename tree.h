#ifndef TREE
#define TREE
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
#include "indexCreate.h"
using namespace std;

class Tree
{
        public:
        char treeContent[10000];

        void Print_Content1();
               
        
};

string createTreeObject(char *path1,vector<Index> list);
void deserializeTree(string file);

#endif
