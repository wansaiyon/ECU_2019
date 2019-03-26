/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: ecu.c
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/02		04:39:41
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#define ECU_GLOBALS
//#include "Include.h"
#include "ecu.h"

/**********************************************************************************/
/*      ˽�б�������              	                                		      */
/**********************************************************************************/
//�����������ͺŶ���
/**
* @�ṹ�幦��  ���������������ṹ��

Table_ECUHall[0]:�����������������������λA
Table_ECUHall[1]:�����������������ѹ����λV
Table_ECUHall[2]:�ŵ���������������������λA
Table_ECUHall[3]:�ŵ���������������ѹ����λV
Table_ECUHall[4]:©����������������������λmA
Table_ECUHall[5]:©����������������ѹ����λV
*/
const uint16_t Table_ECUHall[6]={200,4,50,4,100,5};

static const EventDoWithTable_TypeDef astDoWithTable[]=
{
		{TASK_EVENT_BIT00,vDoWithEvent00},
		{TASK_EVENT_BIT01,vDoWithEvent01},
		{TASK_EVENT_BIT02,vDoWithEvent02},
		{TASK_EVENT_BIT03,vDoWithEvent03},
		{TASK_EVENT_BIT04,vDoWithEvent04},
		{TASK_EVENT_BIT05,vDoWithEvent05},
		{TASK_EVENT_BIT06,vDoWithEvent06},
		{TASK_EVENT_BIT07,vDoWithEvent07},
		{TASK_EVENT_BIT08,vDoWithEvent08},
};


/**********************************************************************************/
/*      ˽�к�������              	                                              */
/**********************************************************************************/
static void vEvent_Proc(void);


/**********************************************************************************/
/*      ˽�к���ʵ��              	                                              */
/**********************************************************************************/
static void vEvent_Proc(void)
{
	UNUSED(vEvent_Proc);// TODO :Call it
	uint8_t i;
	for(i=0;i<sizeof(astDoWithTable)/sizeof(astDoWithTable[0]);i++)
	{
		if((ulEventBits&astDoWithTable[i].ulEventBit)&&(astDoWithTable[i].pFun!=NULL))
		{
			(*astDoWithTable[i].pFun)();
		}
	}
}




