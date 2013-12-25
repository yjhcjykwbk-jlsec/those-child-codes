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
using System.Diagnostics;
using System.Collections.Generic;
using System.Text;

namespace SharpICTCLAS
{
   public class NShortPath
   {
      private static ColumnFirstDynamicArray<ChainContent> m_apCost;
      private static int m_nValueKind; //The number of value kinds
      private static int m_nNode; //The number of Node in the graph
      private static CQueue[][] m_pParent; //The 2-dimension array for the nodes
      private static double[][] m_pWeight; //The weight of node

      #region ���캯��

      private NShortPath()
      {
      }

      #endregion

      #region InitNShortPath Method

      private static void InitNShortPath(ColumnFirstDynamicArray<ChainContent> apCost, int nValueKind)
      {
         m_apCost = apCost; //Set the cost
         m_nValueKind = nValueKind; //Set the value kind

         // ��ȡ�������Ŀ
         // ----------------- ע��by zhenyulu ------------------
         // ԭ������Ϊm_nNode = Math.Max(apCost.ColumnCount, apCost.RowCount) + 1;
         // ��apCost.ColumnCountӦ��һ������apCost.RowCount�����Ըĳ�������
         m_nNode = apCost.ColumnCount + 1;

         m_pParent = new CQueue[m_nNode - 1][]; //not including the first node
         m_pWeight = new double[m_nNode - 1][];

         //The queue array for every node
         for (int i = 0; i < m_nNode - 1; i++)
         {
            m_pParent[i] = new CQueue[nValueKind];
            m_pWeight[i] = new double[nValueKind];

            for (int j = 0; j < nValueKind; j++)
               m_pParent[i][j] = new CQueue();
         }
      }

      #endregion

      #region Calculate Method

      //====================================================================
      // ��������н���Ͽ��ܵ�·����Ϊ·�������ṩ����׼��
      //====================================================================
      public static void Calculate(ColumnFirstDynamicArray<ChainContent> apCost, int nValueKind)
      {
         InitNShortPath(apCost, nValueKind);

         QueueElement tmpElement;
         CQueue queWork = new CQueue();
         double eWeight;

         for (int nCurNode = 1; nCurNode < m_nNode; nCurNode++)
         {
            // �����е���ǰ��㣨nCurNode)���ܵı߸���eWeight����ѹ�����
            EnQueueCurNodeEdges(ref queWork, nCurNode);

            // ��ʼ����ǰ������бߵ�eWeightֵ
            for (int i = 0; i < m_nValueKind; i++)
               m_pWeight[nCurNode - 1][i] = Predefine.INFINITE_VALUE;

            // ��queWork�е�����װ��m_pWeight��m_pParent
            tmpElement = queWork.DeQueue();
            if (tmpElement != null)
            {
               for (int i = 0; i < m_nValueKind; i++)
               {
                  eWeight = tmpElement.eWeight;
                  m_pWeight[nCurNode - 1][i] = eWeight;
                  do
                  {
                     m_pParent[nCurNode - 1][i].EnQueue(new QueueElement(tmpElement.nParent, tmpElement.nIndex, 0));
                     tmpElement = queWork.DeQueue();
                     if (tmpElement == null)
                        goto nextnode;

                  } while (tmpElement.eWeight == eWeight);
               }
            }
         nextnode: ;
         }
      }

