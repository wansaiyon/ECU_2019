/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: pc.c
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/02		03:35:42
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#define PC_GLOBALS
//#include "Include.h"
#include "pc.h"

/**********************************************************************************/
/*      ˽�б�������              	                                		      */
/**********************************************************************************/
#if defined(EN_FREERTOS)
#include "cmsis_os.h"
extern osSemaphoreId myCountingSem_C1Handle;
extern osSemaphoreId myCountingSem_C2Handle;
extern osSemaphoreId myCountingSem_C3Handle;
#endif
/**********************************************************************************/
/*      ˽�к�������              	                                              */
/**********************************************************************************/
static void vHostReadCmd0x03( void );
static void vHostReadCmd0x10( void );


/**********************************************************************************/
/*      ˽�к���ʵ��              	                                              */
/**********************************************************************************/
static void vHostReadCmd0x03( void )
{
	uint8_t cmd[255];
	uint16_t tempcrc=0x00;
	
	uint16_t reg_adr=(uint16_t)(Rx_PC.rxData[2]<<8)+Rx_PC.rxData[3];//��ȡ���˼Ĵ�����ַ
	uint16_t 	 reg_cnt =(uint16_t)(Rx_PC.rxData[4]<<8)+Rx_PC.rxData[5];//�Ĵ�������

	//	����ECU��C1 ,C2 ,C3�ŵ���PANID,0x8005-0x800D��
	//	ECU��Cordinator1ͨ���ŵ�	8005
	//	ECU��Cordinator2ͨ���ŵ�	8006
	//	ECU��Cordinator3ͨ���ŵ�	8007
	//	ECU��Cordinator1��PANID	8008
	//	ECU��Cordinator1��PANID_2	8009
	//	ECU��Cordinator2��PANID	800A
	//	ECU��Cordinator2��PANID_2	800B
	//	ECU��Cordinator3��PANID	800C
	//	ECU��Cordinator3��PANID_2	800D
	//	reg_adr=32773,reg_cnt=9
	//	Tx:008-08 03 80 05 00 09 BC 94
	//	Rx:009-08 03 12 00 10 00 11 00 0F 00 1F 00 22 00 25 00 28 00 19 00 1C 83 62
	if(Rx_PC.rxData[2]==0x80 && Rx_PC.rxData[3]==0x05)
	{
		if(reg_cnt==0x09)
		{
			cmd[0]=Rx_PC.rxData[0];
			cmd[1]=Rx_PC.rxData[1];
			cmd[2]=reg_cnt<<1;
			cmd[3]=ECUInfo.nwPara.chanel_C[0]>>8;
			cmd[4]=ECUInfo.nwPara.chanel_C[0];
			cmd[5]=ECUInfo.nwPara.chanel_C[1]>>8;
			cmd[6]=ECUInfo.nwPara.chanel_C[1];
			cmd[7]=ECUInfo.nwPara.chanel_C[2]>>8;
			cmd[8]=ECUInfo.nwPara.chanel_C[2];
			cmd[9]=ECUInfo.nwPara.panid_C[0]>>8;
			cmd[10]=ECUInfo.nwPara.panid_C[0];
			cmd[11]=ECUInfo.nwPara.panid2_C[0]>>8;
			cmd[12]=ECUInfo.nwPara.panid2_C[0];
			cmd[13]=ECUInfo.nwPara.panid_C[1]>>8;
			cmd[14]=ECUInfo.nwPara.panid_C[1];
			cmd[15]=ECUInfo.nwPara.panid2_C[1]>>8;
			cmd[16]=ECUInfo.nwPara.panid2_C[1];
			cmd[17]=ECUInfo.nwPara.panid_C[2]>>8;
			cmd[18]=ECUInfo.nwPara.panid_C[2];
			cmd[19]=ECUInfo.nwPara.panid2_C[2]>>8;
			cmd[20]=ECUInfo.nwPara.panid2_C[2];
			tempcrc=usMBCRC16(cmd,cmd[2]+3);
			cmd[3+cmd[2]]=(uint8_t)tempcrc;
			cmd[4+cmd[2]]=(uint8_t)(tempcrc>>8);
			HAL_UART_Transmit(&PC_Usart,cmd,cmd[2]+5,TimeOut_PC);
		}
	}
	//	�����汾��Ϣ0x80E0-0x80FF TODO:��ȡECUӲ���汾�ţ���ȡBCUӲ���汾�š�
	//	ECU����汾��	80E0~80E4
	//	BCU����汾��	80E5~80E9
	//	ECUӲ���汾��	80EA~80EB
	//	BCUӲ���汾��	80EC~80ED
	//	Ԥ��	80EE~80FF
	//	reg_adr=32992,reg_cnt=10
	//	Tx:882-08 03 80 E0 00 0A ED 62
	//	Rx:883-08 03 14 56 30 30 31 42 30 31 44 31 39 56 30 30 31 42 30 30 44 31 33 A5 E2
	else if(Rx_PC.rxData[2]==0x80 && Rx_PC.rxData[3]==0xE0)
	{
		if(reg_cnt==0x0A)
		{
			cmd[0]=Rx_PC.rxData[0];
			cmd[1]=Rx_PC.rxData[1];
			cmd[2]=reg_cnt<<1;
			memcpy(&cmd[3],ECUInfo.Ver.swVer_ECU,10);
			memcpy(&cmd[13],ECUInfo.Ver.swVer_BCU,10);
			tempcrc=usMBCRC16(cmd,cmd[2]+3);
			cmd[3+cmd[2]]=(uint8_t)tempcrc;
			cmd[4+cmd[2]]=(uint8_t)(tempcrc>>8);
			HAL_UART_Transmit(&PC_Usart,cmd,cmd[2]+5,TimeOut_PC);
//			printf("%s",ECUInfo.Ver.swVer_ECU);
//			printf("%s",ECUInfo.Ver.swVer_BCU);
		}
	}
	//	������ŵ������������Ϣ0x8200~0x8203	TODO:��ȡ©���� ��
	//	������������������������λ��A	8200
	//	������������������ѹ����λ��V	8201
	//	�ŵ����������������������λ��A	8202
	//	�ŵ����������������ѹ����λ��V	8203
	//	©����������������������λ��A	8204
	//	©����������������ѹ����λ��V	8205
	//	Ԥ��	8206~82FF
	//	reg_adr=33280,reg_cnt=4
	//	Tx:037-08 03 82 00 00 04 6C E8
	//	Rx:038-08 03 08 00 C8 00 04 00 32 00 04 A3 4B
	else if(Rx_PC.rxData[2]==0x82 && Rx_PC.rxData[3]==0x00)
	{
		if(reg_cnt==0x04)
		{
			cmd[0]=Rx_PC.rxData[0];
			cmd[1]=Rx_PC.rxData[1];
			cmd[2]=reg_cnt<<1;
			cmd[3]=ECUInfo.hall.HALL_A_Charge>>8;
			cmd[4]=ECUInfo.hall.HALL_A_Charge;
			cmd[5]=ECUInfo.hall.HALL_V_Charge>>8;
			cmd[6]=ECUInfo.hall.HALL_V_Charge;
			cmd[7]=ECUInfo.hall.HALL_A_DisCharge>>8;
			cmd[8]=ECUInfo.hall.HALL_A_DisCharge;
			cmd[9]=ECUInfo.hall.HALL_V_DisCharge>>8;
			cmd[10]=ECUInfo.hall.HALL_V_DisCharge;
			tempcrc=usMBCRC16(cmd,cmd[2]+3);
			cmd[3+cmd[2]]=(uint8_t)(tempcrc);
			cmd[4+cmd[2]]=(uint8_t)(tempcrc>>8);
			HAL_UART_Transmit(&PC_Usart,cmd,cmd[2]+5,TimeOut_PC);
		}
	}
	//	��ECU��ȡ�ɽӵ�״̬ 0x3000~0x300F��
	//	1�Ÿɽӵ㣨���룩	3000
	//	2�Ÿɽӵ㣨���룩	3001
	//	...	...
	//	8�Ÿɽӵ㣨���룩	3007
	//	m�Ÿɽӵ�	3000+m-1
	//	1�Ÿɽӵ㣨�����	3008
	//	...	...
	//	8�Ÿɽӵ㣨�����	300F
	//	Ԥ��	3010~3FFF
	//	reg_adr=12288,reg_cnt=2
	//	Tx:12012-08 03 30 00 00 02 CB 92
	//	Rx:12013-08 03 04 00 01 00 01 F3 33
	else if(reg_adr >=REG_DI_START && reg_adr<REG_DI_END)
	{
		//��������ֻ����ECU��Ӧ�ɽӵ㶯��
		 if(IS_MASTER_ECU() &&(reg_cnt <= 8))//DI:3000~3007,ʵ���õ�DI1:3000
		 {
			cmd[0]=Rx_PC.rxData[0];
			cmd[1]=Rx_PC.rxData[1];
			cmd[2]=reg_cnt<<1;

			uint8_t i;
			for (i = 0; i < reg_cnt; i++)
			{
				cmd[3+i*2]=0x00;
				cmd[4+i*2]=DI(reg_adr-REG_DI_START+i);
			}
			tempcrc=usMBCRC16(cmd,cmd[2]+3);
			cmd[3+cmd[2]]=(uint8_t)(tempcrc);
			cmd[4+cmd[2]]=(uint8_t)(tempcrc>>8);
			HAL_UART_Transmit(&PC_Usart,cmd,cmd[2]+5,TimeOut_PC);
		 }
		 else{
			 printf("\r\nhelloworld\r\n");
		 }
	}
	
	//	���������� 0x600~0x63F TODO:�޸�ECU�Ĵ����汾for(i=0;i<=reg_cnt;i++)Ϊfor(i=0;i<reg_cnt;i++)��
	//	��������˵�ѹ(��1·)	600=1536
	//	��������˵�ѹ(��2·)	601
	//	��������˵�ѹ(��3·)	602
	//	��������˵�ѹ(��4·)	603
	//	��������˵�ѹ(��5·)	604
	//	��������˵�ѹ(��6·)	605
	//	...	...
	//	Ԥ��	60F
	//	��������˳�����(��1·)	610=1552
	//	��������˷ŵ����(��2·)	611
	//	��������˳�����(��3·)	612
	//	��������˷ŵ����(��4·)	613
	//	���������©�����(��5·)	614
	//	���������©�����(��6·)	615
	//	...	...
	//	�����©����(ϵ��0.1mA)ʹ����	618=1560
	//	�����©����(ϵ��0.1mA)	619
	//	...	...
	//	Ԥ��	61F
	//	�����Ļ����¶�(����1)	620=1568
	//	�����Ļ����¶�(����2)	621
	//	�����Ļ����¶�(����3)	622
	//	��	...
	//	Ԥ��	62F
	//	����������׼(��1·)	630=1584
	//	����������׼(��2·) 631
	//	...	...
	//	Ԥ��	63F
	//	reg_adr=1536,reg_cnt=64
	//	Tx:24039-08 03 06 00 00 40 44 2B
	//	Rx:24040-08 03 80 03 27 02 B6 02 A6 02 A5 02 A4 02 A6 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 06 00 00 00 06 00 00 00 02 00 03 00 00 00 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00 02 FE 02 FF 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 E2 8A
	else if(IS_MASTER_ECU() && reg_adr>=REG_GRPDATA_START && reg_adr<REG_GRPDATA_END)	
	{ 
		cmd[0]=Rx_PC.rxData[0];
		cmd[1]=Rx_PC.rxData[1];
		cmd[2]=reg_cnt<<1;
		uint8_t i;
		for(i=0;i<reg_cnt;i++)
		{
			cmd[3+i*2]=BattData[reg_adr+i]>>8;
			cmd[4+i*2]=BattData[reg_adr+i]&0xFF;
		}
		tempcrc=usMBCRC16(cmd,cmd[2]+3);
		cmd[3+cmd[2]]=(uint8_t)(tempcrc);
		cmd[4+cmd[2]]=(uint8_t)(tempcrc>>8);
		HAL_UART_Transmit(&PC_Usart,cmd,cmd[2]+5,TimeOut_PC);
	}
	
	//	������������������������,0x1000-0x2000	TODO:�޸ļĴ����汾(reg_adr-REG_CELL1DATA_START)/8+1Ϊ(reg_adr-REG_CELL1DATA_START)/8��
	//	1�ŵ����ص�ѹ	1000=4096
	//	1�ŵ���������	1001
	//	1�ŵ������¶�	1002
	//	1�ŵ���״̬	1003
	//	1#��������׼, ��׼��Чʱ��0xFFFF	1004
	//	1�ŵ����ص�ѹУ׼ϵ��k	1005
	//	1�ŵ����ص�ѹУ׼ϵ��b	1006
	//	1�ŵ������¶�У׼ϵ��b	1007
	//	Ԥ��	1005-1007
	//	...	...
	//	2�ŵ����ص�ѹ	1008=4104
	//	2�ŵ���������	1009
	//	2�ŵ������¶�	100A
	//	2�ŵ���״̬	100B
	//	2#��������׼, ��׼��Чʱ��0xFFFF	100C
	//	Ԥ��	100D~100F
	//	...	...
	//	m�ŵ����ص�ѹ	1000+(m-1)*8+0
	//	m�ŵ���������	1000+(m-1)*8+1
	//	m�ŵ������¶�	1000+(m-1)*8+2
	//	m�ŵ���״̬	1000+(m-1)*8+3
	//	m#��������׼, ��׼��Чʱ��0xFFFF	1000+(m-1)*8+4
	//	Ԥ��	1000+(m-1)*8+5
	//		~
	//	1000+(m-1)*8+7
	//	...	...
	//	500�ŵ����ص�ѹ	1F98=8088
	//	500�ŵ���������	1F99
	//	500�ŵ������¶�	1F9A
	//	500�ŵ���״̬	1F9B
	//	500�ŵ�������׼, ��׼��Чʱ��0xFFFF	1F9C
	//	Ԥ��	1F9D ~1F9F
	//	...	...
	//	reg_adr=4096+(81-1)*8+0=4736,reg_cnt=8*4=32
	//	Tx:24067-08 03 10 00 00 78 41 B1
	//	Rx:24068-08 03 F0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 83 44
	else if(reg_adr>=ECUInfo.bcuRegAddr[0] && reg_adr<=ECUInfo.bcuRegAddr[1])
	{
		if(reg_cnt>125) reg_cnt=125;
		cmd[0]=Rx_PC.rxData[0];
		cmd[1]=Rx_PC.rxData[1];
		cmd[2]=reg_cnt<<1;
		memcpy(&cmd[3],&BCUData[(reg_adr-REG_CELL1DATA_START)/8].U,reg_cnt<<1);
		tempcrc=usMBCRC16(cmd,cmd[2]+3);
		cmd[3+cmd[2]]=(uint8_t)(tempcrc);
		cmd[4+cmd[2]]=(uint8_t)(tempcrc>>8);
		HAL_UART_Transmit(&PC_Usart,cmd,cmd[2]+5,TimeOut_PC);
	}
	//	������ѹ�����������������¶�������������,0x0000-0x0600��
	//	������BCU[1]����1#��أ�TODO �Ĵ����汾�޸�	0000
	//	1�ŵ����ص�ѹ	0001
	//	2�ŵ����ص�ѹ	0002
	//	m�ŵ����ص�ѹ	m
	//	��	��
	//	500�ŵ����ص�ѹ	01F4
	//	Ԥ��
	//	1�ŵ���������	200=512
	//	2�ŵ���������	201
	//	��	��
	//	m�ŵ���������	200+��m-1��
	//	��	��
	//	500�ŵ���������	03F3
	//	Ԥ��
	//	1�ŵ������¶�	400=1024
	//	2�ŵ������¶�
	//	��	��
	//	m�ŵ������¶�	400+��m-1��
	//	��	��
	//	500�ŵ������¶�	05F3
	//	Ԥ��
	else if((reg_adr>=ECUInfo.bcuRegAddr[4] && reg_adr<=ECUInfo.bcuRegAddr[5])||\
			(reg_adr>=ECUInfo.bcuRegAddr[6] && reg_adr<=ECUInfo.bcuRegAddr[7])||\
			(reg_adr>=ECUInfo.bcuRegAddr[8] && reg_adr<=ECUInfo.bcuRegAddr[9])||\
			(reg_adr>=ECUInfo.bcuRegAddr[10] && reg_adr<=ECUInfo.bcuRegAddr[11])||\
			(reg_adr>=ECUInfo.bcuRegAddr[12] && reg_adr<=ECUInfo.bcuRegAddr[13])||\
			(reg_adr>=ECUInfo.bcuRegAddr[14] && reg_adr<=ECUInfo.bcuRegAddr[15]))
	{
		if(reg_cnt>125) reg_cnt=125;
		cmd[0]=Rx_PC.rxData[0];
		cmd[1]=Rx_PC.rxData[1];
		cmd[2]=reg_cnt<<1;
		uint8_t i;
		for(i=0;i<reg_cnt;i++)
		{
			//�Ѿ��ڽ���ʱת���ˣ�������ת��һ��
			cmd[3+i*2]=BattData[reg_adr+i]&0xFF;
			cmd[4+i*2]=BattData[reg_adr+i]>>8;
		}
		tempcrc=usMBCRC16(cmd,cmd[2]+3);
		cmd[3+cmd[2]]=(uint8_t)(tempcrc);
		cmd[4+cmd[2]]=(uint8_t)(tempcrc>>8);
		HAL_UART_Transmit(&PC_Usart,cmd,cmd[2]+5,TimeOut_PC);
	}
}

