#include <algorithm>
#include <vector>
#include <set>
#include <deque>
#include <iterator>
#include <cstdint>
#include <iostream>
#include <locale>
#include <boost/lexical_cast.hpp>


template <class ContainerT>
std::vector<long int> container_to_longs(const ContainerT& container) {
    typedef typename ContainerT::value_type value_type;
    std::vector<long int> ret;
    typedef long int (*func_t)(const value_type&);
    func_t f = &boost::lexical_cast<long int, value_type>;
    std::transform(container.begin(), container.end(), std::back_inserter(ret), f);
    return ret;
}


int main() {
    int i = boost::lexical_cast<int>("100");
    assert(i == 100);

    // non-zero-terminated strings
    char chars[] = {'1', '0', '0'};
    i = boost::lexical_cast<int>(chars, 3);
    assert(i == 100);

    // bounds checking
    bool exceptionThrown = false;
    try {
        int16_t s = boost::lexical_cast<int16_t>("1000000");
        (void)s; // unused
        assert(false); // should not reach this
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cout << e.what() << "\n";
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    // syntax checking
    exceptionThrown = false;
    try {
        int i = boost::lexical_cast<int>("This is not a number!");
        (void)i;
        assert(false);
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cout << e.what() << "\n";
        exceptionThrown = true;
    }
    assert(exceptionThrown);

#if 0 // this only works if the locale is supported by the OS
    // locale
    std::locale::global(std::locale("de_CH"));
    // in Switzerland coma sign is used as decimal separator
    float f = boost::lexical_cast<float>("1,0");
    assert(f < 1.01 && f > 0.99);
#endif

    // containers
    std::set<std::string> str_set;
    str_set.insert("1");
    assert(container_to_longs(str_set).front() == 1);

    std::deque<const char*> char_deque;
    char_deque.push_front("1");
    char_deque.push_back("2");
    assert(container_to_longs(char_deque).front() == 1);
    assert(container_to_longs(char_deque).back() == 2);

    typedef boost::array<unsigned char, 2> element_t;
    boost::array<element_t, 2> arrays = {{ {{'1', '0'}}, {{'2', '0'}} }};
    assert(container_to_longs(arrays).front() == 10);
    assert(container_to_longs(arrays).back() == 20);

}
