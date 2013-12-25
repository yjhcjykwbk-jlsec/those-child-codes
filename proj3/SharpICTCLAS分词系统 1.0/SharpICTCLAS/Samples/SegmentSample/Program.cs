using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using SharpICTCLAS;
using outSort;
class Program
{
   static void Main(string[] args)
   {
      string DictPath = Path.Combine(Environment.CurrentDirectory, "Data") + Path.DirectorySeparatorChar;
      //Console.WriteLine("正在初始化字典库，请稍候...");
      WordSegmentSample sample = new WordSegmentSample(DictPath, 1);
       
      List<WordResult[]> result = sample.Segment(@"fsfshg iosh goeiwo dsds");
      
      foreach (WordResult[] a in result)
      {
          foreach (WordResult b in a)
          {
              Console.WriteLine(b.sWord);
          }
          Console.WriteLine("");
      }
      Console.ReadLine();
   }

   static void PrintResult(List<WordResult[]> result)
   {
      Console.WriteLine();
      for (int i = 0; i < result.Count; i++)
      {
         for (int j = 1; j < result[i].Length - 1; j++)
            Console.Write("{0} /{1} ", result[i][j].sWord, Utility.GetPOSString(result[i][j].nPOS));

         Console.WriteLine();
      }
   }
}
