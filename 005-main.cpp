#include<iostream>
using namespace std;

const int N = 20;
char prefixCode[2 * N];

class huffmanTree;

//定义树结点结构体
struct treeNode
{

	friend class huffmanTree;

private:
	//结点内容
	int data;

	//结点左右孩子
	treeNode* lchild;
	treeNode* rchild;

};

//建立霍夫曼树类
class huffmanTree
{
	
private:

	//节点总数
	int sumNode;

	//结点内容
	int weights[N];

	//霍夫曼树
	treeNode* fp[N];

	//排序算法
	void sort(int n);

public:

	//用户输入结点
	void get_weights();

	//用户输入总节点数
	void get_sumNode();

	//初始化霍夫曼树各结点
	void init();

	//生成霍夫曼树
	treeNode* HuffmanTree();

	//前序遍历霍夫曼树打印前缀码
	void preorder(treeNode* p, int k, char c);

};

/***************************************************************************
  函数名称：get_weights()
  功    能：用户输入权值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void huffmanTree::get_weights()
{
	cout << "请输入节点(以空格分隔):";
	for (int i = 0; i < sumNode; i++)
	{
		cin >> weights[i];
	}
}

/***************************************************************************
  函数名称：get_sumNode()
  功    能：用户输入节点数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void huffmanTree::get_sumNode()
{
	cout << "请输入节点个数(必须是正整数):";
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
  函数名称：sort(int n)
  功    能：排序函数辅助实现霍夫曼树
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：init
  功    能：初始化函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void huffmanTree::init()
{
	treeNode* pt;

	//将所有节点生成子树为空的二叉树集合
	for (int i = 0; i < sumNode; i++)
	{
		pt = new treeNode; //生成叶子结点
		pt->data = weights[i];
		pt->lchild = NULL;
		pt->rchild = NULL;
		fp[i] = pt;
	}
}

/***************************************************************************
  函数名称：HuffmanTree()
  功    能：生成霍夫曼树
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
treeNode* huffmanTree::HuffmanTree()
{
	treeNode* pt;
	for (int i = 1; i < sumNode; i++)
	{
		pt = new treeNode; 
		//霍夫曼树新节点定义为两最小节点之和，两节点作为新节点左右子树
		pt->data = fp[i - 1]->data + fp[i]->data;
		pt->lchild = fp[i - 1];
		pt->rchild = fp[i];
		fp[i] = pt; 

		//对新得到的树集合进行排序
		sort(sumNode - i);
	}
	return fp[sumNode - 1];
}

/***************************************************************************
  函数名称：preorder(treeNode* p, int k, char c)
  功    能：前序遍历打印前缀码
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void huffmanTree::preorder(treeNode* p, int k, char c)
{
	int j;
	if (p != NULL)
	{
		//向左侧规定为0，向右侧规定为1
		if (c == '1')
			prefixCode[k] = '0';
		else prefixCode[k] = '1';

		if (p->lchild == NULL)
		{ //P 指向叶子
			cout << p->data << ": ";
			for (j = 1; j <= k; j++)
				cout << prefixCode[j];
			cout << endl;
		}
		//递归遍历左子树和右子树
		preorder(p->lchild, k + 1, '1');
		preorder(p->rchild, k + 1, 'r');
	}
}

/***************************************************************************
  函数名称：main
  功    能：程序主函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	huffmanTree T;    //定义霍夫曼树变量
	T.get_sumNode();  // 输入节点总数
	T.get_weights();  //输入节点内容
	treeNode* head;
	T.init(); //初始化结点
	head = T.HuffmanTree(); //生成霍夫曼树
	prefixCode[0] = 0;
	T.preorder(head, 0, '1'); //前序遍历树
	return 0;
}