/****************************************************************************
* Copyright (C), 2011 奋斗嵌入式工作室 www.ourstm.net
*
* 本例程在 奋斗版STM32开发板V2,2.1,V3上调试通过           
* QQ: 9191274, 旺旺：sun68, Email: sun68@163.com 
* 淘宝店铺：ourstm.taobao.com  
*
* 文件名: bsp.c
* 内容简述:
*       本例程提供了硬件平台的初始化
		
*
* 文件历史:
* 版本号  日期       作者    说明
* v0.2    2011-07-01 sun68  创建该文件
*
*/
#include "..\App\includes.h"
#include "globals.h"
#include "NRF24L01.h"
#include ".\TFT\lcd_driver.h"	//包含 void tp_Config(void) ;

extern void FSMC_LCD_Init(void); 
extern void SPI2_NRF24L01_Init(void);
extern void RX_Mode(void);
extern void TX_Mode(void);
extern void MODE_CE(unsigned char a);
extern unsigned char SPI_Read(BYTE reg);
extern unsigned char SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);
extern unsigned char SPI2_NRF_SendByte(unsigned char byte);
extern unsigned char SPI2_NRF_SendByte(unsigned char byte);
extern unsigned char SPI_RW_Reg(unsigned char data1,unsigned char data2);
extern unsigned char SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);
extern void RX_Mode(void);
extern void TX_Mode(void);
extern void NRF24L01_TXBUF(uint8_t* data_buffer, uint8_t Nb_bytes);



/****************************************************************************
* 名    称：void RCC_Configuration(void)
* 功    能：系统时钟配置为72MHZ， 外设时钟配置
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void RCC_Configuration(void){

  SystemInit();	  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC 
                       | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);
}

/****************************************************************************
* 名    称：void GPIO_Configuration(void)
* 功    能：通用IO口配置
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：
****************************************************************************/  
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //状态LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //通用推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
}


/****************************************************************************
* 名    称：void NVIC_Configuration(void)
* 功    能：中断源配置
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void NVIC_Configuration(void)
{
  /*  结构声明*/
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  

  /* 优先级组 1  */    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;					//NRF24L01 中断响应
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		    //抢占优先级 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//子优先级为1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能
  NVIC_Init(&NVIC_InitStructure);											    

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	   //NRF24L01 IRQ  PA0
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;					   //NRF24L01 IRQ PA0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			   //EXTI中断
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		   //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;						   //使能
  EXTI_Init(&EXTI_InitStructure);	
}


/****************************************************************************
* 名    称：void BSP_Init(void)
* 功    能：奋斗板初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/  
void BSP_Init(void)
{
  /*  NRF24L01的6通道发射地址的初始化 */
  TX_ADDRESS0[0]=0x34;	            //通道0 发射地址
  TX_ADDRESS0[1]=0x43;
  TX_ADDRESS0[2]=0x10;
  TX_ADDRESS0[3]=0x10;
  TX_ADDRESS0[4]=0x01;	 

  TX_ADDRESS1[0]=0x01;				//通道1 发射地址
  TX_ADDRESS1[1]=0xE1;
  TX_ADDRESS1[2]=0xE2;
  TX_ADDRESS1[3]=0xE3;
  TX_ADDRESS1[4]=0x02;

  TX_ADDRESS2[0]=0x02;			   //通道2 发射地址
  TX_ADDRESS2[1]=0xE1;
  TX_ADDRESS2[2]=0xE2;
  TX_ADDRESS2[3]=0xE3;
  TX_ADDRESS2[4]=0x02;

  TX_ADDRESS3[0]=0x03;			   //通道3 发射地址
  TX_ADDRESS3[1]=0xE1;
  TX_ADDRESS3[2]=0xE2;
  TX_ADDRESS3[3]=0xE3;
  TX_ADDRESS3[4]=0x02;

  TX_ADDRESS4[0]=0x04;			   //通道4 发射地址
  TX_ADDRESS4[1]=0xE1;
  TX_ADDRESS4[2]=0xE2;
  TX_ADDRESS4[3]=0xE3;
  TX_ADDRESS4[4]=0x02;

  TX_ADDRESS5[0]=0x05;			   //通道5 发射地址
  TX_ADDRESS5[1]=0xE1;
  TX_ADDRESS5[2]=0xE2;
  TX_ADDRESS5[3]=0xE3;
  TX_ADDRESS5[4]=0x02;	   
  RCC_Configuration();  	       //系统时钟初始化及端口外设时钟使能
  GPIO_Configuration();			   //状态LED1的初始化
  SPI2_NRF24L01_Init();			   //SPI2接口及 NRF24L01初始化 
  NVIC_Configuration();			   //中断源配置		 
  tp_Config();					   //SPI1 触摸电路初始化	    
  FSMC_LCD_Init();				   //FSMC TFT接口初始化  
}

/****************************************************************************
* 名    称：void  OS_CPU_SysTickInit(void)
* 功    能：ucos 系统节拍时钟初始化  初始设置为1ms一次节拍
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;

    RCC_GetClocksFreq(&rcc_clocks);		                        //获得系统时钟的值
    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;	//算出时钟节拍的值
	SysTick_Config(cnts);										//设置时钟节拍 
}
   
/******************* (C) COPYRIGHT 2011 奋斗STM32 *****END OF FILE****/

