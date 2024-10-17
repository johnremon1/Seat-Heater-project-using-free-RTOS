################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
File_System/%.obj: ../File_System/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/the c file of/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/File_System" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/Common" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/MCAL" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/Source/include" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/HAL" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/HAL/ADC" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/Source/portable/CCS/ARM_CM4F" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/MCAL/GPTM" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/MCAL/UART" --include_path="D:/embede systems course/advnaced diploma/RTOS/final RTOS project/Final_RTOS_project/MCAL/GPIO" --include_path="E:/the c file of/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="File_System/$(basename $(<F)).d_raw" --obj_directory="File_System" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


