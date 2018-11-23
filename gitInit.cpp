#include<vector>
#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>    
#include<string.h>
#include<errno.h>

using namespace std;

void gitinit(){
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    // cout<<cwd<<endl;
    // DIR *dir=opendir(".git");
    struct stat buf;

    if(stat(".mygit",&buf)==0 && S_ISDIR(buf.st_mode)){
        cout<<"Reinitialising the repository"<<endl;
        // closedir(dir);
    }
    else{
    	chdir(".");
        int check=mkdir(".mygit",0755);
        if(check==-1){
            cout<<"Error initialising the Repository"<<endl;
        }
        else{
        	mkdir(".mygit/branches",0755);
        	mkdir(".mygit/info",0755);
        	mkdir(".mygit/objects",0755);
        	mkdir(".mygit/refs",0755);
        	mkdir(".mygit/objects/info",0755);
        	mkdir(".mygit/objects/pack",0755);
        	mkdir(".mygit/refs/heads",0755);
        	mkdir(".mygit/refs/tags",0755);
        	open(".mygit/HEAD", O_RDWR | O_CREAT, 0644);
        	open(".mygit/config", O_RDWR | O_CREAT, 0644);
        	open(".mygit/description", O_RDWR | O_CREAT, 0644);
        	open(".mygit/info/exclude", O_RDWR | O_CREAT, 0644);

        	fstream fs;
  			fs.open (".mygit/HEAD");
  			fs << "ref: refs/heads/master";
  			fs.close();
            // cout<<"Initialised new repository"<<endl;

            // fstream fs;
  			fs.open (".mygit/description");
  			fs << "Unnamed repository; edit this file 'description' to name the repository.";
  			fs.close();
            // cout<<"Initialised new repository"<<endl;

            // fstream fs;
  			fs.open (".mygit/config");
  			fs << "[core]\n	repositoryformatversion = 0\n	filemode = true\n	bare = false\n	logallrefupdates = true";
  			fs.close();

  			fs.open (".mygit/info/exclude");
  			fs << "# git ls-files --others --exclude-from=.git/info/exclude\n# Lines that start with '#' are comments.\n# For a project mostly in C, the following would be a good set of\n# exclude patterns (uncomment them if you want to use them):\n# *.[oa]\n# *~";
  			fs.close();

            cout<<"Initialised New Repository"<<endl;
        }
    }
    
}

int main(int args,char *argv[]){
	// cout<<argv[1];
	if (strcmp("init",argv[1])==0)
    	gitinit();
    return 0;
}