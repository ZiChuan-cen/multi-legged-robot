#include "OLED.h"
#include "OLED_Font.h"



/*���ų�ʼ��*/
void OLED_SPI_Init(void)
{
/********************************** �������� **********************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;          //OLED_W_D0
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;          //OLED_W_D1
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;          //OLED_W_RES
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;          //OLED_W_DC
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //OLED_W_CS
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    OLED_W_D0(1);
    OLED_W_D1(1);
    OLED_W_RES(1);
    OLED_W_DC(1);
    OLED_W_CS(1);
}

/**
  * @brief  SPI����һ���ֽ�
  * @param  Byte Ҫ���͵�һ���ֽ�
  * @retval ��
  */
void OLED_SPI_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        OLED_W_D0(0);
        OLED_W_D1(Byte & (0x80 >> i));
        OLED_W_D0(1);
    }
}

/**
  * @brief  OLEDд����
  * @param  Command Ҫд�������
  * @retval ��
  */
void OLED_WriteCommand(uint8_t Command)
{
    OLED_W_CS(0);
    OLED_W_DC(0);
    OLED_SPI_SendByte(Command);
    OLED_W_CS(1);
}

/**
  * @brief  OLEDд����
  * @param  Data Ҫд�������
  * @retval ��
  */
void OLED_WriteData(uint8_t Data)
{
    OLED_W_CS(0);
    OLED_W_DC(1);
    OLED_SPI_SendByte(Data);
    OLED_W_CS(1);
}

/**
  * @brief  OLED���ù��λ��
  * @param  Y �����Ͻ�Ϊԭ�㣬���·�������꣬��Χ��0~7
  * @param  X �����Ͻ�Ϊԭ�㣬���ҷ�������꣬��Χ��0~127
  * @retval ��
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCommand(0xB0 | Y);                    //����Yλ��
    OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));    //����Xλ�ø�4λ
    OLED_WriteCommand(0x00 | (X & 0x0F));           //����Xλ�õ�4λ
}

/**
  * @brief  OLED����
  * @param  ��
  * @retval ��
  */
void OLED_Clear(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++)
    {
        OLED_SetCursor(j, 0);
        for (i = 0; i < 128; i++)
        {
            OLED_WriteData(0x00);
        }
    }
}

/**
  * @brief  OLED��ʾһ���ַ�
  * @param  Line ��λ�ã���Χ��1~4
  * @param  Column ��λ�ã���Χ��1~16
  * @param  Char Ҫ��ʾ��һ���ַ�����Χ��ASCII�ɼ��ַ�
  * @retval ��
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);       //���ù��λ�����ϰ벿��
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i]);          //��ʾ�ϰ벿������
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);   //���ù��λ�����°벿��
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);      //��ʾ�°벿������
    }
}

/**
  * @brief  OLED��ʾ�ַ���
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  String Ҫ��ʾ���ַ�������Χ��ASCII�ɼ��ַ�
  * @retval ��
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar(Line, Column + i, String[i]);
    }
}

/**
  * @brief  OLED�η�����
  * @retval ����ֵ����X��Y�η�
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  OLED��ʾ���֣�ʮ���ƣ�������
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~4294967295
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~10
  * @retval ��
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  OLED��ʾ���֣�ʮ���ƣ�����������
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��-2147483648~2147483647
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~10
  * @retval ��
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    uint8_t i;
    uint32_t Number1;
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');
        Number1 = -Number;
    }
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  OLED��ʾ���֣�ʮ�����ƣ�������
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~0xFFFFFFFF
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~8
  * @retval ��
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)
    {
        SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            OLED_ShowChar(Line, Column + i, SingleNumber + '0');
        }
        else
        {
            OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
        }
    }
}

/**
  * @brief  OLED��ʾ���֣������ƣ�������
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~1111 1111 1111 1111
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~16
  * @retval ��
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
    }
}


/**
  * @brief  OLED��ʾ����
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  
  * @param  
  * @retval ��
  */
void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t num)
{
	uint8_t i;
	OLED_SetCursor((Line - 1)*2, (Column - 1)*16);
	for(i=0; i<16; i++)
	{
		OLED_WriteData(Font_Chinese[2*num][i]);
	}
	OLED_SetCursor((Line - 1)*2 + 1, (Column - 1)*16);
	for(i=0; i<16; i++)
	{
		OLED_WriteData(Font_Chinese[2*num + 1][i]);
	}
}



/**
  * @brief  OLED��ʾͼƬ����ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  
  * @param  
  * @retval ��
  */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char PI[])
{  
	unsigned int j=0;
	unsigned char x,y;

	// if(y1%8==0) y=y1/8;      
	// else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetCursor(y,x0);  //��һ������y,�ڶ�������x//���ù��λ�����Ͻ�(0,0) ����0-7 �� ����0-127
		for(x=x0;x<x1;x++)
		{      
			OLED_WriteData(PI[j++]);      //д����
		}
	}
} 


void OLED_BMP(int i)
{ 
   OLED_Clear();
   OLED_DrawBMP(0,2,127,0,PI[i]);
   OLED_DrawBMP(0,2,127,1,PI[i]);
   OLED_DrawBMP(0,2,127,2,PI[i]);
   OLED_DrawBMP(0,2,127,3,PI[i]);
   OLED_DrawBMP(0,2,127,4,PI[i]);
   OLED_DrawBMP(0,2,127,5,PI[i]);
   OLED_DrawBMP(0,2,127,6,PI[i]);
   OLED_DrawBMP(0,2,127,7,PI[i]);
}





/**
  * @brief  OLED��ʼ��
  * @param  ��
  * @retval ��
  */
void OLED_Init(void)
{
    uint32_t i, j;

    for (i = 0; i < 1000; i++)          //�ϵ���ʱ
    {
        for (j = 0; j < 1000; j++);
    }

    OLED_SPI_Init();            //�˿ڳ�ʼ��

    OLED_WriteCommand(0xAE);    //�ر���ʾ

    OLED_WriteCommand(0xD5);    //������ʾʱ�ӷ�Ƶ��/����Ƶ��
    OLED_WriteCommand(0x80);

    OLED_WriteCommand(0xA8);    //���ö�·������
    OLED_WriteCommand(0x3F);

    OLED_WriteCommand(0xD3);    //������ʾƫ��
    OLED_WriteCommand(0x00);

    OLED_WriteCommand(0x40);    //������ʾ��ʼ��

    OLED_WriteCommand(0xA1);    //�������ҷ���0xA1���� 0xA0���ҷ���

    OLED_WriteCommand(0xC8);    //�������·���0xC8���� 0xC0���·���

    OLED_WriteCommand(0xDA);    //����COM����Ӳ������
    OLED_WriteCommand(0x12);

    OLED_WriteCommand(0x81);    //���öԱȶȿ���
    OLED_WriteCommand(0xCF);

    OLED_WriteCommand(0xD9);    //����Ԥ�������
    OLED_WriteCommand(0xF1);

    OLED_WriteCommand(0xDB);    //����VCOMHȡ��ѡ�񼶱�
    OLED_WriteCommand(0x30);

    OLED_WriteCommand(0xA4);    //����������ʾ��/�ر�

    OLED_WriteCommand(0xA6);    //��������/��ת��ʾ

    OLED_WriteCommand(0x8D);    //���ó���
    OLED_WriteCommand(0x14);

    OLED_WriteCommand(0xAF);    //������ʾ

    OLED_Clear();               //OLED����
}



