using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;
using SharpICTCLAS;

namespace ConsoleTest
{
   class Program
   {
      public static string DictPath = Path.Combine(Environment.CurrentDirectory, "Data") + Path.DirectorySeparatorChar;
      public static string coreDictFile = DictPath + "coreDict.dct";
      public static string biDictFile = DictPath + "BigramDict.dct";
      public static string contextFile = DictPath + "nr.ctx";
      public static string nrFile = DictPath + "tr.dct";

      static void Main(string[] args)
      {
         //TestDictionary();
         //TestNShortPath();
         //TestAtomSegment();
         //TestGenerateWordNet();
         //TestBiGraphGenerate();
         //TestBiSegment();
         //TestContextStat();
         //TestCCStringCompare();

         //Console.Write("按下回车键退出......");
         Console.ReadLine();
      }

     
    
     

     
     
   }
}
