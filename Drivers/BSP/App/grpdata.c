/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: grpdata.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/04		01:03:15
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define GRPDATA_GLOBALS
//#include "Include.h"
#include "grpdata.h"


/**********************************************************************************/
/*      私有变量声明              	                                		      */
/**********************************************************************************/
/**
 * @全局变量功能    采用100阶FIR滤波器,matlab生成系数全局变量,单位：
									Filter Order:100,Fpass:7HZ,Fstop:8Hz,Fs:50Hz
									Response Type:Lowpass,Design Method:FIR,Least-squares
									Purpose:to Avoid RC Fault
 * @复位状态			0x00
 * @注意事项
 */
float h[N_FIR]={4.8776e-05,0.00086458,0.0010997,0.00035534,-0.00092516,-0.0016653,-0.0010344,0.00069986,0.0021731,0.0019664,-7.9178e-05,-0.0024577,-0.0030619,-0.0010074,0.0023291,0.004158,0.0025655,-0.0015988,-0.0050231,-0.0045139,0.0001103,0.0053718,0.0066717,0.0022296,-0.0048875,-0.008754,-0.0054256,0.0032471,0.010376,0.0093777,-0.00013732,-0.011056,-0.01388,-0.0047546,0.0102,0.018633,0.011815,-0.0070095,-0.023274,-0.021752,0.0001557,0.027412,0.036437,0.013514,-0.03068,-0.062764,-0.046221,0.032774,0.15107,0.25728,0.29984,0.25728,0.15107,0.032774,-0.046221,-0.062764,-0.03068,0.013514,0.036437,0.027412,0.0001557,-0.021752,-0.023274,-0.0070095,0.011815,0.018633,0.0102,-0.0047546,-0.01388,-0.011056,-0.00013732,0.0093777,0.010376,0.0032471,-0.0054256,-0.008754,-0.0048875,0.0022296,0.0066717,0.0053718,0.0001103,-0.0045139,-0.0050231,-0.0015988,0.0025655,0.004158,0.0023291,-0.0010074,-0.0030619,-0.0024577,-7.9178e-05,0.0019664,0.0021731,0.00069986,-0.0010344,-0.0016653,-0.00092516,0.00035534,0.0010997,0.00086458,4.8776e-05};

