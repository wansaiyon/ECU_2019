/*
********************************************************************************
*Copyright (C), 2019, CunXin_ All Rights Reserved
*文 件 名: led.h
*说    明:
*版    本: V000B00D00
*创建日期: 2019/01/22		00:42:15
*创 建 人: wansaiyon
*修改信息：
================================================================================
*修 改 人    		  修改日期       	  修改内容
*<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
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
//LED硬件引脚定义


//LED亮、灭、翻转定义


//LED使能定义
#define  LED1_GREEN_EN            0x08   
#define  LED2_ORANGE_EN           0x04   
#define  LED3_ORANGE_EN           0x02   
#define  LED4_ORANGE_EN           0x01  


//LED闪烁周期定义
#define  LED_PERIOD_EXFAST	(10)	//超速闪烁，100ms周期,单位:10ms
#define  LED_PERIOD_FAST		(20)	//快速闪烁，200ms周期,单位:10ms
#define  LED_PERIOD_MIDIUM	(50)	//中速闪烁，500ms周期,单位:10ms
#define  LED_PERIOD_LOW			(100)	//慢速闪烁，1000ms周期,单位:10ms

//LED常用业务逻辑周期定义
#define  LED_PERIOD_SYSINIT		LED_PERIOD_FAST	
#define  LED_PERIOD_ERR				LED_PERIOD_EXFAST	
#define  LED_PERIOD_NUMECU		LED_PERIOD_EXFAST	

//LED闪烁次数定义
#define  LED_CNT_SYSINIT		(4)		//系统初始化闪烁次数
#define  LED_CNT_NUMECU			(4)	//编号ECU闪烁次数
#define  LED_CNT_CALIBV			(125)	//复位无线模块闪烁次数


#define Led_SysRun()			{Led_Init(LED1_GREEN_EN,LED_PERIOD_SYSINIT,LED_CNT_CALIBV);}
/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
* @枚举功能 LED结构体
*/
typedef struct
{
	uint8_t	En;	   //bit0==1.使能Led1闪烁  bit1==1.使能Led2闪烁
	uint8_t Cnt;   //闪烁次数
	uint8_t	Tick;  //计数器，单位:10ms
	uint8_t Peroid;//周期,单位:10ms
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

