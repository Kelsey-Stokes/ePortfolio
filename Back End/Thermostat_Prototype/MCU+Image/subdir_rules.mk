################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1107294271: ../gpiointerrupt.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_8_0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_5_20_00_06/.metadata/product.json" --script "C:/Users/kelse/workspace_v11/Thermostat_Prototype/gpiointerrupt.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1107294271 ../gpiointerrupt.syscfg
syscfg/ti_drivers_config.h: build-1107294271
syscfg/ti_utils_build_linker.cmd.genlibs: build-1107294271
syscfg/syscfg_c.rov.xs: build-1107294271
syscfg/ti_utils_runtime_model.gv: build-1107294271
syscfg/ti_utils_runtime_Makefile: build-1107294271
syscfg/: build-1107294271

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Program Files/MySQL/MySQL Server 8.0/include" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include/xlocale" --include_path="C:/Program Files/MySQL/Connector C++ 8.0/include/jdbc" --include_path="C:/Program Files/MySQL/Connector C++ 8.0/lib64" --include_path="C:/Users/kelse/workspace_v11/Thermostat_Prototype" --include_path="C:/Users/kelse/workspace_v11/Thermostat_Prototype/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos/posix" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/kelse/workspace_v11/Thermostat_Prototype/MCU+Image/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-639339345: ../image.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_8_0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_5_20_00_06/.metadata/product.json" --script "C:/Users/kelse/workspace_v11/Thermostat_Prototype/image.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_net_wifi_config.json: build-639339345 ../image.syscfg
syscfg/: build-639339345

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Program Files/MySQL/MySQL Server 8.0/include" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include/xlocale" --include_path="C:/Program Files/MySQL/Connector C++ 8.0/include/jdbc" --include_path="C:/Program Files/MySQL/Connector C++ 8.0/lib64" --include_path="C:/Users/kelse/workspace_v11/Thermostat_Prototype" --include_path="C:/Users/kelse/workspace_v11/Thermostat_Prototype/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_5_20_00_06/kernel/nortos/posix" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/kelse/workspace_v11/Thermostat_Prototype/MCU+Image/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


