################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/harle/Documents/ECE3849Lab1/Lab2_FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/utils" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/Users/harle/Documents/ECE3849Lab1/FreeRTOS/include" --include_path="C:/Users/harle/Documents/ECE3849Lab1/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/HAL_TM4C1294" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/OPT3001" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/buttonsDriver" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/display" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/elapsedTime" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/joystickDriver" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/timerLib" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/harle/Documents/ECE3849Lab1/Lab2_FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/utils" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/Users/harle/Documents/ECE3849Lab1/FreeRTOS/include" --include_path="C:/Users/harle/Documents/ECE3849Lab1/FreeRTOS/portable/CCS/ARM_CM4F" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/HAL_TM4C1294" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/OPT3001" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/buttonsDriver" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/display" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/elapsedTime" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/joystickDriver" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries" --include_path="C:/Users/harle/Documents/ECE3849Lab1/libraries/timerLib" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


