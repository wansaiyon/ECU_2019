/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: radioland.h
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/05		00:03:00
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#ifndef RADIOLAND_H_
#define	RADIOLAND_H_

#ifdef RADIOLAND_GLOBALS
#define RADIOLAND_EXT
#else
#define  RADIOLAND_EXT extern
#endif

#include "include.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
//CC2530 ResetӲ�����Ŷ���


//CC2530 Reset��������������
//#define  C1_RST_PU()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //����RST
//#define  C1_RST_PD()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //����RST
//#define  C2_RST_PU()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //����RST
//#define  C2_RST_PD()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //����RST
//#define  C3_RST_PU()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //����RST
//#define  C3_RST_PD()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //����RST

//CC2530 Reset�Ƿ���������
//#define  IS_C1RST_PD    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)
//#define  IS_C2RST_PD    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)
//#define  IS_C3RST_PD    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)

/*MCU���ڲ���CC2530������ͷ��ǰ4���ֽ�*/
#define CC2530CMD_HEAD_01	(0x02)
#define CC2530CMD_HEAD_02	(0xA8)
#define CC2530CMD_HEAD_03	(0x79)
#define CC2530CMD_HEAD_04	(0xC3)

/*01�����ѯ����״̬*/
#define CC2530CMD_READ_NET_STATUS	(0x01)
/*02������ò�ѯ����ʱ����*/
#define CC2530CMD_WRITE_CHK_TIME	(0x02)
/*03����ָ���������*/
#define CC2530CMD_RESET_FACTORY	(0x03)
/*04����޸�ģ��PANID*/
#define CC2530CMD_WRITE_PANID	(0x04)
/*05�����ȡPANID��ͨ���ŵ�*/
#define CC2530CMD_READ_PANID	(0x05)
/*06����޸�ģ�鲨����*/
#define CC2530CMD_WRITE_BAUDRATE	(0x06)
/*07�������͹���״̬*/
#define CC2530CMD_ENTER_LOWPOWER	(0x07)
/*08�������Ѱ������ʱ��*/
#define CC2530CMD_WRITE_SEARCHTIME	(0x08)
/*09����޸�ͨ���ŵ�*/
#define CC2530CMD_WRITE_COMMUNICATION_CHANNEL	(0x09)
/*0A����ڵ���Э�����������ݣ��Զ����Ӷ̵�ַ��*/
#define CC2530CMD_SENDDATA_2CORDINATOR	(0x0A)
/*0B���Э������ڵ㷢�����ݣ���Ҫ���Ӷ̵�ַ��*/
#define CC2530CMD_SENDDATA_2ROUTER_2ENDDEVICE	(0x0B)
/*0C�����ȡģ��MAC��ַ*/
#define CC2530CMD_READ_MACADRR	(0x0C)
/*0D��������û��Զ���̵�ַ*/
#define CC2530CMD_WRITE_SHORTADDR_USERDEF	(0x0D)
/*0E�����ȡ�û��Զ���̵�ַ*/
#define CC2530CMD_READ_SHORTADDR_USERDEF	(0x0E)
/*0F����û��Զ���̵�ַ��Ե����ݴ���*/
#define CC2530CMD_SENDDATA_BY_SHORTADDR_USERDEF	(0x0F)

/*Coordinator�Ķ̵�ַ*/
#define CC2530_SHORTADDR_COORDINATOR	(0x00)
/*Coordinator��Router�Զ���̵�ַ��Ե����ݴ��䣬����ͷ�ֽ���*/
#define CC2530_HEADSIZE_C2R_USERNWADDR	(0x09)
/*Coordinator��Routerϵͳ����̵�ַ��Ե����ݴ��䣬����ͷ�ֽ���*/
#define CC2530_HEADSIZE_C2R_SYSNWADDR	(0x07)
/*������Ŷ̵�ַ���壨�������ʱ����Routerд�˹̶��̵�ַ,����CҲ�ô˹̶��̵�ַ�㲥�����Ϣ*/
#define CC2530_NWADD_SETBCUID  (0x8888)

/*CC2530δ��������:��ǰ������Э����ʱ����02 A8 79 C3 05�����ѯ·��/�ն˻᷵��02 A8 79 C3 05 FE FF 00*/
#define CC2530RESULT_NOT_ADDIN_NETWORK1	(0xFE)
#define CC2530RESULT_NOT_ADDIN_NETWORK2	(0xFF)
#define CC2530RESULT_NOT_ADDIN_NETWORK3	(0x00)  

