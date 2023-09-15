#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void output(int mat[][100]);   //打印关系矩阵
void zifan(int mat[][100]);    //求关系矩阵自反
void duichen(int mat[][100]);  //求关系矩阵对称
void chuandi(int mat[][100]);  //求关系矩阵传递
void trans(int mat[][100]);    //求关系矩阵转置

//常变量定义矩阵最大行列数
const int mcol = 100;
const int mrow = 100;

int N = 0;  //关系矩阵行列
int mat[mcol][mrow];   // 定义关系矩阵
char ch = '0';         //定义选项变量

/***************************************************************************
  函数名称：main()
  功    能：主函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	

	cout << "请输入矩阵的行列数:";
	cin >> N;
	cout << "请输入关系矩阵:" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << endl;
		cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔) :";
		for (int j = 0; j < N; j++)
			cin >> mat[i][j];
	}
	while (1) {
		cout << "输入对应序号选择算法\nl:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出\n";
		cin >> ch;
		//输入错误处理
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else {
			break;
		}
	}

	//选择功能
	switch (ch)
	{
		case '1':
			zifan(mat);
			break;
		case '2':
			chuandi(mat);
			break;
		case '3':
			duichen(mat);
			break;
		case '4':
			exit(0);
			break;
		default:
			break;
	}
	return 0;
}

/***************************************************************************
  函数名称：output(int s[][mrow])
  功    能：打印关系矩阵
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void output(int s[][mrow])
{
	cout << "所求关系矩阵为:\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << s[i][j];
		cout << endl;
	}
}

/***************************************************************************
  函数名称：zifan(int s[][mrow])
  功    能：求自反矩阵
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zifan(int s[][mrow])
{
	//将主对角线元素置为1
	for (int i = 0; i < N; i++)
		s[i][i] = 1;
	output(s);
}

/***************************************************************************
  函数名称：trans(int s[][mrow])
  功    能：求转置矩阵
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void trans(int s[][mrow])
{
	//定义二维数组存储新矩阵
	int transMat[mcol][mrow];
	//所有元素行列互换
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			transMat[i][j] = s[j][i];
		}
	}
	//将原矩阵改变
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			s[i][j] = transMat[i][j];
		}
	}
}

/***************************************************************************
  函数名称：duichen(int s2[][mrow])
  功    能：求对称矩阵
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void duichen(int s2[][mrow])
{
	//复制原矩阵作为转置矩阵载体
	int s1[mcol][mrow];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			s1[i][j] = s2[i][j];
		}
	//求转置矩阵
	trans(s1);
	//原矩阵与转置矩阵逻辑加
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			s2[i][j] = s2[i][j] + s1[i][j];
			if (s2[i][j] > 1)
				s2[i][j] = 1;
		}
	output(s2);
}

/***************************************************************************
  函数名称：chuandi(int s2[][mrow])
  功    能：求传递矩阵
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void chuandi(int s2[][mrow])
{
	int m[100][100], a[100][100];
	int t[100][100];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			a[i][j] = 0;
			t[i][j] = s2[i][j];
			m[i][j] = s2[i][j];
		}
	for (int h = 0; h < N; h++)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (m[i][j] == 1)
				{
					for (int k = 0; k < N; k++)
						if (s2[j][k] == 1)
							a[i][k] = 1;
				}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				m[i][j] = a[i][j];
				t[i][j] += a[i][j];
				a[i][j] = 0;
				if (t[i][j] > 1)
					t[i][j] = 1;
			}
	}
	output(t);
}
