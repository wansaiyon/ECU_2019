/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: radioland.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/05		00:03:27
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define RADIOLAND_GLOBALS
#include "Include.h"


/**********************************************************************************/
/*      私有变量声明              	                                		      */
/**********************************************************************************/



/**********************************************************************************/
/*      私有函数声明              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      私有函数实现              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      公有函数实现	             	                                              */
/**********************************************************************************/
CC2530NetWorkStatus_TypeDef eCC2530CMD_ReadNetStatus_01(UART_HandleTypeDef *huart)
{
	CC2530NetWorkStatus_TypeDef nwStatus = CC2530NETWORK_CORDINATOR_OK;
	uint8_t cmd[5];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_READ_NET_STATUS;
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	return nwStatus;
}
CC2530CmdRet_TypeDef eCC2530CMD_WriteChkTime_02(UART_HandleTypeDef *huart, uint16_t checkTime)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	uint8_t cmd[7];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_WRITE_CHK_TIME;
	cmd[5]=checkTime>>8;
	cmd[6]=checkTime;
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	return cc2530CmdRet;
}
CC2530CmdRet_TypeDef eCC2530CMD_Rst_03(UART_HandleTypeDef *huart)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	uint8_t cmd[5];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_RESET_FACTORY;
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	return cc2530CmdRet;
}
CC2530CmdRet_TypeDef eCC2530CMD_SetPANID_04(UART_HandleTypeDef *huart,uint16_t panid)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	uint8_t cmd[7];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_WRITE_PANID;
	cmd[5]=panid>>8;
	cmd[6]=panid;	
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	return cc2530CmdRet;
}
uint16_t ulCC2530CMD_GetPANID_05(UART_HandleTypeDef *huart)
{
	uint8_t cmd[5];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_READ_PANID;
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	return 1;
}
CC2530CmdRet_TypeDef eCC2530CMD_WriteBaudRate_06(UART_HandleTypeDef *huart,CC2530BaudRate_TypeDef CC2530BaudRate_XX)
{	
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	uint8_t cmd[6];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_WRITE_BAUDRATE;
	cmd[5]=CC2530BaudRate_XX;
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	return cc2530CmdRet;
}
CC2530CmdRet_TypeDef eCC2530CMD_SetChannel_09(UART_HandleTypeDef *huart,uint8_t channel)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	uint8_t cmd[6];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_WRITE_COMMUNICATION_CHANNEL;
	cmd[5]=channel;
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	return cc2530CmdRet;
}
CC2530CmdRet_TypeDef eCC2530CMD_SendData2Router_0B(UART_HandleTypeDef *huart, uint16_t shorAdd, uint8_t *sendBuff)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	uint8_t cmd[7];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_SENDDATA_2ROUTER_2ENDDEVICE;
	cmd[5]=shorAdd>>8;
	cmd[6]=(uint8_t)shorAdd;
	HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
	//todo:crc
	HAL_UART_Transmit(huart,sendBuff,sizeof(sendBuff),TimeOut_PC);
	return cc2530CmdRet;
}



/*****************************************End of radioland.c*****************************************/
