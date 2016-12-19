/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "tsc.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "tsl_user.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
unsigned char BYPASS_DTO;

// For debug purpose with STMStudio
uint8_t DS[TSLPRM_TOTAL_TKEYS + TSLPRM_TOTAL_LNRTS]; // To store the States (one per object)
int16_t DD[TSLPRM_TOTAL_TKEYS + (TSLPRM_TOTAL_LNRTS * 3)]; // To store the Deltas (one per channel)
uint32_t TouchRefSum[13];
uint16_t TouchRef[13];
unsigned int  KeyRead;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void ProcessSensors(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define DETECT_TKEY(NB)   (MyTKeys[(NB)].p_Data->StateId == TSL_STATEID_DETECT)
#define TOUCH_TKEY(NB)   (MyTKeys[(NB)].p_Data->StateId == TSL_STATEID_TOUCH)
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TSC_Init();

  /* USER CODE BEGIN 2 */
  TSL_user_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    if( TSL_user_Action() == TSL_STATUS_OK ){
      ProcessSensors(); // Execute sensors related tasks
    }  
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
//==============================================================================
// TSL_routines
//==============================================================================
//==============================================================================

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/**
* @brief  Manage the activity on sensors when touched/released (example)
* @param  None
* @retval None
*/
void ProcessSensors(void)
{
  uint32_t idx;
  //uint32_t idxch;
  uint32_t idx_ds = 0;
  uint32_t idx_dd = 0;
  
#if TSLPRM_TOTAL_TKEYS > 0  
  // Read all TKeys
  for (idx = 0; idx < TSLPRM_TOTAL_TKEYS; idx++)
  {
    // STMStudio debug
    DS[idx_ds++] = MyTKeys[idx].p_Data->StateId;    
    DD[idx_dd++] = MyTKeys[idx].p_ChD->Delta;
    if (DETECT_TKEY(idx) || TOUCH_TKEY(idx))
      //    if (TEST_TKEY(idx))
    {
            KeyRead |= (1<<idx);
    }
    else
    {
      KeyRead &= ~(1<<idx);
          
      // tavares
      if(MyTKeys[idx].p_Data->StateId == TSL_STATEID_RELEASE)
      {
         if(MyTKeys[idx].p_ChD->Ref < (TouchRef[idx] - TSLPRM_TKEY_DETECT_IN_TH))
         {
            MyTKeys[idx].p_ChD->Ref = TouchRef[idx];
         }
      }
    }
  }
#endif
}

/**
* @brief  Executed when a sensor is in Error state
* @param  None
* @retval None
*/
void MyTKeys_ErrorStateProcess(void)
{
  // Add here your own processing when a sensor is in Error state
  TSL_tkey_SetStateOff();
}

/**
* @brief  Executed when a sensor is in Off state
* @param  None
* @retval None
*/
void MyTKeys_OffStateProcess(void)
{
  // Add here your own processing when a sensor is in Off state
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
