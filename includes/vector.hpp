/*
// Vector -- последовательный контейнер, который инкапсулирует динамический массив.
// Сложность (эффективность) обычныйх операций над векторами таков:
//		Произвольный доступ -- константа О(1).
//		Вставка или удаление элементов в конце -- О(1)+.
//		Вставка или удаление элементов - линейно по расстоянию до конца вектора О(n).
//		Работа с размером вектора -- О(1).
//		Удаление элеметов из вектора -- О(n).
// Использованные материалы:
//		https://en.cppreference.com/w/cpp/container/vector
//		https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf
//		https://eel.is/c++draft/vector
//		https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_vector.h
*/

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils/utils.h"

namespace ft {

	template <typename T, typename Allocator = std::allocator<T> >
	class vector {
		
		public:
//types:
			typedef	T											value_type;
			typedef	Allocator									allocator_type;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef	std::size_t									size_type;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef	std::ptrdiff_t								difference_type;
			typedef	ft::random_access_iterator<pointer>			iterator;
			typedef	ft::random_access_iterator<const_pointer>	const_iterator;
			typedef	ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		private:
			allocator_type	alloc_;
			pointer			ptr_start_;
			pointer			ptr_for_data_;
			pointer 		ptr_end_;

		public:
//construct/copy/destroy:
			explicit vector(const Allocator& alloc = Allocator()):
									alloc_(alloc),
									ptr_start_(t_nullptr),
									ptr_for_data_(t_nullptr),
									ptr_end_(t_nullptr)
			{}

			explicit vector(size_t n, const value_type& value = value_type(),
					const allocator_type& alloc = allocator_type()): alloc_(alloc),
																	ptr_start_(alloc_.allocate(n)),
																	ptr_for_data_(ptr_start_),
																	ptr_end_(ptr_start_ + n) {
				while (ptr_for_data_ != ptr_end_) {
					alloc_.construct(ptr_for_data_++, value);
				}
			}

			template<typename InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<ft::is_iter<InputIterator>::value, InputIterator>::type* = t_nullptr):
					alloc_(alloc) {
				if (first > last) {
					throw std::length_error("vector");
				}
				difference_type n = ft::distance(first, last);
				ptr_start_ = alloc_.allocate(n);
				ptr_end_ = ptr_start_ + n;
				ptr_for_data_ = ptr_start_;
				while (first != last){
					alloc_.construct(ptr_for_data_++, *first++);
				}
			}

			vector (const vector& rhs) {
				if (rhs.ptr_start_ > rhs.ptr_end_) {
					throw std::length_error("vector");
				}
				alloc_ = rhs.alloc_;
				difference_type n = ft::distance(rhs.ptr_start_, rhs.ptr_end_);
				ptr_start_ = alloc_.allocate(n);
				ptr_end_ = ptr_start_ + n;
				ptr_for_data_ = ptr_start_;
				pointer rhs_start_ = rhs.ptr_start_;
				while (rhs_start_ != rhs.ptr_for_data_) {
					alloc_.construct(ptr_for_data_++, *rhs_start_++);
				}
			}

			~vector() {
				clear();
				alloc_.deallocate(ptr_start_, capacity());
			}

			vector &operator=(const vector& rhs) {
				if (*this == rhs) {
					return *this;
				}
				if (rhs.ptr_start_ > rhs.ptr_end_) {
					throw std::length_error("vector");
				}
				clear();
				alloc_.deallocate(ptr_start_, capacity());
				alloc_ = rhs.alloc_;
				difference_type n = ft::distance(rhs.ptr_start_, rhs.ptr_end_);
				ptr_start_ =  alloc_.allocate(n);
				ptr_end_ = ptr_start_ + n;
				ptr_for_data_ = ptr_start_;
				pointer rhs_start = rhs.ptr_start_;
				while (rhs_start != rhs.ptr_for_data_) {
					alloc_.construct(ptr_for_data_++, *rhs_start++);
				}
				return *this;
			}

