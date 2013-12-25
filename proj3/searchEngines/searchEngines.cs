using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace searchEngines
{
    public partial class searchEngines : Form
    {
        public string str;
        public loserTree Tree;
        public searchEngines()
        {
            InitializeComponent();
        }

        private void buttonSearch_Click(object sender, EventArgs e)
        {
            str = searchStr.Text;
            report.SearchReport(str, Tree);
        }
        
        private void buttonMakeIndexTable_Click(object sender, EventArgs e)
        {
            //////////////////////////////////////////
            /////外排序，建立主码hash//////////////////////////
            partSort partsort = new partSort();

            List<long> bound = partsort.Sort();
            Console.WriteLine(bound.Count);

            Tree = new loserTree(bound, @"index3.txt", @"index2.txt");

            Tree.sort();
        }

        private void searchStr_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
