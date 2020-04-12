#ifndef __DHT12_CPP__
#define __DHT12_CPP__

#include "dht12.h"

DHT12::DHT12(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 100;
}

void DHT12::init(void) {
	// clear initialized flag
	initialized = false;
	
	// Reset speed of I2C
	/*i2c_config_t conf;

	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = CHAIN_SDA_GPIO;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_io_num = CHAIN_SCL_GPIO;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 100E3;

	i2c_param_config(I2C_NUM_1, &conf);*/
	
	// Set new timeout of i2c
	i2c_set_timeout(I2C_NUM_1, 40000);
	
	state = s_detect;
}

int DHT12::prop_count(void) {
	// not supported
	return 0;
}

bool DHT12::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool DHT12::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool DHT12::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool DHT12::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool DHT12::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

void DHT12::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// clear error flag
				error = false;
				// set initialized flag
				initialized = true;
			
				// Go to main state
				state = s_read;
			} else {
				state = s_error;
			}
			break;
		
		case s_read: {
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				tickcnt = get_tickcnt();
				
				uint8_t addr = 0x00;
				uint8_t buff[4];
				if (i2c->read(channel, address, &addr, 1, buff, 4) == ESP_OK) {
					temperature = (buff[2] + ((buff[3] & 0b01111111) / 10.0)) * ((buff[3] & 0b10000000) ? -1 : 1);
					humidity = buff[0] + (buff[1] / 10.0);
				} else {
					// ESP_LOGI("DHT12", "read error!");
					state = s_error;
				}
			}
			break;
		}
		
		case s_wait:
			if (error) {
				// wait polling_ms timeout
				if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
					state = s_detect;
				}
			}
			break;

		case s_error:
			temperature = 0.0;
			humidity = 0.0;
					
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

	}
}

// Method
double DHT12::readTemperature() {
	return temperature;
}

double DHT12::readHumidity() {
	return humidity;
}

#endif