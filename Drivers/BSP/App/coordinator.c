/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: coordinator.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/02		04:39:53
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define COORDINATOR_GLOBALS
//#include "Include.h"
#include "coordinator.h"


/**********************************************************************************/
/*      私有变量声明              	                                		      */
/**********************************************************************************/


/**********************************************************************************/
/*      私有函数声明              	                                              */
/**********************************************************************************/

static void vCC2530_ErrorHandle(void);
static CC2530CmdRet_TypeDef eCC2530Cmd_CmdHeadCheck(uint8_t *,uint8_t *,uint8_t);
//TODO
static CC2530BaudRate_TypeDef eCC2530_BaudFind(UART_HandleTypeDef *);
static CC2530CmdRet_TypeDef eCC2530_BaudInit0(CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef );

//CC2530给BCU编号
static void vCC2530_NumBCU(CC2530Cast_TypeDef castType);
static void vHAL_NumBCU(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//CC2530给BCU心跳同步信号
static void vCC2530_HeartBeat(CC2530Cast_TypeDef castType);
static void vHAL_HeartBeat(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//CC2530内阻测试

//CC2530点播BCU复位
static void vCC2530_NWRst(CC2530Cast_TypeDef castType);
static void vHAL_NWRst(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//CC2530网络重启
static void vCC2530_NWRestart(CC2530Cast_TypeDef castType);
static void vHAL_NWRestart(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//写1000寄存器地址
//static void HAL_WriteReg1000(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx,REG1000_TypeDef reg1000Type,CC2530NWADD_TypeDef nwAddType);
void vHAL_WriteReg1000(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx,REG1000_TypeDef reg1000Type,CC2530NWADD_TypeDef nwAddType);



//CC2530发送,接收数据处理
//static void CoordinatorTx_Proc(void);
//static void CoordinatorRx_Proc(UsartxDMARx_TypeDef *hRx);
void vCoordinatorTx_Proc(void);
void vCoordinatorRx_Proc(UsartxDMARx_TypeDef *hRx);

//modbus协议接收处理
static void vSlaveReadCmd0x03( UsartxDMARx_TypeDef *hRx );
static void vSlaveReadCmd0x10( UsartxDMARx_TypeDef *hRx );
//radioland CC2530命令是否设置成功接收处理
static void vCC2530CmdRet_Proc( UsartxDMARx_TypeDef *hRx );

#if defined(CC2530TEST_UPDOWNRATE)
//无线通信数据统计
static void vTestDemo_CC2530UpDwRate( void );
#endif
/**********************************************************************************/
/*      私有函数实现              	                                              */
/**********************************************************************************/

static void vCC2530_ErrorHandle(void)
{
	printf("\r\nCC2530 Init Err!\r\n");
}

static CC2530CmdRet_TypeDef eCC2530Cmd_CmdHeadCheck(uint8_t *cmd,uint8_t *retVal,uint8_t size)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	do 
	{		
		if (*cmd++ == *retVal++)
		{
			;//Do Nothing
		}
		else 
		{
			cc2530CmdRet=CC2530CMD_ERROR;
			break;
		}
	} while (--size);
	return cc2530CmdRet;	
}
/******************************************************************************
* @函数名称：CC2530_BaudFind
* @函数功能：
* @输入参数：
*
* @输出参数：void
* @算法思路：
						串口初始化为38400;
            若01入网查询命令有返回，说明coordinator的波特率为38400,打印入网信息
						否则coordinator的波特率为9600，MCU串口初始为9600，打印入网信息
* @被调用的函数：
* @使用资源：
* @注意事项：
******************************************************************************/
static CC2530BaudRate_TypeDef eCC2530_BaudFind(UART_HandleTypeDef *huart)
{
	CC2530BaudRate_TypeDef cc2530BaudRate = CC2530BAUDRATE_38400;
	uint8_t cmd[5];
	uint8_t retVal[6];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_READ_NET_STATUS;
//	USART_UART_Init(&huart2,38400);
	HAL_UART_Transmit(&huart2,cmd,sizeof(cmd),TimeOut_PC);
	HAL_UART_Receive(&huart2,retVal,sizeof(retVal),TimeOut_PC);
	
	if (CC2530CMD_OK==eCC2530Cmd_CmdHeadCheck(cmd,retVal,5))
	{
			switch (retVal[5])
			{
				case CC2530NETWORK_ERROR:
					printf("设备没有加入网络");
				break;
				case CC2530NETWORK_ENDDEVICE_OK:
					printf("End Device已经入网");
				break;
				case CC2530NETWORK_ROUTER_OK:
					printf("Router已经入网");
				break;
				case CC2530NETWORK_CORDINATOR_OK:
					printf("Cordinator已经入网");
				break;
				default:
				break;
			}
	}
	else
	{
		cc2530BaudRate = CC2530BAUDRATE_9600;
//		USART_UART_Init(huart,9600);
		HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
		HAL_UART_Receive(huart,retVal,sizeof(retVal),TimeOut_PC);
		if (CC2530CMD_OK==eCC2530Cmd_CmdHeadCheck(cmd,retVal,5))
		{
			switch (retVal[5])
			{
				case CC2530NETWORK_ERROR:
					printf("设备没有加入网络");
				break;
				case CC2530NETWORK_ENDDEVICE_OK:
					printf("End Device已经入网");
				break;
				case CC2530NETWORK_ROUTER_OK:
					printf("Router已经入网");
				break;
				case CC2530NETWORK_CORDINATOR_OK:
					printf("Cordinator已经入网");
				break;
				default:
				break;
			}
		}
	}
	return cc2530BaudRate;
}

/******************************************************************************
* @函数名称：CC2530_BaudInit0
* @函数功能：
* @输入参数：
*						cc2530Baud：波特率
* @输出参数：void
* @算法思路：
						读取Coordinator的波特率，若与输入参数相等，直接返回
            若不相等，则按cc2530 06命令重新设置一下
* @被调用的函数：
* @使用资源：
* @注意事项：
******************************************************************************/
static CC2530CmdRet_TypeDef eCC2530_BaudInit0(CC2530BaudRate_TypeDef cc2530Baud_C1,CC2530BaudRate_TypeDef cc2530Baud_C2,CC2530BaudRate_TypeDef cc2530Baud_C3)
{
	UNUSED(eCC2530_BaudInit0);// TODO :Call it
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	CC2530BaudRate_TypeDef cc2530BaudRate;
	uint8_t cmd[6];
	uint8_t retVal[7];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;
	cmd[4]=CC2530CMD_WRITE_BAUDRATE;		
	
	//读取C1波特率	
	cmd[5]=cc2530Baud_C1;
	cc2530BaudRate = eCC2530_BaudFind(&huart2);
	
	if(cc2530BaudRate ==cc2530Baud_C1)
	{
		printf("\r\nCC2530_BaudInit() C1: OK,初始化为:%0x\r\n",cc2530BaudRate);
	}
	else
	{
		if(cc2530Baud_C1==CC2530BAUDRATE_9600)
		{
//			USART2_UART_Init(9600);
		}
		else if(cc2530Baud_C1==CC2530BAUDRATE_38400)
		{
//			USART2_UART_Init(38400);
		}
		HAL_UART_Transmit(&huart2,cmd,sizeof(cmd),TimeOut_PC);
		HAL_UART_Receive(&huart2,retVal,sizeof(retVal),TimeOut_PC);
		if (CC2530CMD_OK==eCC2530Cmd_CmdHeadCheck(cmd,retVal,5))
		{
			if ((retVal[5]!=CC2530CMD_OK_0)&&(retVal[6]!=CC2530CMD_OK_1))
			{
				cc2530CmdRet = CC2530CMD_ERROR;
				printf("\r\nCC2530_BaudInit() C1: Err\r\n");
			}
			else
				printf("\r\nCC2530_BaudInit() C1: OK,初始化为:%0x\r\n",cc2530BaudRate);
		}
		else
		{
			cc2530CmdRet = CC2530CMD_ERROR;
			printf("\r\nCC2530_BaudInit() C1: Err\r\n");//理论上应该是不会跑到这个分支的
		}
	}
	
	//读取C2波特率	
	cmd[5]=cc2530Baud_C2;
	cc2530BaudRate = eCC2530_BaudFind(&huart3);
	
	if(cc2530BaudRate ==cc2530Baud_C2)
	{
		printf("\r\nCC2530_BaudInit() C2: OK,初始化为:%0x\r\n",cc2530BaudRate);
	}
	else
	{
		if(cc2530Baud_C2==CC2530BAUDRATE_9600)
		{
//			USART3_UART_Init(9600);
		}
		else if(cc2530Baud_C2==CC2530BAUDRATE_38400)
		{
//			USART3_UART_Init(38400);
		}
		HAL_UART_Transmit(&huart3,cmd,sizeof(cmd),TimeOut_PC);
		HAL_UART_Receive(&huart3,retVal,sizeof(retVal),TimeOut_PC);
		if (CC2530CMD_OK==eCC2530Cmd_CmdHeadCheck(cmd,retVal,5))
		{
			if ((retVal[5]!=CC2530CMD_OK_0)&&(retVal[6]!=CC2530CMD_OK_1))
			{
				cc2530CmdRet = CC2530CMD_ERROR;
				printf("\r\nCC2530_BaudInit() C2: Err\r\n");
			}
			else
				printf("\r\nCC2530_BaudInit() C2: OK,初始化为:%0x\r\n",cc2530BaudRate);
		}
		else
		{
			cc2530CmdRet = CC2530CMD_ERROR;
			printf("\r\nCC2530_BaudInit() C2: Err\r\n");//理论上应该是不会跑到这个分支的
		}
	}
	
	//读取C3波特率	
	cmd[5]=cc2530Baud_C3;
	cc2530BaudRate = eCC2530_BaudFind(&huart6);
	
	if(cc2530BaudRate ==cc2530Baud_C3)
	{
		printf("\r\nCC2530_BaudInit() C3: OK,初始化为:%0x\r\n",cc2530BaudRate);
	}
	else
	{
		if(cc2530Baud_C3==CC2530BAUDRATE_9600)
		{
//			USART6_UART_Init(9600);
		}
		else if(cc2530Baud_C3==CC2530BAUDRATE_38400)
		{
//			USART6_UART_Init(38400);
		}
		HAL_UART_Transmit(&huart6,cmd,sizeof(cmd),TimeOut_PC);
		HAL_UART_Receive(&huart6,retVal,sizeof(retVal),TimeOut_PC);
		if (CC2530CMD_OK==eCC2530Cmd_CmdHeadCheck(cmd,retVal,5))
		{
			if ((retVal[5]!=CC2530CMD_OK_0)&&(retVal[6]!=CC2530CMD_OK_1))
			{
				cc2530CmdRet = CC2530CMD_ERROR;
				printf("\r\nCC2530_BaudInit() C3: Err\r\n");
			}
			else
				printf("\r\nCC2530_BaudInit() C3: OK,初始化为:%0x\r\n",cc2530BaudRate);
		}
		else
		{
			cc2530CmdRet = CC2530CMD_ERROR;
			printf("\r\nCC2530_BaudInit() C3: Err\r\n");//理论上应该是不会跑到这个分支的
		}
	}
	return cc2530CmdRet;	
}


//CC2530给BCU编号
static void vCC2530_NumBCU(CC2530Cast_TypeDef castType)
{
	UNUSED(vCC2530_NumBCU);// TODO :Call it
	if(tagTime_NumBCU)
	{
		tagTime_NumBCU=0;
		
	}
}
static void vHAL_NumBCU(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx)
{
	UNUSED(vHAL_NumBCU);// TODO :Call it
}
//CC2530给BCU心跳同步信号
static void vCC2530_HeartBeat(CC2530Cast_TypeDef castType)
{
	UNUSED(vCC2530_HeartBeat);// TODO :Call it
	if(tagTime_HeatBeat)
	{
		tagTime_HeatBeat=0;
		switch ((ECUInfo.battJarNum-1)/MAXROUTER_Default)
		{
			case 0:
				vHAL_HeartBeat(&huart2,CC2530PA2S_C1);
				break;
			case 1:
				vHAL_HeartBeat(&huart2,CC2530PA2S_C1);
				vHAL_HeartBeat(&huart3,CC2530PA2S_C2);
				break;
			case 2:
				vHAL_HeartBeat(&huart2,CC2530PA2S_C1);
				vHAL_HeartBeat(&huart3,CC2530PA2S_C2);
				vHAL_HeartBeat(&huart6,CC2530PA2S_C3);
				break;
			default:
						break;
		}
	}
}
static void vHAL_HeartBeat(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx)
{	
	uint8_t cmd[20];
	uint16_t tempcrc;
	if( Coordinator[cx].txStopTick[POLLTASK_HEARTBEAT]==0)
	{
		//HeadFrame
		cmd[0]=CC2530CMD_HEAD_01;
		cmd[1]=CC2530CMD_HEAD_02;													
		cmd[2]=CC2530CMD_HEAD_03;							
		cmd[3]=CC2530CMD_HEAD_04;	
		cmd[4]=CC2530CMD_SENDDATA_BY_SHORTADDR_USERDEF;												
		cmd[5]=(Coordinator[cx].txBCUNum[POLLTASK_HEARTBEAT]*8)/256;
		cmd[6]=(Coordinator[cx].txBCUNum[POLLTASK_HEARTBEAT]*8)%256;
		cmd[7]=CC2530_SHORTADDR_COORDINATOR;
		cmd[8]=CC2530_SHORTADDR_COORDINATOR;
		//DataFrame
		cmd[9]=(ECUInfo.slaveID&0x08);	
		cmd[10]=0x41;											
		cmd[11]=cmd[5];	
		cmd[12]=cmd[6];	
		cmd[13]=0x00;			
		cmd[14]=0x04;
		tempcrc= usMBCRC16(&cmd[9],0x06);
		cmd[15] = (uint8_t)(tempcrc);
		cmd[16] = (uint8_t)(tempcrc>>8);
		//Transmit		
		HAL_UART_Transmit(huart,cmd,sizeof(cmd),TimeOut_PC);
		Coordinator[cx].txBCUNum[POLLTASK_HEARTBEAT]++;
	}
	if(Coordinator[cx].txBCUNum[POLLTASK_HEARTBEAT]>(ECUInfo.battJarNum-cx*MAXBCU_Default))
	{
		Coordinator[cx].txStopTick[POLLTASK_HEARTBEAT]++;
		if( Coordinator[cx].txStopTick[POLLTASK_HEARTBEAT] > TXSTOPTICKS_HEARTBEAT)
		{
			Coordinator[cx].txStopTick[POLLTASK_HEARTBEAT] = 0;
			Coordinator[cx].txBCUNum[POLLTASK_HEARTBEAT] = 1;
			Coordinator[cx].txCnt[POLLTASK_HEARTBEAT]++;
		}
	}
}
//CC2530内阻测试
void vCC2530_RestTest(CC2530Cast_TypeDef castType)
{
	UNUSED(vCC2530_RestTest);// TODO :Call it
	CC2530NWADD_TypeDef nwAddType=NWADD_USERDEF;
	if(tagTime_ResTest)
	{
		tagTime_ResTest=0;
		switch ((ECUInfo.battJarNum-1)/MAXROUTER_Default)
		{
			case 0:
				vHAL_WriteReg1000(&huart2,CC2530PA2S_C1,REG1000_RESTEST,nwAddType);
				break;
			case 1:
				vHAL_WriteReg1000(&huart2,CC2530PA2S_C1,REG1000_RESTEST,nwAddType);
				vHAL_WriteReg1000(&huart3,CC2530PA2S_C2,REG1000_RESTEST,nwAddType);
				break;
			case 2:
				vHAL_WriteReg1000(&huart2,CC2530PA2S_C1,REG1000_RESTEST,nwAddType);
				vHAL_WriteReg1000(&huart3,CC2530PA2S_C2,REG1000_RESTEST,nwAddType);
				vHAL_WriteReg1000(&huart6,CC2530PA2S_C3,REG1000_RESTEST,nwAddType);
				break;
			default:
				break;
		}
	}
}

//CC2530点播BCU复位
static void vCC2530_NWRst(CC2530Cast_TypeDef castType)
{
	UNUSED(vCC2530_NWRst);// TODO :Call it
	if(tagTime_NWRst)
	{
		tagTime_NWRst=0;
	}
}
static void vHAL_NWRst(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx)
{
	UNUSED(vHAL_NWRst);// TODO :Call it
}
//CC2530网络重启
static void vCC2530_NWRestart(CC2530Cast_TypeDef castType)
{
	UNUSED(vCC2530_NWRestart);// TODO :Call it
	if(tagTime_NWRestart)
	{
		tagTime_NWRestart=0;
	}
}
static void vHAL_NWRestart(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx)
{
	UNUSED(vHAL_NWRestart);// TODO :Call it
}

void vHAL_WriteReg1000(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx,REG1000_TypeDef reg1000Type,CC2530NWADD_TypeDef nwAddType)
{	
	uint8_t cmd[50];
	uint16_t tempcrc =0x00;
	uint8_t op_msb =(uint8_t)(reg1000Type>>8);
	uint8_t op_lsb =(uint8_t)(reg1000Type);
	uint8_t bias=0x00;
	
	if( Coordinator[cx].txStopTick[POLLTASK_WRREG1000]==0)
	{
		//Header Frame
		cmd[0]=CC2530CMD_HEAD_01;
		cmd[1]=CC2530CMD_HEAD_02;													
		cmd[2]=CC2530CMD_HEAD_03;							
		cmd[3]=CC2530CMD_HEAD_04;	
		if(nwAddType == NWADD_USERDEF)
		{
			bias = 0x09;
			cmd[4]=CC2530CMD_SENDDATA_BY_SHORTADDR_USERDEF;												
			cmd[5]=(Coordinator[cx].txBCUNum[POLLTASK_WRREG1000]*8)/256;
			cmd[6]=(Coordinator[cx].txBCUNum[POLLTASK_WRREG1000]*8)%256;
			cmd[7]=CC2530_SHORTADDR_COORDINATOR;
			cmd[8]=CC2530_SHORTADDR_COORDINATOR;
		}
		else if(nwAddType == NWADD_SYSALLOC)
		{
			bias = 0x07;
			cmd[4]=CC2530CMD_SENDDATA_2ROUTER_2ENDDEVICE;		
			cmd[5]=Coordinator[cx].shortAdd[Coordinator[cx].txBCUNum[POLLTASK_WRREG1000]]>>8;		
			cmd[6]=(uint8_t)Coordinator[cx].shortAdd[Coordinator[cx].txBCUNum[POLLTASK_WRREG1000]];	
		}
		//Data Frame
		cmd[0+bias]=ECUInfo.slaveID;				
		cmd[1+bias]=0x42;											
		cmd[2+bias]=0x10;											
		cmd[3+bias]=Coordinator[cx].txBCUNum[POLLTASK_WRREG1000]-1;								
		cmd[4+bias]=0x00;											
		cmd[5+bias]=0x01;											
		cmd[6+bias]=0x02;											
		cmd[7+bias]=op_msb;										
		cmd[8+bias]=op_lsb;										
		tempcrc= usMBCRC16(&cmd[0+bias],0x09);
		cmd[9+bias] = (uint8_t)(tempcrc);
		cmd[10+bias] = (uint8_t)(tempcrc>>8);
		
		//Transmit		
		HAL_UART_Transmit(huart,cmd,11+bias,TimeOut_PC);

		Coordinator[cx].txBCUNum[POLLTASK_WRREG1000]++;
//		printf("\r\n点播发送的序号:%d\r\n",Coordinator[2].txBCUNum[POLLTASK_WRREG1000]);
	}
	if(Coordinator[cx].txBCUNum[POLLTASK_WRREG1000]>(MAXROUTER_Test(BCUNUM_Test)))//TODO
	{
		Coordinator[cx].txStopTick[POLLTASK_WRREG1000]++;
		if( Coordinator[cx].txStopTick[POLLTASK_WRREG1000] > TXSTOPTICKS_WRREG1000)
		{
			Coordinator[cx].txStopTick[POLLTASK_WRREG1000] = 0;
			Coordinator[cx].txBCUNum[POLLTASK_WRREG1000] = 1;
			Coordinator[cx].txCnt[POLLTASK_WRREG1000]++;
		}
	}
}

void vCoordinatorTx_Proc(void)
{
	;
}

void vCoordinatorRx_Proc(UsartxDMARx_TypeDef *hRx)
{
	uint8_t cmd[4];
	cmd[0]=CC2530CMD_HEAD_01;
	cmd[1]=CC2530CMD_HEAD_02;
	cmd[2]=CC2530CMD_HEAD_03;
	cmd[3]=CC2530CMD_HEAD_04;

	if(hRx->rxFlag)    
	{
		hRx->rxFlag=0;	
		
		if (CC2530CMD_OK!=eCC2530Cmd_CmdHeadCheck(cmd,hRx->rxData,4))return;
		
		if(hRx->rxData[4]==CC2530CMD_SENDDATA_2CORDINATOR &&\
			usMBCRC16(&hRx->rxData[7],hRx->rxSize-7)==0x00)//Zigbee命令头无需要校验
		{
			//modbus协议解析
			switch(hRx->rxData[8])
			{
				case 0x41:
					if(hRx->rxSize==22)
						vSlaveReadCmd0x03(hRx);					
					break;
				case 0x42:
					if(hRx->rxSize==15)
						vSlaveReadCmd0x10(hRx);
					break;
				default:
					break;
			}			
		}
		else if( 	(hRx->rxData[4]==CC2530CMD_READ_NET_STATUS) ||\
							(hRx->rxData[4]==CC2530CMD_RESET_FACTORY) ||\
							(hRx->rxData[4]==CC2530CMD_WRITE_PANID) ||\
							(hRx->rxData[4]==CC2530CMD_READ_PANID) ||\
							(hRx->rxData[4]==CC2530CMD_WRITE_BAUDRATE) ||\
							(hRx->rxData[4]==CC2530CMD_WRITE_COMMUNICATION_CHANNEL) ||\
							(hRx->rxData[4]==CC2530CMD_READ_MACADRR) ||\
							(hRx->rxData[4]==CC2530CMD_SENDDATA_BY_SHORTADDR_USERDEF)
						)
		vCC2530CmdRet_Proc(hRx);	
	}
}

/******************************************************************************
* @函数名称：SlaveReadCmd0x03
* @函数功能：接收BCU 03功能码
* @输入参数：
* @输出参数：
* @算法思路：
Coodinator接收22字节
	FRAME= HEAD+ DATA								      								 --22bytes
	HEAD = 02 A8 79 C3 0A + 29 D7                          --7bytes
	DATA = 00 41 0A + 00 08 09 DB 00 00 10 10 00 00 +17 6D --15bytes(3+10+2)
Router实际发送20字节
	FRAME= HEAD+ DATA								      								 --20bytes
	HEAD = 02 A8 79 C3 0A					                         --5bytes
	DATA = 00 41 0A + 00 08 09 DB 00 00 10 10 00 00 +17 6D --15bytes(3+10+2)
* @使用资源：
* @注意事项：
******************************************************************************/
static void vSlaveReadCmd0x03( UsartxDMARx_TypeDef *hRx )
{
	if(hRx==&Rx_C1)
	{
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		Cx = CC2530PA2S_C1;//0
	}			
	else if(hRx==&Rx_C2)
	{
		HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);	
		Cx = CC2530PA2S_C2;	//1		
	}			
	else if(hRx==&Rx_C3)
	{
		HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
		Cx = CC2530PA2S_C3;//2
	}
	
	/* Start Protocol */
	Coordinator[Cx].rxBCUNum[_1_40] = ((uint16_t)(hRx->rxData[10]<<8)+hRx->rxData[11])>>3;//接收Ri的编号,范围1~40
	Coordinator[Cx].rxBCUNum[_1_512] = Coordinator[Cx].rxBCUNum[_1_40] +(Cx*MAXROUTER_Default+ECUInfo.bias);//接收Ri的编号,范围1~512
	Coordinator[Cx].shortAdd[Coordinator[Cx].rxBCUNum[_1_40]-1]=(uint16_t)(hRx->rxData[5]<<8)+hRx->rxData[6];//接收Ri的系统分配短地址
	Coordinator[Cx].rxCntNow[Coordinator[Cx].rxBCUNum[_1_40]-1]++;//接收Ri的次数				
	
	/* Start Save to Buffer */
#if 0
	//BigEndian
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.U = (uint16_t)(hRx->rxData[12]<<8)+hRx->rxData[13];
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.R = (uint16_t)(hRx->rxData[14]<<8)+hRx->rxData[15];
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.T = (uint16_t)(hRx->rxData[16]<<8)+hRx->rxData[17];
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.S = (uint16_t)(hRx->rxData[18]<<8)+hRx->rxData[19];
	
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].U = (uint16_t)(hRx->rxData[12]<<8)+hRx->rxData[13];
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].R = (uint16_t)(hRx->rxData[14]<<8)+hRx->rxData[15];
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].T = (uint16_t)(hRx->rxData[16]<<8)+hRx->rxData[17];
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].S = (uint16_t)(hRx->rxData[18]<<8)+hRx->rxData[19];
	CellV[Coordinator[Cx].rxBCUNum[_1_512]-1]=(uint16_t)(hRx->rxData[12]<<8)+hRx->rxData[13];
	CellR[Coordinator[Cx].rxBCUNum[_1_512]-1]=(uint16_t)(hRx->rxData[14]<<8)+hRx->rxData[15];
	CellT[Coordinator[Cx].rxBCUNum[_1_512]-1]=(uint16_t)(hRx->rxData[16]<<8)+hRx->rxData[17];
