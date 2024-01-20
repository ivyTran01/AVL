#include"AVLTree.h"
using namespace std;

////////// IMPLEMENT PRIVATE UTILITIES //////////////////////////

bool AVLTree::isExternal(Node* v) const
{
	if (v->left == nullptr && v->right == nullptr)
		return true;
	else
		return false;
}

int AVLTree::max(int a, int b)
{
	return (a > b)? a:b ;
}

AVLTree::Node* AVLTree::expandExternal(Node* v, int k)
{
	//pre-condition: v is a leaf
	v->key = k;
	v->height = 1;

	v->left = new Node;
	v->left->parent = v;
	v->right = new Node;
	v->right->parent = v;

	return v;
}

AVLTree::Node* AVLTree::rotateRight(Node* v)
{
	Node* parent = v->parent;
	Node* w = v->left;
	Node* T = w->right;

	//rotate
	w->right = v;
	v->left = T;
	T->parent = v;
	v->parent = w;
	w->parent = parent;

	//change child address on the parent above
	if (parent != nullptr)
	{
		if (v == parent->left)
			parent->left = w;
		else if (v == parent->right)
			parent->right = w;
	}
	else
	{
		root = w;
	}

	//update heights
	v->height = max(v->left->height, v->right->height) + 1;
	w->height = max(w->left->height, w->right->height) + 1;

	return w;
}

AVLTree::Node* AVLTree::rotateLeft(Node* v)
{
	Node* parent = v->parent;
	Node* w = v->right;
	Node* T = w->left;

	//rotate
	w->left = v;
	v->right = T;
	T->parent = v;
	v->parent = w;
	w->parent = parent;

	//change child address
	if (v != root)
	{
		if (v == parent->left)
			parent->left = w;
		else if (v == parent->right)
			parent->right = w;
	}
	else
		root = w;

	//update heights
	v->height = max(v->left->height, v->right->height) + 1;
	w->height = max(w->left->height, w->right->height) + 1;

	return w;
}

AVLTree::Node* AVLTree::searchSpotForInsert(int k) const
{
	Node* temp = root;
	while (!isExternal(temp))
	{
		if (temp->key <= k)
			temp = temp->right;
		else if (temp->key > k)
			temp = temp->left;
	}
	return temp;
}

int AVLTree::balanceFactor(Node* v) const
{
	int bf = (v->left->height) - (v->right->height);
	return bf;
}

bool AVLTree::isBalanced(Node* v) const
{
	int bf = balanceFactor(v);
	if (bf >= -1 && bf <= 1)
		return true;
	else
		return false;
}

AVLTree::Node* AVLTree::lookUp(int k) const
{
	Node* answer = root;
	bool found = false;
	while (!found && !isExternal(answer))
	{
		if (answer->key == k)
			found = true;
		else if (answer->key > k)
			answer = answer->left;
		else
			answer = answer->right;
	}
	return answer;
}

AVLTree::Node* AVLTree::removeAboveExternal(Node* v)
{
	Node* par = v->parent;
	//find sibling
	Node* sib;
	if (v == par->left)
		sib = par->right;
	else
		sib = par->left;

	//if parent is the ROOT node
	if (par == root)
	{
		root = sib;
		sib->parent = nullptr;
	}
	else
	{
		Node *grandParent = par->parent;
		if (par == grandParent->left)
			grandParent->left = sib;
		else
			grandParent->right = sib;

		sib->parent = grandParent;
	}
	delete v;
	delete par;
	return sib;
}

AVLTree::Node* AVLTree::findMinNode(AVLTree::Node* v) const
{
	while (!isExternal(v->left))
		v = v->left;
	return v;
}

void AVLTree::print(Node* v) const
{
	if (isExternal(v))
		cout << "L (" << v->height << ")" << endl;
	else
		cout << v->key << " (" << v->height << ")" << endl;
}

void AVLTree::indent(int n) const
{
	for (int i=1; i<=n; i++)
		cout << "   ";
}

void AVLTree::printPreorder(Node* v, int n) const
{
	indent(n);
	print(v);
	if (!isExternal(v))
	{
		printPreorder(v->left, n+1);
		printPreorder(v->right, n+1);
	}
}

