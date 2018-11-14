#include<vector>
#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
#include<errno.h>

using namespace std;

void gitinit(){
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    // cout<<cwd<<endl;
    // DIR *dir=opendir(".git");
    struct stat buf;

    if(stat(".git",&buf)==0 && S_ISDIR(buf.st_mode)){
        cout<<"Reinitialising the repository"<<endl;
        // closedir(dir);
    }
    else{
        int check=mkdir(".git",755);
        if(check==-1){
            cout<<"Error initialising the repository"<<endl;
        }
        else{
            cout<<"Initialised new repository"<<endl;
        }
    }
    
}

int main(){
    gitinit();
    return 0;
}