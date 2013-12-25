using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace mediaplayer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.InitialDirectory = "f:\\music";
            openFileDialog1.ShowDialog();
            String file = openFileDialog1.SafeFileName;
           
           // openFileDialog1.OpenFile();
            
        }
    }
}
