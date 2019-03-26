/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: soc.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/05		00:32:41
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef SOC_H_
#define	SOC_H_

#ifdef SOC_GLOBALS
#define SOC_EXT
#else
#define  SOC_EXT extern
#endif

#include "Include.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
#define PERIOD_SOC	((uint8_t)1)	//步进时间,单位：秒
/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/
/**
* @枚举功能
*/
typedef enum
{
	VL_2V   				 =0x00,	//额定电压2V
	VL_12V   			 	 =0x01	//额定电压12V
}VoltLevel_TypeDef;
/**
* @枚举功能
*/
typedef enum
{
	Neither   				 =0x00,	//静置
	Charge   			 	 =0x01,	//充电
	DisCharge				 =0x02	//放电
}BattWorkState_TypeDef;
/**
* @枚举功能
*/
typedef enum
{
	KC   				 =0x00,	//电池容量系数
	KF   			 	 =0x01,	//浮充老化系数
	KK				 	 =0x02,	//温度容量系数
	KT				 	 =0x03	//浮充寿命温度折算系数
}LookUpTable1D_K_TypeDef;

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
#define NOWINC				((uint8_t)0)
#define NOWDEC				((uint8_t)1)
#define LASTCHARGEDEC		((uint8_t)2)
#define LASTDISCHARGEDEC	((uint8_t)3)
#define TOTALINC	((uint8_t)4)
#define TOTALDEC	((uint8_t)5)
#define NOWUSED		((uint8_t)6)

#define NOW			((uint8_t)0)
#define DISCHARGEOV	((uint8_t)1)
#define CHARGEOV	((uint8_t)2)

typedef struct
{
	bool en_SocStep;//SOC步进计算使能
	bool en_SocCalib;//SOC校准使能
	bool full;//充满标志
	float T;//单位:小时
	float ic;//放电倍率
	float soc[3];
	float soh;
	float bkT;

	float capacity[7];
	float resFltLife;
	float resCirLife;
	float coeCalibSoc[3];
	float coeAge[4];
	VoltLevel_TypeDef vl;
	BattWorkState_TypeDef workState;
}BMS_TypdeDef;
/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
SOC_EXT BMS_TypdeDef BMS;

/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
SOC_EXT void vBMSInit(void);
SOC_EXT float fGetSOC(void);

#endif /* SOC_H_ */
