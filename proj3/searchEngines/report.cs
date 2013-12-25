using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;
using System.Windows.Forms;
namespace searchEngines
{
    public class report
    {
        static public void SearchReport(string str, loserTree Tree)
        {
            string temp1 = "", temp2 = "";
            
            char op;
            int len = str.Length;
            int i = 0;
            while (i < len && str[i] != '+' && str[i] != '-' && str[i] != '|')  // 提取第一个关键词
            {
                temp1 += str[i++];
            }
            if (i < len)
                op = str[i++];     // 提取操作符
            else
                op = ' ';
            while (i < len && str[i] != '+' && str[i] != '-' && str[i] != '|')  // 提取第二个关键词
            {
                temp2 += str[i++];
            }

            List<FilePos> l = new List<FilePos>();
            if (temp1.Length > 0 && temp2.Length > 0)       // 找到第一、二个关键词在倒排表中的内容
            {
                List<FilePos> l1 = new List<FilePos>();
                List<FilePos> l2 = new List<FilePos>();

                l1 = Tree.search(temp1);                // 如果不存在temp1,temp2，则返回null
                l2 = Tree.search(temp2);
                
                if (l1 != null && l2 != null)       // 如果两个都存在
                {
                    int j = 0;
                    switch (op)                 // 进行操作
                    {
                    case '|':               // 求key1.file和key2.file的并集
                            i = 0;
                            while (true)
                            {
                                if (i >= l1.Count || j >= l2.Count)
                                    break;
                                if (l1[i].file < l2[j].file)
                                {
                                    l.Add(l1[i]);
                                    i ++;
                                }
                                else if (l1[i].file > l2[j].file)
                                {
                                    l.Add(l2[j]);
                                    j ++;
                                }
                                else
                                {
                                    FilePos fp = new FilePos(l1[i].file);
                                    fp.poslist = l1[i].poslist.Union(l2[j].poslist).ToList<long>();
                                    i ++;
                                    j ++;
                                    l.Add(fp);
                                }
                            }
                            if (i < l1.Count)
                            {
                                while (i < l1.Count)
                                {
                                    l.Add(l1[i]);
                                    i ++;
                                }
                            }
                            if (j < l2.Count)
                            {
                                while (j < l2.Count)
                                {
                                    l.Add(l2[j]);
                                    j ++;
                                }
                            }
                        break;
                    case '-':               // 只含temp1，不含temp2
                        i = 0;
                        j = 0;
                            l = l1;
                            while (true)
                            {
                                if (i >= l1.Count || j >= l2.Count)
                                    break;
                                if (l1[i].file < l2[j].file)
                                    i++;
                                else if (l1[i].file > l2[j].file)
                                    j++;
                                else
                                {
                                    l.Remove(l1[i]);        // 如果有文件既含temp1，又含temp2，则从l中删除
                                    i++;
                                    j++;
                                }
                            }
                            break;
                    case '+':               // 求交集
                            while (true)
                            {
                                if (i >= l1.Count || j >= l2.Count)
                                    break;
                                if (l1[i].file < l2[j].file)
                                    i++;
                                else if (l1[i].file > l2[j].file)
                                    j++;
                                else
                                {
                                    FilePos fp = new FilePos(l1[i].file);
                                    fp.poslist = l1[i].poslist.Union(l2[j].poslist).ToList<long>();
                                    l.Add(fp);
                                    i++;
                                    j++;
                                }
                            }
                            break;
                    default:                // 没有运算符
                            break;
                    }// end switch
                }// end if
                else                     //如果有不存在的
                {
                    if (l1 != null)
                        l = l1;
                    else if (l2 != null)
                        l = l2;
                    else
                        l = null;
                }
            }// end if
            else if (temp1.Length > 0 && temp2.Length == 0)
            {
                l = Tree.search(temp1);
            }
            else
            {
                MessageBox.Show("请输入需要搜索的词语");
                return;
            }
            if (l != null)
            {

                // 对l按照词在file中出现的多少进行排序
                System.Comparison<FilePos> cmp = new Comparison<FilePos>(MyCompare);
                l.Sort(cmp);
            }
            /////////////////////////////////////////////////////////////////////
            // 索引报告
            FileStream strm = new FileStream("Report.htm", FileMode.Create, FileAccess.Write);  // 创建索引报告
            StreamWriter writer = new StreamWriter(strm, Encoding.UTF8);

            writer.WriteLine("<html>\r\n<body>");
            if (l == null)
                writer.WriteLine("<div>对不起，没有找到与" + str + "相关的网页</div><BR>");
            else
            {
                writer.WriteLine("<div>共得到" + l.Count.ToString() + "个检索结果</div><BR>\r\n<BR>");
                string url;
                string pageData;
                string pageData1;
                string picPath =@"pic\";
                for (i = 0; i < l.Count; i++)  // 写报告
                {
                    try
                    {
                        FileStream file = new FileStream("" + "down\\" + l[i].file + ".html", FileMode.Open);
                        StreamReader readfile = new StreamReader(file, Encoding.Unicode);
                        url = readfile.ReadLine();
                        pageData = readfile.ReadToEnd();
                        pageData1 = getMarkedText(pageData, l[i].poslist);
                        file.Close();
                        file.Dispose();
                        readfile.Close();
                        readfile.Dispose();
                        pageData = highLight(pageData, temp1, temp2);
                        pageData1 = highLight(pageData1, temp1, temp2);
                    }
                    catch (Exception)
                    {
                        continue;
                    }
                    
                    FileStream tempStrm = new FileStream(picPath+i+".html", FileMode.Create, FileAccess.Write);  // 创建索引报告
                    StreamWriter tempWriter = new StreamWriter(tempStrm, Encoding.UTF8);
                    tempWriter.WriteLine(pageData);
                    tempWriter.Flush();
                    tempWriter.Close();
                    tempWriter.Dispose();

                    writer.WriteLine("<A href=\"" + url + "\">" + url + "</A><BR>");//+ l[i].file + "</A><label>&nbsp&nbsp&nbsp" + l[i].file + "</label><BR>");
                    writer.WriteLine("<div>" + pageData1 + "</div>");
                    writer.WriteLine("<A href=\"" + picPath + i + ".html" + "\">" + "网页快照" + "</A><label>&nbsp" + "</label><BR><BR>");
                }
            }
            writer.WriteLine("</body>\r\n</html>");
            writer.Close();
            strm.Close();
            System.Diagnostics.Process.Start("Report.htm");  // 打开报告
        } 

