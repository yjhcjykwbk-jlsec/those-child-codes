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
using System.Text;
using System.Collections.Generic;

namespace SharpICTCLAS
{
   public abstract class DynamicArray<T>
   {
      protected ChainItem<T> pHead;  //The head pointer of array chain
      public int ColumnCount, RowCount;  //The row and col of the array

      #region Constructor

      public DynamicArray()
      {
         pHead = null;
         RowCount = 0;
         ColumnCount = 0;
      }

      #endregion

      #region ItemCount Property

      public int ItemCount
      {
         get
         {
            ChainItem<T> pCur = pHead;
            int nCount = 0;
            while (pCur != null)
            {
               nCount++;
               pCur = pCur.next;
            }
            return nCount;
         }
      }

      #endregion

      #region GetElement Method

      //====================================================================
      // �����С���ֵΪnRow, nCol�Ľ��
      //====================================================================
      public ChainItem<T> GetElement(int nRow, int nCol)
      {
         ChainItem<T> pCur = pHead;

         while (pCur != null && !(pCur.col == nCol && pCur.row == nRow))
            pCur = pCur.next;

         return pCur;
      }

      #endregion

      #region SetElement Method

      //====================================================================
      // ���û����һ���µĽ��
      //====================================================================
      public abstract void SetElement(int nRow, int nCol, T content);

      #endregion

      #region GetHead, GetTail, SetEmpty Method

      //====================================================================
      // Return the head element of ArrayChain
      //====================================================================
      public ChainItem<T> GetHead()
      {
         return pHead;
      }

      //====================================================================
      //Get the tail Element buffer and return the count of elements
      //====================================================================
      public int GetTail(out ChainItem<T> pTailRet)
      {
         ChainItem<T> pCur = pHead, pPrev = null;
         int nCount = 0;
         while (pCur != null)
         {
            nCount++;
            pPrev = pCur;
            pCur = pCur.next;
         }
         pTailRet = pPrev;
         return nCount;
      }

      //====================================================================
      // Set Empty
      //====================================================================
      public void SetEmpty()
      {
         pHead = null;
         ColumnCount = 0;
         RowCount = 0;
      }

      #endregion

      #region ToString Method

      public override string ToString()
      {
         StringBuilder sb = new StringBuilder();

         ChainItem<T> pCur = pHead;

         while (pCur != null)
         {
            sb.Append(string.Format("row:{0,3},  col:{1,3},  ", pCur.row, pCur.col));
            sb.Append(pCur.Content.ToString());
            sb.Append("\r\n");
            pCur = pCur.next;
         }

         return sb.ToString();
      }

      #endregion

      #region 

      public List<ChainItem<T>> ToListItems()
      {
         List<ChainItem<T>> result = new List<ChainItem<T>>();

         ChainItem<T> pCur = pHead;
         while (pCur != null)
         {
            result.Add(pCur);
            pCur = pCur.next;
         }

         return result;
      }

      #endregion
   }
}
