/****************************************************************************
* Copyright (C), 2013 �ܶ�Ƕ��ʽ������ www.ourstm.net
*
* �������� �ܶ���STM32������V5�ϵ���ͨ��           
* QQ: 9191274, ������sun68, Email: sun68@163.com 
* �Ա����̣�ourstm.taobao.com  
*
* �ļ���: Fun.c
* ���ݼ���:
*       �����̲���ucGUI3.90�汾�� ʹ���˶Ի����б�򣬵�ѡ���ı��� �༭�򣬰�ť�Ȳ���
		
*
* �ļ���ʷ:
* �汾��  ����       ����    ˵��
* v0.1    2013-01-28 sun68  �������ļ�
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
///* ucgui���Ͷ���*/ 
//WM_HWIN hWin;
//WM_HWIN hListBox[8];
//WM_HWIN text1,text2,text3,text4,text5,text6,bt[2],edit1,edit2,slider0,rd0,list1;	
//GUI_COLOR DesktopColorOld;
//const GUI_FONT* pFont = &GUI_FontComic24B_1;
//const GUI_FONT* pFont18 = &GUI_FontComic18B_1;
// 
///* �����˶Ի�����Դ�б� */
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
///*  ������NRF24L01ͨ��ѡ���б��ĳ�ʼ��Ŀ */
//static const GUI_ConstString _apListBox[] = {
//  "Pipe 0", "Pipe 1","Pipe 2","Pipe 3","Pipe 4","Pipe 5", NULL
//};


void Fun(void);
extern void RX_Mode(void);
extern void TX_Mode(void);
extern void NRF24L01_TXBUF(uint8_t* data_buffer, uint8_t Nb_bytes);
int8_t Shift = 0; 
unsigned char text_buf[32] = "";
/* ucgui���Ͷ���*/ 
  WM_HWIN hWin;
  WM_HWIN hListBox[8];
  WM_HWIN text1,text2,text3,bt[33],edit1,edit2;	
 GUI_COLOR DesktopColorOld;
// const GUI_FONT* pFont1 = &GUI_FontComic24B_1;
 const GUI_FONT* pFont = &GUI_Font8x13_1;
 const GUI_FONT* pFont18 = &GUI_FontComic18B_1;
 //const GUI_FONT* pFont18 = &GUI_FontD60x80;
 
/* �����˶Ի�����Դ�б� */
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
* ��    �ƣ�static void _cbCallback(WM_MESSAGE * pMsg)
* ��    �ܣ�ucgui�ص�����������Ϊ�Ի�������Ӧ�ĺ���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����
****************************************************************************/  
static void _cbCallback(WM_MESSAGE * pMsg) 
{
  unsigned char text_buf[1] = "";
  int NCode, Id;
  switch (pMsg->MsgId) 
  {
    case WM_NOTIFY_PARENT:				  		//֪ͨ���������¼��ڴ��ڲ����Ϸ���
      Id    = WM_GetId(pMsg->hWinSrc);    		//��öԻ��򴰿��﷢���¼��Ĳ�����ID
      NCode = pMsg->Data.v;               		//֪ͨ����
      switch (NCode) 
	  {
        case WM_NOTIFICATION_RELEASED:    		//���岿���������ͷ�             
          if (Id == GUI_ID_BUTTON1) 
		  {     		//����CLEAR���ɿ�
            memcpy(status_buf, "", 20);	  		//���״̬�ı������� 
			memcpy(rx_buf, "", 32);		  		//��ս����ı������� 		
			TEXT_SetText(text3,(const char *)status_buf);	   	//���״̬�ı���	
			EDIT_SetText(edit2,(const char *)rx_buf);			//��ս����ַ��༭��
			memcpy(tx_buf, "", 32);				//��շ����ı�������
			NRF24L01_TXBUF(tx_buf,32);			//�������ַ����������ַ�ͨ��NRF24L01���ͳ�ȥ
			EDIT_SetText(edit1,(const char *)tx_buf);			//��ս����ַ��༭��
          }          
		  else if (Id == GUI_ID_BUTTON0) 
		  {            //����SEND ���ɿ�
//		  	memcpy(tx_buf, "1234567890abcdefghij!@#$%^&*()-=", 32);	  //��32�ֽڵ��ı������������ı�������
//          memcpy(tx_buf, "", 32);				//��շ����ı�������

			memcpy(rx_buf, "", 32);				//��ս����ı������� 	
			memcpy(status_buf, "", 20);			//���״̬�ı������� 
			EDIT_SetText(edit2,(const char *)rx_buf);			//��ս����ַ��༭��	
			NRF24L01_TXBUF(tx_buf,32);			//�������ַ����������ַ�ͨ��NRF24L01���ͳ�ȥ
			memcpy(tx_buf, "", 32);				//��շ����ı�������
			EDIT_SetText(edit1,(const char *)tx_buf);			//��ս����ַ��༭��
			TEXT_SetText(text3,(const char *)status_buf);		//���״̬�ı���   			
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
//		  {            //NRF24L01�������ʵ�ѡ���ѡ�������
//		  	nrf_baud= RADIO_GetValue(rd0);		//������ʱ�ʾֵ
//		    RX_Mode();							//�������ģʽ			
//          }
//		  else if (Id == GUI_ID_LISTBOX0)
//		  {      //NRF24L01����ͨ��ѡ����
//			nrf_Pipe= LISTBOX_GetSel(list1);	//���NRF24LL01����ͨ����ʾֵ 			
//		    RX_Mode();   						//�������ģʽ 	
//		  }
		 break;
		default: break;
      }	    
    default:
      WM_DefaultProc(pMsg);						//Ĭ�ϳ�����������Ϣ
	  break;
  }
}


/****************************************************************************
* ��    �ƣ�void Fun(void)
* ��    �ܣ���ʾ���������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void Fun(void) 
{
//  unsigned int  bt_index = 0;
//  unsigned int  bt_handler = 0;  
  GUI_CURSOR_Show();                                        //�����ͼ����ʾ  
  
  /* �����Ի���ʱ����������Դ�б���Դ��Ŀ�� ����ָ�������ڶ�����Ӧ�Ļص�����  */
  hWin = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), _cbCallback, 0, 0, 0);

  FRAMEWIN_SetFont(hWin, &GUI_FontComic18B_1);	  			//�Ի����������� 
  FRAMEWIN_SetClientColor(hWin, GUI_WHITE);		  			//�Ի���Ĵ�����ɫ�Ǻ�ɫ