#if  T_LOOKUPTABLE==(1)
const NTC_LookUpTable_TypeDef NTC_ConstP = {
	//Temperature
	{ 1750.0, 1740.0, 1730.0, 1720.0, 1710.0, 1700.0, 1690.0, 1680.0, 1670.0,
	1660.0, 1650.0, 1640.0, 1630.0, 1620.0, 1610.0, 1600.0, 1590.0, 1580.0,
	1570.0, 1560.0, 1550.0, 1540.0, 1530.0, 1520.0, 1510.0, 1500.0, 1490.0,
	1480.0, 1470.0, 1460.0, 1450.0, 1440.0, 1430.0, 1420.0, 1410.0, 1400.0,
	1390.0, 1380.0, 1370.0, 1360.0, 1350.0, 1340.0, 1330.0, 1320.0, 1310.0,
	1300.0, 1290.0, 1280.0, 1270.0, 1260.0, 1250.0, 1240.0, 1230.0, 1220.0,
	1210.0, 1200.0, 1190.0, 1180.0, 1170.0, 1160.0, 1150.0, 1140.0, 1130.0,
	1120.0, 1110.0, 1100.0, 1090.0, 1080.0, 1070.0, 1060.0, 1050.0, 1040.0,
	1030.0, 1020.0, 1010.0, 1000.0, 990.0, 980.0, 970.0, 960.0, 950.0, 940.0,
	930.0, 920.0, 910.0, 900.0, 890.0, 880.0, 870.0, 860.0, 850.0, 840.0, 830.0,
	820.0, 810.0, 800.0, 790.0, 780.0, 770.0, 760.0, 750.0, 740.0, 730.0, 720.0,
	710.0, 700.0, 690.0, 680.0, 670.0, 660.0, 650.0, 640.0, 630.0, 620.0, 610.0,
	600.0, 590.0, 580.0, 570.0, 560.0, 550.0, 540.0, 530.0, 520.0, 510.0, 500.0,
	490.0, 480.0, 470.0, 460.0, 450.0, 440.0, 430.0, 420.0, 410.0, 400.0, 390.0,
	380.0, 370.0, 360.0, 350.0, 340.0, 330.0, 320.0, 310.0, 300.0, 290.0, 280.0,
	270.0, 260.0, 250.0, 240.0, 230.0, 220.0, 210.0, 200.0, 190.0, 180.0, 170.0,
	160.0, 150.0, 140.0, 130.0, 120.0, 110.0, 100.0, 90.0, 80.0, 70.0, 60.0,
	50.0 },
#ifdef USE_10BITSADC			//使用10位ADC
	//AD
	{ 52.0, 53.0, 54.0, 55.0, 56.0, 58.0, 59.0, 60.0, 62.0, 63.0, 64.0, 66.0, 67.0,
		69.0, 70.0, 72.0, 74.0, 75.0, 77.0, 79.0, 81.0, 83.0, 85.0, 87.0, 89.0, 91.0,
		93.0, 95.0, 97.0, 100.0, 102.0, 105.0, 107.0, 110.0, 112.0, 115.0, 118.0,
		121.0, 124.0, 127.0, 130.0, 133.0, 136.0, 139.0, 143.0, 146.0, 150.0, 154.0,
		157.0, 161.0, 165.0, 169.0, 173.0, 178.0, 182.0, 187.0, 191.0, 196.0, 201.0,
		206.0, 211.0, 216.0, 221.0, 226.0, 232.0, 238.0, 243.0, 249.0, 255.0, 261.0,
		268.0, 274.0, 280.0, 287.0, 294.0, 301.0, 308.0, 315.0, 322.0, 330.0, 337.0,
		345.0, 353.0, 361.0, 369.0, 377.0, 385.0, 394.0, 402.0, 411.0, 420.0, 428.0,
		437.0, 446.0, 456.0, 465.0, 474.0, 483.0, 493.0, 502.0, 512.0, 522.0, 531.0,
		541.0, 551.0, 560.0, 570.0, 580.0, 590.0, 600.0, 609.0, 619.0, 629.0, 639.0,
		648.0, 658.0, 667.0, 677.0, 686.0, 695.0, 705.0, 714.0, 723.0, 732.0, 741.0,
		749.0, 758.0, 766.0, 775.0, 783.0, 791.0, 799.0, 806.0, 814.0, 821.0, 829.0,
		836.0, 843.0, 850.0, 856.0, 863.0, 869.0, 875.0, 881.0, 887.0, 892.0, 898.0,
		903.0, 908.0, 913.0, 918.0, 922.0, 927.0, 931.0, 935.0, 939.0, 943.0, 947.0,
		951.0, 954.0, 957.0, 960.0, 964.0, 966.0, 969.0, 972.0, 975.0, 977.0, 979.0,
		982.0, 984.0 }
#else											//使用12位ADC
	 { 206.0, 211.0, 215.0, 220.0, 225.0, 230.0, 235.0, 241.0, 246.0, 252.0, 257.0,
			263.0, 269.0, 275.0, 282.0, 288.0, 295.0, 302.0, 309.0, 316.0, 323.0, 331.0,
			338.0, 346.0, 355.0, 363.0, 372.0, 381.0, 390.0, 399.0, 408.0, 418.0, 428.0,
			439.0, 449.0, 460.0, 471.0, 483.0, 494.0, 506.0, 519.0, 531.0, 544.0, 558.0,
			571.0, 585.0, 600.0, 614.0, 629.0, 645.0, 661.0, 677.0, 694.0, 711.0, 728.0,
			746.0, 764.0, 783.0, 802.0, 822.0, 842.0, 863.0, 884.0, 905.0, 927.0, 950.0,
			973.0, 996.0, 1020.0, 1045.0, 1070.0, 1096.0, 1122.0, 1148.0, 1175.0, 1203.0,
			1231.0, 1260.0, 1289.0, 1319.0, 1349.0, 1380.0, 1411.0, 1443.0, 1475.0,
			1508.0, 1541.0, 1574.0, 1609.0, 1643.0, 1678.0, 1713.0, 1749.0, 1785.0,
			1822.0, 1859.0, 1896.0, 1933.0, 1971.0, 2009.0, 2048.0, 2086.0, 2125.0,
			2163.0, 2202.0, 2241.0, 2280.0, 2320.0, 2359.0, 2398.0, 2437.0, 2476.0,
			2515.0, 2553.0, 2592.0, 2630.0, 2668.0, 2706.0, 2744.0, 2781.0, 2818.0,
			2855.0, 2891.0, 2927.0, 2962.0, 2997.0, 3031.0, 3065.0, 3098.0, 3131.0,
			3163.0, 3194.0, 3225.0, 3255.0, 3285.0, 3314.0, 3342.0, 3370.0, 3397.0,
			3424.0, 3449.0, 3474.0, 3499.0, 3523.0, 3546.0, 3568.0, 3590.0, 3611.0,
			3631.0, 3651.0, 3670.0, 3689.0, 3707.0, 3724.0, 3740.0, 3756.0, 3772.0,
			3787.0, 3801.0, 3815.0, 3828.0, 3841.0, 3853.0, 3865.0, 3876.0, 3887.0,
			3897.0, 3907.0, 3917.0, 3926.0, 3935.0 }
 #endif
};

