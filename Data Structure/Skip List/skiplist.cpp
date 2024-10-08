#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
	    int data;
	    Node **next;
        Node(int data, int level)
        {
	        this->data = data;
	        next = new Node*[level+1];
	        memset(next, 0, sizeof(Node*)*(level+1));
        }
};

class SkipList
{
	int mxLevel, level;
	float P;
	Node *header;
    public:
	    SkipList(int mxLevel, float P);
	    int randomLevel();
	    void insertNode(int data);
	    void deletetNode(int data);
	    void searchNode(int data);
	    void print();
};

int lnN(int data){
    int answer = 0;
    while(data > 1){
        answer ++;
        data /= 2;
    }
    return answer;
}

int main()
{
	srand((unsigned)time(0));
    int n, x;
    string cmnd;
    cin >> n;
    SkipList myList(lnN(n)+ 1, 0.5);
    for(int i = 0; i < n; i ++){
        cin >> cmnd >> x;
        if(cmnd == "insert"){
            myList.insertNode(x);
        }
        if(cmnd == "delete"){
            myList.deletetNode(x);
        }
        if(cmnd == "search"){
            myList.searchNode(x);
        }
        myList.print();
    }

    int z;
    cin >> z;
    return 0;
}




SkipList::SkipList(int mxLevel, float P)
{
	this->mxLevel = mxLevel;
	this->P = P;
	level = 0;
	header = new Node(-1, mxLevel);
};

int SkipList::randomLevel()
{
	float r = float(rand())/ RAND_MAX;
	int level = 0;
	while(r < P and level < mxLevel)
	{
		level++;
		r = float(rand())/ RAND_MAX;
	}
	return level;
};

void SkipList::insertNode(int data)
{
	Node *current = header;
	Node *update[mxLevel+1];
	memset(update, 0, sizeof(Node*)*(mxLevel+1));
	for(int i = level; i >= 0; i--)
	{
		while(current->next[i] != NULL and current->next[i]->data < data)
			current = current->next[i];
		update[i] = current;
	}
	current = current->next[0];
	if (current == NULL || current->data != data)
	{
		int rlevel = randomLevel();
		if(rlevel > level)
		{
			for(int i = level+1; i < rlevel+1; i++)
				update[i] = header;
			level = rlevel;
		}

		Node* n =   new Node(data, level); 
		for(int i = 0; i <= rlevel; i++)
		{
			n->next[i] = update[i]->next[i];
			update[i]->next[i] = n;
		}
		cout<< data  << "  Inserted" << endl;
	}
};

void SkipList::deletetNode(int data)
{
	Node *current = header;
	Node *update[mxLevel+1];
	memset(update, 0, sizeof(Node*)*(mxLevel+1));

	for(int i = level; i >= 0; i--)
	{
		while(current->next[i] != NULL and current->next[i]->data < data)
			current = current->next[i];
		update[i] = current;
	}

	current = current->next[0];

	if(current != NULL and current->data == data)
	{
		for(int i = 0; i <= level; i++)
		{
			if(update[i]->next[i] != current)
				break;
			update[i]->next[i] = current->next[i];
		}

		while(level > 0 and header->next[level] == 0)
			level--;
		cout<< data << " Deleted" << endl;
	}
};

void SkipList::searchNode(int data)
{
	Node *current = header;
	for(int i = level; i >= 0; i--)
	{
		while(current->next[i] and current->next[i]->data < data)
			current = current->next[i];
	}

	current = current->next[0];

	if(current and current->data == data)
		cout<< "Found data: " << data << endl;
    else
        cout << "Data was not found" << endl;
};

void SkipList::print()
{
    cout << "**************************" << endl;
	for(int i = 0; i <= level; i++)
	{
		Node *node = header->next[i];
		cout<< "Level " << i << ": ";
		while(node != NULL)
		{
			cout<< node->data << " ";
			node = node->next[i];
		}
		cout<< endl;
	}
    cout << "**************************" << endl;
};

