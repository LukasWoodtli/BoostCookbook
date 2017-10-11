
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <assert.h>

/* From the Book:
 * If you want to avoid code bloat, try to write parsers in source files
 * and not in headers. Also take care of iterator types passed to the
 * boost::spirit::parse function, the fewer different types of iterators
 * you use, the smaller binary you'll get. */


struct date {
  unsigned short year;
  unsigned short month;
  unsigned short day;
};


date parse_date_time1(const std::string& s) {
  using boost::spirit::qi::_1;
  using boost::spirit::qi::ushort_;
  using boost::spirit::qi::char_;
  using boost::phoenix::ref;

  date res;
  const char* first = s.data();
  const char* const end = first + s.size();

  bool success = boost::spirit::qi::parse(first, end,
    ushort_[ ref(res.year) = _1] >> char('-') >>
    ushort_[ ref(res.month) = _1] >> char('-') >>
    ushort_[ ([&res](unsigned short s) {res.day = s;}) ] // lambdas can be used instead of bind
  );

  if (!success || first != end) {
    throw std::logic_error("Parsing failed");
  }

  return res;
}


date parse_date_time2(const std::string& s) {
  using boost::spirit::qi::_1;
  using boost::spirit::qi::uint_parser;
  using boost::spirit::qi::char_;
  using boost::phoenix::ref;

  // output type: unsiged short
  // radix: 10
  // digits from 2 to 2
  uint_parser<unsigned short, 10, 2, 2> u2_;

  // output type: unsiged short
  // radix: 10
  // digits from 4 to 4
  uint_parser<unsigned short, 10, 4, 4> u4_;

  date res;
  const char* first = s.data();
  const char* const end = first + s.size();

  bool success = boost::spirit::qi::parse(first, end,
    u4_[ ref(res.year) = _1] >> char('-') >>
    u2_[ ref(res.month) = _1] >> char('-') >>
    u2_[ ([&res](unsigned short s) {res.day = s;}) ] // lambdas can be used instead of bind
  );

  if (!success || first != end) {
    throw std::logic_error("Parsing failed");
  }

  return res;
}

int main() {
  date d = parse_date_time1("2012-12-31");
  assert(d.year == 2012);
  assert(d.month == 12);
  assert(d.day == 31);

  d = parse_date_time2("2013-11-01");
  assert(d.year == 2013);
  assert(d.month == 11);
  assert(d.day == 01);
  
}
