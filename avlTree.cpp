#include <bits/stdc++.h>
using namespace std;

typedef Type int;

struct Node {
	Node* left;
	Node* right;
	int height;
	Type data;
	Node(Type x) {
		data = x;
		height = 1;
		left = right = NULL;
	}
};

int getHeight(Node *node) {
	return node->height;
}

//LL----右旋
Node* rightRotate(Node* a) {
	Node *b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = max(getHeight(a->left), getHeight(a->right));
	b->height = max(getHeight(b_>left), getHeight(b->right));
}

//RR----左旋
Node* leftRotate(Node* a) {
	Node *b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = max(getHeight(a->left), getHeight(a->right));
	b->height = max(getHeight(b_>left), getHeight(b->right));	
}

//LR
Node* leftRightRotate(Node* a) {
	a->left = leftRotate(a->left);
	return rightRotate(a);
}

//RL
Node* rightLeftRotate(Node* a) {
	a->right = rightRotate(a->right);
	return leftRotate(a);
}

Node* insert(Type x, Node* tree) {
	if(t == NULL) {
		t = new Node(x);
	}
	else if(x < t->data) {
		t->left = insert(t->left);
		if(getHeight(t->left)-getHeight(t->right) == 2) {
			if(x < t->left->data) {		//x插入到了左子树的左子树
				t = rightRotate(t);
			}
			else {
				t = leftRightRotate(t);
			}
		}
	}
	else {
		t->right = insert(t->right);
		if(getHeight(t->right) - getHeight(t->left) == 2) {
			if(x > t->right->data) {
				t = leftRotate(t);
			}
			else {
				t = rightLeftRotate(t);
			}
		}
	}
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	return t;
}

Node *deleteNode(Type x, Node* t) {
	if(t == NULL) {
		return NULL;
	}
	if(t->data == x) {
		if(t->right == NULL) {
			Node* temp = t;
			t = t->left;
			delete temp;
		}
		else {
			Node* head = t->right;	//找出后继节点
			while(head->left) {
				head = head->left;
			}
			t->data = head->data;
			t->right = deleteNode(t->data, t->right);
			t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
		}
		return t;
	}
	else if(t->data < x) {
		deleteNode(x, t->left);
		if(t->right) {
			//TODO
		}
	}
	else {
		deleteNode(x, t->left);
		if(t->left) {
			// TODO
		}
	}
	if(t) {
		// TODO
	}
}

Node* find(Type x, Node* t) {
	if(t == NULL) {
		return NULL;
	}
	if(t->data == x) { 
		return t;
	}
	else if(t->data > x) {
		return find(t->left);
	}
	else {
		return find(t->right);
	}
}

int main() {

	return 0;
}