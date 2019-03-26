/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: coordinator.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/02		04:39:46
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef COORDINATOR_H_
#define	COORDINATOR_H_

#ifdef COORDINATOR_GLOBALS
#define COORDINATOR_EXT
#else
#define  COORDINATOR_EXT extern
#endif

//#include "pc.h"
//#include "timer.h"
#include "Include.h"

/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
#define MAXBCU_Default			(512)//协议最多支持BCU数量512个
#define MAXROUTER_Default		(40)//1coordinator默认组网40Router

// 更新点灯帧
// TODO nextBCUNum,numNextBcu_Tick,numNextBcu_En
#define UPDATE_NUMBCU_LEDFRAME_C(x)  {nextBCUNum=Coordinator[x].Cfg.BCUNum;numNextBcu_Tick=0x00;numNextBcu_En =0x01;}
// 更新编号帧
#define UPDATE_NUMBCU_NUMFRAME_C(x)  {Coordinator[x].Cfg.BCUNum++;Coordinator[x].Cfg.BCUTime=0x00;}

#define NONE_CONFIG_MODE   (0x00)      //没有配置
#define FULL_CONFIG_MODE   (0x01)      //全配置模式，工装出厂配置模式，所有bcu均需要编号后再发货,B3按3次触发,按4次退出，后台配置120节
#define PART_CONFIG_MODE   (0x02)      //部分配置模式，部分BCU需要编号，B2按3次触发,按4次退出
#define OVER_NONE_CONFIG_MODE   		(0x00) //非配置完成
#define OVER_FULL_CONFIG_MODE   		(0x01) //全配置完成
#define OVER_PART_CONFIG_MODE   		(0x02) //部分配置完成
#define USEROVER_PART_CONFIG_MODE   (0x04) //部分配置完成,由用户终止
#define OVER_ALL_CONFIG_MODE    		(0x08)   //全\临时配置完成

//点播任务定义
#define POLLTASK_NUM	(8)				//点播轮询任务的数量
#define POLLTASK_WRREG1000			(0x00)//写1000寄存器
#define POLLTASK_NUMBCU					(0x01)//编号BCU
#define POLLTASK_NWRST					(0x02)//复位Router1S
#define POLLTASK_NWRESTART			(0x03)//复位Router5MIN,网络重启
#define POLLTASK_HEARTBEAT			(0x04)//心跳同步
//add something here


//点播发送后停止时间定义
#define TXSTOPTICKS_WRREG1000 (2)//协调器单播一圈后停止时间,单位:秒
#define TXSTOPTICKS_NUMBCU 	 (20)//协调器单播一圈后停止时间,单位:秒
#define TXSTOPTICKS_NWRST		 (20)//协调器单播一圈后停止时间,单位:秒
#define TXSTOPTICKS_NWRESTART (20)//协调器单播一圈后停止时间,单位:秒
#define TXSTOPTICKS_HEARTBEAT (20)//协调器单播一圈后停止时间,单位:秒

//接收到的编号定义
#define RXBCUNUM				(8)
#define _1_40					(0)//接收编号,1~40
#define _1_512				(1)//接收编号,1~512	
#define CNTMAX_1_40		(2)//接收次数最多的BCU编号,1-40
#define CNTMAX_1_512	(3)//接收次数最多的BCU编号,1-512
#define CNTMIN_1_40		(4)//接收次数最少的BCU编号,1-40
#define CNTMIN_1_512	(5)//接收次数最少的BCU编号,1-512
//add something here


/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/

/**
* @枚举功能  协调器名称结构体
*/
typedef enum
{
	CC2530PA2S_C1 =0x00,//Coordinator1
	CC2530PA2S_C2 =0x01,//Coordinator2
	CC2530PA2S_C3 =0x02	//Coordinator3
}CoordinatorX_TypeDef;

