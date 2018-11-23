#include<stdio.h>
#include<string>
#include <openssl/sha.h>
#include "generateSHA.h"
// #include<boost.h>

void gitAdd(string fileName){
    FILE *textFile,*binFile;
    char *buffer;
    textFile=fopen(fileName.c_str(),"r");
    binFile=fopen("binaryFile.bin","wb");
    while (fgetc(textFile) != EOF)
    {
        fread(buffer, 1, 1, textFile);
        fwrite(buffer, 1, 1, binFile);
    }

    string hashString=generateSHA("binaryFile.bin");
    cout<<hashString<<endl;

    fclose(textFile);
    fclose(binFile);   

}

int main(){
    string fileName="abc.txt";
    gitAdd(fileName);
    return 0;
}