/**********************************************************************************/
/*      ���к���ʵ��	             	                                              */
/**********************************************************************************/
void vECUPara_Init(void)
{	
	ECUInfo.baud =BAUD_C_Default;	
	if(ECUInfo.battJarNum==0xff)
	{
		ECUInfo.battJarNum =BATTJARNUM_Default;
	}
	//modbusAddr,ID,bias
	if(ECUInfo.slaveID==0xff)
	{
		ECUInfo.slaveID =SLAVEID_Default;
	}
	ECUInfo.ECUID =(ECUInfo.slaveID % 8)+1;
	if((ECUInfo.ECUID>6)||(ECUInfo.slaveID<8))ECUInfo.ECUID=0x01;
	ECUInfo.bias=3*MAXROUTER_Default*(ECUInfo.ECUID-1);

	//cc2530 network
	if(ECUInfo.nwPara.nwNum_C[0]==0xff ||\
		ECUInfo.nwPara.nwNum_C[1]==0xff ||\
		ECUInfo.nwPara.nwNum_C[2]==0xff)
	{
		ECUInfo.nwPara.nwNum_C[0]=NWPARA_C1_Default;
		ECUInfo.nwPara.nwNum_C[1]=NWPARA_C2_Default;
		ECUInfo.nwPara.nwNum_C[2]=NWPARA_C3_Default;
	}	
	eNwNum2PANID(ECUInfo.nwPara.nwNum_C[0],ECUInfo.nwPara.nwNum_C[1],ECUInfo.nwPara.nwNum_C[2]);
	ECUInfo.nwPara.jarNum_C[0]=JARNUM_C1_Default;
	ECUInfo.nwPara.jarNum_C[1]=JARNUM_C1_Default;
	ECUInfo.nwPara.jarNum_C[2]=JARNUM_C1_Default;
	
	
	//version
	ECUInfo.Ver.voltLevel=VOLTLEVEL_Default;
	ECUInfo.Ver.swVer_ECU ="V001B00D00";
	ECUInfo.Ver.swVer_BCU ="V001B00D13";
	ECUInfo.Ver.hwVer_ECU ="V2.0";
	ECUInfo.Ver.hwVer_BCU ="V4.0";
#if defined(EN_FREERTOS)
	ECUInfo.Ver.osVer_ECU ="FreeRTOS V9.0.0";
#else
	ECUInfo.Ver.osVer_ECU ="	  		   ";
#endif
	
	//sensor
	ECUInfo.hall.HALL_A_Charge=HALL_A_Default(0);
	ECUInfo.hall.HALL_V_Charge=HALL_V_Default(0);
	ECUInfo.hall.HALL_A_DisCharge=HALL_A_Default(1);
	ECUInfo.hall.HALL_V_DisCharge=HALL_V_Default(1);
	ECUInfo.hall.HALL_A_LeakageCurr=HALL_A_Default(2);
	ECUInfo.hall.HALL_V_LeakageCurr=HALL_V_Default(2);
	ECUInfo.grpData.s_kHall[0]=HALL_K_Default(0);
	ECUInfo.grpData.s_kHall[1]=HALL_K_Default(1);
	ECUInfo.grpData.s_kHall[2]=HALL_K_Default(2);
	
	//protocol coefficient
	ECUInfo.grpData.p_bU=0;
	ECUInfo.grpData.p_kU=10.0f;
	ECUInfo.grpData.p_bI=0;
	ECUInfo.grpData.p_kI=10.0f;
	#if T_LOOKUPTABLE==(1)
	ECUInfo.grpData.p_bT=0;
	ECUInfo.grpData.p_kT=1.0f;
	#elif T_LOOKUPTABLE==(0)
	ECUInfo.grpData.p_bT=500;
	ECUInfo.grpData.p_kT=10.0f;
	#endif
	
	//multiple ECU application
	//�����ض�ECUӦ�ó�����ECU��Ӧ��̨��ȡ������������������
	ECUInfo.bcuRegAddr[0] = ECU_REG_START(ECUInfo.ECUID,1,8);//0x1000-0x2000	�����ѹ�����衢�¶�	��1��
	ECUInfo.bcuRegAddr[1] = ECU_REG_END(ECUInfo.ECUID,1,8);
	ECUInfo.bcuRegAddr[2] = ECU_REG_START(ECUInfo.ECUID,2,1);//0x2000-0x3000	�������			��1��
	ECUInfo.bcuRegAddr[3] = ECU_REG_END(ECUInfo.ECUID,2,1);

	ECUInfo.bcuRegAddr[4] = ECU_REG_START2(ECUInfo.ECUID,0,1);//0x0000-0x0200	�����ѹ			��2��
	ECUInfo.bcuRegAddr[5] = ECU_REG_END2(ECUInfo.ECUID,0,1);
	ECUInfo.bcuRegAddr[6] = ECU_REG_START2(ECUInfo.ECUID,1,1);//0x0200-0x0400	��������			��2��
	ECUInfo.bcuRegAddr[7] = ECU_REG_END2(ECUInfo.ECUID,1,1);
	ECUInfo.bcuRegAddr[8] = ECU_REG_START2(ECUInfo.ECUID,2,1);//0x0400-0x0600	�����¶�			��2��
	ECUInfo.bcuRegAddr[9] = ECU_REG_END2(ECUInfo.ECUID,2,1);

	ECUInfo.bcuRegAddr[10] = ECU_REG_START3(ECUInfo.ECUID,0,1);//0x0640-0x0840	���������׼		��3��
	ECUInfo.bcuRegAddr[11] = ECU_REG_END3(ECUInfo.ECUID,0,1);
	ECUInfo.bcuRegAddr[12] = ECU_REG_START3(ECUInfo.ECUID,1,1);//0x0840-0x0A40	����״̬			��3��
	ECUInfo.bcuRegAddr[13] = ECU_REG_END3(ECUInfo.ECUID,1,1);
	ECUInfo.bcuRegAddr[14] = ECU_REG_START3(ECUInfo.ECUID,2,1);//0x0A40-0x0C40	����SOC			��3��
	ECUInfo.bcuRegAddr[15] = ECU_REG_END3(ECUInfo.ECUID,2,1);

	if(ECUInfo.ECUID==5)
	{
		ECUInfo.bcuRegAddr[0] = 0x1F00;
		ECUInfo.bcuRegAddr[1] = 0x1FA0;	
		ECUInfo.bcuRegAddr[2] = 0x21E0;
		ECUInfo.bcuRegAddr[3] = 0x21F3;		
	}
	
	//ECU��д���������
	ECUInfo.nwPara.periodWriteNw=Period_WriteNw_Default;
	ECUInfo.nwPara.periodReadNw=Period_ReadNw_Default;
	
	//�á�BCD���ơ�+���������д�������ϱ��ECU�Ĵ�վ��
	ECUInfo.ledBCDNum =((ECUInfo.slaveID%0x0F)==0)?0x0F:(ECUInfo.slaveID%0x0F);
	ECUInfo.BeepNum = (ECUInfo.slaveID-1)/15;
}