/**
* @枚举功能  ECU2BCU 协议1000处寄存器操作
*/
typedef enum
{
	REG1000_RESTEST   					=0x01,//内阻测试
	REG1000_ALARM_ON   					=0x04,//告警状态写入
	REG1000_ALARM_OFF   				=0x08,//告警状态清除
	REG1000_NWRSTONE   					=0x10,//个别R通讯异常复位RST 1秒恢复
	REG1000_NWRSTALL   					=0x20,//C死掉，复位R持续5min，重写C恢复

	REG1000_M2O_LOWSPEED   			=0x40,//R到C主动上发周期15s
	REG1000_M2O_MEDIUMSPEED   	=0x80,//R到C主动上发周期10s
	REG1000_M2O_HIGHSPEED  			=0xC0,//R到C主动上发周期2s
	REG1000_M2O_SUPERFASTSPEED  =0x100,//R到C主动上发周期1s
	REG1000_M2O_GODLIKESPEED    =0x101,//R到C主动上发周期200ms
	REG1000_M2O_DEFAULTSPEED    =0x110,//R到C主动上发周期5s默认值
	REG1000_M2O_RSTBCU          =0x200,//复位AVR MCU
	REG1000_NUMNEXTBCU          =0x202 //编号下一个BCU
}REG1000_TypeDef;

/**
* @枚举功能 many to one 方式下，Router到Coodinator点对点主动发送的频率
            这里主要作为函数CC2530M2OSpeedCtrl的参数使用
*/
typedef enum
{
	LOWSPEED_M2O					=0x00,					//低速，15s
	MEDIUMSPEED_M2O				=0x01,					//中速，10s
	HIGHSPEED_M2O					=0x02,					//快速，2s
	SUPERFASTSPEED_M2O		=0x03,					//超快速，1s
	GODLIKESPEED_M20			=0X04,					//超神般的速度，200ms
	DEFAULTSPEED_M2O			=0x05						//默认速度，5s	
}M2OSpeed_TypeDef;

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
* @枚举功能  ECU的协调器C1,C2,C3依次发送配置信息结构体
*/
typedef struct
{
	uint8_t Mode;        //在轮询帧中插入配置帧模式,按序插入1~电池节数的帧
	uint8_t BCUNum; 			//当前协调器配置到第X个BCU模块，X范围1~MAXNUM_CORDINATOR个，当前范围为1~40个
	uint8_t BCUNum_Last; //预留，保存上一次协调器配置到第X个BCU模块，X范围1~MAXNUM_CORDINATOR个，当前范围为1~40个
	uint8_t Cplt;				//配置完成
	uint16_t BCUTime;    //配置当前一个BCU所消耗的时间成本,单位:s
	//TODO
	// uint16_t NextNumTick;//点灯时间
	// uint16_t NextNumEn;	//点灯使能，表明C收到了上行帧可以编号下一个BCU了
	// uint8_t  NextNum;//点灯编号
}NumBCU_TypeDef;

/**
* @枚举功能  协调器信息结构体
*/
typedef struct
{
	/**
	timer.h文件中定义
	#define Period_WrReg1000_Defaul	(1000)//写1000寄存器周期,单位：ms
	#define Period_NumBCU_Defaul	(1000)//编号BCU周期,单位：ms
	#define Period_NWRst_Defaul	(1000)//复位R1s周期,单位：ms
	#define Period_NWRestart_Defaul	(1000)//复位R5min周期,单位：ms
	#define Period_HeartBeat_Defaul	(1000)//心跳周期,单位：ms
	#define Period_WriteNw_Default		(5000)//网络配置周期,单位：ms
	#define Period_ReadNw_Default		(2000)//网络查询周期,单位：ms
	*******************************************************************
	
	Coordinator[0].txPeriod[POLLTASK_WRREG1000]=Period_WrReg1000_Defaul;
	**/
	uint16_t txPeriod[POLLTASK_NUM];//点播发送周期
	uint16_t txCnt[POLLTASK_NUM];		//C轮询的次数
	uint8_t  txBCUNum[POLLTASK_NUM];//发送编号,1~40
	uint16_t txStopTick[POLLTASK_NUM];//停止发送秒计时
	
	/**
	rxBCUNum[0]	:接收编号,1~40
	rxBCUNum[1]	:接收编号,1~512	
	rxBCUNum[2]	:接收次数最多的BCU编号,1-40
	rxBCUNum[3]	:接收次数最多的BCU编号,1-512
	rxBCUNum[4]	:接收次数最少的BCU编号,1-40
	rxBCUNum[5]	:接收次数最少的BCU编号,1-512
	
	rxCntNow[MAXROUTER_Default]		:40个R接收次数均值，
	rxCntNow[MAXROUTER_Default+1]	:40个R接收次数最大值
	rxCntNow[MAXROUTER_Default+2]	:40个R接收次数最小值
	rxCntNow[MAXROUTER_Default+3]	:40个R接收次数为0的个数
	**/
	uint16_t  rxBCUNum[RXBCUNUM];//接收编号
	uint32_t rxCntNow[MAXROUTER_Default+4];		//当前接收Rn的次数
	uint32_t rxCntStatus[MAXROUTER_Default+4];		//当前接收Rn的次数

	uint32_t rxCntPre[MAXROUTER_Default];			//上次接收Rn的次数
	uint16_t rxCntErr[MAXROUTER_Default];			//当前接收Rn的次数与上次接收Rn次数的偏差
	uint16_t rxCntUnChange_Tick[MAXROUTER_Default];//当前接收Rn的次数与上次接收Rn次数的偏差持续不变化的持续时间
	uint16_t rxCntUnChange_TickPre[MAXROUTER_Default];//上次接收Rn的次数与上次接收Rn次数的偏差持续不变化的持续时间
  uint16_t R_Rate[MAXROUTER_Default];	 			//R的得包率
	uint16_t shortAdd[MAXROUTER_Default];			//接收到Router模块的短地址，由系统分配
	uint16_t lossCnt[MAXROUTER_Default];			//通讯故障的次数
	NumBCU_TypeDef Cfg;												//配置BCU编号	
}Coordinator_TypeDef;

