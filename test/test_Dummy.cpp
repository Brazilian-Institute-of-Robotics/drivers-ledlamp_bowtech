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

	lamp.openSerial("/dev/ttyUSB0", 9600);

	lamp.setPowerUpLightLevel(50);
	usleep(1000000);
	for (int i=0; i < 4; ++i)
	{
	lamp.setLightLevel(5);
	usleep(1000000);
	lamp.setLightLevel(50);
	usleep(1000000);
	lamp.setLightLevel(100);
	usleep(1000000);
	}
//	lamp.getAddress();



	lamp.close();


	return 0;

}
