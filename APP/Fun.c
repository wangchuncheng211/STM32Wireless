/****************************************************************************
* Copyright (C), 2013 奋斗嵌入式工作室 www.ourstm.net
*
* 本例程在 奋斗版STM32开发板V5上调试通过           
* QQ: 9191274, 旺旺：sun68, Email: sun68@163.com 
* 淘宝店铺：ourstm.taobao.com  
*
* 文件名: Fun.c
* 内容简述:
*       本例程采用ucGUI3.90版本， 使用了对话框，列表框，点选框，文本框， 编辑框，按钮等部件
		
*
* 文件历史:
* 版本号  日期       作者    说明
* v0.1    2013-01-28 sun68  创建该文件
*
****************************************************************************/

#include <stddef.h>           /* needed for definition of NULL */
#include <string.h>
#include "..\uCGUI\uCGUIInc\GUI.h"
#include "..\uCGUI\uCGUIInc\WM.h"
#include "..\uCGUI\uCGUIInc\BUTTON.h"
#include "..\uCGUI\uCGUIInc\DIALOG.h"
#include "..\uCGUI\uCGUIInc\LISTBOX.h"
#include "..\uCGUI\uCGUIInc\EDIT.h"
#include "..\uCGUI\uCGUIInc\FRAMEWIN.h"	
#include "globals.h"
#include "NRF24L01.h"

//void Fun(void);
//extern void RX_Mode(void);
//extern void TX_Mode(void);
//extern void NRF24L01_TXBUF(uint8_t* data_buffer, uint8_t Nb_bytes);
//
///* ucgui类型定义*/ 
//WM_HWIN hWin;
//WM_HWIN hListBox[8];
//WM_HWIN text1,text2,text3,text4,text5,text6,bt[2],edit1,edit2,slider0,rd0,list1;	
//GUI_COLOR DesktopColorOld;
//const GUI_FONT* pFont = &GUI_FontComic24B_1;
//const GUI_FONT* pFont18 = &GUI_FontComic18B_1;
// 
///* 定义了对话框资源列表 */
//static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
//  { FRAMEWIN_CreateIndirect, "NRF24L01", 0,               0,   0, 240, 400, FRAMEWIN_CF_ACTIVE },
//  { BUTTON_CreateIndirect,   "SEND",   GUI_ID_BUTTON0,  0,   316, 120,  55 }, 
//  { BUTTON_CreateIndirect,   "CLEAR",  GUI_ID_BUTTON2,  120, 316, 120,  55 },

//  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT1,    0,   120, 230,  35, EDIT_CF_LEFT, 50 },
//  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT2,    0,   190, 230,  35, EDIT_CF_LEFT, 50 },
//  
//  { TEXT_CreateIndirect,     "Send Text Area",      GUI_ID_TEXT0,   1,   95,   230,  25, TEXT_CF_LEFT },
//  { TEXT_CreateIndirect,     "Receive Text Area ",  GUI_ID_TEXT1,   1,   163,  230,  25, TEXT_CF_LEFT },
// 
//  { TEXT_CreateIndirect,     "2M bps",    GUI_ID_TEXT2,     23,    2,  140,  25, TEXT_CF_LEFT },
//  { TEXT_CreateIndirect,     "1M bps",    GUI_ID_TEXT3,     23,   22,  140,  25, TEXT_CF_LEFT },
//  { TEXT_CreateIndirect,     "250K bps",  GUI_ID_TEXT5,     23,   42,  140,  25, TEXT_CF_LEFT },
//  
//  { TEXT_CreateIndirect,     "",  GUI_ID_TEXT4,     0,   60,  240,  25, TEXT_CF_LEFT },
//
//  { RADIO_CreateIndirect,     "Receive Mode",  GUI_ID_RADIO0,     3,   13,  40,  55, RADIO_TEXTPOS_LEFT,3},
//
//  { LISTBOX_CreateIndirect,  "",       GUI_ID_LISTBOX0,  104,    3,  120,  52, 0, 0 },
//};
//
///*  定义了NRF24L01通道选择列表框的初始项目 */
//static const GUI_ConstString _apListBox[] = {
//  "Pipe 0", "Pipe 1","Pipe 2","Pipe 3","Pipe 4","Pipe 5", NULL
//};