        static public int MyCompare(FilePos fp1, FilePos fp2)
        {
            return (fp2.Count() - fp1.Count());
        }
      
        static public string highLight(string pageData, string temp1,string temp2)
        {
            Regex regex = new Regex(temp1, RegexOptions.Compiled | RegexOptions.Multiline | RegexOptions.IgnoreCase);
            Match match = regex.Match(pageData);
            while (match.Length > 0)
            {
                pageData = regex.Replace(pageData, "<span style=\"background:#ffff66;color:black;font-weight:bold\">" + temp1 + "</span>");
                match = match.NextMatch();
            }
            if (temp2 != "")
            {
                Regex regex1 = new Regex(temp2, RegexOptions.Compiled | RegexOptions.Singleline | RegexOptions.IgnoreCase);
                Match match1 = regex1.Match(pageData);
                while (match1.Length > 0)
                {
                    pageData = regex1.Replace(pageData, "<span style=\"background:#ffff66;color:black;font-weight:bold\">" + temp2 + "</span>");
                    match1 = match1.NextMatch();
                }
            }
            return pageData;
        }
        static public string getMarkedText( string str, List<long> list)      //截取网页中需要高亮的字符所在字符串
        {
            string result = "";
            int pos=0;
            foreach (long p in list)
            {
                pos = (int)p;
                while (pos<str.Length&&str[pos] != 13)
                {
                    result += str[pos++];
                }
                result += "\r\n";
            }
            return result;
        }
    }

}
