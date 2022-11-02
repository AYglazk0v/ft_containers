#include <iostream>
#include <vector>
#include "includes/vector.hpp"

int main() {
	{
		ft::vector<int> ft_v(5, 5);
		std::vector<int> v(6,6);
		std::cout << "v " << v[0] << std::endl;
		std::cout << "ft " << ft_v[0] << std::endl;
	}
	{
		ft::vector<int> ft_v(5, 5);
		ft::vector<int> ft_v1(ft_v.begin(), ft_v.end());
		std::cout << "ctor(iter1, iter2) [ft::ft] " << ft_v1[0] << std::endl; 
	}
	{
		std::vector<int> v(6,6);
		ft::vector<int> ft_v1(v.begin(),v.end());
		std::cout << "ctor(iter1, iter2) [ft::std] " << ft_v1[0] << std::endl; 
	}
	return 0;
}