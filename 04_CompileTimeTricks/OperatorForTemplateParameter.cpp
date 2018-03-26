#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <boost/type_traits/has_post_increment.hpp>
#include <boost/type_traits/has_pre_increment.hpp>

#include <iostream>

namespace detail {
	struct pre_inc_functor {
		template <class T>
		void operator()(T& value) const {
			std::cout << "Calling operator() of pre_inc_functor\n";
			++value;
		}
	};

	struct post_inc_functor {
		template <class T>
		void operator()(T& value) const {
			std::cout << "Calling operator() of post_inc_functor\n";
			value++;
		}
	};

	struct plus_assignable_functor {
		template <class T>
		void operator()(T& value) const {
			std::cout << "Calling operator() of plus_assignable_functor\n";
			value += T(1);
		}
	};

	struct plus_functor {
		template <class T>
		void operator()(T& value) const {
			std::cout << "Calling operator() of plus_functor\n";
			value = value + T(1);
		}
	};
}


template <class T>
void inc(T& value) {
	typedef detail::plus_functor step_0_t;

	typedef typename boost::conditional<boost::has_plus_assign<T>::value,
	detail::plus_assignable_functor, step_0_t>::type step_1_t;

	// C++11 has the same meta-function
	typedef typename std::conditional<boost::has_post_increment<T>::value,
	detail::post_inc_functor, step_1_t>::type step_2_t;

	typedef typename boost::conditional<boost::has_pre_increment<T>::value,
	detail::pre_inc_functor, step_2_t>::type step_3_t;

	step_3_t()(value); // default constructing functor. calling operator()
}



// tests

struct type_with_post_increment {

	type_with_post_increment(int i) : m_i{i} {}

	type_with_post_increment& operator++(int) {
		m_i++;
		return *this;
	}

	int m_i;
};


struct type_with_pre_and_post_increment {

	type_with_pre_and_post_increment(int i) : m_i{i} {}

	type_with_pre_and_post_increment& operator++() {
		++m_i;
		return *this;
	}

	type_with_pre_and_post_increment operator++(int) {
		type_with_pre_and_post_increment tmp(m_i);
		operator++(); // pre-increment
		return tmp;
	}

	int m_i;
};


struct type_with_pre_and_post_increment_and_plus_assign {

	type_with_pre_and_post_increment_and_plus_assign(int i) : m_i{i} {}

	type_with_pre_and_post_increment_and_plus_assign& operator++() {
		++m_i;
		return *this;
	}

	type_with_pre_and_post_increment_and_plus_assign operator++(int) {
		type_with_pre_and_post_increment_and_plus_assign tmp(m_i);
		operator++(); // pre-increment
		return tmp;
	}

	type_with_pre_and_post_increment_and_plus_assign& operator+=(const type_with_pre_and_post_increment_and_plus_assign& rhs) {
		m_i = rhs.m_i;
		return *this;
	}

	int m_i;
};

struct type_with_only_plus_assign {

	type_with_only_plus_assign(int i) : m_i{i} {}

	type_with_only_plus_assign& operator+=(const type_with_only_plus_assign& rhs) {
		m_i = rhs.m_i;
		return *this;
	}

	int m_i;
};

int main() {
	int i=0;
	std::cout << "int:\n";
	inc(i);
	std::cout << "Incremented: " << i << "\n\n";

	type_with_post_increment p(0);
	std::cout << "type_with_post_increment:\n";
	inc(p);
	std::cout << "Incremented: " << i << "\n\n";

	type_with_pre_and_post_increment pp(0);
	std::cout << "type_with_pre_and_post_increment:\n";
	inc(pp);
	std::cout << "Incremented: " << i << "\n\n";

	type_with_pre_and_post_increment_and_plus_assign pppa(0);
	std::cout << "type_with_pre_and_post_increment_and_plus_assign:\n";
	inc(pppa);
	std::cout << "Incremented: " << i << "\n\n";

	type_with_only_plus_assign pa(0);
	std::cout << "type_with_only_plus_assign:\n";
	inc(pa);
	std::cout << "Incremented: " << i << "\n\n";

}
