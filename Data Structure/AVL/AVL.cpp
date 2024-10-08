#include <bits/stdc++.h>
using namespace std;

struct AVL {
	struct AVL* left;
	struct AVL* right;
	struct AVL* par;
	int height, data;
};

void Updateheight(struct AVL* root)
{
	if (root != NULL) {
		int val = 1;

		if (root->left != NULL)
			val = root->left->height + 1;

		if (root->right != NULL)
			val = max(val, root->right->height + 1);

		root->height = val;
	}
}

//handle Left Left Case
struct AVL* LLR(struct AVL* root)
{
	struct AVL* tmpnode = root->left;
	root->left = tmpnode->right;

	if (tmpnode->right != NULL)
		tmpnode->right->par = root;

	tmpnode->right = root;
	tmpnode->par = root->par;
	root->par = tmpnode;

	if (tmpnode->par != NULL && root->data < tmpnode->par->data) {
		tmpnode->par->left = tmpnode;
	}
	else {
		if (tmpnode->par != NULL)
			tmpnode->par->right = tmpnode;
	}
	root = tmpnode;
	Updateheight(root->left);
	Updateheight(root->right);
	Updateheight(root);
	Updateheight(root->par);
	return root;
}

//handle Right Right Case
struct AVL* RRR(
	struct AVL* root)
{
	struct AVL* tmpnode = root->right;
	root->right = tmpnode->left;

	if (tmpnode->left != NULL)
		tmpnode->left->par = root;

	tmpnode->left = root;
	tmpnode->par = root->par;
	root->par = tmpnode;

	if (tmpnode->par != NULL && root->data < tmpnode->par->data) {
		tmpnode->par->left = tmpnode;
	}
	else {
		if (tmpnode->par != NULL)
			tmpnode->par->right = tmpnode;
	}
	root = tmpnode;
	Updateheight(root->left);
	Updateheight(root->right);
	Updateheight(root);
	Updateheight(root->par);
	return root;
}

//handle Left Right Case
struct AVL* LRR(struct AVL* root)
{
	root->left = RRR(root->left);
	return LLR(root);
}

//handle right left case
struct AVL* RLR(struct AVL* root)
{
	root->right = LLR(root->right);
	return RRR(root);
}

struct AVL* Balance(struct AVL* root)
{
	int firstheight = 0, secondheight = 0;

	if (root->left != NULL)
		firstheight = root->left->height;

	if (root->right != NULL)
		secondheight = root->right->height;

	if (abs(firstheight - secondheight) == 2) {
		if (firstheight < secondheight) {
			int rightheight1 = 0, rightheight2 = 0;
			if (root->right->right != NULL)
				rightheight2 = root->right->right->height;

			if (root->right->left != NULL)
				rightheight1 = root->right->left->height;

			if (rightheight1 > rightheight2) {
				root = RLR(root);
			}
			else {
				root = RRR(root);
			}
		}
		else {
			int leftheight1 = 0, leftheight2 = 0;
			if (root->left->right != NULL)
				leftheight2 = root->left->right->height;

			if (root->left->left != NULL)
				leftheight1 = root->left->left->height;

			if (leftheight1 > leftheight2) {
				root = LLR(root);
			}
			else {
				root = LRR(root);
			}
		}
	}
	return root;
}

struct AVL* insertNode(struct AVL* root, struct AVL* parent, int data)
{
	if (root == NULL) {
		root = new struct AVL;
		if (root == NULL)
			cout << "Error in memory" << endl;
		else {
			root->height = 1;
			root->left = NULL;
			root->right = NULL;
			root->par = parent;
			root->data = data;
		}
	}

	else if (root->data > data) {
		root->left = insertNode(root->left, root, data);
		int firstheight = 0, secondheight = 0;

		if (root->left != NULL)
			firstheight = root->left->height;

		if (root->right != NULL)
			secondheight = root->right->height;

		if (abs(firstheight - secondheight) == 2) {

			if (root->left != NULL && data < root->left->data) {
				root = LLR(root);
			}
			else {
				root = LRR(root);
			}
		}
	}

	else if (root->data < data) {
		root->right = insertNode(root->right, root, data);
		int firstheight = 0, secondheight = 0;

		if (root->left != NULL)
			firstheight = root->left->height;

		if (root->right != NULL)
			secondheight = root->right->height;

		if (abs(firstheight - secondheight) == 2) {
			if (root->right != NULL && data < root->right->data) {
				root = RLR(root);
			}
			else {
				root = RRR(root);
			}
		}
	}
	else {
	}
	Updateheight(root);
	return root;
}

struct AVL* deleteNode(struct AVL* root, int data)
{
	if (root != NULL) {
		if (root->data == data) {
			if (root->right == NULL && root->left != NULL) {
				if (root->par != NULL) {
					if (root->par->data < root->data)
						root->par->right = root->left;
					else
						root->par->left = root->left;
					Updateheight(root->par);
				}

				root->left->par = root->par;
				root->left = Balance(root->left);
				return root->left;
			}
			else if (root->left == NULL && root->right != NULL) {
				if (root->par != NULL) {
					if (root->par->data < root->data)
						root->par->right = root->right;
					else
						root->par->left = root->right;
					Updateheight(root->par);
				}

				root->right->par = root->par;
				root->right = Balance(root->right);
				return root->right;
			}

			else if (root->left == NULL && root->right == NULL) {
				if (root->par->data < root->data) {
					root->par->right = NULL;
				}
				else {
					root->par->left = NULL;
				}

				if (root->par != NULL)
					Updateheight(root->par);

				root = NULL;
				return NULL;
			}
			else {
				struct AVL* tmpnode = root;
				tmpnode = tmpnode->right;
				while (tmpnode->left != NULL) {
					tmpnode = tmpnode->left;
				}

				int val = tmpnode->data;

				root->right = deleteNode(root->right, tmpnode->data);
				root->data = val;
				root = Balance(root);
			}
		}
		else if (root->data < data) {
			root->right = deleteNode(root->right, data);

			root = Balance(root);
		}
		else if (root->data > data) {
			root->left = deleteNode(root->left, data);
			root = Balance(root);
		}
		if (root != NULL) {
			Updateheight(root);
		}
	}
	else {
		cout << "data was not found " << endl;
	}
	return root;
}

bool searchNode(struct AVL* root, int data)
{
    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (root->data > data) {
        bool val = searchNode(root->left, data);
        return val;
    }
    else {
        bool val = searchNode(root->right, data);
        return val;
    }
}

//inorder
void print(struct AVL* root)
{
	if (root->left != NULL) {
		print(root->left);
	}
	cout << root->data << " ";

	if (root->right != NULL) {
		print(root->right);
	}
}

int main()
{
	struct AVL* root;
	root = NULL;


    int n, x;
    string cmnd;
    cin >> n;
    for(int i = 0; i < n; i ++){
        cin >> cmnd >> x;
        if(cmnd == "insert"){
            root = insertNode(root, NULL, x);
        }
        if(cmnd == "delete"){
            root = deleteNode(root, x);
        }
        if(cmnd == "search"){
            if(searchNode(root, x))
                cout << x << " was found" << endl;
            else
                cout << x << " was not found" << endl;
        }
        print(root);
        cout << endl;
    }
	return 0;
}
