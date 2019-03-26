/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: pc.h
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/03/02		03:35:34
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#ifndef PC_H_
#define	PC_H_

#ifdef PC_GLOBALS
#define PC_EXT
#else
#define  PC_EXT extern
#endif

#include "include.h"
//#include "stm32f4xx.h"
//#include "usart.h"
//#include "ecu.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
#define USARTX_RXSIZE (1024)//�������ݻ����С����λ��Bytes

#define RS485_GPIO_PORT	SPI2_CS_GPIO_Port//TODO
#define RS485_PIN	SPI2_CS_Pin
#define RS485_RX_MODE()		{HAL_GPIO_WritePin(RS485_GPIO_PORT,RS485_PIN,GPIO_PIN_RESET);}
#define RS485_TX_MODE()		{HAL_GPIO_WritePin(RS485_GPIO_PORT,RS485_PIN,GPIO_PIN_SET);}


//modbusrtu function code
#define MODBUSRTU_FUNCODE_0X01	(0x01)
#define MODBUSRTU_FUNCODE_0X03	(0x03)
#define MODBUSRTU_FUNCODE_0X05	(0x05)
#define MODBUSRTU_FUNCODE_0X06	(0x06)
#define MODBUSRTU_FUNCODE_0X10	(0x10)
/**********************************************************************************/
/*****************************  Э���ַ�ռ����  	*******************************/
/**********************************************************************************/
//�����������������������
#define MAX_CELL_SIZE   (512)    //���֧��512��
#define MAX_GROUP_SIZE   (16)    //���֧��16��

//����������ͨѶЭ���ַ����,ԭʼЭ��û�����Ԥ����˳��
#define CELL_V_SIZE    (512)     //�����ѹ
#define CELL_R_SIZE    (512)     //��������
#define CELL_T_SIZE    (512)     //�����¶�
#define GROUP_V_SIZE    (16)     //��˵�ѹ
#define GROUP_I_SIZE    (16)     //��˵���
#define GROUP_T_SIZE    (16)     //�����¶�
#define GROUP_RB_SIZE   (16)     //��������׼
#define CELL_RB_SIZE    (512)    //�������������׼
#define CELL_S_SIZE     (512)    //����״̬
//TODO �㷨��ַ�ռ���չ


//���������������ݻ���ַ
#define CellV_BASE	(0x0000)
#define CellR_BASE	(0x0200)    
#define CellT_BASE	(0x0400) 
#define GrpV_BASE		(0x0600)
#define GrpI_BASE		(0x0610)
#define GrpT_BASE		(0x0620)
#define GrpRB_BASE	(0x0630)
#define CellRB_BASE	(0x0640)
#define CellS_BASE	(0x0840)
#define BATTDATAEND_BASE	(0x0A34)//BattData����ռ��С
//TODO �㷨��ַ�ռ���չ


#define  CellV ((uint16_t *)(&BattData[CellV_BASE]))   //�����ѹ
#define  CellR ((uint16_t *)(&BattData[CellR_BASE]))   //��������
#define  CellT ((uint16_t *)(&BattData[CellT_BASE]))   //�����¶�
#define  GrpV ((uint16_t *)(&BattData[GrpV_BASE])) //��˵���
#define  GrpI ((uint16_t *)(&BattData[GrpI_BASE])) //��˵���
#define  GrpT ((uint16_t *)(&BattData[GrpT_BASE])) //�����¶�
#define GrpRB ((uint16_t *)(&BattData[GrpRB_BASE])) //��������׼
#define CellRB ((uint16_t *)(&BattData[CellRB_BASE])) //�������������׼
#define CellS ((uint16_t *)(&BattData[CellS_BASE])) //����״̬
/**********************************************************************************/
/**********************************************************************************/


/**********************************************************************************/
/*******************************  �Ĵ�����ַ	�ж�ʱǰ�պ�***********************/
/**********************************************************************************/
//03����������
#define REG_CELL0DATA_START (CellV_BASE)  //�������ݿ�ʼ��ַ������ѹ��������¶���Ϣ���嵥��
#define REG_CELL0DATA_END   (GrpV_BASE)   //�������ݽ�����ַ
#define REG_GRPDATA_START (GrpV_BASE)   //������ݿ�ʼ��ַ
#define REG_GRPDATA_END   (CellRB_BASE) //������ݽ�����ַ
#define REG_GRPRB_START    (GrpRB_BASE)//��������׼��ʼ��ַ
#define REG_GRPRB_END    	 (CellRB_BASE)//��������׼������ַ
#define REG_CELLRB_START    (CellRB_BASE)//���������׼��ʼ��ַ
#define REG_CELLRB_END    	 (CellS_BASE)//���������׼������ַ
#define REG_CELLS_START    (CellS_BASE)//����״̬��ʼ��ַ
#define REG_CELLS_END    	 (BATTDATAEND_BASE)//����״̬������ַ
//#define xxxxx Ԥ��
#define REG_CELL1DATA_START (0x1000)   //�������ݿ�ʼ��ַ������ѹ�����衢�¶ȡ�״̬��Ϣ���嵥��
#define REG_CELL1DATA_END   (0x2000)   //�������ݽ�����ַ


