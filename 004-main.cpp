#include<iostream>
#include<queue>
#include<vector>
using namespace std;

const int DefaultSize = 10;
const int MAXINT = 100;
int adjacencyMat[MAXINT][MAXINT]; //邻接矩阵
int sumVertices = 0, sumEdge = 0;  //总顶点数目和总边数

//设计并查集辅助Kruskal算法
class UFsets {
public:
	UFsets(int s = DefaultSize);
	~UFsets() { delete[]parent; }
	//并查集查找函数
	int find(int x);
	//并查集合并函数
	void Union(int root1, int root2);
private:
	int* parent;
	int size;
};

/***************************************************************************
  函数名称：UFsets(int s) 
  功    能：并查集析构函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
UFsets::UFsets(int s) 
{
	size = s;
	parent = new int[size + 1];
	for (int i = 0; i < size; i++) {
		parent[i] = -1;
	}
}

/***************************************************************************
  函数名称：find(int x)
  功    能：并查集查找函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int UFsets::find(int x)
{
	if (parent[x] <= 0) {
		return x;
	}
	else
		return find(parent[x]);
}

/***************************************************************************
  函数名称：Union(int root1,int root2)
  功    能：并查集合并函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void UFsets::Union(int root1,int root2)
{
	parent[root2] = root1;
}

//最小生成树边结构体
struct MSTedgeNode {
	int head;
	int tail;
	int weight;
};

/***************************************************************************
  函数名称：bool operator()(const MSTedgeNode& a, const MSTedgeNode& b)
  功    能：STL最小堆辅助比较算法
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
struct cmp {
	bool operator()(const MSTedgeNode& a, const MSTedgeNode& b)
	{
		return a.weight > b.weight;
	}
};

/***************************************************************************
  函数名称：Kruskal(int sumVertices)
  功    能：Kruskal算法求最小堆
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void Kruskal(int sumVertices)
{
	MSTedgeNode e;
	priority_queue<MSTedgeNode, vector<MSTedgeNode>, cmp> min_heap;
	UFsets F(sumVertices);
	for(int u=1 ; u<= sumVertices;u++)
		for (int v = u + 1; v <= sumVertices; v++) {
			if (adjacencyMat[u][v] != INT_MAX) {
				e.tail = u;
				e.head = v;
				e.weight = adjacencyMat[u][v];
				min_heap.push(e);
			}
		}
	int count = 1;
	while (count < sumVertices&&!min_heap.empty()) {
		int u = F.find(min_heap.top().tail);
		int v = F.find(min_heap.top().head);
		if (u != v) {
			F.Union(u, v);
			cout << "最小耗费是: " << min_heap.top().tail << " 和 " << min_heap.top().head << endl;
			count++;
		}
		min_heap.pop();
	}
}

/***************************************************************************
  函数名称：Prim
  功    能：Prim算法求最小堆
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void Prim()
{
	int* lowcost = new int[sumVertices + 1];
	int* nearvex = new int[sumVertices + 1];
	for (int i = 1; i <= sumVertices; i++) {
		lowcost[i] = adjacencyMat[1][i];
		nearvex[i] = 1;
	}
	nearvex[1] = 0;
	for (int i = 2; i <= sumVertices; i++) {
		int min = INT_MAX;
		int v = 1;
		for (int j = 1; j <= sumVertices; j++) {
			if (nearvex[j] != 0 && lowcost[j] < min) {
				v = j;
				min = lowcost[j];
			}
		}
		if (v) {
			cout << "最小耗费是: " << nearvex[v] << " 和 " << v << endl;
			nearvex[v] = 0;
			for (int j = 1; j <= sumVertices; j++) {
				if (nearvex[j] != 0 && adjacencyMat[v][j] < lowcost[j]) {
					lowcost[j] = adjacencyMat[v][j];
					nearvex[j] = v;
				}
			}
		}
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
	int head, tail, cost;
	char ch = '0';
	cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):";
		while (1)
		{
			cin >> sumVertices >> sumEdge;
			if (sumVertices != 0 && sumEdge != 0)
			{
				for (int i = 1; i < sumVertices; i++)
				{
					for (int j = 1; j < sumVertices; j++)
						adjacencyMat[i][j] = INT_MAX;
				}
				cout << "请输入两条边的节点序号以及它们的权值(以空格分隔各个数):\n";
				while (sumEdge--) //输入所有边数以及它们的权值
				{
					cin >> head >> tail >> cost; //输入边以及它们的权值
					adjacencyMat[head][tail] = adjacencyMat[tail][head] = cost;
				}
				cout << "请选择使用Kruskal算法或Prim算法构造最小生成树：(a或b)";
				cin >> ch;
				switch (ch)
				{
					case 'a':
						Kruskal(sumVertices);
						break;
					case 'b':
						Prim();
						break;
					default:
						break;
				}
				cout << endl;
				cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束) :" << endl;
			}
			else if (sumEdge == 0 && sumVertices == 0)
				return 0;
		}
	return 0;
}