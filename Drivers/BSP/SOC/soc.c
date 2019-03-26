/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: soc.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/05		00:32:34
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define SOC_GLOBALS
//#include "Include.h"
#include "soc.h"

/**********************************************************************************/
/*      私有变量声明              	                                		      */
/**********************************************************************************/
//电池参数定义
/**
* @结构体功能  电流传感器参数结构体

Table_BattPara[0]:容量
Table_BattPara[1]:浮充寿命，单位V
Table_BattPara[2]:循环寿命，单位A
Table_BattPara[3]:，单位V
Table_BattPara[4]:，单位mA
Table_BattPara[5]:，单位V
*/
#define T_EFFICIENCY_BIT	(0)///充电效率默认0.9,单位：null
#define T_CAPACITY_BIT		(1)//电池容量,单位：AH
#define T_CIRLIFE_BIT		(2)//设计循环寿命默认150次,单位：AH
#define T_FLTLIFE_BIT		(3)//设计浮充寿命默认96个月,单位：AH
#define T_VL_BIT			(4)//电压等级,2v/12v,单位：null


#define EFFICIENCY	((float)0.9)

static const float T_BattPara[6]={0.9,100,150,96,2,5};

/**********************************************************************************/
/*      私有函数声明              	                                              */
/**********************************************************************************/
static bool bSocStepEn(void);
static float fGetQ(float I,float T);
static float fGetSOCTarget(float gI, float gU);
static float fGetSOCStep(float soc,float q,float *capacity);

/**********************************************************************************/
/*      私有函数实现              	                                              */
/**********************************************************************************/
static bool bSocStepEn(void)
{
	return true;
}
static float fGetQ(float I,float T)
{
	return I*T;
}
static float fGetSOCTarget(float gI, float gU)
{
	UNUSED(fGetSOCTarget);
	return 1;
	//TODO
//	float p10 = -1472;
//	float p01 = 651.9;
//	float p20 = -144.7;
//	float p11 = 259.4;
//	float p02 = -83.41;
//	float p30 = 5.982;
//	float p21 = 11.65;
//	float p12 = -11.26;
//	float p03 = 3.294;

//	return p00 +
//		p10 * IC +
//		p01 * Voltage +
//		p20 * Math.Pow(IC, 2) +
//		p11 * IC * Voltage +
//		p02 * Math.Pow(Voltage, 2) +
//		p30 * Math.Pow(IC, 3) +
//		p21 * Math.Pow(IC, 2) * Voltage +
//		p12 * IC * Math.Pow(Voltage, 2) +
//		p03 * Math.Pow(Voltage, 3);
}

static float fGetSOCStep(float soc,float q,float *capacity)
{
	float retval=0;
	if(BMS.workState==Charge)
		retval=(1-soc)*T_BattPara[T_EFFICIENCY_BIT]*q*BMS.capacity[LASTDISCHARGEDEC];
	else if(BMS.workState==DisCharge)
		retval=soc*q/(capacity[NOWUSED]-capacity[LASTCHARGEDEC]);
	return retval;
}

/**********************************************************************************/
/*      公有函数实现	             	                                              */
/**********************************************************************************/
void vBMSInit(void)
{
	BMS.soc[NOW]=1.0;
	BMS.soc[DISCHARGEOV]=1.0;
	BMS.soc[CHARGEOV]=1.0;
	BMS.T=PERIOD_SOC/3600;
}

float fGetSOC(void)
{
	float Q;
	Q=fGetQ((float)ECUInfo.grpData.I[0],BMS.T);
	if(!BMS.en_SocStep)return BMS.soc[NOW];

	switch(BMS.workState)
	{
		case Neither:
			Q=0;
		break;

		case Charge:
			if(BMS.full)vCC2530_RestTest(SingleCast);

			BMS.soc[NOW]+=fGetSOCStep(BMS.soc[DISCHARGEOV],Q,BMS.capacity);
			if(BMS.en_SocCalib)bSocStepEn();
			BMS.capacity[NOWDEC]-=T_BattPara[T_EFFICIENCY_BIT]*Q;
			BMS.capacity[TOTALINC]+=Q;

			BMS.soc[CHARGEOV]=BMS.soc[NOW];
			BMS.capacity[LASTCHARGEDEC]=BMS.capacity[NOWDEC];

		break;

		case DisCharge:
			BMS.capacity[NOWUSED]=BMS.coeCalibSoc[0]*BMS.coeAge[KC]*BMS.coeAge[KF]*BMS.coeAge[KK]*T_BattPara[T_CAPACITY_BIT];

			BMS.soc[NOW]+=fGetSOCStep(BMS.soc[CHARGEOV],Q,BMS.capacity);
			if(BMS.en_SocCalib)bSocStepEn();

			BMS.capacity[NOWDEC]-=Q;
			BMS.capacity[TOTALDEC]-=Q;

			BMS.soc[DISCHARGEOV]=BMS.soc[NOW];
			BMS.capacity[LASTDISCHARGEDEC]=BMS.capacity[NOWDEC];


		break;
		default:
		break;
	}


	return 1;
}








/*****************************************End of soc.c*****************************************/