void vPrint_ECUInformation( void )
{
	printf("*******(C) COPYRIGHT WANSAIYON 2019-09-29 ***********\r\n");
	printf("*                                                  \r\n");
	printf("*             ��һ. ECU Information��              \r\n");
	printf("*                                                  \r\n");
	printf("*******************��1����Ӳ���汾��*****************\r\n");
	printf("*                                                  \r\n");
	printf("*         ECUϵͳ�汾��%s	          							 \r\n",ECUInfo.Ver.osVer_ECU);
	printf("*         ECU����汾��%s	          							 \r\n",ECUInfo.Ver.swVer_ECU);
	printf("*         BCU����汾��%s	  	    								 \r\n",ECUInfo.Ver.swVer_BCU);
	printf("*         ECUӲ���汾��%s	          							 \r\n",ECUInfo.Ver.hwVer_ECU);
	printf("*         BCUӲ���汾��%s		        							 \r\n",ECUInfo.Ver.hwVer_BCU);
	if(ECUInfo.Ver.voltLevel==LOWVOLT)
	printf("*         ECU��ѹ��ⷶΧ��0-125V                  \r\n");
  else if(ECUInfo.Ver.voltLevel==HIGHVOLT)
  printf("*         ECU��ѹ��ⷶΧ��125V-850V               \r\n");
	printf("*                                                  \r\n");
	printf("*******************��2��Ӳ����Դ����*****************\r\n");
	printf("*                                                  \r\n");
	printf("*         MCU�ͺţ�STM32F407ZET6                   \r\n");
	/* Start SPI W25Q16 */
#if defined(EN_W25Q16)
	vLoad_FlashMemory();
#endif
	printf("*         SRAM Is Err!                             \r\n");	
	printf("*         CAN Is Err!                              \r\n");	
	printf("*         USBCDC Is OK!                            \r\n");
	printf("*                                                  \r\n");
	printf("*******************��3��ECU����**********************\r\n");
	printf("*                                                  \r\n");
	printf("*         ��վ�ţ�%d                        			 \r\n",ECUInfo.slaveID);
	printf("*         ECUID�ţ�%d                              \r\n",ECUInfo.ECUID);
	printf("*        ƫ�Ƶ�ַ��%d                              \r\n",ECUInfo.bias);
	printf("*         ��ص�ؽ�����%d                         \r\n",ECUInfo.battJarNum);	
	printf("*                                                  \r\n");
	printf("*******************��4��Zigbee����*******************\r\n");
	printf("*                                                  \r\n");
	printf("*                  ����� �ŵ�  PANID ������       \r\n");	
	printf("*         Э����1�� %d    0x%0X   0x%0X  %d				 \r\n",ECUInfo.nwPara.nwNum_C[0],ECUInfo.nwPara.chanel_C[0],ECUInfo.nwPara.panid_C[0],ECUInfo.baud);
	printf("*         Э����2�� %d    0x%0X  0x%0X  %d         \r\n",ECUInfo.nwPara.nwNum_C[1],ECUInfo.nwPara.chanel_C[1],ECUInfo.nwPara.panid_C[1],ECUInfo.baud);
	printf("*         Э����3�� %d    0x%0X  0x%0X  %d         \r\n",ECUInfo.nwPara.nwNum_C[2],ECUInfo.nwPara.chanel_C[2],ECUInfo.nwPara.panid_C[2],ECUInfo.baud);
	printf("*                                                  \r\n");
	printf("*******************��5����������������***************\r\n");
	printf("*                                                  \r\n");
	printf("*         ����������������������%dA          \r\n",ECUInfo.hall.HALL_A_Charge);
	printf("*         ����������������������%dV          \r\n",ECUInfo.hall.HALL_V_Charge);
	printf("*         �ŵ��������������������%dA          \r\n",ECUInfo.hall.HALL_A_DisCharge);
	printf("*         �ŵ��������������������%dV          \r\n",ECUInfo.hall.HALL_V_DisCharge);
	printf("*         ©���������������������%dmA         \r\n",ECUInfo.hall.HALL_A_LeakageCurr);
	printf("*         ©���������������������%dV          \r\n",ECUInfo.hall.HALL_V_LeakageCurr);
	printf("*                                                  \r\n");
	printf("*******************��6������ʱ��*********************\r\n");
	printf("*                                                  \r\n");
	print_ECUOnLineTime();
	printf("*                                                  \r\n");
	printf("*******************��7������ģʽ*********************\r\n");
	printf("*                                                  \r\n");
	print_ECUMode();
	printf("*                                                  \r\n");
	printf("*****************************************************\r\n\r\n"); 
}

