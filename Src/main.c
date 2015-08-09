/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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

/* USER CODE BEGIN Includes */

#include "ili9341.h"
#include <string.h>

#include "speccy_hardware.h"
#include "speccy_common.h"
#include "screen.h"
#include "debug_msg.h"


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
LTDC_HandleTypeDef hltdc;

SDRAM_HandleTypeDef hsdram1;

LTDC_HandleTypeDef LtdcHandle;


/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

extern void form_speccy_screen_asm();
extern uint32_t add_asm(uint16_t one, uint16_t two);


int main(void)
{
    //form_speccy_screen_asm();
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_FMC_Init();
    MX_LTDC_Init();
    //HAL_LTDC_SetWindowPosition(&LtdcHandle, 0, 0, 0);
    //HAL_LTDC_SetWindowPosition(&LtdcHandle, 0, 0, 1);

    /* USER CODE BEGIN 2 */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;

    memset((void*)SCREEN_BUFFER_ADDR, 0, 192 * 256 * 2);


    speccy_hadrware speccy;
    init_speccy_hardware(&speccy);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    print_num("core clock: ", SystemCoreClock);

    uint16_t *addr = 0;
    print_num("addr: ", (uintptr_t)addr++);
    print_num("addr: ", (uintptr_t)addr);

    int x = 50;
    uint16_t pattern = 0;

    DWT->CTRL |= 1;
    while (1)
    {

        /* USER CODE END WHILE */
        int tick = HAL_GetTick();
        uint32_t tt = SysTick->VAL;
        DWT->CYCCNT = 0;

        LtdcHandle.Init.Backcolor.Blue += 1;
        LtdcHandle.Init.Backcolor.Red += 1;
        LtdcHandle.Init.Backcolor.Green += 1;
        HAL_LTDC_Init(&LtdcHandle);

        // speccy_frame(&speccy);


        static int fake = 0;

        fake ^= 1;
        HAL_LTDC_SetAddress(&LtdcHandle, fake ? SCREEN_BUFFER_ADDR : SCREEN_BUFFER_ADDR + 192 * 2, 1);
        gen_speccy_screen(&speccy);
        pattern += 1000;
        uint32_t tt2 = SysTick->VAL;
        tick = HAL_GetTick() - tick;

        if (--x < 0){
            print_num("cycle count:", DWT->CYCCNT);
            print_num("start systick: ", tt);
            print_num("end systick: ", tt2);
            print_num("ms: ", tick);
            x = 50;
        }


        /* USER CODE BEGIN 3 */

    }
    /* USER CODE END 3 */

}



/**
* @brief  System Clock Configuration
*         The system Clock is configured as follow :
*            System Clock source            = PLL (HSE)
*            SYSCLK(Hz)                     = 180000000
*            HCLK(Hz)                       = 180000000
*            AHB Prescaler                  = 1
*            APB1 Prescaler                 = 4
*            APB2 Prescaler                 = 2
*            HSE Frequency(Hz)              = 8000000
*            PLL_M                          = 8
*            PLL_N                          = 360
*            PLL_P                          = 2
*            PLL_Q                          = 7
*            VDD(V)                         = 3.3
*            Main regulator output voltage  = Scale1 mode
*            Flash Latency(WS)              = 5
*         The LTDC Clock is configured as follow :
*            PLLSAIN                        = 192
*            PLLSAIR                        = 4
*            PLLSAIDivR                     = 8
* @param  None
* @retval None
*/
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is
   clocked below the maximum system frequency, to update the voltage scaling value
   regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /*##-1- System Clock Configuration #########################################*/
    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 360;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* Activate the Over-Drive mode */
    HAL_PWREx_EnableOverDrive();

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
   clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

    /*##-2- LTDC Clock Configuration ###########################################*/
    /* LCD clock configuration */
    /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 MHz */
    /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 MHz */
    /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/4 = 48 MHz */
    /* LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDIVR_8 = 48/8 = 6 MHz */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 4;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
}

