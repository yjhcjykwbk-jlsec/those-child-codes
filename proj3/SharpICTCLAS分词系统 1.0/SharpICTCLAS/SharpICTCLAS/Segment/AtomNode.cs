/***********************************************************************************
 * ICTCLAS��飺����������ʷ�����ϵͳICTCLAS
 *              Institute of Computing Technology, Chinese Lexical Analysis System
 *              �����У����ķִʣ����Ա�ע��δ��¼��ʶ��
 *              �ִ���ȷ�ʸߴ�97.58%(973ר��������)��
 *              δ��¼��ʶ���ٻ��ʾ�����90%�������й�������ʶ���ٻ��ʽӽ�98%;
 *              �����ٶ�Ϊ31.5Kbytes/s��
 * ����Ȩ��  Copyright(c)2002-2005�п�Ժ������ ְ������Ȩ�ˣ��Ż�ƽ
 * ��ѭЭ�飺��Ȼ���Դ�������Դ���֤1.0
 * Email: zhanghp@software.ict.ac.cn
 * Homepage:www.i3s.ac.cn
 * 
 *----------------------------------------------------------------------------------
 * 
 * Copyright (c) 2000, 2001
 *     Institute of Computing Tech.
 *     Chinese Academy of Sciences
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of
 * Institute of Computing Tech. and the posession or use of this file requires
 * a written license from the author.
 * Author:   Kevin Zhang
 *          (zhanghp@software.ict.ac.cn)��
 * 
 *----------------------------------------------------------------------------------
 * 
 * SharpICTCLAS��.netƽ̨�µ�ICTCLAS
 *               ���ɺӱ�����ѧ����ѧԺ���������Free��ICTCLAS�ı���ɣ�
 *               ����ԭ�д������˲�����д�����
 * 
 * Email: zhenyulu@163.com
 * Blog: http://www.cnblogs.com/zhenyulu
 * 
 ***********************************************************************************/
using System;
using System.Collections.Generic;
using System.Text;

namespace SharpICTCLAS
{
   public class AtomNode
   {
      public string sWord;
      public int nPOS;

      public AtomNode()
      {
      }

      public AtomNode(string sWord, int nPOS)
      {
         this.sWord = sWord;
         this.nPOS = nPOS;
      }
   }
}
