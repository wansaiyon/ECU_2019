/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: grpdata.h
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/04		01:03:23
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
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
//�˲�����������ͨ������
//Count of Filter: 100,	Number of ADC1 Channel:	9
#define ADC1_N 101
#define ADC1_M 9
//Count of Filter: 100,	Number of ADC3 Channel:	6
#define ADC3_N 101
#define ADC3_M 6	

//FIR��������
#define N_FIR 101

//�˲���������
#define MEAN_FILTER 0			//��ֵ
#define FIRSTORDER_FILTER 1//�����˲�
#define FIR_FILTER_MATLAB 2//FIR
#define FIR_FILTER_ARM_DSP 3
#define KALMAN_FILTER 4	//kalman

//�¶ȼ��㷽������0:ʹ�ù�ʽ�� 1:ʹ�ò��
#define T_LOOKUPTABLE	(1)



/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
#if		T_LOOKUPTABLE==(1)
/**
* @�ṹ�幦�� ������ż�¶Ȳ��ṹ��
*/
typedef struct
{
	float  uDLookupTable1_tableData[171];		//Temperature,-45��~ 125��
	uint16_t  uDLookupTable1_bp01Data[171];		//ADC
}NTC_LookUpTable_TypeDef;
#elif   T_LOOKUPTABLE==(0)
/**
* @�ṹ�幦�� ������ż��׼�����ṹ��
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
