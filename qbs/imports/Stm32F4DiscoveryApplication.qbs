import qbs
import qbs.FileInfo
import qbs.File
import qbs.ModUtils
import qbs.Process
import qbs.TextFile

import "helpers.js" as Helpers
import "modulesinfo.js" as ModulesInfo


Product {
    type: ["application"] // To suppress bundle generation on Mac

    Depends { name: "cpp" }

    property bool createAsmDump: false

    property bool halModule: true
    property bool halAdcModule:false
    property bool halCanModule: false
    property bool halCrcModule: false
    property bool halCrypModule: false
    property bool halDacModule: false
    property bool halDcmiModule: false
    property bool halDmaModule: false
    property bool halDma2DModule: false
    property bool halEthModule: false
    property bool halFlashModule: false
    property bool halNandModule: false
    property bool halNorModule: false
    property bool halPcCartModule: false
    property bool halSRamModule: false
    property bool halSDRamModule: false
    property bool halHashModule: false
    property bool halGpioModule: false
    property bool halI2CModule: false
    property bool halI2SModule: false
    property bool halIwdgModule: false
    property bool halLtdcModule: false
    property bool halPwrModule: false
    property bool halRccModule: false
    property bool halRngModule: false
    property bool halRtcModule: false
    property bool halSaiModule: false
    property bool halSDModule: false
    property bool halSpiModule: false
    property bool halTimModule: false
    property bool halUartModule: false
    property bool halUsartModule: false
    property bool halIrdaModule: false
    property bool halSmartCardModule: false
    property bool halWwdgModule: false
    property bool halCortexModule: false
    property bool halPcdModule: false
    property bool halHcdModule: false


    property stringList baseDefines: {
        var defines =
                [
                    "STM32F429xx",
                    "USE_HAL_DRIVER",
                    "HSE_VALUE=8000000"
                ];
        if (halModule) {
            defines = defines.concat(["HAL_MODULE_ENABLED"]);
        }
        if (halAdcModule) {
            defines = defines.concat(["HAL_ADC_MODULE_ENABLED"]);
        }
        if (halCanModule) {
            defines = defines.concat(["HAL_CAN_MODULE_ENABLED"]);
        }
        if (halCrcModule) {
            defines = defines.concat(["HAL_CRC_MODULE_ENABLED"]);
        }
        if (halCrypModule) {
            defines = defines.concat(["HAL_CRYP_MODULE_ENABLED"]);
        }
        if (halDacModule) {
            defines = defines.concat(["HAL_DAC_MODULE_ENABLED"]);
        }
        if (halDcmiModule) {
            defines = defines.concat(["HAL_DCMI_MODULE_ENABLED"]);
        }
        if (halDmaModule) {
            defines = defines.concat(["HAL_DMA_MODULE_ENABLED"]);
        }
        if (halDma2DModule) {
            defines = defines.concat(["HAL_DMA2D_MODULE_ENABLED"]);
        }
        if (halEthModule) {
            defines = defines.concat(["HAL_ETH_MODULE_ENABLED"]);
        }
        if (halFlashModule) {
            defines = defines.concat(["HAL_FLASH_MODULE_ENABLED"]);
        }
        if (halNandModule) {
            defines = defines.concat(["HAL_NAND_MODULE_ENABLED"]);
        }
        if (halNorModule) {
            defines = defines.concat(["HAL_NOR_MODULE_ENABLED"]);
        }
        if (halPcCartModule) {
            defines = defines.concat(["HAL_PCCARD_MODULE_ENABLED"]);
        }
        if (halSRamModule) {
            defines = defines.concat(["HAL_SRAM_MODULE_ENABLED"]);
        }
        if (halSDRamModule) {
            defines = defines.concat(["HAL_SDRAM_MODULE_ENABLED"]);
        }
        if (halHashModule) {
            defines = defines.concat(["HAL_HASH_MODULE_ENABLED"]);
        }
        if (halGpioModule) {
            defines = defines.concat(["HAL_GPIO_MODULE_ENABLED"]);
        }
        if (halI2CModule) {
            defines = defines.concat(["HAL_I2C_MODULE_ENABLED"]);
        }
        if (halI2SModule) {
            defines = defines.concat(["HAL_I2S_MODULE_ENABLED"]);
        }
        if (halIwdgModule) {
            defines = defines.concat(["HAL_IWDG_MODULE_ENABLED"]);
        }
        if (halLtdcModule) {
            defines = defines.concat(["HAL_LTDC_MODULE_ENABLED"]);
        }
        if (halPwrModule) {
            defines = defines.concat(["HAL_PWR_MODULE_ENABLED"]);
        }
        if (halRccModule) {
            defines = defines.concat(["HAL_RCC_MODULE_ENABLED"]);
        }
        if (halRngModule) {
            defines = defines.concat(["HAL_RNG_MODULE_ENABLED"]);
        }
        if (halRtcModule) {
            defines = defines.concat(["HAL_RTC_MODULE_ENABLED"]);
        }
        if (halSaiModule) {
            defines = defines.concat(["HAL_SAI_MODULE_ENABLED"]);
        }
        if (halSDModule) {
            defines = defines.concat(["HAL_SD_MODULE_ENABLED"]);
        }
        if (halSpiModule) {
            defines = defines.concat(["HAL_SPI_MODULE_ENABLED"]);
        }
        if (halTimModule) {
            defines = defines.concat(["HAL_TIM_MODULE_ENABLED"]);
        }
        if (halUartModule) {
            defines = defines.concat(["HAL_UART_MODULE_ENABLED"]);
        }
        if (halUsartModule) {
            defines = defines.concat(["HAL_USART_MODULE_ENABLED"]);
        }
        if (halIrdaModule) {
            defines = defines.concat(["HAL_IRDA_MODULE_ENABLED"]);
        }
        if (halSmartCardModule) {
            defines = defines.concat(["HAL_SMARTCARD_MODULE_ENABLED"]);
        }
        if (halWwdgModule) {
            defines = defines.concat(["HAL_WWDG_MODULE_ENABLED"]);
        }
        if (halCortexModule) {
            defines = defines.concat(["HAL_CORTEX_MODULE_ENABLED"]);
        }
        if (halPcdModule) {
            defines = defines.concat(["HAL_PCD_MODULE_ENABLED"]);
        }
        if (halHcdModule) {
            defines = defines.concat(["HAL_HCD_MODULE_ENABLED"]);
        }
        return defines;
    }
/*
     -mcpu=cortex-m4
 -mthumb
 -mfloat-abi=soft
  -fmessage-length=0
-fsigned-char
 -ffunction-sections
-fdata-sections
 -ffreestanding
 -fno-move-loop-invariants
-Wunused
-Wuninitialized
-Wall
-Wextra
-Wmissing-declarations
 -Wconversion
-Wpointer-arith
 -Wpadded
 -Wshadow
-Wlogical-op
-Waggregate-return
-Wfloat-equal
-g3
-std=gnu11
-Wmissing-prototypes
-Wstrict-prototypes
 -Wbad-function-cast
-MMD
-MP
 -MF"src/main.d" -MT"src/main.o" -c -o "src/main.o" "../src/main.c"
     */

    property stringList  baseCommonCompilerFlags: [
        "-mcpu=cortex-m4",
        "-mthumb",
        "-mfpu=fpv4-sp-d16",
        "-mfloat-abi=softfp",
        "-fno-exceptions",
        "-fno-unwind-tables",
        "-fno-asynchronous-unwind-tables",
        "-ffunction-sections",
        "-fdata-sections",
        "-fsigned-char",
        "-ffreestanding",
        "-fno-move-loop-invariants",
        "-Wuninitialized",
        "-fmessage-length=0",
        "-fsigned-char",
        /* "-Wconversion", */
        "-Wpointer-arith",
        "-Wpadded",
        "-Wshadow",
        "-Wlogical-op",
        "-Waggregate-return",
        "-Wfloat-equal",
        "-MMD",
        "-MP"
    ]

    cpp.includePaths: [
        "../system/source/newlib",
        "../system/include/cmsis",
        "../system/include/cortexm",
        "../system/include/stm32f4-hal",
        "../src"
    ]

    cpp.linkerFlags: [
       "-mcpu=cortex-m4",
       "-mthumb",
       "-mfpu=fpv4-sp-d16",
       "-mfloat-abi=softfp",
       "-Xlinker",
       "--gc-sections",
       "-Xlinker",
       "-Map=" + destinationDirectory + "/" + name + ".map",
       "-fno-exceptions",
       "-fno-unwind-tables",
       "-fno-asynchronous-unwind-tables",
        "--specs=nano.specs"
   ]

   cpp.positionIndependentCode: false
   cpp.executableSuffix: ".elf"

    Properties  {
        name: "debug build"
        condition: qbs.buildVariant == "debug"
        cpp.defines: baseDefines.concat([
                     "DEBUG=1"
                     ])
        cpp.commonCompilerFlags: baseCommonCompilerFlags
    }

    Properties  {
        name: "release build"
        condition: qbs.buildVariant == "release"
        cpp.defines: baseDefines
        cpp.commonCompilerFlags: baseCommonCompilerFlags
    }

    Group {
        name: "cmsis"
        prefix: "../system/"
        files: [
            "source/cmsis/system_stm32f4xx.c",
            "source/cmsis/vectors_stm32f4xx.c"
        ]
    }

    Group {
        name: "hal"
        prefix: "../system/"
        files: {
            var f = ["include/stm32f4-hal/stm32f4xx_hal_conf.h"];
            if (halModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal.c",
                               "include/stm32f4-hal/stm32f4xx_hal.h"]);
            }
            if (halAdcModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_adc.c",
                               "include/stm32f4-hal/stm32f4xx_hal_adc.h",
                               "source/stm32f4-hal/stm32f4xx_hal_adc_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_adc_ex.h"]);
            }
            if (halCanModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_can.c",
                               "include/stm32f4-hal/stm32f4xx_hal_can.h"] )
            }
            if (halCrcModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_crc.c",
                               "include/stm32f4-hal/stm32f4xx_hal_crc.h"]);
            }
            if (halCrypModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_cryp.c",
                               "include/stm32f4-hal/stm32f4xx_hal_cryp.h",
                               "source/stm32f4-hal/stm32f4xx_hal_cryp_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_cryp_ex.h"]);
            }
            if (halDacModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_dac.c",
                               "include/stm32f4-hal/stm32f4xx_hal_dac.h",
                               "source/stm32f4-hal/stm32f4xx_hal_dac_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_dac_ex.h"]);
            }
            if (halDcmiModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_dcmi.c",
                               "include/stm32f4-hal/stm32f4xx_hal_dcmi.h"]);
            }
            if (halDmaModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_dma.c",
                               "include/stm32f4-hal/stm32f4xx_hal_dma.h",
                               "source/stm32f4-hal/stm32f4xx_hal_dma_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_dma_ex.h"]);
            }
            if (halDma2DModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_dma2d.c",
                               "include/stm32f4-hal/stm32f4xx_hal_dma2d.h"]);
            }
            if (halEthModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_eth.c",
                               "include/stm32f4-hal/stm32f4xx_hal_eth.h"]);
            }
            if (halFlashModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_flash.c",
                               "include/stm32f4-hal/stm32f4xx_hal_flash.h",
                               "source/stm32f4-hal/stm32f4xx_hal_flash_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_flash_ex.h"]);
            }
            if (halNandModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_nand.c",
                               "include/stm32f4-hal/stm32f4xx_hal_nand.h"]);
            }
            if (halNorModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_nor.c",
                               "include/stm32f4-hal/stm32f4xx_hal_nor.h"]);
            }
            if (halPcCartModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_pccard.c",
                               "include/stm32f4-hal/stm32f4xx_hal_pccard.h"]);
            }
            if (halSRamModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_sram.c",
                               "include/stm32f4-hal/stm32f4xx_hal_sram.h"
                             ]);
            }
            if (halSDRamModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_sdram.c",
                               "include/stm32f4-hal/stm32f4xx_hal_sdram.h",
                               "source/stm32f4-hal/stm32f4xx_ll_fmc.c",
                               "include/stm32f4-hal/stm32f4xx_ll_fmc.h"]);
            }
            if (halHashModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_hash.c",
                               "include/stm32f4-hal/stm32f4xx_hal_hash.h",
                               "source/stm32f4-hal/stm32f4xx_hal_hash_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_hash_ex.h"]);
            }
            if (halGpioModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_gpio.c",
                               "include/stm32f4-hal/stm32f4xx_hal_gpio.h"]);
            }
            if (halI2CModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_i2c.c",
                               "include/stm32f4-hal/stm32f4xx_hal_i2c.h",
                               "source/stm32f4-hal/stm32f4xx_hal_i2c_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_i2c_ex.h"]);
            }
            if (halI2SModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_i2s.c",
                               "include/stm32f4-hal/stm32f4xx_hal_i2s.h",
                               "source/stm32f4-hal/stm32f4xx_hal_i2s_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_i2s_ex.h"]);
            }
            if (halIwdgModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_iwdg.c",
                               "include/stm32f4-hal/stm32f4xx_hal_iwdg.h"]);
            }
            if (halLtdcModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_ltdc.c",
                               "include/stm32f4-hal/stm32f4xx_hal_ltdc.h"]);
            }
            if (halPwrModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_pwr.c",
                               "include/stm32f4-hal/stm32f4xx_hal_pwr.h",
                               "source/stm32f4-hal/stm32f4xx_hal_pwr_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_pwr_ex.h"]);
            }
            if (halRccModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_rcc.c",
                               "include/stm32f4-hal/stm32f4xx_hal_rcc.h",
                               "source/stm32f4-hal/stm32f4xx_hal_rcc_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_rcc_ex.h"]);
            }
            if (halRngModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_rng.c",
                               "include/stm32f4-hal/stm32f4xx_hal_rng.h"]);
            }
            if (halRtcModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_rtc.c",
                               "include/stm32f4-hal/stm32f4xx_hal_rtc.h",
                               "source/stm32f4-hal/stm32f4xx_hal_rtc_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_rtc_ex.h"]);
            }
            if (halSaiModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_sai.c",
                               "include/stm32f4-hal/stm32f4xx_hal_sai.h"]);
            }
            if (halSDModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_sd.c",
                               "include/stm32f4-hal/stm32f4xx_hal_sd.h"]);
            }
            if (halSpiModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_spi.c",
                               "include/stm32f4-hal/stm32f4xx_hal_spi.h"]);
            }
            if (halTimModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_tim.c",
                               "include/stm32f4-hal/stm32f4xx_hal_tim.h",
                               "source/stm32f4-hal/stm32f4xx_hal_tim_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_tim_ex.h"]);
            }
            if (halUartModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_uart.c",
                               "include/stm32f4-hal/stm32f4xx_hal_uart.h"]);
            }if (halUsartModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_usart.c",
                               "include/stm32f4-hal/stm32f4xx_hal_usart.h"]);
            }
            if (halIrdaModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_irda.c",
                               "include/stm32f4-hal/stm32f4xx_hal_irda.h"]);
            }
            if (halSmartCardModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_smartcard.c",
                               "include/stm32f4-hal/stm32f4xx_hal_smartcard.h"]);
            }
            if (halWwdgModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_wwdg.c",
                               "include/stm32f4-hal/stm32f4xx_hal_wwdg.h"]);
            }
            if (halCortexModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_cortex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_cortex.h"]);
            }
            if (halPcdModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_pcd.c",
                               "include/stm32f4-hal/stm32f4xx_hal_pcd.h",
                               "source/stm32f4-hal/stm32f4xx_hal_pcd_ex.c",
                               "include/stm32f4-hal/stm32f4xx_hal_pcd_ex.h"]);
            }
            if (halHcdModule) {
                f = f.concat( ["source/stm32f4-hal/stm32f4xx_hal_hcd.c",
                               "include/stm32f4-hal/stm32f4xx_hal_hcd.h"]);
            }
            return f;
        }
    }

    Group {
        name: "newlib"
        prefix: "../system/"
        files: [
            "source/newlib/_sbrk.c",
            "source/newlib/_syscalls.c",
            "source/newlib/_exit.c",
            "source/newlib/_startup.c",
            "source/newlib/_cxx.cpp",
        ]
    }

    Group {
        name: "cortexm"
        prefix: "../system/"
        files: [
            "source/cortexm/_initialize_hardware.c",
            "source/cortexm/_reset_hardware.c",
        ]
    }

    Group {
        name: "ldscripts"
        prefix: "../ldscripts/"
        files: [ "*.ld" ]
    }

    cpp.linkerScripts: [
        "../ldscripts/libs.ld",
        "../ldscripts/mem.ld",
        "../ldscripts/sections.ld"
    ]

    cpp.cxxFlags: [
        "-std=c++11",
        "-fno-rtti"
    ]
    cpp.cFlags: [ "-std=gnu99" ]
    cpp.warningLevel: 'all'

    Rule {
        inputs: ["application"]
        Artifact {
            fileTags: ['postbuild']
            filePath: FileInfo.completeBaseName(input.fileName) + '.hex'
        }

        prepare: {
            var retVal = [];

            var arg = ['-O', 'ihex', input.filePath, output.filePath]
            var cmd = new Command(Helpers.toolPath(product, 'objcopy'), arg);
            cmd.description = "create hex file "+ output.fileName;
            cmd.silent = false;
            cmd.highlight = "linker";
            retVal.push(cmd);

            var binFileName = output.fileName.substring(0, output.fileName.length - 3) + 'bin';
            var binFilePath = output.filePath.substring(0, output.filePath.length - 3) + 'bin';

            arg = ['-O', 'binary', input.filePath, binFilePath]
            cmd = new Command(Helpers.toolPath(product, 'objcopy'), arg);
            cmd.description = "create bin file "+ binFileName;
            cmd.silent = false;
            cmd.highlight = "linker";
            retVal.push(cmd);

            if (product.createAsmDump) {
                var asmFileName = output.fileName.substring(0, output.fileName.length - 3) + 'asm';
                cmd = new JavaScriptCommand();
                cmd.description = "create asm dump file "+ asmFileName;
                cmd.silent = false
                cmd.highlight = "create";
                cmd.sourceCode = function() {
                    var asmFilePath = output.filePath.substring(0, output.filePath.length - 3) + 'asm';
                    var f = TextFile(asmFilePath, TextFile.WriteOnly);
                    var proc = Process();
                    proc.start(Helpers.toolPath(product, 'objdump'), ['-S', '--disassemble', input.filePath]);
                    proc.waitForFinished();
                    f.write(proc.readStdOut());
                    f.close();
                }
                retVal.push(cmd);
            }

            var proc = Process();
            proc.setWorkingDirectory(FileInfo.path(input.filePath));
            proc.start(Helpers.toolPath(product, 'size'), ['--format=Berkeley', input.fileName]);
            proc.waitForFinished();
            cmd = new JavaScriptCommand();
            cmd.description = "compilation info:\n"+ proc.readStdOut();
            cmd.silent = false;
            cmd.highlight = "linker";
            cmd.sourceCode = function() {
                print("Nothing to do");
            };
            retVal.push(cmd);

            return retVal;
        }
    }

}
