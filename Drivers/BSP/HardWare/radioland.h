/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: radioland.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/05		00:03:00
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
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
//CC2530 Reset硬件引脚定义


//CC2530 Reset上拉、下拉定义
//#define  C1_RST_PU()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //拉高RST
//#define  C1_RST_PD()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //拉低RST
//#define  C2_RST_PU()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //拉高RST
//#define  C2_RST_PD()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //拉低RST
//#define  C3_RST_PU()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //拉高RST
//#define  C3_RST_PD()      {HAL_GPIO_WritePin(B2_GPIO_Port,B2_Pin,GPIO_PIN_RESET);} //拉低RST

//CC2530 Reset是否下拉定义
//#define  IS_C1RST_PD    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)
//#define  IS_C2RST_PD    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)
//#define  IS_C3RST_PD    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)

/*MCU串口操作CC2530的命令头：前4个字节*/
#define CC2530CMD_HEAD_01	(0x02)
#define CC2530CMD_HEAD_02	(0xA8)
#define CC2530CMD_HEAD_03	(0x79)
#define CC2530CMD_HEAD_04	(0xC3)

/*01命令：查询入网状态*/
#define CC2530CMD_READ_NET_STATUS	(0x01)
/*02命令：设置查询数据时间间隔*/
#define CC2530CMD_WRITE_CHK_TIME	(0x02)
/*03命令：恢复出厂设置*/
#define CC2530CMD_RESET_FACTORY	(0x03)
/*04命令：修改模块PANID*/
#define CC2530CMD_WRITE_PANID	(0x04)
/*05命令：读取PANID及通信信道*/
#define CC2530CMD_READ_PANID	(0x05)
/*06命令：修改模块波特率*/
#define CC2530CMD_WRITE_BAUDRATE	(0x06)
/*07命令：进入低功耗状态*/
#define CC2530CMD_ENTER_LOWPOWER	(0x07)
/*08命令：设置寻找网络时间*/
#define CC2530CMD_WRITE_SEARCHTIME	(0x08)
/*09命令：修改通信信道*/
#define CC2530CMD_WRITE_COMMUNICATION_CHANNEL	(0x09)
/*0A命令：节点向协调器发送数据（自动附加短地址）*/
#define CC2530CMD_SENDDATA_2CORDINATOR	(0x0A)
/*0B命令：协调器向节点发送数据（需要附加短地址）*/
#define CC2530CMD_SENDDATA_2ROUTER_2ENDDEVICE	(0x0B)
/*0C命令：读取模块MAC地址*/
#define CC2530CMD_READ_MACADRR	(0x0C)
/*0D命令：设置用户自定义短地址*/
#define CC2530CMD_WRITE_SHORTADDR_USERDEF	(0x0D)
/*0E命令：读取用户自定义短地址*/
#define CC2530CMD_READ_SHORTADDR_USERDEF	(0x0E)
/*0F命令：用户自定义短地址点对点数据传输*/
#define CC2530CMD_SENDDATA_BY_SHORTADDR_USERDEF	(0x0F)

/*Coordinator的短地址*/
#define CC2530_SHORTADDR_COORDINATOR	(0x00)
/*Coordinator到Router自定义短地址点对点数据传输，命令头字节数*/
#define CC2530_HEADSIZE_C2R_USERNWADDR	(0x09)
/*Coordinator到Router系统分配短地址点对点数据传输，命令头字节数*/
#define CC2530_HEADSIZE_C2R_SYSNWADDR	(0x07)
/*按键编号短地址定义（按键编号时，对Router写此固定短地址,方便C也用此固定短地址点播编号信息*/
#define CC2530_NWADD_SETBCUID  (0x8888)

/*CC2530未入网定义:当前不存在协调器时，用02 A8 79 C3 05命令查询路由/终端会返回02 A8 79 C3 05 FE FF 00*/
#define CC2530RESULT_NOT_ADDIN_NETWORK1	(0xFE)
#define CC2530RESULT_NOT_ADDIN_NETWORK2	(0xFF)
#define CC2530RESULT_NOT_ADDIN_NETWORK3	(0x00)  

