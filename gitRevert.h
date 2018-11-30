#ifndef GIT_REVERT
#define GIT_REVERT
#include <string>
#include<iostream>
#include<map>
#include<vector>
using namespace std;

void retCommitObjectTree(string hash,string &treeObj,string &parent);
void deserialize1(string file,string name);
void revert(string hash,string tre,map<string,int> &lis);
void calculateDiff(map<string,int> &newFiles,map<string,int> &oldFiles,map<string,int> &diffFiles);
vector<string> fileToVector(string name) ;
void applyDiff(map<string,int> diffFiles);
void revertMain(string hash);
#endif
