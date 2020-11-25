//======================================================================
//�ļ����ƣ�user.h��userͷ�ļ���
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200221
//��Ҫ˵��������gpio.h�ļ���ʵ�ֶԾ���Ӧ�ñ�̣������Ƕ�����״̬�ȱ��
//======================================================================
#ifndef USER_H   //��ֹ�ظ����壨USER_H ��ʼ��
#define USER_H

//��1�����������ļ�����
#include "mcu.h"
#include "gpio.h"
#include "uart.h"
#include "systick.h"
#include "flash.h"
#include "wdog.h"
#include "emuart.h"
#include "printf.h"


//��2�����Ķ���ָʾ�ƶ˿ڼ����Ŷ��塪����ʵ��ʹ�õ����ŸĶ�

#define  LIGHT_RED      (PTA_NUM|5)   //���
#define  LIGHT_GREEN    (PTA_NUM|12)  //�̵�
#define  LIGHT_BLUE     (PTA_NUM|13)  //����
#define  LIGHT_ON       0   //��������״̬�궨�壬��Ӳ���ӷ�������
#define  LIGHT_OFF      1   //�ư�

//��3�����Ķ���UART����ģ�鶨��
#define UART_Debug  UART_2  //���ڳ�����£��޷���ʹ��
#define UART_User    UART_0  //�û�����
#define UART_User_Handler    UART0_IRQHandler  //�û������жϺ���

//��4�����Ķ���SysTick����ģ�鶨��
#define SYSTICK_USER_Handler SysTick_Handler   //�û�ϵͳ��ʱ���жϺ���


//��5��Flash�����궨�壬����ʵ�����õĲ������ݣ������û��޸�
//#define Offset 0                         //������д�롢���߼���ַ����ȡ������ʵ����ʹ��������ƫ�Ƶ�ַ
//#define CNT 30                           //������д�롢���߼���ַ����ȡ������ʵ����ʹ���ֽ���
//#define Content "Welcome to Soochow University!"//������д�롢��ȡ���߼���ַ��������ʵ������
//#define SectorNum   62       //������
//#define Address   (0xF800)  //62������ʼ��ַ��KL36������һ�������ռ��СΪ2KB��62*2^10= 0x0000F800
//#define CNTvar 0           //�������ַ����ȡ���ֽ���

#endif    //��ֹ�ظ����壨USER_H ��β��


