#include <xbee.h>
#include <random>
std::array<int, 6> XBee::getCommand__Test(){
	std::array<int, 6> test_array;
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(500.0,100.0);
	for (size_t i=0; i<6; i++){
		test_array[i] = distribution(generator);
	}
	return test_array;
}