			template <typename InputIterator>
			void assign(InputIterator first, InputIterator last,
						typename ft::enable_if<ft::is_iter<InputIterator>::value, InputIterator>::type* = t_nullptr) {
				if (first > last) {
					throw std::length_error("vector::vector");
				}
				clear();
				difference_type n = ft::distance(first, last);
				if ((size_type) n > capacity()) {
					alloc_.deallocate(ptr_start_, capacity());
					ptr_start_ = alloc_.allocate(n);
					ptr_end_ = ptr_start_ + n;
				}
				ptr_for_data_ = ptr_start_;
				while (first != last){
					alloc_.construct(ptr_for_data_++, *first++);
				}
			}

			void assign(size_type n, const value_type& u) {
				clear();
				if ((size_type)n > capacity()) {
					alloc_.deallocate(ptr_start_, capacity());
					ptr_start_ = alloc_.allocate(n);
					ptr_end_ = ptr_start_ + n;
				}
				ptr_for_data_ = ptr_start_;
				for (size_type i = 0; i < n; ++i){
					alloc_.construct(ptr_for_data_++, u);
				}
			}

			allocator_type get_allocator() const { return alloc_; }

// iterators:
			iterator begin() { return iterator(ptr_start_); }
			const_iterator begin() const { return const_iterator(ptr_start_); }
			iterator end() { return iterator(ptr_for_data_); }
			const_iterator end() const { return const_iterator(ptr_for_data_); }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return reverse_iterator(begin()); }

// capacity:
			size_type size() const { return (ptr_for_data_ - ptr_start_); }
			size_type max_size()const { return (allocator_type().max_size()); }
			
			void resize(size_type sz, value_type c = value_type()) {
				if (sz > max_size()) {
					throw std::length_error("vector");
				} else if (sz < size()) {
					while (sz < size()) {
						alloc_.destroy(--ptr_for_data_);
					}
				} else {
					if (capacity() > sz);
					else if (capacity() * 2 < sz) {
						reserve(sz);
					} else {
						reserve (capacity() * 2);
					}
					while (size() < sz) {
						alloc_.construct(ptr_for_data_++, c);
					}
				}
			}

			size_type capacity() const { return (ptr_end_ - ptr_start_); }

			bool empty() const {
				if (size() == 0) {
					return true;
				}
				return false;
			}

			void reserve(size_type n) {
				if (n > max_size()) {
					throw std::length_error("vector");
				} else if (n > capacity()) {
					pointer prev_start = ptr_start_;
					pointer prev_start_for_dealloc = ptr_start_;
					pointer prev_end = ptr_for_data_;
					size_type prev_capasity = capacity();
					ptr_start_ = alloc_.allocate(n);
					ptr_end_ = ptr_start_ + n;
					ptr_for_data_ = ptr_start_;
					while (prev_start != prev_end) {
						alloc_.construct(ptr_for_data_++, *prev_start);
						alloc_.destroy(prev_start++);
					}
					alloc_.deallocate(prev_start_for_dealloc, prev_capasity);
				}
			}

// element access:
			reference operator[](size_type n) { return *(ptr_start_ + n); }
			const reference operator[](size_type n) const { return *(ptr_start_ + n); }

			const reference at(size_type n) const {
				if (n >= size()) {
					throw std::length_error("vector");
				}
				return ((*this)[n]);
			}
			
			reference at(size_type n) {
				if (n >= size()) {
					throw std::length_error("vector");
				}
				return ((*this)[n]);
			}

			reference front() { return *ptr_start_; }
			const_reference front() const { return *ptr_start_; }
			reference back() { return *(ptr_for_data_ - 1); }
			const_reference back() const { return *(ptr_for_data_ - 1); }
	