#elif	T_LOOKUPTABLE==(0)
/**
* @枚举功能  NTC热电偶状态结构体实例变量
*/
const NTC_StandardPara_TypeDef ntc_std_paramtr = {
		3.3f,               // Vref
		4096.0f,           	// A:D resolution
		10000,              // NTC resistance
		1,                  // NTC initial tolerance
		0,                  // NTC B0/50, none
		3380,               // NTC B25/50
		3322,               // NTC B25/80
		3435,               // NTC B25/85
		3446,               // NTC B25/100
		0,                  // NTC other Beta value
		1,                  // NTC beta tolerance
		// 3.32k 1% 100ppm
		10000,               // Series resistor value
		1,                  // Series resistor tolerance
		200                 // Series Resistor tempco ppm
};
#endif

/**********************************************************************************/
/*      私有函数声明              	                                              */
/**********************************************************************************/
static void vGrpVolt_Sample_Calib(void);
static void vGrpCurrent_Sample_Calib(void);
static void vGrpEnvTemperature_Sample_Calib(void);
#if T_LOOKUPTABLE==(1)
static float fLookUpTable_1D(uint16_t u0, const uint16_t bp0[], const float table[], uint8_t maxIndex);		
#elif T_LOOKUPTABLE==(0)
static float fGet_NTC_Res_ViaAD(uint16_t adValue);
static float fGet_NTC_Temp(uint16_t adValue); 
#endif
static void vDataAnalysis_Filter(uint8_t filter_Method);
static uint8_t ucLinearRegression(float *data, uint8_t rows, float *a, float *b, float *SquarePoor);


