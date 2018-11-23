#include<stdio.h>
#include<string>
#include <openssl/sha.h>
#include "generateSHA.cpp"
// #include<boost.h>

// void gitAdd(string fileName){
//     FILE *textFile,*binFile;
//     char *buffer;
//     textFile=fopen(fileName.c_str(),"r");
//     binFile=fopen("binaryFile.bin","wb");
//     while (fgetc(textFile) != EOF)
//     {
//         fread(buffer, 1, 1, textFile);
//         fwrite(buffer, 1, 1, binFile);
//     }

//     string hashString=generateSHA("binaryFile.bin");
//     cout<<hashString<<endl;

//     fclose(textFile);
//     fclose(binFile);   

// }

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<string>
#include<fstream>
#include<iostream>
#include<stdio.h>

using namespace std;


class TestA
{
    private:
        string type;
        string header;
        string content;
        int length;
        

    public:
        // TestA(){type = "";header="";content=""; length=0; }
        string gitAdd();

        void Print_Type()
        {
            printf("Type : %s",type);
        }

        void Print_Content()
        {
            printf("%s",content);
        }
};


string TestA::gitAdd()
{
    FILE *fptr;
  
    // char buffer[512];
    ifstream ifs("abc.txt", ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    content= string(bytes.data(), fileSize);

    // cout<<content<<endl;
    int length=content.length();
    type="blob";
    header=type+" "+to_string(content.length())+'\0';
    // cout<<header;

    string store=header+content;
    // cout<<store;

    string sha1String=generateSHAstring(store);
    // cout<<sha1String;

return sha1String;
}

void serialize(){
    TestA Test;
    string hash_filename=Test.gitAdd();
    FILE *File = fopen("File.txt","wb");
    // Test.Print();
    fwrite((char *)&Test,sizeof(Test),1,File); //Treats the object as if it is a char array
    fclose(File);

     TestA Test2;
    // FILE *File;
    File = fopen("File.txt","rb");
    fread((char *)&Test2,sizeof(Test2),1,File); //Treats the object as if it is a char array
    Test2.Print_Content();
    fclose(File);
}

// void deserialize(){


// }
int main(){
    // string fileName="abc.txt";
    serialize();
    // deserialize();
    return 0;
}