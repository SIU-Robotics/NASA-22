#include <iostream>
#include <wiringPiI2C.h>
#define DEVICE_ID 0x08
int main (int argc, char **argv)
{
    // Setup I2C communication
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        std::cout << "Failed to init I2C communication.\n";
        return -1;
    }
    std::cout << "I2C communication successfully setup.\n";
    // Send data to arduino
    std::cout << "Command List:\n";
    std::cout << "Forward: f\n";
    std::cout << "Backward: b\n";
    std::cout << "Left: l\n";
    std::cout << "Right: r\n";
    std::cout << "Universal Stop: s\n";
    std::cout << "Timed Foward: F\n";
    std::cout << "Timed Backward: B\n";
    std::cout << "Timed Left: L\n";
    std::cout << "Timed Right: R\n";
    std::cout << "Auger Forward: p\n";
    std::cout << "Auger Backward: o\n";
    std::cout << "Auger Stop: S\n";
    std::cout << "Drill CC: c\n";
    std::cout << "Drill CCW: w\n";
    std::cout << "Drill Stop: D\n";
    std::cout << "Lin Act Up: u\n";
    std::cout << "Lin Act Down: d\n";
    std::cout << "Lin Act Stop: A\n";
    while(1)
    {
    	uint8_t data_to_send;
	std::cout << "Enter a command: ";
	std::cin >> data_to_send;
    	wiringPiI2CWrite(fd, data_to_send);
    	std::cout << "Sent data: " << (int)data_to_send << "\n";
    	// Read data from arduino
    	int received_data = wiringPiI2CRead(fd);
    	std::cout << "Data received: " << received_data << "\n";
    	if (received_data == data_to_send) {
        	std::cout << "Success!\n";
    	}
    }
    return 0;
}
