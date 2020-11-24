#include<iostream>
#define AVLTrees_H
#include<cmath>

using namespace std;

struct Node {
	int data;
	Node *lChild = NULL;
	Node *rChild = NULL;
	int Height;
	//implement any required constructors/getters/setters.
};
class AVL {
private:
	Node * root;
public:
	AVL() {
		root = NULL;
	}
	void insert(int data) {
		if (root == NULL) {
			Node *newNoode = new Node;
			newNoode->data = data;
			newNoode->lChild = NULL;
			newNoode->rChild = NULL;
			root = newNoode;
		}
		else {
			root = insert(root, data);
		}
		root->Height = this->height(root);
	}
	Node* insert(Node *parent, int data) {
		if (parent == NULL) {
			Node *newNoode = new Node;
			newNoode->data = data;
			newNoode->lChild = NULL;
			newNoode->rChild = NULL;
			parent = newNoode;
			return newNoode;
		}
		else if (data < parent->data) {
			parent->lChild = insert(parent->lChild, data);
			parent = balance(parent);
		}
		else if (data > parent->data) {
			parent->rChild = insert(parent->rChild, data);
			parent = balance(parent);
		} return parent;
	}
	int height(Node* parent) {
		if (parent == NULL)
			return 0;
		else {
			/* compute the depth of each subtree */
			int lDepth = height(parent->lChild);
			int rDepth = height(parent->rChild);

			/* use the larger one */
			if (lDepth > rDepth)
				return(lDepth + 1);
			else return(rDepth + 1);
		}
	}

	int leftRightHeightDifference(Node *parent) {
		int leftHeight = height(parent->lChild);
		int rightHeight = height(parent->rChild);
		return (leftHeight - rightHeight);
	}
	Node* balance(Node *parent) {
		int bal_factor = leftRightHeightDifference(parent);
		if (bal_factor > 1) {
			if (leftRightHeightDifference(parent->lChild) > 0)
				parent = rotate(parent, 3);
			else
				parent = rotate(parent, 4);
		}
		else if (bal_factor < -1) {
			if (leftRightHeightDifference(parent->rChild) > 0)
				parent = rotate(parent, 2);
			else
				parent = rotate(parent, 1);
		}
		return parent;
	}

	Node* rotate(Node* parent, int opetion) {
		/*
		1 = rr
		2 = rl
		3 = ll
		4 = lr
		*/
		if (opetion == 1) {
			Node *temp;
			temp = parent->rChild;
			parent->rChild = temp->lChild;
			temp->lChild = parent;
			return temp;
		}
		else if (opetion == 2) {
			Node* temp;
			temp = parent->rChild;
			parent->rChild = rotate(temp, 3);
			return rotate(parent,1);
		}
		else if (opetion == 3) {
			Node *temp;
			temp = parent->lChild;
			parent->lChild = temp->rChild;
			temp->rChild = parent;
			return temp;
		}
		else if (opetion == 4) {
			Node *temp;
			temp = parent->lChild;
			parent->lChild = rotate(temp, 1);
			return rotate(parent,3);
		}
	}
	void Printintreeform() {
		cout << "? represent Null node\n";
		print(root, height(root));
	}
	void printNodesAtLevel(Node* root, int currentLevel, int level, int tempspaces) {
		int spaces = tempspaces + tempspaces - 1;
		
		if (root == NULL) {
			cout << "?";
			for (int k = 0; k < spaces; k++) {
				cout << " ";
			}
			return;
		}
		if (currentLevel == level) {
			cout << root->data;
			for (int k = 0; k < spaces; k++) {
				cout << " ";
			}
			return;
		}

		printNodesAtLevel(root->lChild, currentLevel + 1, level,tempspaces);
		printNodesAtLevel(root->rChild, currentLevel + 1, level, tempspaces);
	}
	void print(Node*parent,int height) {
		Node * temp = parent;
		for (int i = 0; i < height; i++) {
			int element = pow(2, i);
			int tempspaces = pow(2, height - (i + 1));

			for (int j = 0; j < tempspaces; j++) { // print first spaces
				cout << " ";
			}
			printNodesAtLevel(parent, 0, i, tempspaces);
			cout << endl;
		}
	}
	void deletedata(int data) {
		root = deletedata(root,data);
	}

	Node * deletedata(Node*parent, int data) {

		if (parent->lChild== NULL && parent->rChild == NULL) {
			if (parent == this->root)
				this->root = NULL;
			delete parent;
			return NULL;
		}
		Node *temp;
		if (parent->data < data) {
			parent->rChild = deletedata(parent->rChild, data);
		}
		else if (parent->data > data) {
			parent->lChild= deletedata(parent->lChild, data);
		}
		else {
			if (parent->lChild!= NULL) {
				temp = Right(parent->lChild);
				parent->data = temp->data;
				parent->lChild = deletedata(parent->lChild, temp->data);
			}
			else {
				temp = Left(parent->rChild);
				parent->data = temp->data;
				parent->rChild = deletedata(parent->rChild, temp->data);
			}
		}

		if (leftRightHeightDifference(parent) == 2 && leftRightHeightDifference(parent->lChild) == 1){
			parent = rotate(parent, 3);
		}
		else if (leftRightHeightDifference(parent) == 2 && leftRightHeightDifference(parent->lChild) == -1){
			parent = rotate(parent, 4);
		}
		else if (leftRightHeightDifference(parent) == 2 && leftRightHeightDifference(parent->lChild) == 0){
			parent = rotate(parent, 3);
		}
		else if (leftRightHeightDifference(parent) == -2 && leftRightHeightDifference(parent->rChild) == -1){
			parent = rotate(parent, 1);
		}
		else if (leftRightHeightDifference(parent) == -2 && leftRightHeightDifference(parent->rChild) == 1){
			parent = rotate(parent, 2);
		}
		else if (leftRightHeightDifference(parent) == -2 && leftRightHeightDifference(parent->rChild) == 0){
			parent = rotate(parent, 3);
		}
		return parent;
	}
	Node* Left(Node* parent) {
		while (parent->lChild != NULL)
			parent = parent->lChild;

		return parent;
	}
	Node* Right(Node* parent) {
		while (parent->rChild != NULL)
			parent = parent->rChild;

		return parent;
	}
	bool search(int key) {
		return search(root, key);
	}
	bool search(Node *parent, int key) {
		if (parent == NULL) {
			return NULL;
		}
		else {
			if (key == parent->data) {
				return true;
			}
			else if (key < parent->data) {
				return search(parent->lChild, key);
			}
			else {
				return search(parent->rChild, key);
			}
		}
		return 0;
	}
	int NoofNodes() const {
		int length = 0;
		NoofNodes(root, length);
		return length;
	}
	void NoofNodes(Node *parent, int&length) const {
		if (parent == NULL)
			return;
		NoofNodes(parent->lChild, length);
		length++;
		NoofNodes(parent->rChild, length);
	}
	void Delete(Node *parent) {
		if (parent != NULL) {
			Delete(parent->lChild);
			Delete(parent->rChild);
			delete parent;
		}
	}
	void flipClockwise() {
		Node*temp = root;
		Node*tempRight = root->rChild;
		Node* tempLeft = root->lChild;
		tempLeft->rChild = tempRight;
		root->rChild = NULL;
		tempLeft->rChild = tempLeft->lChild;
		tempLeft->lChild = tempRight;
	}
	~AVL() {
		Delete(root);
	}
};