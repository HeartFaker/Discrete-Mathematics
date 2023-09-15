#include<iostream>
#include<queue>
#include<vector>
using namespace std;

const int DefaultSize = 10;
const int MAXINT = 100;
int adjacencyMat[MAXINT][MAXINT]; //�ڽӾ���
int sumVertices = 0, sumEdge = 0;  //�ܶ�����Ŀ���ܱ���

//��Ʋ��鼯����Kruskal�㷨
class UFsets {
public:
	UFsets(int s = DefaultSize);
	~UFsets() { delete[]parent; }
	//���鼯���Һ���
	int find(int x);
	//���鼯�ϲ�����
	void Union(int root1, int root2);
private:
	int* parent;
	int size;
};

/***************************************************************************
  �������ƣ�UFsets(int s) 
  ��    �ܣ����鼯��������
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�find(int x)
  ��    �ܣ����鼯���Һ���
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�Union(int root1,int root2)
  ��    �ܣ����鼯�ϲ�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void UFsets::Union(int root1,int root2)
{
	parent[root2] = root1;
}

//��С�������߽ṹ��
struct MSTedgeNode {
	int head;
	int tail;
	int weight;
};

/***************************************************************************
  �������ƣ�bool operator()(const MSTedgeNode& a, const MSTedgeNode& b)
  ��    �ܣ�STL��С�Ѹ����Ƚ��㷨
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
struct cmp {
	bool operator()(const MSTedgeNode& a, const MSTedgeNode& b)
	{
		return a.weight > b.weight;
	}
};

/***************************************************************************
  �������ƣ�Kruskal(int sumVertices)
  ��    �ܣ�Kruskal�㷨����С��
  ���������
  �� �� ֵ��
  ˵    ����
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
			cout << "��С�ķ���: " << min_heap.top().tail << " �� " << min_heap.top().head << endl;
			count++;
		}
		min_heap.pop();
	}
}

/***************************************************************************
  �������ƣ�Prim
  ��    �ܣ�Prim�㷨����С��
  ���������
  �� �� ֵ��
  ˵    ����
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
			cout << "��С�ķ���: " << nearvex[v] << " �� " << v << endl;
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
  �������ƣ�main
  ��    �ܣ�����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	int head, tail, cost;
	char ch = '0';
	cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����):";
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
				cout << "�����������ߵĽڵ�����Լ����ǵ�Ȩֵ(�Կո�ָ�������):\n";
				while (sumEdge--) //�������б����Լ����ǵ�Ȩֵ
				{
					cin >> head >> tail >> cost; //������Լ����ǵ�Ȩֵ
					adjacencyMat[head][tail] = adjacencyMat[tail][head] = cost;
				}
				cout << "��ѡ��ʹ��Kruskal�㷨��Prim�㷨������С��������(a��b)";
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
				cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����) :" << endl;
			}
			else if (sumEdge == 0 && sumVertices == 0)
				return 0;
		}
	return 0;
}