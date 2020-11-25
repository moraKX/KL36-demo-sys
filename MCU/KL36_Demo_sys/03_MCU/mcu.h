//======================================================================
//�ļ����ƣ�mcu.h��mcuͷ�ļ���
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200221
//��Ҫ˵��������cpu.h��оƬͷ�ļ���������ֻҪ����mcu.h����
//======================================================================
#ifndef  MCU_H  //��ֹ�ظ����壨MCU_H ��ͷ��
#define  MCU_H
 //��1������оƬͷ�ļ�
#include "MKL36Z4.h"
#include "system_MKL36Z4.h"

//��2������cpuͷ�ļ�
#include "cpu.h"
void **  component_fun;   //���ڴ�ź���ָ�������ַ��

//��3�����жϺ궨��
#define ENABLE_INTERRUPTS        __enable_irq()             // �����ж�()
#define DISABLE_INTERRUPTS       __disable_irq()            // �����ж�()

//��BIOS���̺궨���޸Ĵ���1
#define MCU_IRQ_MAX           32     // �������ж�������
#define MCU_IRQ_PRIOR_MAX     3      // ����������ж����ȼ�
#define NOP 				     __asm ("NOP")              // �޲���
#define DisableIRQ(irq)          NVIC_DisableIRQ(irq)       // ��ֹirq�ж�
#define EnableIRQ(irq)           NVIC_EnableIRQ(irq)        // ��irq�ж�
#define SetPriority(irq, prio)   NVIC_SetPriority(irq, prio)  // ����irq�ж����ȼ�

//��4��MCU������Ϣ��غ곣��
//��BIOS���̺궨���޸Ĵ���2
//                                        "1234567890123456789"
#define MCU_TYPE              "AHL-GEC-KL36-V2.8   "  //MCU�ͺţ�19�ֽڣ�
//                                         "123456789"
#define BIOS_TYPE               "20200222 "       //BIOS�汾�ţ�19�ֽڣ�
#define MCU_SECTORSIZE        1024              //������С��B��
#define MCU_SECTOR_NUM        64                //MCU��������
#define MCU_STACKTOP          0x20001800        //ջ����ַ
#define MCU_FLASH_ADDR_START  0x00000000        //MCU��FLASH��ʼ��ַ
#define MCU_FLASH_ADDR_LENGTH 0x00010000        //MCU��FLASH���ȣ�64KB��
#define MCU_RAM_ADDR_START    0x1FFFF800	    //MCU��RAM��ʼ��ַ
#define MCU_RAM_ADDR_LENGTH   0x00002000	    //MCU��RAM���ȣ�8KB��


//(5)��λ���
//��BIOS���̺궨���޸Ĵ���3
#define IS_PIN_RESET_OCCURED      BGET(RCM_SRS0_PIN_SHIFT,RCM_SRS0)    // ������λ
#define IS_POWERON_RESET          BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0)   // �ϵ縴λ
#define IS_WDOG_RESET_OCCURED     BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0)  // ���Ź���λ
#define CLEAR_PIN_RESET_FLAG      NOP  //д1�����Ÿ�λ��־λ

//(6)����ϵͳʹ�õ�ʱ��Ƶ��
//��BIOS���̺궨���޸Ĵ���4
#define  MCU_SYSTEM_CLK       SystemCoreClock              // оƬϵͳʱ��Ƶ��(HZ)
#define  MCU_SYSTEM_CLK_KHZ   SystemCoreClock/1000         // оƬϵͳʱ��Ƶ��(KHz)
#define  MCU_BUS_CLK_KHZ      MCU_SYSTEM_CLK_KHZ/2         // оƬ����ʱ��Ƶ��(KHz)
#define  MCU_SYSTEM_CLK_MS    (SystemCoreClock / 1000)     // 1ms����ʱ��Ƶ��(HZ)
#define  MCU_SYSTEM_CLK_US    (MCU_SYSTEM_CLK_MS / 1000)   // 1us����ʱ��Ƶ��(HZ)

#endif  //��ֹ�ظ����壨MCU_H ��β��
