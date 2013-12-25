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
   public sealed class Predefine
   {
      private Predefine()
      {
      }

      #region Original predefined in Utility.h file

      public const int CT_SENTENCE_BEGIN = 1;        //Sentence begin 
      public const int CT_SENTENCE_END = 4;          //Sentence ending
      public const int CT_SINGLE = 5;                //SINGLE byte
      public const int CT_DELIMITER = CT_SINGLE + 1; //delimiter
      public const int CT_CHINESE = CT_SINGLE + 2;   //Chinese Char
      public const int CT_LETTER = CT_SINGLE + 3;    //HanYu Pinyin
      public const int CT_NUM = CT_SINGLE + 4;       //HanYu Pinyin
      public const int CT_INDEX = CT_SINGLE + 5;     //HanYu Pinyin
      public const int CT_OTHER = CT_SINGLE + 12;    //Other

      public const string POSTFIX_SINGLE =
        "�Ӱ���ǳش嵥�����̵궴�ɶӷ��帮�Ը۸󹬹������źӺ������������ǽ־����ӿڿ�����¥·������Ū����������������Ȫ��ɽʡ��ˮ����̨̲̳����ͤ��������ϪϿ������������ҤӪ����԰ԷԺբկվ����ׯ�������";

      public readonly static string[] POSTFIX_MUTIPLE = {"�뵺","��ԭ","����","���","�󹫹�","����","����",
    "�۹�","�ɲ�","�ۿ�","���ٹ�·","��ԭ","��·","��԰","���͹�","�ȵ�","�㳡",
    "����","��Ͽ","��ͬ","����","����","����","�ֵ�","�ڰ�","��ͷ","ú��",
    "����","ũ��","���","ƽԭ","����","Ⱥ��","ɳĮ","ɳ��","ɽ��","ɽ��",
    "ˮ��","���","����","��·","�´�","ѩ��","�γ�","�κ�","�泡","ֱϽ��",
    "������","������","������",""};

      public const string TRANS_ENGLISH =
        "�������������������°İʰŰͰװݰ������������ȱϱ˱𲨲��������������Ųɲֲ��񳹴��Ĵȴδ����������������µõĵǵϵҵٵ۶����Ŷض����������������Ʒҷѷ�򸣸������ǸɸԸ���������ŹϹ��������������ϺӺպ����������������Ӽּ��ܽ𾩾þӾ��������������¿ƿɿ˿Ͽ����������������������������������������������������������¡¬²³·��������������������éï÷����������������ĦĪīĬķľ������������������������ŦŬŵŷ��������������Ƥƽ��������ǡǿ��������Ȫ��������������������ɣɪɭɯɳɽ������ʥʩʫʯʲʷʿ��˹˾˿��������̩̹����������͡ͼ������������������Τάκ��������������������ϣϲ������Ъл������������ҢҶ��������������ӢӺ����Լ������ղ������������׿������٤��������üν�����������Ľ����������������ɺ����ѷ��������ܽ���������������";
      public const string TRANS_RUSSIAN =
        "�������°ͱȱ˲�����Ĵ�µö��Ŷ���������Ǹ�����Ӽ�ݽ𿨿ƿɿ˿���������������������¬³������÷����ķ������ŵ������������������ɫɽ��ʲ˹����̹������ά������ϣл��ҮҶ�������������ǵٸ�����ջ������������������������������ɣɳ��̩ͼ������׿��";
      public const string TRANS_JAPANESE =
        "���°˰װٰ�������ȱ��������ʲ˲ֲ������سന�����δ����������µص�ɶ������縣�Ը߹����Źȹع���úƺͺϺӺں���󻧻Ļ漪�ͼѼӼ�������������������þƾտ����ɿ˿�����������������������������¡¹������������ľ��������������Ƭƽ����ǧǰǳ����������������Ȫ������������ɭɴɼɽ��������ʥʯʵʸ������ˮ˳˾��̩��������������βδ����������ϸ������СТ����������������������ңҰҲҶһ����������ӣ��������������ԨԪԫԭԶ����������������լ����������ֲ֦֪֮��������������׵��������ܥݶ��޹������";

      //Translation type
      public const int TT_ENGLISH = 0;
      public const int TT_RUSSIAN = 1;
      public const int TT_JAPANESE = 2;

      //Seperator type
      public const string SEPERATOR_C_SENTENCE = "������������";
      public const string SEPERATOR_C_SUB_SENTENCE = "����������������";
      public const string SEPERATOR_E_SENTENCE = "!?:;";
      public const string SEPERATOR_E_SUB_SENTENCE = ",()*'";
      //ע�ͣ�ԭ������Ϊ",()\042'"��"\042"Ϊ10����42��ASC�ַ���Ϊ*
      public const string SEPERATOR_LINK = "\n\r ��";

      //Sentence begin and ending string
      public const string SENTENCE_BEGIN = "ʼ##ʼ";
      public const string SENTENCE_END = "ĩ##ĩ";

      //Seperator between two words
      public const string WORD_SEGMENTER = "@";

      #endregion

      #region Original predefined in Dictionary.h file

      public const int CC_NUM = 6768;

      //The number of Chinese Char,including 5 empty position between 3756-3761
      public const int WORD_MAXLENGTH = 100;
      public const int WT_DELIMITER = 0;
      public const int WT_CHINESE = 1;
      public const int WT_OTHER = 2;

      #endregion

      #region Original predefined in Segment.h file

      public const int MAX_WORDS = 650;
      public const int MAX_SEGMENT_NUM = 10;

      #endregion

      #region Original predefined in SegGraph.h file

      public const int MAX_FREQUENCE = 2079997;   //7528283+329805  //1993123+86874 
      public const int MAX_SENTENCE_LEN = 2000;

      #endregion

      #region Original predefined in DynamicArray.h file

      //if MIN_PROBLEM==1 then INFINITE_VALUE 10000.00  //The shortest path
      //else INFINITE_VALUE 0.00  //infinite value
      public const int MIN_PROBLEM = 1;
      public const double INFINITE_VALUE = 10000.00;

      #endregion

      #region Original predefined in CSpan.h file

      public const int MAX_WORDS_PER_SENTENCE = 120;
      public const int MAX_UNKNOWN_PER_SENTENCE = 200;
      public const int MAX_POS_PER_WORD = 20;
      public const int LITTLE_FREQUENCY = 6;

      #endregion

   }
}