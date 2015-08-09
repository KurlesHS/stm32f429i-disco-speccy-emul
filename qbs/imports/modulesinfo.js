var modules = {
    "hal": {
        "includePaths": [],
        "defines": [],
        "files": [],
        "prefix": "../system/",
        "halModule": {
            "defines": [
                "HAL_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal.c",
                "include/stm32f4-hal/stm32f4xx_hal.h"
            ],
            "includePaths": []
        },
        "halAdcModule": {"defines": [
                "HAL_ADC_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_adc.c",
                "include/stm32f4-hal/stm32f4xx_hal_adc.h",
                "source/stm32f4-hal/stm32f4xx_hal_adc_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_adc_ex.h"
            ]},
        "halCanModule": {"defines": [
                "HAL_CAN_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_can.c",
                "include/stm32f4-hal/stm32f4xx_hal_can.h"
            ]},
        "halCrcModule": {
            "defines": [
                "HAL_CRC_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_crc.c",
                "include/stm32f4-hal/stm32f4xx_hal_crc.h"
            ]
        },"halCrypModule": {
            "defines": [
                "HAL_CRYP_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_cryp.c",
                "include/stm32f4-hal/stm32f4xx_hal_cryp.h",
                "source/stm32f4-hal/stm32f4xx_hal_cryp_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_cryp_ex.h"
            ],
            "includePaths": []
        },
        "halDacModule": {"defines": [
                "HAL_DAC_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_dac.c",
                "include/stm32f4-hal/stm32f4xx_hal_dac.h",
                "source/stm32f4-hal/stm32f4xx_hal_dac_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_dac_ex.h"
            ]},
        "halDcmiModule": {"defines": [
                "HAL_DCMI_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_dcmi.c",
                "include/stm32f4-hal/stm32f4xx_hal_dcmi.h"
            ]},
        "halDmaModule": {"defines": [
                "HAL_DMA_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_dma.c",
                "include/stm32f4-hal/stm32f4xx_hal_dma.h",
                "source/stm32f4-hal/stm32f4xx_hal_dma_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_dma_ex.h"
            ]},
        "halDma2DModule": {"defines": [
                "HAL_DMA2D_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_dma2d.c",
                "include/stm32f4-hal/stm32f4xx_hal_dma2d.h"
            ]},
        "halEthModule": {"defines": [
                "HAL_ETH_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_eth.c",
                "include/stm32f4-hal/stm32f4xx_hal_eth.h"
            ]},
        "halFlashModule": {"defines": [
                "HAL_FLASH_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_flash.c",
                "include/stm32f4-hal/stm32f4xx_hal_flash.h",
                "source/stm32f4-hal/stm32f4xx_hal_flash_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_flash_ex.h"
            ]},
        "halNandModule": {"defines": [
                "HAL_NAND_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_nand.c",
                "include/stm32f4-hal/stm32f4xx_hal_nand.h"
            ]},
        "halNorModule": {"defines": [
                "HAL_NOR_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_nor.c",
                "include/stm32f4-hal/stm32f4xx_hal_nor.h"
            ]},
        "halPcCartModule": {"defines": [
                "HAL_PCCARD_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_pccard.c",
                "include/stm32f4-hal/stm32f4xx_hal_pccard.h"
            ]},
        "halSRamModule": {"defines": [
                "HAL_SRAM_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_sram.c",
                "include/stm32f4-hal/stm32f4xx_hal_sram.h"
            ]},
        "halSDRamModule": {"defines": [
                "HAL_SDRAM_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_sdram.c",
                "include/stm32f4-hal/stm32f4xx_hal_sdram.h"
            ]},
        "halHashModule": {"defines": [
                "HAL_HASH_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_hash.c",
                "include/stm32f4-hal/stm32f4xx_hal_hash.h",
                "source/stm32f4-hal/stm32f4xx_hal_hash_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_hash_ex.h"
            ]},
        "halGpioModule": {"defines": [
                "HAL_GPIO_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_gpio.c",
                "include/stm32f4-hal/stm32f4xx_hal_gpio.h"
            ]},
        "halI2CModule": {"defines": [
                "HAL_I2C_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_i2c.c",
                "include/stm32f4-hal/stm32f4xx_hal_i2c.h",
                "source/stm32f4-hal/stm32f4xx_hal_i2c_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_i2c_ex.h"
            ]},
        "halI2SModule": {"defines": [
                "HAL_I2S_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_i2s.c",
                "include/stm32f4-hal/stm32f4xx_hal_i2s.h",
                "source/stm32f4-hal/stm32f4xx_hal_i2s_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_i2s_ex.h"
            ]},
        "halIwdgModule": {"defines": [
                "HAL_IWDG_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_iwdg.c",
                "include/stm32f4-hal/stm32f4xx_hal_iwdg.h"
            ]},
        "halLtdcModule": {"defines": [
                "HAL_LTDC_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_ltdc.c",
                "include/stm32f4-hal/stm32f4xx_hal_ltdc.h"
            ]},
        "halPwrModule": {"defines": [
                "HAL_PWR_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_pwr.c",
                "include/stm32f4-hal/stm32f4xx_hal_pwr.h",
                "source/stm32f4-hal/stm32f4xx_hal_pwr_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_pwr_ex.h"
            ]},
        "halRccModule": {"defines": [
                "HAL_RCC_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_rcc.c",
                "include/stm32f4-hal/stm32f4xx_hal_rcc.h",
                "source/stm32f4-hal/stm32f4xx_hal_rcc_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_rcc_ex.h"
            ]},
        "halRngModule": {"defines": [
                "HAL_RNG_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_rng.c",
                "include/stm32f4-hal/stm32f4xx_hal_rng.h"
            ]},
        "halRtcModule": {"defines": [
                "HAL_RTC_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_rtc.c",
                "include/stm32f4-hal/stm32f4xx_hal_rtc.h",
                "source/stm32f4-hal/stm32f4xx_hal_rtc_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_rtc_ex.h"
            ]},
        "halSaiModule": {"defines": [
                "HAL_SAI_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_sai.c",
                "include/stm32f4-hal/stm32f4xx_hal_sai.h"
            ]},
        "halSDModule": {"defines": [
                "HAL_SD_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_sd.c",
                "include/stm32f4-hal/stm32f4xx_hal_sd.h"
            ]},
        "halSpiModule": {"defines": [
                "HAL_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_spi.c",
                "include/stm32f4-hal/stm32f4xx_hal_spi.h"
            ]},
        "halTimModule": {"defines": [
                "HAL_TIM_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_tim.c",
                "include/stm32f4-hal/stm32f4xx_hal_tim.h",
                "source/stm32f4-hal/stm32f4xx_hal_tim_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_tim_ex.h"
            ]},
        "halUartModule": {"defines": [
                "HAL_UART_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_uart.c",
                "include/stm32f4-hal/stm32f4xx_hal_uart.h"
            ]},
        "halUsartModule": {"defines": [
                "HAL_USART_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_usart.c",
                "include/stm32f4-hal/stm32f4xx_hal_usart.h"
            ]},
        "halIrdaModule": {"defines": [
                "HAL_IRDA_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_irda.c",
                "include/stm32f4-hal/stm32f4xx_hal_irda.h"
            ]},
        "halSmartCardModule": {"defines": [
                "HAL_SMARTCARD_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_smartcard.c",
                "include/stm32f4-hal/stm32f4xx_hal_smartcard.h"
            ]},
        "halWwdgModule": {"defines": [
                "HAL_WWDG_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_wwdg.c",
                "include/stm32f4-hal/stm32f4xx_hal_wwdg.h"
            ]},
        "halCortexModule": {"defines": [
                "HAL_CORTEX_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_cortex.c",
                "include/stm32f4-hal/stm32f4xx_hal_cortex.h"
            ]},
        "halPcdModule": {"defines": [
                "HAL_PCD_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_pcd.c",
                "include/stm32f4-hal/stm32f4xx_hal_pcd.h",
                "source/stm32f4-hal/stm32f4xx_hal_pcd_ex.c",
                "include/stm32f4-hal/stm32f4xx_hal_pcd_ex.h"
            ]},
        "halHcdModule": {"defines": [
                "HAL_HCD_MODULE_ENABLED"
            ],
            "files": [
                "source/stm32f4-hal/stm32f4xx_hal_hcd.c",
                "include/stm32f4-hal/stm32f4xx_hal_hcd.h"
            ]}
    }
};
