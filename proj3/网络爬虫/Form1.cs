using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.IO;

using System.Net;
using System.Threading;
using SharpICTCLAS;
using outSort;

namespace 搜索引擎
{
    public partial class Form1 : Form
    {
        #region initialize
        public Form1()
        {
            //////////////////////////////////////////
            ////////切词////////////
            wordSeg = new WordSegmentSample(DictPath, 1);
            IndexStream = new StreamWriter(IndexWriter, Encoding.Unicode);
            for (int i = 0; i < result.Count; i++)
            {
                for (int j = 1; j < result[i].Length - 1; j++)
                    Console.Write("{0} /{1} ", result[i][j].sWord, Utility.GetPOSString(result[i][j].nPOS));
            }

            InitializeComponent();
        }

        #endregion
   
        #region someVariables of program
        bool Stop = false;                              //用户控制是否停止选项
        //爬虫初始爬的地址
        string OriginalFile = "http://my.xcar.com.cn/album/friend_albums.php?uid=2155639";  //默认起始读取网页文件
        //搜索引擎网页数据库地址
        string DownloadPath = @"down\";       //默认下载目录
        //写入索引文件流       
        FileStream IndexWriter=new FileStream(@"index.txt",FileMode.Append);
        StreamWriter IndexStream;
        //地址池
        System.Collections.Hashtable linkPool = new System.Collections.Hashtable();
        //切词所用字典路径
        string DictPath = Path.Combine(Environment.CurrentDirectory, "Data") + Path.DirectorySeparatorChar;
        //切词对象实例
        WordSegmentSample wordSeg;
        //爬虫：当前链接网页号码
        int numLinks = 235;
        #endregion 
        
        #region beginHere
        //爬虫开始：下载网页，分析链接和切词。保存索引和网页快照
        private void start_Click(object sender, EventArgs e)
        {
            numLinks = 0;
            new Thread(delegate() { begin(OriginalFile); }).Start();
        }
        void SetLinkDown(string url)
        {
            linkPool[url] = true;
        }
        public void begin(string strOriginalFile)
        {
            if (strOriginalFile == null) return;
            AddLink(strOriginalFile);
            while (!Stop)
            {
                string oneUrl = null;
                lock (linkPool.SyncRoot)
                {
                    foreach (string url in linkPool.Keys)
                    {
                        if (!(bool)linkPool[url])
                        {
                            oneUrl = url;
                            break;
                        }
                    }
                }
                if (oneUrl == null) break;
                if (Stop) break;
                DealWithOnePage(oneUrl);
                SetLinkDown(oneUrl);
                numLinks++;
            }
            Thread.CurrentThread.Abort();
            IndexStream.Close();
            IndexStream.Dispose();
            IndexWriter.Close();
            IndexWriter.Dispose();
        }
        #endregion

        #region DealWithOneWebFile
        //获得网页编码
        Regex getEncode = new Regex("(?:.*)(?:charset=[\"]?)(.*?\")(.*)", RegexOptions.IgnoreCase | RegexOptions.Multiline | RegexOptions.Compiled);
        //获得链接
        Regex reg = new Regex("(?:.*)(?:href=[\"]?)(http:.*?)(?:\".*)", RegexOptions.IgnoreCase | RegexOptions.Multiline | RegexOptions.Compiled);
        //添加网页链接
        void AddLink(string url)
        {
            if (linkPool[url] == null) { linkPool[url] = false; }
        }
        //读取一个网页
        void DealWithOnePage(string url)
        {
            string PageData;
            string encode;
            try
            {
                Uri PageAddress = new Uri(url);
                //获取网页内容
                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(PageAddress);

                // make the connect
                HttpWebResponse resp = (HttpWebResponse)req.GetResponse();

                // get the page data
                StreamReader tempsr = new StreamReader(resp.GetResponseStream(), Encoding.Default);

                PageData = tempsr.ReadToEnd();

                Match b = getEncode.Match(PageData);
                encode = getEncode.Replace(b.ToString(), "${1}");
                encode = encode.Substring(0, encode.Length - 1);

                //解决utf8导致乱码
                if (encode.ToLower().Equals("utf-8"))
                {
                    req = (HttpWebRequest)WebRequest.Create(PageAddress);
                    resp = (HttpWebResponse)req.GetResponse();
                    StreamReader sr = new StreamReader(resp.GetResponseStream(), Encoding.UTF8);
                    PageData = sr.ReadToEnd();
                    sr.Dispose();
                }
                tempsr.Dispose();
                tempsr.Close();
            }

            catch (Exception)
            {
                return;
            }

            //通过读取网页内容,链接到新网页
            string link_File = null;                             //链接到的文件名
            MatchCollection matches = reg.Matches(PageData);     //正则匹配，筛选链接
            foreach (Match a in matches)
            {
                if (a.Success)
                {   //匹配成功
                    link_File = reg.Replace(a.ToString(), "${1}");//筛选链接
                    if (link_File != null)
                        AddLink(link_File);                 //添加链接
                }
            }
            getText(ref PageData);           //获取网页正文及其他重要部分

            //把获取内容存储成本地
            FileStream write = new FileStream(DownloadPath + numLinks + ".html", FileMode.Create);
            StreamWriter writer = new StreamWriter(write, Encoding.Unicode);
            writer.WriteLine(url);
           
            long pos = IndexWriter.Position;
            writer.Write(PageData);
            writer.Flush();
            writer.Close();
            writer.Dispose();

            DealWithIndexs(PageData, pos);

        }
        #endregion

