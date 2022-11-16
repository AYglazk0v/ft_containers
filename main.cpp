#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include <map.hpp>
	#include "includes/iterators/RBTree_iterator.hpp"
	#include <stack.hpp>
	#include <vector.hpp>
	#include <set.hpp>
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
	ft::vector<int> secondvector_int = vector_int;
	std::cout << "[copy assign]" << std::endl;
	std::cout << "1 element: " << secondvector_int[1] << "; ";
	std::cout << "5 element: " << secondvector_int[5] << "; ";
	std::cout << "42 element: " << secondvector_int[42] << std::endl;

	std::cout << "[check equals elem]: ";
	if (vector_int != secondvector_int) {
		throw ("Vectors should be equal");
	}
	std::cout << "first vector and second vector equal" << std::endl;

	std::cout << "[check equals iterators]: ";

	ft::vector<int>::iterator it = vector_int.begin();
	ft::vector<int>::const_iterator it2 = secondvector_int.begin();
	ft::vector<int>::const_iterator ite = vector_int.end();
	ft::vector<int>::iterator ite2 = secondvector_int.begin();
	while (it!=ite && it2!=ite2) {
		if (*it!=*it2) {
			throw ("Vector' iterators should be equal");
		}
		++it;
		++it2;
	}
	std::cout << "iterators are equal" << std::endl;

	std::cout << "sizes v1: " << vector_int.size() << " v2: " << secondvector_int.size() << std::endl;
	std::cout << "max_sizes v1: " << vector_int.max_size() << " v2: " << secondvector_int.max_size() << std::endl;

	std::cout << "[check front()]: ";
	if (vector_int.front() != secondvector_int.front()) {
		throw ("front elements not equal");
	}
	std::cout << "front are equal" << std::endl;

	std::cout << "[check front()]: ";
	if (vector_int.back() != secondvector_int.back()) {
		throw ("front elements not equal");
	}
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
	std::cout <<"	v1 == v2 ?:" <<  std::boolalpha << (vector_int == secondvector_int) << std::endl;
	std::cout <<"	v1 != v2 ?:" << std::boolalpha <<  (vector_int != secondvector_int) << std::endl;
	std::cout <<"	v1 < v2 ?:" <<  std::boolalpha << (vector_int < secondvector_int) << std::endl;
	std::cout <<"	v1 <= v2 ?:" << std::boolalpha <<  (vector_int <= secondvector_int) << std::endl;
	std::cout <<"	v1 > v2 ?:" <<  std::boolalpha << (vector_int > secondvector_int) << std::endl;
	std::cout <<"	v1 >= v2 ?:" << std::boolalpha <<  (vector_int >= secondvector_int) << std::endl;


	std::cout << "____________________CHECK_STACK_________________________" << std::endl;
	std::cout << "[check empty()]: ";
	std::cout << "stack is empty? "<< std::boolalpha << stack_int.empty() << std::endl;

	std::cout << "[check push() and top()]: ";
	stack_int.push(4242);
	std::cout << "top element = " << stack_int.top() << std::endl;
	
	std::cout << "#create new stack"<< std::endl;
	stack_int = ft::stack<int>();
	std::cout << "	stack is empty? " << std::boolalpha <<stack_int.empty() << std::endl;
	for (int i = 1; i < 100; ++i)
		stack_int.push(i * i % 4242 + 2121);
	std::cout << "	stack is empty? " << std::boolalpha <<stack_int.empty() << std::endl;
	std::cout << "	top element = " << stack_int.top() << std::endl; 
	stack_int.pop();
	std::cout << "	popped element and new top =" << stack_int.top()<< std::endl;

	std::cout << "[check copy assign]: ";
	ft::stack<int> secondstack_int = stack_int;
	
	if (stack_int != secondstack_int) {
		throw ("Stacks should be equal");
	}
	std::cout << "stack1 equal stack2" << std::endl;

	std::cout << "[check size() and max_size()]: " << std::endl;
	std::cout << "sizes s1: " << stack_int.size() << " s2: " << secondstack_int.size() << std::endl;

	std::cout << "[pop secondstack and check operator's]: "<< std::endl;
	secondstack_int.pop();
	std::cout <<"	s1 == s2 ?:" <<  std::boolalpha << (stack_int == secondstack_int) << std::endl;
	std::cout <<"	s1 != s2 ?:" << std::boolalpha <<  (stack_int != secondstack_int) << std::endl;
	std::cout <<"	s1 < s2 ?:" <<  std::boolalpha << (stack_int < secondstack_int) << std::endl;
	std::cout <<"	s1 <= s2 ?:" << std::boolalpha <<  (stack_int <= secondstack_int) << std::endl;
	std::cout <<"	s1 > s2 ?:" <<  std::boolalpha << (stack_int > secondstack_int) << std::endl;
	std::cout <<"	s1 >= s2 ?:" << std::boolalpha <<  (stack_int >= secondstack_int) << std::endl;
	

	std::cout << "____________________CHECK_MAP___________________________" << std::endl;
	std::cout << "[check size() before clear()]: " << map_int.size() << std::endl;
	map_int.clear();
	std::cout << "[check size() after clear()]: " << map_int.size() << std::endl;
	for (int i = 1; i < 1000; ++i)
		map_int.insert(ft::make_pair(i, i * i % 4242 + 2121));
	std::cout << "[check operator[]]: ";
	std::cout << "1 element: " << map_int[1] << "; ";
	std::cout << "55 element: " << map_int[55] << "; ";
	std::cout << "555 element: " << map_int[555] << std::endl;
	
	std::cout << "[check copy assign]: ";
	ft::map<int, int> secondmap_int = map_int;
	std::cout << "1 element: " << secondmap_int[1] << "; ";
	std::cout << "55 element: " << secondmap_int[55] << "; ";
	std::cout << "555 element: " << secondmap_int[555] << "; " << std::endl;

	ft::map<int, int>::iterator mit = map_int.begin();
	ft::map<int, int>::iterator mit2 = secondmap_int.begin();
	ft::map<int, int>::iterator mite = map_int.end();
	ft::map<int, int>::iterator mite2 = secondmap_int.begin();

	std::cout << "[check equals iterators]: ";
	while (mit != mite && mit2 != mite2) {
		if (*mit!=*mit2) {
			throw ("Map's iterators should be equal");
		}
		++mit;
		++mit2;
	}
	std::cout << "iterators are equal" << std::endl;

	std::cout << "[check equals]: ";
	if (map_int != secondmap_int) {
		throw ("Maps should be equal");
	}
	std::cout << "maps equal" << std::endl;

	map_int[123] = 333;

	std::cout << "[check equals afte modification map_int]: ";
	if (map_int==secondmap_int) {
		throw ("Maps shouldn't be equal");
	}
	std::cout << "maps not equal" << std::endl;
	
	std::cout << "[check erase()]: ";
	map_int.erase(123);
	std::cout << "	check[123]:" << map_int[123] << std::endl;

	std::cout << "	Map size before clear " << map_int.size() << std::endl;
	map_int.erase(++(++(map_int.begin())));
	std::cout << "	Map size after erase() " << map_int.size() << std::endl;

	std::cout << "[check operator> and swap()]:" << std::endl; 
	if (map_int > secondmap_int) {
		std::cout << "	now first map is bigger than second" << std::endl;
		map_int.swap(secondmap_int);
		if (map_int > secondmap_int)
			throw ("Swap didn't work");
		std::cout << "	now second is bigger than first -> swap -- OK" << std::endl;
	}

	std::cout << "[check operator[] and find()]:" << std::endl; 
	map_int[5555] = 99999;
	map_int[5557] = 99599;
	mit = map_int.find(5555);
	std::cout << "	find(5555) element :" << mit->first << " " << mit->second << std::endl;

	std::cout << "[check count()]:" << std::endl; 
	std::cout << "	count of 5555 elements :" << map_int.count(5555) << std::endl;
	std::cout << "	count of 5556 elements :" << map_int.count(5556) << std::endl;
	std::cout << "	count of 5557 elements :" << map_int.count(5557) << std::endl;

	std::cout << "[check lower/upper bound and range]: " << std::endl;
	mit = map_int.lower_bound(5000);
	ft::map<int, int>::iterator upper = map_int.upper_bound(5000);
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> result = map_int.equal_range(5000);
	ft::map<int, int>::iterator res1 = result.first;
	ft::map<int, int>::iterator res2 = result.second;

	std::cout << "	lower bound element: " << mit->first << " " << mit->second << std::endl;
	std::cout << "	upper bound element: " << upper->first << " " << upper->second << std::endl;
	std::cout << "	equal range lower: " << res1->first << " " << res1->second << std::endl;
	std::cout << "	equal range upper: " << res2->first << " " << res2->second << std::endl;
	
	std::cout << "____________________CHECK_SET___________________________" << std::endl;
	ft::set<int> set_int;
	std::cout << "[check size() before clear()]: " << set_int.size() << std::endl;
	set_int.clear();
	std::cout << "[check size() after clear()]: " << set_int.size() << std::endl;
	for (int i = 0; i < 1000; ++i)
		set_int.insert(set_int.begin(), i);
	std::cout << "[check size() after loop]: " << set_int.size() << std::endl;
	std::cout << "[check find()]: ";
	std::cout << "1 element: " << *set_int.find(1) << "; ";
	std::cout << "55 element: " << *set_int.find(55) << "; ";
	std::cout << "555 element: " << *set_int.find(555) << std::endl;
	
	std::cout << "[check copy assign]: ";
	ft::set<int> second_set_int = set_int;
	std::cout << "1 element: " << *second_set_int.find(1) << "; ";
	std::cout << "55 element: " << *second_set_int.find(55) << "; ";
	std::cout << "555 element: " << *second_set_int.find(555) << "; " << std::endl;

	ft::set<int>::iterator sit = set_int.begin();
	ft::set<int>::iterator sit2 = second_set_int.begin();
	ft::set<int>::iterator site = set_int.end();
	ft::set<int>::iterator site2 = second_set_int.begin();

	std::cout << "[check equals iterators]: ";
	while (sit != site && sit2 != site2) {
		if (*sit != *sit2) {
			throw ("set's iterators should be equal");
		}
		++sit;
		++sit2;
	}
	std::cout << "iterators are equal" << std::endl;

	// std::cout << "[check equals]: ";
	// if (map_int != secondmap_int) {
	// 	throw ("Maps should be equal");
	// }
	// std::cout << "maps equal" << std::endl;

	// map_int[123] = 333;

	// std::cout << "[check equals afte modification map_int]: ";
	// if (map_int==secondmap_int) {
	// 	throw ("Maps shouldn't be equal");
	// }
	// std::cout << "maps not equal" << std::endl;
	
	// std::cout << "[check erase()]: ";
	// map_int.erase(123);
	// std::cout << "	check[123]:" << map_int[123] << std::endl;

	// std::cout << "	Map size before clear " << map_int.size() << std::endl;
	// map_int.erase(++(++(map_int.begin())));
	// std::cout << "	Map size after erase() " << map_int.size() << std::endl;

	// std::cout << "[check operator> and swap()]:" << std::endl; 
	// if (map_int > secondmap_int) {
	// 	std::cout << "	now first map is bigger than second" << std::endl;
	// 	map_int.swap(secondmap_int);
	// 	if (map_int > secondmap_int)
	// 		throw ("Swap didn't work");
	// 	std::cout << "	now second is bigger than first -> swap -- OK" << std::endl;
	// }

	// std::cout << "[check operator[] and find()]:" << std::endl; 
	// map_int[5555] = 99999;
	// map_int[5557] = 99599;
	// mit = map_int.find(5555);
	// std::cout << "	find(5555) element :" << mit->first << " " << mit->second << std::endl;

	// std::cout << "[check count()]:" << std::endl; 
	// std::cout << "	count of 5555 elements :" << map_int.count(5555) << std::endl;
	// std::cout << "	count of 5556 elements :" << map_int.count(5556) << std::endl;
	// std::cout << "	count of 5557 elements :" << map_int.count(5557) << std::endl;

	// std::cout << "[check lower/upper bound and range]: " << std::endl;
	// mit = map_int.lower_bound(5000);
	// ft::map<int, int>::iterator upper = map_int.upper_bound(5000);
	// ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> result = map_int.equal_range(5000);
	// ft::map<int, int>::iterator res1 = result.first;
	// ft::map<int, int>::iterator res2 = result.second;

	// std::cout << "	lower bound element: " << mit->first << " " << mit->second << std::endl;
	// std::cout << "	upper bound element: " << upper->first << " " << upper->second << std::endl;
	// std::cout << "	equal range lower: " << res1->first << " " << res1->second << std::endl;
	// std::cout << "	equal range upper: " << res2->first << " " << res2->second << std::endl;

	(void)argc;
	(void)argv;
	return (0);
}