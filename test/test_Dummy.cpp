//#include <boost/test/unit_test.hpp>
#include "ledlamp_bowtech/BowtechDriver.hpp"

using namespace ledlamp_bowtech;

//BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
//{
//    ledlamp_bowtech::DummyClass dummy;
//    dummy.welcome();
//}


int main()
{

	BowtechDriver lamp;

	lamp.openSerial("/dev/ttyUSB1", 9600);

	usleep(10000);
	lamp.setPowerUpLightLevel(50);
	usleep(10000);
	lamp.setLightLevel(20);
//	usleep(10000);
//	lamp.setAddress(2, 10);
	usleep(10000);
	lamp.getAddress();
	usleep(10000);


	lamp.close();


	return 0;

}
