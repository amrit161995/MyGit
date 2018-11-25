#include<stdio.h>
#include<string>
#include<cstring>
#include "generateSHA.cpp"
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

    char* getHash() {
        return hash;
    }

    int getCommit() {
        return commit;
    }

    void setCommit(int c) {
        this->commit = c;
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
    int i;
    vector<Index> lis = indexRead();
    for(i=0;i<lis.size();i++) if(strcmp(path,lis[i].getPath())==0) {flag=1;break;}
    if(flag==0) {
        cout<<"Added to index file"<<endl;
        Index test;
        test.init(mode,hash,stage,path,commit);
        ofstream ofs(".mygit/index",ios::app|ios::binary);
        ofs.write((char*)&test,sizeof(test)); 
        ofs.close();
    }
    else {
        lis[i].init(mode,hash,stage,path,commit);
        remove(".mygit/index");
        ofstream ofs(".mygit/index",ios::app|ios::binary);
        for(int i=0;i<lis.size();i++) {
            ofs.write((char*)&lis[i],sizeof(lis[i])); 
        }
        ofs.close();
    }
}

void commitAll() {
    vector<Index> lis = indexRead();
    for(int i=0;i<lis.size();i++) lis[i].setCommit(1);
    remove(".mygit/index");
    ofstream ofs(".mygit/index",ios::app|ios::binary);
    for(int i=0;i<lis.size();i++) {
        ofs.write((char*)&lis[i],sizeof(lis[i])); 
    }
    ofs.close();
}

string newHash(string fileName) {
    FILE *fptr;
    ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    char* content = new char[(long long)(fileSize)+1];
    // char* content = t;
    string temp=string(bytes.data(), fileSize);
    strcpy(content, temp.c_str());
    // setContent(content);
    // string type="blob";
    string header="blob "+to_string(fileSize);

    string store = header+ " " + content;
    string sha1=generateSHAstring(store);

    return sha1;
}

int check(string name, vector<Index> lis,vector<bool> &v) {
    int msg=0;
    for(int i=0;i<lis.size();i++) {
        if(strcmp(lis[i].getPath(),name.c_str())==0) {
            v[i] = true;
            if(lis[i].getCommit()==0) {
                if(strcmp(newHash(name).c_str(),lis[i].getHash())==0) msg=1;
                else msg=2;
            }
            else msg=3;
            return msg;
        }
    }
    return msg;
}

map< string,vector<string> > getFiles(vector<string> fileList) {
    vector<Index> lis = indexRead();
    map< string,vector<string> > m;
    vector<bool> v(lis.size(),false);
    // if(lis.size()!=0) {
        int msg;
        for(int i=0;i<fileList.size();i++) {
            msg = check(fileList[i],lis,v);
            if(msg==0) m["untracked"].push_back(fileList[i]);
            else if(msg==1) m["tracked"].push_back(fileList[i]);
            else if(msg==2) m["modified"].push_back(fileList[i]);
            else m["committed"].push_back(fileList[i]);
        // }
    }
    for(int i=0;i<v.size();i++) if(v[i]==false) m["deleted"].push_back(lis[i].getPath());
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