#include <set>
#include <fstream>
#include "../tree.hpp"
#include <ctime>

void gentest(char* test_fname, char* answ_fname);

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Not enough arguments" << std::endl;
		return -1;
	}

	gentest(argv[1], argv[2]);

	return 0;
}

void gentest(char* test_fname, char* answ_fname)
{
	std::srand(std::time(nullptr));

	std::set<int> keys;
	std::fstream test{test_fname, std::ios::out}, 
				 answ{answ_fname, std::ios::out};

	char request{};
	int k{};

	while (keys.size() != 100)
	{
		request = rand() % 3;
		k = rand() % 1000 - 500;

		if (request == 0)
		{
			if (keys.find(k) == keys.cend())
			{
				test << "k " << k << std::endl;
				keys.insert(k);
			}
		}
		else if (request == 1)
		{
			test << "n " << k << std::endl;
			auto it = keys.lower_bound(k);
			answ << std::distance(keys.cbegin(), it) << std::endl;
		}
		else if (request == 2)
		{
			if (k > keys.size() || k <= 0)
				continue;

			test << "m " << k << std::endl;                

			auto it = keys.cbegin();
			advance(it, k - 1);
			answ << *it << std::endl;
		}
	}
}