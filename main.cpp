#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	std::cout << "____________________CHECK_VECTOR________________________" << std::endl;
	vector_int.clear();

	for (int i = 1; i<100; ++i)
		vector_int.push_back(i*(3%i)+12);
	std::cout << "1 element: " << vector_int[1] << "; ";
	std::cout << "5 element: " << vector_int[5] << "; ";
	std::cout << "42 element: " << vector_int[42] << std::endl;
	ft::vector<int> second_vector_int = vector_int;
	std::cout << "[copy assign]" << std::endl;
	std::cout << "1 element: " << second_vector_int[1] << "; ";
	std::cout << "5 element: " << second_vector_int[5] << "; ";
	std::cout << "42 element: " << second_vector_int[42] << std::endl;

	std::cout << "[check equals elem]: ";
	if (vector_int != second_vector_int) {
		throw ("Vectors should be equal");
	}
	std::cout << "first vector and second vector equal" << std::endl;

	std::cout << "[check equals iterators]: ";

	ft::vector<int>::iterator it = vector_int.begin();
	ft::vector<int>::const_iterator it2 = second_vector_int.begin();
	ft::vector<int>::const_iterator ite = vector_int.end();
	ft::vector<int>::iterator ite2 = second_vector_int.begin();
	while (it!=ite && it2!=ite2) {
		if (*it!=*it2)
			throw ("Vector' iterators should be equal");
		++it;
		++it2;
	}
	std::cout << "iterators are equal" << std::endl;

	std::cout << "sizes v1: " << vector_int.size() << " v2: " << second_vector_int.size() << std::endl;
	std::cout << "max_sizes v1: " << vector_int.max_size() << " v2: " << second_vector_int.max_size() << std::endl;

	std::cout << "[check front()]: ";
	if (vector_int.front() != second_vector_int.front())
		throw ("front elements not equal");
	std::cout << "front are equal" << std::endl;

	std::cout << "[check front()]: ";
	if (vector_int.back() != second_vector_int.back())
		throw ("front elements not equal");
	std::cout << "back are equal" << std::endl;

	std::cout << "[check assign]: " << std::endl;
	std::cout << "	vector size before: " << vector_int.size() << std::endl;
	vector_int.assign(10000, 100);
	std::cout << "	vector size after: " << vector_int.size() << std::endl;
	int lastVectorElement = vector_int.back();
	std::cout << "	last elem:" << lastVectorElement << std::endl;

	std::cout << "[check pop]: " << std::endl;
	vector_int.pop_back();
	std::cout << "	vector size after pop: " << vector_int.size() << std::endl;
	
	std::cout << "[check erase]: " << std::endl;
	vector_int.erase(vector_int.begin(), vector_int.begin() + 498);
	vector_int.erase(vector_int.begin());

	std::cout << "	vector size after remove some elements: " << vector_int.size() << std::endl;

	std::cout << "[check operator's]: "<< std::endl;
	std::cout <<"	v1 = v2 ?:" <<  std::boolalpha << (vector_int == second_vector_int) << std::endl;
	std::cout <<"	v1 != v2 ?:" << std::boolalpha <<  (vector_int != second_vector_int) << std::endl;
	std::cout <<"	v1 < v2 ?:" <<  std::boolalpha << (vector_int < second_vector_int) << std::endl;
	std::cout <<"	v1 <= v2 ?:" << std::boolalpha <<  (vector_int <= second_vector_int) << std::endl;
	std::cout <<"	v1 > v2 ?:" <<  std::boolalpha << (vector_int > second_vector_int) << std::endl;
	std::cout <<"	v1 >= v2 ?:" << std::boolalpha <<  (vector_int >= second_vector_int) << std::endl;

	return (0);
}