using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
namespace outSort
{
    public class loserTree
    {
        FileStream outputFile;
        FileStream inputFile;
        StreamReader reader;
        StreamWriter writer;
        System.Collections.Hashtable keywordTable=new System.Collections.Hashtable();  //倒排索引
        long [] Boundaries;     //读的各段首个位置
        long [] Positions;      //读的各段当前位置
    
        public record[] L;      //实际记录数组
        public int[] B;         //名次编号数组。b【0】对应最小值编号。
        private int lowExt;
        private int offset;
        private int n;
        private int CurrentPaths;

        public loserTree(){}

        public loserTree(List<long> boundary,string outfileName,string infileName)
        {
            //boundary存储各段在文件中的起始地址
            //outfile存储归并以后的文件。
            //infile为归并以前的文件。
            //size为归并路数。
            n  = boundary.Count();
            CurrentPaths = n;
            outputFile=new FileStream(outfileName,FileMode.OpenOrCreate);
            inputFile=new FileStream(infileName,FileMode.Open);
            reader = new StreamReader(inputFile,Encoding.Unicode);
            writer = new StreamWriter(outputFile,Encoding.Unicode);

            Boundaries = new long[n+2];
            Positions = new long[n+1];
            for(int i=1;i<=n;i++)
            {
                Boundaries[i]=boundary[i-1];              //分段读入的起始地址，也是上一段读入的界限
                Positions[i]=boundary[i-1];
            }
            Boundaries[n+1] = inputFile.Length;        //最后一段的读入界限
  
            B = new int[n];
            L=new record[n+1];
            
            record temp;
            L[0] = new record();
            for(int i=1;i<=n;i++)
            {
                temp=getData(i);
                L[i]=temp;
            }
            init();
        }

        void play(int p, int l, int r) 	//p为B中的下标，l,r为L中的下标
        {
            B[p] = loser(l, r);
            Console.WriteLine(p + " " + B[p]);
            int tmp1 = winner(l, r), tmp2;
            while (p % 2 == 1 && p != 1)
            {
                tmp2 = winner(tmp1, B[p / 2]);
                B[p / 2] = loser(tmp1, B[p / 2]);
                //Console.WriteLine(((int)(p / 2)).ToString() + " " + B[(int)(p / 2)]);
                tmp1 = tmp2;
                p /= 2;
            }
            B[p / 2] = tmp1;	//将先阶段最后的胜者写入再高一层的节点中 等待兄弟节点的胜者来挑战
            //Console.WriteLine(((int)(p/2)).ToString() + " " + tmp1);
        }

        //size为实际选手数 最大为MAX 若超过MAX需要多次归并
        void init()
        {
            int s;
            for (s = 1; 2 * s <= n - 1; s *= 2) { }
            lowExt = (n - s) * 2;
            offset = 2 * s - 1;

            //由于lowExt内外节点的父节点编号转换公式不同 并且比赛的对象也不同 因此分开处理
            //并且如果n为奇数 那么将有一次内部节点和外部节点的比赛
            //先处理lowExt中的节点
            int i;
            for (i = 2; i <= lowExt; i += 2)
            {
                play((offset + i) / 2, i - 1, i);
            }
            //如果lowExt是奇数
            if ((n % 2) == 1)
            {
                play(n / 2, B[(n - 1) / 2], lowExt + 1);
                i = lowExt + 3;
            }
            else
                i = lowExt + 2;
            //处理lowExt以外的外部节点
            for (; i <= n; i += 2)
            {
                play((n - 1 + i - lowExt) / 2, i - 1, i);
            }
           
        }

        int winner(int x, int y)
        {
            if (L[x].NO_MEANING) return y;
            if (L[y].NO_MEANING) return x;
            if (L[x] < L[y]) return x;
            else return y;
        }

        int loser(int x, int y)
        {
            if (L[x].NO_MEANING) return x;
            if (L[y].NO_MEANING) return y;
            if (L[x] < L[y]) return y;
            else return x;
        }

       
        void replay(int i)
        {
            int p;
            if (i <= lowExt)
            {
                p = (offset + i) / 2;
            }
            else
            {
                p = (n - 1 + i - lowExt) / 2;
            }
            B[0] = winner(B[p], i);
            B[p] = loser(B[p], i);

           
            for (; (p / 2) >= 1; p /= 2)
            {
                int temp;
                temp = winner(B[p / 2], B[0]);
                B[p / 2] = loser(B[p / 2], B[0]);
                B[0] = temp;
            }

        }

        public void test()
        {
            long k=0;
            for(int i=1;i<=n;i++)
            {
                k=Boundaries[i];
                reader.BaseStream.Position=k;
                string temp=reader.ReadLine();
                Console.WriteLine(temp);
            }
        }

        record getData( int m )
        {
            string temp;
            inputFile.Seek(Positions[m], SeekOrigin.Begin);
            reader = new StreamReader(inputFile,Encoding.Unicode);
            //reader.BaseStream.Position = Positions[m];
            temp = reader.ReadLine();
            Positions[m] += 2 * temp.Length + 4;//reader.BaseStream.Position;
          
            int i = 0, len = temp.Length;
            string x = ""; string word = "";
            int file; long pos;
        
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
            pos = long.Parse(x);

            return (new record(word, file, pos));
        }
        
        public void sort()                             //外排序,建倒排索引
        {
            int i;
            string LastKey = "";
            string CurrentKey = null;
            long CurrentIndexFilePos = 0;
            while (CurrentPaths>0)
            {
                i = B[0];
                CurrentKey = L[i].key;
                if (CurrentKey.CompareTo(LastKey) != 0)
                {
                    CurrentIndexFilePos = outputFile.Position;
                    keywordTable[CurrentKey] = CurrentIndexFilePos;
                }
                writer.WriteLine(CurrentKey + " " + L[i].fNum + " " + L[i].posInFile);    //写入胜者
                writer.Flush();////////////
                if (Positions[i] < Boundaries[i + 1])    //没有冲突
                {
                    //Console.WriteLine(i);
                    L[i] = getData(i);
                    //Console.WriteLine(L[i].key);
                }
                else
                {
                    L[i].NO_MEANING = true;
                    CurrentPaths -= 1;
                }
                replay(i);                               //重新从i开始排序
            }
            writer.Close();
            reader.Close();
            inputFile.Close();
            outputFile.Close();
        }

        public List<FilePos> search(string word)    // 查询hash，返回word出现的List<文件、List<地址>>
        {
            long address = (long)keywordTable[word];
            FileStream strm = new FileStream("index2.txt", FileMode.Open, FileAccess.Read);
            strm.Seek(address, SeekOrigin.Begin);
            StreamReader reader = new StreamReader(strm);
            KEY key = new KEY();
            FilePos fp = new FilePos();
            List<FilePos> list = new List<FilePos>();   // list中的元素按照file从小到大的顺序排列

            key = KEY.getKey(reader);
            while (key != null && key.word == word)
            {
                fp.file = key.file;
                fp.poslist.Add(key.pos);
                int i;
                for (i = 0; i < list.Count && list[i].file <= fp.file; i++)
                {
                    if (list[i].file == fp.file)        // 将相同file的地址合并在一起
                    {
                        list[i].poslist.Union<long>(fp.poslist);
                        break;
                    }
                }
                if ((i < list.Count && list[i].file > fp.file) || i == list.Count)
                    list.Insert(i, fp);                 // 把新的file放入list
                key = KEY.getKey(reader);
            }

            return list;
        }

    };
}
