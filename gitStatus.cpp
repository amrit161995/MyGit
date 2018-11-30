#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "indexCreate.h"
#include "gitStatus.h"
#include<map>

vector<string> splitStrings(string str, char dl)
{
    string word = "";
    str = str + dl;
    int l = str.size();
    vector<string> substr_list;
    for (int i = 0; i < l; i++) {
        if (str[i] != dl) {
            if(str[i]=='\\') {
                i++;
            }
            word = word + str[i];
        }
        else {
            if ((int)word.size() != 0)
                substr_list.push_back(word);
            word = "";
        }
    }
    return substr_list;
}

void listdir(const char *name, int indent, vector<string> &lis)
{
    DIR *dir;
    struct dirent *entry;
    // cout<<name<<endl;

    if (!(dir = opendir(name)))        
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR and entry->d_name[0]!='.') {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            // printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2,lis);
        } 
        else if(entry->d_name[0]!='.'){
            char cwd[1024];
            getcwd(cwd,sizeof(cwd));
            string pa(cwd);
            vector<string> na = splitStrings(name,'/');
            string path;
            if(na.size()>1) path = pa + "/" + na[na.size()-1] + "/" + entry->d_name;
            else path = pa + "/" + entry->d_name;
            lis.push_back(path);
            // printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

void display(map < string,vector<string> > m) {
    cout<<"On branch master"<<endl;
    if(m["committed"].size()==0) cout<<endl<<"Initial commit"<<endl<<endl;
    if(m["tracked"].size()!=0) {
        cout<<"Changes to be committed:"<<endl;
        cout<<"  (use \"git rm --cached <file>...\" to unstage)"<<endl<<endl;
        for(int j=0;j<m["tracked"].size();j++) cout<<"\tnew file:   "<<m["tracked"][j]<<endl;
        cout<<endl;
    }
    if(m["modified"].size()!=0 or m["deleted"].size()!=0) {
        cout<<"Changes not staged for commit:"<<endl;
        cout<<"  (use \"mygit add <file>...\" to update what will be committed)"<<endl;
        cout<<"  (use \"mygit checkout -- <file>...\" to discard changes in working directory)"<<endl<<endl;
        for(int j=0;j<m["modified"].size();j++) cout<<"\tmodified:   "<<m["modified"][j]<<endl;
        for(int j=0;j<m["deleted"].size();j++) cout<<"\tdeleted:   "<<m["deleted"][j]<<endl;
        cout<<endl;
    }
    if(m["untracked"].size()!=0) {
        cout<<"Untracked files:"<<endl;
        cout<<"  (use \"mygit add <file>...\" to include in what will be committed)"<<endl<<endl;
        for(int j=0;j<m["untracked"].size();j++) cout<<"\t"<<m["untracked"][j]<<endl;
        cout<<endl;
    }
    if(m["tracked"].size()==0)
        if(m["untracked"].size()!=0)
            cout<<"nothing added to commit but untracked files present (use \"mygit add\" to track)"<<endl;
        else
            cout<<"nothing to commit, working directory clean"<<endl;
}

void status() {
    vector<string> lis;
    listdir(".", 0,lis);
    map< string,vector<string> > m = getFiles(lis);
    display(m);
}

// int main() {
//     status();
// }