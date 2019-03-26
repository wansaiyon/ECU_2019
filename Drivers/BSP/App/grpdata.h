/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: grpdata.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/04		01:03:23
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef GRPDATA_H_
#define	GRPDATA_H_

#ifdef GRPDATA_GLOBALS
#define GRPDATA_EXT
#else
#define  GRPDATA_EXT extern
#endif

#include "Include.h"
//#include "stm32f4xx.h"
//#include "ecu.h"
//#include<math.h>
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
//滤波点数及采样通道定义
//Count of Filter: 100,	Number of ADC1 Channel:	9
#define ADC1_N 101
#define ADC1_M 9
//Count of Filter: 100,	Number of ADC3 Channel:	6
#define ADC3_N 101
#define ADC3_M 6	

//FIR阶数定义
#define N_FIR 101

//滤波方法定义
#define MEAN_FILTER 0			//均值
#define FIRSTORDER_FILTER 1//惯性滤波
#define FIR_FILTER_MATLAB 2//FIR
#define FIR_FILTER_ARM_DSP 3
#define KALMAN_FILTER 4	//kalman

//温度计算方法定义0:使用公式法 1:使用查表法
#define T_LOOKUPTABLE	(1)



/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
#if		T_LOOKUPTABLE==(1)
/**
* @结构体功能 热敏电偶温度查表结构体
*/
typedef struct
{
	float  uDLookupTable1_tableData[171];		//Temperature,-45℃~ 125℃
	uint16_t  uDLookupTable1_bp01Data[171];		//ADC
}NTC_LookUpTable_TypeDef;
#elif   T_LOOKUPTABLE==(0)
/**
* @结构体功能 热敏电偶标准参数结构体
*/
typedef struct 
{
	float vref;         /*!< Referense voltage*/
	float ad_resolution; /*!< A:D resolution*/
	int ntc_res;        /*!< NTC resistance value at 25C*/
	int ntc_tol;        /*!< NTC initial tolerance %*/
	int ntc_beta_0050;  /*!< NTC Beta, B0/50*/
	int ntc_beta_2550;  /*!< NTC Beta, B25/50*/
	int ntc_beta_2580;  /*!< NTC Beta, B25/80*/
	int ntc_beta_2585;  /*!< NTC Beta, B25/85*/
	int ntc_beta_25100; /*!< NTC Beta, B25/100*/
	int ntc_beta_other; /*!< NTC Beta, other value vs temp*/
	int ntc_beta_tol;   /*!< NTC Beta tolerance %*/
	int sres_res;       /*!< Series resistor value*/
	int sres_tol;       /*!< Series resistor tolerance %*/
	int sres_ppm;       /*!< Series resistor tempco in ppm*/
} NTC_StandardPara_TypeDef;
#endif
/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
//HalfWord,12Bits ADC
GRPDATA_EXT uint16_t ADC1Buf[ADC1_N][ADC1_M];
GRPDATA_EXT uint16_t ADC3Buf[ADC3_N][ADC3_M];
//After Filter
GRPDATA_EXT float ADC1Filter[ADC1_M];
GRPDATA_EXT float ADC3Filter[ADC3_M]; 


/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
GRPDATA_EXT void vGrpData_Proc(void);

#endif /* GRPDATA_H_ */
