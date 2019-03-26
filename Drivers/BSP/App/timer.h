/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: timer.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/01/22		00:42:31
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef TIMER_H_
#define	TIMER_H_

#ifdef TIMER_GLOBALS
#define TIMER_EXT
#else
#define  TIMER_EXT extern
#endif

#include "Include.h"
//#include "stm32f4xx.h"
//#include "led.h"
//#include "key.h"
//#include "ecu.h"
//#include "iwdg.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
#define PERIOD_ms(x)	(x)//单位：ms

#define Period_WrReg1000_Defaul	(2000)//写1000寄存器周期,单位：ms
#define Period_NumBCU_Defaul	(1000)//编号BCU周期,单位：ms
#define Period_NWRst_Defaul	(1000)//复位R1s周期,单位：ms
#define Period_NWRestart_Defaul	(1000)//复位R5min周期,单位：ms
#define Period_HeartBeat_Defaul	(1000)//心跳周期,单位：ms
#define Period_WriteNw_Default		(5000)//网络配置周期,单位：ms
#define Period_ReadNw_Default		(2000)//网络查询周期,单位：ms



/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
TIMER_EXT uint32_t t1Tick1ms;
TIMER_EXT uint32_t osTick1ms;

TIMER_EXT uint8_t tag_10ms;
TIMER_EXT uint8_t tag_100ms;
TIMER_EXT uint8_t tag_250ms;
TIMER_EXT uint8_t tag_500ms;
TIMER_EXT uint8_t tag_1s;
TIMER_EXT uint8_t tag_2s;
TIMER_EXT uint8_t tag_5s;
TIMER_EXT uint8_t tag_10s;
TIMER_EXT uint8_t tag_15s;

TIMER_EXT uint8_t tagTime_Reg1000;
TIMER_EXT uint8_t tagTime_NumBCU;
TIMER_EXT uint8_t tagTime_NWRst;
TIMER_EXT uint8_t tagTime_NWRestart;
TIMER_EXT uint8_t tagTime_HeartBeat;
TIMER_EXT uint8_t tagTime_WriteNw;
TIMER_EXT uint8_t tagTime_ReadNw;	
	
TIMER_EXT uint8_t tagTime_ResTest;
TIMER_EXT uint8_t tagTime_HeatBeat;
TIMER_EXT uint8_t Num_Reg1000;


/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/

#endif /* TIMER_H_ */
