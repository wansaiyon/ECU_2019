/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: coordinator.c
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/02		04:39:53
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#define COORDINATOR_GLOBALS
//#include "Include.h"
#include "coordinator.h"


/**********************************************************************************/
/*      ˽�б�������              	                                		      */
/**********************************************************************************/


/**********************************************************************************/
/*      ˽�к�������              	                                              */
/**********************************************************************************/

static void vCC2530_ErrorHandle(void);
static CC2530CmdRet_TypeDef eCC2530Cmd_CmdHeadCheck(uint8_t *,uint8_t *,uint8_t);
//TODO
static CC2530BaudRate_TypeDef eCC2530_BaudFind(UART_HandleTypeDef *);
static CC2530CmdRet_TypeDef eCC2530_BaudInit0(CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef );

//CC2530��BCU���
static void vCC2530_NumBCU(CC2530Cast_TypeDef castType);
static void vHAL_NumBCU(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//CC2530��BCU����ͬ���ź�
static void vCC2530_HeartBeat(CC2530Cast_TypeDef castType);
static void vHAL_HeartBeat(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//CC2530�������

//CC2530�㲥BCU��λ
static void vCC2530_NWRst(CC2530Cast_TypeDef castType);
static void vHAL_NWRst(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//CC2530��������
static void vCC2530_NWRestart(CC2530Cast_TypeDef castType);
static void vHAL_NWRestart(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx);
//д1000�Ĵ�����ַ
//static void HAL_WriteReg1000(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx,REG1000_TypeDef reg1000Type,CC2530NWADD_TypeDef nwAddType);
void vHAL_WriteReg1000(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx,REG1000_TypeDef reg1000Type,CC2530NWADD_TypeDef nwAddType);



//CC2530����,�������ݴ���
//static void CoordinatorTx_Proc(void);
//static void CoordinatorRx_Proc(UsartxDMARx_TypeDef *hRx);
void vCoordinatorTx_Proc(void);
void vCoordinatorRx_Proc(UsartxDMARx_TypeDef *hRx);

//modbusЭ����մ���
static void vSlaveReadCmd0x03( UsartxDMARx_TypeDef *hRx );
static void vSlaveReadCmd0x10( UsartxDMARx_TypeDef *hRx );
//radioland CC2530�����Ƿ����óɹ����մ���
static void vCC2530CmdRet_Proc( UsartxDMARx_TypeDef *hRx );

#if defined(CC2530TEST_UPDOWNRATE)
//����ͨ������ͳ��
static void vTestDemo_CC2530UpDwRate( void );
#endif
/**********************************************************************************/
/*      ˽�к���ʵ��              	                                              */
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
* @�������ƣ�CC2530_BaudFind
* @�������ܣ�
* @���������
*
* @���������void
* @�㷨˼·��
						���ڳ�ʼ��Ϊ38400;
            ��01������ѯ�����з��أ�˵��coordinator�Ĳ�����Ϊ38400,��ӡ������Ϣ
						����coordinator�Ĳ�����Ϊ9600��MCU���ڳ�ʼΪ9600����ӡ������Ϣ
* @�����õĺ�����
* @ʹ����Դ��
* @ע�����
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
					printf("�豸û�м�������");
				break;
				case CC2530NETWORK_ENDDEVICE_OK:
					printf("End Device�Ѿ�����");
				break;
				case CC2530NETWORK_ROUTER_OK:
					printf("Router�Ѿ�����");
				break;
				case CC2530NETWORK_CORDINATOR_OK:
					printf("Cordinator�Ѿ�����");
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
					printf("�豸û�м�������");
				break;
				case CC2530NETWORK_ENDDEVICE_OK:
					printf("End Device�Ѿ�����");
				break;
				case CC2530NETWORK_ROUTER_OK:
					printf("Router�Ѿ�����");
				break;
				case CC2530NETWORK_CORDINATOR_OK:
					printf("Cordinator�Ѿ�����");
				break;
				default:
				break;
			}
		}
	}
	return cc2530BaudRate;
}

