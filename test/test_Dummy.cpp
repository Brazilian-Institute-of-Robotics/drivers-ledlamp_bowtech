#include <boost/test/unit_test.hpp>
#include <ledlamp_bowtech/Dummy.hpp>

using namespace ledlamp_bowtech;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    ledlamp_bowtech::DummyClass dummy;
    dummy.welcome();
}
