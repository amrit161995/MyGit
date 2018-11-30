#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include<stdlib.h>

// #include "indexCreate.cpp"
#include "indexCreate.h"
#include "generateSHA.h"
#include "gitAdd.h"
#include "gitCheckout.h"
using namespace std;

string pathname;

string deserial(string hash){
    TestA Test2;

    string directory="";
    string blobname="";

    for(int i=0;i<2;i++)
        directory+=hash[i];

    for(int i=2;i<40;i++)
        blobname+=hash[i];

     string path=".mygit/objects/"+directory+"/"+blobname;
     
     string te;
     std::ifstream binFile(path.c_str(), std::ios::in | std::ios::binary);
           if(binFile.is_open())
           {
              size_t len = 0;
              binFile.read((char*)&len, sizeof(len));
              te.resize(len);
              binFile.read((char*)&te[0], len);
           }
      
     return te;
 }


void read(){
    vector<Index> ind=indexRead();
    for(int i=0;i<ind.size();i++){
        cout<<ind[i].path<<"            "<<endl;
        cout<<ind[i].hash<<"FOUND"<<endl;
    }
}

void checkout(string filename){
    // cout<<filename<<endl;
    char cwd[PATH_MAX];
    // string pathname=getcwd(cwd,sizeof(cwd));
    // pathname=pathname+"/"+filename;
    // cout<<filename<<endl;
    vector<Index> ind=indexRead();
    string fileHash;
    for(int i=0;i<ind.size();i++){
        if(strcmp(ind[i].path,filename.c_str())==0){
            fileHash=ind[i].hash;
            // cout<<"here"<<endl;
            string temp=deserial(fileHash);
            string con(temp);
            std::ofstream ofs;
            ofs.open (filename, std::ofstream::out);
            ofs << con;
            ofs.close();
            break;
        }
    }

    // cout<<pathname<<"  "<<fileHash<<endl;
    
}

void getRootPath(){
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir("."))){
        cout<<"Could not open the directory"<<endl;
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // cout<<entry->d_name<<endl;
        if (strcmp(entry->d_name,".mygit")==0) {
            // cout<<"FOUND THE FOLDER"<<endl;
            char cwd[PATH_MAX];
            pathname=getcwd(cwd,sizeof(cwd));
            // cout<<pathname<<endl;
            return;
        } 
    }
    chdir("..");
    getRootPath();
    closedir(dir);
    
}

void checkoutAll(const char* pathname){
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(pathname)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || 
                strcmp(entry->d_name, "..") == 0 || 
                strcmp(entry->d_name, ".mygit") == 0 || 
                strcmp(entry->d_name, ".git") == 0)

                continue;

            snprintf(path, sizeof(path), "%s/%s", pathname, entry->d_name);
            // cout<<entry->d_name<<endl;
            // cout<<entry->d_type<<endl;
            // string sPath(path);
            checkoutAll(path);
        } 
        else {
            string s(pathname);
            string p=s+"/"+entry->d_name;
            checkout(p);
        }
    }
    closedir(dir);
}

void checkoutMain(){
    getRootPath();
    checkoutAll(pathname.c_str());
}

// int main(){
   
//     checkoutMain();
//     // read();
//     return 0;
// }