/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: ecu.h
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/02		04:39:35
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#ifndef ECU_H_
#define	ECU_H_

#ifdef ECU_GLOBALS
#define ECU_EXT
#else
#define  ECU_EXT extern
#endif

#include "Include.h"
//#include "stm32f4xx.h"
//#include "coordinator.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
#define SLAVEID_Default			(16)//ECUĬ��ͨѶ��վ��
#define BATTJARNUM_Default	(120)//һ��ECUĬ���������120��BCU
#define MAXROUTER_Default		(40)//1coordinatorĬ������40Router

#define JARNUM_C1_Default	((uint16_t)40)//C1Ĭ����������
#define JARNUM_C2_Default	((uint16_t)40)//C2Ĭ����������
#define JARNUM_C3_Default	((uint16_t)40)//C3Ĭ����������

#define NWPARA_C1_Default	((uint16_t)5)//C1Ĭ���������
#define NWPARA_C2_Default	((uint16_t)6)//C2Ĭ���������
#define NWPARA_C3_Default	((uint16_t)7)//C3Ĭ���������

#define BAUD_C_Default	((uint8_t)CC2530BAUDRATE_38400)//Э����Ĭ�ϲ�����

#define VOLTLEVEL_Default	(HIGHVOLT)//ECUĬ�ϸ�ѹ�汾

//�����������ͺŶ���
//����ͺŶ���
#define TKC400HAT_FS_A (400)  //�����400A,�����̵�ѹ4V
#define TKC200EKB_FS_A (200)  //�����200A,�����̵�ѹ4V
//�ŵ��ͺŶ���
#define TKC50LB_FS_A 	(50)  //�����50A,�����̵�ѹ4V
#define TKC_FS_V 		(4)	  //����TKC�����̵�ѹ4V
//©�����ͺŶ���
#define LFB7_FS_A 	(100)	  //�����100mA,�����̵�ѹ5V
#define LFB7_FS_V    (5)      //����LFB7�����̵�ѹ5V

#define HALL_A_Default(x)	(Table_ECUHall[2*(x)])
#define HALL_V_Default(x)	(Table_ECUHall[2*(x)+1])
#define HALL_K_Default(x)	((float)HALL_A_Default(x)/HALL_V_Default(x))

#define CHNUM_U	((uint8_t)6)//��ѹͨ����
#define CHNUM_I	((uint8_t)6)//����ͨ����
#define CHNUM_T	((uint8_t)6)//�����¶�ͨ����,��������Ϊ6Ϊ��printf��ӡ��Խ��


#define CALIB_U_NUM		 (2) //��ѹУ׼�ĵ���
#define CALIB_I_NUM		 (2) //����У׼�ĵ���
#define CALIB_T_NUM		 (2) //�����¶�У׼�ĵ���

