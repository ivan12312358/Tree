#include <iostream>
#include <fstream>
#include <cmath>

struct Node
{
	int key;
	int height;
	int size;
	Node* left;
	Node* right;
	Node* prev;

	Node(int key = 0): key{key}, height{1}, size{1},
		left{}, right{}, prev{} {}

	Node(const Node& other): left{}, right{}, prev{} { *this = other; }

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

			Node *curr = this;
			Node const* cp_node = &other;

			while(true)
			{
				curr->key    = cp_node->key;
				curr->height = cp_node->height;
				curr->size   = cp_node->size;

				if (cp_node->left && !curr->left)
				{
					curr->left = new Node;
					curr->left->prev = curr;
					cp_node = cp_node->left;
					curr 	= curr->left;
				}
				else if (cp_node->right && !curr->right)
				{
					curr->right = new Node;
					curr->right->prev = curr;
					cp_node = cp_node->right;
					curr 	= curr->right;
				}
				else if (cp_node->prev)
				{
					cp_node = cp_node->prev;
					curr	= curr->prev;
				} else break;
			}
		}
		return *this;
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

	void calc_height()
	{
		int h_left  =  left ?  left->height : 1;
		int h_right = right ? right->height : 1;
		height = std::max(h_left, h_right) + 1;
	}

	void calc_size()
	{
		int s_left  =  left ?  left->size : 0;
		int s_right = right ? right->size : 0;
		size = s_left + s_right + 1;
	}

	void insert(int Key)
	{
		if (Key < key)
		{
			if (left)
				left->insert(Key);
			else 
			{
				left = new Node{Key};
				left->prev = this;
			}
		}
		else
		{
			if (right)
				right->insert(Key);
			else 
			{
				right = new Node{Key};
				right->prev = this;
			}
		}

		calc_height();
		calc_size();
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
	size_t size{};
public:

	void insert(int Key)
	{
		if (size != 0)
			top.insert(Key);
		else
			top.key = Key;

		size++;
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
	tree.insert(6);
	tree.insert(11);
	tree.insert(-3);
	tree.insert(9);

	Tree tr1{tree};

	tr1.graph();

	return 0;
}