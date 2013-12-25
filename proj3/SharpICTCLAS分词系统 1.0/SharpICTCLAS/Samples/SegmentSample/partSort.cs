using System;
using System.Collections.Generic;

using System.Text;
using System.IO;
namespace outSort
{
    public class HEAP
    {
        KEY[] heap;                   // 最小堆
        public int Count;

        public HEAP(int capacity)
        {
            Count = 0;
            this.heap = new KEY[capacity];
        }

        public void Push(KEY v)       // 添加元素
        {
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
            for (var n2 = (n - 1) / 2; n > 0 && n2 >= 0 && v.word.CompareTo(heap[n2].word) < 0; n = n2, n2 = (n2 - 1) / 2)
                heap[n] = heap[n2];
            heap[n] = v;
        }

        void SiftDown(int n)        // 将Heap[n]往后挪
        {
            var v = heap[n];
            for (var n2 = n * 2 + 1; n2 < Count; n = n2, n2 = n2 * 2 + 1)
            {
                if (n2 + 1 < Count && heap[n2 + 1].word.CompareTo(heap[n2].word) < 0)
                    n2++;
                if (v.word.CompareTo(heap[n2].word) <= 0)
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
            public KEY() { }
            public KEY(string w, int f, int p)
            {
                word = w;
                file = f;
                pos = p;
            }
            static public KEY getKey(StreamReader reader1)     // 得到下一个KEY
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
        }

        public class PartSort
        {
            public int NUM = 5000;

            public FileStream strm1;
            public StreamReader reader1;
            public FileStream strm2;
            public StreamWriter writer2;

            public PartSort()
            {
                strm1 = new FileStream("index.txt", FileMode.Open, FileAccess.Read);        // 打开文件index.txt
                reader1 = new StreamReader(strm1, Encoding.Unicode);
                strm2 = new FileStream("index2.txt", FileMode.Create, FileAccess.Write);    // 创建文件index2.txt
                writer2 = new StreamWriter(strm2, Encoding.Unicode);
            }

            

            public List<long> Sort()
            {
                List<long> list = new List<long>();
                HEAP[] priorityqueue = new HEAP[2];
                priorityqueue[0] = new HEAP(NUM);
                priorityqueue[1] = new HEAP(NUM);


                int cur = 0;
                while (priorityqueue[cur].Count < NUM)           // 建堆
                {
                    KEY key = KEY.getKey(reader1);
                    if (key == null)
                        break;
                    priorityqueue[cur].Push(key);
                }
                while (true)
                {
                    writer2.Flush();
                    list.Add(writer2.BaseStream.Position);
                    while (priorityqueue[cur].Count > 0)                    // 置换排序
                    {
                        KEY key = KEY.getKey(reader1);
                        KEY key2 = priorityqueue[cur].Pop();

                        if (key != null)
                        {
                            if (key2.word.CompareTo(key.word) <= 0)         // 如果新key不比堆中最小key2小
                                priorityqueue[cur].Push(key);               // 把key放入堆里
                            else
                                priorityqueue[1 - cur].Push(key);           // 如果新的key比堆中最小key2xiao，把key放入另外一个堆
                        }
                        writer2.WriteLine(key2.word + " " + key2.file.ToString() + " " + key2.pos.ToString());  // 写入index2.txt
                    }
                    cur = 1 - cur;
                    if (priorityqueue[cur].Count == 0)
                        break;
                }
                writer2.Flush();
                strm1.Close();
                strm2.Close();
                strm1.Dispose();
                strm2.Dispose();
                reader1.Close();
                reader1.Dispose();
                return list;
            }
        }
        
    }