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
		static const int BROADCAST_ADDRESS = 0x52;

		public:
			BowtechDriver();
			virtual ~BowtechDriver();

			/**
			 * Sets the adress of a lamp to a new value
			 * @param current_address - Current address of the lamp
			 * @param new_address - New address for the lamp
			 */
			void setAddress(uint8_t current_address, uint8_t new_address);

			/**
			 * Gets the adress of all conected lamps
			 * @param address_list - return a list of all available lamp address
			 */
			void getAddress(std::vector<int>* address_list);

			/**
			 * Sets the light level of a specific lamp or sets the light
			 * level for all lamps (BROADCAST_ADDRESS)
			 * @param value - Desired light level. Should belong to the
			 * 				  interval [0.0, 1.0]
			 * @param address - Address of the lamp whose light level will
			 * 					be changed. If address is equal to
			 * 					BROADCAST_ADDRESS, then the light
			 * 					level will be applied to all lamps. For
			 * 					changing the light level of a specific lamp,
			 * 					its address must be set in this variable [1, 255].
			 */
			void setLightLevel(float value, uint8_t address=BROADCAST_ADDRESS);

			/**
			 * Sets the default light level for when the lamp is powered up
			 * @param value - Desired power up light level. Should belong to the
			 * 				  interval [0.0, 1.0]
			 * @param address - Address of the lamp whose power up light level will
			 * 					be changed. If address is equal to
			 * 					BROADCAST_ADDRESS, then the power up light
			 * 					level will be applied to all lamps. For
			 * 					changing the power up light level of a specific lamp,
			 * 					its address must be set in this variable [1, 255].
			 */
			void setPowerUpLightLevel(float value, uint8_t address=BROADCAST_ADDRESS);
			/**
			 * Sets the command label for the commands.
			 * @param label - string that will be added at the begining of the command
			 *                final_cmd = label + "command
			 *
			 */
			void setCmdLabel(std::string label);

		private:
			virtual int extractPacket(const uint8_t* buffer, size_t buffer_size) const;
			uint8_t checksum(uint8_t byte1, uint8_t byte2, uint8_t byte3);
			void readMsg();
			void generateCommand(uint8_t command, uint8_t value, uint8_t address, uint8_t *data);
			std::string cmd_label;
	};

} /* namespace ledlamp_bowtech */

#endif /* SRC_BOWTECHDRIVER_HPP_ */
