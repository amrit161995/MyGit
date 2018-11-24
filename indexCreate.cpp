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
    char mode[10],path[100],hash[40];    
    int stage,commit;

public:
    void init(char* mode,char* hash,int stage,char* path,int commit) {
        strcpy(this->mode,mode);
        strcpy(this->hash,hash);
        strcpy(this->path,path);
        this->stage = stage;
        this->commit = commit;
    }       

    char* getPath() {
        return path;
    }

    void display() {
        cout<<mode<<endl;
        cout<<hash<<endl;
        cout<<stage<<endl;
        cout<<path<<endl;
    }
};

vector<Index> indexRead(){
    //Reading
    ifstream ifs(".mygit/index", ios::binary);
    ifs.seekg(0, std::ios::end);
    int fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    vector<Index> list(fileSize/sizeof(Index));
    ifs.read((char*)list.data(), fileSize);
    ifs.close();
    return list;
}

void indexFill(char* mode,char* hash,int stage,char* path,int commit){
    bool flag=0;
    vector<Index> list = indexRead();
    for(int i=0;i<list.size();i++) if(strcmp(path,list[i].getPath())==0) flag=1;
    if(flag==0) {
        cout<<"Added to index file"<<endl;
        Index test;
        test.init(mode,hash,stage,path,commit);
        ofstream ofs(".mygit/index",ios::app|ios::binary);
        ofs.write((char*)&test,sizeof(test)); 
        ofs.close();
    }    
}

// int main(){
//     // indexFill("1","asd",0,"asd");
//     // indexRead();
//     return 0;
// }