#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include"gitCommit.cpp"

using namespace std;

string retCommitObjectTree(string hash){
    Commit com;
    FILE *File;
    string treeObj="";

    string directory="";
    string commitname="";

    for(int i=0;i<2;i++)
       directory+=hash[i];

    for(int i=2;i<40;i++)
        commitname+=hash[i];

    string path=".mygit/objects/"+directory+"/"+commitname;
    File = fopen(path.c_str(),"rb");
    fread((char *)&com,sizeof(com),1,File); //Treats the object as if it is a char array
    treeObj=com.tree;
    cout<<treeObj<<endl;
    fclose(File);
    return treeObj;
}

void deserialize(string file){
     
    FILE *File;

    string directory="";
    string blobname="";

    for(int i=0;i<2;i++)
        directory+=file[i];
    // mkdir(".git/objects/"+directory);
    // cout<<directory<<endl;

    for(int i=2;i<40;i++)
        blobname+=file[i];

    string path=".mygit/objects/"+directory+"/"+blobname;
    File = fopen(path.c_str(),"rb");
    fread((char *)&Test2,sizeof(Test2),1,File); //Treats the object as if it is a char array
     
    fclose(File);

 }

void revert(string hash){
    FILE *File;


    



    for(int i=0;i<2;i++)
       directory+=hash[i];

    for(int i=2;i<40;i++)
       treename+=hash[i];

    string pathwd=getenv("PWD");
    string path=pathwd+"/.mygit/objects/"+directory+"/"+treename;
     
    File = fopen(path.c_str(),"rb");

    fread((char *)&t,sizeof(t),1,File); //Treats the object as if it is a char array
    t.Print_Content1();
    fclose(File);
}


int main(){
    
    // cout<<retCommitObjectTree("3fb60bf5ed60d54820671290a8945f7fc29c64f2").c_str();
    return 0;
}