/******************************************************************************
* @�������ƣ�CC2530_BaudInit0
* @�������ܣ�
* @���������
*						cc2530Baud��������
* @���������void
* @�㷨˼·��
						��ȡCoordinator�Ĳ����ʣ��������������ȣ�ֱ�ӷ���
            ������ȣ���cc2530 06������������һ��
* @�����õĺ�����
* @ʹ����Դ��
* @ע�����
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
	
	//��ȡC1������	
	cmd[5]=cc2530Baud_C1;
	cc2530BaudRate = eCC2530_BaudFind(&huart2);
	
	if(cc2530BaudRate ==cc2530Baud_C1)
	{
		printf("\r\nCC2530_BaudInit() C1: OK,��ʼ��Ϊ:%0x\r\n",cc2530BaudRate);
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
				printf("\r\nCC2530_BaudInit() C1: OK,��ʼ��Ϊ:%0x\r\n",cc2530BaudRate);
		}
		else
		{
			cc2530CmdRet = CC2530CMD_ERROR;
			printf("\r\nCC2530_BaudInit() C1: Err\r\n");//������Ӧ���ǲ����ܵ������֧��
		}
	}
	
	//��ȡC2������	
	cmd[5]=cc2530Baud_C2;
	cc2530BaudRate = eCC2530_BaudFind(&huart3);
	
	if(cc2530BaudRate ==cc2530Baud_C2)
	{
		printf("\r\nCC2530_BaudInit() C2: OK,��ʼ��Ϊ:%0x\r\n",cc2530BaudRate);
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
				printf("\r\nCC2530_BaudInit() C2: OK,��ʼ��Ϊ:%0x\r\n",cc2530BaudRate);
		}
		else
		{
			cc2530CmdRet = CC2530CMD_ERROR;
			printf("\r\nCC2530_BaudInit() C2: Err\r\n");//������Ӧ���ǲ����ܵ������֧��
		}
	}
	
	//��ȡC3������	
	cmd[5]=cc2530Baud_C3;
	cc2530BaudRate = eCC2530_BaudFind(&huart6);
	
	if(cc2530BaudRate ==cc2530Baud_C3)
	{
		printf("\r\nCC2530_BaudInit() C3: OK,��ʼ��Ϊ:%0x\r\n",cc2530BaudRate);
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
				printf("\r\nCC2530_BaudInit() C3: OK,��ʼ��Ϊ:%0x\r\n",cc2530BaudRate);
		}
		else
		{
			cc2530CmdRet = CC2530CMD_ERROR;
			printf("\r\nCC2530_BaudInit() C3: Err\r\n");//������Ӧ���ǲ����ܵ������֧��
		}
	}
	return cc2530CmdRet;	
}


//CC2530��BCU���
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
//CC2530��BCU����ͬ���ź�
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
//CC2530�������
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

//CC2530�㲥BCU��λ
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
//CC2530��������
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
//		printf("\r\n�㲥���͵����:%d\r\n",Coordinator[2].txBCUNum[POLLTASK_WRREG1000]);
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
			usMBCRC16(&hRx->rxData[7],hRx->rxSize-7)==0x00)//Zigbee����ͷ����ҪУ��
		{
			//modbusЭ�����
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
* @�������ƣ�SlaveReadCmd0x03
* @�������ܣ�����BCU 03������
* @���������
* @���������
* @�㷨˼·��
Coodinator����22�ֽ�
	FRAME= HEAD+ DATA								      								 --22bytes
	HEAD = 02 A8 79 C3 0A + 29 D7                          --7bytes
	DATA = 00 41 0A + 00 08 09 DB 00 00 10 10 00 00 +17 6D --15bytes(3+10+2)
Routerʵ�ʷ���20�ֽ�
	FRAME= HEAD+ DATA								      								 --20bytes
	HEAD = 02 A8 79 C3 0A					                         --5bytes
	DATA = 00 41 0A + 00 08 09 DB 00 00 10 10 00 00 +17 6D --15bytes(3+10+2)
* @ʹ����Դ��
* @ע�����
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
	Coordinator[Cx].rxBCUNum[_1_40] = ((uint16_t)(hRx->rxData[10]<<8)+hRx->rxData[11])>>3;//����Ri�ı��,��Χ1~40
	Coordinator[Cx].rxBCUNum[_1_512] = Coordinator[Cx].rxBCUNum[_1_40] +(Cx*MAXROUTER_Default+ECUInfo.bias);//����Ri�ı��,��Χ1~512
	Coordinator[Cx].shortAdd[Coordinator[Cx].rxBCUNum[_1_40]-1]=(uint16_t)(hRx->rxData[5]<<8)+hRx->rxData[6];//����Ri��ϵͳ����̵�ַ
	Coordinator[Cx].rxCntNow[Coordinator[Cx].rxBCUNum[_1_40]-1]++;//����Ri�Ĵ���				
	
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

	//�������гɹ��ʲ���ʱʹ��modbuspoll�ۿ�����
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
//	printf("\r\n%d/%d��BCU��״̬λ:%d\r\n",Coordinator[Cx].rxBCUNum[_1_512],Coordinator[Cx].rxBCUNum[_1_40],BCUData[Coordinator[Cx].rxBCUNum[_1_512]-1].S);
	
	/* Start Print BcuData */
