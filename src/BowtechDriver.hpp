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
#include <sstream>
#include <iomanip>



namespace ledlamp_bowtech
{

	class BowtechDriver : public iodrivers_base::Driver
	{
		static const int BOWTECH_MAX_PACKET_SIZE = 200;
		static const int BOWTECH_COMMAND_SIZE = 6;

		public:
			BowtechDriver();
			virtual ~BowtechDriver();

			/**
			 * Sets the adress of a lamp to a new value
			 * @param current_address - Current address of the lamp
			 * @param new_address - New address for the lamp
			 */
			void setAddress(uint8_t current_address, uint8_t new_address, bool msg_header = false);

			/**
			 * Gets the adress of all conected lamps
			 */
			void getAddress(bool msg_header = false);

			/**
			 * Sets the light level of a specific lamp or sets the light
			 * level for all lamps (address < 0)
			 * @param value - Desired light level. Should belong to the
			 * 				  interval [1, 100]
			 * @param address - Address of the lamp whose light level will
			 * 					be changed. If address < 0, then the light
			 * 					level will be applied to all lamps. For
			 * 					changing the light level of a specific lamp,
			 * 					its address must be set in this variable [1, 255].
			 */
			void setLightLevel(uint8_t value, int address=-1, bool msg_header = false);

			/**
			 * Sets the default light level for when the lamp is powered up
			 * @param value - Desired power up light level. Should belong to the
			 * 				  interval [1, 100]
			 * @param address - Address of the lamp whose power up light level will
			 * 					be changed. If address < 0, then the power up light
			 * 					level will be applied to all lamps. For
			 * 					changing the power up light level of a specific lamp,
			 * 					its address must be set in this variable [1, 255].
			 */
			void setPowerUpLightLevel(uint8_t value, int address=-1, bool msg_header = false);

		private:
			virtual int extractPacket(const uint8_t* buffer, size_t buffer_size) const;
			uint8_t checksum(uint8_t byte1, uint8_t byte2, uint8_t byte3);
			void readMsg();
	};

} /* namespace ledlamp_bowtech */

#endif /* SRC_BOWTECHDRIVER_HPP_ */
