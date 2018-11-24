#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "indexCreate.cpp"
#include<map>

void listdir(const char *name, int indent, vector<string> &lis)
{
    DIR *dir;
    struct dirent *entry;

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
            string path = pa + "/" + entry->d_name;
            lis.push_back(path);
            // printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

int main() {
    vector<string> lis;
    listdir(".", 0,lis);
    cout<<lis.size()<<endl;
    map< string,vector<string> > m = getFiles(lis);
    cout<<"Untracked"<<endl;
    for(int j=0;j<m["untracked"].size();j++) cout<<m["untracked"][j]<<endl;
    cout<<endl;
    cout<<"Tracked (Added but not committed)"<<endl;
    for(int j=0;j<m["tracked"].size();j++) cout<<m["tracked"][j]<<endl;
    cout<<endl;
    cout<<"Committed"<<endl;
    for(int j=0;j<m["committed"].size();j++) cout<<m["committed"][j]<<endl;
    cout<<endl;
    // }
    return 0;
}