#include <string>
#include <cassert>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/at.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/max_element.hpp>

template <class T0, class T1, class T2, class T3, class T4, 
    class T5>
struct variant {
    typedef boost::mpl::vector<T0, T1, T2, T3, T4, T5> types;
};

    
struct declared { unsigned char data[4096]; };

struct non_defined;


typedef variant<
    volatile int,
    const int,
    const long,
    declared,
    non_defined,
    std::string>::types types;

static_assert(not boost::mpl::empty<types>::value, "Types empty!");


static_assert(boost::is_same<non_defined, 
                boost::mpl::at_c<types, 4>::type>::value, "Wrong type!");


static_assert(boost::is_same<boost::mpl::back<types>::type, 
                std::string>::value, "Wrong type at back!");

/* the whole expression means "for each type in types, do `boost::remove_cv<>::type` and push back that type to the resulting vector. Return the resulting vector via `::type` */
typedef boost::mpl::transform<types, 
    boost::remove_cv<boost::mpl::_1>>::type noncv_types;

typedef boost::mpl::unique<noncv_types,
    boost::is_same<boost::mpl::_1, boost::mpl::_2>>::type unique_types;

static_assert(boost::mpl::size<unique_types>::value == 5, "Wrong size");


struct non_defined {}; // this needs to be defined now

/* `sizes_types`: a vector of integral constants—types representing numbers. The `sizes_types` typedef is actually the following type:
    
    struct boost::mpl::vector<
      struct boost::mpl::size_t<4>,
      struct boost::mpl::size_t<4>,
      struct boost::mpl::size_t<4096>,
      struct boost::mpl::size_t<1>,
      struct boost::mpl::size_t<32> 
    > */
typedef boost::mpl::transform<unique_types,
    boost::mpl::sizeof_<boost::mpl::_1>>::type sizes_types;

typedef boost::mpl::max_element<sizes_types>::type max_size_type;

static_assert(max_size_type::type::value == sizeof(declared), "Wrong max size");


template <class Vector>
int foo_size() {
    return boost::mpl::size<Vector>::value;
}

int main() {

    typedef boost::mpl::vector<int, int, int> vector1_type;
    assert(foo_size<vector1_type>() == 3);

}
