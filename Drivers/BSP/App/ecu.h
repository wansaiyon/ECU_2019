/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: ecu.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/02		04:39:35
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
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
#define SLAVEID_Default			(16)//ECU默认通讯从站号
#define BATTJARNUM_Default	(120)//一个ECU默认组网监控120个BCU
#define MAXROUTER_Default		(40)//1coordinator默认组网40Router

#define JARNUM_C1_Default	((uint16_t)40)//C1默认组网节数
#define JARNUM_C2_Default	((uint16_t)40)//C2默认组网节数
#define JARNUM_C3_Default	((uint16_t)40)//C3默认组网节数

#define NWPARA_C1_Default	((uint16_t)5)//C1默认网络参数
#define NWPARA_C2_Default	((uint16_t)6)//C2默认网络参数
#define NWPARA_C3_Default	((uint16_t)7)//C3默认网络参数

#define BAUD_C_Default	((uint8_t)CC2530BAUDRATE_38400)//协调器默认波特率

#define VOLTLEVEL_Default	(HIGHVOLT)//ECU默认高压版本

//电流传感器型号定义
//充电型号定义
#define TKC400HAT_FS_A (400)  //额定电流400A,满量程电压4V
#define TKC200EKB_FS_A (200)  //额定电流200A,满量程电压4V
//放电型号定义
#define TKC50LB_FS_A 	(50)  //额定电流50A,满量程电压4V
#define TKC_FS_V 		(4)	  //厂商TKC满量程电压4V
//漏电流型号定义
#define LFB7_FS_A 	(100)	  //额定电流100mA,满量程电压5V
#define LFB7_FS_V    (5)      //厂商LFB7满量程电压5V

#define HALL_A_Default(x)	(Table_ECUHall[2*(x)])
#define HALL_V_Default(x)	(Table_ECUHall[2*(x)+1])
#define HALL_K_Default(x)	((float)HALL_A_Default(x)/HALL_V_Default(x))

#define CHNUM_U	((uint8_t)6)//电压通道数
#define CHNUM_I	((uint8_t)6)//电流通道数
#define CHNUM_T	((uint8_t)6)//环境温度通道数,这里设置为6为了printf打印不越界


#define CALIB_U_NUM		 (2) //电压校准的点数
#define CALIB_I_NUM		 (2) //电流校准的点数
#define CALIB_T_NUM		 (2) //环境温度校准的点数

