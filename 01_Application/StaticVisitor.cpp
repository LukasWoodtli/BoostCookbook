#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <iostream>


typedef boost::any any_cell_t;
typedef std::vector<any_cell_t> any_db_row_t;

// dummy
any_db_row_t any_get_row(const char* query) {
	(void)query;

	any_db_row_t row;
	row.push_back(10);
	row.push_back(10.1f);
	row.push_back(10.2d);
	row.push_back("hello again");
	return row;
}

// traditional way //////////////////
struct db_sum : std::unary_function<boost::any, void> {

private:
	double& sum_;
	
public:
	explicit db_sum(double& sum) :
		sum_(sum)
	{}

	void operator()(const any_cell_t& value) {
		const std::type_info& ti = value.type();
		if (ti == typeid(int)) {
			sum_ += boost::any_cast<int>(value);
		} else if (ti == typeid(float)) {
			sum_ += boost::any_cast<float>(value);
		} else if (ti == typeid(double)) {
			sum_ += boost::any_cast<double>(value);
		}
	}
};




// boost way //////////////////
typedef boost::variant<int, float, double, std::string> cell_t;
typedef std::vector<cell_t> db_row_t;

// dummy
db_row_t get_row(const char* query) {
	(void)query;

	db_row_t row;
	row.push_back(10);
	row.push_back(10.1f);
	row.push_back(10.2d);
	row.push_back("hello again");
	return row;
}

struct db_sum_visitor : public boost::static_visitor<double> { // template param: return value of operator()
	double operator()(int value) const {
		return value;
	}

	double operator()(float value) const {
		return value;

	}

	double operator()(double value) const {
		return value;
	}

	double operator()(const std::string& value) const {
		(void)value;
		return 0.0;
	}
};


int main(void) {
	// traditional way
	any_db_row_t any_row = any_get_row("Query: ...");
	double res = 0.0;

	std::for_each(any_row.begin(), any_row.end(), db_sum(res));
	std::cout << "Sum of arithmetic types in row (boost::any) is: " << res << "\n";


	// boost way
	db_row_t row = get_row("Query: ...");
	res = 0.0;
	for(const auto& it: row)
		res += boost::apply_visitor(db_sum_visitor(), it);

	std::cout << "Sum of arithmetic types in row (boost::variant) is: " << res << "\n";

	return 0;
}