#else
	//ARM_CPU is LittleEndian
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.U = (uint16_t)(hRx->rxData[13]<<8)+hRx->rxData[12];
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.R = (uint16_t)(hRx->rxData[15]<<8)+hRx->rxData[14];
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.T = (uint16_t)(hRx->rxData[17]<<8)+hRx->rxData[16];
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.S = (uint16_t)(hRx->rxData[19]<<8)+hRx->rxData[18];

	//for modbus rtu 03,reg:0x1000~0x2000
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].U = (uint16_t)(hRx->rxData[13]<<8)+hRx->rxData[12];
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].R = (uint16_t)(hRx->rxData[15]<<8)+hRx->rxData[14];
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].T = (uint16_t)(hRx->rxData[17]<<8)+hRx->rxData[16];
//	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].S = (uint16_t)(hRx->rxData[19]<<8)+hRx->rxData[18];
	//TODO Delete
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].S = (uint16_t)(hRx->rxData[18]<<8)+hRx->rxData[19];

	//上行下行成功率测试时使用modbuspoll观看数据
	#if defined(VIEWMODBUSPOLL_CC2530TEST_UPDOWNRATE)
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].RB = __REV16(Coordinator[Cx].rxCntNow[MAXROUTER_Default]/ECUInfo.ECUOnLineTime.Second*100.0);
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].RES[0] = __REV16(Coordinator[Cx].txCnt[POLLTASK_WRREG1000]);
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].RES[1] = __REV16(ECUInfo.ECUOnLineTime.Second);
	BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].RES[2] = __REV16(Coordinator[Cx].rxCntNow[MAXROUTER_Default]);
	#endif

	//for modbus rtu 03,reg:0x0000~0x0600
	CellV[Coordinator[Cx].rxBCUNum[_1_512]-1]=(uint16_t)(hRx->rxData[13]<<8)+hRx->rxData[12];
	CellR[Coordinator[Cx].rxBCUNum[_1_512]-1]=(uint16_t)(hRx->rxData[15]<<8)+hRx->rxData[14];
	CellT[Coordinator[Cx].rxBCUNum[_1_512]-1]=(uint16_t)(hRx->rxData[17]<<8)+hRx->rxData[16];