/*
x代表ECUInfo.ID(不取5),含义如下：
			x=1:代表主1号ECU
			x=2:代表从2号ECU
			x=3:代表从3号ECU
			x=4:代表从4号ECU
y,z含义如下：
			y=1:代表ECU响应单体数据03功能码，ECU轮询单体寄存器的起止地址范围0x1000-0x2000
			z=8:代表03读1000~2000,一个单体数据占用8个寄存器 
			
			y=2:代表ECU响应单体电池交互操作10功能码，ECU轮询单体寄存器的起止地址范围0x2000-0x3000
			z=1:代表10写2000~3000,一个单体操作占用1个寄存器
			
例如1,PC读取物理量不连续单体电池数据：
			 主1号ECU第一组120节电压内阻温度等：0x1000~0x13BF		【1】
			 从2号ECU第二组120节电压内阻温度等：0x13C0~0x177F
			 从3号ECU第三组120节电压内阻温度等：0x1780~0x1B3F
			 从4号ECU第四组120节电压内阻温度等：0x1B40~0x1EFF
			 从5号ECU第五组 20节电压内阻温度等：0x1F00~0x1FA0
			
例如2,单体电池交互操作：
			 主1号ECU第一组120节操作：2000~2077				【1】
			 从2号ECU第二组120节操作：2078~20EF
			 从3号ECU第三组120节操作：20F0~2167
			 从4号ECU第四组120节操作：2168~21DF
			 从5号ECU第五组 20节操作：21E0~21F3

例如3,PC读取物理量连续单体电池数据：
			 主1号ECU第一组120节单体电压：0000~0077		【2】
			 从2号ECU第二组120节单体电压：0078~00EF
			 从3号ECU第三组120节单体电压：00F0~0167
			 从4号ECU第四组120节单体电压：0168~01DF
			 从5号ECU第五组 20节单体电压：01E0~01F3

		 	 主1号ECU第一组120节单体内阻：0200~0277		【2】
			 从2号ECU第二组120节单体内阻：0278~02EF
			 从3号ECU第三组120节单体内阻：02F0~0367
			 从4号ECU第四组120节单体内阻：0368~03DF
			 从5号ECU第五组 20节单体内阻：03E0~03F3

			 主1号ECU第一组120节单体温度：0400~0477		【2】
			 从2号ECU第二组120节单体温度：0478~04EF
			 从3号ECU第三组120节单体温度：04F0~0567
			 从4号ECU第四组120节单体温度：0568~05DF
			 从5号ECU第五组 20节单体温度：05E0~05F3

			主1号ECU第一组120节单体内阻基准：0640~0477 	【3】
			从2号ECU第二组120节单体内阻基准：0478~04EF
			从3号ECU第三组120节单体内阻基准：04F0~0567
			从4号ECU第四组120节单体内阻基准：0568~05DF
			从5号ECU第五组 20节单体内阻基准：05E0~05F3

			主1号ECU第一组120节单体状态：0840~0477 		【3】
			从2号ECU第二组120节单体状态：0478~04EF
			从3号ECU第三组120节单体状态：04F0~0567
			从4号ECU第四组120节单体状态：0568~05DF
			从5号ECU第五组 20节单体状态：05E0~05F3

			主1号ECU第一组120节单体SOC：0A40~0477 	【3】
			从2号ECU第二组120节单体SOC：0478~04EF
			从3号ECU第三组120节单体SOC：04F0~0567
			从4号ECU第四组120节单体SOC：0568~05DF
			从5号ECU第五组 20节单体SOC：05E0~05F3

			ECUInfo.bcuRegAddr[0] = ECU_REG_START(ECUInfo.ECUID,1,8);//0x1000-0x2000	单体电压、内阻、温度	【1】
			ECUInfo.bcuRegAddr[1] = ECU_REG_END(ECUInfo.ECUID,1,8);
			ECUInfo.bcuRegAddr[2] = ECU_REG_START(ECUInfo.ECUID,2,1);//0x2000-0x3000	单体操作			【1】
			ECUInfo.bcuRegAddr[3] = ECU_REG_END(ECUInfo.ECUID,2,1);

			ECUInfo.bcuRegAddr[4] = ECU_REG_START2(ECUInfo.ECUID,0,1);//0x0000-0x0200	单体电压			【2】
			ECUInfo.bcuRegAddr[5] = ECU_REG_END2(ECUInfo.ECUID,0,1);
			ECUInfo.bcuRegAddr[6] = ECU_REG_START2(ECUInfo.ECUID,1,1);//0x0200-0x0400	单体内阻			【2】
			ECUInfo.bcuRegAddr[7] = ECU_REG_END2(ECUInfo.ECUID,1,1);
			ECUInfo.bcuRegAddr[8] = ECU_REG_START2(ECUInfo.ECUID,2,1);//0x0400-0x0600	单体温度			【2】
			ECUInfo.bcuRegAddr[9] = ECU_REG_END2(ECUInfo.ECUID,2,1);

			ECUInfo.bcuRegAddr[10] = ECU_REG_START3(ECUInfo.ECUID,0,1);//0x0640-0x0840	单体内阻基准		【3】
			ECUInfo.bcuRegAddr[11] = ECU_REG_END3(ECUInfo.ECUID,0,1);
			ECUInfo.bcuRegAddr[12] = ECU_REG_START3(ECUInfo.ECUID,1,1);//0x0840-0x0A40	单体状态			【3】
			ECUInfo.bcuRegAddr[13] = ECU_REG_END3(ECUInfo.ECUID,1,1);
			ECUInfo.bcuRegAddr[14] = ECU_REG_START3(ECUInfo.ECUID,2,1);//0x0A40-0x0C40	单体SOC			【3】
			ECUInfo.bcuRegAddr[15] = ECU_REG_END3(ECUInfo.ECUID,2,1);

*/													 
#define ECU_REG_START(x,y,z)	((y)*(0x1000)+MAXROUTER_Default*3*(z)*((x)-1))
#define ECU_REG_END(x,y,z)		((y)*(0x1000)+MAXROUTER_Default*3*(z)*(x)-1)

