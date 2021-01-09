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
    uint16_t mcu_temp_AD;			 //�¶�ֵ
	uint16_t light;                  //����
	uint16_t data[20];
    float temperature;
    float mcu_temp;
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //��1.3����������ʹ�õľֲ���������ֵ
    mFlag=1;              //��ѭ��ʹ�õ���ʱ����������״̬��־
    
    //��1.4����ȫ�ֱ�������ֵ
   	//"ʱ����"�����ʼ��(00:00:00)
//   	gTime[0] = 0;       //ʱ
//   	gTime[1] = 0;	  	//��
//   	gTime[2] = 0;	  	//��
//   	mSec = gTime[2];	//��ס��ǰ���ֵ
    //��1.5���û�����ģ���ʼ��
    //��ʼ����ɫ��
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);    
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    //LCD��ʼ������ʼ�������
    LCD_Init();
    LCD_aotu(2,2,238,318,0);
    
    LCD_ShowCharactor(55,20,BLACK,GRAY,GB_16[3].Msk);
    LCD_ShowCharactor(70,20,BLACK,GRAY,GB_16[4].Msk);
    LCD_ShowCharactor(85,20,BLACK,GRAY,GB_16[5].Msk);
    LCD_ShowCharactor(100,20,BLACK,GRAY,GB_16[6].Msk);
    LCD_ShowCharactor(115,20,BLACK,GRAY,GB_16[7].Msk);
    LCD_ShowCharactor(130,20,BLACK,GRAY,GB_16[8].Msk);
    LCD_ShowCharactor(145,20,BLACK,GRAY,GB_16[9].Msk);
    LCD_ShowCharactor(160,20,BLACK,GRAY,GB_16[10].Msk);
    LCD_ShowCharactor(175,20,BLACK,GRAY,GB_16[11].Msk);
    LCD_ShowString(60,50,RED,GRAY,(char *)" Not Connected");

    LCD_ShowString(6,90,BLACK,GRAY,(char *)"LED_Color:");
    LCD_aotu(4,110,236,120,1);
    LCD_ShowString(6,125,BLACK,GRAY,(char *)"Mcu_Temp:");
    LCD_aotu(4,145,236,155,1);
    LCD_ShowString(6,160,BLACK,GRAY,(char *)"Round_Temp:");
    LCD_aotu(4,180,236,190,1);
    LCD_ShowString(6,195,BLACK,GRAY,(char *)"Light_Intensity:");
    LCD_aotu(4,215,236,225,1);
    //���ڳ�ʼ��
    uart_init(UART_User, 115200);
    uart_init(UART_Debug, 115200);
    //flash��ʼ��
    flash_init();
    //ADC��ʼ��
    adc_init(AD_BOARD_TEMP,0);        
  	adc_init(AD_MCU_TEMP,0);        
    adc_init(AD_BRIGHT,0);
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
        if(gadflag==1)
       {
       		LCD_ShowString(60,50,BLACK,GRAY, (char *)"                 ");
       		if(gcRecvBuf[0]==9&&strncmp((char *)(gcRecvBuf+1),"temp",4) == 0)
				{
					mcu_temp_AD = adc_read(AD_MCU_TEMP);
					mcu_temp=TempTrans(mcu_temp_AD);
					NumToStr_float(mcu_temp,1,data);
					uart_send_string(UART_User,data);
					LCD_ShowString(100,160,GREEN,GRAY,(char *)data);
					gadflag=0;
				}
			if(gcRecvBuf[0]==12&&strncmp((char *)(gcRecvBuf+1),"mcutemp",7) == 0)
				{
					temperature = TempRegression(adc_read(AD_BOARD_TEMP));
        			NumToStr_float(temperature,1,data);
					uart_send_string(UART_User,data);
					LCD_ShowString(80,125,GREEN,GRAY,(char *)data);
        			gadflag=0;
				}
			if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"light",7) == 0)
				{
					light = adc_read(AD_BRIGHT);
        			NumToStr_float(light/10.0,1,data);
        			uart_send_string(UART_User,data);
        			LCD_ShowString(135,195,GREEN,GRAY,(char *)data);
                	gadflag=0;
				}
       
       }
        if(gchflag==1){
        	LCD_ShowString(60,50,BLACK,GRAY, (char *)"                 ");
       		if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"red",3) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
					gpio_set(LIGHT_BLUE,LIGHT_OFF);
					gpio_set(LIGHT_GREEN,LIGHT_OFF);
					LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,RED,GRAY,(char *)"red ");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,RED);
					uart_send_string(UART_User,"���:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==9&&strncmp((char *)(gcRecvBuf+1),"blue",4) == 0)
				{
					gpio_set(LIGHT_BLUE,LIGHT_ON);  
					gpio_set(LIGHT_RED,LIGHT_OFF);
					gpio_set(LIGHT_GREEN,LIGHT_OFF);
					LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,BLUE,GRAY,(char *)"blue");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,BLUE);
					uart_send_string(UART_User,"����:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"green",5) == 0)
				{
					//�����̵ơ�����,���ƺ�ƣ�������
					gpio_set(LIGHT_GREEN,LIGHT_ON); 
					gpio_set(LIGHT_RED,LIGHT_OFF);
					gpio_set(LIGHT_BLUE,LIGHT_OFF);
					LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,GREEN,GRAY,(char *)"green");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,GREEN);
					uart_send_string(UART_User,"�̵�:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==9&&strncmp((char *)(gcRecvBuf+1),"cyan",4) == 0)
				{
					//������ơ�����
					gpio_set(LIGHT_BLUE,LIGHT_ON);   
					gpio_set(LIGHT_GREEN,LIGHT_ON);
					gpio_set(LIGHT_RED,LIGHT_OFF);
					LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,CYAN,GRAY,(char *)"cyan");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,CYAN);
					uart_send_string(UART_User,"��ƣ����̺ϳɣ�:��\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==11&&strncmp((char *)(gcRecvBuf+1),"violet",6) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
            		gpio_set(LIGHT_BLUE,LIGHT_ON);   
            		gpio_set(LIGHT_GREEN,LIGHT_OFF);
            		LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,VIOLET,GRAY,(char *)"violet");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,VIOLET);
            		uart_send_string(UART_User,"�ϵƣ������ϳɣ�:��\r\n");
            		gchflag=0;
				}
				if(gcRecvBuf[0]==11&&strncmp((char *)(gcRecvBuf+1),"yellow",6) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
           			gpio_set(LIGHT_GREEN,LIGHT_ON);
           			gpio_set(LIGHT_BLUE,LIGHT_OFF);
           			LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,YELLOW,GRAY,(char *)"yellow");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,YELLOW);
            		uart_send_string(UART_User,"�Ƶƣ����̺ϳɣ�:��\r\n");
            		gchflag=0;
				}
				if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"white",5) == 0)
				{
					//���ð׵ơ�����
					gpio_set(LIGHT_RED,LIGHT_ON);
            		gpio_set(LIGHT_BLUE,LIGHT_ON);
            		gpio_set(LIGHT_GREEN,LIGHT_ON);
            		LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,WHITE,GRAY,(char *)"white");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,WHITE);
            		uart_send_string(UART_User,"�׵ƣ������̺ϳɣ�:��\r\n");
            		gchflag=0;
				}
				 if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"off",3) == 0 )
				{
					//�ص�
					gpio_set(LIGHT_RED,LIGHT_OFF);
            		gpio_set(LIGHT_BLUE,LIGHT_OFF);
            		gpio_set(LIGHT_GREEN,LIGHT_OFF);
            		LCD_ShowString(90,90,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(90,90,BLACK,GRAY,(char *)"light off");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,270,i,GRAY);
            		uart_send_string(UART_User,"�ص�\r\n");
            		gchflag=0;
				}	   
       }//if(gchflag)��β
       
        

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



