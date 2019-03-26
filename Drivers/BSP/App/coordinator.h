/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: coordinator.h
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/02		04:39:46
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#ifndef COORDINATOR_H_
#define	COORDINATOR_H_

#ifdef COORDINATOR_GLOBALS
#define COORDINATOR_EXT
#else
#define  COORDINATOR_EXT extern
#endif

//#include "pc.h"
//#include "timer.h"
#include "Include.h"

/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
#define MAXBCU_Default			(512)//Э�����֧��BCU����512��
#define MAXROUTER_Default		(40)//1coordinatorĬ������40Router

// ���µ��֡
// TODO nextBCUNum,numNextBcu_Tick,numNextBcu_En
#define UPDATE_NUMBCU_LEDFRAME_C(x)  {nextBCUNum=Coordinator[x].Cfg.BCUNum;numNextBcu_Tick=0x00;numNextBcu_En =0x01;}
// ���±��֡
#define UPDATE_NUMBCU_NUMFRAME_C(x)  {Coordinator[x].Cfg.BCUNum++;Coordinator[x].Cfg.BCUTime=0x00;}

#define NONE_CONFIG_MODE   (0x00)      //û������
#define FULL_CONFIG_MODE   (0x01)      //ȫ����ģʽ����װ��������ģʽ������bcu����Ҫ��ź��ٷ���,B3��3�δ���,��4���˳�����̨����120��
#define PART_CONFIG_MODE   (0x02)      //��������ģʽ������BCU��Ҫ��ţ�B2��3�δ���,��4���˳�
#define OVER_NONE_CONFIG_MODE   		(0x00) //���������
#define OVER_FULL_CONFIG_MODE   		(0x01) //ȫ�������
#define OVER_PART_CONFIG_MODE   		(0x02) //�����������
#define USEROVER_PART_CONFIG_MODE   (0x04) //�����������,���û���ֹ
#define OVER_ALL_CONFIG_MODE    		(0x08)   //ȫ\��ʱ�������

//�㲥������
#define POLLTASK_NUM	(8)				//�㲥��ѯ���������
#define POLLTASK_WRREG1000			(0x00)//д1000�Ĵ���
#define POLLTASK_NUMBCU					(0x01)//���BCU
#define POLLTASK_NWRST					(0x02)//��λRouter1S
#define POLLTASK_NWRESTART			(0x03)//��λRouter5MIN,��������
#define POLLTASK_HEARTBEAT			(0x04)//����ͬ��
//add something here


//�㲥���ͺ�ֹͣʱ�䶨��
#define TXSTOPTICKS_WRREG1000 (2)//Э��������һȦ��ֹͣʱ��,��λ:��
#define TXSTOPTICKS_NUMBCU 	 (20)//Э��������һȦ��ֹͣʱ��,��λ:��
#define TXSTOPTICKS_NWRST		 (20)//Э��������һȦ��ֹͣʱ��,��λ:��
#define TXSTOPTICKS_NWRESTART (20)//Э��������һȦ��ֹͣʱ��,��λ:��
#define TXSTOPTICKS_HEARTBEAT (20)//Э��������һȦ��ֹͣʱ��,��λ:��

//���յ��ı�Ŷ���
#define RXBCUNUM				(8)
#define _1_40					(0)//���ձ��,1~40
#define _1_512				(1)//���ձ��,1~512	
#define CNTMAX_1_40		(2)//���մ�������BCU���,1-40
#define CNTMAX_1_512	(3)//���մ�������BCU���,1-512
#define CNTMIN_1_40		(4)//���մ������ٵ�BCU���,1-40
#define CNTMIN_1_512	(5)//���մ������ٵ�BCU���,1-512
//add something here


/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/

/**
* @ö�ٹ���  Э�������ƽṹ��
*/
typedef enum
{
	CC2530PA2S_C1 =0x00,//Coordinator1
	CC2530PA2S_C2 =0x01,//Coordinator2
	CC2530PA2S_C3 =0x02	//Coordinator3
}CoordinatorX_TypeDef;

