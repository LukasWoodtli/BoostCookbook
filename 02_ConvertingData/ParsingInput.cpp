
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>


#include <stdexcept>
#include <assert.h>

/* From the Book:
 * If you want to avoid code bloat, try to write parsers in source files
 * and not in headers. Also take care of iterator types passed to the
 * boost::spirit::parse function, the fewer different types of iterators
 * you use, the smaller binary you'll get. */


/* There is a possibility to declare the parser in the header and implement
 * it in the source file.
 * See book. */

struct datetime {
  enum zone_offsets_t {
    OFFSET_NOT_SET,
    OFFSET_Z,
    OFFSET_UTC_PLUS,
    OFFSET_UTC_MINUS
  };

private:
  unsigned short year_;
  unsigned short month_;
  unsigned short day_;
  unsigned short hours_;
  unsigned short minutes_;
  unsigned short seconds_;
  zone_offsets_t zone_offset_type_;
  unsigned int zone_offset_in_min_;

  static void dt_assert(bool v, const char *msg) {
    if (!v) {
      throw std::logic_error("Assertion failed: " + std::string(msg));
    }
  }

public:
  datetime()
    : year_(0),
      month_(0),
      day_(0),
      hours_(0),
      minutes_(0),
      seconds_(0),
      zone_offset_type_(OFFSET_NOT_SET),
      zone_offset_in_min_(0)
  {}

    unsigned short year() const { return year_; }
    unsigned short month() const { return month_; }
    unsigned short day() const { return day_; }

    unsigned short hours() const { return hours_; }
    unsigned short minutes() const { return minutes_; }
    unsigned short seconds() const { return seconds_; }

    zone_offsets_t zone_offset_type() const { return zone_offset_type_; }
    unsigned int zone_offset_in_min() const { return zone_offset_in_min_; }

  void set_year(unsigned short year)
  {
    year_ = year;
  }

  void set_month(unsigned short month)
  {
    month_ =  month;
  }

  void set_day(unsigned short day)
  {
    day_ = day;
  }

  void set_hours(unsigned short hours)
  {
    hours_ = hours;
  }

  void set_minutes(unsigned short minutes)
  {
    minutes_ = minutes;
  }

  void set_seconds(unsigned short seconds)
  {
    seconds_ = seconds;
  }

  void set_zone_offset_type(zone_offsets_t zone_offset_type) {
    zone_offset_type_ = zone_offset_type;
  }

  void set_zone_offset_in_min(unsigned short zone_offset_in_min) {
    zone_offset_in_min_ = zone_offset_in_min;
  }

};


void set_zone_offset(datetime& dt, char sign, unsigned short hours, unsigned short minutes) {
  dt.set_zone_offset_type(sign == '+' ? datetime::OFFSET_UTC_PLUS : datetime::OFFSET_UTC_MINUS);
  dt.set_zone_offset_in_min(hours * 60 + minutes);
}


datetime parse_datetime(const std::string& s) {
  using boost::spirit::qi::_1;
  using boost::spirit::qi::_2;
  using boost::spirit::qi::_3;
  using boost::spirit::qi::uint_parser;
  using boost::spirit::qi::char_;
  using boost::phoenix::bind;
  using boost::phoenix::ref;

  datetime ret;

  // output type: unsiged short
  // radix: 10
  // digits from 2 to 2
  uint_parser<unsigned short, 10, 2, 2> u2_;

  // output type: unsiged short
  // radix: 10
  // digits from 4 to 4
  uint_parser<unsigned short, 10, 4, 4> u4_;

  boost::spirit::qi::rule<const char*, void()> timezone_parser
    = -( // unary minus means  optional rule
         // zero offset
         char_('Z')[ bind(&datetime::set_zone_offset_type, &ret, datetime::OFFSET_Z)]
         | // OR
         // Specific zone offset
         ((char_('+') | char_('-')) >> u2_ >> ':' >> u2_) [bind(&set_zone_offset, ref(ret), _1, _2, _3)]
    );


  boost::spirit::qi::rule<const char*, void()> date_parser =
       u4_[ bind(&datetime::set_year, &ret, _1) ] >> char_('-')
    >> u2_[ bind(&datetime::set_month, &ret, _1) ] >> char_('-')
    >> u2_[ bind(&datetime::set_day, &ret, _1) ];

  /* In C++11 boost::spirit::qi::rule<const char*, void()> 
   * this type erasure is not needed. Use `auto` instead. */
  auto time_parser =
    u2_[ bind(&datetime::set_hours, &ret, _1) ] >> char_(':') >>
    u2_[ bind(&datetime::set_minutes, &ret, _1) ] >> char_(':') >>
    u2_[ bind(&datetime::set_seconds, &ret, _1) ];

  const char* first = s.data();
  const char* const end = first + s.size();
  bool success = boost::spirit::qi::parse(first, end,
    ((date_parser >> char_('T') >> time_parser) | date_parser | time_parser)
      >> timezone_parser);

  if (!success || first != end) {
    throw std::logic_error("Parsing of '" + s + "' failed");
  }

  return ret;
}

int main() {
  datetime d = parse_datetime("2012-12-31");
  assert(d.year() == 2012);
  assert(d.month() == 12);
  assert(d.day() == 31);

  d = parse_datetime("2013-11-01");
  assert(d.year() == 2013);
  assert(d.month() == 11);
  assert(d.day() == 01);


  datetime d1  = parse_datetime("2012-10-20T10:00:00Z");
  assert(d1.year() == 2012);
  assert(d1.month() == 10);
  assert(d1.day() == 20);
  assert(d1.hours() == 10);
  assert(d1.minutes() == 0);
  assert(d1.seconds() == 0);
  assert(d1.zone_offset_type() == datetime::OFFSET_Z);
  assert(d1.zone_offset_in_min() == 0);

  datetime d2  = parse_datetime("2012-10-20T10:00:00");
  assert(d2.year() == 2012);
  assert(d2.month() == 10);
  assert(d2.day() == 20);
  assert(d2.hours() == 10);
  assert(d2.minutes() == 0);
  assert(d2.seconds() == 0);
  assert(d2.zone_offset_type() == datetime::OFFSET_NOT_SET);
  assert(d2.zone_offset_in_min() == 0);

  datetime d3  = parse_datetime("2012-10-20T10:00:00+09:15");
  assert(d3.year() == 2012);
  assert(d3.month() == 10);
  assert(d3.day() == 20);
  assert(d3.hours() == 10);
  assert(d3.minutes() == 0);
  assert(d3.seconds() == 0);
  assert(d3.zone_offset_type() == datetime::OFFSET_UTC_PLUS);
  assert(d3.zone_offset_in_min() == 9 * 60 + 15);

  datetime d4  = parse_datetime("2012-10-20-09:15");
  assert(d4.year() == 2012);
  assert(d4.month() == 10);
  assert(d4.day() == 20);
  assert(d4.hours() == 0);
  assert(d4.minutes() == 0);
  assert(d4.seconds() == 0);
  assert(d4.zone_offset_type() == datetime::OFFSET_UTC_MINUS);
  assert(d4.zone_offset_in_min() == 9 * 60 + 15);

  datetime d5  = parse_datetime("10:00:09+09:15");
  assert(d5.year() == 0);
  assert(d5.month() == 0);
  assert(d5.day() == 0);
  assert(d5.hours() == 10);
  assert(d5.minutes() == 0);
  assert(d5.seconds() == 9);
  assert(d5.zone_offset_type() == datetime::OFFSET_UTC_PLUS);
  assert(d5.zone_offset_in_min() ==  9 * 60 + 15);

}