/*
x����ECUInfo.ID(��ȡ5),�������£�
			x=1:������1��ECU
			x=2:�����2��ECU
			x=3:�����3��ECU
			x=4:�����4��ECU
y,z�������£�
			y=1:����ECU��Ӧ��������03�����룬ECU��ѯ����Ĵ�������ֹ��ַ��Χ0x1000-0x2000
			z=8:����03��1000~2000,һ����������ռ��8���Ĵ��� 
			
			y=2:����ECU��Ӧ�����ؽ�������10�����룬ECU��ѯ����Ĵ�������ֹ��ַ��Χ0x2000-0x3000
			z=1:����10д2000~3000,һ���������ռ��1���Ĵ���
			
����1,PC��ȡ���������������������ݣ�
			 ��1��ECU��һ��120�ڵ�ѹ�����¶ȵȣ�0x1000~0x13BF		��1��
			 ��2��ECU�ڶ���120�ڵ�ѹ�����¶ȵȣ�0x13C0~0x177F
			 ��3��ECU������120�ڵ�ѹ�����¶ȵȣ�0x1780~0x1B3F
			 ��4��ECU������120�ڵ�ѹ�����¶ȵȣ�0x1B40~0x1EFF
			 ��5��ECU������ 20�ڵ�ѹ�����¶ȵȣ�0x1F00~0x1FA0
			
����2,�����ؽ���������
			 ��1��ECU��һ��120�ڲ�����2000~2077				��1��
			 ��2��ECU�ڶ���120�ڲ�����2078~20EF
			 ��3��ECU������120�ڲ�����20F0~2167
			 ��4��ECU������120�ڲ�����2168~21DF
			 ��5��ECU������ 20�ڲ�����21E0~21F3

����3,PC��ȡ�������������������ݣ�
			 ��1��ECU��һ��120�ڵ����ѹ��0000~0077		��2��
			 ��2��ECU�ڶ���120�ڵ����ѹ��0078~00EF
			 ��3��ECU������120�ڵ����ѹ��00F0~0167
			 ��4��ECU������120�ڵ����ѹ��0168~01DF
			 ��5��ECU������ 20�ڵ����ѹ��01E0~01F3

		 	 ��1��ECU��һ��120�ڵ������裺0200~0277		��2��
			 ��2��ECU�ڶ���120�ڵ������裺0278~02EF
			 ��3��ECU������120�ڵ������裺02F0~0367
			 ��4��ECU������120�ڵ������裺0368~03DF
			 ��5��ECU������ 20�ڵ������裺03E0~03F3

			 ��1��ECU��һ��120�ڵ����¶ȣ�0400~0477		��2��
			 ��2��ECU�ڶ���120�ڵ����¶ȣ�0478~04EF
			 ��3��ECU������120�ڵ����¶ȣ�04F0~0567
			 ��4��ECU������120�ڵ����¶ȣ�0568~05DF
			 ��5��ECU������ 20�ڵ����¶ȣ�05E0~05F3

			��1��ECU��һ��120�ڵ��������׼��0640~0477 	��3��
			��2��ECU�ڶ���120�ڵ��������׼��0478~04EF
			��3��ECU������120�ڵ��������׼��04F0~0567
			��4��ECU������120�ڵ��������׼��0568~05DF
			��5��ECU������ 20�ڵ��������׼��05E0~05F3

			��1��ECU��һ��120�ڵ���״̬��0840~0477 		��3��
			��2��ECU�ڶ���120�ڵ���״̬��0478~04EF
			��3��ECU������120�ڵ���״̬��04F0~0567
			��4��ECU������120�ڵ���״̬��0568~05DF
			��5��ECU������ 20�ڵ���״̬��05E0~05F3

			��1��ECU��һ��120�ڵ���SOC��0A40~0477 	��3��
			��2��ECU�ڶ���120�ڵ���SOC��0478~04EF
			��3��ECU������120�ڵ���SOC��04F0~0567
			��4��ECU������120�ڵ���SOC��0568~05DF
			��5��ECU������ 20�ڵ���SOC��05E0~05F3

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

*/													 
#define ECU_REG_START(x,y,z)	((y)*(0x1000)+MAXROUTER_Default*3*(z)*((x)-1))
#define ECU_REG_END(x,y,z)		((y)*(0x1000)+MAXROUTER_Default*3*(z)*(x)-1)

#define ECU_REG_START2(x,y,z)	((y)*(0x0200)+MAXROUTER_Default*3*(z)*((x)-1))
#define ECU_REG_END2(x,y,z)		((y)*(0x0200)+MAXROUTER_Default*3*(z)*(x)-1)

#define ECU_REG_START3(x,y,z)	(((y)*0x200+0x0640)+MAXROUTER_Default*3*(z)*((x)-1))
#define ECU_REG_END3(x,y,z)		(((y)*0x200+0x0640)+MAXROUTER_Default*3*(z)*(x)-1)

//tobe delete
//03��1000~2000,һ����������ռ��8���Ĵ��� 
#define ECU_REG_START_03(x)  (0x1000+MAXROUTER_Default*3*8*((x)-1))
#define ECU_REG_END_03(x)    (0x1000+MAXROUTER_Default*3*8*(x)-1)
//10д2000~3000,һ���������ռ��1���Ĵ���
#define ECU_REG_START_10(x)  (0x2000+MAXROUTER_Default*3*((x)-1))
#define ECU_REG_END_10(x)    (0x2000+MAXROUTER_Default*3*(x)-1)


