#ifndef NULLPTR_HPP
# define NULLPTR_HPP

# include "utils.hpp"

namespace ft{

	const class s_nullptr {
		private:
			void operator&() const;
		
		public:
			template<typename T>
			operator T*() const { return 0; }
			
			template<typename T, typename C>
			operator T C::*() const { return 0; }
	} t_nullptr = {};

} //namespace ft

#endif