/*CC2530�������óɹ�,����*/
#define CC2530CMD_OK_0	(0x4F)//ASCII "O"
#define CC2530CMD_OK_1	(0x4B)//ASCII "K"
#define CC2530CMD_ERR_0	(0x45)//ASCII "E"
#define CC2530CMD_ERR_1	(0x52)//ASCII "R"

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/
/**
* @ö�ٹ���  �����CC2530(Vendor)�̵�ַ����
*/
typedef enum
{
	NWADD_USERDEF   				 =0x00,	//�û��Զ���Ķ̵�ַ
	NWADD_SYSALLOC   			 	 =0x01	//ϵͳ����Ķ̵�ַ
}CC2530NWADD_TypeDef;
/**
* @ö�ٹ���  CC2530���ڲ����ɹ����״̬�ṹ��
*/
typedef enum
{
	CC2530CMD_OK       = 0x00,	//���óɹ�
	CC2530CMD_ERROR    = 0x01		//����ʧ��
}CC2530CmdRet_TypeDef;

/**
* @ö�ٹ���  CC2530����״̬�ṹ��
*/
typedef enum
{
	CC2530NETWORK_ERROR						=0x02,			//�豸û�м�������
	CC2530NETWORK_ENDDEVICE_OK		=0x06,			//End Device�Ѿ�����
	CC2530NETWORK_ROUTER_OK				=0x07,			//Router�Ѿ�����
	CC2530NETWORK_CORDINATOR_OK		=0x09				//Cordinator�Ѿ�����
}CC2530NetWorkStatus_TypeDef;

/**
* @ö�ٹ��� CC2530ͨѶ�ŵ�״̬�ṹ��
*/
typedef enum {
	CC2530CHANNEL_0B				=0x0B,				//0B�ŵ�,2405MHZ
	CC2530CHANNEL_0C				=0x0C,				//0C�ŵ�,2410MHZ
	CC2530CHANNEL_0D				=0x0D,				//0D�ŵ�,2415MHZ
	CC2530CHANNEL_0E				=0x0E,				//0E�ŵ�,2420MHZ
	CC2530CHANNEL_0F				=0x0F,				//0F�ŵ�,2425MHZ
	CC2530CHANNEL_10				=0x10,				//10�ŵ�,2430MHZ
	CC2530CHANNEL_11				=0x11,				//11�ŵ�,2435MHZ
	CC2530CHANNEL_12				=0x12,				//12�ŵ�,2440MHZ
	CC2530CHANNEL_13				=0x13,				//13�ŵ�,2445MHZ
	CC2530CHANNEL_14				=0x14,				//14�ŵ�,2450MHZ
	CC2530CHANNEL_15				=0x15,				//15�ŵ�,2455MHZ
	CC2530CHANNEL_16				=0x16,				//16�ŵ�,2460MHZ
	CC2530CHANNEL_17				=0x17,				//17�ŵ�,2465MHZ
	CC2530CHANNEL_18				=0x18,				//18�ŵ�,2470MHZ
	CC2530CHANNEL_19				=0x19,				//19�ŵ�,2475MHZ
	CC2530CHANNEL_1A				=0x1A					//1A�ŵ�,2480MHZ
} CC2530Channel_TypeDef;
/**
* @ö�ٹ��� CC2530�����ʽṹ��
*/
typedef enum {
	CC2530BAUDRATE_9600				=0x00,				//9600
	CC2530BAUDRATE_19200			=0x01,				//19200
	CC2530BAUDRATE_38400			=0x02,				//38400
	CC2530BAUDRATE_57600			=0x03,				//57600
	CC2530BAUDRATE_115200			=0x04					//115200
} CC2530BaudRate_TypeDef;

/**
 * @ö�ٹ���  CC2530�������ݷ�ʽ
 */
typedef enum {
	SingleCast=0x00,//�㲥
	BroadCast=0x01//�㲥
} CC2530Cast_TypeDef;
/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/


/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
//CC2530�����оƬ��������
RADIOLAND_EXT CC2530NetWorkStatus_TypeDef eCC2530CMD_ReadNetStatus_01(UART_HandleTypeDef *huart);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_WriteChkTime_02(UART_HandleTypeDef *huart, uint16_t checkTime);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_Rst_03(UART_HandleTypeDef *huart);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_SetPANID_04(UART_HandleTypeDef *huart,uint16_t panid);
RADIOLAND_EXT uint16_t ulCC2530CMD_GetPANID_05(UART_HandleTypeDef *huart);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_WriteBaudRate_06(UART_HandleTypeDef *huart,CC2530BaudRate_TypeDef CC2530BaudRate_XX);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_SetChannel_09(UART_HandleTypeDef *huart,uint8_t channel);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_SendData2Router_0B(UART_HandleTypeDef *huart, uint16_t shorAdd, uint8_t *sendBuff);

#endif /* RADIOLAND_H_ */
