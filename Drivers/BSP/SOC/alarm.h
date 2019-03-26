/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: alarm.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/05		23:27:08
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef ALARM_H_
#define	ALARM_H_

#ifdef ALARM_GLOBALS
#define ALARM_EXT
#else
#define  ALARM_EXT extern
#endif

/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/


/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/
typedef enum
{
	U_warning_oorh,
	U_warning_oorl,
	U_fault_oorh,
	U_fault_oorl,

	T_warning_oorh,
	T_warning_oorl,
	T_fault_oorh,
	T_fault_oorl,

	R_warning_oorh,
	R_warning_oorl,
	R_fault_oorh,
	R_fault_oorl
}CellAlarmType_TypeDef;
typedef enum
{
	gU_warning_oorh,
	gU_warning_oorl,
	gU_fault_oorh,
	gU_fault_oorl,

	gT_warning_oorh,
	gT_warning_oorl,
	gT_fault_oorh,
	gT_fault_oorl,
	gT_burst,

	gI_warning_oorh,
	gI_warning_oorl,
	gI_fault_oorh,
	gI_fault_oorl
}GrpAlarmType_TypeDef;

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
typedef struct
{


	uint8_t (*pFun)(float);
}OBD_Typdef;

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/


/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/



#endif /* ALARM_H_ */
