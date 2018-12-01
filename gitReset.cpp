#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sstream>
#include <fstream>
#include "gitAdd.h"
#include "tree.h"
#include "gitCommit.h"
#include "gitStatus.h"
#include "indexCreate.h"
#include "generateSHA.h"
#define DEBUG(x) std::cout<<"checkpoint"<<x<<endl

using namespace std;
string globDir="";
string globDir1="";
vector<Index> readV;

vector<string> splitString(string s,char delim){
    vector<string> v;
    istringstream ss(s);
    string token;
    while(getline(ss, token, delim)) {
        v.push_back(token);
    }
    return v;
}

void getRPath(){
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
            globDir=getcwd(cwd,sizeof(cwd));
            globDir1=globDir;
            // cout<<pathname<<endl;
            return;
        } 
    }
    chdir("..");
    getRPath();
    closedir(dir);
    
}

void reset(string hash){
    if(hash!="") {
        Tree tr;
        FILE *File;
        // DEBUG("7");
        string directory="";
        string objectname="";

        for(int i=0;i<2;i++)
           directory+=hash[i];

        for(int i=2;i<40;i++)
            objectname+=hash[i];

        string path=".mygit/objects/"+directory+"/"+objectname;
        // cout<<path<<endl;
        File = fopen(path.c_str(),"rb");
        // DEBUG("9");
        fread((char *)&tr,sizeof(tr),1,File); //Treats the object as if it is a char array
        // DEBUG("8");
        // cout<<tr.treeContent<<endl;
        string content(tr.treeContent);
        vector<string> files = splitString(content,'\n');

        for(int i=0;i<files.size();i++) {
            vector<string> p = splitString(files[i],' ');
            // DEBUG("6");
            if(p[1]=="blob") {
                // cout<<p[1]<<endl;
                // DEBUG("1");
                string fPath=p[3];
                fPath.pop_back();
                // cout<<fPath<<endl;
                string fContent=deserialize(p[2]);
                string con(fContent);
                std::ofstream ofs;
                ofs.open (fPath, std::ofstream::out);
                ofs << fContent;
                ofs.close();
                // DEBUG("3");
            }
     else if(p[1]=="tree") {
                // DEBUG("2");
                string dir=p[3];
                dir.pop_back();
                // // cout<<globDir<<endl;
                // // globDir=globDir+"/"+dir;
                mkdir(dir.c_str(),0755);
                // DEBUG("4");
                // // int rc=chdir(dir.c_str());
                // // if(rc<0) cout<<"Could not change"<<endl;
                // DEBUG("5");
                reset(p[2]);
            }
        }
        fclose(File);
    }
}

string retCommitObjectTree(string hash){
    string treeObj="";
    if(hash!="0000000000000000000000000000000000000000") {
        Commit com;
        FILE *File;
        treeObj="";
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
        // cout<<treeObj<<endl;
        fclose(File);
        
    }
    return treeObj;
}

int remove_directory(string globDir)
{
   DIR *d = opendir(globDir.c_str());
   size_t path_len = strlen(globDir.c_str());
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..") || !strcmp(p->d_name, ".mygit"))
          {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2; 
          buf = (char*)malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", globDir.c_str(), p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = remove_directory(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }

   if (!r)
   {
      r = rmdir(globDir.c_str());
   }

   return r;
}

void setLog(string hash){

struct stat buf;
    if (stat(".mygit/log", &buf) != -1)
    {
    	vector <string> vecOfStrs;
    	vector <string> vecResult;
        // cout<<"hello";
        std::ifstream in(".mygit/log");
        string str;
		while (std::getline(in, str))
			{
				// Line contains string of length > 0 then save it in vector
				if(str.size() > 0)
					vecOfStrs.push_back(str);
			}


			for(int i=0;i<vecOfStrs.size();i++){
				string line = vecOfStrs[i]; 
			    
			    vector <string> tokens; 
			    stringstream check1(line); 
			    string intermediate; 
			     
			    while(getline(check1, intermediate, '|')) 
			    { 
			        tokens.push_back(intermediate); 
			    } 
			    vecResult.push_back(vecOfStrs[i]);
			    if(tokens[1]==hash)
			    	break;
			}
				std::ofstream ofs;
		    	 ofs.open (".mygit/log", std::ofstream::out);
			for(int i=0;i<vecResult.size();i++){
				
		    	 ofs << vecResult[i]<<endl;
		    	 
			}
			ofs.close();
			
	}
			      
}

void gitResetMain(string hash1){
	getRPath();
    string hash=retCommitObjectTree(hash1);
    // cout<<hash;
    // remove_directory(globDir1.c_str());
    unlink(".mygit/index");
    addAll(".");
    setLog(hash1);
    reset(hash);
}

// int main(){
//     string hash;
//     cin>>hash;
//     gitResetMain(hash);
//     return 0;
// }
