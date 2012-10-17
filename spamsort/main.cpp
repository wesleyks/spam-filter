#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <dirent.h>
#include <sstream>
#include <direct.h>
#include "windows.h"
#include <cmath>
using namespace std;

//first convert to log and add. or just mult
int mailsort(char* dictloc,char* readloc, float spamprob);

int main(int argc, char *argv[])
{
    char* maildir = argv[1];
    char* spamdir = argv[2];
    char* hamdir = argv[3];
    float spamprob = atof(argv[4]);
    char* dictloc = argv[5];

    ifstream* read = new ifstream;
    ifstream* dict=new ifstream(dictloc);
    DIR *sdp;
    struct dirent *directory;

    string line;

    CreateDirectory(spamdir,NULL);
    CreateDirectory(hamdir,NULL);

    sdp = opendir(maildir);
    opendir(spamdir);
    while(directory = readdir(sdp)){
        char* name = directory->d_name;
        string filepath(maildir);
        filepath+="/"+string(name);
        int decision = mailsort(dictloc,(char*)filepath.c_str(),spamprob);
        //cout<< decision<<endl;
        if(decision==1){
            string dest=string(spamdir)+"/"+string(name);
            MoveFile(filepath.c_str(),dest.c_str());
        }
        else{
            string dest=string(hamdir)+"/"+string(name);
            MoveFile(filepath.c_str(),dest.c_str());
        }
        filepath.clear();
    }
/*
    while(getline(*dict,line)){
        cout << line.c_str() <<endl;
    }
*/
    return 0;
}



/*
mailsort determines if a mail is spam or ham. 1 for spam. -1 for ham
*/
int mailsort(char* dictloc,char* readloc, float spamprob){
    ifstream dict(dictloc);


    string dline;
    string line;
    float rsp = log(spamprob);
    float rhp = log(1-spamprob);

    while(getline(dict,dline)){
        string key = strtok((char*)dline.c_str()," ");
        float ksp = atof(strtok(NULL," "));
        float khp = atof(strtok(NULL," "));
        //cout<<key<<" "<<ksp<<" "<<khp<<endl;
        ifstream read(readloc);

        int haz = 0;

        while((getline(read,line))&&(haz==0)){
            /*
            char* tok;
            char* lin=(char *)line.c_str();
            tok = strtok(lin,"   	");
            while((tok!=NULL)&&(haz==0))
            {
                //cout<<tok<<endl;
                if(key.compare(tok)==0)
                    haz = 1;
                tok = strtok(NULL,"   	");

            }
*/
            //cout<<"looking for "<<key<<" in: "<<line<<endl;
            if(strstr(line.c_str(),key.c_str())!=NULL){
                //cout<<"found: "<<key<<endl;
                haz = 1;
            }
            line.clear();
        }
        read.close();
        if(haz==1){
            rsp+=log(ksp);
            rhp+=log(khp);
        }
        else{
            rsp+=log(1-ksp);
            rhp+=log(1-khp);
        }
    }
    if(rsp>rhp)
        return 1;
    else if(rsp<rhp)
        return -1;


    return 0;
}
