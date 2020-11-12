#include"Graph.h"

//输出选项提示
void choice()
{
	cout << "0.显示已经输入的图" << endl;
	cout << "1.以邻接矩阵的形式输入图" << endl;
	cout << "2.以邻接表的形式输入图" << endl;
	cout << "3.将邻接表的图转换为邻接矩阵的图" << endl;
	cout << "4.将邻接矩阵的图转换为邻接表的图" << endl;
	cout << "5.对图的深度优先搜索(递归)(邻接矩阵)" << endl;
	cout << "6.对图的深度优先搜索(递归)(邻接表)" << endl;
	cout << "7.对图的深度优先搜索(非递归)(邻接矩阵)" << endl;
	cout << "8.对图的深度优先搜索(非递归)(邻接表)" << endl;
	cout << "9.对图的广度优先搜索(邻接矩阵)" << endl;
	cout << "10.对图的广度优先搜索(邻接表)" << endl;
	cout << "11.以文件形式输入图(邻接矩阵)" << endl;
	cout << "12.以文件形式输入图(邻接表)" << endl;
	cout << "-1.退出" << endl;
	cout << "请输入您的选项:" << endl;
}



//输出图的构造
//以邻接矩阵储存的图
void Print_Matrix(Graph_Adjacency_Matrix* G)
{
	if (G)
	{
		cout << "邻接矩阵构成的图为:" << endl;
		for (int i = 0; i < G->n; i++)
			cout << "\t" << G->verlist[i];
		cout << endl;
		for (int i = 0; i < G->n; i++)
		{
			cout << G->verlist[i];
			for (int j = 0; j < G->n; j++)
			{
				cout << "\t" << G->edge[i][j];
			}
			cout << endl;
		}
	}
}
//以邻接表储存的图
void Print_List(AdjGraph* G)
{
	if (G)
	{
		cout << "邻接表构成的图为:" << endl;
		EdgeNode node1;
		for (int i = 0; i < G->n; i++)
		{
			cout << G->vexlist[i].vertex;
			node1 = G->vexlist[i].firstedge;
			while (node1 != nullptr)
			{
				cout << "->" << G->vexlist[node1->adjvex].vertex<<" "<<node1->cost;
				node1 = node1->next;
			}
			cout << endl;
		}
	}
}




//邻接矩阵的存储结构
//构造图
void Create_Graph_Adjacency_Matrix(Graph_Adjacency_Matrix* G)
{
	int i, j, k, w;
	cout << "请分别输入顶点个数和边数:" << endl;
	cin >> G->n >> G->e;
	cout << "请输入图的顶点信息:" << endl;
	for (i = 0; i < G->n; i++)
	{
		cin >> G->verlist[i];
	}
	for (i = 0; i < G->n; i++)
		for (j = 0; j < G->n; j++)
			G->edge[i][j] = 0;
	cout << "请输入顶点的下表i、j和权值:" << endl;
	for (k = 0; k < G->e; k++)
	{
		cin >> i >> j >> w;
		G->edge[i-1][j-1] = w;
	}
}
//邻接表的存储结构
//构造图
void Create_Graph_Adjacency_List(AdjGraph* G)
{
	int weight;
	int tail;
	int head;
	cout << "请分别输入顶点个数和边数:" << endl;
	cin >> G->n >> G->e;
	cout << "请输入顶点的信息:" << endl;
	for (int i = 0; i < G->n; i++)
	{
		//输入邻接表顶点信息
		//cout << "请输入顶点的信息:" << endl;
		cin >> G->vexlist[i].vertex;
		G->vexlist[i].firstedge = nullptr;
	}
	cout << "请输入顶点的下表i、j和权值:" << endl;
	for (int i = 0; i < G->e; i++)
	{
		//cout << "请分别输入边的信息   头结点的下标、该结点的下标、权值:" << endl;
		cin >> tail >> head >> weight;
		EdgeNode p = new node;
		p->adjvex = head - 1;
		p->cost = weight;
		p->next = G->vexlist[tail - 1].firstedge;
		G->vexlist[tail-1].firstedge = p;
		
		
	}

}




//输入邻接矩阵存储结构的图
Graph_Adjacency_Matrix* Input_Graph_Adjacency_Matrix()
{
	Graph_Adjacency_Matrix* G = new Graph_Adjacency_Matrix;
	Create_Graph_Adjacency_Matrix(G);
	return G;
}
//输入邻接矩阵存储表的图
AdjGraph* Input_Graph_Adjacency_List()
{
	AdjGraph* G = new AdjGraph;
	Create_Graph_Adjacency_List(G);
	return G;
}