/**********************************************************************************/
/*      私有函数实现              	                                              */
/**********************************************************************************/
/*Convert AD Values 2 Group Voltage*/
static void vGrpVolt_Sample_Calib(void)
{
	uint8_t i;
	for (i=0;i<6;i++)	
	{
		// sample calculate
		if(ECUInfo.Ver.voltLevel ==HIGHVOLT)			
			ECUInfo.grpData.U[i]=(ADC1Filter[i+3]*3.3f/4096)/0.00332226f;			
		else 
			ECUInfo.grpData.U[i]=(ADC1Filter[i+3]*3.3f/4096)/0.02597f;
		
		//calibration,线性回归(推荐三点校准，精度比两点校准更好)
		if(ECUInfo.grpData.calib.En_U==1)
		{		
			if(ucLinearRegression((float*)ECUInfo.grpData.calib.U, CALIB_U_NUM, &ECUInfo.grpData.calib.bU[0], &ECUInfo.grpData.calib.kU[0], ECUInfo.grpData.calib.squarePoorU)==1)
				ECUInfo.grpData.U[i]=ECUInfo.grpData.calib.bU[0] + ECUInfo.grpData.calib.kU[0]* ECUInfo.grpData.U[i];
		}				
		//protocol
		GrpV[i] =ECUInfo.grpData.U[i]*ECUInfo.grpData.p_kU+ECUInfo.grpData.p_bU;
	}	
}
/*Convert AD Values 2 Group Current*/
static void vGrpCurrent_Sample_Calib(void)
{
	// sample calculate
	//0,2 充
	ECUInfo.grpData.I[0]=ECUInfo.grpData.s_kHall[0]*33.0f/20*(ADC3Filter[0]*3.3f/4096);
	ECUInfo.grpData.I[2]=ECUInfo.grpData.s_kHall[0]*33.0f/20*(ADC3Filter[2]*3.3f/4096);
	//1,3放
	ECUInfo.grpData.I[1]=ECUInfo.grpData.s_kHall[1]*33.0f/20*(ADC3Filter[1]*3.3f/4096);
	ECUInfo.grpData.I[3]=ECUInfo.grpData.s_kHall[1]*33.0f/20*(ADC3Filter[3]*3.3f/4096);
	//4,5漏电流
	ECUInfo.grpData.I[4]=ECUInfo.grpData.s_kHall[2]*33.0f/20*(ADC3Filter[4]*3.3f/4096);
	ECUInfo.grpData.I[5]=ECUInfo.grpData.s_kHall[2]*33.0f/20*(ADC3Filter[5]*3.3f/4096);
	
	//calibration,线性回归(推荐三点校准，精度比两点校准更好)
	if(ECUInfo.grpData.calib.En_U==1)
	{	
		uint8_t i;
		for (i=0;i<6;i++)	
		{		
			if(ucLinearRegression((float*)ECUInfo.grpData.calib.I, CALIB_U_NUM, &ECUInfo.grpData.calib.bI[0], &ECUInfo.grpData.calib.kI[0], ECUInfo.grpData.calib.squarePoorI)==1)
			{
				ECUInfo.grpData.calib.bI[0]*=(1/ECUInfo.grpData.s_kHall[0]/10.0f);
				ECUInfo.grpData.I[i]=ECUInfo.grpData.calib.bI[0] + ECUInfo.grpData.calib.kI[0]* ECUInfo.grpData.I[i];
			}
		}
	}	
	//protocol
	GrpI[0] =ECUInfo.grpData.I[0]*ECUInfo.grpData.p_kI+ECUInfo.grpData.p_bI;
	GrpI[1] =ECUInfo.grpData.I[1]*(-1.0f)*ECUInfo.grpData.p_kI+ECUInfo.grpData.p_bI;
	GrpI[2] =ECUInfo.grpData.I[2]*ECUInfo.grpData.p_kI+ECUInfo.grpData.p_bI;
	GrpI[3] =ECUInfo.grpData.I[3]*(-1.0f)*ECUInfo.grpData.p_kI+ECUInfo.grpData.p_bI;
	GrpI[4] =ECUInfo.grpData.I[4]*ECUInfo.grpData.p_kI+ECUInfo.grpData.p_bI;
	GrpI[5] =ECUInfo.grpData.I[5]*ECUInfo.grpData.p_kI+ECUInfo.grpData.p_bI;
	GrpI[8] =GrpI[5];
}
/*Convert AD Values 2 Temperature*/
static void vGrpEnvTemperature_Sample_Calib(void)
{
	uint8_t i;
	for (i=0;i<3;i++)	
	{
		// sample calculate
		#if T_LOOKUPTABLE==(1)	
			ECUInfo.grpData.T[i] = fLookUpTable_1D(ADC1Filter[i], NTC_ConstP.uDLookupTable1_bp01Data, NTC_ConstP.uDLookupTable1_tableData, 170U);
		#elif T_LOOKUPTABLE==(0)
			ECUInfo.grpData.T[i]=fGet_NTC_Temp(ADC1Filter[i]);
		#endif
		
		//calibration,线性回归(推荐三点校准，精度比两点校准更好)
		if(ECUInfo.grpData.calib.En_T==1)
		{		
			if(ucLinearRegression((float*)ECUInfo.grpData.calib.T, CALIB_T_NUM, &ECUInfo.grpData.calib.bT[0], &ECUInfo.grpData.calib.kT[0], ECUInfo.grpData.calib.squarePoorT)==1)
				ECUInfo.grpData.T[i]=ECUInfo.grpData.calib.bT[0] + ECUInfo.grpData.calib.kT[0]* ECUInfo.grpData.T[i];
		}				
		//protocol
		GrpT[0] =ECUInfo.grpData.T[0]*ECUInfo.grpData.p_kT+ECUInfo.grpData.p_bT;
		GrpT[1] =ECUInfo.grpData.T[1]*ECUInfo.grpData.p_kT+ECUInfo.grpData.p_bT;
		GrpT[2] =ECUInfo.grpData.T[2]*ECUInfo.grpData.p_kT+ECUInfo.grpData.p_bT;
	}	
}

