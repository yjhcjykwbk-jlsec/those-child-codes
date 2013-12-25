using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace searchEngines
{
    public class FilePos
    {
        public int file;    // 文件编号
        public List<long> poslist;      // 文件file中，关键码的位置
        public FilePos()
        {
            poslist = new List<long>();
        }
        public FilePos(int f)
        {
            file = f;
            poslist = new List<long>();
        }
        public int Count()
        {
            return poslist.Count;
        }
    }
}
