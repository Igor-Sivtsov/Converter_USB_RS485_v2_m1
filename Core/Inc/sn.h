#ifndef INC_SN_H_
#define INC_SN_H_

#include "main.h"
#include <stdbool.h>

bool check_magic_combination(uint8_t* buf);
bool save_new_serial_number(uint8_t* buf);
void delay(uint32_t delay);

#endif /* INC_SN_H_ */