static void vHostReadCmd0x10( void )
{ 
	uint8_t cmd[10];
	uint16_t tempcrc;
	uint16_t reg_adr =(uint16_t)(Rx_PC.rxData[2]<<8)+Rx_PC.rxData[3];//�Ĵ�����ַ
	uint16_t reg_cnt =(uint16_t)(Rx_PC.rxData[4]<<8)+Rx_PC.rxData[5];//�Ĵ�������
	uint16_t data_cnt=Rx_PC.rxData[6];//�ֽ�����

	
 if(data_cnt==(reg_cnt<<1))
 {
	 //��TOTO ֧����������һ������ȫ����ReadNw_En  PC��ECU�·��ӻ���ַ����ؽ���������������������졿
	 //reg_adr=16640,reg_cnt=5
	 //15 120 6 7 5 = 08 10 41 00 00 05 0A 00 0F 00 78 00 06 00 07 00 05 16 AF
	 //15 120 4 7 5 = 08 10 41 00 00 05 0A 00 0F 00 78 00 04 00 07 00 05 6F 6F
	 //8  120 6 7 5
	 //Tx:094-08 10 41 00 00 05 0A 00 08 00 78 00 06 00 07 00 05 30 9F
	 //Rx:095-08 10 41 00 00 05 14 AF
	 if(reg_adr==REG_NUMECU && IS_KEY1MODE(KEYMODE_SETECUID))
	 {
		 if(reg_cnt!=5)return;
		 
		 /* Start Protocol Analysis */
		 ECUInfo.slaveID=((uint16_t)(Rx_PC.rxData[7]<<8)+Rx_PC.rxData[8]);
		 ECUInfo.battJarNum =((uint16_t)(Rx_PC.rxData[9]<<8)+Rx_PC.rxData[10]);
		 ECUInfo.nwPara.nwNum_C[0]=((uint16_t)(Rx_PC.rxData[11]<<8)+Rx_PC.rxData[12]);
		 ECUInfo.nwPara.nwNum_C[1]=((uint16_t)(Rx_PC.rxData[13]<<8)+Rx_PC.rxData[14]);
		 ECUInfo.nwPara.nwNum_C[2]=((uint16_t)(Rx_PC.rxData[15]<<8)+Rx_PC.rxData[16]);
		 
		 /* Start Coordinator Configuration*/
		 //�յ��˾ͽ��������������ڳ�����������ȥ�������ߣ�����Ҫ�����߲���������Ч���ٻ�Ӧ��֡
		 //ע�⣺��̨�������һֱ��д��������ʹ��ECUInfo.nwPara.WriteNw_En����Ӧ�����̨��֡���˿��ܵ������벻��������
		 //TODO:ECU��ųɹ�һ��Ҫ���縴λ
			ECUInfo.nwPara.WriteNw_En =WRITENW_C1_EN|WRITENW_C2_EN|WRITENW_C3_EN;
		 
		 /* Start Save */
		hW25Qx.wData[0]=ECUInfo.slaveID;
		hW25Qx.wData[1]=ECUInfo.battJarNum;
		hW25Qx.wData[2]=ECUInfo.nwPara.nwNum_C[0];
		hW25Qx.wData[3]=ECUInfo.nwPara.nwNum_C[1];
		hW25Qx.wData[4]=ECUInfo.nwPara.nwNum_C[2];
		tempcrc=usMBCRC16(hW25Qx.wData,5);
		hW25Qx.wData[5]=(uint8_t)tempcrc;
		hW25Qx.wData[6]=(uint8_t)(tempcrc>>8);
		if(ucBSP_W25Qx_Erase_Block(0) == W25Qx_OK)
		{
			ucBSP_W25Qx_Write(hW25Qx.wData,0,7);
			memcpy(&cmd[0],&Rx_PC.rxData[0],6);
			tempcrc=usMBCRC16(cmd,6);
			cmd[6]=(uint8_t)tempcrc;
			cmd[7]=(uint8_t)(tempcrc>>8);
			HAL_UART_Transmit(&PC_Usart,cmd,8,TimeOut_PC);
		}
		else
		{
			Error_Handler();
		}
	 }
	 //PC��ECU�·������������
	 if(Rx_PC.rxData[2]==0x81 && Rx_PC.rxData[3]==0x00)
	 {
	 }
	 //PC��ECU�·������ؽ�����������
	 if(reg_adr >=REG_CELLOP_START && reg_adr<REG_CELLOP_END)
	 {
		 // 08 10 20 00 00 03 06 00 04 00 04 00 04
		 if(reg_adr>=ECUInfo.bcuRegAddr[2] && reg_adr<=ECUInfo.bcuRegAddr[3])
		 {
		 }
	 }
	 //��PC��ECU�ķ��������в�����
	 //reg_adr=16432
	 if(reg_adr ==REG_TEST_BEEP)
	 {
		if(reg_cnt!=0x01) return;
		if(((uint16_t)(Rx_PC.rxData[7]<<8)+Rx_PC.rxData[8])==0x01)
			HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_SET);
		else if(((uint16_t)(Rx_PC.rxData[7]<<8)+Rx_PC.rxData[8])==0x00)
			HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET);
		memcpy(&cmd[0],&Rx_PC.rxData[0],6);
		tempcrc=usMBCRC16(cmd,6);
		cmd[6]=(uint8_t)(tempcrc>>8);
		cmd[7]=(uint8_t)tempcrc;
		HAL_UART_Transmit(&PC_Usart,cmd,8,TimeOut_PC);
	 }
	//ֻ����ECU��ӦУ׼������ô�������������
	if(IS_MASTER_ECU())
	{
		 //���ѹУ׼
		 if(reg_adr >= REG_V_CALIB_START && reg_adr <= REG_V_CALIB_END)
		 {
		 }
			
		 //�����У׼
		 if(reg_adr >= REG_I_CALIB_START && reg_adr <= REG_I_CALIB_END)
		 {
		 }
		 //�����¶�У׼
		 if(reg_adr >= REG_T_CALIB_START && reg_adr <= REG_T_CALIB_END)
		 {
		 }
		 //PC��ECU�·����õ�����������Ϣ
		 if(Rx_PC.rxData[2]==0x82 && Rx_PC.rxData[3]==0x00 \
			 && Rx_PC.rxData[4]==0x00 && Rx_PC.rxData[5]==0x04)
		 {
		 }
		 //PCдECU��D0
		 if(reg_adr >=REG_DO_START && reg_adr<=REG_DO_END)
		 {
			 //��������ֻ����ECU��Ӧ�ɽӵ㶯��
			 if(reg_cnt <= 8)//DO:3008~300F,ʵ���õ�DO1:3008,DO2:3009
			 {
			 }
		 }
	}
