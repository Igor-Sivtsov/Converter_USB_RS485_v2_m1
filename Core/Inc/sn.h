#ifndef INC_SN_H_
#define INC_SN_H_

#include "main.h"
#include <stdbool.h>

//#define SN_MESSAGE_LEN           45
#define SN_MESSAGE_LEN           32
#define MAGIC_COMBINATION_LEN    32


bool check_magic_combination(uint8_t* buf);

#endif /* INC_SN_H_ */