//图的转换
//邻接矩阵转邻接表
AdjGraph* Transform_to_List(Graph_Adjacency_Matrix* G)
{
	AdjGraph* Graph = new AdjGraph;
	Graph->e = G->e;
	Graph->n = G->n;
	for (int i = 0; i < G->n; i++)
	{
		Graph->vexlist[i].vertex = G->verlist[i];
		Graph->vexlist[i].firstedge = nullptr;
		for (int j = 0; j < G->n; j++)
		{
			if (G->edge[i][j] != 0)
			{
				EdgeNode p = new node;
				p->cost = G->edge[i][j];
				p->adjvex = j;
				p->next = Graph->vexlist[i].firstedge;
				Graph->vexlist[i].firstedge = p;	
			}
		}
	}
	return Graph;
}
//图的转换
//邻接表转邻接矩阵
Graph_Adjacency_Matrix* Transform_to_Matrix(AdjGraph* G)
{
	Graph_Adjacency_Matrix* Graph = new Graph_Adjacency_Matrix;
	EdgeNode node1;
	VertexNode* vertexnode;
	for (int i = 0; i < G->n; i++)
	{
		Graph->verlist[i] = G->vexlist[i].vertex;
		for (int j = 0; j < G->n; j++)
			Graph->edge[i][j] = 0;
	}
	int j;
	for (int i = 0; i < G->n; i++)
	{
		node1 = G->vexlist[i].firstedge;
		while (node1 != nullptr)
		{
			Graph->edge[i][node1->adjvex] = node1->cost;
			node1 = node1->next;
		}
	}
	return Graph;
}


//搜索算法
//深度优先搜索
//递归
void DFS_Recursion_Matrix(Graph_Adjacency_Matrix* G)
{
	bool* visited = new bool[G->n];
	int* dfn = new int[G->n];
	int count = 0;
	for (int i = 0; i < G->n; i++)
		visited[i] = false;
	for (int i = 0; i < G->n; i++)
		if (!visited[i])
			DFS_Matrix(G, i, visited, dfn, count); //从顶点 i 出发的一次搜索，BFSX(G, i )
	delete[]visited;
	delete[]dfn;
}
void DFS_Matrix(Graph_Adjacency_Matrix* G, int i, bool visited[],int dfn[],int count)
{
	int j;
	cout << G->verlist[i];
	visited[i] = true; 
	dfn[i] = count; 
	count++;
	for (j = 0; j < G->n; j++)
		if ((G->edge[i][j] == 1) && !visited[j])
			DFS_Matrix(G, j, visited, dfn,count);
}
//邻接表
//递归
void DFS_Recursion_List(AdjGraph* G)
{
	bool* visited = new bool[G->n];
	int* dfn = new int[G->n];
	int count = 0;
	for (int i = 0; i < G->n; i++)
		visited[i] = false;
	for (int i = 0; i < G->n; i++)
		if (!visited[i])
			DFS_List(G, i, visited, dfn, count);
	delete[]visited;
	delete[]dfn;
}
void DFS_List(AdjGraph* G, int i, bool visited[], int dfn[], int count)
{
	EdgeNode p;
	cout << G->vexlist[i].vertex;
	visited[i] = true;
	dfn[i] = count++;
	p = G->vexlist[i].firstedge;
	while (p) 
	{
		if (!visited[p->adjvex])
			DFS_List(G, p->adjvex, visited, dfn, count);
		p = p->next;
	}
}




//从文件输入
//以邻接矩阵形式从文件输入
Graph_Adjacency_Matrix* Input_from_file_Matrix(Graph_Adjacency_Matrix* G)
{
	ifstream fin;
	fin.open("Graph_Adjacency_Matrix.txt");
	if (!fin.is_open())
	{
		cout << "文件打开失败!" << endl;
		cout << "请输入您的选项:" << endl;
		return G;
	}
	else
	{
		G = new Graph_Adjacency_Matrix;
		char ch;
		fin >> G->n >> G->e;
		for (int i = 0; i < G->n; i++)
		{
			fin >> ch;
		}
		for (int i = 0; i < G->n; i++)
		{
			fin >> G->verlist[i];
			for (int j = 0; j < G->n; j++)
				fin >> G->edge[i][j];
		}
		cout << "读入成功!" << endl;
		cout << "请输入您的选项:" << endl;
		return G;
	}
}
//以邻接表形式从文件输入
AdjGraph* Input_from_file_List(AdjGraph* G)
{
	ifstream fin;
	fin.open("Graph_Adjacency_AdjGraph.txt");
	if (!fin.is_open())
	{
		cout << "文件打开失败!" << endl;
		cout << "请输入您的选项:" << endl;
		return G;
	}
	else
	{
		int weight;
		int tail;
		int head;
		int i;
		char ch;
		AdjGraph* G = new AdjGraph;
		fin >> G->n >> G->e;
		for (i = 0; i < G->n; i++)
		{
			fin >> G->vexlist[i].vertex;
			G->vexlist[i].firstedge = nullptr;
		}
		for (i = 0; i < G->e; i++)
		{
			fin >> tail >> head >> weight;
			EdgeNode p = new node;
			p->adjvex = head - 1;
			p->cost = weight;
			p->next = G->vexlist[tail - 1].firstedge;
			G->vexlist[tail - 1].firstedge = p;
		}
		int a = 0;
		cout << "请输入您的选项:" << endl;
		return G;
	}
}


