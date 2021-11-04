#include "tree.hpp"
#include <iostream>

int main()
{
	Tree tree{};

	char request{};
	int k{};

	while (true)
	{
		std::cin >> request >> k;

		if (std::cin.good())
		{
			if (request == 'k')
				tree.insert(k);
			else if (request == 'n')
				std::cout << tree.cnt_less(k) << std::endl;
			else if (request == 'm')
			{
				if (k > tree.size() || k <= 0)
					return -1;

				std::cout << tree.k_min(k) << std::endl;
			}
		}
		else break;
	}
	return 0;
}