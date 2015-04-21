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

	}

	BowtechDriver::~BowtechDriver()
	{
		// TODO Auto-generated destructor stub
	}


	void BowtechDriver::setAddress(uint8_t current_address, uint8_t new_address)
	{
		if (new_address > 255 || new_address <=0 || current_address > 255 || current_address <=0)
			throw std::runtime_error("The address must be a value between 1 and 255  - [1,255]");

		uint8_t data[BOWTECH_COMMAND_SIZE];

		data[0] = current_address;
		data[1] = 0x27;
		data[2] = new_address;
		data[3] = checksum(data[0], data[1], data[2]);
		data[4] = 0x0D;
		data[5] = 0x0A;

		this->writePacket(data, BOWTECH_COMMAND_SIZE);
		readMsg();
	}

	void BowtechDriver::getAddress()
	{
		uint8_t data[6];

		data[0] = 0x52;
		data[1] = 0x29;
		data[2] = 0xFF;
		data[3] = checksum(data[0], data[1], data[2]);
		data[4] = 0x0D;
		data[5] = 0x0A;

		if (iodrivers_base::Driver::writePacket(data, BOWTECH_COMMAND_SIZE))
		{
		uint8_t* reply = new uint8_t[BOWTECH_MAX_PACKET_SIZE];

		iodrivers_base::Driver::readPacket(reply, BOWTECH_MAX_PACKET_SIZE, 200);

		std::stringstream ss;
		ss.str("");
		ss << reply[67];
		ss << reply[68];
		ss << reply[69];

		int address;
		ss >> address;

		std::cout << "lamp_address " << address << std::endl;

		delete[] reply;
		}

	}

	void BowtechDriver::setLightLevel(uint8_t value, int address)
	{
		//if is a valid value, calculates the percentual value for the light level.
		if (value > 100 || value <=0)
			throw std::runtime_error("The light level must be a value between 1 and 100 - [1,100]");
		else
			value = (255*value)/100;

		if (address < 0)
			address = 0x52;
		else if (address > 255 || address == 0)
			throw std::runtime_error("The address must be a value between 1 and 255  - [1,255]");

		uint8_t data[BOWTECH_COMMAND_SIZE];

		data[0] = (uint8_t)address;
		data[1] = 0x28;
		data[2] = value;
		data[3] = checksum(data[0], data[1], data[2]);
		data[4] = 0x0D;
		data[5] = 0x0A;

		this->writePacket(data, BOWTECH_COMMAND_SIZE);
		readMsg();

	}

	void BowtechDriver::setPowerUpLightLevel(uint8_t value, int address)
	{
		//if is a valid value, calculates the percentual value for the light level.
		if (value > 100 || value <=0)
			throw std::runtime_error("The power up light level must be a value between 1 and 100 - [1,100]");
		else
			value = (255*value)/100;

		if (address < 0)
			address = 0x52;
		else if (address > 255 || address == 0)
			throw std::runtime_error("The address must be a value between 1 and 255  - [1,255]");

		uint8_t data[BOWTECH_COMMAND_SIZE];

		data[0] = (uint8_t)address;
		data[1] = 0x2A;
		data[2] = value;
		data[3] = checksum(data[0], data[1], data[2]);
		data[4] = 0x0D;
		data[5] = 0x0A;

		this->writePacket(data, BOWTECH_COMMAND_SIZE);
		readMsg();
	}

	int BowtechDriver::extractPacket(const uint8_t* buffer, size_t buffer_size) const
	{
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

	void BowtechDriver::readMsg()
	{
		uint8_t* reply = new uint8_t[BOWTECH_MAX_PACKET_SIZE];
		int packet_size = iodrivers_base::Driver::readPacket(reply, BOWTECH_MAX_PACKET_SIZE,50);

		std::cout << "Ox";
		for (int i=0; i< packet_size; ++i)
		{
			std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)reply[i] << " ";
		}
		std::cout << std::endl;

		delete[] reply;
	}

} /* namespace ledlamp_bowtech */