//10����������
#define REG_CELLOP_START		(0x2000)  //�����ؽ���������ʼ��ַ
#define REG_CELLOP_END			(0x3000)  //�����ؽ�������������ַ
#define REG_DI_START		    (0x3000)  //ECU����ɽӵ���ʼ��ַ
#define REG_DI_END          (0x3008)  //ECU����ɽӽ�����ַ
#define REG_DO_START  			(0x3008)  //ECU����ɽӵ���ʼ��ַ
#define REG_DO_END    			(0x3010)  //ECU����ɽӽ�����ַ
#define DI(x)			(((x)==0)?\
		(HAL_GPIO_ReadPin(DI1_GPIO_Port,DI1_Pin)):\
		(HAL_GPIO_ReadPin(DI2_GPIO_Port,DI2_Pin)))

#define REG_NUMECU		(0x4100)  //ECU���

//05������
#define REG_ECURST  	(0x4000)  //ECU��λ��ַ
#define REG_NWRST_C1    (0x4001)  //ECU����ģ��C1������ַ
#define REG_NWRST_C2    (0x4002)  //ECU����ģ��C2������ַ
#define REG_NWRST_C3    (0x4003)  //ECU����ģ��C3������ַ
#define REG_TEST_BEEP   (0x4030)  //ECU������������ַ



//����ϢУ׼
#define REG_V_CALIB_START  (0xA000)  //ECU���ѹУ׼��ʼ��ַ
#define REG_V_CALIB_END    (0xA00B)  //ECU���ѹУ׼������ַ
#define REG_I_CALIB_START  (0xA00C)  //ECU�����У׼��ʼ��ַ
#define REG_I_CALIB_END    (0xA017)  //ECU�����У׼������ַ
#define REG_T_CALIB_START  (0xA018)  //ECU�����¶�У׼��ʼ��ַ
#define REG_T_CALIB_END    (0xA01D)  //ECU�����¶�У׼������ַ


#define TimeOut_PC			((uint8_t)100)//38400������ʱ�㹻��


/**********************************************************************************/
/**********************************************************************************/

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
 * @�ṹ�幦��  USARTx���սṹ��
 */
typedef struct  
{  
	uint8_t  rxFlag;        	 			//IDLE receive flag
	uint16_t rxSize;          			//receive length
	uint8_t  rxData[USARTX_RXSIZE]; //DMA receive buffer
}UsartxDMARx_TypeDef;  

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
/**
 * @ȫ�ֱ�������    **ȫ�ֱ���,��λ��
 * @��λ״̬			
 * @ע������
 */
PC_EXT UsartxDMARx_TypeDef Rx_PC;

/**
 * @ȫ�ֱ�������    **ȫ�ֱ���,��λ��
 * @��λ״̬			
 * @ע������
 */
PC_EXT UsartxDMARx_TypeDef Rx_C1;
/**
 * @ȫ�ֱ�������    **ȫ�ֱ���,��λ��
 * @��λ״̬			
 * @ע������
 */
PC_EXT UsartxDMARx_TypeDef Rx_C2;

/**
 * @ȫ�ֱ�������    **ȫ�ֱ���,��λ��
 * @��λ״̬			
 * @ע������
 */
PC_EXT UsartxDMARx_TypeDef Rx_C3;


/**
 * @ȫ�ֱ�������    ����������0x0A40=(512*4+16*4+512)���Ĵ�����Ӧ0x0000-0x0A3F
 * @��λ״̬			
 * @ע������
 */
PC_EXT uint16_t BattData[MAX_CELL_SIZE*4+MAX_GROUP_SIZE*4+CELL_RB_SIZE];


/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
PC_EXT void vPCHost_Proc(void);
PC_EXT void vUsartReceive_IDLE(UART_HandleTypeDef *huart,UsartxDMARx_TypeDef *husartDMA);  
PC_EXT HAL_StatusTypeDef eHAL_UART_TransmitPC(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//TODO :return value is static HAL_StatusTypeDef
PC_EXT HAL_StatusTypeDef eHAL_UART_Transmit485(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
#endif /* PC_H_ */
