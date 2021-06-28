#include "hwlib.hpp"
#include <array>
#include "mpu6050-driver.hpp"

int main(int argc, char **argv){
	auto scl = hwlib::target::pin_oc( hwlib::target::pins::d21 );
	auto sda = hwlib::target::pin_oc( hwlib::target::pins::d20 );
	auto i2c = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

	mpu6050 mpu(i2c);

	if(mpu.start()){
		for(;;){
			sensordata gyro = mpu.read_gyro();
			sensordata acc = mpu.read_acc();
			
			hwlib::cout << 
			"Gyro_x:" << gyro.x << 
			"\tGyro_y:" << gyro.y << 
			"\tGyro_z:" << gyro.z <<
			"\tAcc_x:" << acc.x << 
			"\tAcc_y:" << acc.y << 
			"\tAcc_z:" << acc.z <<  "\n";
			
			hwlib::wait_ms(17);
		}
	}
}
