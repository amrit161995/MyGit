#include<stdio.h>
#include<string>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;


class Index
{
   public:
        string mode="";
        string hash="";
        int stage=0;
        string path="";
        

    // public:
    //     // TestA(){type = "";header="";content=""; length=0; }
    //     // string gitAdd();

       


       
};



        void indexFill(string mode,string hash,int stage,string path,int count){
            //cout<<"hello";
            vector <Index> list; 
            // Index test;
            // test.mode="test";
            // test.hash="test";
            // test.stage=0;
            // test.path="/";
            // list.push_back(test);
               FILE *File;
            //  File=fopen(".mygit/index","wb");
            // // Test.Print_Content();
            // // cout<<Test.getContent();
            // fwrite((char *)&list[0],list.size()*sizeof(Index),1,File); 

            
            File = fopen(".mygit/index","rb");

             fseek (File , 0 , SEEK_END);
                size_t lSize = ftell (File);
                rewind (File);
            fread((char *)&list[0],sizeof(Index)*count,1,File);

            // Index Test;
            
            // Test.mode=mode;
            // Test.hash=hash;
            // Test.stage=stage;
            // Test.path=path;

            // list.push_back(Test);
            // File=fopen(".mygit/index","wb");
            // // Test.Print_Content();
            // // cout<<Test.getContent();
            // fwrite((char *)&list,sizeof(list),1,File); //Treats the object as if it is a char array
            // fclose(File);

            
        }

         void indexRead(string file){
             // Index Test2;
             FILE *File;
              vector <Index> list; 
             
            File = fopen(".mygit/index","rb");
            fread((char *)&list,sizeof(list),1,File); //Treats the object as if it is a char array
            // Test2.Print_Content();
            fclose(File);

         }


int main(){
    // string fileName="abc.txt";
    indexFill("1","asd",0,"asd",1);
    return 0;
}