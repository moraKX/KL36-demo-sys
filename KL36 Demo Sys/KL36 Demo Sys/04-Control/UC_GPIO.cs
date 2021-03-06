﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KL36_Demo_Sys._04_Control
{
    public partial class UC_GPIO : UserControl
    {
        SCI sci;
        //委托,将从串口接收到的数据显示到接收框里面
        delegate void handleinterfaceupdatedelegate(Object textbox,
                                                    string text);

        byte[] Confirm  = { 8,  (byte)'L', (byte)'E', (byte)'D' }; //确认指令，指定下面接收的命令是LED相关
        byte[] RedON    = { 8,  (byte)'r', (byte)'e', (byte)'d' }; //点亮小灯指令
        byte[] BlueON   = { 9,  (byte)'b', (byte)'l', (byte)'u', (byte)'e' };
        byte[] GreenON  = { 10, (byte)'g', (byte)'r', (byte)'e', (byte)'e', (byte)'n' };
        byte[] CyanON   = { 9,  (byte)'c', (byte)'y', (byte)'a', (byte)'n' };
        byte[] VioletON = { 11, (byte)'v', (byte)'i', (byte)'o', (byte)'l', (byte)'e', (byte)'t' };
        byte[] YellowON = { 11, (byte)'y', (byte)'e', (byte)'l', (byte)'l', (byte)'o', (byte)'w' };
        byte[] WhiteON  = { 10, (byte)'w', (byte)'h', (byte)'i', (byte)'t', (byte)'e' };
        byte[] LedOff   = { 8,  (byte)'o', (byte)'f', (byte)'f' };
        public UC_GPIO()
        {
            InitializeComponent();
            sci = new SCI(PublicVar.g_SCIComNum, PublicVar.g_SCIBaudRate);
        }

        private void UC_GPIO_Load(object sender, EventArgs e)
        {
            
        }
        public void SetInt()
        {

            if (sci.SCIOpen())
            {
                //设置接收中断处理事件
                sci.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SCIPort_DataReceived);
                //设置每接收到1个字节中断1次
                sci.SCIReceInt(1);
            }

        }
        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 对    象:SCIPort                                                
        /// 事    件:DataReceived                                           
        /// 功    能:串口接收数据                                           
        /// 函数调用:(1)SCIReceiveData,串口接收函数                         
        ///          (2)SCIUpdateRevtxtbox,更新文本框中的内容               
        /// </summary>                                                      
        /// <param name="sender"></param>                                   
        /// <param name="e"></param>                                        
        ///-----------------------------------------------------------------
        private void SCIPort_DataReceived(object sender,
            System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            String str = String.Empty;
            bool Flag;//标记串口接收数据是否成功

            byte[] ch2 = new byte[2];
            //ComDevice.Encoding = System.Text.Encoding.GetEncoding("GB2312");

            //调用串口接收函数,并返回结果
            Flag = sci.SCIReceiveData(ref PublicVar.g_ReceiveByteArray);
            if (Flag == true)//串口接收数据成功
            {
                str = Encoding.GetEncoding("GB2312").GetString(PublicVar.g_ReceiveByteArray);
                SCIUpdateRevtxtbox(textBox1, str);
                sci.Close();
            }

        }

        ///-----------------------------------------------------------------
        /// <summary>                                                       
        /// 函数名:SCIUpdateRevtxtbox                                       
        /// 参  数:(1)textbox,Object类型,接收数据要放入的文本框             
        ///        (2)text,string类型,要放入文本框的数据                    
        /// 功  能:若串行接收与Object不在同一线程中运行，那么通过invoke     
        ///        跨线程用串口接收到的数据来更新接收文本框中的数据         
        /// 返  回:无                                                       
        /// </summary>                                                      
        /// <param name="textbox"></param>                                  
        /// <param name="str"></param>                                      
        ///-----------------------------------------------------------------
        private void SCIUpdateRevtxtbox(Object textbox, string text)
        {
            //textbox显示文本与串口执行不在同一个线程中
            if (((TextBox)textbox).InvokeRequired)
            {
                handleinterfaceupdatedelegate InterFaceUpdate = new
                    handleinterfaceupdatedelegate(SCIUpdateRevtxtbox);
                this.Invoke(InterFaceUpdate, new object[] { textbox, text });
            }
            else
            {
                ((TextBox)textbox).Text += text;
                //把光标放在最后一行
                ((TextBox)textbox).SelectionStart =
                                           ((TextBox)textbox).Text.Length;
                //将文本框中的内容调整到当前插入符号位置
                ((TextBox)textbox).ScrollToCaret();
            }
        }

        private void BtnLedBlue_Click(object sender, EventArgs e)
        {
    
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref BlueON);
                sci.Close();
                SetInt();
            }
            
        }

        private void BtnLedGreen_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref GreenON);
                sci.Close();
                SetInt();
            }
           
        }

        private void BtnLedCyan_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref CyanON);
                sci.Close();
                SetInt();
            }
           
        }

        private void BtnLedYellow_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref YellowON);
                sci.Close();
                SetInt();
            }
           
        }

        private void BtnLedViolet_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref VioletON);
                sci.Close();
                SetInt();
            }
          
        }

        private void BtnLedWhite_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref WhiteON);
                sci.Close();
                SetInt();
            }
           
        }

        private void BtnLedOff_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref LedOff);
                sci.Close();
                SetInt();
            }

        }

        private void BtnLedRed_Click(object sender, EventArgs e)
        {
            if (sci.SCIOpen())//串口打开成功
            {
                sci.SCISendFrameData(ref Confirm);
                sci.SCISendFrameData(ref RedON);
                sci.Close();
                SetInt();
            }
        }


    }
}
