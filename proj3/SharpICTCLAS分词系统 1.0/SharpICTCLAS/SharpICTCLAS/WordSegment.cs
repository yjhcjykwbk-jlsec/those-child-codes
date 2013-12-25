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
using System.IO;

namespace SharpICTCLAS
{
   public class WordSegment
   {
      private double m_dSmoothingPara;
      private string m_pNewSentence;
      private Segment m_Seg;//Seg class
      private WordDictionary m_dictCore, m_dictBigram;//Core dictionary,bigram dictionary
      private Span m_POSTagger;//POS tagger
      private UnknowWord m_uPerson, m_uTransPerson, m_uPlace;//Person recognition

      public bool PersonRecognition = true;       //�Ƿ��������ʶ��
      public bool TransPersonRecognition = true;  //�Ƿ���з�������ʶ��
      public bool PlaceRecognition = true;        //�Ƿ���е���ʶ��
      public event SegmentEventHandler OnSegmentEvent;

      #region ���캯��

      public WordSegment() : this(0.1) { }

      public WordSegment(double SmoothingParameter)
      {
         m_dictCore = new WordDictionary();
         m_dictBigram = new WordDictionary();
         m_POSTagger = new Span();
         m_uPerson = new UnknowWord();
         m_uTransPerson = new UnknowWord();
         m_uPlace = new UnknowWord();
         m_Seg = new Segment(m_dictBigram, m_dictCore);
         m_Seg.OnSegmentEvent += new SegmentEventHandler(this.OnSegmentEventHandler);

         m_dSmoothingPara = SmoothingParameter;//Smoothing parameter
      }

      #endregion

      #region InitWordSegment Method

      public bool InitWordSegment(string pPath)
      {
         string filename;

         filename = pPath + "coreDict.dct";
         if (!m_dictCore.Load(filename)) return false;

         filename = pPath + "lexical.ctx";
         if (!m_POSTagger.LoadContext(filename)) return false;
         m_POSTagger.SetTagType();

         filename = pPath + "nr";
         if (!m_uPerson.Configure(filename, TAG_TYPE.TT_PERSON)) return false;

         filename = pPath + "ns";
         if (!m_uPlace.Configure(filename, TAG_TYPE.TT_PLACE)) return false;

         filename = pPath + "tr";
         if (!m_uTransPerson.Configure(filename, TAG_TYPE.TT_TRANS_PERSON)) return false;

         filename = pPath + "BigramDict.dct";
         if (!m_dictBigram.Load(filename)) return false;

         return true;
      }

      #endregion

      #region Segment

      public List<WordResult[]> Segment(string sentence)
      {
         return Segment(sentence, 1);
      }

      public List<WordResult[]> Segment(string sentence, int nKind)
      {
         OnBeginSegment(sentence);

         m_pNewSentence = Predefine.SENTENCE_BEGIN + sentence + Predefine.SENTENCE_END;
         int nResultCount = m_Seg.BiSegment(m_pNewSentence, m_dSmoothingPara, nKind);

         for (int i = 0; i < nResultCount; i++)
         {
            if (this.PersonRecognition)
               m_uPerson.Recognition(m_Seg.m_pWordSeg[i], m_Seg.m_graphOptimum, m_Seg.atomSegment, m_dictCore);

            if (this.TransPersonRecognition)
               m_uTransPerson.Recognition(m_Seg.m_pWordSeg[i], m_Seg.m_graphOptimum, m_Seg.atomSegment, m_dictCore);

            if (this.PlaceRecognition)
               m_uPlace.Recognition(m_Seg.m_pWordSeg[i], m_Seg.m_graphOptimum, m_Seg.atomSegment, m_dictCore);
         }
         OnPersonAndPlaceRecognition(m_Seg.m_graphOptimum);

         m_Seg.BiOptimumSegment(1, m_dSmoothingPara);

         for (int i = 0; i < m_Seg.m_pWordSeg.Count; i++)
            m_POSTagger.POSTagging(m_Seg.m_pWordSeg[i], m_dictCore, m_dictCore);

         OnFinishSegment(m_Seg.m_pWordSeg);

         return m_Seg.m_pWordSeg;
      }

      #endregion

      #region Events

      private void SendEvents(SegmentEventArgs e)
      {
         if (OnSegmentEvent != null)
            OnSegmentEvent(this, e);
      }

      private void OnBeginSegment(string sentence)
      {
         SendEvents(new SegmentEventArgs(SegmentStage.BeginSegment, sentence));
      }

      private void OnPersonAndPlaceRecognition(RowFirstDynamicArray<ChainContent> m_graphOptimum)
      {
         SendEvents(new SegmentEventArgs(SegmentStage.PersonAndPlaceRecognition, m_graphOptimum.ToString()));
      }

      private void OnFinishSegment(List<WordResult[]> m_pWordSeg)
      {
         StringBuilder sb = new StringBuilder();
         for (int k = 0; k < m_pWordSeg.Count; k++)
         {
            for (int j = 1; j < m_pWordSeg[k].Length - 1; j++)
               sb.Append(string.Format("{0} /{1} ", m_pWordSeg[k][j].sWord, Utility.GetPOSString(m_pWordSeg[k][j].nPOS)));
            sb.Append("\r\n");
         }

         SendEvents(new SegmentEventArgs(SegmentStage.FinishSegment, sb.ToString()));
      }

      private void OnSegmentEventHandler(object sender, SegmentEventArgs e)
      {
         SendEvents(e);
      }

      #endregion

   }
}
