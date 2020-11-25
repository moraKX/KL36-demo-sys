///======================================================================
//�ļ����ƣ�gec.c�ļ�
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200221
//��Ҫ˵�������Ժ�פ�������ӿڵ�ʹ��
//                ��С���ϵͳ�����Ҳ���
//======================================================================

#include "gec.h"


//======================================================================
//�������ƣ�BIOS_API_Init
//�������أ���
//����˵������
//���ܸ�Ҫ����1��BIOS����������������ָ���ʼ��
//       ��2��User�ж��������漰BIOS�����ж������ĸ���
//======================================================================
void  BIOS_API_Init()
{
#if (GEC_USER_SECTOR_START!=0)
	uint32_t user[MCU_SECTORSIZE/4];
	void ** bios=MCU_FLASH_ADDR_START;
//��1��������������ָ���ʼ��
     component_fun=(void **)(GEC_COMPONENT_LST_START*MCU_SECTORSIZE);//���ھɰ汾BIOS���ֶ���ֵ
//��2���ı�User�ж���������BIOS_UART�жϡ�BIOS_TIMER�ж�����
     flash_read_physical((uint8_t *)user,GEC_USER_SECTOR_START*MCU_SECTORSIZE,MCU_SECTORSIZE);
     if((user[BIOS_UART_UPDATE_IRQn] != (uint32_t)bios[BIOS_UART_UPDATE_IRQn]) //�ж�USER�д��ڸ����жϺͶ�ʱ���ж��Ƿ�ΪBIOS��Ӧ�жϵ�ַ
     	  || (user[BIOS_TIMER_IRQn] != (uint32_t)bios[BIOS_TIMER_IRQn]))    //�����ǣ����������������޸�ΪBIOS��Ӧ�жϵ�ַ
	 {
    	 flash_erase(GEC_USER_SECTOR_START);

		 //��USER�ж��������BIOS����д�봮�ڵ��жϴ�������ַ
		 user[BIOS_UART_UPDATE_IRQn]=(uint32_t)bios[BIOS_UART_UPDATE_IRQn];
		 //��USER�ж��������BIOS����ʱ�����жϴ�������ַ
		 user[BIOS_TIMER_IRQn]=(uint32_t)bios[BIOS_TIMER_IRQn];

		 flash_write_physical(GEC_USER_SECTOR_START*MCU_SECTORSIZE,MCU_SECTORSIZE,(uint8_t *)user);
	 }
//��3���ж�������ָ���ض���
	 SCB->VTOR = (uint32_t)GEC_USER_SECTOR_START*MCU_SECTORSIZE;//ָ��USER����FLASH�е��ж�������
	 printf("  ��USER��ʾ��������USER��������...\r\n");
	 wdog_feed();
#endif
}

