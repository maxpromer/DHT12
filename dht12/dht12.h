#ifndef __DHT12_H__
#define __DHT12_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "kidbright32.h"

class DHT12 : public Device {
	private:		
		enum {
			s_detect,
			s_read,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;

		double temperature = 0.0, humidity = 0.0;


	public:
		// constructor
		DHT12(int bus_ch, int dev_addr) ;
		
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		double readTemperature() ;
		double readHumidity() ;
		
};

#endif