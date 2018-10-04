#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <list>
#include <vector>

void test_combine()
{
    std::vector<int> v;
    std::list<char> l;
    for (int i = 0; i < 5; ++i)
    {
        v.push_back(i);
        l.push_back(static_cast<char>(i) + 'a');
    }

    // !!!!! seg fault!! v.push_back(99);

    int ti;
    char tc;
    BOOST_FOREACH(boost::tie(ti, tc), boost::combine(v, l))
    {
        std::cout << '(' << ti << ',' << tc << ')' << '\n';
    }
}

int main()
{
    test_combine();

    return 0;
}