//  memcpy(tx_buf, "1234567890abcdefghij!@#$%^&*()-=", 32);   //������Ϊ32�ֽڵķ����ַ������������ͻ�����
  memcpy(tx_buf, "", 32);
  memcpy(rx_buf, "", 32);									//�����ջ��������
 		
  text1 = WM_GetDialogItem(hWin, GUI_ID_TEXT0);				//��öԻ�����GUI_ID_TEXT0��Ŀ(�ı���Send Text Area)�ľ��
  text2 = WM_GetDialogItem(hWin, GUI_ID_TEXT1);				//��öԻ�����GUI_ID_TEXT1��Ŀ(�ı���Receive Text Area)�ľ��
  text3 = WM_GetDialogItem(hWin, GUI_ID_TEXT2);				//��öԻ�����GUI_ID_TEXT2��Ŀ(״̬�ַ��ı���)�ľ�� 
  TEXT_SetFont(text1,pFont);							    //���öԻ������ı���Send Text Area������
  TEXT_SetFont(text2,pFont);								//���öԻ������ı���Receive Text Area������
  TEXT_SetFont(text3,pFont);								//���öԻ�����״̬�ַ��ı��������
  TEXT_SetTextColor(text1,GUI_GREEN);						//���öԻ������ı���Send Text Area��������ɫ
  TEXT_SetTextColor(text2,GUI_GREEN);						//���öԻ������ı���Receive Text Area��������ɫ
  TEXT_SetTextColor(text3,GUI_RED);						    //���öԻ�����״̬�ַ��ı����������ɫ

  edit1 = WM_GetDialogItem(hWin, GUI_ID_EDIT1);				//��öԻ�����GUI_ID_EDIT1��Ŀ(�༭�� �����ַ�����ʾ��)�ľ��
  EDIT_SetFont(edit1,pFont18);								//���öԻ�����༭�� �����ַ�����ʾ��������
  EDIT_SetText(edit1,(const char *)tx_buf);								//���öԻ�����༭�� �����ַ�����ʾ�����ַ���
  edit2 = WM_GetDialogItem(hWin, GUI_ID_EDIT2);			    //��öԻ�����GUI_ID_EDIT2��Ŀ(�༭�� �����ַ�����ʾ��)�ľ��
  EDIT_SetFont(edit2,pFont18);								//���öԻ�����༭�� �����ַ�����ʾ��������
  EDIT_SetText(edit2,(const char *)rx_buf);								//���öԻ�����༭�� �����ַ�����ʾ�����ַ���

//  bt_handler = GUI_ID_BUTTON0;
//  for (bt_index=0; bt_index<10; bt_index++,bt_handler++)
//  {
//      bt[bt_index]=WM_GetDialogItem(hWin,bt_handler);				//��öԻ�����GUI_ID_BUTTON0��Ŀ(����SEND)�ľ��  
//  }
//  bt_handler = GUI_ID_BUTTON10;
//  for (bt_index=10; bt_index<=32; bt_index++,bt_handler++)
//  {
//      bt[bt_index]=WM_GetDialogItem(hWin,bt_handler);				//��öԻ�����GUI_ID_BUTTON0��Ŀ(����SEND)�ľ��  
//  }
  bt[0]=WM_GetDialogItem(hWin,GUI_ID_BUTTON0);				//��öԻ�����GUI_ID_BUTTON0��Ŀ(����SEND)�ľ��
  bt[1]=WM_GetDialogItem(hWin,GUI_ID_BUTTON1);				//��öԻ�����GUI_ID_BUTTON0��Ŀ(����CLEAR)�ľ��
  BUTTON_SetFont(bt[0],pFont);								//���öԻ����ﰴ��SEND������
  BUTTON_SetFont(bt[1],pFont);								//���öԻ����ﰴ��CLEAR������  
  BUTTON_SetTextColor(bt[0],0,GUI_WHITE); 					//���öԻ����ﰴ��SENDδ�����µ�������ɫ
  BUTTON_SetTextColor(bt[1],0,GUI_WHITE);					//���öԻ����ﰴ��CLEARδ�����µ�������ɫ
  			
  nrf_Pipe = 0;												//NRF24L01��ʼ����ͨ������Ϊ0			
  nrf_baud = 0;												//NRF24L01���� ��ʼΪ2MPS
  RX_Mode();												//NRF24L01�������ģʽ  
  while (1)
  {	   	
	
	if(Rx_Succ==1){	                                        //��NRF24L01���յ���Ч����
		EDIT_SetText(edit2,(const char *)rx_buf);		    //�����ջ��������ַ�д�뵽�����ַ��༭����
		TEXT_SetText(text3,(const char *)status_buf);		//��״̬�ı����������ַ�д�뵽״̬�ı�����
		Rx_Succ = 0; 		
	}
	WM_Exec();									            //ˢ����Ļ
  }	  
}

/******************* (C) COPYRIGHT 2013 �ܶ�STM32 *****END OF FILE****/