//д��Э�����������ʹ�ܶ���
#define WRITENW_C1_EN 0x01
#define WRITENW_C2_EN 0x02
#define WRITENW_C3_EN 0x04
//��ѯЭ�����������ʹ�ܶ���
#define READNW_C1_EN 0x01
#define READNW_C2_EN 0x02
#define READNW_C3_EN 0x04
//ECU����ģʽ
#define IS_ECUMODE(x)	 (ECUInfo.runMode==(x))	//ECU�Ƿ�������ģʽx
#define ECUMODE_ATTACH(x)	{ECUInfo.runMode=(x);}//ECUģʽ�󶨶��� 
#define ECUMODE_Normal   (0x00)//����ģʽ
#define ECUMODE_Product  (0x01)//����ģʽ
#define ECUMODE_Debug    (0x02)//����ģʽ
#define ECUMODE_Calib    (0x04)//У׼ģʽ
#define ECUMODE_CfgNw    (0x08)//Э��������д��ģʽ,��������յ�����֡ͬʱ���㷽�ܴ���
#define ECUMODE_ReadNw   (0x10)//Э���������ȡģʽ,��������,������ʱ��ȡ�Ĳ�����洢�Ĳ����г���ʱ����д�洢����ֱ���ɹ�

//ECU ID
#define IS_MASTER_ECU()   (ECUInfo.ECUID==ID1_MASTER_ECU)
#define ID1_MASTER_ECU		(0x01)//��1ECU�ɼ�����Ϣ��ID=1
#define ID2_SLAVE_ECU			(0x02)//��2ECU�ɼ�����Ϣ��ID=2
#define ID3_SLAVE_ECU			(0x03)//��3ECU�ɼ�����Ϣ��ID=3
#define ID4_SLAVE_ECU			(0x04)//��4ECU�ɼ�����Ϣ��ID=4
#define ID5_SLAVE_ECU			(0x05)//��5ECU�ɼ�����Ϣ��ID=5

//print ecu running mode
#define print_ECUMode()		{printf("ECU Running Mode:%d	WriteNw_En:%d	ReadNw_En:%d\r\n",\
ECUInfo.runMode,ECUInfo.nwPara.WriteNw_En,ECUInfo.nwPara.ReadNw_En);}

//print ecu running time
#define print_ECUOnLineTime() {printf("* 	 %4d��%2d��%2d��%2dʱ%2d��%2d��  \r\n",\
ECUInfo.ECUOnLineTime._Year,\
ECUInfo.ECUOnLineTime._Month,\
ECUInfo.ECUOnLineTime._Day,\
ECUInfo.ECUOnLineTime._Hour,\
ECUInfo.ECUOnLineTime._Min,\
ECUInfo.ECUOnLineTime._Sec);}

#define print_RTC()	{printf("* 	 %04d��%02d��%02d��%02dʱ%02d��%02d��  \r\n",\
2000+ECUInfo.ECUOnLineTime.data.Year,\
ECUInfo.ECUOnLineTime.data.Month,\
ECUInfo.ECUOnLineTime.data.Date,\
ECUInfo.ECUOnLineTime.time.Hours,\
ECUInfo.ECUOnLineTime.time.Minutes,\
ECUInfo.ECUOnLineTime.time.Seconds);}


//��ӡ��Ϣ����
#define BIT_PRINT_FLASHMEMORY	(0x00)
#define BIT_PRINT_ECUINFO			(0x01)
#define BIT_PRINT_ZIGBEEINFO	(0x02)
#define BIT_PRINT_READNW  		(0x04)


#define TASK_EVENT_BIT00	(1<<0)
#define TASK_EVENT_BIT01	(1<<1)
#define TASK_EVENT_BIT02	(1<<2)
#define TASK_EVENT_BIT03	(1<<3)
#define TASK_EVENT_BIT04	(1<<4)
#define TASK_EVENT_BIT05	(1<<5)
#define TASK_EVENT_BIT06	(1<<6)
#define TASK_EVENT_BIT07	(1<<7)
#define TASK_EVENT_BIT08	(1<<8)

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/
/**
 * @ö�ٹ���    ECU��ѹ��ѹ�汾
 */
typedef enum {
	LOWVOLT =0x00,
	HIGHVOLT =0x01
} ECUVoltLevel_TypeDef;

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
 * @�ṹ�幦��  ECUӲ���汾�ṹ��
 */
typedef struct {
	char *swVer_ECU;		//ECU����汾��,10���ֽ�V001B01D00
	char *swVer_BCU;		//BCU����汾��,10���ֽ�V001B01D00
	char *hwVer_ECU;		//ECUӲ���汾��,4���ֽ�V2.0
	char *hwVer_BCU;	    //BCUӲ���汾��,4���ֽ�V4.0
	char *osVer_ECU;		//ECUϵͳ�汾��,v9.0.0
	ECUVoltLevel_TypeDef voltLevel;
} ECUVer_TypeDef;

