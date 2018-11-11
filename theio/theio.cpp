#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "theIO.h"

theIO::theIO() {
	
}

void theIO::init(void) {
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int theIO::prop_count(void) {
	return 0;
}

bool theIO::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool theIO::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool theIO::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool theIO::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool theIO::prop_write(int index, char *value) {
	// not supported
	return false;
}


void theIO::process(Driver *drv) {
	for (int eIndex=0;eIndex<eventLen;eIndex++) {
		// char test_str[255];

		uint8_t &_btn_type = event[eIndex].type;
		ButtonEventCallback &_btn_callback = event[eIndex].fn;
		ButtonState &_btn_state = event[eIndex].state;
		int64_t &_pressed_time = event[eIndex].pressed_time;
		
		uint8_t pin = 0;
		
		if (_btn_type < 3) { // SW1 & SW2
			pin = (_btn_type == 1) ? 16 : 14;
		}
		
		if (_btn_state == BTN_WAIT_PRESSED) {
			if (_btn_type < 3) {
				if (gpio_get_level((gpio_num_t)pin) == 0) {
					_pressed_time = esp_timer_get_time();
					_btn_state = BTN_WAIT_RELEASE;
				}
			}
		} else if (_btn_state == BTN_WAIT_RELEASE) {
			if (_btn_type < 3) { // SW1 & SW2
				if (gpio_get_level((gpio_num_t)pin) == 1) {
					int64_t now_time = esp_timer_get_time();
					int64_t tMS = (now_time - _pressed_time) / 1000;
					if (tMS > 50) { // Debounce
						if (_btn_callback) {
							_btn_callback();
						}
					}
					_btn_state = BTN_WAIT_PRESSED;
				}
			}
		}
		
		/*
		sprintf(test_str, "Pin: %d, State: %d, Type: %d\n", pin, _btn_state, _btn_type);
		
		uart_write_bytes(UART_NUM_0, (const char*)test_str, strlen(test_str));
		*/
	}
}

void theIO::btn_set_callback(uint8_t type, ButtonEventCallback fn) {
	event[eventLen].type = type;
	event[eventLen].fn = fn;
	event[eventLen].state = BTN_WAIT_PRESSED;
	eventLen++;
	/*
	_btn_type = type;
	_btn_callback = fn;
	
	const char* test_str = "Config\n";
	uart_write_bytes(UART_NUM_0, (const char*)test_str, strlen(test_str));
	*/
}
