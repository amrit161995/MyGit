#ifndef GIT_ADD
#define GIT_ADD
#include <string>
#include<iostream>
#endif

using namespace std;

class TestA
{
    private:
        string type="";
        string header="";
        char *content;
        int length;
        

    public:
        // TestA(){type = "";header="";content=""; length=0; }
        string gitAdd();

        void Print_Type()
        {
            cout<<type<<endl;
        }

        void Print_Content()
        {
            int len = sizeof(content)/sizeof(char);
            // cout<<"len: "<<len<<endl;
            cout<<content;
        }

        void setContent(char *con){
            content=con;
        }

        char * getContent(){
            return content;
        } 
};

void serialize();
void deserialize(string str);