/**
 * @�ṹ�幦��  ECU��������ṹ��
 */
 

typedef struct {
	uint8_t cnt;//����ȫ�����óɹ�ʱִ��CC2530_NWInit����
	uint8_t confirmTimes[3];//��ʼ��ʼ����������
	uint8_t WriteNw_En;	 //�������д��ʹ��
	uint8_t ReadNw_En;	 //���������ѯʹ��
	uint8_t tag_WriteNw;//�������д���־
	uint8_t tag_ReadNw;//���������ѯ��־
	uint16_t periodWriteNw;//��������������ڣ���λms
	uint16_t periodReadNw;//���������ѯ���ڣ���λms
	
	uint16_t nwNum_C[3];
	uint16_t panid_C[3];
	uint16_t panid2_C[3];//����panid
	uint8_t chanel_C[3];
	uint8_t jarNum_C[3];
} ECUNWPara_TypeDef;

/**
 * @�ṹ�幦��  ECU�������ṹ��
 */
typedef struct {
	uint16_t  HALL_A_Charge;											//��������������������
	uint16_t  HALL_V_Charge;											//������������������ѹ
	uint16_t  HALL_A_DisCharge;											//�ŵ������������������
	uint16_t  HALL_V_DisCharge;											//�ŵ����������������ѹ
	uint16_t  HALL_A_LeakageCurr;										//©���������������������
	uint16_t  HALL_V_LeakageCurr;										//©�����������������ѹ
} ECUHall_TypeDef;

/**
 * @�ṹ�幦��  ECUУ׼�����ṹ��
 */
typedef struct {
	
	uint8_t En_U;//���ѹУ׼ʹ��
	uint8_t En_I;//�����У׼ʹ��
	uint8_t En_T;//�����¶�У׼ʹ��
	
	float U[CALIB_U_NUM][2];//���ѹУ׼��������
	float I[CALIB_I_NUM][2];//�����У׼��������
	float T[CALIB_T_NUM][2];//�����¶�У׼��������
	
	float kU[CHNUM_U];//���ѹУ׼ϵ��k,��λ: NULL
	float kI[CHNUM_I];//�����У׼ϵ��k,��λ��NULL
	float kT[CHNUM_T];//�����¶�У׼ϵ��k,��λ��NULL
	float bU[CHNUM_U];//���ѹУ׼ϵ��b,��λ��NULL
	float bI[CHNUM_I];//�����У׼ϵ��b,��λ��NULL
	float bT[CHNUM_T];//�����¶�У׼ϵ��b,��λ��NULL	
	
	float squarePoorU[4];//�������ָ��: �ع�ƽ����,ʣ��ƽ����,�ع�ƽ����,ʣ��ƽ����
	float squarePoorI[4];
	float squarePoorT[4];

} ECUCalib_TypeDef;

/**
 * @�ṹ�幦��  ECU�����ݽṹ��
 */
typedef struct {
	float U[CHNUM_U];//���ѹ,��λ: V
	float I[CHNUM_I];//�����,��λ: A
	float T[CHNUM_T];//�����¶�,��λ: ��
	
	ECUCalib_TypeDef calib;//ECUУ׼
	
	float s_kHall[3];//������������������,��λ������ÿ����A/V,0:��������1���ŵ������2��©����
	
	float p_kU;//ͨѶЭ��,���ѹ����ϵ��k,��λ��NULL
	float p_bU;//ͨѶЭ��,���ѹ����ϵ��b,��λ��NULL
	float p_kI;//ͨѶЭ��,���������ϵ��k,��λ��NULL
	float p_bI;//ͨѶЭ��,���������ϵ��b,��λ��NULL
	float p_kT;//ͨѶЭ��,�����¶ȴ���ϵ��k,��λ��NULL
	float p_bT;//ͨѶЭ��,�����¶ȴ���ϵ��b,��λ��NULL
} ECUGrpData_TypeDef;

/**
* @ö�ٹ���  ECU����ʱ��ṹ��
*/
typedef struct
{
	uint8_t _Year;     //BCU�ϵ�����ʱ�䣬��λ����
	uint8_t _Month; 	 //BCU�ϵ�����ʱ�䣬��λ����
	uint16_t _Day; 		 //BCU�ϵ�����ʱ�䣬��λ����
	uint8_t _Hour;     //BCU�ϵ�����ʱ�䣬��λ��Сʱ
	uint8_t _Min; 		 //BCU�ϵ�����ʱ�䣬��λ������
	uint8_t _Sec; 		 //BCU�ϵ�����ʱ�䣬��λ����
	float Second; 	 	 //BCU�ϵ�����ʱ�䣬��λ����,һֱͳ��ֱ�����
	
	RTC_DateTypeDef data;
	RTC_TimeTypeDef time;
}ECUOnLineTime_TypeDef;		

