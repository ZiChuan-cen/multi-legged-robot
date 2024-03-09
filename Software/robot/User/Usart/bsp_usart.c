/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  zichuan
  * @date    2023-06-08
  * @brief   ���ô���
  ******************************************************************************
  */

#include "bsp_usart.h"
#include "stdio.h"



/**
    * @brief  ����USART1
    * @pin    UART1_TX:PA9  UART1_RX:PA10
    * @param  ��
    * @retval ��
    */
void Usart1_Config(void)
{
    /*********************************����GPIO*************************************/
    RCC_APB2PeriphClockCmd(USART1_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    //PA9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Pin  = USART1_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);//��ʼ���Ĵ���
    //PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin  = USART1_RX_Pin;
    GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);  //��ʼ���Ĵ���

    /*********************************���ô���*************************************/
    RCC_APB2PeriphClockCmd(USART1_CLK, ENABLE);  //��������ʱ��
    USART_InitTypeDef USART_InitStructure = {0};

    USART_InitStructure.USART_BaudRate = 115200;  //������
    USART_InitStructure.USART_HardwareFlowControl = DISABLE;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;  //��ʹ����żУ��
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART1, &USART_InitStructure); //��ʼ���Ĵ���
    USART_Cmd(USART1, ENABLE); //ʹ�ܴ���
}


/**
    * @brief  ����USART2
    * @pin    UART2_TX:PA2  UART2_RX:PA3
    * @param  ��
    * @retval ��
    */
void Usart2_Config(void)
{
    /*********************************����GPIO*************************************/
    RCC_APB2PeriphClockCmd(USART2_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    //PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //�����������
    GPIO_InitStructure.GPIO_Pin  = USART2_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_TX_PORT, &GPIO_InitStructure);
    //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //��������
    GPIO_InitStructure.GPIO_Pin  = USART2_RX_Pin;
    GPIO_Init(USART2_RX_PORT, &GPIO_InitStructure);

    /*********************************���ô���*************************************/
    RCC_APB1PeriphClockCmd(USART2_CLK, ENABLE);  //��������ʱ��
    USART_InitTypeDef USART_InitStructure = {0};

    USART_InitStructure.USART_BaudRate = 115200;  //������
    USART_InitStructure.USART_HardwareFlowControl = DISABLE;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;  //��ʹ����żУ��
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART2, &USART_InitStructure); //��ʼ���Ĵ���
    USART_Cmd(USART2, ENABLE); //ʹ�ܴ���
}

/**
    * @brief  ����USART3
    * @pin    UART3_TX:PB10     UART3_RX:PB11
    * @param  ��
    * @retval ��
    */
void Usart3_Config(void)
{
    /*********************************** ����GPIO ***********************************/
    RCC_APB2PeriphClockCmd(USART3_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    //PB10  USART3_TX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;    //�����������
    GPIO_InitStructure.GPIO_Pin   = USART3_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_TX_PORT, &GPIO_InitStructure);     //��ʼ���Ĵ���

    //PB11  USART3_RX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;  //��������
    GPIO_InitStructure.GPIO_Pin   = USART3_RX_Pin;
    GPIO_Init(USART3_RX_PORT, &GPIO_InitStructure);     //��ʼ���Ĵ���

    /*********************************** ���ô��� ***********************************/
    RCC_APB1PeriphClockCmd(USART3_CLK, ENABLE);
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate  =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   DISABLE;
    USART_InitStructure.USART_Mode  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity    =   USART_Parity_No;
    USART_InitStructure.USART_StopBits  =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength    =   USART_WordLength_8b;

    USART_Init(USART3, &USART_InitStructure);   //��ʼ���Ĵ���
    USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���
}




//printf�ض���
int fputc(int c, FILE *stream)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == 0) {}
    USART_SendData(USART1, c);
    return c;
}





