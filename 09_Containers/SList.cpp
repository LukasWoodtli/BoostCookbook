#include <list>

// C++11 has std::forward_list which is simmilar to boost::container::slist

#include <boost/pool/pool_alloc.hpp>
#include <boost/container/slist.hpp>

typedef boost::fast_pool_allocator<int> allocator_t;
typedef boost::container::slist<int, allocator_t> slist_t;



void list_specific(slist_t& list, slist_t::iterator it) {
	typedef slist_t::iterator iterator;

	// erasing element
	assert(*(++iterator(it)) = 776);
	assert(*it = 777);
	list.erase_after(it);
	assert(*it = 777);
	assert(*(++iterator(it)) = 775);


	// freeing memory
	boost::singleton_pool<boost::pool_allocator_tag, sizeof(int)>::release_memory();
}


void list_specific(std::list<int> list, std::list<int>::iterator it) {

	// erasing
	++it;
	assert(*it == 776);
	it = list.erase(it);
	assert(*it == 775);
	
}


template <class ListT>
void test_lists() {
	ListT list(10000, 0);

	// insertig values
	for (int i = 0; i < 1000; ++i) {
		list.insert(list.begin(), i);
	}

	// searching
	typedef typename ListT::iterator iterator;
	iterator it = std::find(list.begin(), list.end(), 777);
	assert(it != list.end());

	// erasing
	for (int i = 0; i < 100; ++i) {
		list.pop_front();
	}

	// iterator is still valid and points to same item
	assert(it != list.end());
	assert(*it == 777);

	// insertig other values
	for (int i = -100; i < 10; ++i) {
		list.insert(list.begin(), i);
	}

	// iterator is still valid and points to same item
	assert(it != list.end());
	assert(*it == 777);

	list_specific(list, it);
}



int main() {
	test_lists<slist_t>();
	test_lists<std::list<int>>();
}