#endif


//	if(BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].S>0)
//	printf("\r\n%d/%d号BCU的状态位:%d\r\n",Coordinator[Cx].rxBCUNum[_1_512],Coordinator[Cx].rxBCUNum[_1_40],BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].S);
	
	/* Start Print BcuData */
#if defined(PRINT_BCUDATA)
	if(!IS_ECUMODE(ECUMODE_ReadNw))
		printf("\r\n[%d/%d]#BCU,接收次数:%d,电压:%dmV 内阻:%dμΩ 温度:%d℃ 状态%0X\r\n",\
	Coordinator[Cx].rxBCUNum[_1_512],\
	Coordinator[Cx].rxBCUNum[_1_40],\
	Coordinator[Cx].rxCntNow[Coordinator[Cx].rxBCUNum[_1_40]-1],\
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.U,\
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.R,\
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.T-50,\
	BCUInfo[Coordinator[Cx].rxBCUNum[_1_512]-1].data.S);
#endif
}

/**
* @函数名称：SlaveReadCmd0x10
* @函数功能：0x10功能码，对BCU的写入操作
* @输入参数：
*
* @输出参数：void
* @算法思路：判断编号成功的上行帧 02 A8 79 C3 0A +  30 4C + 08 42 00 08 4F 4B 8C 99
						1）当接收到上述编号成功的的上行帧，更新配置序号C1.Config_BCUNum;
            2）当协调器接收到第40个模块时，退出全配置模式，直到C3退出全配置模式

* @使用资源：
* @注意事项：
*/
static void vSlaveReadCmd0x10( UsartxDMARx_TypeDef *hRx  )
{
	uint16_t reg_adr   =(uint16_t)(hRx->rxData[9]<<8)+hRx->rxData[10];//获取到了寄存器地址
	uint16_t op_result =(uint16_t)(hRx->rxData[11]<<8)+hRx->rxData[12];//返回操作结果
	
	if(hRx==&Rx_C1)
	{
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		Cx = CC2530PA2S_C1;//0
	}			
	else if(hRx==&Rx_C2)
	{
		HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);	
		Cx = CC2530PA2S_C2;//1		
	}			
	else if(hRx==&Rx_C3)
	{
		HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
		Cx = CC2530PA2S_C3;//2
	}			

	if(op_result == 0x4F4B )
	{			
		if((Coordinator[Cx].Cfg.BCUNum<<3)==reg_adr)
		{
			/*接收到了BCU编号的上行帧后，更新点灯帧*/
			UPDATE_NUMBCU_LEDFRAME_C(Cx);
			/*接收到了BCU编号的上行帧后，更新编号帧*/
			UPDATE_NUMBCU_NUMFRAME_C(Cx);
			/*当前C1配置结束，进入C2配置*/
			if(Coordinator[Cx].Cfg.Mode==FULL_CONFIG_MODE)
			{
				if((MAXROUTER_Default<<3)==reg_adr)
				{	
					//全配置模式需要逐个认领完MAXNUM_CORDINATOR个BCU模块
					Coordinator[Cx].Cfg.Cplt=OVER_FULL_CONFIG_MODE;
				}						
			}
			else if(Coordinator[Cx].Cfg.Mode==PART_CONFIG_MODE)
			{
				//临时配置模式需要由用户终止配置
				if(Coordinator[Cx].Cfg.BCUNum>MAXROUTER_Default)
				{
					Coordinator[Cx].Cfg.Cplt=OVER_PART_CONFIG_MODE;
				}				
			}
		}

	}
	else
	{
		//参数错误

	}
}