#if defined(PRINT_BCUDATA)
	if(!IS_ECUMODE(ECUMODE_ReadNw))
		printf("\r\n[%d/%d]#BCU,���մ���:%d,��ѹ:%dmV ����:%d�̦� �¶�:%d�� ״̬%0X\r\n",\
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
* @�������ƣ�SlaveReadCmd0x10
* @�������ܣ�0x10�����룬��BCU��д�����
* @���������
*
* @���������void
* @�㷨˼·���жϱ�ųɹ�������֡ 02 A8 79 C3 0A +  30 4C + 08 42 00 08 4F 4B 8C 99
						1�������յ�������ųɹ��ĵ�����֡�������������C1.Config_BCUNum;
            2����Э�������յ���40��ģ��ʱ���˳�ȫ����ģʽ��ֱ��C3�˳�ȫ����ģʽ

* @ʹ����Դ��
* @ע�����
*/
static void vSlaveReadCmd0x10( UsartxDMARx_TypeDef *hRx  )
{
	uint16_t reg_adr   =(uint16_t)(hRx->rxData[9]<<8)+hRx->rxData[10];//��ȡ���˼Ĵ�����ַ
	uint16_t op_result =(uint16_t)(hRx->rxData[11]<<8)+hRx->rxData[12];//���ز������
	
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
			/*���յ���BCU��ŵ�����֡�󣬸��µ��֡*/
			UPDATE_NUMBCU_LEDFRAME_C(Cx);
			/*���յ���BCU��ŵ�����֡�󣬸��±��֡*/
			UPDATE_NUMBCU_NUMFRAME_C(Cx);
			/*��ǰC1���ý���������C2����*/
			if(Coordinator[Cx].Cfg.Mode==FULL_CONFIG_MODE)
			{
				if((MAXROUTER_Default<<3)==reg_adr)
				{	
					//ȫ����ģʽ��Ҫ���������MAXNUM_CORDINATOR��BCUģ��
					Coordinator[Cx].Cfg.Cplt=OVER_FULL_CONFIG_MODE;
				}						
			}
			else if(Coordinator[Cx].Cfg.Mode==PART_CONFIG_MODE)
			{
				//��ʱ����ģʽ��Ҫ���û���ֹ����
				if(Coordinator[Cx].Cfg.BCUNum>MAXROUTER_Default)
				{
					Coordinator[Cx].Cfg.Cplt=OVER_PART_CONFIG_MODE;
				}				
			}
		}

	}
	else
	{
		//��������

	}
}

