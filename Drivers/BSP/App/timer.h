/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: timer.h
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/01/22		00:42:31
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
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
#define PERIOD_ms(x)	(x)//��λ��ms

#define Period_WrReg1000_Defaul	(2000)//д1000�Ĵ�������,��λ��ms
#define Period_NumBCU_Defaul	(1000)//���BCU����,��λ��ms
#define Period_NWRst_Defaul	(1000)//��λR1s����,��λ��ms
#define Period_NWRestart_Defaul	(1000)//��λR5min����,��λ��ms
#define Period_HeartBeat_Defaul	(1000)//��������,��λ��ms
#define Period_WriteNw_Default		(5000)//������������,��λ��ms
#define Period_ReadNw_Default		(2000)//�����ѯ����,��λ��ms



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
