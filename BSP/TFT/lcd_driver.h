#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include "stm32f10x.h"

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ram
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ram

//u16 CheckController(void);

//void ili9320_Initializtion(void);
//void ili9320_Reset(void);
//void ili9320_WriteRegister(uint16_t index,u16 dat);
//void ili9320_SetCursor(u16 x,u16 y);
//void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
//void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u8 *pic);
//void ili9320_SetPoint(u16 x,u16 y,u16 point);
//void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);
//void ili9320_Clear(u16 dat);
//void ili9320_Delay(u32 nCount);
//void ili9320_Test(void);
//u16  ili9320_GetCode(void);
//void ili9320_WriteData(u16 dat);
//void ili9320_WriteIndex(u16 idx);
//void ili9320_BackLight(u8 status);
//u16 ili9320_BGR2RGB(u16 c);
//u16 ili9320_GetPoint(u16 x,u16 y);
//u16 ili9320_ReadData(void);
//u16 ili9320_ReadRegister(u16 index);

u16 GUI_Color565(u32 RGB);  // RGB��ɫתΪ16λ(565)
void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor);
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);  // ����
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill);  // ��԰
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill); // ������
void GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill);  // ��������


void tp_Config(void);
u16 TPReadX(void);
u16 TPReadY(void);
//void Touch_Initializtion(void);
//u16  Touch_GetPhyX(void);
//u16  Touch_GetPhyY(void);
//u16  Touch_MeasurementX(void);
//u16  Touch_MeasurementY(void);

#endif