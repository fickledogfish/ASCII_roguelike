#include <boost/test/unit_test.hpp>
#include "../lib/random/random.hpp"

BOOST_AUTO_TEST_SUITE(librandom)

BOOST_AUTO_TEST_CASE(simple_random_number) {
    int j = rnd::random_int(0, 10);
    BOOST_CHECK(j >= 0 && j <= 10);
}

BOOST_AUTO_TEST_SUITE_END()