/*CC2530命令设置成功,错误*/
#define CC2530CMD_OK_0	(0x4F)//ASCII "O"
#define CC2530CMD_OK_1	(0x4B)//ASCII "K"
#define CC2530CMD_ERR_0	(0x45)//ASCII "E"
#define CC2530CMD_ERR_1	(0x52)//ASCII "R"

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/
/**
* @枚举功能  瑞迪莱CC2530(Vendor)短地址类型
*/
typedef enum
{
	NWADD_USERDEF   				 =0x00,	//用户自定义的短地址
	NWADD_SYSALLOC   			 	 =0x01	//系统分配的短地址
}CC2530NWADD_TypeDef;
/**
* @枚举功能  CC2530串口操作成功与否状态结构体
*/
typedef enum
{
	CC2530CMD_OK       = 0x00,	//设置成功
	CC2530CMD_ERROR    = 0x01		//设置失败
}CC2530CmdRet_TypeDef;

/**
* @枚举功能  CC2530入网状态结构体
*/
typedef enum
{
	CC2530NETWORK_ERROR						=0x02,			//设备没有加入网络
	CC2530NETWORK_ENDDEVICE_OK		=0x06,			//End Device已经入网
	CC2530NETWORK_ROUTER_OK				=0x07,			//Router已经入网
	CC2530NETWORK_CORDINATOR_OK		=0x09				//Cordinator已经入网
}CC2530NetWorkStatus_TypeDef;

/**
* @枚举功能 CC2530通讯信道状态结构体
*/
typedef enum {
	CC2530CHANNEL_0B				=0x0B,				//0B信道,2405MHZ
	CC2530CHANNEL_0C				=0x0C,				//0C信道,2410MHZ
	CC2530CHANNEL_0D				=0x0D,				//0D信道,2415MHZ
	CC2530CHANNEL_0E				=0x0E,				//0E信道,2420MHZ
	CC2530CHANNEL_0F				=0x0F,				//0F信道,2425MHZ
	CC2530CHANNEL_10				=0x10,				//10信道,2430MHZ
	CC2530CHANNEL_11				=0x11,				//11信道,2435MHZ
	CC2530CHANNEL_12				=0x12,				//12信道,2440MHZ
	CC2530CHANNEL_13				=0x13,				//13信道,2445MHZ
	CC2530CHANNEL_14				=0x14,				//14信道,2450MHZ
	CC2530CHANNEL_15				=0x15,				//15信道,2455MHZ
	CC2530CHANNEL_16				=0x16,				//16信道,2460MHZ
	CC2530CHANNEL_17				=0x17,				//17信道,2465MHZ
	CC2530CHANNEL_18				=0x18,				//18信道,2470MHZ
	CC2530CHANNEL_19				=0x19,				//19信道,2475MHZ
	CC2530CHANNEL_1A				=0x1A					//1A信道,2480MHZ
} CC2530Channel_TypeDef;
/**
* @枚举功能 CC2530波特率结构体
*/
typedef enum {
	CC2530BAUDRATE_9600				=0x00,				//9600
	CC2530BAUDRATE_19200			=0x01,				//19200
	CC2530BAUDRATE_38400			=0x02,				//38400
	CC2530BAUDRATE_57600			=0x03,				//57600
	CC2530BAUDRATE_115200			=0x04					//115200
} CC2530BaudRate_TypeDef;

/**
 * @枚举功能  CC2530发送数据方式
 */
typedef enum {
	SingleCast=0x00,//点播
	BroadCast=0x01//广播
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
//CC2530瑞迪莱芯片操作命令
RADIOLAND_EXT CC2530NetWorkStatus_TypeDef eCC2530CMD_ReadNetStatus_01(UART_HandleTypeDef *huart);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_WriteChkTime_02(UART_HandleTypeDef *huart, uint16_t checkTime);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_Rst_03(UART_HandleTypeDef *huart);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_SetPANID_04(UART_HandleTypeDef *huart,uint16_t panid);
RADIOLAND_EXT uint16_t ulCC2530CMD_GetPANID_05(UART_HandleTypeDef *huart);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_WriteBaudRate_06(UART_HandleTypeDef *huart,CC2530BaudRate_TypeDef CC2530BaudRate_XX);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_SetChannel_09(UART_HandleTypeDef *huart,uint8_t channel);
RADIOLAND_EXT CC2530CmdRet_TypeDef eCC2530CMD_SendData2Router_0B(UART_HandleTypeDef *huart, uint16_t shorAdd, uint8_t *sendBuff);

#endif /* RADIOLAND_H_ */
