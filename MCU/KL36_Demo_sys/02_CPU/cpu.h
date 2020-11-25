//======================================================================
//�ļ����ƣ�cpu.h��cpuͷ�ļ���
//������λ��SD-ARM(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200502
//��Ҫ˵��������cpu��ص�ͷ�ļ�������mcu.hֻҪ����cpu.h�Ϳ�����
//======================================================================
#ifndef   CPU_H    //��ֹ�ظ����壨��ͷ��
#define  CPU_H

#include "core_cm0plus.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"

//��1��λ�����꺯������λ����λ����üĴ���һλ��״̬��
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    //�üĴ�����һλ
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  //��Ĵ�����һλ
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  //��üĴ���һλ��״̬

//��2�����Ż����ͻ������ͱ����궨��
typedef volatile uint8_t       vuint8_t;         // ���Ż��޷�����
typedef volatile uint16_t     vuint16_t;
typedef volatile uint32_t     vuint32_t;
typedef volatile uint64_t     vuint64_t;
typedef volatile int8_t         vint8_t;         // ���Ż��з�����
typedef volatile int16_t       vint16_t;
typedef volatile int32_t       vint32_t;
typedef volatile int64_t       vint64_t;

#endif          //��ֹ�ظ����壨��β��