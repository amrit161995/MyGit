#ifndef GIT_RESET
#define GIT_RESET
#include <string>
#include<iostream>
#include <vector>

using namespace std;

vector<string> splitString(string s,char delim);
void getRPath();
void reset(string hash);
string retCommitObjectTree(string hash);
int remove_directory(string globDir);
void gitResetMain(string hash1);
void setLog(string hash);

#endif