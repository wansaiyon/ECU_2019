################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/App/coordinator.c \
../Drivers/BSP/App/dsa.c \
../Drivers/BSP/App/ecu.c \
../Drivers/BSP/App/flashmemory.c \
../Drivers/BSP/App/grpdata.c \
../Drivers/BSP/App/mbcrc16.c \
../Drivers/BSP/App/multi_button.c \
../Drivers/BSP/App/pc.c \
../Drivers/BSP/App/timer.c \
../Drivers/BSP/App/usbvcp.c \
../Drivers/BSP/App/view.c 

OBJS += \
./Drivers/BSP/App/coordinator.o \
./Drivers/BSP/App/dsa.o \
./Drivers/BSP/App/ecu.o \
./Drivers/BSP/App/flashmemory.o \
./Drivers/BSP/App/grpdata.o \
./Drivers/BSP/App/mbcrc16.o \
./Drivers/BSP/App/multi_button.o \
./Drivers/BSP/App/pc.o \
./Drivers/BSP/App/timer.o \
./Drivers/BSP/App/usbvcp.o \
./Drivers/BSP/App/view.o 

C_DEPS += \
./Drivers/BSP/App/coordinator.d \
./Drivers/BSP/App/dsa.d \
./Drivers/BSP/App/ecu.d \
./Drivers/BSP/App/flashmemory.d \
./Drivers/BSP/App/grpdata.d \
./Drivers/BSP/App/mbcrc16.d \
./Drivers/BSP/App/multi_button.d \
./Drivers/BSP/App/pc.d \
./Drivers/BSP/App/timer.d \
./Drivers/BSP/App/usbvcp.d \
./Drivers/BSP/App/view.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/App/%.o: ../Drivers/BSP/App/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


