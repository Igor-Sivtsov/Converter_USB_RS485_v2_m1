#include "main.h"
#include "protection.h"

void FlashReadoutProtection()
{
	  FLASH_OBProgramInitTypeDef FLASH_OBInitStruct;

	  HAL_FLASHEx_OBGetConfig(&FLASH_OBInitStruct);

	  if(FLASH_OBInitStruct.RDPLevel == OB_RDP_LEVEL_0)
	  {

	  	  FLASH_OBInitStruct.OptionType = OPTIONBYTE_RDP;
	  	  FLASH_OBInitStruct.RDPLevel = OB_RDP_LEVEL_1;

		  HAL_FLASH_Unlock();
		  HAL_FLASH_OB_Unlock();


		  HAL_FLASHEx_OBProgram(&FLASH_OBInitStruct);

		  HAL_FLASH_OB_Lock();
		  HAL_FLASH_Lock();

		  HAL_NVIC_SystemReset();
	  }
}
