#include <iostream.h>
#include "HuffmanTree.h"

void main(){

	int weight[] = {6,2,3,4};       //Ȩֵ
	
	HuffmanTree<int> a(weight,4);    //ͼ5.19 Huffman��
	cout<< "HuffmanTree is constructed. " << endl;

	cout<< "�������Σ� " << endl;
	a.InOrder(a.GetRoot());        //��������
}