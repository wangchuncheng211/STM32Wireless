/****************************************************************************
* Copyright (C), 2011 �ܶ�Ƕ��ʽ������ www.ourstm.net
*
* �������� �ܶ���STM32������V2,2.1,V3�ϵ���ͨ��           
* QQ: 9191274, ������sun68, Email: sun68@163.com 
* �Ա����̣�ourstm.taobao.com  
*
* �ļ���: bsp.c
* ���ݼ���:
*       �������ṩ��Ӳ��ƽ̨�ĳ�ʼ��
		
*
* �ļ���ʷ:
* �汾��  ����       ����    ˵��
* v0.2    2011-07-01 sun68  �������ļ�
*
*/
#include "..\App\includes.h"
#include "globals.h"
#include "NRF24L01.h"
#include ".\TFT\lcd_driver.h"	//���� void tp_Config(void) ;

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
* ��    �ƣ�void RCC_Configuration(void)
* ��    �ܣ�ϵͳʱ������Ϊ72MHZ�� ����ʱ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void RCC_Configuration(void){

  SystemInit();	  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC 
                       | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);
}

/****************************************************************************
* ��    �ƣ�void GPIO_Configuration(void)
* ��    �ܣ�ͨ��IO������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����
****************************************************************************/  
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //״̬LED1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //ͨ���������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
}


/****************************************************************************
* ��    �ƣ�void NVIC_Configuration(void)
* ��    �ܣ��ж�Դ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void NVIC_Configuration(void)
{
  /*  �ṹ����*/
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  

  /* ���ȼ��� 1  */    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;					//NRF24L01 �ж���Ӧ
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		    //��ռ���ȼ� 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//�����ȼ�Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ��
  NVIC_Init(&NVIC_InitStructure);											    

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	   //NRF24L01 IRQ  PA0
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;					   //NRF24L01 IRQ PA0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			   //EXTI�ж�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		   //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;						   //ʹ��
  EXTI_Init(&EXTI_InitStructure);	
}


/****************************************************************************
* ��    �ƣ�void BSP_Init(void)
* ��    �ܣ��ܶ����ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/  
void BSP_Init(void)
{
  /*  NRF24L01��6ͨ�������ַ�ĳ�ʼ�� */
  TX_ADDRESS0[0]=0x34;	            //ͨ��0 �����ַ
  TX_ADDRESS0[1]=0x43;
  TX_ADDRESS0[2]=0x10;
  TX_ADDRESS0[3]=0x10;
  TX_ADDRESS0[4]=0x01;	 

  TX_ADDRESS1[0]=0x01;				//ͨ��1 �����ַ
  TX_ADDRESS1[1]=0xE1;
  TX_ADDRESS1[2]=0xE2;
  TX_ADDRESS1[3]=0xE3;
  TX_ADDRESS1[4]=0x02;

  TX_ADDRESS2[0]=0x02;			   //ͨ��2 �����ַ
  TX_ADDRESS2[1]=0xE1;
  TX_ADDRESS2[2]=0xE2;
  TX_ADDRESS2[3]=0xE3;
  TX_ADDRESS2[4]=0x02;

  TX_ADDRESS3[0]=0x03;			   //ͨ��3 �����ַ
  TX_ADDRESS3[1]=0xE1;
  TX_ADDRESS3[2]=0xE2;
  TX_ADDRESS3[3]=0xE3;
  TX_ADDRESS3[4]=0x02;

  TX_ADDRESS4[0]=0x04;			   //ͨ��4 �����ַ
  TX_ADDRESS4[1]=0xE1;
  TX_ADDRESS4[2]=0xE2;
  TX_ADDRESS4[3]=0xE3;
  TX_ADDRESS4[4]=0x02;

  TX_ADDRESS5[0]=0x05;			   //ͨ��5 �����ַ
  TX_ADDRESS5[1]=0xE1;
  TX_ADDRESS5[2]=0xE2;
  TX_ADDRESS5[3]=0xE3;
  TX_ADDRESS5[4]=0x02;	   
  RCC_Configuration();  	       //ϵͳʱ�ӳ�ʼ�����˿�����ʱ��ʹ��
  GPIO_Configuration();			   //״̬LED1�ĳ�ʼ��
  SPI2_NRF24L01_Init();			   //SPI2�ӿڼ� NRF24L01��ʼ�� 
  NVIC_Configuration();			   //�ж�Դ����		 
  tp_Config();					   //SPI1 ������·��ʼ��	    
  FSMC_LCD_Init();				   //FSMC TFT�ӿڳ�ʼ��  
}

/****************************************************************************
* ��    �ƣ�void  OS_CPU_SysTickInit(void)
* ��    �ܣ�ucos ϵͳ����ʱ�ӳ�ʼ��  ��ʼ����Ϊ1msһ�ν���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;

    RCC_GetClocksFreq(&rcc_clocks);		                        //���ϵͳʱ�ӵ�ֵ
    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;	//���ʱ�ӽ��ĵ�ֵ
	SysTick_Config(cnts);										//����ʱ�ӽ��� 
}
   
/******************* (C) COPYRIGHT 2011 �ܶ�STM32 *****END OF FILE****/