#if T_LOOKUPTABLE==(1)
/******************************************************************************
 * @函数名称：Look1_binlxpw
 * @函数功能：AD码-温度拟合曲线对应的一维查找表
 * @输入参数：
			  u0		：温度采样通道的AD码
			  bp0		：ADC
			  table 	：Temperature
			  maxIndex	
 * @输出参数：uint8_t
 * @算法思路： 1.搜索方法:二分法
			   2.插值方法:线性
			   3.外推方法:线性
 * @使用资源：Simulink模型生成C代码
 * @注意事项：
 ******************************************************************************/
static float fLookUpTable_1D(uint16_t u0, const uint16_t bp0[], const float table[], uint8_t maxIndex)
{
    uint32_t frac;
    uint16_t iRght;
    uint16_t iLeft;
    uint16_t bpIdx;

    if (u0 <= bp0[0]) 
    {
        iLeft = 0;
        frac = (u0 - bp0[0]) / (bp0[1] - bp0[0]);
    } 
    else if (u0 < bp0[maxIndex]) 
    {
        /* Binary Search */
        bpIdx = maxIndex >> 1;
        iLeft = 0;
        iRght = maxIndex;
        while (iRght - iLeft > 1) 
        {
            if (u0 < bp0[bpIdx]) 
            {
                iRght = bpIdx;
            } 
            else 
            {
                iLeft = bpIdx;
            }

            bpIdx = (iRght + iLeft) >> 1;
        }
        frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1] - bp0[iLeft]);
    } 
    else 
    {
        iLeft = maxIndex - 1;
        frac = (u0 - bp0[maxIndex - 1]) / (bp0[maxIndex] - bp0[maxIndex - 1]);
    }
    
    return (table[iLeft + 1] - table[iLeft]) * frac + table[iLeft];
}
#elif T_LOOKUPTABLE==(0)
/******************************************************************************
* @函数名称：float Get_NTC_Res_ViaAD(uint16_t adValue)
* @函数功能：由AD采样码求解热电偶阻值
* @输入参数：adValue  :AD采样码
*				   
* @输出参数：float : 热电偶阻值
* @算法思路：方案二：通过B值公式计算热电偶温度
* @使用资源：
* @注意事项：
******************************************************************************/
static float fGet_NTC_Res_ViaAD(uint16_t adValue)
{
	float adv = ntc_std_paramtr.vref / ntc_std_paramtr.ad_resolution * (float)adValue;
	return (ntc_std_paramtr.vref / ((ntc_std_paramtr.vref - adv) / ntc_std_paramtr.sres_res) - ntc_std_paramtr.sres_res);
}

/******************************************************************************
* @函数名称：float Get_NTC_Res_ViaAD(uint16_t adValue)
* @函数功能：求取NTC温度
* @输入参数：adValue  :AD码
*				   
* @输出参数：float : 温度值
* @算法思路：
			斯坦哈特-哈特三阶公式
			T=B/ln(R/r_inf)
			r_inf=R0*exp(-B/T0)
* @使用资源：
* @注意事项：
*			R0:25摄氏度对应电阻
*			R:当前电阻
*			T0=(273.15+25）:25摄氏度对应的热力学温度298.15
*			B值：B25/50=ln(R50/R25)/(1/(273.15+50)-1/(273.15+25))

******************************************************************************/
static float fGet_NTC_Temp(uint16_t adValue)
{
	float ntc_res = 0.0f;
	int beta = ntc_std_paramtr.ntc_beta_2550;
	ntc_res = fGet_NTC_Res_ViaAD(adValue);
	return (beta / (log(ntc_res / (ntc_std_paramtr.ntc_res * exp(-beta / 298.0f)))) - 273.0f);
}
#endif