#define ECU_REG_START2(x,y,z)	((y)*(0x0200)+MAXROUTER_Default*3*(z)*((x)-1))
#define ECU_REG_END2(x,y,z)		((y)*(0x0200)+MAXROUTER_Default*3*(z)*(x)-1)

#define ECU_REG_START3(x,y,z)	(((y)*0x200+0x0640)+MAXROUTER_Default*3*(z)*((x)-1))
#define ECU_REG_END3(x,y,z)		(((y)*0x200+0x0640)+MAXROUTER_Default*3*(z)*(x)-1)

//tobe delete
//03读1000~2000,一个单体数据占用8个寄存器 
#define ECU_REG_START_03(x)  (0x1000+MAXROUTER_Default*3*8*((x)-1))
#define ECU_REG_END_03(x)    (0x1000+MAXROUTER_Default*3*8*(x)-1)
//10写2000~3000,一个单体操作占用1个寄存器
#define ECU_REG_START_10(x)  (0x2000+MAXROUTER_Default*3*((x)-1))
#define ECU_REG_END_10(x)    (0x2000+MAXROUTER_Default*3*(x)-1)


//写入协调器网络参数使能定义
#define WRITENW_C1_EN 0x01
#define WRITENW_C2_EN 0x02
#define WRITENW_C3_EN 0x04
//查询协调器网络参数使能定义
#define READNW_C1_EN 0x01
#define READNW_C2_EN 0x02
#define READNW_C3_EN 0x04
//ECU工作模式
#define IS_ECUMODE(x)	 (ECUInfo.runMode==(x))	//ECU是否在运行模式x
#define ECUMODE_ATTACH(x)	{ECUInfo.runMode=(x);}//ECU模式绑定定义 
#define ECUMODE_Normal   (0x00)//正常模式
#define ECUMODE_Product  (0x01)//生产模式
#define ECUMODE_Debug    (0x02)//调试模式
#define ECUMODE_Calib    (0x04)//校准模式
#define ECUMODE_CfgNw    (0x08)//协调器网络写入模式,按键与接收到配置帧同时满足方能触发
#define ECUMODE_ReadNw   (0x10)//协调器网络读取模式,按键触发,当运行时读取的参数与存储的参数有出入时，重写存储参数直到成功

//ECU ID
#define IS_MASTER_ECU()   (ECUInfo.ECUID==ID1_MASTER_ECU)
#define ID1_MASTER_ECU		(0x01)//主1ECU采集组信息，ID=1
#define ID2_SLAVE_ECU			(0x02)//从2ECU采集组信息，ID=2
#define ID3_SLAVE_ECU			(0x03)//从3ECU采集组信息，ID=3
#define ID4_SLAVE_ECU			(0x04)//从4ECU采集组信息，ID=4
#define ID5_SLAVE_ECU			(0x05)//从5ECU采集组信息，ID=5

//print ecu running mode
#define print_ECUMode()		{printf("ECU Running Mode:%d	WriteNw_En:%d	ReadNw_En:%d\r\n",\
ECUInfo.runMode,ECUInfo.nwPara.WriteNw_En,ECUInfo.nwPara.ReadNw_En);}

//print ecu running time
#define print_ECUOnLineTime() {printf("* 	 %4d年%2d月%2d日%2d时%2d分%2d秒  \r\n",\
ECUInfo.ECUOnLineTime._Year,\
ECUInfo.ECUOnLineTime._Month,\
ECUInfo.ECUOnLineTime._Day,\
ECUInfo.ECUOnLineTime._Hour,\
ECUInfo.ECUOnLineTime._Min,\
ECUInfo.ECUOnLineTime._Sec);}

