#include "mpu6050-driver.hpp"
#include "hwlib.hpp"
#include <cmath>

mpu6050::mpu6050(hwlib::i2c_bus & bus):
	bus(bus)	
{}
bool mpu6050::start(){
	 
	hwlib::wait_ms(2000);
	//Check of het WHOAMI adres het adres van de mpu teruggeeft om te controleren of het verbonden is.
	if (read8(WHOAMI) == MPUADDRESS){
		//reset mpu6050 en wacht tot het weer aan staat
		write_register(POWERMNG, 0x40);
		while (read8(POWERMNG) == 1){
			hwlib::wait_ms(1);
		}
		hwlib::wait_ms(100);
		//reset gyroscoop, accelerometer en temperatuursensor
		write_register(MPUADDRESS, 0x07);
		hwlib::wait_ms(100);
		//start de clock
		write_register(POWERMNG, 0x01);
		hwlib::wait_ms(100);
		//zet de lowpass filter aan op de accelerometer x en y (alleen relevant voor mijn project)
		write_register(CONFIG, 0x2E);
		hwlib::wait_ms(100);
		write_register(CONFIG, 0x36);
		return true;
	}else{
		return false;
	}

}
void mpu6050::write_register(const uint_fast8_t r_address, const uint_fast8_t value){
	//start write transactie met schrijven naar mpu adres
	hwlib::i2c_write_transaction writing = bus.write(MPUADDRESS);
	//schrijf het adres en de meegegeven waarde
	writing.write(r_address);
	writing.write(value);
	//stop de transactie
	writing.~i2c_write_transaction();
}

void mpu6050::write(const uint_fast8_t value){
	//start write transactie met schrijven naar mpu adres
	hwlib::i2c_write_transaction writing = bus.write(MPUADDRESS);
	//schrijf de meegegeven waarde
	writing.write(value);
	//stop de transactie
	writing.~i2c_write_transaction();
}

uint8_t mpu6050::read8(uint8_t r_address){
	//schrijf welk register er gelezen moet worden
	write(r_address);
	//geef de byte waarde die wordt gelezen terug
	return bus.read(MPUADDRESS).read_byte();
	
}

int16_t mpu6050::read16(uint8_t r_address_high, uint8_t r_address_low){
	//geef de eerste en laatse 8 bits door ze per stuk te lezen
	uint16_t data = read8(r_address_high) << 8 | read8(r_address_low);
	//geef die waarde terug
	return data;
}

sensordata mpu6050::read_gyro(){
	//lees de x, y en z waarde van de gyroscoop en geef deze terug als sensordata waarde
	sensordata sensor;
	sensor.x = read16(GYRO_X_H, GYRO_X_L);
	sensor.y = read16(GYRO_Y_H, GYRO_Y_L);
	sensor.z = read16(GYRO_Z_H, GYRO_Z_L);
	return sensor;
}

sensordata mpu6050::read_acc(){
	//lees de x, y en z waarde van de accelerometer en geef deze terug als sensordata waarde
	sensordata sensor;
	sensor.x = read16(ACC_X_H, ACC_X_L);
	sensor.y = read16(ACC_Y_H, ACC_Y_L);
	sensor.z = read16(ACC_Z_H, ACC_Z_L);
	return sensor;
}

int16_t read_temp(){
	//lees de temperatuur en geef dit terug
	return read16(TEMP_H, TEMP_L);
}