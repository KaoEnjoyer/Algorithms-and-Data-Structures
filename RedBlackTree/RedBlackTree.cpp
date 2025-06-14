#include <iostream>

#define RED 1
#define BLACK 0

struct Node {
	int key;
	int data;
	int color;
	Node *left;
	Node *right;
	Node *parent;

	Node();
	Node(int key, int val, int color);
	void Recolor();
	bool IsRightChild();
	Node *Uncle();
	Node *Grandparent();
};

Node::Node() {
	key = -1;
	data = -1;
	color = BLACK;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

Node::Node(int key, int val, int color) : key(key), data(val), color(color) {
	if (color != BLACK || color != RED)
		throw "wtf?";
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

void Node::Recolor() {
	if (color == RED)
		color = BLACK;
	else
		color = RED;
}

Node *Node::Grandparent() {
	if (parent != nullptr) {
		return parent->parent;
	}
	return nullptr;
}

bool Node::IsRightChild() { return this == parent->right; }

Node *Node::Uncle() {
	Node *temp = Grandparent();
	if (temp != nullptr) {
		if (parent == temp->left)
			return temp->right;
		else
			return temp->left;
	}

	return nullptr;
}

void LeftRotate(Node *root, Node *x) {
	Node *y = x->right;
	if (y == nullptr)
		return;
	x->right = y->left;
	if (y->left != nullptr)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RightRotate(Node *root, Node *x) {
	Node *y = x->left;

	if (y == nullptr)
		return;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

void FixUp(Node *root, Node *x) {
	while (x != root && x->parent->color == RED) {
		if (x->Uncle() != nullptr && x->Uncle()->color == RED) {
			x->Grandparent()->Recolor();
			x->parent->Recolor();
			x->Uncle()->Recolor();
			x = x->Grandparent();
		} else {
			if (x->Uncle()->IsRightChild()) {
				x = x->parent;
				LeftRotate(root, x);
			}
			x->parent->Recolor();
			x->Grandparent()->Recolor();
			LeftRotate(root, x);
			root->color = BLACK;
		}
	}

	root->color = BLACK;
}

Node *Bst_Insert(Node *root, Node *x) {
	Node *current = root;
	while (current == nullptr) {
		if (x->key >= current->key)
			current = current->right;
		else
			current = current->left;
	}
	return current;
}
Node *Insert(Node *root, Node *x) {
	root = Bst_Insert(root, x);
	x->color = RED;
	// root -> color = black założnie
	while (x != root && x->parent->color == RED) {
		if (x->parent == x->parent->parent->left) {
			// uncle is a right child
			FixUp(root, x);
		} else {
			FixUp(root, x);
		}
		root->color = BLACK;
	}

	root->color = BLACK;
	return root;
}