void vPrint_ZigbeeInformation(void)
{
}

void vECUOnLineTime_Update(void)
{
	ECUInfo.ECUOnLineTime._Sec++;
	ECUInfo.ECUOnLineTime.Second++;
	if((ECUInfo.ECUOnLineTime._Sec%60==0))
	{		
		ECUInfo.ECUOnLineTime._Sec = 0x00;
		ECUInfo.ECUOnLineTime._Min++;
		if((ECUInfo.ECUOnLineTime._Min%60==0))
		{
			ECUInfo.ECUOnLineTime._Min = 0x00;
			ECUInfo.ECUOnLineTime._Hour++;
			if((ECUInfo.ECUOnLineTime._Hour%24==0))
			{
				ECUInfo.ECUOnLineTime._Hour = 0x00;
				ECUInfo.ECUOnLineTime._Day++;
				if((ECUInfo.ECUOnLineTime._Day%30==0))
				{
					ECUInfo.ECUOnLineTime._Day = 0x00;
					ECUInfo.ECUOnLineTime._Month++;
					if((ECUInfo.ECUOnLineTime._Month%12==0))
					{
						ECUInfo.ECUOnLineTime._Month = 0x00;
						ECUInfo.ECUOnLineTime._Year++;
					}
				}
			}
		}
	}
}


