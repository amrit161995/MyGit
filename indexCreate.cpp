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
#include<map>

using namespace std;

#define debug(x) cout<<"Checkpoint "<<x<<endl

class Index
{
    

public:
    char mode[10],path[100],hash[40];    
    int stage,commit;
    
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

    int getCommit() {
        return commit;
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
    vector<Index> ls;
    ifstream ifs(".mygit/index", ios::binary);
    if(ifs) {
        ifs.seekg(0, std::ios::end);
        int fileSize = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        vector<Index> list(fileSize/sizeof(Index));
        ifs.read((char*)list.data(), fileSize);
        ls = list;
    }
    ifs.close();
    // ls = list;
    return ls;
}

void indexFill(char* mode,char* hash,int stage,char* path,int commit){
    bool flag=0;
    vector<Index> lis = indexRead();
    for(int i=0;i<lis.size();i++) if(strcmp(path,lis[i].getPath())==0) flag=1;
    if(flag==0) {
        cout<<"Added to index file"<<endl;
        Index test;
        test.init(mode,hash,stage,path,commit);
        ofstream ofs(".mygit/index",ios::app|ios::binary);
        ofs.write((char*)&test,sizeof(test)); 
        ofs.close();
    }    
}

int check(string name, vector<Index> lis) {
    int msg=0;
    for(int i=0;i<lis.size();i++) {
        if(strcmp(lis[i].getPath(),name.c_str())==0) {
            if(lis[i].getCommit()==0) msg=1;
            else msg=2;
            return msg;
        }
    }
    return msg;
}

map< string,vector<string> > getFiles(vector<string> fileList) {
    vector<Index> lis = indexRead();
    map< string,vector<string> > m;
    if(lis.size()!=0) {
        int msg;
        for(int i=0;i<fileList.size();i++) {
            msg = check(fileList[i],lis);
            // cout<<msg<<endl;
            if(msg==0) m["untracked"].push_back(fileList[i]);
            else if(msg==1) m["tracked"].push_back(fileList[i]);
            else m["committed"].push_back(fileList[i]);
        }
    }
    return m;
}

// int main(){
//     // indexFill("1","asd",0,"asd");
//     vector<Index> ls = indexRead();
//     for(int i=0;i<ls.size();i++) {
//         ls[i].display();
//     }
//     return 0;
// }