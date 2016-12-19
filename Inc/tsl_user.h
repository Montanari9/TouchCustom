/**
  ******************************************************************************
  * @file    STM32F0518_Ex03_9T1L1R_SENSOR\inc\tsl_user.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    22-February-2013
  * @brief   Touch-Sensing user configuration and api file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TSL_USER_H
#define __TSL_USER_H

#include "tsl.h"


//=======================
// Channel IOs definition
//=======================

// TouchKeys

#define CHANNEL_0_IO_MSK    (TSL_GROUP1_IO1)
#define CHANNEL_0_GRP_MSK   (TSL_GROUP1)
#define CHANNEL_0_SRC       (0) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_0_DEST      (0) // Index in destination result array

#define CHANNEL_1_IO_MSK    (TSL_GROUP1_IO2)
#define CHANNEL_1_GRP_MSK   (TSL_GROUP1)
#define CHANNEL_1_SRC       (0) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_1_DEST      (1) // Index in destination result array

#define CHANNEL_2_IO_MSK    (TSL_GROUP1_IO3)
#define CHANNEL_2_GRP_MSK   (TSL_GROUP1)
#define CHANNEL_2_SRC       (0) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_2_DEST      (2) // Index in destination result array

#define CHANNEL_3_IO_MSK    (TSL_GROUP2_IO1)
#define CHANNEL_3_GRP_MSK   (TSL_GROUP2)
#define CHANNEL_3_SRC       (1) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_3_DEST      (3) // Index in destination result array

#define CHANNEL_4_IO_MSK    (TSL_GROUP2_IO2)
#define CHANNEL_4_GRP_MSK   (TSL_GROUP2)
#define CHANNEL_4_SRC       (1) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_4_DEST      (4) // Index in destination result array

#define CHANNEL_5_IO_MSK    (TSL_GROUP2_IO3)
#define CHANNEL_5_GRP_MSK   (TSL_GROUP2)
#define CHANNEL_5_SRC       (1) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_5_DEST      (5) // Index in destination result array

#define CHANNEL_6_IO_MSK    (TSL_GROUP3_IO2)
#define CHANNEL_6_GRP_MSK   (TSL_GROUP3)
#define CHANNEL_6_SRC       (2) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_6_DEST      (6) // Index in destination result array

#define CHANNEL_7_IO_MSK    (TSL_GROUP4_IO2)
#define CHANNEL_7_GRP_MSK   (TSL_GROUP4)
#define CHANNEL_7_SRC       (3) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_7_DEST      (7) // Index in destination result array

#define CHANNEL_8_IO_MSK    (TSL_GROUP4_IO3)
#define CHANNEL_8_GRP_MSK   (TSL_GROUP4)
#define CHANNEL_8_SRC       (3) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_8_DEST      (8) // Index in destination result array

#define CHANNEL_9_IO_MSK    (TSL_GROUP4_IO4)
#define CHANNEL_9_GRP_MSK   (TSL_GROUP4)
#define CHANNEL_9_SRC       (3) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_9_DEST      (9) // Index in destination result array

#define CHANNEL_10_IO_MSK    (TSL_GROUP6_IO2)
#define CHANNEL_10_GRP_MSK   (TSL_GROUP6)
#define CHANNEL_10_SRC       (5) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_10_DEST      (10) // Index in destination result array

#define CHANNEL_11_IO_MSK    (TSL_GROUP6_IO3)
#define CHANNEL_11_GRP_MSK   (TSL_GROUP6)
#define CHANNEL_11_SRC       (5) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_11_DEST      (11) // Index in destination result array

#define CHANNEL_12_IO_MSK    (TSL_GROUP6_IO4)
#define CHANNEL_12_GRP_MSK   (TSL_GROUP6)
#define CHANNEL_12_SRC       (5) // Index in source register (TSC->IOGXCR[])
#define CHANNEL_12_DEST      (12) // Index in destination result array
//======================
// Shield IOs definition
//======================

#define SHIELD_IO_MSK (0) // None

//=================
// Banks definition
//=================

#define BANK_0_NBCHANNELS    (4)
#define BANK_0_MSK_CHANNELS  (CHANNEL_0_IO_MSK | CHANNEL_4_IO_MSK | CHANNEL_8_IO_MSK | CHANNEL_12_IO_MSK )
#define BANK_0_MSK_GROUPS    (CHANNEL_0_GRP_MSK | CHANNEL_4_GRP_MSK | CHANNEL_8_GRP_MSK | CHANNEL_12_GRP_MSK )

#define BANK_1_NBCHANNELS    (3)
#define BANK_1_MSK_CHANNELS  (CHANNEL_1_IO_MSK | CHANNEL_5_IO_MSK | CHANNEL_9_IO_MSK )
#define BANK_1_MSK_GROUPS    (CHANNEL_1_GRP_MSK | CHANNEL_5_GRP_MSK | CHANNEL_9_GRP_MSK )

#define BANK_2_NBCHANNELS    (3)
#define BANK_2_MSK_CHANNELS  (CHANNEL_2_IO_MSK | CHANNEL_6_IO_MSK | CHANNEL_10_IO_MSK )
#define BANK_2_MSK_GROUPS    (CHANNEL_2_GRP_MSK | CHANNEL_6_GRP_MSK | CHANNEL_10_GRP_MSK )

#define BANK_3_NBCHANNELS    (3)
#define BANK_3_MSK_CHANNELS  (CHANNEL_3_IO_MSK | CHANNEL_7_IO_MSK | CHANNEL_11_IO_MSK )
#define BANK_3_MSK_GROUPS    (CHANNEL_3_GRP_MSK | CHANNEL_7_GRP_MSK | CHANNEL_11_GRP_MSK )

// User Parameters
extern CONST TSL_Bank_T MyBanks[];
extern TSL_Zone_T MyZone;
extern CONST TSL_TouchKey_T MyTKeys[];
extern CONST TSL_LinRot_T MyLinRots[];
extern CONST TSL_Object_T MyObjects[];
extern TSL_ObjectGroup_T MyObjGroup;
extern uint32_t TouchRefSum[13];
extern uint16_t TouchRef[13];

void TSL_user_Init(void);
TSL_Status_enum_T TSL_user_Action(void);
void TSL_user_SetThresholds(void);

#endif /* __TSL_USER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
