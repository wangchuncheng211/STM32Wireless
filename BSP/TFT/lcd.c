/****************************************************************************
* Copyright (C), 2012 �ܶ�Ƕ��ʽ������ www.ourstm.net
*
* �������� �ܶ���STM32������V2,2.1,V3�ϵ���ͨ��           
* QQ: 9191274, ������sun68, Email: sun68@163.com 
* �Ա����̣�ourstm.taobao.com  
*
* �ļ���: Fun.c
* ���ݼ���:
*       �������ṩ��ucGUI3.90�ķܶ�3����ģ�������ӿ�
		
*
* �ļ���ʷ:
* �汾��  ����       ����    ˵��
* v0.2    2012-10-16 sun68  �������ļ�
*
*/
#include ".\TFT\lcd_driver.h"
#include "lcd_font.h"
#include "lcdconf.h"

//#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ram
//#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ram

extern void LCD_WR_REG(unsigned char index);
extern void LCD_WR_CMD(unsigned int index,unsigned int val);
extern void LCD_WR_Data(unsigned int val);
extern unsigned int LCD_RD_data(void);
extern void lcd_Init(void);

u16 lcd_BGR2RGB(u16 c);
u16 lcd_ReadData(void);
void lcd_Initializtion(void);
void lcd_SetPoint(u16 x,u16 y,u16 point);
void lcd_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);

/****************************************************************************
* ��    �ƣ�void lcd_Initializtion()
* ��    �ܣ���ʼ�� lcd ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����lcd_Initializtion();
****************************************************************************/
void lcd_Initializtion(void)
{ 
   lcd_Init();
}

/****************************************************************************
* ��    �ƣ�void lcd_SetCursor(u16 x,u16 y)
* ��    �ܣ�������Ļ����
* ��ڲ�����x      ������
*           y      ������
* ���ڲ�������
* ˵    ����
* ���÷�����lcd_SetCursor(10,10);
****************************************************************************/
void lcd_SetCursor(u16 x,u16 y)
{				
   
  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0200;		  //����X����
  *(__IO uint16_t *) (Bank1_LCD_D)= x;

  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0201;		  //����Y����
  *(__IO uint16_t *) (Bank1_LCD_D)= y;
}

/****************************************************************************
* ��    �ƣ�void lcd_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* ��    �ܣ����ô�������
* ��ڲ�����StartX     ����ʼ����
*           StartY     ����ʼ����
*           EndX       �н�������
*           EndY       �н�������
* ���ڲ�������
* ˵    ����
* ���÷�����lcd_SetWindows(0,0,100,100)��
****************************************************************************/
void lcd_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0210;		  
  *(__IO uint16_t *) (Bank1_LCD_D)= StartX;

  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0211;	
  *(__IO uint16_t *) (Bank1_LCD_D)= EndX;

  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0212;	
  *(__IO uint16_t *) (Bank1_LCD_D)= StartY;

  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0213;	
  *(__IO uint16_t *) (Bank1_LCD_D)= EndY; 
}


/****************************************************************************
* ��    �ƣ�u16 lcd_GetPoint(u16 x,u16 y)
* ��    �ܣ���ȡָ���������ɫֵ
* ��ڲ�����x      ������
*           y      ������
* ���ڲ�������ǰ������ɫֵ
* ˵    ����
* ���÷�����i=lcd_GetPoint(10,10);
****************************************************************************/
u16 lcd_GetPoint(u16 x,u16 y)
{ 
  lcd_SetCursor(x,y);
  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0202;	
  return (lcd_ReadData());
}

/****************************************************************************
* ��    �ƣ�void lcd_SetPoint(u16 x,u16 y,u16 point)
* ��    �ܣ���ָ�����껭��
* ��ڲ�����x      ������
*           y      ������
*           point  �����ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����lcd_SetPoint(10,10,0x0fe0);
****************************************************************************/
void lcd_SetPoint(u16 x,u16 y,u16 point)
{   
  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0200;	
  *(__IO uint16_t *) (Bank1_LCD_D)= x;

  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0201;	
  *(__IO uint16_t *) (Bank1_LCD_D)= y;

  *(__IO uint16_t *) (Bank1_LCD_C)= 0x0202;	
  *(__IO uint16_t *) (Bank1_LCD_D)= point;  
 
}


/****************************************************************************
* ��    �ƣ�void lcd_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* ��    �ܣ���ָ��������ʾһ��8x16�����ascii�ַ�
* ��ڲ�����x          ������
*           y          ������
*           charColor  �ַ�����ɫ
*           bkColor    �ַ�������ɫ
* ���ڲ�������
* ˵    ������ʾ��Χ�޶�Ϊ����ʾ��ascii��
* ���÷�����lcd_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void lcd_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  
  u8 tmp_char=0;

  for (i=0;i<16;i++)
  {
    tmp_char=ascii_8x16[((c-0x20)*16)+i];
    for (j=0;j<8;j++)
    {
      if ( (tmp_char >> 7-j) & 0x01 == 0x01)
        {
          lcd_SetPoint(x+j,y+i,charColor); // �ַ���ɫ
        }
        else
        {
          lcd_SetPoint(x+j,y+i,bkColor); // ������ɫ
        }
    }
  }
}

/****************************************************************************
* ��    �ƣ�u16 lcd_BGR2RGB(u16 c)
* ��    �ܣ�RRRRRGGGGGGBBBBB ��Ϊ BBBBBGGGGGGRRRRR ��ʽ
* ��ڲ�����c      BRG ��ɫֵ
* ���ڲ�����RGB ��ɫֵ
* ˵    �����ڲ���������
* ���÷�����
****************************************************************************/
u16 lcd_BGR2RGB(u16 c)
{
  u16  r, g, b;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  return( (b<<11) + (g<<5) + (r<<0) );
}


/****************************************************************************
* ��    �ƣ�u16 lcd_ReadData(void)
* ��    �ܣ���ȡ����������
* ��ڲ�������
* ���ڲ��������ض�ȡ��������
* ˵    �����ڲ�����
* ���÷�����i=lcd_ReadData();
****************************************************************************/
u16 lcd_ReadData(void)
{
  u16 val=0;
  val=LCD_RD_data();
  return val;
}


/******************* (C) COPYRIGHT 2012 �ܶ�STM32 *****END OF FILE****/