#define print_RTC()	{printf("* 	 %04d年%02d月%02d日%02d时%02d分%02d秒  \r\n",\
2000+ECUInfo.ECUOnLineTime.data.Year,\
ECUInfo.ECUOnLineTime.data.Month,\
ECUInfo.ECUOnLineTime.data.Date,\
ECUInfo.ECUOnLineTime.time.Hours,\
ECUInfo.ECUOnLineTime.time.Minutes,\
ECUInfo.ECUOnLineTime.time.Seconds);}


//打印信息定义
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
 * @枚举功能    ECU高压低压版本
 */
typedef enum {
	LOWVOLT =0x00,
	HIGHVOLT =0x01
} ECUVoltLevel_TypeDef;

/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
 * @结构体功能  ECU硬件版本结构体
 */
typedef struct {
	char *swVer_ECU;		//ECU软件版本号,10个字节V001B01D00
	char *swVer_BCU;		//BCU软件版本号,10个字节V001B01D00
	char *hwVer_ECU;		//ECU硬件版本号,4个字节V2.0
	char *hwVer_BCU;	    //BCU硬件版本号,4个字节V4.0
	char *osVer_ECU;		//ECU系统版本号,v9.0.0
	ECUVoltLevel_TypeDef voltLevel;
} ECUVer_TypeDef;

/**
 * @结构体功能  ECU网络参数结构体
 */
 

typedef struct {
	uint8_t cnt;//网络全部配置成功时执行CC2530_NWInit次数
	uint8_t confirmTimes[3];//开始初始化无线网络
	uint8_t WriteNw_En;	 //网络参数写入使能
	uint8_t ReadNw_En;	 //网络参数查询使能
	uint8_t tag_WriteNw;//网络参数写入标志
	uint8_t tag_ReadNw;//网络参数查询标志
	uint16_t periodWriteNw;//网络参数配置周期，单位ms
	uint16_t periodReadNw;//网络参数查询周期，单位ms
	
	uint16_t nwNum_C[3];
	uint16_t panid_C[3];
	uint16_t panid2_C[3];//备用panid
	uint8_t chanel_C[3];
	uint8_t jarNum_C[3];
} ECUNWPara_TypeDef;

/**
 * @结构体功能  ECU传感器结构体
 */
typedef struct {
	uint16_t  HALL_A_Charge;											//充电电流传感器额定输入电流
	uint16_t  HALL_V_Charge;											//充电电流传感器额定输出电压
	uint16_t  HALL_A_DisCharge;											//放电电流传感器额定输入电流
	uint16_t  HALL_V_DisCharge;											//放电电流传感器额定输出电压
	uint16_t  HALL_A_LeakageCurr;										//漏电电流流传感器额定输入电流
	uint16_t  HALL_V_LeakageCurr;										//漏电电流流感器额定输出电压
} ECUHall_TypeDef;

/**
 * @结构体功能  ECU校准参数结构体
 */
typedef struct {
	
	uint8_t En_U;//组电压校准使能
	uint8_t En_I;//组电流校准使能
	uint8_t En_T;//环境温度校准使能
	
	float U[CALIB_U_NUM][2];//组电压校准样本数据
	float I[CALIB_I_NUM][2];//组电流校准样本数据
	float T[CALIB_T_NUM][2];//环境温度校准样本数据
	
	float kU[CHNUM_U];//组电压校准系数k,单位: NULL
	float kI[CHNUM_I];//组电流校准系数k,单位：NULL
	float kT[CHNUM_T];//环境温度校准系数k,单位：NULL
	float bU[CHNUM_U];//组电压校准系数b,单位：NULL
	float bI[CHNUM_I];//组电流校准系数b,单位：NULL
	float bT[CHNUM_T];//环境温度校准系数b,单位：NULL	
	
	float squarePoorU[4];//方差分析指标: 回归平方和,剩余平方和,回归平方差,剩余平方差
	float squarePoorI[4];
	float squarePoorT[4];

} ECUCalib_TypeDef;