/**
 * @�ṹ�幦��  ECU�ṹ��
 */
typedef struct {
	 uint8_t slaveID; //modbus�ӻ���ַ
	 uint8_t ECUID;//����ECU�ı��,��Χ:1,2,3,4,5�ֱ������1#ECU,��2#ECU,��3#ECU,��4#ECU,��5#ECU
	 uint16_t bias; //һ���ض�ECUʱ��ƫ�Ƶ�ַ

	 uint8_t ledBCDNum;//8421BCD�����ʾ�ӻ���slaveID
	 uint8_t BeepNum;//4��LEDֻ֧��1~15����ַ������16~30�ĵ�ַ��������1�Σ�31~45�ĵ�ַ��������2�Σ�����
	 uint8_t runMode;//ECU����ģʽ
	 uint8_t battJarNum;//����ECU��صĵ�ؽ���
	 uint8_t baud;//������
	 ECUVer_TypeDef Ver; //���Ӳ���汾��
	 ECUNWPara_TypeDef nwPara;//zigbee�������
	 ECUGrpData_TypeDef grpData;//���������
	 ECUOnLineTime_TypeDef ECUOnLineTime;//ECU����ʱ��
	 ECUHall_TypeDef hall;//��������������
	 uint8_t En_IwdgRst;//ʹ�ܿ��Ź���λ
	 uint16_t bcuRegAddr[20];//��Ӧ��̨03/10��дBCU����ַ��ʼλ�ã����ECU_REG_START/ECU_REG_END
	 uint8_t print;//��ӡ
} ECUInfo_TypeDef;

/**
 * @�ṹ�幦��  **�ṹ��
 */
typedef struct {

	float32_t meanU;
	float32_t meanR;
	float32_t meanT;

	float32_t maxU;
	float32_t maxR;
	float32_t maxT;

	float32_t indexMaxU;
	float32_t indexMaxR;
	float32_t indexMaxT;

	float32_t minU;
	float32_t minR;
	float32_t minT;

	float32_t indexMinU;
	float32_t indexMinR;
	float32_t indexMinT;

	float32_t stdU;
	float32_t stdR;
	float32_t stdT;

	float32_t rmsU;
	float32_t rmsR;
	float32_t rmsT;

	float32_t varU;
	float32_t varR;
	float32_t varT;
} BCUDataStatistics_TypeDef;


/**
 * @�ṹ�幦��  **�ṹ��
 */
typedef struct {
	uint16_t ulEventBit;
	void (*pFun)(void);
} EventDoWithTable_TypeDef;

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
/**
 * @ȫ�ֱ�������    **ȫ�ֱ���,��λ��
 * @��λ״̬			
 * @ע������
 */
ECU_EXT ECUInfo_TypeDef ECUInfo;

/**
 * @ȫ�ֱ�������    **ȫ�ֱ���
 * @��λ״̬
 * @ע������
 */
ECU_EXT uint16_t ulEventBits;

/**
 * @ȫ�ֱ�������    **ȫ�ֱ���
 * @��λ״̬
 * @ע������
 */
ECU_EXT BCUDataStatistics_TypeDef BCUSta;

/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
ECU_EXT void vECUPara_Init(void);
ECU_EXT void vPrint_ECUInformation(void);
ECU_EXT void vPrint_ZigbeeInformation(void);
ECU_EXT void vECUOnLineTime_Update(void);
ECU_EXT void vECUMode_Ctrl(void);
ECU_EXT void vGlobalVarInit(void);

ECU_EXT void vDoWithEvent00(void);
ECU_EXT void vDoWithEvent01(void);
ECU_EXT void vDoWithEvent02(void);
ECU_EXT void vDoWithEvent03(void);
ECU_EXT void vDoWithEvent04(void);
ECU_EXT void vDoWithEvent05(void);
ECU_EXT void vDoWithEvent06(void);
ECU_EXT void vDoWithEvent07(void);
ECU_EXT void vDoWithEvent08(void);

ECU_EXT void vBCUDataStatistics(void);
#endif /* ECU_H_ */


