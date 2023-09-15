#include<iostream>
using namespace std;

const int N = 20;
char prefixCode[2 * N];

class huffmanTree;

//���������ṹ��
struct treeNode
{

	friend class huffmanTree;

private:
	//�������
	int data;

	//������Һ���
	treeNode* lchild;
	treeNode* rchild;

};

//��������������
class huffmanTree
{
	
private:

	//�ڵ�����
	int sumNode;

	//�������
	int weights[N];

	//��������
	treeNode* fp[N];

	//�����㷨
	void sort(int n);

public:

	//�û�������
	void get_weights();

	//�û������ܽڵ���
	void get_sumNode();

	//��ʼ���������������
	void init();

	//���ɻ�������
	treeNode* HuffmanTree();

	//ǰ���������������ӡǰ׺��
	void preorder(treeNode* p, int k, char c);

};

/***************************************************************************
  �������ƣ�get_weights()
  ��    �ܣ��û�����Ȩֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void huffmanTree::get_weights()
{
	cout << "������ڵ�(�Կո�ָ�):";
	for (int i = 0; i < sumNode; i++)
	{
		cin >> weights[i];
	}
}

/***************************************************************************
  �������ƣ�get_sumNode()
  ��    �ܣ��û�����ڵ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void huffmanTree::get_sumNode()
{
	cout << "������ڵ����(������������):";
	while (true)
	{
		cin >> sumNode;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(2104, '\n');
			continue;
		}
		else {
			break;
		}
	}
	
}

/***************************************************************************
  �������ƣ�sort(int n)
  ��    �ܣ�����������ʵ�ֻ�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void huffmanTree::sort(int n)
{
	int i;
	treeNode* temp;
	for (i = sumNode - n; i < sumNode - 1; i++)
		if (fp[i]->data > fp[i + 1]->data)
		{
			temp = fp[i + 1];
			fp[i + 1] = fp[i];
			fp[i] = temp;
		}
}

/***************************************************************************
  �������ƣ�init
  ��    �ܣ���ʼ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void huffmanTree::init()
{
	treeNode* pt;

	//�����нڵ���������Ϊ�յĶ���������
	for (int i = 0; i < sumNode; i++)
	{
		pt = new treeNode; //����Ҷ�ӽ��
		pt->data = weights[i];
		pt->lchild = NULL;
		pt->rchild = NULL;
		fp[i] = pt;
	}
}

/***************************************************************************
  �������ƣ�HuffmanTree()
  ��    �ܣ����ɻ�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
treeNode* huffmanTree::HuffmanTree()
{
	treeNode* pt;
	for (int i = 1; i < sumNode; i++)
	{
		pt = new treeNode; 
		//���������½ڵ㶨��Ϊ����С�ڵ�֮�ͣ����ڵ���Ϊ�½ڵ���������
		pt->data = fp[i - 1]->data + fp[i]->data;
		pt->lchild = fp[i - 1];
		pt->rchild = fp[i];
		fp[i] = pt; 

		//���µõ��������Ͻ�������
		sort(sumNode - i);
	}
	return fp[sumNode - 1];
}

/***************************************************************************
  �������ƣ�preorder(treeNode* p, int k, char c)
  ��    �ܣ�ǰ�������ӡǰ׺��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void huffmanTree::preorder(treeNode* p, int k, char c)
{
	int j;
	if (p != NULL)
	{
		//�����涨Ϊ0�����Ҳ�涨Ϊ1
		if (c == '1')
			prefixCode[k] = '0';
		else prefixCode[k] = '1';

		if (p->lchild == NULL)
		{ //P ָ��Ҷ��
			cout << p->data << ": ";
			for (j = 1; j <= k; j++)
				cout << prefixCode[j];
			cout << endl;
		}
		//�ݹ������������������
		preorder(p->lchild, k + 1, '1');
		preorder(p->rchild, k + 1, 'r');
	}
}

/***************************************************************************
  �������ƣ�main
  ��    �ܣ�����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	huffmanTree T;    //���������������
	T.get_sumNode();  // ����ڵ�����
	T.get_weights();  //����ڵ�����
	treeNode* head;
	T.init(); //��ʼ�����
	head = T.HuffmanTree(); //���ɻ�������
	prefixCode[0] = 0;
	T.preorder(head, 0, '1'); //ǰ�������
	return 0;
}