#if defined(CC2530TEST_UPDOWNRATE)
/**
* @函数名称：Communication_Statistics
* @函数功能：
* @输入参数：
* @输出参数：
* @算法思路：
						rxBCUNum[0]	:接收编号,1~40
						rxBCUNum[1]	:接收编号,1~512	
						rxBCUNum[2]	:接收次数最多的BCU编号,1-40
						rxBCUNum[3]	:接收次数最多的BCU编号,1-512
						rxBCUNum[4]	:接收次数最少的BCU编号,1-40
						rxBCUNum[5]	:接收次数最少的BCU编号,1-512
						
						rxCntNow[MAXROUTER_Default]	:当前接收Rn的平均次数，
						rxCntNow[MAXROUTER_Default+1]	:最大次数
						rxCntNow[MAXROUTER_Default+2]	:最小次数
						rxCntNow[MAXROUTER_Default+3]	:未接收到BCU的个数
						
* @使用资源：
* @注意事项：
*/
static void vTestDemo_CC2530UpDwRate(void)
{
	float sum[3]={0,0,0};
	float sum2[3]={0,0,0};
	uint8_t cntZero[3]={0,0,0};
	uint8_t cntZero2[3]={0,0,0};
	float temp1;
	float temp2;
	
	#if defined(PRINT_CC2530TEST_UPDOWNRATE)
	printf("\r\n\r\n\r\n\r\n*****************************************************【Test1 Coordinator点播发送给Ri的次数】********************************************************************\r\n");
	#endif
	for (uint8_t j=0;j<3;j++)
	{
		for(uint8_t i=0;i<MAXROUTER_Default;i++)
		{
			#if defined(PRINT_CC2530TEST_UPDOWNRATE)
			if(i==0)printf("\r\nCoordinator%d点播(点播数量:%d)发送给Ri的次数\r\n\r\n",j+1,MAXROUTER_Test(BCUNUM_Test));
			printf(" R[%2d]=%-8d ",i,BCUData[i+j*MAXROUTER_Default+ECUInfo.bias].S);
			if(((i+1)%10)==0)printf("\r\n");
			#endif
			if(i<MAXROUTER_Test(BCUNUM_Test))
			{
				sum2[j]+=BCUData[i+j*MAXROUTER_Default+ECUInfo.bias].S;
				if(BCUData[i+j*MAXROUTER_Default+ECUInfo.bias].S==0)
					cntZero2[j]++;
			}
		}

		if((sum2[j]!=0) &&\
			(MAXROUTER_Test(BCUNUM_Test)-cntZero2[j]!=0))
		{
			temp1=sum2[j]/(MAXROUTER_Test(BCUNUM_Test)-cntZero2[j]);
		}
		else
		{
			temp1=0;
		}

		if((sum2[j]!=0) &&\
			(MAXROUTER_Test(BCUNUM_Test)-cntZero2[j]!=0) &&\
			(Coordinator[j].txCnt[POLLTASK_WRREG1000]!=0))
		{
			temp2=sum2[j]/(MAXROUTER_Test(BCUNUM_Test)-cntZero2[j])/Coordinator[j].txCnt[POLLTASK_WRREG1000]*100.0f;
		}
		else
		{
			temp2=0;
		}

		#if defined(PRINT_CC2530TEST_UPDOWNRATE)
		printf("\r\nC%d点播发送到Ri次数的统计信息：【点播轮次:%d轮,平均接收次数:%.1f,下行得包率:%.1f%%,%d个BCU未收到点播命令】\r\n",\
		j+1,\
		Coordinator[j].txCnt[POLLTASK_WRREG1000],\
		temp1,\
		temp2,\
		cntZero2[j]);
		#endif
	}
	
	#if defined(PRINT_CC2530TEST_UPDOWNRATE)
	printf("\r\n\r\n\r\n\r\n******************************************************【Test2 Coordinator接收到Ri的次数】***********************************************************************\r\n");
	#endif
	for (uint8_t i=0;i<3;i++)
	{
		Coordinator[i].rxCntNow[MAXROUTER_Default+1]=Coordinator[i].rxCntNow[0];//C0 max
		Coordinator[i].rxCntNow[MAXROUTER_Default+2]=Coordinator[i].rxCntNow[0];//C0 min
		Coordinator[i].rxBCUNum[CNTMAX_1_40]=1;
		Coordinator[i].rxBCUNum[CNTMIN_1_40]=1;
	}
	for (uint8_t j=0;j<3;j++)
	{
		for(uint8_t i=0;i<MAXROUTER_Default;i++)
		{
			/* sum */
			sum[j]+=Coordinator[j].rxCntNow[i];
			/* max */
			if(Coordinator[j].rxCntNow[i]>Coordinator[j].rxCntNow[MAXROUTER_Default+1])
			{
				Coordinator[j].rxCntNow[MAXROUTER_Default+1]=Coordinator[j].rxCntNow[i];
				Coordinator[j].rxBCUNum[CNTMAX_1_40]=i+1;
			}
			/* min */
			if(Coordinator[j].rxCntNow[i]<Coordinator[j].rxCntNow[MAXROUTER_Default+2])
			{
				Coordinator[j].rxCntNow[MAXROUTER_Default+2]=Coordinator[j].rxCntNow[i];
				Coordinator[j].rxBCUNum[CNTMIN_1_40]=i+1;
			}
			/* zero */
			if(Coordinator[j].rxCntNow[i]==0)
			{
				cntZero[j]++;
				#if defined(PRINT_CC2530TEST_UPDOWNRATE)
//				printf(" cntZero[%d][%d]:%d ",j,i,cntZero[j]);
				#endif
			}
			
			#if defined(PRINT_CC2530TEST_UPDOWNRATE)
			/* print */
			if(i==0)printf("\r\nCoordinator%d接收到Ri的次数\r\n\r\n",j+1);
			printf(" R[%2d]=%-8d ",i,Coordinator[j].rxCntNow[i]);
			if(((i+1)%10)==0)printf("\r\n");
			#endif
		}
		
		Coordinator[j].rxCntNow[MAXROUTER_Default]=sum[j]/(MAXROUTER_Default-cntZero[j]);
		Coordinator[j].rxBCUNum[CNTMAX_1_512]=Coordinator[j].rxBCUNum[CNTMAX_1_40]+(j*MAXROUTER_Default+ECUInfo.bias);
		Coordinator[j].rxBCUNum[CNTMIN_1_512]=Coordinator[j].rxBCUNum[CNTMIN_1_40]+(j*MAXROUTER_Default+ECUInfo.bias);
		
		Coordinator[j].rxCntNow[MAXROUTER_Default+3]=cntZero[j];
		#if defined(PRINT_CC2530TEST_UPDOWNRATE)
//		printf("\r\n  C%d未收到的BCU个数%d\r\n ",j,Coordinator[j].rxCntNow[MAXROUTER_Default+3]);
		#endif
	}
	
	#if defined(PRINT_CC2530TEST_UPDOWNRATE)
	printf("\r\n运行时间\r\n");
	print_ECUOnLineTime();
	print_RTC();
	for (uint8_t j=0;j<3;j++)
	{
		printf("\r\nC%d接收到Ri次数的统计信息：【运行时间:%.1fs,平均次数:%ld,上行得包率:%.1f%%,Rmax[%d/%d]=%ld,Rmin[%d,%d]=%ld,%ld个BCU数据未上报】\r\n",\
		j+1,\
		ECUInfo.ECUOnLineTime.Second,\
		Coordinator[j].rxCntNow[MAXROUTER_Default],\
		Coordinator[j].rxCntNow[MAXROUTER_Default]/ECUInfo.ECUOnLineTime.Second*100.0f,\
		Coordinator[j].rxBCUNum[CNTMAX_1_512],\
		Coordinator[j].rxBCUNum[CNTMAX_1_40],\
		Coordinator[j].rxCntNow[MAXROUTER_Default+1],\
		Coordinator[j].rxBCUNum[CNTMIN_1_512],\
		Coordinator[j].rxBCUNum[CNTMIN_1_40],\
		Coordinator[j].rxCntNow[MAXROUTER_Default+2],\
		Coordinator[j].rxCntNow[MAXROUTER_Default+3]
		);		
	}
	#endif
}
#endif

