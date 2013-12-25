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
{/*
    public class PriorityQueue
    {
        KEY[] heap;                   // 最小堆

        public int Count { get; private set; }

        public PriorityQueue(int capacity)
        {
            this.heap = new KEY[capacity];
        }

        public void Push(KEY v)       // 添加元素
        {
            if (Count >= heap.Length)       // 如果堆中元素超过堆的容量，则重设堆
                Array.Resize(ref heap, Count * 2);
            heap[Count] = v;
            SiftUp(Count++);
        }

        public KEY Pop()              // 取出堆的头（此处为最小元素）
        {
            var v = Top();
            if (v == null)
                return null;
            heap[0] = heap[--Count];
            if (Count > 0) SiftDown(0);
                return v;
        }

        public KEY Top()              // 查看堆得头（不取出）
        {
            if (Count > 0) 
                return heap[0];
            return null;
        }

        void SiftUp(int n)          // 将Heap[n]往前挪
        {
            var v = heap[n];
            for (var n2 = n / 2; n > 0 && v.word.CompareTo(heap[n2]) < 0; n = n2, n2 /= 2)
                heap[n] = heap[n2];
            heap[n] = v;
        }

        void SiftDown(int n)        // 将Heap[n]往后挪
        {
            var v = heap[n];
            for (var n2 = n * 2; n2 < Count; n = n2, n2 *= 2)
            {
                if (n2 + 1 < Count && heap[n2 + 1].word.CompareTo(heap[n2]) > 0)
                    n2++;
                if (v.word.CompareTo(heap[n2]) <= 0) 
                    break;
                heap[n] = heap[n2];
            }
            heap[n] = v;
        }
    }

    public class KEY      // 元素类型
    {
        public string word;
        public int file;
        public int pos;
        public KEY(){}
        public KEY(string w, int f, int p)
        {
            word = w;
            file = f;
            pos = p;
        }
    }

    public class PartSort
    {
        public int NUM = 10000;
        
        public FileStream strm1;
        public StreamReader reader1;
        public FileStream strm2;
        public StreamWriter writer2;

        public PartSort()
        {
            strm1 = new FileStream("index.txt", FileMode.Open, FileAccess.Read);        // 打开文件index.txt
            reader1 = new StreamReader(strm1);
            strm2 = new FileStream("index2.txt", FileMode.Create, FileAccess.Write);    // 创建文件index2.txt
            writer2 = new StreamWriter(strm2);
        }

        ~PartSort()      // 析构函数，关闭文件
        {
            reader1.Close();
            writer2.Close();
            strm1.Close();
            strm2.Close();
        }

        public KEY getKey()     // 得到下一个KEY
        {
            if (reader1.EndOfStream)            // 若读到文件尾，则返回null
                return null;
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
            KEY key = new KEY(word, file, pos);
            return key;
        }

        public void Sort()
        {
            PriorityQueue<KEY>[] priorityqueue = new PriorityQueue<KEY>[2];
            priorityqueue[0] = new PriorityQueue<KEY>(NUM);
            priorityqueue[1] = new PriorityQueue<KEY>(NUM);


            int cur = 0;
            while (1)
            {
                while (priorityqueue[cur].Count() < NUM)           // 建堆
                {
                    KEY key = getKey();
                    if (key == null)
                        break;
                    priorityqueue[cur].Push(key);
                }

                while (priorityqueue[cur].Count() > 0)              // 置换排序
                {
                    KEY key = getKey();
                    KEY key2 = priorityqueue[cur].Pop();

                    if (key != null)
                    {
                        if (key2.word.CompareTo(key.word) <= 0)     // 如果新key不比堆中最小key2小
                            priorityqueue[cur].Push(key);       // 把key放入堆里
                        else
                            priorityqueue[1 - cur].Push(key);   // 如果新的key比堆中最小key2大，把key放入另外一个堆
                        writer2.WriteLine(key2.word + " " + key2.file.ToString() + " " + key2.pos.ToString());  // 写入index2.txt
                    }
                    else
                        writer2.WriteLine(key2.word + " " + key2.file.ToString() + " " + key2.pos.ToString());  // 写入index2.txt
                }
                cur = 1 - cur;
                if (priorityqueue[cur].Count() == 0)
                    break;
            }
        }
    }

   /* static class Program1
    {
        static void Main()
        {
            PartSort partsort = new PartSort();
            partsort.Sort();
        }
    }*/
}