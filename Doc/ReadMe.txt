һ.Ӳ���ͺ�:
stm32f407zet6
FLASH:512KB,
SRAM:192KB


��.����汾��¼

1.ECULIB_V001B00D00,2019/1/22,wansaiyon

1)��ʼ���ײ�����,MDK��ECLIPSE��������
2)�����޸�ECUӦ�ò����
3)ʹ��DMA�����жϽ���UART1��2,3,6����
4)����USBͨ���豸��
5)����DSP
6)֧��printf_uartmode,printf_vcpmode,TODO:printf_vcpmode���������Ḵλ
7)TODO:CAN1,SPI2��LCD,SRAM,SD Card


2.OS_ECULIB_V001B00D00,2019/1/22,wansaiyon

1)����ECULIB_V001B00D00��ֲFreeRTOS
2)���Ӽ����ź���ͬ������
3)���������ʱ������
4)֧��printf_uartmode,TODO:printf_vcpmode��֧��
5)TODO:eclipse�����³���ʹ��vTestDemo_CC2530UpDwRate��ӡ�����������

3.SerialIAP_BootLoader_ECULIB_V001B00D00,2019/1/22,wansaiyon

1)bootloader��С��Ƴ�sector0,16kb=0x4000
#define APPLICATION_ADDRESS   (uint32_t)0x08004000
2)bootloader��¼�ļ�����BootLoader_Flash_SerialIAP.hex������BootLoader_Flash_SerialIAP.elf��
3)tools:securecrt8.5

4.OS_ECULIB_V002B00D00,2019/1/22,wansaiyon

1)TODO:����OS_ECULIB_V001B00D00
2)TODO:��������/��Ϣ���д�������жϵ�����
3)TODO:���������ʱ������
4)TODO:�����̶߳�ȡ����/��Ϣ�������ݣ�������1,2,3,6����

5.USBDFU_BootLoader_ECULIB_V002B00D00,2019/1/22,wansaiyon

1)TODO:USB��������


��.ʹ����Դ
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
��Library������Ҫ����arm_cortexM4lf_math.lib/libarm_cortexM4lf_math.a
keil:��λ��Ϊ\Drivers\CMSIS\Lib\ARM\arm_cortexM4lf_math.lib
keil:��λ��Ϊ\Drivers\CMSIS\Lib\GCC\libarm_cortexM4lf_math.a