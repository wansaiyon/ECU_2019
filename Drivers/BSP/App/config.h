/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: config.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/11		01:51:27
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef CONFIG_H_
#define	CONFIG_H_

#ifdef CONFIG_GLOBALS
#define CONFIG_EXT
#else
#define  CONFIG_EXT extern
#endif

#include "include.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/

/* pcConfig.h	*/
#define		PC_Usart				huart1
//#define EN_FREEMODBUSRTU
//#define EN_RS485

/* coordinatorConfig.h */
#define		Coordinator1_Usart		huart2
#define		Coordinator2_Usart		huart3
#define		Coordinator3_Usart		huart6

/* keyConfig.h */
#define  PRINT_KEY

/* ecuConfig.h */
//#define  PRINT_ECUMODE
#define  PRINT_ECUINFORMATION
#define  PRINT_ECUINFORMATION_INIT

/* flashMemoryConfig.h */
#define  PRINT_FLASHMEMORY
#define  EN_W25Q16

/* coordinatorConfig.h */
//#define  PRINT_BCUDATA
#define	EN_FREERTOS
#if defined(EN_FREERTOS)
#define DelayMs(x)	osDelay((x))
#else
#define DelayMs(x)	HAL_Delay((x))
#endif

/* viewConfig.h */
#define EN_VIEWSTMSTD





/* ECU Test */
#define CC2530TEST_UPDOWNRATE
#define PRINT_CC2530TEST_UPDOWNRATE
//#define VIEWMODBUSPOLL_CC2530TEST_UPDOWNRATE
#if defined(CC2530TEST_UPDOWNRATE)
#define MAXROUTER_Test(x) 	(x)
#define BCUNUM_Test					(4)//分别测试4个点，10个点，15个点下行点播成功率
#endif






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



#endif /* CONFIG_H_ */
