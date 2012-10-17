#ifndef tree_h
#define tree_h

using namespace std;

class node
{
public:
    string kee;
    node* parent;
    node* left;
    node* right;
    int spamcount;
    int hamcount;
    node(char* k);
    char* key();
};

node* incrspam(node* root, char* k);
node* incrham(node* root, char* k);
node* addspam(node* bigroot, char* k);
node* addham(node* bigroot, char* k);
void printinorder(node* root);
void writedict(ofstream* nm, node* root,int totalspam,int totalham);
node* transfer(node* root,node* bigroot);
#endif