/**
* @ö�ٹ���  ECU2BCU Э��1000���Ĵ�������
*/
typedef enum
{
	REG1000_RESTEST   					=0x01,//�������
	REG1000_ALARM_ON   					=0x04,//�澯״̬д��
	REG1000_ALARM_OFF   				=0x08,//�澯״̬���
	REG1000_NWRSTONE   					=0x10,//����RͨѶ�쳣��λRST 1��ָ�
	REG1000_NWRSTALL   					=0x20,//C��������λR����5min����дC�ָ�

	REG1000_M2O_LOWSPEED   			=0x40,//R��C�����Ϸ�����15s
	REG1000_M2O_MEDIUMSPEED   	=0x80,//R��C�����Ϸ�����10s
	REG1000_M2O_HIGHSPEED  			=0xC0,//R��C�����Ϸ�����2s
	REG1000_M2O_SUPERFASTSPEED  =0x100,//R��C�����Ϸ�����1s
	REG1000_M2O_GODLIKESPEED    =0x101,//R��C�����Ϸ�����200ms
	REG1000_M2O_DEFAULTSPEED    =0x110,//R��C�����Ϸ�����5sĬ��ֵ
	REG1000_M2O_RSTBCU          =0x200,//��λAVR MCU
	REG1000_NUMNEXTBCU          =0x202 //�����һ��BCU
}REG1000_TypeDef;

/**
* @ö�ٹ��� many to one ��ʽ�£�Router��Coodinator��Ե��������͵�Ƶ��
            ������Ҫ��Ϊ����CC2530M2OSpeedCtrl�Ĳ���ʹ��
*/
typedef enum
{
	LOWSPEED_M2O					=0x00,					//���٣�15s
	MEDIUMSPEED_M2O				=0x01,					//���٣�10s
	HIGHSPEED_M2O					=0x02,					//���٣�2s
	SUPERFASTSPEED_M2O		=0x03,					//�����٣�1s
	GODLIKESPEED_M20			=0X04,					//�������ٶȣ�200ms
	DEFAULTSPEED_M2O			=0x05						//Ĭ���ٶȣ�5s	
}M2OSpeed_TypeDef;

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
* @ö�ٹ���  ECU��Э����C1,C2,C3���η���������Ϣ�ṹ��
*/
typedef struct
{
	uint8_t Mode;        //����ѯ֡�в�������֡ģʽ,�������1~��ؽ�����֡
	uint8_t BCUNum; 			//��ǰЭ�������õ���X��BCUģ�飬X��Χ1~MAXNUM_CORDINATOR������ǰ��ΧΪ1~40��
	uint8_t BCUNum_Last; //Ԥ����������һ��Э�������õ���X��BCUģ�飬X��Χ1~MAXNUM_CORDINATOR������ǰ��ΧΪ1~40��
	uint8_t Cplt;				//�������
	uint16_t BCUTime;    //���õ�ǰһ��BCU�����ĵ�ʱ��ɱ�,��λ:s
	//TODO
	// uint16_t NextNumTick;//���ʱ��
	// uint16_t NextNumEn;	//���ʹ�ܣ�����C�յ�������֡���Ա����һ��BCU��
	// uint8_t  NextNum;//��Ʊ��
}NumBCU_TypeDef;

