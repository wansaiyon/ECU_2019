################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/adc.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/dac.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/dma.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/freertos.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/gpio.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/iwdg.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/main.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/rng.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/rtc.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/spi.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/stm32f4xx_hal_msp.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/stm32f4xx_hal_timebase_TIM.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/stm32f4xx_it.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/tim.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usart.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usb_device.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usbd_cdc_if.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usbd_conf.c \
F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usbd_desc.c 

OBJS += \
./Application/User/adc.o \
./Application/User/dac.o \
./Application/User/dma.o \
./Application/User/freertos.o \
./Application/User/gpio.o \
./Application/User/iwdg.o \
./Application/User/main.o \
./Application/User/rng.o \
./Application/User/rtc.o \
./Application/User/spi.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_hal_timebase_TIM.o \
./Application/User/stm32f4xx_it.o \
./Application/User/tim.o \
./Application/User/usart.o \
./Application/User/usb_device.o \
./Application/User/usbd_cdc_if.o \
./Application/User/usbd_conf.o \
./Application/User/usbd_desc.o 

C_DEPS += \
./Application/User/adc.d \
./Application/User/dac.d \
./Application/User/dma.d \
./Application/User/freertos.d \
./Application/User/gpio.d \
./Application/User/iwdg.d \
./Application/User/main.d \
./Application/User/rng.d \
./Application/User/rtc.d \
./Application/User/spi.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_hal_timebase_TIM.d \
./Application/User/stm32f4xx_it.d \
./Application/User/tim.d \
./Application/User/usart.d \
./Application/User/usb_device.d \
./Application/User/usbd_cdc_if.d \
./Application/User/usbd_conf.d \
./Application/User/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/adc.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/dac.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/dac.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/dma.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/freertos.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/freertos.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/gpio.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/iwdg.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/iwdg.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/rng.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/rng.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/rtc.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/spi.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_timebase_TIM.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/stm32f4xx_hal_timebase_TIM.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/tim.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usart.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usb_device.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usb_device.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_cdc_if.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usbd_cdc_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_conf.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usbd_conf.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_desc.o: F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Src/usbd_desc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx '-DARM_MATH_CM4=1' -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/MyWorkSpaceFile/MCU/SFE/ECU_LibVer/ECU_2019/OS_ECULIB_V001B00D00/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


