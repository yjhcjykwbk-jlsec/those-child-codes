using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace 搜索引擎
{
    public class index
    {
        public string keyWord;
        public int fileNum;
        public long pos;
        public index()
        {
            keyWord = "";
        }
        public index(string word, int num, long pos)
        {
            keyWord = word;
            fileNum = num;
            this.pos = pos;
        }
        public void SetIndex(string word, int num, long pos)
        {
            keyWord = word;
            fileNum = num;
            this.pos = pos;
        }
    }
}
