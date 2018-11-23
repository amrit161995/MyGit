#include<stdio.h>
#include<string>
#include <openssl/sha.h>
#include "generateSHA.h"
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

void gitAdd()
{
    FILE *fptr;
  
    // char buffer[512];
    ifstream ifs("abc.txt", ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    string s= string(bytes.data(), fileSize);

    cout<<s<<endl;
    int n=s.length();

    string header="blob "+to_string(s.length())+'\0';
    cout<<header;

    string store=header+s;
    cout<<store;

    string sha1String=generateSHAstring(store);
    cout<<sha1String;

}


int main(){
    string fileName="abc.txt";
    gitAdd();
    return 0;
}