/**
 * @结构体功能  ECU组数据结构体
 */
typedef struct {
	float U[CHNUM_U];//组电压,单位: V
	float I[CHNUM_I];//组电流,单位: A
	float T[CHNUM_T];//环境温度,单位: ℃
	
	ECUCalib_TypeDef calib;//ECU校准
	
	float s_kHall[3];//霍尔电流传感器参数,单位：安培每伏特A/V,0:充电电流，1：放电电流，2：漏电流
	
	float p_kU;//通讯协议,组电压传输系数k,单位：NULL
	float p_bU;//通讯协议,组电压传输系数b,单位：NULL
	float p_kI;//通讯协议,组电流传输系数k,单位：NULL
	float p_bI;//通讯协议,组电流传输系数b,单位：NULL
	float p_kT;//通讯协议,环境温度传输系数k,单位：NULL
	float p_bT;//通讯协议,环境温度传输系数b,单位：NULL
} ECUGrpData_TypeDef;

/**
* @枚举功能  ECU运行时间结构体
*/
typedef struct
{
	uint8_t _Year;     //BCU上电运行时间，单位：年
	uint8_t _Month; 	 //BCU上电运行时间，单位：月
	uint16_t _Day; 		 //BCU上电运行时间，单位：日
	uint8_t _Hour;     //BCU上电运行时间，单位：小时
	uint8_t _Min; 		 //BCU上电运行时间，单位：分钟
	uint8_t _Sec; 		 //BCU上电运行时间，单位：秒
	float Second; 	 	 //BCU上电运行时间，单位：秒,一直统计直到溢出
	
	RTC_DateTypeDef data;
	RTC_TimeTypeDef time;
}ECUOnLineTime_TypeDef;		

/**
 * @结构体功能  ECU结构体
 */
typedef struct {
	 uint8_t slaveID; //modbus从机地址
	 uint8_t ECUID;//主从ECU的编号,范围:1,2,3,4,5分别代表主1#ECU,从2#ECU,从3#ECU,从4#ECU,从5#ECU
	 uint16_t bias; //一组电池多ECU时的偏移地址

	 uint8_t ledBCDNum;//8421BCD点灯显示从机号slaveID
	 uint8_t BeepNum;//4个LED只支持1~15个地址，对于16~30的地址喇叭鸣叫1次，31~45的地址喇叭鸣叫2次，类推
	 uint8_t runMode;//ECU运行模式
	 uint8_t battJarNum;//单个ECU监控的电池节数
	 uint8_t baud;//波特率
	 ECUVer_TypeDef Ver; //软件硬件版本号
	 ECUNWPara_TypeDef nwPara;//zigbee网络参数
	 ECUGrpData_TypeDef grpData;//组采样数据
	 ECUOnLineTime_TypeDef ECUOnLineTime;//ECU运行时间
	 ECUHall_TypeDef hall;//霍尔电流传感器
	 uint8_t En_IwdgRst;//使能看门狗复位
	 uint16_t bcuRegAddr[20];//响应后台03/10读写BCU，地址起始位置，详见ECU_REG_START/ECU_REG_END
	 uint8_t print;//打印
} ECUInfo_TypeDef;

/**
 * @结构体功能  **结构体
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
 * @结构体功能  **结构体
 */
typedef struct {
	uint16_t ulEventBit;
	void (*pFun)(void);
} EventDoWithTable_TypeDef;

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
/**
 * @全局变量功能    **全局变量,单位：
 * @复位状态			
 * @注意事项
 */
ECU_EXT ECUInfo_TypeDef ECUInfo;

/**
 * @全局变量功能    **全局变量
 * @复位状态
 * @注意事项
 */
ECU_EXT uint16_t ulEventBits;

/**
 * @全局变量功能    **全局变量
 * @复位状态
 * @注意事项
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


