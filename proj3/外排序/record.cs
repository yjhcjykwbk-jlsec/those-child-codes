using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace outSort
{
    public class record
    {
    public bool NO_MEANING;
	public string key ;
	public int fNum ;
    public long posInFile;
    public record (string keyword, int num, long pos)
    {
        NO_MEANING = false;
        key = keyword;
        fNum=num;
        posInFile = pos;
    }
    public record()
    {
        NO_MEANING = false;
    }
   
    public  static bool operator < ( record a,record right){
		return (  a.key.CompareTo(right.key)<0) ;
	}
	public static bool operator>(record a, record right){
		return ( a.key.CompareTo(right.key )>0);
	}
	public static bool operator>=(record a, record right)
    {
		if(a<right) return false ;
		return true ;
	}
    public static bool operator <=(record a, record right)
    {
        if (a > right) return false;
        return true;
    }
    };
    
}
