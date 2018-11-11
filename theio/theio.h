#ifndef __THE_IO_H__
#define __THE_IO_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/uart.h"

typedef void(*ButtonEventCallback)();

class theIO : public Device {
	private:
		enum ButtonState {
		  BTN_WAIT_PRESSED,
		  BTN_WAIT_RELEASE
		};

		struct {
			uint8_t type;
			ButtonEventCallback fn;
			ButtonState state;
			int64_t pressed_time;
		} event[6];
		uint8_t eventLen = 0;

	public:
		// constructor
		theIO();
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
		void btn_set_callback(uint8_t, ButtonEventCallback);
};

#endif
