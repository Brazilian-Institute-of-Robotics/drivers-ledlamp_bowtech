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
		// TODO Auto-generated constructor stub
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
		std::cout << BOWTECH_MAX_PACKET_SIZE << std::endl;

		int packet_size = iodrivers_base::Driver::readPacket(reply, BOWTECH_MAX_PACKET_SIZE, 100);
		std::cout << "Packet_size" << packet_size << std::endl;
		std::cout << std::hex << reply << std::endl;


		char a = reply[68];
		uint8_t i = (uint8_t)a;
		int add = i*100;
		a = reply[69];
		i = (uint8_t)a;
		add += i*10;
		a = reply[70];
		i = (uint8_t)a;
		add += i*1;

		std::cout << "lamp_address " << add << std::endl;
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
	}

	int BowtechDriver::extractPacket(const uint8_t* buffer, size_t buffer_size) const
	{
		if (buffer[0] == 0x0d & buffer[1] == 0x0a)
			return 116;
		else
			return -buffer_size;
	}

	uint8_t BowtechDriver::checksum(uint8_t byte1, uint8_t byte2, uint8_t byte3)
	{
		return (byte1^byte2)^byte3;
	}

} /* namespace ledlamp_bowtech */