#if defined(CC2530TEST_UPDOWNRATE)
/**
* @�������ƣ�Communication_Statistics
* @�������ܣ�
* @���������
* @���������
* @�㷨˼·��
						rxBCUNum[0]	:���ձ��,1~40
						rxBCUNum[1]	:���ձ��,1~512	
						rxBCUNum[2]	:���մ�������BCU���,1-40
						rxBCUNum[3]	:���մ�������BCU���,1-512
						rxBCUNum[4]	:���մ������ٵ�BCU���,1-40
						rxBCUNum[5]	:���մ������ٵ�BCU���,1-512
						
						rxCntNow[MAXROUTER_Default]	:��ǰ����Rn��ƽ��������
						rxCntNow[MAXROUTER_Default+1]	:������
						rxCntNow[MAXROUTER_Default+2]	:��С����
						rxCntNow[MAXROUTER_Default+3]	:δ���յ�BCU�ĸ���
						
* @ʹ����Դ��
* @ע�����
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
	printf("\r\n\r\n\r\n\r\n*****************************************************��Test1 Coordinator�㲥���͸�Ri�Ĵ�����********************************************************************\r\n");
	#endif
	for (uint8_t j=0;j<3;j++)
	{
		for(uint8_t i=0;i<MAXROUTER_Default;i++)
		{
			#if defined(PRINT_CC2530TEST_UPDOWNRATE)
			if(i==0)printf("\r\nCoordinator%d�㲥(�㲥����:%d)���͸�Ri�Ĵ���\r\n\r\n",j+1,MAXROUTER_Test(BCUNUM_Test));
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
		printf("\r\nC%d�㲥���͵�Ri������ͳ����Ϣ�����㲥�ִ�:%d��,ƽ�����մ���:%.1f,���еð���:%.1f%%,%d��BCUδ�յ��㲥���\r\n",\
		j+1,\
		Coordinator[j].txCnt[POLLTASK_WRREG1000],\
		temp1,\
		temp2,\
		cntZero2[j]);
		#endif
	}
	
	#if defined(PRINT_CC2530TEST_UPDOWNRATE)
	printf("\r\n\r\n\r\n\r\n******************************************************��Test2 Coordinator���յ�Ri�Ĵ�����***********************************************************************\r\n");
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
			if(i==0)printf("\r\nCoordinator%d���յ�Ri�Ĵ���\r\n\r\n",j+1);
			printf(" R[%2d]=%-8d ",i,Coordinator[j].rxCntNow[i]);
			if(((i+1)%10)==0)printf("\r\n");
			#endif
		}
		
		Coordinator[j].rxCntNow[MAXROUTER_Default]=sum[j]/(MAXROUTER_Default-cntZero[j]);
		Coordinator[j].rxBCUNum[CNTMAX_1_512]=Coordinator[j].rxBCUNum[CNTMAX_1_40]+(j*MAXROUTER_Default+ECUInfo.bias);
		Coordinator[j].rxBCUNum[CNTMIN_1_512]=Coordinator[j].rxBCUNum[CNTMIN_1_40]+(j*MAXROUTER_Default+ECUInfo.bias);
		
		Coordinator[j].rxCntNow[MAXROUTER_Default+3]=cntZero[j];
		#if defined(PRINT_CC2530TEST_UPDOWNRATE)
//		printf("\r\n  C%dδ�յ���BCU����%d\r\n ",j,Coordinator[j].rxCntNow[MAXROUTER_Default+3]);
		#endif
	}
	
	#if defined(PRINT_CC2530TEST_UPDOWNRATE)
	printf("\r\n����ʱ��\r\n");
	print_ECUOnLineTime();
	print_RTC();
	for (uint8_t j=0;j<3;j++)
	{
		printf("\r\nC%d���յ�Ri������ͳ����Ϣ��������ʱ��:%.1fs,ƽ������:%ld,���еð���:%.1f%%,Rmax[%d/%d]=%ld,Rmin[%d,%d]=%ld,%ld��BCU����δ�ϱ���\r\n",\
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
	//CC2530�����ѯ֡
	switch (hRx->rxData[4])
	{
		case CC2530CMD_READ_NET_STATUS:
				if(hRx->rxSize!=6) return;
				if(hRx->rxData[5]==CC2530NETWORK_ERROR)printf("\r\n�豸%dû�м�������\r\n",Cx);
				else if(hRx->rxData[5]==CC2530NETWORK_ENDDEVICE_OK)printf("\r\nEnd Device%d�Ѿ�����\r\n",Cx);
				else if(hRx->rxData[5]==CC2530NETWORK_ROUTER_OK)printf("\r\nRouter%d�Ѿ�����\r\n",Cx);
				else if(hRx->rxData[5]==CC2530NETWORK_CORDINATOR_OK)printf("\r\nCordinator%d�Ѿ�����\r\n",Cx);
		break;
		
		case CC2530CMD_RESET_FACTORY:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d�ָ���������!\r\n",Cx);
				else printf("\r\nC%d�ָ������ɹ�!\r\n",Cx);
		break;
		
		case CC2530CMD_WRITE_PANID:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d PANID���ô���!\r\n",Cx);
				else printf("\r\nC%d PANID���óɹ�!\r\n",Cx);
		break;
		
		case CC2530CMD_READ_PANID:
				if(hRx->rxSize!=8) return;
				else
				{
					if(IS_ECUMODE(ECUMODE_CfgNw))
					{
							//��ѯʱPANID���ش���(������ֵ�����)
							if(	ECUInfo.nwPara.panid_C[Cx] != ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
							{
								printf("\r\nPANID C%d Err,PANID:0x%0X\r\n",Cx,(uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]);
								print_ECUMode();
								if((ECUInfo.nwPara.panid_C[Cx]+0x100) == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
									printf("\r\nC%d����д��ʱ��1��,������������ͻԭ��\r\n",Cx);
							}
							//��ѯʱ�ŵ����ش���(������ֵ�����)
							if(ECUInfo.nwPara.chanel_C[Cx] != hRx->rxData[7])
							{
								ECUInfo.nwPara.confirmTimes[Cx]++;
								printf("\r\nChannel C%d Err\r\n",Cx);
							}
							//��ѯʱPANID�ŵ���������ȷ(������ֵ���)
							if((ECUInfo.nwPara.panid_C[Cx] == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))&&\
								(ECUInfo.nwPara.chanel_C[Cx] == hRx->rxData[7]))
							{
									ClrBit(ECUInfo.nwPara.WriteNw_En,Cx);
									printf("\r\nC%d�������óɹ�,�����顾%d��=��PANID:0x%0X,�ŵ�:0x%0X��\r\n",Cx,ECUInfo.nwPara.nwNum_C[Cx],ECUInfo.nwPara.panid_C[Cx],ECUInfo.nwPara.chanel_C[Cx]);
									print_ECUMode();
									if(ECUInfo.nwPara.WriteNw_En==0)
									{
										ECUInfo.En_IwdgRst=0x01;//��������C�����óɹ��Ÿ�λ
										printf("\r\n�����������,����ģ�����������\r\n");
									}
							}
					}
					else if(IS_ECUMODE(ECUMODE_ReadNw))
					{
							//��ѯʱPANID���ش���(������ֵ�����)
							if(	ECUInfo.nwPara.panid_C[Cx] != ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
							{
								SetBit(ECUInfo.nwPara.WriteNw_En,Cx);
								printf("\r\nPANID C%d Err,PANID:0x%0X\r\n",Cx,(uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]);
								print_ECUMode();
								if((ECUInfo.nwPara.panid_C[Cx]+0x100) == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))
									printf("\r\nC%d����д��ʱ��1��,������������ͻԭ��\r\n",Cx);
							}
							//��ѯʱ�ŵ����ش���(������ֵ�����)
							if(ECUInfo.nwPara.chanel_C[Cx] != hRx->rxData[7])
							{
								ECUInfo.nwPara.confirmTimes[Cx]++;
								printf("\r\nChannel C%d Err\r\n",Cx);
							}
							//��ѯʱPANID�ŵ���������ȷ(������ֵ���)
							if((ECUInfo.nwPara.panid_C[Cx] == ((uint16_t)(hRx->rxData[5]<<8) + hRx->rxData[6]))&&\
								(ECUInfo.nwPara.chanel_C[Cx] == hRx->rxData[7]))
							{
									ClrBit(ECUInfo.nwPara.ReadNw_En,Cx);
									printf("\r\nC%d�����ѯ����,�����顾%d��=��PANID:0x%0X,�ŵ�:0x%0X��\r\n",Cx,ECUInfo.nwPara.nwNum_C[Cx],ECUInfo.nwPara.panid_C[Cx],ECUInfo.nwPara.chanel_C[Cx]);
									print_ECUMode();
									if(ECUInfo.nwPara.ReadNw_En==0)
									{
										ECUMODE_ATTACH(ECUMODE_Normal);
										KEY2EVENT_ATTACH(KEYMODE_NORMAL);
										printf("\r\n�����ѯ���,����ģ�����������\r\n");
										print_ECUMode();
									}
							}
					}
				}
		break;
		
		case CC2530CMD_WRITE_BAUDRATE:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d ���������ô���!\r\n",Cx);
				else printf("\r\nC%d ���������óɹ�!\r\n",Cx);
		break;
		
		case CC2530CMD_WRITE_COMMUNICATION_CHANNEL:
				if(hRx->rxSize!=7) return;
				if((hRx->rxData[5]!=CC2530CMD_OK_0)&&(hRx->rxData[6]!=CC2530CMD_OK_1))printf("\r\nC%d �ŵ����ô���!\r\n",Cx);
				else printf("\r\nC%d �ŵ����óɹ�!\r\n",Cx);
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
/*      ���к���ʵ��	             	                                              */
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
* @�������ƣ�BCUSlave_Proc
* @�������ܣ�
* @���������
*
* @���������void
* @�㷨˼·��
									��������֡��02 A8 79 C3 0A xx yy + "data"
						CC2530�����ѯ֡: 02 A8 79 C3 01/03/04/05/06/09
* @�����õĺ�����
* @ʹ����Դ��
* @ע�����
******************************************************************************/
void vBCUSlave_Proc(void)
{
	vCoordinatorTx_Proc();//TODO��֤���񲻱�����
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

	//�������������еð���ͳ��ʵ��
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

	/* �������� */
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
 * @�������ƣ�CC2530_NWInit
 * @�������ܣ����������ʼ��(PANID,�ŵ�)
 * @���������
 *            1)network_Num_C1
 *            network_Num_C2
 *            network_Num_C3
 * @���������
 *            1)
 * @�㷨˼·��
 * @�����õĺ�����
 * @ʹ����Դ��
 * @ע�����
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
	printf("\r\n��д�벨����=��C1:0x%0X,C2:0x%0X,C3:0x%0X��\r\n",cc2530Baud_C1,cc2530Baud_C2,cc2530Baud_C3);
	return cc2530CmdRet;
}





/*****************************************End of coordinator.c*****************************************/