/*Algorithm Of Filter, TBD:	DataAnalysis*/
void vDataAnalysis_Filter(uint8_t filter_Method)
{
	uint16_t i;
	uint16_t j;
	float sum = 0;
	uint8_t count;
	if(filter_Method==MEAN_FILTER)
	{
		/***********ADC1Filter[ADC1_M]************/
		for(i=0;i<ADC1_M;i++)
		{
			for(count=0;count<ADC1_N;count++)
			{
				sum += ADC1Buf[count][i];
			}
			ADC1Filter[i]=sum/ADC1_N;
			sum=0;
		}
		/***********ADC3Filter[ADC3_M]************/
		for(j=0;j<ADC3_M;j++)
		{
			for(count=0;count<ADC3_N;count++)
			{
				sum += ADC3Buf[count][j];
			}
			ADC3Filter[j]=sum/ADC3_N;
			sum=0;
		}
	}
	else if(filter_Method==FIRSTORDER_FILTER)
	{
				;//do something here
	}
	else if(filter_Method==FIR_FILTER_MATLAB)
	{		
		/***********ADC1Filter[ADC1_M]************/
		for(i=0;i<ADC1_M;i++)
		{
			ADC1Filter[i]=0;
		}
		for(i=0;i<ADC1_M;i++)
		{
			for(count=0;count<ADC1_N;count++)
			{	
				ADC1Filter[i]=ADC1Filter[i]+ADC1Buf[count][i]*h[ADC1_N-count-1];
			}
		}
		/***********ADC3Filter[ADC3_M]************/
		for(i=0;i<ADC3_M;i++)
		{
			ADC3Filter[i]=0;
		}
		for(i=0;i<ADC3_M;i++)
		{
			for(count=0;count<ADC3_N;count++)
			{	
				ADC3Filter[i]=ADC3Filter[i]+ADC3Buf[count][i]*h[ADC3_N-count-1];
			}
		}
	}
	else if(filter_Method==FIR_FILTER_ARM_DSP)
	{
		;//do something here
	}
}

/**
* @函数名称：LinearRegression
* @函数功能求线性回归方程:Y = a + bx
* @输入参数：
*						dada[rows*2]数组:X, Y;
*           rows:数据行数;
*           a, b:返回回归系数
*						SquarePoor[4]:返回方差分析指标: 回归平方和,剩余平方和,回归平方差,剩余平方差
* @输出参数：1求解成功,0错误
* @算法思路：
* @使用资源：
* @注意事项：
*/
static uint8_t ucLinearRegression(float *data, uint8_t rows, float *a, float *b, float *SquarePoor)
{
		uint8_t m;
		float *p, Lxx = 0.0, Lxy = 0.0, xa = 0.0, ya = 0.0;
		if (data == 0 || a == 0 || b == 0 || rows < 1)
			return 0;
		for (p = data, m = 0; m < rows; m++)
		{
			xa += *p++;
			ya += *p++;
		}
		xa /= rows;                                     // X平均值
		ya /= rows;                                     // Y平均值
		for (p = data, m = 0; m < rows; m++, p += 2)
		{
			Lxx += ((*p - xa) * (*p - xa));             // Lxx = Sum((X - Xa)??)
			Lxy += ((*p - xa) * (*(p + 1) - ya));       // Lxy = Sum((X - Xa)(Y - Ya))
		}
		*b = Lxy / Lxx;                                 // b = Lxy / Lxx
		*a = ya - *b * xa;                              // a = Ya - b*Xa
		if (SquarePoor == 0)
			return 1;
		// 方差分析
		SquarePoor[0] = SquarePoor[1] = 0.0;
		for (p = data, m = 0; m < rows; m++, p++)
		{
			Lxy = *a + *b * *p++;
			SquarePoor[0] += ((Lxy - ya) * (Lxy - ya)); // U(回归平方和)
			SquarePoor[1] += ((*p - Lxy) * (*p - Lxy)); // Q(剩余平方和)
		}
		SquarePoor[2] = SquarePoor[0];                  // 回归平方差
		SquarePoor[3] = SquarePoor[1] / (rows - 2);     // 剩余平方差
		return 1;
}



/**********************************************************************************/
/*      公有函数实现	             	                                              */
/**********************************************************************************/
void vGrpData_Proc(void)
{
	if(!IS_MASTER_ECU())return;
	
	vDataAnalysis_Filter(FIR_FILTER_MATLAB);
	vGrpVolt_Sample_Calib();
	vGrpCurrent_Sample_Calib();
	vGrpEnvTemperature_Sample_Calib();
	
	if(ECUInfo.runMode==ECUMODE_Product)
	{
		uint8_t i;
		for (i=0;i<6;i++)	
			printf("\r\nU%d:%.1f	I%d:%.1f	T%d:%.1f\r\n",i+1,ECUInfo.grpData.U[i],i+1,ECUInfo.grpData.I[i],i+1,ECUInfo.grpData.T[i]);
	}
}






/*****************************************End of grpdata.c*****************************************/
