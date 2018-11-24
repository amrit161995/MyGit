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

using namespace std;

#define debug(x) cout<<"Checkpoint "<<x<<endl

class Index
{
    char mode[10];
    char hash[40];
    int stage;
    char path[100];   

public:
    void init(char* mode,char* hash,int stage,char* path) {
        strcpy(this->mode,mode);
        strcpy(this->hash,hash);
        strcpy(this->path,path);
        this->stage = stage;
    }       

    void display() {
        cout<<mode<<endl;
        cout<<hash<<endl;
        cout<<stage<<endl;
        cout<<path<<endl;
    }
};

void indexFill(char* mode,char* hash,int stage,char* path){
    Index test;
    test.init(mode,hash,stage,path);
    ofstream ofs(".mygit/index",ios::app|ios::binary);
    ofs.write((char*)&test,sizeof(test)); 
    ofs.close();
}

void indexRead(){
    //Reading
    ifstream ifs(".mygit/index", ios::binary);
    ifs.seekg(0, std::ios::end);
    int fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    vector<Index> list(fileSize/sizeof(Index));
    ifs.read((char*)list.data(), fileSize);
    ifs.close();

    //Displaying
    debug(list.size());
    for(int i=0;i<list.size();i++) {
        debug(i);
        list[i].display();
        cout<<endl;
    }
}

// int main(){
//     indexFill("1","asd",0,"asd");
//     indexRead();
//     return 0;
// }