void vECUMode_Ctrl(void)
{
	#if defined(PRINT_ECUMODE)
	if(tag_2s)
	{
		tag_2s=0;
		print_ECUMode();
	}
	#endif
	
	switch (ECUInfo.runMode)
	{
		case ECUMODE_Normal:
		/* Your code here */
		break;
		case ECUMODE_Product:
		/* Your code here */
		break;
		case ECUMODE_Debug:
		/* Your code here */
		break;
		case ECUMODE_Calib:			
		/* Your code here */
		break;
		case ECUMODE_CfgNw:
				if(ECUInfo.nwPara.tag_WriteNw && ECUInfo.nwPara.WriteNw_En)
			  {
					ECUInfo.nwPara.tag_WriteNw=0;
					eCC2530_NWInit(ECUInfo.nwPara.nwNum_C[0],ECUInfo.nwPara.nwNum_C[1],ECUInfo.nwPara.nwNum_C[2]);
					printf("\r\n�������磬ѭ������:%d\r\n",++ECUInfo.nwPara.cnt);
			  }
		break;
		case ECUMODE_ReadNw:
				ECUInfo.nwPara.ReadNw_En=READNW_C1_EN|READNW_C2_EN|READNW_C3_EN;
				if(ECUInfo.nwPara.tag_ReadNw && ECUInfo.nwPara.ReadNw_En)
				{
					ECUInfo.nwPara.tag_ReadNw=0;
					eCC2530_NWInit(ECUInfo.nwPara.nwNum_C[0],ECUInfo.nwPara.nwNum_C[1],ECUInfo.nwPara.nwNum_C[2]);
					printf("\r\n��ѯ���磬ѭ������:%d\r\n",++ECUInfo.nwPara.cnt);
				}
			break;
		default:
		/* Your code here */
		break;
	}
}

void vGlobalVarInit(void)
{
	Coordinator[0].txBCUNum[POLLTASK_WRREG1000]=0x01;
	Coordinator[1].txBCUNum[POLLTASK_WRREG1000]=0x01;
	Coordinator[2].txBCUNum[POLLTASK_WRREG1000]=0x01;
}


void vBCUDataStatistics(void)
{
	if(tag_10s)
	{
		tag_10s=0;
		//TODO Eclipse and Keil is not work
//		arm_mean_f32((float32_t*)&CellV[ECUInfo.bias+80],4,&BCUSta.meanU);
//		arm_mean_f32((float32_t*)&CellR[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.meanR);
//		arm_mean_f32((float32_t*)&CellT[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.meanT);

//		arm_max_f32((float32_t*)&CellV[ECUInfo.bias+80],4				,(float32_t*)&BCUSta.maxU,(uint32_t *)&BCUSta.indexMaxU);
//		arm_max_f32((float32_t*)&CellR[ECUInfo.bias],3*MAXROUTER_Default,(float32_t*)&BCUSta.maxR,(uint32_t *)&BCUSta.indexMaxR);
//		arm_max_f32((float32_t*)&CellT[ECUInfo.bias],3*MAXROUTER_Default,(float32_t*)&BCUSta.maxT,(uint32_t *)&BCUSta.indexMaxT);

//		arm_min_f32((float32_t*)&CellV[ECUInfo.bias+80],4,				&BCUSta.minU,&BCUSta.indexMinU);
//		arm_min_f32((float32_t*)&CellR[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.minR,&BCUSta.indexMinU);
//		arm_min_f32((float32_t*)&CellT[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.minT,&BCUSta.indexMinU);
//
//		arm_std_f32((float32_t*)&CellV[ECUInfo.bias+80],4,&BCUSta.stdU);
//		arm_std_f32((float32_t*)&CellR[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.stdR);
//		arm_std_f32((float32_t*)&CellT[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.stdT);
//
//		arm_rms_f32((float32_t*)&CellV[ECUInfo.bias+80],4,&BCUSta.rmsU);
//		arm_rms_f32((float32_t*)&CellR[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.rmsR);
//		arm_rms_f32((float32_t*)&CellT[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.rmsT);
//
//		arm_var_f32((float32_t*)&CellV[ECUInfo.bias+80],4,&BCUSta.varU);
//		arm_var_f32((float32_t*)&CellR[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.varR);
//		arm_var_f32((float32_t*)&CellT[ECUInfo.bias],3*MAXROUTER_Default,&BCUSta.varT);

//		printf("\r\nBCUData Statistics With DSP:Mean:%.1f Max:%.1f Min:%.1f Std:%.1f Rms:%.1f Var:%.1f\r\n",\
//				BCUSta.meanU,\
//				BCUSta.maxU,\
//				BCUSta.minU,\
//				BCUSta.stdU,\
//				BCUSta.rmsU,\
//				BCUSta.varU);
	}

}
/*****************************************End of ecu.c*****************************************/
