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
				std::cout << tree.cnt_less(k) << " ";
			else if (request == 'm')
			{
				if (k <= 0)
				{
					std::cout << "ERROR: K min is less than zero" << std::endl;
					return -1;					
				}

				if (k > tree.size())
				{
					std::cout << "ERROR: K min is greater than tree size" << std::endl;
					return -1;
				}
				
				std::cout << tree.k_min(k) << " ";
			}
		}
		else break;
	}
	return 0;
}