// modifiers:
		public:		
			void push_back(const value_type& value) {
				if (ptr_for_data_ == ptr_end_) {
					if (size() == 0) {
						alloc_.deallocate(ptr_start_, capacity());
						ptr_start_ = alloc_.allocate(1);
						ptr_end_ = ptr_start_ + 1;
						ptr_for_data_ = ptr_start_;
					} else {
						reserve(size() * 2);
					}
				}
				alloc_.construct(ptr_for_data_++, value);
			}

			void pop_back() {
				alloc_.destroy(--ptr_for_data_);
			}

			iterator insert(iterator position, const value_type& x) {
				pointer pos = &(*position);
				if (capacity() == 0) {
					ptr_start_ = alloc_.allocate(1);
					ptr_end_ = ptr_start_ + 1;
					ptr_for_data_ = ptr_start_;
					alloc_.construct(ptr_for_data_++, x);
					return iterator(ptr_start_);
				} else if (capacity() >= size() + 1) {
					pointer tmp = ptr_for_data_;
					while (pos != tmp--) {
						alloc_.construct(tmp + 1, *tmp);
					}
					alloc_.construct(tmp, x);
					ptr_for_data_++;
					return iterator(tmp);
				} else {
					difference_type n = pos - ptr_start_;
					pointer prev_start = ptr_start_;
					pointer prev_start_for_dealloc = ptr_start_;
					pointer prev_end = ptr_for_data_;
					size_type prev_capacity = capacity();
					ptr_start_ = alloc_.allocate(prev_capacity * 2);
					ptr_end_ = ptr_start_ = ptr_start_ + (prev_capacity * 2);
					ptr_for_data_ = ptr_start_;
					while (prev_start != pos) {
						alloc_.construct(ptr_for_data_++, *prev_start);
						alloc_.destroy(prev_start++);
					}
					alloc_.construct(ptr_for_data_++, x);
					while (prev_start != prev_end) {
						alloc_.construct(ptr_for_data_++, *prev_start);
						alloc_.destroy(prev_start++);
					}
					alloc_.deallocate(prev_start_for_dealloc, prev_capacity);
					return iterator(ptr_start_ + n);
				}
			}

			void insert(iterator position, size_type n, const value_type& x) {
				pointer pos = &(*position);
				if (n == 0) {
					return ;
				}
				if (size() + n > max_size()) {
					throw std::length_error("vector");
				}
				if (capacity() >= size() + n) {
					pointer tmp = ptr_for_data_;
					while (pos != tmp--) {
						alloc_.construct(tmp + n, *tmp);
					}
					for (size_type i = 0; i < n; ++i) {
						alloc_.construct(tmp + i, x);
					}
					ptr_for_data_ += n;
				} else {
					pointer prev_start = ptr_start_;
					pointer prev_start_for_dealloc = ptr_start_;
					pointer prev_end = ptr_for_data_;
					size_type prev_size = size();
					size_type prev_capacity = capacity();
					if (prev_capacity * 2 > n + prev_size) {
						ptr_start_ = alloc_(prev_capacity * 2);
						ptr_end_ = ptr_start_ + ( prev_capacity * 2);
					} else {
						ptr_start_ = alloc_.allocate(n + prev_size);
						ptr_end_ = ptr_start_ + prev_size + n;
					}
					ptr_for_data_ = ptr_start_;
					while (prev_start != pos) {
						alloc_.construct(ptr_for_data_++, *prev_start);
						alloc_.destroy(prev_start++);
					}
					for (size_type i = 0; i < n; ++i) {
						alloc_.construct(ptr_for_data_++, x);
					}
					while (prev_start != prev_end) {
						alloc_.construct(ptr_for_data_++, *prev_start);
						alloc_.destroy(prev_start++);
					}
					alloc_.deallocate(prev_start_for_dealloc, prev_capacity);
				}
			}

			template<typename InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<ft::is_iter<InputIterator>::value, InputIterator>::type* = t_nullptr) {
				if (first > last || position < begin() || position > end()) {
					throw std::logic_error("vector");
				}
				pointer pos = &(*position);
				difference_type n = ft::distance(first, last);
				if (n == 0) {
					return ;
				}
				if (size() + n > max_size()) {
					throw std::length_error("vector");
				}
				if (capacity() >= size() + n) {
					pointer tmp = ptr_for_data_;
					while (pos != tmp--) {
						alloc_.construct(tmp + n, *tmp);
					}
					for (size_type i = 0; i < (size_type)n; ++i) {
						alloc_.construct(tmp + i, *first++);
					}
					ptr_for_data_ += n;
				} else {
					pointer prev_start = ptr_start_;
					pointer prev_start_for_dealloc = ptr_start_;
					pointer prev_end = ptr_for_data_;
					size_type prev_size = size();
					size_type prev_capacity = capacity();
					if (prev_capacity * 2 > (size_type)n + prev_size){
						ptr_start_ = alloc_.allocate(prev_capacity * 2);
						ptr_end_ = ptr_start_ + (prev_capacity * 2);
					} else {
						ptr_start_ = alloc_.allocate(n + prev_size);
						ptr_end_ = ptr_start_ + n + prev_size; 
					}
					ptr_for_data_ = ptr_start_;
					while (prev_start != pos) {
						alloc_.construct(ptr_for_data_++, *prev_start);
						alloc_.destroy(prev_start++);
					}
					while (first != last) {
						alloc_.construct(ptr_for_data_++, *first++);
					}
					while (prev_start != prev_end) {
						alloc_.construct(ptr_for_data_++, *prev_start);
						alloc_.destroy(prev_start++);
					}
					alloc_.deallocate(prev_start_for_dealloc, prev_capacity);
				}
			}

			iterator erase(iterator position) {
				pointer pos = &(*position);
				alloc_.destroy(pos);
				for (; pos != ptr_for_data_ - 1; ++pos) {
					alloc_.construct(pos, *(pos + 1));
				}
				alloc_.destroy(--ptr_for_data_);
				return position;
			}

			iterator erase(iterator first, iterator last) {
				if (first > last) {
					std::length_error("vector");
				}
				pointer ptr_first = &(*first);
				pointer ptr_last = &(*last);
				pointer tmp  = ptr_first;
				while (tmp != ptr_last) {
					alloc_.destroy(tmp++);
				}
				tmp = ptr_first;
				while (ptr_last != ptr_for_data_) {
					alloc_.construct(tmp++, *ptr_last++);
				}
				ptr_for_data_ = tmp;
				return first;
			}

			void swap(vector& x) {
				allocator_type tmp_alloc = x.alloc_;
				pointer tmp_start = x.ptr_start_;
				pointer tmp_ptr_for_data = x.ptr_for_data_;
				pointer tmp_end = x.ptr_end_;
				x.alloc_ = alloc_;
				x.ptr_start_ = ptr_start_;
				x.ptr_for_data_ = ptr_for_data_;
				x.ptr_end_ = ptr_end_;
				alloc_ = tmp_alloc;
				ptr_start_ = tmp_start;
				ptr_end_ = tmp_end;
				ptr_for_data_ = tmp_ptr_for_data;
			}

			void clear() {
				while (ptr_for_data_ != ptr_start_) {
					alloc_.destroy(--ptr_for_data_);
				}
			}