        #region getTextFromTheWebFile
        ////////////////////////////////////////////////////
        //获得正文
        Regex script = new Regex("<script.*?>.*?</script.*?>", RegexOptions.IgnoreCase | RegexOptions.Compiled | RegexOptions.Singleline);
        Regex style = new Regex("<style.*?>.*?</style.*?>", RegexOptions.IgnoreCase | RegexOptions.Compiled | RegexOptions.Singleline);
        Regex notcontex = new Regex("<.*?>", RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.Singleline);
        Regex voidPos = new Regex("[( )\t]+[^( )\t]", RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.Singleline);
        Regex voidLines = new Regex(@"(?:[\s^( )]\s+[^\s])", RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.Singleline);//([^( )(\r\n)])
        Regex otherMarks = new Regex(@"[(&gt/;)(&nbsp/;)]", RegexOptions.Compiled);
        public void getText(ref string sourceHTML)
        {
            sourceHTML.Replace("\r\n", "\n");
            sourceHTML.Replace("\n", "\r\n");
            Match b = script.Match(sourceHTML);
            while (b.Length > 0)
            {
                sourceHTML = sourceHTML.Replace(b.ToString(), "\r\n");
                b = b.NextMatch();
            }

            Match c = style.Match(sourceHTML);
            while (c.Length > 0)
            {
                sourceHTML = sourceHTML.Replace(c.ToString(), "\r\n");
                c = c.NextMatch();
            }

            Match d = notcontex.Match(sourceHTML);
            while (d.Length > 0)
            {
                sourceHTML = sourceHTML.Replace(d.ToString(), "\r\n");
                d = d.NextMatch();
            }
            Match g = otherMarks.Match(sourceHTML);
            while (g.Length > 0)
            {
                sourceHTML = sourceHTML.Replace(g.ToString(), "");
                g = g.NextMatch();
            }
            Match f = voidPos.Match(sourceHTML);
            while (f.Length > 0)
            {
                sourceHTML = sourceHTML.Replace(f.ToString(), " " + f.Value[f.Value.Length - 1]);
                f = f.NextMatch();
            }

            Match e = voidLines.Match(sourceHTML);
            while (e.Length > 0)
            {
                sourceHTML = sourceHTML.Replace(e.ToString(), "\r\n" + e.Value[e.Value.Length - 1]);
                e = e.NextMatch();
            }



        }

        #endregion

        #region divideWords
        public List<WordResult[]> divideWords(string a)
        {
            List<WordResult[]> result = new List<WordResult[]>();
            try
            {
                result = wordSeg.Segment(a);
            }
            catch (Exception)
            {
                return null;
            }
            return result;
        }
        #endregion

        #region dealWithIndexes
        
        index index = new index();
        Regex GetStr=new Regex(@".*?[\s^( )]");
        Regex GetWord = new Regex(@".*?( ).*");
        List<WordResult[]> result = new List<WordResult[]>();
        public void DealWithIndexs(string PageData,long pos)
        {   int i=0;
            Match str = GetStr.Match(PageData);
            string toBeDividedStr="";
            while (str.Length > 0)
            {
                toBeDividedStr = str.Value.Substring(0, str.Value.Length - 1);
                i = str.Index;
                addIndex(toBeDividedStr, i);
                str = str.NextMatch();
            }
        }
        public void addIndex(string str,long pos) 
        {
            if (str == null || str.Length<=0) return;
            if (str == @"\s") return;
            string temp = "";
            result = divideWords(str);
            if (result == null) return;
            foreach (WordResult[] a in result)
                foreach (WordResult b in a)
                    if (b.sWord != "始##始" && b.sWord != "末##末")
                    {
                        temp = getWord(b.sWord);
                        if (temp != "")
                        {
                           // Console.WriteLine(temp);
                            index.SetIndex(temp, numLinks, pos);
                            //Console.WriteLine(index.keyWord);
                            IndexStream.WriteLine(index.keyWord+" "+numLinks.ToString()+" "+ pos.ToString());
                        }
                    }
        }
        public string getWord(string temp)
        {
            int i=0;
            while(i<temp.Length)
            {
                if(temp[i++]==32)break;
            }
            return temp.Substring(0,i);
        }
        #endregion

        #region settingsLikeStopOrBeginningUrl
        ///////////////////////////////////////////////////////////////////////////////////////
        ////其他用户设置项////
        //起始网页地址,默认北大主页
        private void originalWebFile_TextChanged(object sender, EventArgs e)
        {
            OriginalFile = originalWebFile.Text;
        }

        //取消项
        private void stopDownload_Click(object sender, EventArgs e)
        {
            Stop = true;
        }
        #endregion
    }
}