/**
* @结构体功能  BCUData结构体
*/
typedef struct
{
	uint16_t U;			//单体电压(单位：mV)
	uint16_t R;			//单体内阻(单位：uΩ)
	uint16_t T;			//正极,负极柱温度(单位：℃)高字节正，低字节负
	uint16_t S; 		//单体状态
	uint16_t RB;    	//单体内阻基准(单位：uΩ)
	uint16_t RES[3]; 	//预留
}BCUData_TypeDef;
/**
* @结构体功能  BCUData校准结构体
*/
typedef struct
{
	float kU;//电压校准系数k,单位: NULL
	float kR;//内阻校准系数k,单位: NULL
	float kT1;//极柱温度校准系数k,单位: NULL
	float bU;//电压校准系数b,单位: NULL
	float bR;//内阻校准系数b,单位: NULL
	float bT1;//极柱温度校准系数b,单位: NULL
}BCUCalib_TypeDef;

/**
 * @结构体功能  BCU结构体
 */
typedef struct {
	uint16_t Num;					 //BCU编号
	BCUData_TypeDef data;	 //BCU数据
	BCUCalib_TypeDef calib;//BCU数据校准
} BCUInfo_TypeDef;


/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
COORDINATOR_EXT Coordinator_TypeDef Coordinator[3];
COORDINATOR_EXT BCUData_TypeDef BCUData[MAXBCU_Default];
COORDINATOR_EXT BCUInfo_TypeDef BCUInfo[MAXBCU_Default];
COORDINATOR_EXT uint8_t Cx;

COORDINATOR_EXT uint16_t numNextBcu_Tick;//点灯时间
COORDINATOR_EXT uint16_t numNextBcu_En;	//点灯使能，表明C收到了上行帧可以编号下一个BCU了
COORDINATOR_EXT uint8_t nextBCUNum;		//点灯编号
/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
COORDINATOR_EXT void vCoordinator_Init(void);
COORDINATOR_EXT void vBCUSlave_Proc(void);
COORDINATOR_EXT void vCommunicationFault_Proc(void);
COORDINATOR_EXT void vCC2530_RestTest(CC2530Cast_TypeDef castType);
COORDINATOR_EXT CC2530CmdRet_TypeDef eCC2530_NWInit(uint16_t ,uint16_t ,uint16_t );
COORDINATOR_EXT CC2530CmdRet_TypeDef eNwNum2PANID(uint16_t ,uint16_t ,uint16_t );
COORDINATOR_EXT CC2530CmdRet_TypeDef vCC2530_BaudInit(CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef ,CC2530BaudRate_TypeDef );
#endif /* COORDINATOR_H_ */
