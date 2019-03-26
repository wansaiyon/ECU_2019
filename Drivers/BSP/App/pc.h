/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: pc.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/02		03:35:34
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
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
#define USARTX_RXSIZE (1024)//接收数据缓存大小，单位：Bytes

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
/*****************************  协议地址空间设计  	*******************************/
/**********************************************************************************/
//单体数据与组数据设计容量
#define MAX_CELL_SIZE   (512)    //最多支持512节
#define MAX_GROUP_SIZE   (16)    //最多支持16组

//电池相关数据通讯协议地址分区,原始协议没有设计预留好顺序
#define CELL_V_SIZE    (512)     //单体电压
#define CELL_R_SIZE    (512)     //单体内阻
#define CELL_T_SIZE    (512)     //单体温度
#define GROUP_V_SIZE    (16)     //组端电压
#define GROUP_I_SIZE    (16)     //组端电流
#define GROUP_T_SIZE    (16)     //环境温度
#define GROUP_RB_SIZE   (16)     //组端内阻基准
#define CELL_RB_SIZE    (512)    //单体内阻纵向基准
#define CELL_S_SIZE     (512)    //单体状态
//TODO 算法地址空间扩展


//单体数据与组数据基地址
#define CellV_BASE	(0x0000)
#define CellR_BASE	(0x0200)    
#define CellT_BASE	(0x0400) 
#define GrpV_BASE		(0x0600)
#define GrpI_BASE		(0x0610)
#define GrpT_BASE		(0x0620)
#define GrpRB_BASE	(0x0630)
#define CellRB_BASE	(0x0640)
#define CellS_BASE	(0x0840)
#define BATTDATAEND_BASE	(0x0A34)//BattData缓存空间大小
//TODO 算法地址空间扩展


#define  CellV ((uint16_t *)(&BattData[CellV_BASE]))   //单体电压
#define  CellR ((uint16_t *)(&BattData[CellR_BASE]))   //单体内阻
#define  CellT ((uint16_t *)(&BattData[CellT_BASE]))   //单体温度
#define  GrpV ((uint16_t *)(&BattData[GrpV_BASE])) //组端电流
#define  GrpI ((uint16_t *)(&BattData[GrpI_BASE])) //组端电流
#define  GrpT ((uint16_t *)(&BattData[GrpT_BASE])) //环境温度
#define GrpRB ((uint16_t *)(&BattData[GrpRB_BASE])) //组端内阻基准
#define CellRB ((uint16_t *)(&BattData[CellRB_BASE])) //单体内阻纵向基准
#define CellS ((uint16_t *)(&BattData[CellS_BASE])) //单体状态
/**********************************************************************************/
/**********************************************************************************/


/**********************************************************************************/
/*******************************  寄存器地址	判断时前闭后开***********************/
/**********************************************************************************/
//03功能码区域
#define REG_CELL0DATA_START (CellV_BASE)  //单体数据开始地址，按电压或内阻或温度信息定义单体
#define REG_CELL0DATA_END   (GrpV_BASE)   //单体数据结束地址
#define REG_GRPDATA_START (GrpV_BASE)   //组端数据开始地址
#define REG_GRPDATA_END   (CellRB_BASE) //组端数据结束地址
#define REG_GRPRB_START    (GrpRB_BASE)//组端内阻基准开始地址
#define REG_GRPRB_END    	 (CellRB_BASE)//组端内阻基准结束地址
#define REG_CELLRB_START    (CellRB_BASE)//单体内阻基准开始地址
#define REG_CELLRB_END    	 (CellS_BASE)//单体内阻基准结束地址
#define REG_CELLS_START    (CellS_BASE)//单体状态开始地址
#define REG_CELLS_END    	 (BATTDATAEND_BASE)//单体状态结束地址
//#define xxxxx 预留
#define REG_CELL1DATA_START (0x1000)   //单体数据开始地址，按电压、内阻、温度、状态信息定义单体
#define REG_CELL1DATA_END   (0x2000)   //单体数据结束地址


//10功能码区域
#define REG_CELLOP_START		(0x2000)  //单体电池交互操作起始地址
#define REG_CELLOP_END			(0x3000)  //单体电池交互操作结束地址
#define REG_DI_START		    (0x3000)  //ECU输入干接点起始地址
#define REG_DI_END          (0x3008)  //ECU输入干接结束地址
#define REG_DO_START  			(0x3008)  //ECU输出干接点起始地址
#define REG_DO_END    			(0x3010)  //ECU输出干接结束地址
#define DI(x)			(((x)==0)?\
		(HAL_GPIO_ReadPin(DI1_GPIO_Port,DI1_Pin)):\
		(HAL_GPIO_ReadPin(DI2_GPIO_Port,DI2_Pin)))

#define REG_NUMECU		(0x4100)  //ECU编号

//05功能码
#define REG_ECURST  	(0x4000)  //ECU复位地址
#define REG_NWRST_C1    (0x4001)  //ECU无线模块C1重启地址
#define REG_NWRST_C2    (0x4002)  //ECU无线模块C2重启地址
#define REG_NWRST_C3    (0x4003)  //ECU无线模块C3重启地址
#define REG_TEST_BEEP   (0x4030)  //ECU操作蜂鸣器地址



//组信息校准
#define REG_V_CALIB_START  (0xA000)  //ECU组电压校准起始地址
#define REG_V_CALIB_END    (0xA00B)  //ECU组电压校准结束地址
#define REG_I_CALIB_START  (0xA00C)  //ECU组电流校准起始地址
#define REG_I_CALIB_END    (0xA017)  //ECU组电流校准结束地址
#define REG_T_CALIB_START  (0xA018)  //ECU环境温度校准起始地址
#define REG_T_CALIB_END    (0xA01D)  //ECU环境温度校准结束地址


#define TimeOut_PC			((uint8_t)100)//38400波特率时足够了


/**********************************************************************************/
/**********************************************************************************/

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
 * @结构体功能  USARTx接收结构体
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
 * @全局变量功能    **全局变量,单位：
 * @复位状态			
 * @注意事项
 */
PC_EXT UsartxDMARx_TypeDef Rx_PC;

/**
 * @全局变量功能    **全局变量,单位：
 * @复位状态			
 * @注意事项
 */
PC_EXT UsartxDMARx_TypeDef Rx_C1;
/**
 * @全局变量功能    **全局变量,单位：
 * @复位状态			
 * @注意事项
 */
PC_EXT UsartxDMARx_TypeDef Rx_C2;

/**
 * @全局变量功能    **全局变量,单位：
 * @复位状态			
 * @注意事项
 */
PC_EXT UsartxDMARx_TypeDef Rx_C3;


/**
 * @全局变量功能    建立缓存与0x0A40=(512*4+16*4+512)个寄存器对应0x0000-0x0A3F
 * @复位状态			
 * @注意事项
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
