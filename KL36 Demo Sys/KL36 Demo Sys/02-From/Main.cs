﻿using KL36_Demo_Sys._04_Control;
using System;
using System.Windows.Forms;

namespace KL36_Demo_Sys
{
    public partial class FrmMain : Form
    {

        public int count;
        UC_Introduction uci = new UC_Introduction();
        public FrmMain()
        {
            InitializeComponent();
            AddControlsToPanel(panelControls,uci);
            
        }
        public void AddControlsToPanel(Control master,Control slave)
        {
            master.Controls.Clear();
            master.Controls.Add(slave);
        }
        public void CheckUart()
        {
            count += 1;
            if (PublicVar.g_Uflag==1)
            {
                this.label3.Text = "连接成功";
                BtnConnection.Text = "已连接";
                BtnConnection.Enabled = false;
            }
            if(count>=2 && PublicVar.g_Uflag==-1)
            {
                this.label3.Text = "连接失败";
            }

        }
        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string msg = "确定需要退出吗？";
            if ((int)MessageBox.Show(msg, "提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation) == 1)
            {
                this.Dispose();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label3.Text = "正在连接";
            UC_SelectUart usu = new UC_SelectUart();
            AddControlsToPanel(panelControls,usu);
            timer1.Start();

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            CheckUart();
        }
        public void ClearPanel(Control c)
        {
            c.Controls.Clear();
        }
        private void 开始实验ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UC_GPIO ucg = new UC_GPIO();
            ClearPanel(panelControls);
            AddControlsToPanel(panelControls, ucg);

        }

        private void 返回首页ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ClearPanel(panelControls);
            AddControlsToPanel(panelControls, uci);
        }

        private void 开始实验ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            UC_UART ucu = new UC_UART();
            ClearPanel(panelControls);
            AddControlsToPanel(panelControls,ucu);

        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            UC_ADC uca = new UC_ADC();
            ClearPanel(panelControls);
            AddControlsToPanel(panelControls,uca);
        }

        private void toolStripMenuItem8_Click(object sender, EventArgs e)
        {
            UC_Timer uct = new UC_Timer();
            ClearPanel(panelControls);
            AddControlsToPanel(panelControls, uct);
        }
    }
}
