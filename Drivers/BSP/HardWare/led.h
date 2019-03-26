/*
********************************************************************************
*Copyright (C), 2019, CunXin_ All Rights Reserved
*�� �� ��: led.h
*˵    ��:
*��    ��: V000B00D00
*��������: 2019/01/22		00:42:15
*�� �� ��: wansaiyon
*�޸���Ϣ��
================================================================================
*�� �� ��    		  �޸�����       	  �޸�����
*<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#ifndef LED_H_
#define	LED_H_

#ifdef LED_GLOBALS
#define LED_EXT
#else
#define  LED_EXT extern
#endif

#include "Include.h"
//#include "stm32f4xx.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
//LEDӲ�����Ŷ���


//LED�����𡢷�ת����


//LEDʹ�ܶ���
#define  LED1_GREEN_EN            0x08   
#define  LED2_ORANGE_EN           0x04   
#define  LED3_ORANGE_EN           0x02   
#define  LED4_ORANGE_EN           0x01  


//LED��˸���ڶ���
#define  LED_PERIOD_EXFAST	(10)	//������˸��100ms����,��λ:10ms
#define  LED_PERIOD_FAST		(20)	//������˸��200ms����,��λ:10ms
#define  LED_PERIOD_MIDIUM	(50)	//������˸��500ms����,��λ:10ms
#define  LED_PERIOD_LOW			(100)	//������˸��1000ms����,��λ:10ms

//LED����ҵ���߼����ڶ���
#define  LED_PERIOD_SYSINIT		LED_PERIOD_FAST	
#define  LED_PERIOD_ERR				LED_PERIOD_EXFAST	
#define  LED_PERIOD_NUMECU		LED_PERIOD_EXFAST	

//LED��˸��������
#define  LED_CNT_SYSINIT		(4)		//ϵͳ��ʼ����˸����
#define  LED_CNT_NUMECU			(4)	//���ECU��˸����
#define  LED_CNT_CALIBV			(125)	//��λ����ģ����˸����


#define Led_SysRun()			{Led_Init(LED1_GREEN_EN,LED_PERIOD_SYSINIT,LED_CNT_CALIBV);}
/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
* @ö�ٹ��� LED�ṹ��
*/
typedef struct
{
	uint8_t	En;	   //bit0==1.ʹ��Led1��˸  bit1==1.ʹ��Led2��˸
	uint8_t Cnt;   //��˸����
	uint8_t	Tick;  //����������λ:10ms
	uint8_t Peroid;//����,��λ:10ms
}Led_TypeDef;

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
LED_EXT Led_TypeDef Led;
/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
LED_EXT void vLed_Init(uint8_t ledEn,uint8_t period,uint8_t cnt);
LED_EXT void vLed_Start(void);
LED_EXT void vLed_ShowSlaveID(void);
#endif /* LED_H_ */

