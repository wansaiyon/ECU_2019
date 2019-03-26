/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: include.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/01/22		00:41:47
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef INCLUDE_H_
#define	INCLUDE_H_

#ifdef INCLUDE_GLOBALS
#define INCLUDE_EXT
#else
#define  INCLUDE_EXT extern
#endif

/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/

//Bit Option Command,y:0~7(bit0~bit7)
#define SetBit(x,y)  (x)|=(1<<(y))
#define ClrBit(x,y)  (x)&=~(1<<(y))
#define ReverseBit(x,y)  (x)^=(1<<(y))
#define GetBit(x,y)   ((x)>>(y)&1)

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/


/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
//sys
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


//hal
#include "stm32f4xx.h"
#include "usart.h"
#include "iwdg.h"
#include "spi.h"
#include "arm_math.h"
#include "usbd_cdc_if.h"

//config.h
#include "config.h"
#include "mbcrc16.h"
#if defined(EN_FREERTOS)
#include "cmsis_os.h"
#endif

//bsp
#include "led.h"
#include "key.h"
#include "main.h"
#include "w25qxx.h"
#include "timer.h"
#include "grpdata.h"
#include "ecu.h"
#include "pc.h"
#include "radioland.h"
#include "coordinator.h"
#include "multi_button.h"
#include "flashmemory.h"
#include "mbcrc16.h"
#include "dsa.h"
#include "view.h"
#include "usbvcp.h"

#if defined(EN_FREEMODBUSRTU)
#include "mb.h"
#include "mbport.h"
#include "RegisterList.h"
#include "portcallback.h"
#endif

//soc
#include "basecurve.h"
#include "soc.h"
#include "alarm.h"



#endif /* INCLUDE_H_ */


