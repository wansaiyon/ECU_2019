################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./Middlewares/USB_Device_Library/usbd_cdc.o \
./Middlewares/USB_Device_Library/usbd_core.o \
./Middlewares/USB_Device_Library/usbd_ctlreq.o \
./Middlewares/USB_Device_Library/usbd_ioreq.o 

C_DEPS += \
./Middlewares/USB_Device_Library/usbd_cdc.d \
./Middlewares/USB_Device_Library/usbd_core.d \
./Middlewares/USB_Device_Library/usbd_ctlreq.d \
./Middlewares/USB_Device_Library/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/USB_Device_Library/usbd_cdc.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_core.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_ctlreq.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_ioreq.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