      //====================================================================
      // �����е���ǰ��㣨nCurNode�����ܵı߸���eWeight����ѹ�����
      //====================================================================
      private static void EnQueueCurNodeEdges(ref CQueue queWork, int nCurNode)
      {
         int nPreNode;
         double eWeight;
         ChainItem<ChainContent> pEdgeList;

         queWork.Clear();
         pEdgeList = m_apCost.GetFirstElementOfCol(nCurNode);

         // Get all the edges
         while (pEdgeList != null && pEdgeList.col == nCurNode)
         {
            nPreNode = pEdgeList.row;  // ���ر�����������row��col�Ĺ�ϵ
            eWeight = pEdgeList.Content.eWeight; //Get the eWeight of edges

            for (int i = 0; i < m_nValueKind; i++)
            {
               // ��һ����㣬û��PreNode��ֱ�Ӽ������
               if (nPreNode == 0)
               {
                  queWork.EnQueue(new QueueElement(nPreNode, i, eWeight));
                  break;
               }

               // ���PreNode��Weight == Predefine.INFINITE_VALUE����û�б�Ҫ������ȥ��
               if (m_pWeight[nPreNode - 1][i] == Predefine.INFINITE_VALUE)
                  break;

               queWork.EnQueue(new QueueElement(nPreNode, i, eWeight + m_pWeight[nPreNode - 1][i]));
            }
            pEdgeList = pEdgeList.next;
         }
      }

      #endregion

      #region GetPaths Method

      //====================================================================
      // ע��index �� 0 : ��̵�·���� index = 1 �� �ζ̵�·��
      //     �������ơ�index <= this.m_nValueKind
      //====================================================================
      public static List<int[]> GetPaths(int index)
      {
         Debug.Assert(index <= m_nValueKind && index >= 0);

         Stack<PathNode> stack = new Stack<PathNode>();
         int curNode = m_nNode - 1, curIndex = index;
         QueueElement element;
         PathNode node;
         int[] aPath;
         List<int[]> result = new List<int[]>();

         element = m_pParent[curNode - 1][curIndex].GetFirst();
         while (element != null)
         {
            // ---------- ͨ��ѹջ�õ�·�� -----------
            stack.Push(new PathNode(curNode, curIndex));
            stack.Push(new PathNode(element.nParent, element.nIndex));
            curNode = element.nParent;

            while (curNode != 0)
            {
               element = m_pParent[element.nParent - 1][element.nIndex].GetFirst();
               stack.Push(new PathNode(element.nParent, element.nIndex));
               curNode = element.nParent;
            }

            // -------------- ���·�� --------------
            PathNode[] nArray = stack.ToArray();
            aPath = new int[nArray.Length];

            for (int i = 0; i < aPath.Length; i++)
               aPath[i] = nArray[i].nParent;

            result.Add(aPath);

            // -------------- ��ջ�Լ���Ƿ�������·�� --------------
            do
            {
               node = stack.Pop();
               curNode = node.nParent;
               curIndex = node.nIndex;

            } while (curNode < 1 || (stack.Count != 0 && !m_pParent[curNode - 1][curIndex].CanGetNext));

            element = m_pParent[curNode - 1][curIndex].GetNext();
         }

         return result;
      }

      #endregion

      #region GetBestPath Method

      //====================================================================
      // ��ȡΨһһ�����·������Ȼ���·�����ܲ�ֻһ��
      //====================================================================
      public static int[] GetBestPath()
      {
         Debug.Assert(m_nNode > 2);

         Stack<int> stack = new Stack<int>();
         int curNode = m_nNode - 1, curIndex = 0;
         QueueElement element;

         element = m_pParent[curNode - 1][curIndex].GetFirst();

         stack.Push(curNode);
         stack.Push(element.nParent);
         curNode = element.nParent;

         while (curNode != 0)
         {
            element = m_pParent[element.nParent - 1][element.nIndex].GetFirst();
            stack.Push(element.nParent);
            curNode = element.nParent;
         }

         return stack.ToArray();
      }

      #endregion

      #region GetNPaths Method

      //====================================================================
      // �Ӷ̵�����ȡ���� n ��·��
      //====================================================================
      public static List<int[]> GetNPaths(int n)
      {
         List<int[]> result = new List<int[]>();
         List<int[]> tmp;
         int nCopy;

         for (int i = 0; i < m_nValueKind && result.Count < Predefine.MAX_SEGMENT_NUM; i++)
         {
            tmp = GetPaths(i);

            if (n - result.Count < tmp.Count)
               nCopy = n - result.Count;
            else
               nCopy = tmp.Count;

            for (int j = 0; j < nCopy; j++)
               result.Add(tmp[j]);
         }

         return result;
      }

      #endregion

   

   }
}
