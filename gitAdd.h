#ifndef GIT_ADD
#define GIT_ADD
#include <string>
#include<iostream>

using namespace std;

class TestA
{
    public:
        char type[10];
        char header[50];
        char *content;
        int length;
        
        // TestA(){type = "";header="";content=""; length=0; }
        string gitAdd(string filename);

        void Print_Type();
       	void Print_Content();
        void setContent(char *con);
        char * getContent();
};

void serialize(string filename);
string deserialize(string str);

#endif
