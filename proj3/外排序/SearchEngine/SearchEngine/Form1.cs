using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace SearchEngine
{

    public partial class Form1 : Form
    {
        static int FILENUM = 1001;
        static FileStream strm1;
        static StreamReader reader1;
        static hashdict Hashdict = new hashdict(1000000);

        public Form1()
        {
            InitializeComponent();

            strm1 = new FileStream("index.txt", FileMode.Open, FileAccess.Read);
            reader1 = new StreamReader(strm1);

            while (reader1.Peek() >= 0)             // 创建散列表
            {
                string temp = reader1.ReadLine();
                string word = "";
                string x = "";
                int file, pos;
                int i = 0, len = temp.Length;

                while (i < len && temp[i] != ' ')   // 提取word
                {
                    word += temp[i++];
                }
                i++;
                while (i < len && temp[i] != ' ')   // 提取file
                {
                    x += temp[i++];
                }
                file = int.Parse(x);
                i++;
                x = "";
                while (i < len && temp[i] != ' ')   // 提取pos
                {
                    x += temp[i++];
                }
                pos = int.Parse(x);
                Hashdict.insert(word, file, pos);   // 插入(word, file, pos)
            }
            reader1.Close();
            strm1.Close();
        }

        private void buttonSearch_Click(object sender, EventArgs e)
        {
            string temp1 = "", temp2 = "";
            string str = textBoxKeywords.Text;
            char op;
            int len = str.Length;
            int i = 0;
            while (i < len && str[i] != '+' && str[i] != '-' && str[i] != '|')  // 提取第一个关键词
            {
                temp1 += str[i ++];
            }
            if (i < len)
                op = str[i++];     // 提取操作符
            else
                op = ' ';
            while (i < len && str[i] != '+' && str[i] != '-' && str[i] != '|')  // 提取第二个关键词
            {
                temp2 += str[i++];
            }

            KEY key1, key2;
            List<int>[] file = new List<int>[FILENUM];

            if (temp1.Length > 0 && temp2.Length > 0)       // 找到第一、二个关键词在倒排表中的内容
            {
                key1 = new KEY();
                key1 = Hashdict.search(temp1);
                key2 = new KEY();
                key2 = Hashdict.search(temp2);
                switch (op)                 // 进行操作
                {
                    case '|':               // 求key1.file和key2.file的并集
                        for (i = 0; i < FILENUM; i++)
                        {
                            if (key1.file[i].Count != 0 && key2.file[i].Count != 0)
                            {
                                file[i] = (System.Collections.Generic.List<int>)key1.file[i].Union(key2.file[i]);
                            }
                        }
                        break;
                    case '-':               // 只含temp1，不含temp2
                        for (i = 0; i < FILENUM; i++)
                        {
                            if (key2.file[i].Count == 0)
                                file[i] = key1.file[i];
                            else
                                file[i] = null;
                        }
                        break;
                    case '+':               // 求key1.file和key2.file的交集
                        for (i = 0; i < FILENUM; i++)
                        {
                            if (key1.file[i].Count > 0 && key2.file[i].Count > 0)
                            {
                                key1.file[i].Sort();
                                key2.file[i].Sort();
                                if (key1.file[i].Count > key2.file[i].Count)
                                    foreach (int xx in key2.file[i])
                                        if (key1.file[i].Contains(xx))
                                            file[i].Add(xx);
                                        else
                                            foreach (int yy in key1.file[i])
                                                if (key2.file[i].Contains(yy))
                                                    file[i].Add(yy);
                            }
                        }
                        break;
                    default:                // 没有运算符
                        file = key1.file;
                        break;
                }
            }
            else if (temp1.Length > 0 && temp2.Length == 0)
            {
                key1 = new KEY();
                key1 = Hashdict.search(temp1);
                file = key1.file;
            }
            else
            {
                MessageBox.Show("请输入需要搜索的词语");
                return;
            }

            textBoxShowWebAddress.Text = key1.word;

            for (i = 0; i < FILENUM; i++)
            {
                if (file[i] != null && file[i].Count() > 0)
                {
                    textBoxShowWebAddress.Text += " file:" + i.ToString() + " address:";
                    for (int j = 0; j < file[i].Count(); j++)
                        textBoxShowWebAddress.Text += " " + file[i][j].ToString();
                }
            }
            /*
            FileStream strm = new FileStream("Report.htm", FileMode.Create, FileAccess.Write);  // 创建索引报告
            StreamWriter writer = new StreamWriter(strm, Encoding.UTF8);
            for (i = 0; i < FILENUM; i++)  // 写报告
            {
                if (file[i].Count > 0)
                {
                    //    writer.WriteLine("<A href=\"" + G.graList[i].v.address + "\">" + G.graList[i].v.address + "</A><label>&nbsp&nbsp&nbsp" + G.graList[i].v.title + "</label><BR>");
                }
            }
            writer.Close();
            strm.Close();
            System.Diagnostics.Process.Start("Report.htm");  // 打开报告*/
        }

        public class KEY
        {
            public string word; // 词
            public List<int>[] file;    // file[n]代表编号为n的文件中word所在的位置的List
            public KEY()
            {
                word = "";
                file = new List<int>[FILENUM];
            }
        }

        public class hashdict
        {
            private int M;      // 表长
            public KEY[] HT;    // 散列表放在daopai.txt文件
            public hashdict(int sz)
            {
                M = sz;
                HT = new KEY[M];
            }
            public int h(string word)           // ELFhash散列函数
            {
                string s = new string(word.ToCharArray());
                long g, h = 0;
                int i = 0, len = s.Length;
                while (i < len)
                {
                    h = (h << 4) + s[i++].GetHashCode();
                    g = h & 0xF0000000L;
                    if (g != 0)
                        h ^= g >> 24;
                    h &= ~g;
                }
                return (int)h % M;
            }
            public int p(int i)     // 二次探查法的探查函数
            {
                if (i % 2 != 0)
                    return i * i / 4;
                else
                    return -i / 2 * i / 2;
            }
            public void insert(string word, int file, int position)  // 往daopai.txt即倒排文件中插入此元素
            {
                int home;       // 存储基位置
                int i = 0;      // 探查序列编号
                int pos = h(word);     // 初始化探查序列
                home = pos;
                while (HT[pos] != null)
                {
                    if (HT[pos].word == word)       // 如果word已经存在倒排表中，则把它出现的位置添加进去
                    {
                        if (HT[pos].file[file] == null)
                            HT[pos].file[file] = new List<int>();
                        HT[pos].file[file].Add(position);
                    }
                    i++;
                    pos = (home + p(i)) % M;
                    if (pos < 0)
                        pos = 0 - pos;
                }
                HT[pos] = new KEY();                // 如果word不存在倒排表中，则添入
                HT[pos].word = word;
                if (HT[pos].file[file] == null)
                    HT[pos].file[file] = new List<int>();
                HT[pos].file[file].Add(position);
            }
            public KEY search(string word)        // 找到word对应HT中的元素
            {
                int home = h(word);
                int i = 0;
                int pos = home;
                while (HT[pos] != null)
                {
                    if (HT[pos].word == word)
                        return HT[pos];
                    i++;
                    pos = (home + p(i)) % M;
                }
                KEY key = new KEY();             // 没有找到word
                return key;
            }
        }
    }
}
