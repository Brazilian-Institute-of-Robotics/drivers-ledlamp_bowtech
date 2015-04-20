/*
 * BowtechDriver.hpp
 *
 *  Created on: Apr 16, 2015
 *      Author: diego
 */

#ifndef SRC_BOWTECHDRIVER_HPP_
#define SRC_BOWTECHDRIVER_HPP_

#include "iodrivers_base/Driver.hpp"
#include <iostream>


namespace ledlamp_bowtech
{

	class BowtechDriver : public iodrivers_base::Driver
	{
		static const int BOWTECH_MAX_PACKET_SIZE = 200;
		static const int BOWTECH_COMMAND_SIZE = 6;

		public:
			BowtechDriver();
			virtual ~BowtechDriver();
			void setAddress(uint8_t current_address, uint8_t new_address);
			void getAddress();
			void setLightLevel(uint8_t value, int address=-1);
			void setPowerUpLightLevel(uint8_t value, int address=-1);

		private:
			virtual int extractPacket(const uint8_t* buffer, size_t buffer_size) const;
			uint8_t checksum(uint8_t byte1, uint8_t byte2, uint8_t byte3);
	};

} /* namespace ledlamp_bowtech */

#endif /* SRC_BOWTECHDRIVER_HPP_ */
