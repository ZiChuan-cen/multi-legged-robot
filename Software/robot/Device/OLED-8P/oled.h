#define _OLED_H_
#ifdef _OLED_H_

#include "sys.h"


/* the macro definition to trigger the led on or off
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

//---> .C �ļ���Ҫ�޸�ʱ��
#define OLED_sclk_Group  GPIOA
#define OLED_sclk_GPIO   GPIO_Pin_7
#define OLED_sid_Group   GPIOA
#define OLED_sid_GPIO    GPIO_Pin_6
#define OLED_rs_Group    GPIOA
#define OLED_rs_GPIO     GPIO_Pin_5
#define OLED_CS1_Group   GPIOA
#define OLED_CS1_GPIO    GPIO_Pin_4




#define OLED_CS_Group    GPIOA
#define OLED_CS_GPIO     GPIO_Pin_2
#define OLED_OUT_Group   GPIOA
#define OLED_OUT_GPIO    GPIO_Pin_3



//���κ꣬��������������һ��ʹ��
#define lcd_cs1(a)  if (a)  \
                    GPIO_SetBits(OLED_CS1_Group,OLED_CS1_GPIO);\
                    else        \
                    GPIO_ResetBits(OLED_CS1_Group,OLED_CS1_GPIO)

#define lcd_rs(a)   if (a)  \
                    GPIO_SetBits(OLED_rs_Group,OLED_rs_GPIO);\
                    else        \
                    GPIO_ResetBits(OLED_rs_Group,OLED_rs_GPIO)

#define lcd_sid(a)  if (a)  \
                    GPIO_SetBits(OLED_sid_Group,OLED_sid_GPIO);\
                    else        \
                    GPIO_ResetBits(OLED_sid_Group,OLED_sid_GPIO)

#define lcd_sclk(a) if (a)  \
                    GPIO_SetBits(OLED_sclk_Group,OLED_sclk_GPIO);\
                    else        \
                    GPIO_ResetBits(OLED_sclk_Group,OLED_sclk_GPIO)
#define Rom_CS(a)   if (a)  \
                    GPIO_SetBits(OLED_CS_Group,OLED_CS_GPIO);\
                    else        \
                    GPIO_ResetBits(OLED_CS_Group,OLED_CS_GPIO)

#define Rom_OUT(a)  if (a)  \
                    GPIO_SetBits(OLED_OUT_Group,OLED_OUT_GPIO);\
                    else        \
                    GPIO_ResetBits(OLED_OUT_Group,OLED_OUT_GPIO)


#define ROM_OUT    GPIO_ReadInputDataBit(OLED_OUT_Group,OLED_OUT_GPIO)

extern unsigned char const bmp1[];
extern unsigned char const jiong1[];
extern unsigned char const lei1[];


/*дָ�LCDģ��*/
void transfer_command_lcd(int data1);
/*д���ݵ�LCDģ��*/
void transfer_data_lcd(int data1);
/*��ʱ*/
void delay(int n_ms);
/*LCDģ���ʼ��*/
void OLED_Init(void);
void lcd_address(unsigned char page, unsigned char column);
/*ȫ������*/
void clear_screen(void);
/*��ʾ128x64����ͼ��*/
void display_128x64(const unsigned char *dp);
/*��ʾ132x64����ͼ��*/
//void display_132x64(unsigned char *dp);
/*��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��*/
void display_graphic_16x16(unsigned int page, unsigned int column, const unsigned char *dp);
/*��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��*/
void display_graphic_8x16(unsigned int page, unsigned char column, unsigned char *dp);
/*��ʾ5*7����ͼ��ASCII, ��5x7����������ַ�������ͼ��*/
void display_graphic_5x7(unsigned int page, unsigned char column, unsigned char *dp);
/****��ָ�����Ѷ�ֿ�IC***/
void send_command_to_ROM(unsigned char datu);
/****�Ӿ���Ѷ�ֿ�IC��ȡ���ֻ��ַ����ݣ�1���ֽڣ�***/
static unsigned char get_data_from_ROM(void);
/*����ص�ַ��addrHigh����ַ���ֽ�,addrMid����ַ���ֽ�,addrLow����ַ���ֽڣ�����������DataLen���ֽڵ����ݵ� pBuff�ĵ�ַ*/
/*������ȡ*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh, unsigned char addrMid, unsigned char addrLow, unsigned char *pBuff, unsigned char DataLen);
/******************************************************************/


void display_GB2312_string(unsigned char y, unsigned char x, char *text); //-- y��0,1,2,3
void display_string_5x7(unsigned char y, unsigned char x, unsigned char *text);
void Display_Byte(unsigned char y, unsigned char x, unsigned char Num);     //-- y��0,1,2,3   x��0,1,2,3......15


#endif
