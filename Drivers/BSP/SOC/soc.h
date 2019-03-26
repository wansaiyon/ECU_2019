/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: soc.h
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/05		00:32:41
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
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
#define PERIOD_SOC	((uint8_t)1)	//����ʱ��,��λ����
/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/
/**
* @ö�ٹ���
*/
typedef enum
{
	VL_2V   				 =0x00,	//���ѹ2V
	VL_12V   			 	 =0x01	//���ѹ12V
}VoltLevel_TypeDef;
/**
* @ö�ٹ���
*/
typedef enum
{
	Neither   				 =0x00,	//����
	Charge   			 	 =0x01,	//���
	DisCharge				 =0x02	//�ŵ�
}BattWorkState_TypeDef;
/**
* @ö�ٹ���
*/
typedef enum
{
	KC   				 =0x00,	//�������ϵ��
	KF   			 	 =0x01,	//�����ϻ�ϵ��
	KK				 	 =0x02,	//�¶�����ϵ��
	KT				 	 =0x03	//���������¶�����ϵ��
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
	bool en_SocStep;//SOC��������ʹ��
	bool en_SocCalib;//SOCУ׼ʹ��
	bool full;//������־
	float T;//��λ:Сʱ
	float ic;//�ŵ籶��
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