//	memcpy(&cmd[0],&Rx_PC.rxData[0],6);
//	tempcrc=usMBCRC16(cmd,6);
//	cmd[6]=(uint8_t)(tempcrc>>8);
//	cmd[7]=(uint8_t)tempcrc;
//	HAL_UART_Transmit(&PC_Usart,cmd,8,10);
    
 }
 else
 {
	 Error_Handler();
 }
 
}



/**********************************************************************************/
/*      ���к���ʵ��	             	                                              */
/**********************************************************************************/
void vPCHost_Proc(void)
{
	if(Rx_PC.rxFlag)
	{
		Rx_PC.rxFlag=0;
//		HAL_UART_Transmit485(&PC_Usart,Rx_PC.rxData,Rx_PC.rxSize,TimeOut_PC);//TODO :When You Want To Test Loop Mode
		switch (Rx_PC.rxData[1])
		{
			case MODBUSRTU_FUNCODE_0X03:
				if(usMBCRC16(&Rx_PC.rxData[0],0x08)==0)
				{
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					vHostReadCmd0x03();
				}
			break;

			case MODBUSRTU_FUNCODE_0X10:
				if(usMBCRC16(&Rx_PC.rxData[0],Rx_PC.rxSize)==0)
				{
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					vHostReadCmd0x10();
				}
			break;
			default:
			break;
		}
	}
}

