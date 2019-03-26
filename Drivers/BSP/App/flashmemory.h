/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: flashmemory.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/08		06:28:06
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef FLASHMEMORY_H_
#define	FLASHMEMORY_H_

#ifdef FLASHMEMORY_GLOBALS
#define FLASHMEMORY_EXT
#else
#define  FLASHMEMORY_EXT extern
#endif

#include "Include.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
//important parameters saving address
//block1
#define FLASHADDR_BLOCK1	(0x00)
#define SIZE_BLOCK1	(0x07)
#define FLASHADDR_ECU_slaveID				(0x00)
#define FLASHADDR_ECU_battJarNum		(0x01)
#define FLASHADDR_ECU_nwParaC1			(0x02)
#define FLASHADDR_ECU_nwParaC2			(0x03)
#define FLASHADDR_ECU_nwParaC3			(0x04)
#define FLASHADDR_BLK1_CRCMSB    		(0x05)
#define FLASHADDR_BLK1_CRCLSB				(0x06)


//block2
#define SIZE_BLOCK2	(0x06)
#define FLASHADDR_ECU_HALL_A_Charge					(0x05)
#define FLASHADDR_ECU_HALL_V_Charge					(0x06)
#define FLASHADDR_ECU_HALL_A_DisCharge			(0x07)
#define FLASHADDR_ECU_HALL_V_DisCharge			(0x08)
#define FLASHADDR_ECU_HALL_A_LeakageCurr		(0x09)
#define FLASHADDR_ECU_HALL_V_LeakageCurr		(0x0A)

//block3
#define SIZE_BLOCK3	(0x05)
#define FLASHADDR_ECU_Calib_kU					(0x0B)
#define FLASHADDR_ECU_Calib_kI					(0x0C)
#define FLASHADDR_ECU_Calib_kT					(0x0D)
#define FLASHADDR_ECU_Calib_bU					(0x0E)
#define FLASHADDR_ECU_Calib_bI					(0x0F)
#define FLASHADDR_ECU_Calib_bT					(0x10)


#define BLOCKx_FLASH(x)	(x)












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
FLASHMEMORY_EXT void vLoad_FlashMemory(void);


#endif /* FLASHMEMORY_H_ */

