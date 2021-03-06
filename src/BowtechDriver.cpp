/*
 * BowtechDriver.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: diego
 */

#include "BowtechDriver.hpp"

namespace ledlamp_bowtech {

	BowtechDriver::BowtechDriver() : iodrivers_base::Driver(BOWTECH_MAX_PACKET_SIZE)
	{
		cmd_label = "";
	}

	BowtechDriver::~BowtechDriver()
	{
	}


	void BowtechDriver::setAddress(uint8_t current_address, uint8_t new_address)
	{
		if (new_address == BROADCAST_ADDRESS)
			throw std::runtime_error("The address 82 is reserved for the broadcast");

		uint8_t* data = new uint8_t[BOWTECH_COMMAND_SIZE + cmd_label.size()];
		uint8_t command = 0x27;

		generateCommand(command, new_address, current_address, data);

		this->writePacket(data, BOWTECH_COMMAND_SIZE + cmd_label.size());

		delete[] data;
	}

	void BowtechDriver::getAddress(std::vector<int>* address_list)
	{
		uint8_t* data = new uint8_t[BOWTECH_COMMAND_SIZE + cmd_label.size()];

		/*command for inquiry the lamp address*/
		uint8_t command = 0x29;


		/*ask all address and store all allocated address
		 * in a vector*/
		for (int i=1; i < 255; ++i)
		{
			if (i != BROADCAST_ADDRESS)
			{
				generateCommand(command, 0xFF, i, data);
				iodrivers_base::Driver::writePacket(data, BOWTECH_COMMAND_SIZE + cmd_label.size());


				try
				{
				uint8_t* reply = new uint8_t[BOWTECH_MAX_PACKET_SIZE];
				iodrivers_base::Driver::readPacket(reply, BOWTECH_MAX_PACKET_SIZE, 200, 30);

				std::stringstream ss;
				ss.str("");
				ss << reply[67] << reply[68] << reply[69];

				int address;
				ss >> address;

				address_list->push_back(address);

				delete[] reply;
				reply = NULL;
				}
				catch (iodrivers_base::TimeoutError &e)
				{
				}


			}
		}

		delete[] data;
	}

	void BowtechDriver::setLightLevel(float value, uint8_t address)
	{
		//if is a valid value, calculates the percentual value for the light level.
		if (value < 0.0 || value > 1.0)
			throw std::runtime_error("The light level must be a value between [0.0, 1.0]");

		uint8_t light_value = 255 * value;
		uint8_t* data = new uint8_t[BOWTECH_COMMAND_SIZE + cmd_label.size()];
		uint8_t command = 0x28;

		generateCommand(command, light_value, address, data);

		this->writePacket(data, BOWTECH_COMMAND_SIZE + cmd_label.size());

		delete[] data;
	}

	void BowtechDriver::setPowerUpLightLevel(float value, uint8_t address)
	{
		//if is a valid value, calculates the percentual value for the light level.
		if (value < 0.0 || value > 1.0)
			throw std::runtime_error("The light level must be a value between [0.0, 1.0]");

		uint8_t light_value = 255 * value;
		uint8_t* data = new uint8_t[BOWTECH_COMMAND_SIZE + cmd_label.size()];
		uint8_t command = 0x2A;

		generateCommand(command, light_value, address, data);

		this->writePacket(data, BOWTECH_COMMAND_SIZE + cmd_label.size());

		delete[] data;
	}

	int BowtechDriver::extractPacket(const uint8_t* buffer, size_t buffer_size) const
	{
		// if buffer starts with 0x0d and the third value is 0x42, then is a
		// message containing the address (116bytes).
		// If the message doesn't starts with 0x0d, then it is a normal reply
		// 6bytes
		if (buffer[0] == 0x0d)
		{
			if (buffer_size <3)
				return 0;
			else if (buffer_size >= 3 & buffer[2] == 0x42)
				return ((buffer_size < 116) ?  0 : 116);
			else
				return -buffer_size;
		}
		else
			return ((buffer_size < BOWTECH_COMMAND_SIZE) ?  0 : BOWTECH_COMMAND_SIZE);
	}

	uint8_t BowtechDriver::checksum(uint8_t byte1, uint8_t byte2, uint8_t byte3)
	{
		return (byte1^byte2)^byte3;
	}

	void BowtechDriver::generateCommand(uint8_t command, uint8_t value, uint8_t address, uint8_t *data)
	{
		int lbl_size = cmd_label.size();

		if (lbl_size > 0)
		{
			for (int i=0; i < lbl_size; ++i)
			{
				data[i] = cmd_label.at(i);
			}
		}

		data[0+lbl_size] = (uint8_t)address;
		data[1+lbl_size] = command;
		data[2+lbl_size] = value;
		data[3+lbl_size] = checksum(address, command, value);
		data[4+lbl_size] = 0x0D;
		data[5+lbl_size] = 0x0A;
	}

	void BowtechDriver::setCmdLabel(std::string label)
	{
		cmd_label = label;
	}

} /* namespace ledlamp_bowtech */