/**
* @ö�ٹ���  Э������Ϣ�ṹ��
*/
typedef struct
{
	/**
	timer.h�ļ��ж���
	#define Period_WrReg1000_Defaul	(1000)//д1000�Ĵ�������,��λ��ms
	#define Period_NumBCU_Defaul	(1000)//���BCU����,��λ��ms
	#define Period_NWRst_Defaul	(1000)//��λR1s����,��λ��ms
	#define Period_NWRestart_Defaul	(1000)//��λR5min����,��λ��ms
	#define Period_HeartBeat_Defaul	(1000)//��������,��λ��ms
	#define Period_WriteNw_Default		(5000)//������������,��λ��ms
	#define Period_ReadNw_Default		(2000)//�����ѯ����,��λ��ms
	*******************************************************************
	
	Coordinator[0].txPeriod[POLLTASK_WRREG1000]=Period_WrReg1000_Defaul;
	**/
	uint16_t txPeriod[POLLTASK_NUM];//�㲥��������
	uint16_t txCnt[POLLTASK_NUM];		//C��ѯ�Ĵ���
	uint8_t  txBCUNum[POLLTASK_NUM];//���ͱ��,1~40
	uint16_t txStopTick[POLLTASK_NUM];//ֹͣ�������ʱ
	
	/**
	rxBCUNum[0]	:���ձ��,1~40
	rxBCUNum[1]	:���ձ��,1~512	
	rxBCUNum[2]	:���մ�������BCU���,1-40
	rxBCUNum[3]	:���մ�������BCU���,1-512
	rxBCUNum[4]	:���մ������ٵ�BCU���,1-40
	rxBCUNum[5]	:���մ������ٵ�BCU���,1-512
	
	rxCntNow[MAXROUTER_Default]		:40��R���մ�����ֵ��
	rxCntNow[MAXROUTER_Default+1]	:40��R���մ������ֵ
	rxCntNow[MAXROUTER_Default+2]	:40��R���մ�����Сֵ
	rxCntNow[MAXROUTER_Default+3]	:40��R���մ���Ϊ0�ĸ���
	**/
	uint16_t  rxBCUNum[RXBCUNUM];//���ձ��
	uint32_t rxCntNow[MAXROUTER_Default+4];		//��ǰ����Rn�Ĵ���
	uint32_t rxCntStatus[MAXROUTER_Default+4];		//��ǰ����Rn�Ĵ���

	uint32_t rxCntPre[MAXROUTER_Default];			//�ϴν���Rn�Ĵ���
	uint16_t rxCntErr[MAXROUTER_Default];			//��ǰ����Rn�Ĵ������ϴν���Rn������ƫ��
	uint16_t rxCntUnChange_Tick[MAXROUTER_Default];//��ǰ����Rn�Ĵ������ϴν���Rn������ƫ��������仯�ĳ���ʱ��
	uint16_t rxCntUnChange_TickPre[MAXROUTER_Default];//�ϴν���Rn�Ĵ������ϴν���Rn������ƫ��������仯�ĳ���ʱ��
  uint16_t R_Rate[MAXROUTER_Default];	 			//R�ĵð���
	uint16_t shortAdd[MAXROUTER_Default];			//���յ�Routerģ��Ķ̵�ַ����ϵͳ����
	uint16_t lossCnt[MAXROUTER_Default];			//ͨѶ���ϵĴ���
	NumBCU_TypeDef Cfg;												//����BCU���	
}Coordinator_TypeDef;

/**
* @�ṹ�幦��  BCUData�ṹ��
*/
typedef struct
{
	uint16_t U;			//�����ѹ(��λ��mV)
	uint16_t R;			//��������(��λ��u��)
	uint16_t T;			//����,�������¶�(��λ����)���ֽ��������ֽڸ�
	uint16_t S; 		//����״̬
	uint16_t RB;    	//���������׼(��λ��u��)
	uint16_t RES[3]; 	//Ԥ��
}BCUData_TypeDef;
/**
* @�ṹ�幦��  BCUDataУ׼�ṹ��
*/
typedef struct
{
	float kU;//��ѹУ׼ϵ��k,��λ: NULL
	float kR;//����У׼ϵ��k,��λ: NULL
	float kT1;//�����¶�У׼ϵ��k,��λ: NULL
	float bU;//��ѹУ׼ϵ��b,��λ: NULL
	float bR;//����У׼ϵ��b,��λ: NULL
	float bT1;//�����¶�У׼ϵ��b,��λ: NULL
}BCUCalib_TypeDef;

/**
 * @�ṹ�幦��  BCU�ṹ��
 */
typedef struct {
	uint16_t Num;					 //BCU���
	BCUData_TypeDef data;	 //BCU����
	BCUCalib_TypeDef calib;//BCU����У׼
} BCUInfo_TypeDef;


/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
COORDINATOR_EXT Coordinator_TypeDef Coordinator[3];
COORDINATOR_EXT BCUData_TypeDef BCUData[MAXBCU_Default];
COORDINATOR_EXT BCUInfo_TypeDef BCUInfo[MAXBCU_Default];
COORDINATOR_EXT uint8_t Cx;

COORDINATOR_EXT uint16_t numNextBcu_Tick;//���ʱ��
COORDINATOR_EXT uint16_t numNextBcu_En;	//���ʹ�ܣ�����C�յ�������֡���Ա����һ��BCU��
COORDINATOR_EXT uint8_t nextBCUNum;		//��Ʊ��
/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
COORDINATOR_EXT void vCoordinator_Init(void);
COORDINATOR_EXT void vBCUSlave_Proc(void);
COORDINATOR_EXT void vCommunicationFault_Proc(void);
COORDINATOR_EXT void vCC2530_RestTest(CC2530Cast_TypeDef castType);
COORDINATOR_EXT CC2530CmdRet_TypeDef eCC2530_NWInit(uint16_t ,uint16_t ,uint16_t );
COORDINATOR_EXT CC2530CmdRet_TypeDef eNwNum2PANID(uint16_t ,uint16_t ,uint16_t );
COORDINATOR_EXT CC2530CmdRet_TypeDef vCC2530_BaudInit(CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef );
#endif /* COORDINATOR_H_ */
