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

namespace SharpICTCLAS
{
   public class RowFirstDynamicArray<T> : DynamicArray<T>
   {

      #region GetElement Method

      //====================================================================
      // ������Ϊ nRow �ĵ�һ�����
      //====================================================================
      public ChainItem<T> GetFirstElementOfRow(int nRow)
      {
         ChainItem<T> pCur = pHead;

         while (pCur != null && pCur.row != nRow)
            pCur = pCur.next;

         return pCur;
      }

      //====================================================================
      // �� startFrom ����������Ϊ nRow �ĵ�һ�����
      //====================================================================
      public ChainItem<T> GetFirstElementOfRow(int nRow, ChainItem<T> startFrom)
      {
         ChainItem<T> pCur = startFrom;

         while (pCur != null && pCur.row != nRow)
            pCur = pCur.next;

         return pCur;
      }

      #endregion

      #region SetElement Method

      //====================================================================
      // ���û����һ���µĽ��
      //====================================================================
      public override void SetElement(int nRow, int nCol, T content)
      {
         ChainItem<T> pCur = pHead, pPre = null, pNew;  //The pointer of array chain

         if (nRow > RowCount)//Set the array row
            RowCount = nRow;

         if (nCol > ColumnCount)//Set the array col
            ColumnCount = nCol;

         while (pCur != null && (pCur.row < nRow || (pCur.row == nRow && pCur.col < nCol)))
         {
            pPre = pCur;
            pCur = pCur.next;
         }

         if (pCur != null && pCur.row == nRow && pCur.col == nCol)//Find the same position
            pCur.Content = content;//Set the value
         else
         {
            pNew = new ChainItem<T>();//malloc a new node
            pNew.col = nCol;
            pNew.row = nRow;
            pNew.Content = content;

            pNew.next = pCur;

            if (pPre == null)//link pNew after the pPre
               pHead = pNew;
            else
               pPre.next = pNew;
         }
      }

      #endregion

   }
}