void Fun(void);
extern void RX_Mode(void);
extern void TX_Mode(void);
extern void NRF24L01_TXBUF(uint8_t* data_buffer, uint8_t Nb_bytes);
int8_t Shift = 0; 
unsigned char text_buf[32] = "";
/* ucgui类型定义*/ 
  WM_HWIN hWin;
  WM_HWIN hListBox[8];
  WM_HWIN text1,text2,text3,bt[33],edit1,edit2;	
 GUI_COLOR DesktopColorOld;
// const GUI_FONT* pFont1 = &GUI_FontComic24B_1;
 const GUI_FONT* pFont = &GUI_Font8x13_1;
 const GUI_FONT* pFont18 = &GUI_FontComic18B_1;
 //const GUI_FONT* pFont18 = &GUI_FontD60x80;
 
/* 定义了对话框资源列表 */
static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "NRF24L01P", 0,   0,   0, 240, 400, FRAMEWIN_CF_ACTIVE },
  { BUTTON_CreateIndirect,   "SEND",  GUI_ID_BUTTON0,     0,  316, 120,  55 },
  { BUTTON_CreateIndirect,   "CLEAR", GUI_ID_BUTTON1,   120,  316, 120,  55 },
  { EDIT_CreateIndirect,    "",       GUI_ID_EDIT1,    0,   25, 230,  35, EDIT_CF_LEFT, 50 },
  { EDIT_CreateIndirect,    "",       GUI_ID_EDIT2,    0,   85, 230,  35, EDIT_CF_LEFT, 50 },  
  { TEXT_CreateIndirect,  "Send Text Area",      GUI_ID_TEXT0,   1,    2,  230,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,  "Receive Text Area ",  GUI_ID_TEXT1,   1,   62,  230,  25, TEXT_CF_LEFT },
	{ BUTTON_CreateIndirect,   "Q",         GUI_ID_BUTTON2,   0, 150,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "W",         GUI_ID_BUTTON3,   24, 150,24,30, 0,0},
    { BUTTON_CreateIndirect,   "P",         GUI_ID_BUTTON11,   216,150,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "O",         GUI_ID_BUTTON10,   192,150,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "I",         GUI_ID_BUTTON9,   168,150,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "Y",         GUI_ID_BUTTON7,   120,150,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "U",         GUI_ID_BUTTON8,   144,150,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "T",         GUI_ID_BUTTON6,   96, 150,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "R",         GUI_ID_BUTTON5,   72, 150,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "E",         GUI_ID_BUTTON4,   48, 150,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "A",         GUI_ID_BUTTON12,   10, 182,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "S",         GUI_ID_BUTTON13,   34, 182,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "D",         GUI_ID_BUTTON14,   58, 182,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "F",         GUI_ID_BUTTON15,   82, 182,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "G",         GUI_ID_BUTTON16,   106, 182,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "H",         GUI_ID_BUTTON17,   130, 182,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "J",         GUI_ID_BUTTON18,   154, 182,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "K",         GUI_ID_BUTTON19,   178, 182,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "L",         GUI_ID_BUTTON20,   202, 182,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "Z",         GUI_ID_BUTTON21,   34, 214,24, 30, 0,0 },
    { BUTTON_CreateIndirect,   "X",         GUI_ID_BUTTON22,   58, 214,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "C",         GUI_ID_BUTTON23,   82, 214,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "V",         GUI_ID_BUTTON24,   106, 214,24, 30, 0,0},        
    { BUTTON_CreateIndirect,   "B",         GUI_ID_BUTTON25,   130, 214,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "N",         GUI_ID_BUTTON26,   154, 214,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "M",         GUI_ID_BUTTON27,   178, 214,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "Shift",     GUI_ID_BUTTON28,   0,  214,34, 30, 0,0},
    { BUTTON_CreateIndirect,   "1",         GUI_ID_BUTTON29,   0, 246,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "2",         GUI_ID_BUTTON30,   24, 246,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "3",         GUI_ID_BUTTON31,   48, 246,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "4",         GUI_ID_BUTTON32,   72, 246,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "5",         GUI_ID_BUTTON33,   96, 246,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "6",         GUI_ID_BUTTON34,   120, 246,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "7",         GUI_ID_BUTTON35,   144, 246,24, 30, 0,0},
	{ BUTTON_CreateIndirect,   "8",         GUI_ID_BUTTON36,   168, 246,24, 30, 0,0},
    { BUTTON_CreateIndirect,   "9",         GUI_ID_BUTTON37,   192, 246,24, 30, 0,0},
  { TEXT_CreateIndirect,     "status",  GUI_ID_TEXT2,     1,   120,  240,  25, TEXT_CF_HCENTER },
};