/**
  * @brief  This function handles USART IDLE interrupt.
  */
void vUsartReceive_IDLE(UART_HandleTypeDef *huart ,UsartxDMARx_TypeDef *hRx)
{  
    uint32_t temp;  
  
    if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))  
    {   
		__HAL_UART_CLEAR_IDLEFLAG(huart);
		HAL_UART_DMAStop(huart);
		temp = huart->hdmarx->Instance->NDTR;
		hRx->rxSize =  USARTX_RXSIZE - temp;
		hRx->rxFlag = 1;

#if defined(EN_FREERTOS)
		//TODO :Higher Priority?
		if(huart==&Coordinator1_Usart)
			osSemaphoreRelease(myCountingSem_C1Handle);
		else if(huart==&Coordinator2_Usart)
			osSemaphoreRelease(myCountingSem_C2Handle);
		else if(huart==&Coordinator3_Usart)
			osSemaphoreRelease(myCountingSem_C3Handle);
#endif
		HAL_UART_Receive_DMA(huart,hRx->rxData,USARTX_RXSIZE);
    }  
}

//TODO :Test
HAL_StatusTypeDef eHAL_UART_TransmitPC(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	HAL_StatusTypeDef ret;
#if defined(EN_RS485)
	ret=eHAL_UART_Transmit485(huart, pData, Size, Timeout);
#else
	ret=HAL_UART_Transmit(huart, pData, Size, Timeout);
#endif
	return ret;
}

HAL_StatusTypeDef eHAL_UART_Transmit485(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	HAL_StatusTypeDef ret;
	
	RS485_TX_MODE();
	ret=HAL_UART_Transmit(huart, pData, Size, Timeout);
	RS485_RX_MODE();
	return ret;
}

/*****************************************End of pc.c*****************************************/
