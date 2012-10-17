#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <dirent.h>
#include "tree.h"
#include <sstream>
using namespace std;
//use fstream; GNU functions list files in directory; dirent readir.
//each file would have it's own dictionary and in the end add them all up.
int main(int argc, char *argv[])
{
    char* spamdir = argv[1];
    char* hamdir = argv[2];
    char* dictname = argv[3];

    ofstream* outp = new ofstream;
    ifstream* read = new ifstream;
    DIR *sdp;
    struct dirent *directory;

    int totalspam = 0;
    int totalham = 0;
    node* bigroot = NULL;
    string line;

    sdp = opendir(spamdir);
    while(directory = readdir(sdp)){ //this big messy loop deals with the spam
        node* root = NULL;
        string token;
        stringstream iss;
        //cout << directory->d_name << endl;
        char* name = directory->d_name;
        string filepath(spamdir);
        filepath.append("/");
        filepath.append(name);
        read->open(filepath.c_str());
        if(read->good())
            totalspam++;
        while(getline(*read,line)){
            char* tok;
            char* lin=(char *)line.c_str();
            tok = strtok(lin,"	 ");
            while(tok!=NULL)
            {
                root=incrspam(root,tok);
                tok = strtok(NULL,"	 ");

            }
            iss.clear();
            line.clear();
            //cout<<word<<endl;
        }
        //printinorder(bigroot);
        bigroot = transfer(root,bigroot);
        read->close();
        filepath.clear();
        delete(root);
    }
    sdp = opendir(hamdir);
    while(directory = readdir(sdp)){ //this big messy loop deals with the ham
        node* root = NULL;
        string token;
        stringstream iss;
        //cout << directory->d_name << endl;
        char* name = directory->d_name;
        string filepath(hamdir);
        filepath.append("/");
        filepath.append(name);
        read->open(filepath.c_str());
        if(read->good())
            totalham++;
        while(getline(*read,line)){
            char* tok;
            char* lin=(char *)line.c_str();
            tok = strtok(lin,"   	");
            while(tok!=NULL)
            {
                root=incrham(root,tok);
                tok = strtok(NULL,"  	");

            }
            iss.clear();
            line.clear();
            //cout<<word<<endl;
        }
        //printinorder(bigroot);
        bigroot = transfer(root,bigroot);
        read->close();
        filepath.clear();
        delete(root);
    }

    if(totalham==0)
        totalham++;
    if(totalspam==0)
        totalspam++;
//    printinorder(bigroot);

    outp->open(dictname);
    writedict(outp,bigroot,totalspam,totalham);
    outp->close();

    return 0;
}
