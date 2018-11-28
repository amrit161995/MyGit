#ifndef GIT_STATUS
#define GIT_STATUS
#include<vector>
#include<string>
#include<map>
using namespace std;

void listdir(const char *name, int indent, vector<string> &lis);
void display(map < string,vector<string> > m);
void status();

#endif