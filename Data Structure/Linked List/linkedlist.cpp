#include <bits/stdc++.h>
using namespace std;
vector <int> vec, v;

struct Node {
	int data;
	Node* next;
};

void insert(Node** root, int item)
{
	Node* temp = new Node;
	Node* ptr;
	temp->data = item;
	temp->next = NULL;

	if (*root == NULL)
		*root = temp;
	else {
		ptr = *root;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = temp;
	}
}

void deleteNode(Node** root)
{
	Node* ptr;

	if (*root != NULL){
		ptr = *root;
		while (ptr->next->next != NULL)
			ptr = ptr->next;
		ptr->next = NULL;
	}
}

int findNode(Node** root)
{
	Node* ptr;
	
	if (*root != NULL){
		ptr = *root;
		while (ptr->next != NULL)
			ptr = ptr->next;
		return ptr->data;
	}
	else
	return 0;
}

void display(Node* root)
{
	while (root != NULL) {
		cout << root->data << " ";
		root = root->next;
	}
}

int main()
{
	int n, x;
	cin >> n ;
	Node *root = NULL;
	for(int i = 0; i < n; i ++){
		cin >> x;
		int m = vec.size();
		bool flag = true;
		//cout << i << " : ";
		for(int j = 0; j < m; j ++){
			//cout << v[j] << " ";
			if(x + vec[j] == 0){
				flag = false;
				for(int k = 0; k < m-j; k ++){
					deleteNode(&root);
					vec.pop_back();
					v.pop_back();
				}
				break;
			}
		}
		//cout << endl;
		if(flag){
			for(int j = 0; j < m; j ++){
				vec[i] += x;
			}
			vec.push_back(x);
			v.push_back(x);
			insert(&root , x);
		}
		else{
			for(int j = 0; j < vec.size(); j ++){
				vec[i] -= x;
			}
		}
	}

	display(root);
	//cout << endl << "*********" << endl;
	//for(int i = 0; i < vec.size(); i ++)
	//cout << v[i] << " ";

	return 0;
}
