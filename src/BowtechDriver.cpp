/*
 * BowtechDriver.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: diego
 */

#include "BowtechDriver.hpp"

namespace ledlamp_bowtech {

	BowtechDriver::BowtechDriver() : iodrivers_base::Driver(6)
	{
		// TODO Auto-generated constructor stub
	}

	BowtechDriver::~BowtechDriver()
	{
		// TODO Auto-generated destructor stub
	}


	void BowtechDriver::setAddress(uint8_t& current_address, uint8_t& new_address)
	{

	}

	void BowtechDriver::getAddress(void)
	{

	}

	void BowtechDriver::setLightLevel(uint8_t& value, uint8_t& address)
	{

	}

	void BowtechDriver::setPowerUpLightLevel(uint8_t& value, uint8_t& address)
	{

	}

	int BowtechDriver::extractPacket(const uint8_t* buffer, size_t buffer_size)
	{

	}

} /* namespace ledlamp_bowtech */