//Non-member function:
			template <typename U, typename Allocator_f>
			friend bool operator==(const vector<U,Allocator_f>& lhs, const vector<U,Allocator_f>& rhs);

			template <typename U, typename Allocator_f>
			friend bool operator!=(const vector<U,Allocator_f>& lhs, const vector<U,Allocator_f>& rhs);

			template <typename U, typename Allocator_f>
			friend bool operator< (const vector<U,Allocator_f>& lhs, const vector<U,Allocator_f>& rhs);

			template <typename U, typename Allocator_f>
			friend bool operator> (const vector<U,Allocator_f>& lhs,const vector<U,Allocator_f>& rhs);

			template <typename U, typename Allocator_f>
			friend bool operator<=(const vector<U,Allocator_f>& lhs, const vector<U,Allocator_f>& rhs);

			template <typename U, typename Allocator_f>
			friend bool operator>=(const vector<U,Allocator_f>& lhs, const vector<U,Allocator_f>& rhs);

	}; //class vector

//Non-member function overloads:
  
	template <typename T, typename Allocator>
	bool operator==(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, typename Allocator>
	bool operator!=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return (!(lhs == rhs));
	}

	template <typename T, typename Allocator>
	bool operator< (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, typename Allocator>
	bool operator> (const vector<T,Allocator>& lhs,const vector<T,Allocator>& rhs) {
		return (rhs < lhs);
	}

	template <typename T, typename Allocator>
	bool operator<=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return !(rhs < lhs);
	}

	template <typename T, typename Allocator>
	bool operator>=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return !(lhs < rhs);
	}

// specialized algorithms:
	template <typename T, typename Allocator>
	void swap(vector<T,Allocator>& lhs, vector<T,Allocator>& rhs) {
		lhs.swap(rhs);
	}

} //namespace ft

#endif