/* LTDC init function */
void MX_LTDC_Init(void)
{
    LTDC_LayerCfgTypeDef pLayerCfg;
    LTDC_LayerCfgTypeDef pLayerCfg1;

    /* Initialization of ILI9341 component*/
    ili9341_Init();

    /* LTDC Initialization -------------------------------------------------------*/

    /* Polarity configuration */
    /* Initialize the horizontal synchronization polarity as active low */
    LtdcHandle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    /* Initialize the vertical synchronization polarity as active low */
    LtdcHandle.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    /* Initialize the data enable polarity as active low */
    LtdcHandle.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    /* Initialize the pixel clock polarity as input pixel clock */
    LtdcHandle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

    /* Timing configuration  (Typical configuration from ILI9341 datasheet)
        HSYNC=10 (9+1)
        HBP=20 (29-10+1)
        ActiveW=240 (269-20-10+1)
        HFP=10 (279-240-20-10+1)

        VSYNC=2 (1+1)
        VBP=2 (3-2+1)
        ActiveH=320 (323-2-2+1)
        VFP=4 (327-320-2-2+1)
    */

    /* Timing configuration */
    /* Horizontal synchronization width = Hsync - 1 */
    LtdcHandle.Init.HorizontalSync = 9;
    /* Vertical synchronization height = Vsync - 1 */
    LtdcHandle.Init.VerticalSync = 1;
    /* Accumulated horizontal back porch = Hsync + HBP - 1 */
    LtdcHandle.Init.AccumulatedHBP = 29;
    /* Accumulated vertical back porch = Vsync + VBP - 1 */
    LtdcHandle.Init.AccumulatedVBP = 3;
    /* Accumulated active width = Hsync + HBP + Active Width - 1 */
    LtdcHandle.Init.AccumulatedActiveH = 323;
    /* Accumulated active height = Vsync + VBP + Active Heigh - 1 */
    LtdcHandle.Init.AccumulatedActiveW = 269;
    /* Total height = Vsync + VBP + Active Heigh + VFP - 1 */
    LtdcHandle.Init.TotalHeigh = 327;
    /* Total width = Hsync + HBP + Active Width + HFP - 1 */
    LtdcHandle.Init.TotalWidth = 279;

    /* Configure R,G,B component values for LCD background color */
    LtdcHandle.Init.Backcolor.Blue = 0;
    LtdcHandle.Init.Backcolor.Green = 0;
    LtdcHandle.Init.Backcolor.Red = 0;

    LtdcHandle.Instance = LTDC;

    /* Layer1 Configuration ------------------------------------------------------*/

    /* Windowing configuration */
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 240;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 320;

    /* Pixel Format configuration*/
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;

    /* Start Address configuration : frame buffer is located at FLASH memory */
    pLayerCfg.FBStartAdress = (uint32_t)0;

    /* Alpha constant (255 totally opaque) */
    pLayerCfg.Alpha = 0;

    /* Default Color configuration (configure A,R,G,B component values) */
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.Backcolor.Blue = 255;
    pLayerCfg.Backcolor.Green = 255;
    pLayerCfg.Backcolor.Red = 255;

    /* Configure blending factors */
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;

    /* Configure the number of lines and number of pixels per line */
    pLayerCfg.ImageWidth = 0;
    pLayerCfg.ImageHeight = 0;

    /* Layer2 Configuration ------------------------------------------------------*/

    /* Windowing configuration */
    pLayerCfg1.WindowX0 = 24;
    pLayerCfg1.WindowX1 = 216;
    pLayerCfg1.WindowY0 = 32;
    pLayerCfg1.WindowY1 = 288;

    /* Pixel Format configuration*/
    pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;

    /* Start Address configuration : frame buffer is located at FLASH memory */
    pLayerCfg1.FBStartAdress = (uint32_t)SCREEN_BUFFER_ADDR;

    /* Alpha constant (255 totally opaque) */
    pLayerCfg1.Alpha = 200;

    /* Default Color configuration (configure A,R,G,B component values) */
    pLayerCfg1.Alpha0 = 0;
    pLayerCfg1.Backcolor.Blue = 0;
    pLayerCfg1.Backcolor.Green = 0;
    pLayerCfg1.Backcolor.Red = 0;

    /* Configure blending factors */
    pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;

    /* Configure the number of lines and number of pixels per line */
    pLayerCfg1.ImageWidth = 192;
    pLayerCfg1.ImageHeight = 256;

    /* Configure the LTDC */
    if(HAL_LTDC_Init(&LtdcHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }

    /* Configure the Background Layer*/
    if(HAL_LTDC_ConfigLayer(&LtdcHandle, &pLayerCfg, 0) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }

    /* Configure the Foreground Layer*/

    if(HAL_LTDC_ConfigLayer(&LtdcHandle, &pLayerCfg1, 1) != HAL_OK)
    {
      Error_Handler();
    }


}

FMC_SDRAM_CommandTypeDef command;

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define REFRESH_COUNT       ((uint32_t)0x0569)   /* SDRAM refresh counter (90MHz SD clock) */

static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
    __IO uint32_t tmpmrd =0;
    /* Step 3:  Configure a clock configuration enable command */
    Command->CommandMode 			 = FMC_SDRAM_CMD_CLK_ENABLE;
    Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
    Command->AutoRefreshNumber 	 = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Step 4: Insert 100 ms delay */
    HAL_Delay(100);

    /* Step 5: Configure a PALL (precharge all) command */
    Command->CommandMode 			 = FMC_SDRAM_CMD_PALL;
    Command->CommandTarget 	     = FMC_SDRAM_CMD_TARGET_BANK2;
    Command->AutoRefreshNumber 	 = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Step 6 : Configure a Auto-Refresh command */
    Command->CommandMode 			 = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
    Command->AutoRefreshNumber 	 = 4;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Step 7: Program the external memory mode register */
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
            SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
            SDRAM_MODEREG_CAS_LATENCY_3           |
            SDRAM_MODEREG_OPERATING_MODE_STANDARD |
            SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
    Command->AutoRefreshNumber 	 = 1;
    Command->ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Step 8: Set the refresh rate counter */
    /* (15.62 us x Freq) - 20 */
    /* Set the device refresh counter */
    HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);
}


