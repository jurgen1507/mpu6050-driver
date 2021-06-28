#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "hwlib.hpp"

#define MPUADDRESS 	0x68
#define POWERMNG	0x6B
#define WHOAMI		0x75
#define CONFIG		0x1A
#define GYRO_X_H	0x43
#define GYRO_X_L	0x44
#define GYRO_Y_H	0x45
#define GYRO_Y_L	0x46
#define GYRO_Z_H	0x47
#define GYRO_Z_L	0x48
#define ACC_X_H		0x3B
#define ACC_X_L		0x3C
#define ACC_Y_H		0x3D
#define ACC_Y_L		0x3E
#define ACC_Z_H		0x3F
#define ACC_Z_L		0x40
#define TEMP_H		0x41
#define TEMP_L		0x42


struct sensordata{
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;
};

class mpu6050{
private:
	hwlib::i2c_bus & bus;
	
public:
	mpu6050(hwlib::i2c_bus & bus);
	//start functie voor de mpu, zal true teruggeven als het gelukt is/false als het niet gelukt is
	bool start();
	
	//schrijf waarde naar mpu register
	void write(const uint_fast8_t value);
	
	//schrijf waarde naar specifiek register in de mpu chip
	void write_register(const uint_fast8_t r_address, const uint_fast8_t value);
	
	//lees 8 bits uit i2c bus
	uint8_t read8(uint8_t r_address);
	
	//lees 16 bits uit i2c bus
	int16_t read16(uint8_t r_address_high, uint8_t r_address_low);
	
	//lees gyroscoop en geef terug als sensordata
	sensordata read_gyro();
	
	//lees accelerometer en geef terug als sensordata
	sensordata read_acc(); 
	
	//lees temperatuur en geef terug als 16 bits integer
	int16_t read_temp();
};


#endif