/****************************************************************************
* 名    称：static void _cbCallback(WM_MESSAGE * pMsg)
* 功    能：ucgui回调函数，是作为对话框动作响应的函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：
****************************************************************************/  
static void _cbCallback(WM_MESSAGE * pMsg) 
{
  unsigned char text_buf[1] = "";
  int NCode, Id;
  switch (pMsg->MsgId) 
  {
    case WM_NOTIFY_PARENT:				  		//通知父窗口有事件在窗口部件上发生
      Id    = WM_GetId(pMsg->hWinSrc);    		//获得对话框窗口里发生事件的部件的ID
      NCode = pMsg->Data.v;               		//通知代码
      switch (NCode) 
	  {
        case WM_NOTIFICATION_RELEASED:    		//窗体部件动作被释放             
          if (Id == GUI_ID_BUTTON1) 
		  {     		//按键CLEAR被松开
            memcpy(status_buf, "", 20);	  		//清空状态文本缓冲区 
			memcpy(rx_buf, "", 32);		  		//清空接收文本缓冲区 		
			TEXT_SetText(text3,(const char *)status_buf);	   	//清空状态文本框	
			EDIT_SetText(edit2,(const char *)rx_buf);			//清空接收字符编辑框
			memcpy(tx_buf, "", 32);				//清空发送文本缓冲区
			NRF24L01_TXBUF(tx_buf,32);			//将发送字符缓冲区的字符通过NRF24L01发送出去
			EDIT_SetText(edit1,(const char *)tx_buf);			//清空接收字符编辑框
          }          
		  else if (Id == GUI_ID_BUTTON0) 
		  {            //按键SEND 被松开
//		  	memcpy(tx_buf, "1234567890abcdefghij!@#$%^&*()-=", 32);	  //将32字节的文本拷贝到发送文本缓冲区
//          memcpy(tx_buf, "", 32);				//清空发送文本缓冲区

			memcpy(rx_buf, "", 32);				//清空接收文本缓冲区 	
			memcpy(status_buf, "", 20);			//清空状态文本缓冲区 
			EDIT_SetText(edit2,(const char *)rx_buf);			//清空接收字符编辑框	
			NRF24L01_TXBUF(tx_buf,32);			//将发送字符缓冲区的字符通过NRF24L01发送出去
			memcpy(tx_buf, "", 32);				//清空发送文本缓冲区
			EDIT_SetText(edit1,(const char *)tx_buf);			//清空接收字符编辑框
			TEXT_SetText(text3,(const char *)status_buf);		//清空状态文本框   			
          }
          else if(Id == GUI_ID_BUTTON28)
          {
            if(Shift==0) Shift = 1;
            else         Shift = 0;
          }
		  else if(Id == GUI_ID_BUTTON2)
		  {
			if(Shift==0) memcpy(text_buf,"q", 1);
			else         memcpy(text_buf,"Q", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON3)
		  {
			if(Shift==0) memcpy(text_buf,"w", 1);
			else         memcpy(text_buf,"W", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON4)
		  {
			if(Shift==0) memcpy(text_buf,"e", 1);
			else         memcpy(text_buf,"E", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON5)
		  {
			if(Shift==0) memcpy(text_buf,"r", 1);
			else         memcpy(text_buf,"R", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON6)
		  {
			if(Shift==0) memcpy(text_buf,"t", 1);
			else         memcpy(text_buf,"T", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON7)
		  {
			if(Shift==0) memcpy(text_buf,"y", 1);
			else         memcpy(text_buf,"Y", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON8)
		  {
			if(Shift==0) memcpy(text_buf,"u", 1);
			else         memcpy(text_buf,"U", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON9)
		  {
			if(Shift==0) memcpy(text_buf,"i", 1);
			else         memcpy(text_buf,"I", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON10)
		  {
			if(Shift==0) memcpy(text_buf,"o", 1);
			else         memcpy(text_buf,"O", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON11)
		  {
			if(Shift==0) memcpy(text_buf,"p", 1);
			else         memcpy(text_buf,"P", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON12)
		  {
			if(Shift==0) memcpy(text_buf,"a", 1);
			else         memcpy(text_buf,"A", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON13)
		  {
			if(Shift==0) memcpy(text_buf,"s", 1);
			else         memcpy(text_buf,"S", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON14)
		  {
			if(Shift==0) memcpy(text_buf,"d", 1);
			else         memcpy(text_buf,"D", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON15)
		  {
			if(Shift==0) memcpy(text_buf,"f", 1);
			else         memcpy(text_buf,"F", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON16)
		  {
			if(Shift==0) memcpy(text_buf,"g", 1);
			else         memcpy(text_buf,"G", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON17)
		  {
			if(Shift==0) memcpy(text_buf,"h", 1);
			else         memcpy(text_buf,"H", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON18)
		  {
			if(Shift==0) memcpy(text_buf,"j", 1);
			else         memcpy(text_buf,"J", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON19)
		  {
			if(Shift==0) memcpy(text_buf,"k", 1);
			else         memcpy(text_buf,"K", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON20)
		  {
			if(Shift==0) memcpy(text_buf,"l", 1);
			else         memcpy(text_buf,"L", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON21)
		  {
			if(Shift==0) memcpy(text_buf,"z", 1);
			else         memcpy(text_buf,"Z", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON22)
		  {
			if(Shift==0) memcpy(text_buf,"x", 1);
			else         memcpy(text_buf,"X", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON23)
		  {
			if(Shift==0) memcpy(text_buf,"c", 1);
			else         memcpy(text_buf,"C", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON24)
		  {
			if(Shift==0) memcpy(text_buf,"v", 1);
			else         memcpy(text_buf,"V", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON25)
		  {
			if(Shift==0) memcpy(text_buf,"b", 1);
			else         memcpy(text_buf,"B", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON26)
		  {
			if(Shift==0) memcpy(text_buf,"n", 1);
			else         memcpy(text_buf,"N", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON27)
		  {
			if(Shift==0) memcpy(text_buf,"m", 1);
			else         memcpy(text_buf,"M", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON29)
		  {
			memcpy(text_buf,"1", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON30)
		  {
			memcpy(text_buf,"2", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON31)
		  {
			memcpy(text_buf,"3", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON32)
		  {
			memcpy(text_buf,"4", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON33)
		  {
			memcpy(text_buf,"5", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON34)
		  {
			memcpy(text_buf,"6", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON35)
		  {
			memcpy(text_buf,"7", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON36)
		  {
			memcpy(text_buf,"8", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
		  else if(Id == GUI_ID_BUTTON37)
		  {
			memcpy(text_buf,"9", 1);	
			strcat((char *)tx_buf,(const char *)text_buf);
			EDIT_SetText(edit1,(const char *)tx_buf);
		  }
//		  else if (Id == GUI_ID_RADIO0) 
//		  {            //NRF24L01无线速率点选框点选动作完成
//		  	nrf_baud= RADIO_GetValue(rd0);		//获得速率表示值
//		    RX_Mode();							//进入接收模式			
//          }
//		  else if (Id == GUI_ID_LISTBOX0)
//		  {      //NRF24L01无线通道选择动作
//			nrf_Pipe= LISTBOX_GetSel(list1);	//获得NRF24LL01无线通道表示值 			
//		    RX_Mode();   						//进入接收模式 	
//		  }
		 break;
		default: break;
      }	    
    default:
      WM_DefaultProc(pMsg);						//默认程序来处理消息
	  break;
  }
}


/****************************************************************************
* 名    称：void Fun(void)
* 功    能：显示及处理界面
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void Fun(void) 
{
//  unsigned int  bt_index = 0;
//  unsigned int  bt_handler = 0;  
  GUI_CURSOR_Show();                                        //打开鼠标图形显示  
  
  /* 建立对话框时，包含了资源列表，资源数目， 并且指定了用于动作响应的回调函数  */
  hWin = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), _cbCallback, 0, 0, 0);

  FRAMEWIN_SetFont(hWin, &GUI_FontComic18B_1);	  			//对话框字体设置 
  FRAMEWIN_SetClientColor(hWin, GUI_WHITE);		  			//对话框的窗体颜色是黑色
//  memcpy(tx_buf, "1234567890abcdefghij!@#$%^&*()-=", 32);   //将长度为32字节的发送字符串拷贝到发送缓冲区
  memcpy(tx_buf, "", 32);
  memcpy(rx_buf, "", 32);									//将接收缓存区清空
 		
  text1 = WM_GetDialogItem(hWin, GUI_ID_TEXT0);				//获得对话框里GUI_ID_TEXT0项目(文本框Send Text Area)的句柄
  text2 = WM_GetDialogItem(hWin, GUI_ID_TEXT1);				//获得对话框里GUI_ID_TEXT1项目(文本框Receive Text Area)的句柄
  text3 = WM_GetDialogItem(hWin, GUI_ID_TEXT2);				//获得对话框里GUI_ID_TEXT2项目(状态字符文本框)的句柄 
  TEXT_SetFont(text1,pFont);							    //设置对话框里文本框Send Text Area的字体
  TEXT_SetFont(text2,pFont);								//设置对话框里文本框Receive Text Area的字体
  TEXT_SetFont(text3,pFont);								//设置对话框里状态字符文本框的字体
  TEXT_SetTextColor(text1,GUI_GREEN);						//设置对话框里文本框Send Text Area的字体颜色
  TEXT_SetTextColor(text2,GUI_GREEN);						//设置对话框里文本框Receive Text Area的字体颜色
  TEXT_SetTextColor(text3,GUI_RED);						    //设置对话框里状态字符文本框的字体颜色

  edit1 = WM_GetDialogItem(hWin, GUI_ID_EDIT1);				//获得对话框里GUI_ID_EDIT1项目(编辑框 发送字符串显示区)的句柄
  EDIT_SetFont(edit1,pFont18);								//设置对话框里编辑框 发送字符串显示区的字体
  EDIT_SetText(edit1,(const char *)tx_buf);								//设置对话框里编辑框 发送字符串显示区的字符串
  edit2 = WM_GetDialogItem(hWin, GUI_ID_EDIT2);			    //获得对话框里GUI_ID_EDIT2项目(编辑框 接收字符串显示区)的句柄
  EDIT_SetFont(edit2,pFont18);								//设置对话框里编辑框 接收字符串显示区的字体
  EDIT_SetText(edit2,(const char *)rx_buf);								//设置对话框里编辑框 接收字符串显示区的字符串

//  bt_handler = GUI_ID_BUTTON0;
//  for (bt_index=0; bt_index<10; bt_index++,bt_handler++)
//  {
//      bt[bt_index]=WM_GetDialogItem(hWin,bt_handler);				//获得对话框里GUI_ID_BUTTON0项目(按键SEND)的句柄  
//  }
//  bt_handler = GUI_ID_BUTTON10;
//  for (bt_index=10; bt_index<=32; bt_index++,bt_handler++)
//  {
//      bt[bt_index]=WM_GetDialogItem(hWin,bt_handler);				//获得对话框里GUI_ID_BUTTON0项目(按键SEND)的句柄  
//  }
  bt[0]=WM_GetDialogItem(hWin,GUI_ID_BUTTON0);				//获得对话框里GUI_ID_BUTTON0项目(按键SEND)的句柄
  bt[1]=WM_GetDialogItem(hWin,GUI_ID_BUTTON1);				//获得对话框里GUI_ID_BUTTON0项目(按键CLEAR)的句柄
  BUTTON_SetFont(bt[0],pFont);								//设置对话框里按键SEND的字体
  BUTTON_SetFont(bt[1],pFont);								//设置对话框里按键CLEAR的字体  
  BUTTON_SetTextColor(bt[0],0,GUI_WHITE); 					//设置对话框里按键SEND未被按下的字体颜色
  BUTTON_SetTextColor(bt[1],0,GUI_WHITE);					//设置对话框里按键CLEAR未被按下的字体颜色
  			
  nrf_Pipe = 0;												//NRF24L01初始发射通道设置为0			
  nrf_baud = 0;												//NRF24L01速率 初始为2MPS
  RX_Mode();												//NRF24L01进入接收模式  
  while (1)
  {	   	
	
	if(Rx_Succ==1){	                                        //当NRF24L01接收到有效数据
		EDIT_SetText(edit2,(const char *)rx_buf);		    //将接收缓冲区的字符写入到接收字符编辑框内
		TEXT_SetText(text3,(const char *)status_buf);		//将状态文本缓冲区的字符写入到状态文本框内
		Rx_Succ = 0; 		
	}
	WM_Exec();									            //刷新屏幕
  }	  
}

/******************* (C) COPYRIGHT 2013 奋斗STM32 *****END OF FILE****/