/* FMC initialization function */
void MX_FMC_Init(void)
{
    FMC_SDRAM_TimingTypeDef SdramTiming;

    /** Perform the SDRAM1 memory initialization sequence
  */
    hsdram1.Instance = FMC_SDRAM_DEVICE;
    /* hsdram1.Init */
    hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
    hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
    hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_3;
    hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
    hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
    /* SdramTiming */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshDelay = 7;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 7;
    SdramTiming.WriteRecoveryTime = 2;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;

    HAL_SDRAM_Init(&hsdram1, &SdramTiming);

    SDRAM_Initialization_Sequence(&hsdram1, &command);
}

/** Configure pins as 
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
     PF7   ------> SPI5_SCK
     PF8   ------> SPI5_MISO
     PF9   ------> SPI5_MOSI
     PB12   ------> USB_OTG_HS_ID
     PB13   ------> USB_OTG_HS_VBUS
     PB14   ------> USB_OTG_HS_DM
     PB15   ------> USB_OTG_HS_DP
     PC9   ------> I2C3_SDA
     PA8   ------> I2C3_SCL
*/

void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __GPIOC_CLK_ENABLE();
    __GPIOF_CLK_ENABLE();
    __GPIOH_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();

    /*Configure GPIO pins : PF7 PF8 PF9 */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /*Configure GPIO pins : PC1 PC2 PC4 */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : PA0 PA1 PA2 PA15 */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PA7 */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PC5 */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin : PB2 */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : PB12 PB14 PB15 */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : PB13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : PD11 */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pins : PD12 PD13 */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pin : PC9 */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin : PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PG13 PG14 */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void Error_Handler() {
    while (1) {

    }
}

/* USER CODE END 4 */

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
