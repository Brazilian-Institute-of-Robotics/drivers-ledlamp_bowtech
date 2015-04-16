/*
 * BowtechDriver.hpp
 *
 *  Created on: Apr 16, 2015
 *      Author: diego
 */

#ifndef SRC_BOWTECHDRIVER_HPP_
#define SRC_BOWTECHDRIVER_HPP_

#include "iodrivers_base/Driver.hpp"


namespace ledlamp_bowtech {

class BowtechDriver : public iodrivers_base::Driver
{
	public:
		BowtechDriver();
		virtual ~BowtechDriver();
		void setAddress(uint8_t &current_address, uint8_t &new_address);
		void getAddress(void);
		void setLightLevel(uint8_t &value, uint8_t &address=-1);
		void setPowerUpLightLevel(uint8_t& value, uint8_t& address);

	private:
		virtual int extractPacket(const uint8_t* buffer, size_t buffer_size);
};

} /* namespace ledlamp_bowtech */

#endif /* SRC_BOWTECHDRIVER_HPP_ */
