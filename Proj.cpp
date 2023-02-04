#include <bits/stdc++.h>
using namespace std;

// Represents a node of an general tree
struct Node
{
    string key;
    vector<Node *> child;
    Node *parent;
    Node(string name){
		parent=NULL;
		key=name;
	}
	Node(){
		parent=NULL;
	}
	Node(Node *a){
		this->parent=a->parent;
		this->key=a->key;
		this->child=a->child;
	}
};
// Function to create a new tree node
Node *newNode(string key)
{
    Node *temp = new Node;
    temp->key = key;
    return temp;
}
struct Node *root = newNode("Users");

Node *Search(Node *root, string key)
{
    // Standard level order traversal code
    // using queue
    bool f=false;
    queue<Node *> q; // Create a queue
    struct Node *p;
    q.push(root); // Enqueue root
    while (!q.empty())
    {
        int n = q.size();
        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            p = q.front();
            q.pop();
            if (p->key == key)
            {
                f=true;
                return p;
            }
            // Enqueue all children of the dequeued item
            for (int i = 0; i < p->child.size(); i++) {
                if (p->child[i]!=NULL) {
                    q.push(p->child[i]);
                }
                
            }
            n--;
        }
    }
    if (f==false)
        cout<<"File not found"<<endl;
}

void create_file(string s)
{
    int k;
    for (int j = s.length() - 1; j >= 0; j--)
    {
        if (s[j] == '/')
        {
            k = j;
            break;
        }
    }
    string temp1 = s.substr(k + 1, s.length() - k - 1);
    s.erase(k, s.length() - k);
    k = 0;
    for (int j = s.length() - 1; j >= 0; j--)
    {
        if (s[j] == '/')
        {
            k = j;
            break;
        }
    }
    string temp2 = s.substr(k + 1, s.length() - k - 1);
    s.erase(k, s.length() - k);
    Node *p = Search(root, temp2);
    if (p->child.size()!=0 && p->child[0]==NULL)
        cout<<"Error! Can't create a file in a file"<<endl;
    else 
    {
        (p->child).push_back(newNode(temp1));
        int n = p->child.size();
        p->child[n - 1]->parent = p;
        p = p->child[n - 1];
        p->child.push_back(NULL);
    } 
}

void create_dir(string s)
{
    int k;
    for (int j = s.length() - 1; j >= 0; j--)
    {
        if (s[j] == '/')
        {
            k = j;
            break;
        }
    }
    string temp1 = s.substr(k + 1, s.length() - k - 1);
    s.erase(k, s.length() - k);
    k = 0;
    for (int j = s.length() - 1; j >= 0; j--)
    {
        if (s[j] == '/')
        {
            k = j;
            break;
        }
    }
    string temp2 = s.substr(k + 1, s.length() - k - 1);
    s.erase(k, s.length() - k);
    Node *p = Search(root, temp2);
    if (p->child.size()!=0 && p->child[0]==NULL)
        cout<<"Error! Can't create a directory in a file"<<endl;
    else 
    {
        (p->child).push_back(newNode(temp1));
        int n = p->child.size();
        p->child[n - 1]->parent = p;
    }
}

void del(string s)
{
    int k;
    for (int j = s.length() - 1; j >= 0; j--)
    {
        if (s[j] == '/')
        {
            k = j;
            break;
        }
    }
    string temp1 = s.substr(k + 1, s.length() - k - 1);
    s.erase(k, s.length() - k);
    k = 0;
    for (int j = s.length() - 1; j >= 0; j--)
    {
        if (s[j] == '/')
        {
            k = j;
            break;
        }
    }
    string temp2 = s.substr(k + 1, s.length() - k - 1);
    s.erase(k, s.length() - k);
    Node *p = Search(root, temp2);
    p->child.pop_back();
}

void display(Node *root)
{
    // Standard level order traversal code
    // using queue
    queue<Node *> q; // Create a queue
    q.push(root);    // Enqueue root
    while (!q.empty())
    {
        int n = q.size();

        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            Node *p = q.front();
            q.pop();
            cout << p->key << " ";

            // Enqueue all children of the dequeued item
            for (int i = 0; i < p->child.size(); i++) {
                if (p->child[i]==NULL)
                    break;
                q.push(p->child[i]);
            }
                
            n--;
        }
        cout << endl; // Print new line between two levels
    }
}

string FilePath(Node *p)
{
    string res = "/" + p->key;
    while (p->parent != NULL)
    {
        p = p->parent;
        res = "/" + p->key + res;
    }
    return res;
}


int main()
{
    string path,comm;
    int k;
    create_dir("/Users/abhigyan");
    create_dir("/Users/abhigyan/Dekstop");
    create_dir("/Users/abhigyan/Documents");
    create_dir("/Users/abhigyan/Downloads");
    create_file("/Users/abhigyan/Dekstop/file.txt");
    create_file("/Users/abhigyan/Downloads/dl.ipynb");
    create_file("/Users/abhigyan/Documents/marks.pdf");
    cout << "Enter your command:" << endl;
    do {
        cout<<">";
        cin>>comm;
        if (comm=="mkdir") {
            cin>>path;
            create_dir(path);
        }
        else if (comm=="touch") {
            cin>>path;
            create_file(path);
        }
        else if (comm=="rm"){
            cin>>path;
            string s=path;
            string copy=path;
            for (int j = s.length() - 1; j >= 0; j--)
            {
                if (s[j] == '/')
                {
                    k = j;
                    break;
                }
            }
            string temp1 = s.substr(k + 1, s.length() - k - 1);
            Node *p = Search(root,temp1);
            if (p->child.size()!=0 && p->child[0]==NULL)
                del(copy);
            else
                cout<<"Not a file"<<endl;
        }
        else if (comm=="rmdir") {
            cin>>path;
            string s=path;
            string copy=path;
            for (int j = s.length() - 1; j >= 0; j--)
            {
                if (s[j] == '/')
                {
                    k = j;
                    break;
                }
            }
            string temp1 = s.substr(k + 1, s.length() - k - 1);
            Node *p = Search(root,temp1);
            if (p->child[0]==NULL)
                cout<<"Not a directory"<<endl;
            else
            {
                if (p->child.size()!=0 && p->child.size()>0) {
                    cout<<"Are you sure you want to delete all the files in the directory as well?(y/n)"<<endl;
                    char c;
                    cin>>c;
                    if (c=='y')
                        del(copy);
                    else
                        break;
                }
                else
                    del(copy);
            }
        }
        else if (comm=="find") {
            cin>>path;
            Node *p = Search(root,path);
            if (p)
            cout<<FilePath(p)<<endl;
        }
        else if (comm=="ls") {
            display(root);
        }
        else if (comm=="exit()") {
            cout<<"EXITTING..";
            break;
        }
        else {
            cout<<"Inavlid Command";
        }
    } while(comm!="exit()");
    return 0;
}