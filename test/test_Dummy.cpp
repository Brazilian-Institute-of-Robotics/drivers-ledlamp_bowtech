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
	std::vector<int> address_list;
	address_list.clear();
	BowtechDriver lamp;


	lamp.openSerial("/dev/ttyUSB0", 9600);
	usleep(10000);

//	lamp.setCmdLabel("<L>");

	lamp.setPowerUpLightLevel(60);
	usleep(10000);

	lamp.setLightLevel(40);
	usleep(10000);


	lamp.close();


	std::cout << "LISTA DE ENDEREÇOS" << std::endl;
	for (int i=0; i < address_list.size(); ++i)
	{
		std::cout << address_list[i] << std::endl;
	}


	return 0;

}
