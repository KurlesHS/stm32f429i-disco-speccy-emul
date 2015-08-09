/**
  ******************************************************************************
  * File Name          : stm32f4xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
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
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN 0 */
#include "stm32f4xx_hal_gpio.h"
/* USER CODE END 0 */

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);

  /* System interrupt init*/
/* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
  * @brief LTDC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
  GPIO_InitTypeDef GPIO_Init_Structure;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable the LTDC Clock */
  __HAL_RCC_LTDC_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /******************** LTDC Pins configuration *************************/
  /*
   +------------------------+-----------------------+----------------------------+
   +                       LCD pins assignment                                   +
   +------------------------+-----------------------+----------------------------+
   |  LCD_TFT R2 <-> PC.10  |  LCD_TFT G2 <-> PA.06 |  LCD_TFT B2 <-> PD.06      |
   |  LCD_TFT R3 <-> PB.00  |  LCD_TFT G3 <-> PG.10 |  LCD_TFT B3 <-> PG.11      |
   |  LCD_TFT R4 <-> PA.11  |  LCD_TFT G4 <-> PB.10 |  LCD_TFT B4 <-> PG.12      |
   |  LCD_TFT R5 <-> PA.12  |  LCD_TFT G5 <-> PB.11 |  LCD_TFT B5 <-> PA.03      |
   |  LCD_TFT R6 <-> PB.01  |  LCD_TFT G6 <-> PC.07 |  LCD_TFT B6 <-> PB.08      |
   |  LCD_TFT R7 <-> PG.06  |  LCD_TFT G7 <-> PD.03 |  LCD_TFT B7 <-> PB.09      |
   -------------------------------------------------------------------------------
            |  LCD_TFT HSYNC <-> PC.06  | LCDTFT VSYNC <->  PA.04 |
            |  LCD_TFT CLK   <-> PG.07  | LCD_TFT DE   <->  PF.10 |
             -----------------------------------------------------

  */

  /* LTDC pins configuraiton: PA3 -- 12 */
  GPIO_Init_Structure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 |
                                GPIO_PIN_11 | GPIO_PIN_12;
  GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull = GPIO_NOPULL;
  GPIO_Init_Structure.Speed = GPIO_SPEED_FAST;
  GPIO_Init_Structure.Alternate= GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOA, &GPIO_Init_Structure);

  /* LTDC pins configuraiton: PB8 -- 11 */
  GPIO_Init_Structure.Pin = GPIO_PIN_8 | \
                             GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
  HAL_GPIO_Init(GPIOB, &GPIO_Init_Structure);

  /* LTDC pins configuraiton: PC6 -- 10 */
  GPIO_Init_Structure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
  HAL_GPIO_Init(GPIOC, &GPIO_Init_Structure);

  /* LTDC pins configuraiton: PD3 -- 6 */
  GPIO_Init_Structure.Pin = GPIO_PIN_3 | GPIO_PIN_6;
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* LTDC pins configuraiton: PF10*/
  GPIO_Init_Structure.Pin = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);

  /* LTDC pins configuraiton: PG6 -- 7 */
  GPIO_Init_Structure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | \
                             GPIO_PIN_11;
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);

  /* LTDC pins configuraiton: PB1 -- 1 */
  GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  GPIO_Init_Structure.Alternate= GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_Init_Structure);

  /* LTDC pins configuraiton: PG10 -- 12 */
  GPIO_Init_Structure.Pin = GPIO_PIN_10 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);
}

/**
  * @brief LTDC MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc)
{

  /*##-1- Reset peripherals ##################################################*/
  /* Enable LTDC reset state */
  __HAL_RCC_LTDC_FORCE_RESET();

  /* Release LTDC from reset state */
  __HAL_RCC_LTDC_RELEASE_RESET();
}


static int FMC_Initialized = 0;

static void HAL_FMC_MspInit(void){
  /* USER CODE BEGIN FMC_MspInit 0 */

  /* USER CODE END FMC_MspInit 0 */
  GPIO_InitTypeDef GPIO_InitStruct;
  if (FMC_Initialized) {
    return;
  }
  FMC_Initialized = 1;
  /* Peripheral clock enable */
  __FMC_CLK_ENABLE();
  
  /** FMC GPIO Configuration  
  PF0   ------> FMC_A0
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PF5   ------> FMC_A5
  PC0   ------> FMC_SDNWE
  PF11   ------> FMC_SDNRAS
  PF12   ------> FMC_A6
  PF13   ------> FMC_A7
  PF14   ------> FMC_A8
  PF15   ------> FMC_A9
  PG0   ------> FMC_A10
  PG1   ------> FMC_A11
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10   ------> FMC_D7
  PE11   ------> FMC_D8
  PE12   ------> FMC_D9
  PE13   ------> FMC_D10
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10   ------> FMC_D15
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PG4   ------> FMC_BA0
  PG5   ------> FMC_BA1
  PG8   ------> FMC_SDCLK
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3
  PG15   ------> FMC_SDNCAS
  PB5   ------> FMC_SDCKE1
  PB6   ------> FMC_SDNE1
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_8|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN FMC_MspInit 1 */

  /* USER CODE END FMC_MspInit 1 */
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram){
  /* USER CODE BEGIN SDRAM_MspInit 0 */
    (void)hsdram;

  /* USER CODE END SDRAM_MspInit 0 */
  HAL_FMC_MspInit();
  /* USER CODE BEGIN SDRAM_MspInit 1 */

  /* USER CODE END SDRAM_MspInit 1 */
}

static int FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
  /* USER CODE BEGIN FMC_MspDeInit 0 */

  /* USER CODE END FMC_MspDeInit 0 */
  if (FMC_DeInitialized) {
    return;
  }
  FMC_DeInitialized = 1;
  /* Peripheral clock enable */
  __FMC_CLK_DISABLE();
  
  /** FMC GPIO Configuration  
  PF0   ------> FMC_A0
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PF5   ------> FMC_A5
  PC0   ------> FMC_SDNWE
  PF11   ------> FMC_SDNRAS
  PF12   ------> FMC_A6
  PF13   ------> FMC_A7
  PF14   ------> FMC_A8
  PF15   ------> FMC_A9
  PG0   ------> FMC_A10
  PG1   ------> FMC_A11
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10   ------> FMC_D7
  PE11   ------> FMC_D8
  PE12   ------> FMC_D9
  PE13   ------> FMC_D10
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10   ------> FMC_D15
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PG4   ------> FMC_BA0
  PG5   ------> FMC_BA1
  PG8   ------> FMC_SDCLK
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3
  PG15   ------> FMC_SDNCAS
  PB5   ------> FMC_SDCKE1
  PB6   ------> FMC_SDNE1
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  */
  HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0);

  HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_8|GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);

  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);

  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_6);

  /* USER CODE BEGIN FMC_MspDeInit 1 */

  /* USER CODE END FMC_MspDeInit 1 */
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram){
  /* USER CODE BEGIN SDRAM_MspDeInit 0 */
    (void)hsdram;
  /* USER CODE END SDRAM_MspDeInit 0 */
  HAL_FMC_MspDeInit();
  /* USER CODE BEGIN SDRAM_MspDeInit 1 */

  /* USER CODE END SDRAM_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
