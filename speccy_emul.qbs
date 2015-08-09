import qbs
import qbs.FileInfo
import qbs.File
import qbs.ModUtils
import qbs.Process
import qbs.TextFile

import "qbs/imports/helpers.js" as Helpers
import "qbs/imports/modulesinfo.js" as ModulesInfo

Product {
    type: ["postbuild"] // To suppress bundle generation on Mac

    Depends { name: "cpp" }

    property bool createAsmDump: true


    property stringList baseDefines: {
        var defines =
                [
                    "STM32F429xx",
                    "USE_HAL_DRIVER",
                    "HSE_VALUE=8000000",
                    "DATA_IN_ExtSDRAM"
                ];
        return defines;
    }

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
        "Drivers/CMSIS/Include",
        "Drivers/STM32F4xx_HAL_Driver/Inc",
        "Drivers/CMSIS/Device/ST/STM32F4xx/Include",
        "Inc",
        "Drivers/stm32f429i-discovery",
        "."
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
        name: "debug_build"
        condition: qbs.buildVariant == "debug"
        cpp.defines: baseDefines.concat([
                     "DEBUG=1"
                     ])
        cpp.commonCompilerFlags: baseCommonCompilerFlags
    }

    Properties  {
        name: "release_build"
        condition: qbs.buildVariant == "release"
        cpp.defines: baseDefines
        cpp.commonCompilerFlags: baseCommonCompilerFlags
    }

    Group {
        name: "device"
        prefix: "Drivers/CMSIS/Device/ST/STM32F4xx/"
        files: [
            "Include/stm32f429xx.h",
            "Include/stm32f4xx.h",
            "Include/system_stm32f4xx.h",
            "Source/Templates/gcc/startup_stm32f429xx.s",
            "Source/Templates/system_stm32f4xx.c",
        ]
    }

    Group {
        name: "src"
        files: [
            "Src/*.c",
            "Src/*.s",
            "Inc/*.h"
        ]
    }

    Group {
        name: "z80"
        files: [
            "z80/z80.c",
            "z80/z80.h",
        ]
    }

    Group {
        name: "cmsis"
        prefix: "Drivers/CMSIS/"
        files: [
            "Include/*.h",
        ]

    }

    Group {
        name: "newlib"
        files: [
            "Drivers/newlib/syscalc.c",
        ]
    }

    Group {
        name: "discovery-board"
        prefix: ""
        files: [
            "Drivers/stm32f429i-discovery/*.h",
            "Drivers/stm32f429i-discovery/*.c",
        ]
    }

    Group {
        name: "hal"
        prefix: "Drivers/STM32F4xx_HAL_Driver/"
        files: [
            "Src/*.c",
            "Inc/*.h",
        ]
        excludeFiles: "Src/stm32f4xx_hal_msp_template.*"

    }
/*
    Group {
        name: "hal"
        prefix: "../system/"
        files: {
	    f = "";
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

    */

    Group {
        name: "ldscripts"
        prefix: "ldscripts/"
        files: [ "*.ld" ]
    }

    cpp.linkerScripts: [
        "ldscripts/*.ld"

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