////////////// IMPLEMENT PUBLIC FUNCTIONS ////////////////////////

AVLTree::Node::Node()
{
	key = 0;
	height = 0;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

string AVLTree::Node::toString() const
{
	string s;
	s = "Node(key=" + to_string(key); 
	s += ", height=" + to_string(height);
	s += ")"; 
	return s; 
}

bool AVLTree::Node::operator==(const Node& x) const
{
	if (this->key == x.key && this->height == x.height)
		return true; 
	else
		return false; 
} 

AVLTree::AVLTree()
{
	root = new Node;
	count = 0;
	end.key = -1234567;
}

AVLTree::~AVLTree()
{
	while (!empty())
		erase(root->key);
	delete root;
}

AVLTree::Node AVLTree::find(int k) const
{
	Node* temp = lookUp(k);
	if (isExternal(temp))
		return end;
	else
		return *temp;
}

AVLTree::Node AVLTree::put(int k)
{
	//if tree empty
	if (this->empty())
	{
		expandExternal(root, k);
		count++;
		return (*root);
	}

	//else insert this k into some leaf
	Node* spot = searchSpotForInsert(k);
	Node* temp = expandExternal(spot, k);
	Node returnedTarget = *temp;

	//update heights of its ancestors
	spot = spot->parent;
	while (spot != nullptr)
	{
		//update height
		spot->height = max(spot->left->height, spot->right->height) + 1;
		//check is node is balanced
		if (!isBalanced(spot))
		{
			//left left case
			if (balanceFactor(spot) > 1 && spot->left->key > k)
			{
				spot = rotateRight(spot);
			}
				//left right case
			else if (balanceFactor(spot) > 1 && spot->left->key <= k)
			{
				spot->left = rotateLeft(spot->left);
				spot = rotateRight(spot);
			}
				//right right case
			else if (balanceFactor(spot) < -1 && spot->right->key <= k)
			{
				spot = rotateLeft(spot);
			}
				//right left case
			else if (balanceFactor(spot) < -1 && spot->right->key > k)
			{
				spot->right = rotateRight(spot->right);
				spot = rotateLeft(spot);
			}
		}
		spot = spot->parent;
	}
	count++;
	return returnedTarget;
}

void AVLTree::erase(int k)
{
	if (empty())
		throw EmptyTreeException("ERROR! ERASE FROM EMPTY TREE!");
	//else
	Node* spot = lookUp(k);
	if (isExternal(spot))
		throw KeyNotFoundException("ERROR! KEY NOT FOUND!");

	//else if found k somewhere => 3 cases
	//if it has 0 or 1 children
	if (isExternal(spot->left) || isExternal(spot->right))
	{
		if (isExternal(spot->left))
			spot = removeAboveExternal(spot->left);
		else
			spot = removeAboveExternal(spot->right);
	}
		//if it has 2 children
	else
	{
		Node* minNode = findMinNode(spot->right);
		spot->key = minNode->key;
		spot = removeAboveExternal(minNode->left);
	}

	spot = spot->parent;
	while(spot != nullptr)
	{
		//update height
		spot->height = max(spot->left->height, spot->right->height) + 1;
		//check is node is balanced
		if (!isBalanced(spot))
		{
			//left left case
			if (balanceFactor(spot) > 1 && balanceFactor(spot->left) >= 0)
			{
				spot = rotateRight(spot);
			}
				//left right case
			else if (balanceFactor(spot) > 1 && balanceFactor(spot->left) < 0)
			{
				spot->left = rotateLeft(spot->left);
				spot = rotateRight(spot);
			}
				//right right case
			else if (balanceFactor(spot) < -1 && balanceFactor(spot->right) <= 0)
			{
				spot = rotateLeft(spot);
			}
				//right left case
			else if (balanceFactor(spot) < -1 && balanceFactor(spot->right) > 0)
			{
				spot->right = rotateRight(spot->right);
				spot = rotateLeft(spot);
			}
		}
		spot = spot->parent;
	}
	count--;
}

int AVLTree::size() const
{
	return count;
}

bool AVLTree::empty() const
{
	return (size() == 0);
}

AVLTree::Node AVLTree::getEnd() const
{
	return end;
}

void AVLTree::print() const
{
	printPreorder(root,0);
}

