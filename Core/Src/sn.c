#include "sn.h"

#include <string.h>

const uint8_t magic_combination[MAGIC_COMBINATION_LEN] = { 0xdc, 0x0f, 0xb8, 0xe9, 0x83, 0x57, 0x90, 0x19,
                                                           0x5b, 0xf4, 0xa8, 0xe5, 0xe1, 0x22, 0xfe, 0x60,
                                                           0x8e, 0x54, 0x8f, 0x46, 0xf8, 0x84, 0x10, 0xcc,
                                                           0x67, 0x92, 0x92, 0x7b, 0xed, 0xbb, 0x6d, 0x55 };
static void light_indication();

bool check_magic_combination(uint8_t* buf)
{
  if(memcmp(magic_combination, buf, MAGIC_COMBINATION_LEN) == 0)
//    return true;
  {
    light_indication();
	return true;
  }

  return false;
}

static void light_indication()
{
  for(int i = 0; i < 3; i++)
  {
	LED_GPIO_Port->BSRR = LED_Pin << 16;
	HAL_Delay(250);
	LED_GPIO_Port->BSRR = LED_Pin;
  }
}
