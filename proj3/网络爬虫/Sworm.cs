
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace 网络爬虫
{
    
    //包含links信息列表和bst(反向搜索是否存在节点)
    public class sworm
    {
        public List<string> gralist; //存储节点信息,下面节点下标即gralist下标
            //二叉搜索树,方便反向查找节点编号
        public int numLinks;
        public sworm()
        {
            gralist = new List<string>();
            bstlist = new BST();
            numLinks = 0;
        }

        //添加节点
        public void setVertex(string info)
        {
            numLinks++;
            bstlist.insertNode(new Node(numLinks - 1, info));
            gralist.Add(info); 					//增加新定点
        }

        //查询节点索引
        public int searchVertex(string Info)
        {
            return bstlist.searchNode(Info);
        }

    };



};







