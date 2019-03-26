一.硬件型号:
stm32f407zet6
FLASH:512KB,
SRAM:192KB


二.软件版本记录

1.ECULIB_V001B00D00,2019/1/22,wansaiyon

1)初始化底层驱动,MDK及ECLIPSE开发环境
2)配套修改ECU应用层程序
3)使用DMA接收中断接收UART1，2,3,6数据
4)增加USB通信设备类
5)增加DSP
6)支持printf_uartmode,printf_vcpmode,TODO:printf_vcpmode按键触发会复位
7)TODO:CAN1,SPI2及LCD,SRAM,SD Card


2.OS_ECULIB_V001B00D00,2019/1/22,wansaiyon

1)基于ECULIB_V001B00D00移植FreeRTOS
2)增加计数信号量同步任务
3)增加软件定时器任务
4)支持printf_uartmode,TODO:printf_vcpmode不支持
5)TODO:eclipse环境下持续使用vTestDemo_CC2530UpDwRate打印输出存在问题

3.SerialIAP_BootLoader_ECULIB_V001B00D00,2019/1/22,wansaiyon

1)bootloader大小设计成sector0,16kb=0x4000
#define APPLICATION_ADDRESS   (uint32_t)0x08004000
2)bootloader烧录文件：“BootLoader_Flash_SerialIAP.hex”，“BootLoader_Flash_SerialIAP.elf”
3)tools:securecrt8.5

4.OS_ECULIB_V002B00D00,2019/1/22,wansaiyon

1)TODO:基于OS_ECULIB_V001B00D00
2)TODO:增加邮箱/消息队列处理接收中断的数据
3)TODO:增加软件定时器任务
4)TODO:增加线程读取邮箱/消息队列数据，处理串口1,2,3,6数据

5.USBDFU_BootLoader_ECULIB_V002B00D00,2019/1/22,wansaiyon

1)TODO:USB升级程序


三.使用资源
1)eclipse
preprocessor:
ARM_MATH_CM4=1
includes:
../../../SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App
../../../SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare
../../../SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC

miscellaneous:
Linker flags:-specs=nosys.specs -specs=nano.specs -u _printf_float

config.h:#define	EN_FREERTOS
2)keil
preprocessor:
ARM_MATH_CM4=1
includes:
../SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/App
../SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/HardWare
../SW4STM32/ECU_STM32F407ZET6/Drivers/BSP/SOC

config.h://#define	EN_FREERTOS
3)DSP
在Library部分需要加入arm_cortexM4lf_math.lib/libarm_cortexM4lf_math.a
keil:其位置为\Drivers\CMSIS\Lib\ARM\arm_cortexM4lf_math.lib
keil:其位置为\Drivers\CMSIS\Lib\GCC\libarm_cortexM4lf_math.a