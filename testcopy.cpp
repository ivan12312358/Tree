#include <set>
#include <ctime>
#include <cstdlib>
#include "tree.hpp"


bool is_equal(const Node* n1, const Node* n2);

int main()
{
	std::set<int> keys;

	std::srand(std::time(nullptr));

	while (keys.size() != 10)
		keys.insert(rand() % 1000 - 500);

	Tree tr1{}, tr2{}, tr3{}, tr4{tr3};

	for (auto key: keys)
		tr1.insert(key);

	if (is_equal(tr3, tr4))
	{
		tr3 = tr2 = tr1;

		if (is_equal(tr1, tr2) && is_equal(tr3, tr2))
			std::cout << "Test done" << std::endl;
		else
			std::cout << "Test failed" << std::endl;
	}
	else
		std::cout << "Test failed" << std::endl;

	return 0;
}

bool is_equal(const Tree& tr1, const Tree& tr2)
{
	if (!tr1.init && !tr2.init)
		return true;
	else if (tr1.init && tr2.init)
		return is_equal(tr1.top, tr2.top);

	return false;
}

bool is_equal(const Node* n1, const Node* n2)
{
	if (n1->key    != n2->key    ||
		n1->height != n2->height ||
		n1->size   != n2->size)
	{
		return false;
	}

	if ((n1->left  && !n2->left)  || (!n1->left  && n2->left) ||
		(n1->right && !n2->right) || (!n1->right && n2->right))
	{
		return false;
	}

	if (n1->left && n2->left)
		return is_equal(n1->left, n2->left);

	else if (n1->right && n2->right)
		return is_equal(n1->right, n2->right);

	return true;
}
