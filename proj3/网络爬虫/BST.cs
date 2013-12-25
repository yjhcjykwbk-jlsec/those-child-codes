using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace 网络爬虫
{
    public class Node
    {
        public int index;       //节点编号
        public string value;    //节点信息

        public Node left;
        public Node right;

        public Node(Node left, Node right, int index, string value)
        {
            this.left = left;
            this.right = right;
            this.index = index;
            this.value = value;
        }

        public Node(int index, string value)
        {
            this.index = index;
            this.value = value;
            left = right = null;
        }
        public Node()
        {
            index = -1;
            value = null;
        }
        public string getValue() { return value; }
        static public bool operator <(Node temp1, Node temp2)
        {
            return (temp1.value.CompareTo(temp2.value) < 0);
        }
        static public bool operator >(Node temp1, Node temp2)
        {
            return (temp1.value.CompareTo(temp2.value)>0);
        }
    }

    public class BST : Node//方便通过网页地址反向搜索网页节点是否已经被链接
    {
        public Node root;
        public BST()
        {
            root = null;
        }
        /// <summary>
        /// 查找某一节点
        /// </summary>
        /// <param name="node">根节点</param>
        /// <param name="value">要查找的值</param>
        /// <returns></returns>
        public int findNode(Node root, Node temp)
        {
            if (root == null)
            {
                return -1;              //未检索到节点,返回编号-1
            }
            if (temp < root)
            {
                return findNode(root.left, temp);
            }
            else if (temp > root)
            {
                return findNode(root.right, temp);
            }
            else return root.index;
        }
        //检索节点
        public int searchNode(string info)
        {
            Node temp = new Node(0, info);
            return findNode(root,temp);
        }
        //插入节点
        public bool insertNode(Node temp)
        {
            int tag = 0;        //标记插在左子节点
            Node pointer = root;
            Node temppointer = null;  
            if (pointer == null) { root = temp; return true; }
            while (pointer != null)
            {
                temppointer = pointer;
                if (temp > pointer)
                {
                    pointer = pointer.right;
                    tag = 1;
                }
                else if (pointer > temp)
                {
                    pointer = pointer.left;
                    tag = 0;
                }
                else return false;        //找到相同
            }
            if (tag == 0) temppointer.left = temp;
            else temppointer.right = temp;
            
            return true;
        }
    }

}