static void vCC2530CmdRet_Proc( UsartxDMARx_TypeDef *hRx )
{
	if(hRx==&Rx_C1)
	{
//		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		Cx = CC2530PA2S_C1;//0
	}			
	else if(hRx==&Rx_C2)
	{
//		HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);	
		Cx = CC2530PA2S_C2;	//1		
	}			
	else if(hRx==&Rx_C3)
	{
//		HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
		Cx = CC2530PA2S_C3;//2
	}
	//CC2530命令查询帧
	switch (hRx->rxData[4])
	{
		case CC2530CMD_READ_NET_STATUS:
				if(hRx->rxSize!=6) return;
				if(hRx->rxData[5]==CC2530NETWORK_ERROR)printf("\r\n设备%d没有加入网络\r\n",Cx);
				else if(hRx->rxData[5]==CC2530NETWORK_ENDDEVICE_OK)printf("\r\nEnd Device%d已经入网\r\n",Cx);
				else if(hRx->rxData[5]==CC2530NETWORK_ROUTER_OK)printf("\r\nRouter%d已经入网\r\n",Cx);
				else if(hRx->rxData[5]==CC2530NETWORK_CORDINATOR_OK)printf("\r\nCordinator%d已经入网\r\n",Cx);
		break;
		
		case CC2530CMD_RESET_FACTORY:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d恢复出厂错误!\r\n",Cx);
				else printf("\r\nC%d恢复出厂成功!\r\n",Cx);
		break;
		
		case CC2530CMD_WRITE_PANID:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d PANID设置错误!\r\n",Cx);
				else printf("\r\nC%d PANID设置成功!\r\n",Cx);
		break;
		
		case CC2530CMD_READ_PANID:
				if(hRx->rxSize!=8) return;
				else
				{
					if(IS_ECUMODE(ECUMODE_CfgNw))
					{
							//查询时PANID返回错误(与期望值不相等)
							if(	ECUInfo.nwPara.panid_C[Cx] != ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
							{
								printf("\r\nPANID C%d Err,PANID:0x%0X\r\n",Cx,(uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]);
								print_ECUMode();
								if((ECUInfo.nwPara.panid_C[Cx]+0x100) == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
									printf("\r\nC%d参数写入时加1了,查检网络参数冲突原因\r\n",Cx);
							}
							//查询时信道返回错误(与期望值不相等)
							if(ECUInfo.nwPara.chanel_C[Cx] != hRx->rxData[7])
							{
								ECUInfo.nwPara.confirmTimes[Cx]++;
								printf("\r\nChannel C%d Err\r\n",Cx);
							}
							//查询时PANID信道均返回正确(与期望值相等)
							if((ECUInfo.nwPara.panid_C[Cx] == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))&&\
								(ECUInfo.nwPara.chanel_C[Cx] == hRx->rxData[7]))
							{
									ClrBit(ECUInfo.nwPara.WriteNw_En,Cx);
									printf("\r\nC%d网络设置成功,参数组【%d】=【PANID:0x%0X,信道:0x%0X】\r\n",Cx,ECUInfo.nwPara.nwNum_C[Cx],ECUInfo.nwPara.panid_C[Cx],ECUInfo.nwPara.chanel_C[Cx]);
									print_ECUMode();
									if(ECUInfo.nwPara.WriteNw_En==0)
									{
										ECUInfo.En_IwdgRst=0x01;//所有三个C均设置成功才复位
										printf("\r\n网络设置完毕,三个模块参数均正常\r\n");
									}
							}
					}
					else if(IS_ECUMODE(ECUMODE_ReadNw))
					{
							//查询时PANID返回错误(与期望值不相等)
							if(	ECUInfo.nwPara.panid_C[Cx] != ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
							{
								SetBit(ECUInfo.nwPara.WriteNw_En,Cx);
								printf("\r\nPANID C%d Err,PANID:0x%0X\r\n",Cx,(uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]);
								print_ECUMode();
								if((ECUInfo.nwPara.panid_C[Cx]+0x100) == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
									printf("\r\nC%d参数写入时加1了,查检网络参数冲突原因\r\n",Cx);
							}
							//查询时信道返回错误(与期望值不相等)
							if(ECUInfo.nwPara.chanel_C[Cx] != hRx->rxData[7])
							{
								ECUInfo.nwPara.confirmTimes[Cx]++;
								printf("\r\nChannel C%d Err\r\n",Cx);
							}
							//查询时PANID信道均返回正确(与期望值相等)
							if((ECUInfo.nwPara.panid_C[Cx] == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))&&\
								(ECUInfo.nwPara.chanel_C[Cx] == hRx->rxData[7]))
							{
									ClrBit(ECUInfo.nwPara.ReadNw_En,Cx);
									printf("\r\nC%d网络查询正常,参数组【%d】=【PANID:0x%0X,信道:0x%0X】\r\n",Cx,ECUInfo.nwPara.nwNum_C[Cx],ECUInfo.nwPara.panid_C[Cx],ECUInfo.nwPara.chanel_C[Cx]);
									print_ECUMode();
									if(ECUInfo.nwPara.ReadNw_En==0)
									{
										ECUMODE_ATTACH(ECUMODE_Normal);
										KEY2EVENT_ATTACH(KEYMODE_NORMAL);
										printf("\r\n网络查询完毕,三个模块参数均正常\r\n");
										print_ECUMode();
									}
							}
					}
				}
		break;
		
		case CC2530CMD_WRITE_BAUDRATE:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d 波特率设置错误!\r\n",Cx);
				else printf("\r\nC%d 波特率设置成功!\r\n",Cx);
		break;
		
		case CC2530CMD_WRITE_COMMUNICATION_CHANNEL:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d 信道设置错误!\r\n",Cx);
				else printf("\r\nC%d 信道设置成功!\r\n",Cx);
		break;
		
		case CC2530CMD_READ_MACADRR:
			//TODO
		break;
		
		case CC2530CMD_SENDDATA_BY_SHORTADDR_USERDEF:
			//TODO
		break;
		
		default:
		break;
	}
}

/**********************************************************************************/
/*      公有函数实现	             	                                              */
/**********************************************************************************/


void vCoordinator_Init(void)
{
	//TODO
	if(CC2530CMD_OK!=vCC2530_BaudInit(ECUInfo.baud,ECUInfo.baud,ECUInfo.baud))
	{
		vCC2530_ErrorHandle();
	}
	if(CC2530CMD_OK!=eCC2530_NWInit(ECUInfo.nwPara.nwNum_C[0],ECUInfo.nwPara.nwNum_C[1],ECUInfo.nwPara.nwNum_C[2]))
	{
		vCC2530_ErrorHandle();
	}
}

/******************************************************************************
* @函数名称：BCUSlave_Proc
* @函数功能：
* @输入参数：
*
* @输出参数：void
* @算法思路：
									单体数据帧：02 A8 79 C3 0A xx yy + "data"
						CC2530命令查询帧: 02 A8 79 C3 01/03/04/05/06/09
* @被调用的函数：
* @使用资源：
* @注意事项：
******************************************************************************/
void vBCUSlave_Proc(void)
{
	vCoordinatorTx_Proc();//TODO保证任务不被抢断
#if !defined(EN_FREERTOS)
	vCoordinatorRx_Proc(&Rx_C1);
	vCoordinatorRx_Proc(&Rx_C2);
	vCoordinatorRx_Proc(&Rx_C3);
#endif
	vCommunicationFault_Proc();
}


void vCommunicationFault_Proc(void)
{
	#if defined(EN_VIEWSTMSTD)
	vC1_CntView_Debug();
	vC2_CntView_Debug();
	vC3_CntView_Debug();
	#endif

	vBCUDataStatistics();

	//做无线上行下行得包率统计实验
	#if defined(CC2530TEST_UPDOWNRATE)
	if(tag_15s)
	{
		tag_15s=0;
		vTestDemo_CC2530UpDwRate();
	}
	#endif
}

CC2530CmdRet_TypeDef eNwNum2PANID(uint16_t network_Num_C1,uint16_t network_Num_C2,uint16_t network_Num_C3)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	uint16_t temp=0;
	if((network_Num_C1>500)||(network_Num_C2>500)||(network_Num_C3>500))
	{
		cc2530CmdRet =CC2530CMD_ERROR;
		return cc2530CmdRet;
	}

	/* 参数计算 */
	//panid
	ECUInfo.nwPara.panid_C[0] = 6*network_Num_C1-5;
	ECUInfo.nwPara.panid_C[1] = 6*network_Num_C2-5;
	ECUInfo.nwPara.panid_C[2] = 6*network_Num_C3-5;
	ECUInfo.nwPara.panid2_C[0] = 6*network_Num_C1-2;
	ECUInfo.nwPara.panid2_C[1] = 6*network_Num_C2-2;
	ECUInfo.nwPara.panid2_C[2] = 6*network_Num_C3-2;

	//C1 channel
	temp = network_Num_C1>>4;
	temp = temp<<4;
	ECUInfo.nwPara.chanel_C[0] =network_Num_C1 - temp + 10;
	if(network_Num_C1 % 16 == 0)
		ECUInfo.nwPara.chanel_C[0] =0x1A;
	//C2 channel
	temp = network_Num_C2>>4;
	temp = temp<<4;
	ECUInfo.nwPara.chanel_C[1] =network_Num_C2 - temp + 10;
	if(network_Num_C2 % 16 == 0)
		ECUInfo.nwPara.chanel_C[1] =0x1A;
	//C3 channel
	temp = network_Num_C3>>4;
	temp = temp<<4;
	ECUInfo.nwPara.chanel_C[2] =network_Num_C3 - temp + 10;
	if(network_Num_C3 % 16 == 0)
		ECUInfo.nwPara.chanel_C[2] =0x1A;
	return cc2530CmdRet;
}
/******************************************************************************
 * @函数名称：CC2530_NWInit
 * @函数功能：无线网络初始化(PANID,信道)
 * @输入参数：
 *            1)network_Num_C1
 *            network_Num_C2
 *            network_Num_C3
 * @输出参数：
 *            1)
 * @算法思路：
 * @被调用的函数：
 * @使用资源：
 * @注意事项：
 ******************************************************************************/
CC2530CmdRet_TypeDef eCC2530_NWInit(uint16_t network_Num_C1,uint16_t network_Num_C2,uint16_t network_Num_C3)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	/* TODO GET BAUD RATE*/

	/* Get THE PANID AND CHANNEL */
	if(CC2530CMD_OK!=eNwNum2PANID(network_Num_C1,network_Num_C2,network_Num_C3))
	{
		vCC2530_ErrorHandle();
	}

	/* WRITE THE PANID AND CHANNEL */
	if(GetBit(ECUInfo.nwPara.WriteNw_En,0))
		eCC2530CMD_SetPANID_04(&Coordinator1_Usart,ECUInfo.nwPara.panid_C[0]);
	if(GetBit(ECUInfo.nwPara.WriteNw_En,1))
		eCC2530CMD_SetPANID_04(&Coordinator2_Usart,ECUInfo.nwPara.panid_C[1]);
	if(GetBit(ECUInfo.nwPara.WriteNw_En,2))
		eCC2530CMD_SetPANID_04(&Coordinator3_Usart,ECUInfo.nwPara.panid_C[2]);
	DelayMs(100);

	if(GetBit(ECUInfo.nwPara.WriteNw_En,0))
		eCC2530CMD_SetChannel_09(&Coordinator1_Usart,ECUInfo.nwPara.chanel_C[0]);
	if(GetBit(ECUInfo.nwPara.WriteNw_En,1))
		eCC2530CMD_SetChannel_09(&Coordinator2_Usart,ECUInfo.nwPara.chanel_C[1]);
	if(GetBit(ECUInfo.nwPara.WriteNw_En,2))
		eCC2530CMD_SetChannel_09(&Coordinator3_Usart,ECUInfo.nwPara.chanel_C[2]);
	DelayMs(100);

	/* START READ THE PANID AND CHANNEL */
	if(IS_ECUMODE(ECUMODE_CfgNw))
	{
		if(GetBit(ECUInfo.nwPara.WriteNw_En,0))
			ulCC2530CMD_GetPANID_05(&Coordinator1_Usart);
		if(GetBit(ECUInfo.nwPara.WriteNw_En,1))
			ulCC2530CMD_GetPANID_05(&Coordinator2_Usart);
		if(GetBit(ECUInfo.nwPara.WriteNw_En,2))
			ulCC2530CMD_GetPANID_05(&Coordinator3_Usart);
	}
	else if(IS_ECUMODE(ECUMODE_ReadNw))
	{
		if(GetBit(ECUInfo.nwPara.ReadNw_En,0))
			ulCC2530CMD_GetPANID_05(&Coordinator1_Usart);
		if(GetBit(ECUInfo.nwPara.ReadNw_En,1))
			ulCC2530CMD_GetPANID_05(&Coordinator2_Usart);
		if(GetBit(ECUInfo.nwPara.ReadNw_En,2))
			ulCC2530CMD_GetPANID_05(&Coordinator3_Usart);
	}
	DelayMs(100);

	return cc2530CmdRet;
}

CC2530CmdRet_TypeDef vCC2530_BaudInit(CC2530BaudRate_TypeDef cc2530Baud_C1,CC2530BaudRate_TypeDef cc2530Baud_C2,CC2530BaudRate_TypeDef cc2530Baud_C3)
{
	CC2530CmdRet_TypeDef cc2530CmdRet = CC2530CMD_OK;
	eCC2530CMD_WriteBaudRate_06(&huart2,cc2530Baud_C1);
	eCC2530CMD_WriteBaudRate_06(&huart3,cc2530Baud_C2);
	eCC2530CMD_WriteBaudRate_06(&huart6,cc2530Baud_C3);
	printf("\r\n待写入波特率=【C1:0x%0X,C2:0x%0X,C3:0x%0X】\r\n",cc2530Baud_C1,cc2530Baud_C2,cc2530Baud_C3);
	return cc2530CmdRet;
}





/*****************************************End of coordinator.c*****************************************/
