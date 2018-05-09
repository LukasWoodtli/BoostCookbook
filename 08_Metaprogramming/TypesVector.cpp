#include <string>
#include <cassert>

#include <typeinfo>
#include <iostream>


#include <boost/mpl/vector.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/at.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/if.hpp>

///////////////////////////////////////////////////////////////////////////////
///////// Using type "vector of types" ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////////////////////
////////////////// Manipulating a vector of types /////////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct make_unsign;

struct make_constant;

struct no_change;

template <class Types, class Modifiers>
struct do_modifications {
	static_assert(boost::is_same<
		typename boost::mpl::size<Types>::type,
		typename boost::mpl::size<Modifiers>::type
		>::value, "Types and modifiers have different sizes");

	typedef boost::mpl::if_<
		boost::is_same<boost::mpl::_2, make_unsign>,      // if
		boost::make_unsigned<boost::mpl::_1>,             // then
		boost::mpl::if_<                                  // else if
			boost::is_same<boost::mpl::_2, make_constant>,  // then
			boost::add_const<boost::mpl::_1>,               // else
		boost::mpl::_1                                    // else
		>> binary_operator_t;

		typedef typename boost::mpl::transform<
			Types,
			Modifiers,
			binary_operator_t>::type type;
};



typedef boost::mpl::vector<make_unsign, no_change, make_constant, make_unsign> modifiers;
typedef boost::mpl::vector<int, char, short, long> my_types;
typedef do_modifications<my_types, modifiers>::type result_type;

static_assert(boost::is_same<
		typename boost::mpl::size<my_types>::type,
		typename boost::mpl::size<result_type>::type
		>::value, "Different sizes");


static_assert(boost::is_same<boost::mpl::at_c<result_type, 0>::type, unsigned int>::value, "Wrong type");
static_assert(boost::is_same<boost::mpl::at_c<result_type, 1>::type, char>::value, "Wrong type");
static_assert(boost::is_same<boost::mpl::at_c<result_type, 2>::type, const short>::value, "Wrong type");
static_assert(boost::is_same<boost::mpl::at_c<result_type, 3>::type, unsigned long>::value, "Wrong type");


template <typename T> std::string type_name();

int main() {
	typedef boost::mpl::vector<int, int, int> vector1_type;
	assert(foo_size<vector1_type>() == 3);
}
