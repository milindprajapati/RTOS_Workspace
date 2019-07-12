################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/system_stm32f30x.c 

OBJS += \
./src/main.o \
./src/system_stm32f30x.o 

C_DEPS += \
./src/main.d \
./src/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F3 -DSTM32F30 -DSTM32F302R8Tx -DNUCLEO_F302R8 -DDEBUG -DSTM32F302x8 -DUSE_STDPERIPH_DRIVER -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Third-Party/SEGGER/Config" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Third-Party/SEGGER/OS" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Third-Party/SEGGER/SEGGER" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Utilities/STM32F3xx_Nucleo" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Config" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/Third-Party/FreeRTOS/org/Source/include" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/StdPeriph_Driver/inc" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/inc" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/CMSIS/device" -I"D:/Udemy/RTOS/RTOS_Workspace/STM32_HelloWorld/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


