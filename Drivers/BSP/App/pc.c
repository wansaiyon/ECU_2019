/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: pc.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/02		03:35:42
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define PC_GLOBALS
//#include "Include.h"
#include "pc.h"

/**********************************************************************************/
/*      私有变量声明              	                                		      */
/**********************************************************************************/
#if defined(EN_FREERTOS)
#include "cmsis_os.h"
extern osSemaphoreId myCountingSem_C1Handle;
extern osSemaphoreId myCountingSem_C2Handle;
extern osSemaphoreId myCountingSem_C3Handle;
#endif
/**********************************************************************************/
/*      私有函数声明              	                                              */
/**********************************************************************************/
static void vHostReadCmd0x03( void );
static void vHostReadCmd0x10( void );


/**********************************************************************************/
/*      私有函数实现              	                                              */
/**********************************************************************************/
static void vHostReadCmd0x03( void )
{
	uint8_t cmd[255];
	uint16_t tempcrc=0x00;
	
	uint16_t reg_adr=(uint16_t)(Rx_PC.rxData[2]<<8)+Rx_PC.rxData[3];//获取到了寄存器地址
	uint16_t 	 reg_cnt =(uint16_t)(Rx_PC.rxData[4]<<8)+Rx_PC.rxData[5];//寄存器数量

	//	【读ECU中C1 ,C2 ,C3信道与PANID,0x8005-0x800D】
	//	ECU中Cordinator1通信信道	8005
	//	ECU中Cordinator2通信信道	8006
	//	ECU中Cordinator3通信信道	8007
	//	ECU中Cordinator1的PANID	8008
	//	ECU中Cordinator1的PANID_2	8009
	//	ECU中Cordinator2的PANID	800A
	//	ECU中Cordinator2的PANID_2	800B
	//	ECU中Cordinator3的PANID	800C
	//	ECU中Cordinator3的PANID_2	800D
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
	//	【读版本信息0x80E0-0x80FF TODO:读取ECU硬件版本号，读取BCU硬件版本号】
	//	ECU软件版本号	80E0~80E4
	//	BCU软件版本号	80E5~80E9
	//	ECU硬件版本号	80EA~80EB
	//	BCU硬件版本号	80EC~80ED
	//	预留	80EE~80FF
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
	//	【读充放电电流传感器信息0x8200~0x8203	TODO:读取漏电流 】
	//	充电电流传感器额定输入电流，单位：A	8200
	//	充电电流传感器额定输出电压，单位：V	8201
	//	放电电流传感器额定输入电流，单位：A	8202
	//	放电电流传感器额定输出电压，单位：V	8203
	//	漏电流传感器额定输入电流，单位：A	8204
	//	漏电流传感器额定输出电压，单位：V	8205
	//	预留	8206~82FF
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
	//	【ECU读取干接点状态 0x3000~0x300F】
	//	1号干接点（输入）	3000
	//	2号干接点（输入）	3001
	//	...	...
	//	8号干接点（输入）	3007
	//	m号干接点	3000+m-1
	//	1号干接点（输出）	3008
	//	...	...
	//	8号干接点（输出）	300F
	//	预留	3010~3FFF
	//	reg_adr=12288,reg_cnt=2
	//	Tx:12012-08 03 30 00 00 02 CB 92
	//	Rx:12013-08 03 04 00 01 00 01 F3 33
	else if(reg_adr >=REG_DI_START && reg_adr<REG_DI_END)
	{
		//昆兰储能只有主ECU响应干接点动作
		 if(IS_MASTER_ECU() &&(reg_cnt <= 8))//DI:3000~3007,实际用到DI1:3000
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
	
	//	【读组数据 0x600~0x63F TODO:修改ECU寄存器版本for(i=0;i<=reg_cnt;i++)为for(i=0;i<reg_cnt;i++)】
	//	电池组的组端电压(第1路)	600=1536
	//	电池组的组端电压(第2路)	601
	//	电池组的组端电压(第3路)	602
	//	电池组的组端电压(第4路)	603
	//	电池组的组端电压(第5路)	604
	//	电池组的组端电压(第6路)	605
	//	...	...
	//	预留	60F
	//	电池组的组端充电电流(第1路)	610=1552
	//	电池组的组端放电电流(第2路)	611
	//	电池组的组端充电电流(第3路)	612
	//	电池组的组端放电电流(第4路)	613
	//	电池组的组端漏电电流(第5路)	614
	//	电池组的组端漏电电流(第6路)	615
	//	...	...
	//	电池组漏电流(系数0.1mA)使用中	618=1560
	//	电池组漏电流(系数0.1mA)	619
	//	...	...
	//	预留	61F
	//	电池组的环境温度(检测点1)	620=1568
	//	电池组的环境温度(检测点2)	621
	//	电池组的环境温度(检测点3)	622
	//	…	...
	//	预留	62F
	//	电池组内阻基准(第1路)	630=1584
	//	电池组内阻基准(第2路) 631
	//	...	...
	//	预留	63F
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
	
	//	【读物理量不连续单体数据,0x1000-0x2000	TODO:修改寄存器版本(reg_adr-REG_CELL1DATA_START)/8+1为(reg_adr-REG_CELL1DATA_START)/8】
	//	1号单体电池电压	1000=4096
	//	1号单体电池内阻	1001
	//	1号单体电池温度	1002
	//	1号单体状态	1003
	//	1#电池内阻基准, 基准无效时填0xFFFF	1004
	//	1号单体电池电压校准系数k	1005
	//	1号单体电池电压校准系数b	1006
	//	1号单体电池温度校准系数b	1007
	//	预留	1005-1007
	//	...	...
	//	2号单体电池电压	1008=4104
	//	2号单体电池内阻	1009
	//	2号单体电池温度	100A
	//	2号单体状态	100B
	//	2#电池内阻基准, 基准无效时填0xFFFF	100C
	//	预留	100D~100F
	//	...	...
	//	m号单体电池电压	1000+(m-1)*8+0
	//	m号单体电池内阻	1000+(m-1)*8+1
	//	m号单体电池温度	1000+(m-1)*8+2
	//	m号单体状态	1000+(m-1)*8+3
	//	m#电池内阻基准, 基准无效时填0xFFFF	1000+(m-1)*8+4
	//	预留	1000+(m-1)*8+5
	//		~
	//	1000+(m-1)*8+7
	//	...	...
	//	500号单体电池电压	1F98=8088
	//	500号单体电池内阻	1F99
	//	500号单体电池温度	1F9A
	//	500号单体状态	1F9B
	//	500号电池内阻基准, 基准无效时填0xFFFF	1F9C
	//	预留	1F9D ~1F9F
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
	//	【读电压连续、内阻连续、温度连续单体数据,0x0000-0x0600】
	//	保留（BCU[1]代表1#电池）TODO 寄存器版本修改	0000
	//	1号单体电池电压	0001
	//	2号单体电池电压	0002
	//	m号单体电池电压	m
	//	…	…
	//	500号单体电池电压	01F4
	//	预留
	//	1号单体电池内阻	200=512
	//	2号单体电池内阻	201
	//	…	…
	//	m号单体电池内阻	200+（m-1）
	//	…	…
	//	500号单体电池内阻	03F3
	//	预留
	//	1号单体电池温度	400=1024
	//	2号单体电池温度
	//	…	…
	//	m号单体电池温度	400+（m-1）
	//	…	…
	//	500号单体电池温度	05F3
	//	预留
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
			//已经在接收时转换了，这里再转换一次
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
	uint16_t reg_adr =(uint16_t)(Rx_PC.rxData[2]<<8)+Rx_PC.rxData[3];//寄存器地址
	uint16_t reg_cnt =(uint16_t)(Rx_PC.rxData[4]<<8)+Rx_PC.rxData[5];//寄存器数量
	uint16_t data_cnt=Rx_PC.rxData[6];//字节数量

	
 if(data_cnt==(reg_cnt<<1))
 {
	 //【TOTO 支持配置任意一个或者全配置ReadNw_En  PC对ECU下发从机地址、电池节数、网络参数，按键认领】
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
		 //收到了就将参数保存起来在程序里面慢慢去操作无线，并不要等无线参数真正生效了再回应答帧
		 //注意：后台在这里会一直将写参数进行使能ECUInfo.nwPara.WriteNw_En，若应答给后台的帧丢了可能导致意想不到的问题
		 //TODO:ECU编号成功一定要尽早复位
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
	 //PC对ECU下发检测内阻命令
	 if(Rx_PC.rxData[2]==0x81 && Rx_PC.rxData[3]==0x00)
	 {
	 }
	 //PC对ECU下发单体电池交互操作命令
	 if(reg_adr >=REG_CELLOP_START && reg_adr<REG_CELLOP_END)
	 {
		 // 08 10 20 00 00 03 06 00 04 00 04 00 04
		 if(reg_adr>=ECUInfo.bcuRegAddr[2] && reg_adr<=ECUInfo.bcuRegAddr[3])
		 {
		 }
	 }
	 //【PC对ECU的蜂鸣器进行操作】
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
	//只有主ECU响应校准命令，配置传感器参数命令
	if(IS_MASTER_ECU())
	{
		 //组电压校准
		 if(reg_adr >= REG_V_CALIB_START && reg_adr <= REG_V_CALIB_END)
		 {
		 }
			
		 //组电流校准
		 if(reg_adr >= REG_I_CALIB_START && reg_adr <= REG_I_CALIB_END)
		 {
		 }
		 //环境温度校准
		 if(reg_adr >= REG_T_CALIB_START && reg_adr <= REG_T_CALIB_END)
		 {
		 }
		 //PC对ECU下发配置电流传感器信息
		 if(Rx_PC.rxData[2]==0x82 && Rx_PC.rxData[3]==0x00 \
			 && Rx_PC.rxData[4]==0x00 && Rx_PC.rxData[5]==0x04)
		 {
		 }
		 //PC写ECU的D0
		 if(reg_adr >=REG_DO_START && reg_adr<=REG_DO_END)
		 {
			 //昆兰储能只有主ECU响应干接点动作
			 if(reg_cnt <= 8)//DO:3008~300F,实际用到DO1:3008,DO2:3009
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
/*      公有函数实现	             	                                              */
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
