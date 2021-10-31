#include <iostream>
#include <fstream>

struct Node
{
	int key;
	int height;
	int size;
	Node* left;
	Node* right;
	Node* prev;

	Node(int key = 0): 
		key{key}, height{1}, size{1},
		left{}, right{},  prev{} {}

	Node(const Node& other):
		key{other.key}, height{other.height}, size{other.size},
		left{}, right{}, prev{} { *this = other; }

	Node(Node&& other): 
		key{other.key}, height{other.height}, size{other.size},
		left{other.left}, right{other.right}, prev{other.prev}
	{
		other.left  = nullptr;
		other.right = nullptr;
		other.prev  = nullptr;
	}

	Node& operator= (const Node& other)
	{
		if (this != &other)
		{
			delete left;
			delete right;
			prev = nullptr;

			key    = other.key;
			height = other.height;

			if (other.left)
			{
				left = new Node;
				left->prev = this;
				left->NodeCopy(other.left);
			}
			if (other.right)
			{
				right = new Node;
				right->prev = this;
				right->NodeCopy(other.right);
			}
		}
		return *this;
	}

	void NodeCopy(Node* other)
	{
		Node* curr = this;

		while (true)
		{
			curr->key 	 = other->key;
			curr->height = other->height;

			if (other->left)
			{
				curr->left = new Node;
				curr->left->prev = curr;
				curr = curr->left;
				other = other->left;
			} 
			else if (other->right)
			{
				curr->right = new Node;
				curr->right->prev = curr;
				curr = curr->right;
				other = other->right;
			}
			else break;
		}
	}

	Node& operator= (Node&& other)
	{
		if (this != &other)
		{
			delete left;
			delete right;

			key   = other.key, 	 height = other.height;
			left  = other.left,  other.left  = nullptr;
			right = other.right, other.right = nullptr;
			prev  = other.prev,  other.prev  = nullptr;
		}
		return *this;
	}

	~Node()
	{
		if(!left && !right)
			return;

		Node *curr = this, *tmp{};

		while (true)
		{
			if (curr->left)
				curr = curr->left;
			else if (curr->right)
				curr = curr->right;
			else if (curr->prev)
			{
				tmp  = curr;
				curr = curr->prev;

				if (curr->left == tmp)
					curr->left = nullptr;
				else if (curr->right == tmp)
					curr->right = nullptr;

				delete tmp;
			}
			else break;
		}
	}

	void insert(int Key)
	{
		if (Key < key)
		{
			if (left)
				left->insert(Key);
			else
			{
				left = new Node;
				left->key  = Key; 
				left->prev = this;
			}
		}
		else
		{
			if (right)
				right->insert(Key);
			else 
			{
				right = new Node;
				right->key  = Key; 
				right->prev = this;
			}
		}
//		balance();
	}

	void graph(std::ofstream& fgraph)
	{
		fgraph  << "\n\tp" << this << " [label = \"" 
				<< 	 "key: "    << key
				<< "  height: " << height
				<< "  size: "   << size << "\"]\n";

		if (left && right)
		{
			fgraph << "\tp" << this << " -> { "
				   << "p" << left << " p" << right << " }\n";

			 left->graph(fgraph);
			right->graph(fgraph);
		}
		else if (left)
		{
			fgraph << "\tp" << this << " -> { "
				   << "p" << left << " p" 
				   << &right << " [label = \"\"] }\n";

			left->graph(fgraph);
		}
		else if (right)
		{
			fgraph << "\tp" << this << " -> { "
				   << "p" << &left << " [label = \"\"] "
				   << "p" << right << " }\n";

			right->graph(fgraph);
		}
	}
};

class Tree
{
	Node top;
	size_t size;
public:

	void insert(int Key)
	{
		if (top.size != 0)
			top.insert(Key);
		else
			top.key = Key;

		top.size++;
	}

	void graph()
	{
		std::ofstream fgraph("tree_graph.dot");

		fgraph << "digraph Tree {\n\t";

		top.graph(fgraph);

		fgraph << "}";
	}
};

int main()
{
	Tree tree;

	tree.insert(4);
	tree.insert(3);
	tree.insert(5);
	tree.insert(8);
	tree.insert(11);
	tree.insert(-3);
	tree.insert(9);

	tree.graph();

	return 0;
}