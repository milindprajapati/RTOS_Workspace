################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f302x8.s 

OBJS += \
./startup/startup_stm32f302x8.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Utilities/STM32F3xx_Nucleo" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/StdPeriph_Driver/inc" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/inc" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/CMSIS/device" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/CMSIS/core" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


