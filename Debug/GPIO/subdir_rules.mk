################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
GPIO/%.obj: ../GPIO/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/ahmed/OneDrive/Desktop/CCS_WS1/Free_RTOS1" --include_path="C:/Users/ahmed/OneDrive/Desktop/CCS_WS1/Free_RTOS1/Common" --include_path="C:/Users/ahmed/OneDrive/Desktop/CCS_WS1/Free_RTOS1/GPIO" --include_path="C:/Users/ahmed/OneDrive/Desktop/CCS_WS1/Free_RTOS1/GPTM" --include_path="C:/Users/ahmed/OneDrive/Desktop/CCS_WS1/Free_RTOS1/UART" --include_path="C:/Users/ahmed/OneDrive/Desktop/CCS_WS1/Free_RTOS1/Source/include" --include_path="C:/Users/ahmed/OneDrive/Desktop/CCS_WS1/Free_RTOS1/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="GPIO/$(basename $(<F)).d_raw" --obj_directory="GPIO" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


