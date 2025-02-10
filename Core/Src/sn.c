#include "sn.h"
#include <string.h>

const uint32_t serial_number_addres         = 0x800fc00;
const size_t   serial_number_message_length = 45;
const size_t   magic_combination_length     = 32;

const uint8_t magic_combination[32] =  { 0xdc, 0x0f, 0xb8, 0xe9, 0x83, 0x57, 0x90, 0x19,
                                         0x5b, 0xf4, 0xa8, 0xe5, 0xe1, 0x22, 0xfe, 0x60,
                                         0x8e, 0x54, 0x8f, 0x46, 0xf8, 0x84, 0x10, 0xcc,
                                         0x67, 0x92, 0x92, 0x7b, 0xed, 0xbb, 0x6d, 0x55 };

const size_t  serial_number_length = 30;
uint8_t new_serial_number[30] = "FORWARD_DYN_00-000-000-00-000";

bool check_magic_combination(uint8_t* buf)
{
  if(memcmp(magic_combination, buf, magic_combination_length) == 0)
	return true;

  return false;
}

bool save_new_serial_number(uint8_t* buf)
{
  uint16_t world      = 0;
  uint32_t page_error = 0;
  uint32_t address    = serial_number_addres;

  new_serial_number[12] = buf[0];
  new_serial_number[13] = buf[1];

  new_serial_number[15] = buf[2];
  new_serial_number[16] = buf[3];
  new_serial_number[17] = buf[4];

  new_serial_number[19] = buf[5];
  new_serial_number[20] = buf[6];
  new_serial_number[21] = buf[7];

  new_serial_number[23] = buf[8];
  new_serial_number[24] = buf[9];

  new_serial_number[26] = buf[10];
  new_serial_number[27] = buf[11];
  new_serial_number[28] = buf[12];

  HAL_FLASH_Unlock();

  FLASH_EraseInitTypeDef EraseInitStruct;

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.PageAddress = address;
  EraseInitStruct.NbPages     = 1;

  if(HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK)
  {
	HAL_FLASH_Lock();
	return false;
  }

  for(int i = 0; i < serial_number_length / 2; i++)
  {
    world = new_serial_number[i * 2] | (uint16_t)(new_serial_number[i * 2 + 1] << 8);
    if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, world) != HAL_OK)
    {
      HAL_FLASH_Lock();
      return false;
    }
    address += 2;
  }

  HAL_FLASH_Lock();

  for(int i = 0; i < 3; i++)
  {
	LED_GPIO_Port->BSRR = LED_Pin << 16;
    delay(300000);

	LED_GPIO_Port->BSRR = LED_Pin;
	delay(300000);
  }

  return true;
}

void delay(uint32_t delay)
{
  for(uint32_t i = 0; i < delay; i++)
	  __NOP();
}


