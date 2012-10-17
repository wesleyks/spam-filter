#include <iostream>
#include <fstream>
#include <cstring>
#include "tree.h"
#include <cmath>

using namespace std;
/*
initialize node
*/
node::node(char* k)
{
    // = new char[500];
    kee.assign(k);
    //strcpy(key,k);
    spamcount = 0;
    hamcount = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
}
/*
key returns a char* of the kee member in node
*/
char* node::key(){
    return (char*)kee.c_str();
}
/*
incrspam adds spam to the tree. makes sure the key is only counted once per email
*/
node* incrspam(node* root, char* k)
{
    if(root==NULL)
    {
        root = new node(k);
        root->spamcount++;
    }
    else if(strcasecmp(k,root->key())==0){
        if(root->spamcount==0)
            root->spamcount++;
    }
    else if(strcasecmp(k,root->key())==-1)
        root->left = incrspam(root->left,k);
    else
        root->right = incrspam(root->right,k);
    return root;
}
/*
incrham adds spam to the tree. makes sure the key is only counted once per email
*/
node* incrham(node* root, char* k)
{
    if(root==NULL)
    {
        root = new node(k);
        root->hamcount++;
    }
    else if(strcasecmp(k,root->key())==0){
        if(root->hamcount==0)
            root->hamcount++;
    }
    else if(strcasecmp(k,root->key())==-1)
        root->left = incrham(root->left,k);
    else
        root->right = incrham(root->right,k);
    return root;
}
/*
addspam is the same as incrspam but without the count once restriction
*/
node* addspam(node* bigroot, char* k)
{
    if(bigroot==NULL)
    {
        bigroot = new node(k);
        bigroot->spamcount++;
        //cout<<"created: "<<k<<endl;
    }
    else if(strcasecmp(k,bigroot->key())==0){
            bigroot->spamcount++;
            //cout<<"added: "<<k<<endl;
    }
    else if(strcasecmp(k,bigroot->key())==-1){
        bigroot->left = addspam(bigroot->left,k);
        //cout<<"left: "<<k<<endl;
    }
    else{
        bigroot->right = addspam(bigroot->right,k);
        //cout<<"right: "<<k<<endl;
    }
    return bigroot;
}
/*
addham is the same as incrham but without the count once restriction
*/
node* addham(node* bigroot, char* k)
{
    if(bigroot==NULL)
    {
        bigroot = new node(k);
        bigroot->hamcount++;
    }
    else if(strcasecmp(k,bigroot->key())==0)
            bigroot->hamcount++;
    else if(strcasecmp(k,bigroot->key())==-1)
        bigroot->left = addham(bigroot->left,k);
    else
        bigroot->right = addham(bigroot->right,k);
    return bigroot;
}

/*
prints the words in root in alphanumeric order
*/
void printinorder(node* root)
{
    if(root!=NULL)
    {
        printinorder(root->left);
        cout << root->key() << endl;
        printinorder(root->right);
    }
}
/*
writedict creates the dictionary file.
*/
void writedict(ofstream* outp, node* root,int totalspam,int totalham)
{
    if(root!=NULL)
    {
        writedict(outp,root->left,totalspam,totalham);
        if(root->spamcount==0)  //pseudocount!!!
            root->spamcount++;
        if(root->hamcount==0)
            root->hamcount++;
        if(abs((float)(root->spamcount-root->hamcount))>1)
            *outp << root->key() <<" "<< (float)(root->spamcount)/(float)totalspam <<" "<<(float)(root->hamcount)/(float)totalham<<endl;
        writedict(outp,root->right,totalspam,totalham);
    }
}

/*
adds the counts from root to bigroot
*/
node* transfer(node* root,node* bigroot){
    if(root!=NULL)
    {
        bigroot = transfer(root->left,bigroot);
        if(root->hamcount!=0){
            bigroot=addham(bigroot, root->key());
            //cout<<root->key()<< ": ham" <<endl;
        }
        if(root->spamcount!=0){
            bigroot=addspam(bigroot, root->key());
            //cout<<root->key()<< ": spam" <<endl;
        }
        bigroot = transfer(root->right,bigroot);
    }
    return bigroot;
}


