//====================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-Arm��sumcu.suda.edu.cn��
//�汾���£�2017.08, 2020.05
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//====================================================================
#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�

//----------------------------------------------------------------------
//����ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������

//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̼���壩
int main(void)
{
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mMainLoopCount;  //��ѭ��ʹ�õļ�¼��ѭ����������
    uint8_t  mFlag;           //��ѭ��ʹ�õ���ʱ����
    uint8_t  mSec;	         //�ǵ�ǰ���ֵ
    uint8_t  i;
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //��1.3����������ʹ�õľֲ���������ֵ
    mFlag=1;              //��ѭ��ʹ�õ���ʱ����������״̬��־
    
    //��1.4����ȫ�ֱ�������ֵ
   	//"ʱ����"�����ʼ��(00:00:00)
   	gTime[0] = 0;       //ʱ
   	gTime[1] = 0;	  	//��
   	gTime[2] = 0;	  	//��
   	mSec = gTime[2];	//��ס��ǰ���ֵ
    //��1.5���û�����ģ���ʼ��
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
    LCD_Init();
    
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(92,20,RED,GRAY,(char *)"GPIO-LED");
    LCD_ShowString(60,40,RED,GRAY,(char *)"PC not connected");
    LCD_aotu(2,80,236,120,0);
    LCD_ShowString(6,92,BLACK,GRAY,(char *)"light:");
    uart_init(UART_User, 115200);
    uart_init(UART_Debug, 115200);
    flash_init();
    systick_init(10);      //����systickΪ10ms�ж�
    //��1.6��ʹ��ģ���ж�
    uart_enable_re_int(UART_User);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;

    //��1��======�������֣���β��==========================================
    
    //��2��======��ѭ�����֣���ͷ��=========================================
    for(;;)     //for(;;)����ͷ��
    {
        //��2.1����ѭ����������+1
        mMainLoopCount++;
        //��2.2��δ�ﵽ��ѭ�������趨ֵ������ѭ��
        if (mMainLoopCount<=0x1fffff)  continue;
        //��2.3���ﵽ��ѭ�������趨ֵ��ִ��������䣬���еƵ���������
        //��2.3.1�����ѭ����������
        mMainLoopCount=0; 
        if(gchflag==1){
        	LCD_ShowString(60,40,BLACK,GRAY, (char *)"                 ");
       		if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"red",3) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
					gpio_set(LIGHT_BLUE,LIGHT_OFF);
					gpio_set(LIGHT_GREEN,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,RED,GRAY,(char *)"red ");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,RED);
					uart_send_string(UART_User,"���:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==9&&strncmp((char *)(gcRecvBuf+1),"blue",4) == 0)
				{
					gpio_set(LIGHT_BLUE,LIGHT_ON);  
					gpio_set(LIGHT_RED,LIGHT_OFF);
					gpio_set(LIGHT_GREEN,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,BLUE,GRAY,(char *)"blue");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,BLUE);
					uart_send_string(UART_User,"����:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"green",5) == 0)
				{
					//�����̵ơ�����,���ƺ�ƣ�������
					gpio_set(LIGHT_GREEN,LIGHT_ON); 
					gpio_set(LIGHT_RED,LIGHT_OFF);
					gpio_set(LIGHT_BLUE,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,GREEN,GRAY,(char *)"green");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,GREEN);
					uart_send_string(UART_User,"�̵�:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==9&&strncmp((char *)(gcRecvBuf+1),"cyan",4) == 0)
				{
					//������ơ�����
					gpio_set(LIGHT_BLUE,LIGHT_ON);   
					gpio_set(LIGHT_GREEN,LIGHT_ON);
					gpio_set(LIGHT_RED,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,CYAN,GRAY,(char *)"cyan");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,CYAN);
					uart_send_string(UART_User,"��ƣ����̺ϳɣ�:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==11&&strncmp((char *)(gcRecvBuf+1),"violet",6) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
            		gpio_set(LIGHT_BLUE,LIGHT_ON);   
            		gpio_set(LIGHT_GREEN,LIGHT_OFF);
            		LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,VIOLET,GRAY,(char *)"violet");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,VIOLET);
            		uart_send_string(UART_User,"�ϵƣ������ϳɣ�:��\r\n");
            		gchflag=0;
				}
				if(gcRecvBuf[0]==11&&strncmp((char *)(gcRecvBuf+1),"yellow",6) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
           			gpio_set(LIGHT_GREEN,LIGHT_ON);
           			gpio_set(LIGHT_BLUE,LIGHT_OFF);
           			LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,YELLOW,GRAY,(char *)"yellow");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,YELLOW);
            		uart_send_string(UART_User,"�Ƶƣ����̺ϳɣ�:��\r\n");
            		gchflag=0;
				}
				if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"white",5) == 0)
				{
					//���ð׵ơ�����
					gpio_set(LIGHT_RED,LIGHT_ON);
            		gpio_set(LIGHT_BLUE,LIGHT_ON);
            		gpio_set(LIGHT_GREEN,LIGHT_ON);
            		LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,WHITE,GRAY,(char *)"white");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,WHITE);
            		uart_send_string(UART_User,"�׵ƣ������̺ϳɣ�:��\r\n");
            		gchflag=0;
				}
				 if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"off",3) == 0 )
				{
					//�ص�
					gpio_set(LIGHT_RED,LIGHT_OFF);
            		gpio_set(LIGHT_BLUE,LIGHT_OFF);
            		gpio_set(LIGHT_GREEN,LIGHT_OFF);
            		LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,BLACK,GRAY,(char *)"light off");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,GRAY);
            		uart_send_string(UART_User,"�ص�\r\n");
            		gchflag=0;
				}	   
       }
        

    }     //for(;;)��β
    //��2��======��ѭ�����֣���β��========================================
}

//======����Ϊ���������õ��Ӻ�����Ŵ�=====================================

//====================================================================
/*
֪ʶҪ�أ�
��1��main.c��һ��ģ�壬���ļ����д�������漰�����Ӳ���ͻ�����ͨ�����ù���
ʵ�ֶ�Ӳ���ĸ�Ԥ��
��2�����ļ��б��С����䡿�ĵط�Ϊϵͳ��������������������Ŀ�޹أ�����ɾ����
��3�����ļ��жԺ�GLOBLE_VAR�����˶��壬�����ڰ���"includes.h"ͷ�ļ�ʱ���ᶨ
��ȫ�ֱ������������ļ��а���"includes.h"ͷ�ļ�ʱ��
����ʱ���Զ�����extern
*/



