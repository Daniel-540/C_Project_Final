#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

#include "../include/models/GameModel.h"

BOOST_AUTO_TEST_SUITE(AddOneTest);

BOOST_AUTO_TEST_CASE(TestCases)
{
    GameModel* game = new GameModel();
}

BOOST_AUTO_TEST_SUITE_END()