#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "includes/vector.hpp"

template <typename T, typename Allocator>
bool operator==(const ft::vector<T,Allocator>& lhs, const std::vector<T,Allocator>& rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

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
		std::cout << "ft_v == ft_v1 ?" << std::boolalpha << (ft_v1 == ft_v) << std::endl; 
	}
	{
		std::vector<int> v(6,6);
		ft::vector<int> ft_v1(v.begin(),v.end());
		std::cout << "ctor(iter1, iter2) [ft::std] " << ft_v1[0] << std::endl; 
		std::cout << "v1 == ft_v1 ?" << (ft_v1 == v) << std::endl; 
	}
	return 0;
}