#define _CRT_SECURE_NO_WARNINGS
#include "lib.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

int leading(char *input)
{
	printf("At the beginning,you need to enter the number of proteins in this network:");
	int number;
	scanf("%d", &number);                               //�û����뵰���ʸ���
	getchar();
	if (number <= 0)                               //�����˸���
	{
		printf("please enter a positive integer!\n");
		exit(-1);
	}
	printf("Now choose the way of data entering:\n");
	printf("1 means you want to enter the data by hand;");
	printf("2 means you want to enter the path of the file.\n");
	scanf("%c", input);                                 //�û�ѡ�������ݵ����뷽ʽ
	getchar();

	return number;
}
void dij(int number,int mode,char *name)                 //Dijkstra algorithm
{
	if (mode==1)                                //���ڽ���ʽ����
	{
		int** array = new int* [number];
		int** neighbor = new int* [number];
		for (int i = 0; i < number; i++)
		{
			array[i] = new int[number];    //�����·������ÿһ��Ԫ��a[i][j]�����˵���i��j֮������·��
		}
		for (int i = 0; i < number; i++)
		{
			neighbor[i] = new int[number];
		}                                                     //�ھӾ���չ����ÿ�����׵��ھ���˭
		for (int i = 0; i < number; i++)
		{
			for (int a = 0; a < number; a++)
			{
				neighbor[i][a] = 0;                    //�ھӾ�������ȫ����ʼ��Ϊ0
			}
		}
		for (int i = 0; i < number; i++)              //�������·�����飬���г�ʼ��
		{                                      //����Ԫ��array[i][a]ָ��ǰ������i��������a�Ĺ�����̾���
			for (int a = i; a < number; a++)
			{
				if (i == a)
				{
					array[i][a] = 0;
					a++;
					if (a >= number)
					{
						break;
					}
				}
				printf("Please enter the distance between protein %d and protein %d:", i, a);
				scanf("%d", &array[i][a]); 
				getchar();                                    //�û���������
				array[a][i] = array[i][a];
				if (array[i][a] > 99 || array[i][a] <= 0)             //��������Ч����
				{
					printf("Wrong number!Try it again!\n");
					a--;
				}
				else if (array[i][a] < 99)                       //���������ݣ���˵���������ھ�
				{                                                //(�����������Ϊ99��˵�����߲����ھ�)
					neighbor[i][a] = neighbor[a][i] = 1;
				}
			}
		}
		int* ifwork = new int[number];                             //�����������ȷ���Ƿ��Ѿ����ĳ��Ԫ�صļ���
		for (int i = 0; i < number; i++)                          //��ʼ����������Ѿ�����˼���
		{
			if (i == 0)
			{
				ifwork[i] = 1;
			}
			else
			{
				ifwork[i] = 0;
			}
		}
		int sum = 0;                  //���ڼ���array[i][j]ͬʱ���������ǰ��ֵ
		int min = 100;               //������array[i][a]��aΪi�����ھӣ�����Сֵ
		int sequence = 0;            //���ڼ�ס����Ԫ�ص���ţ�������Ÿ��£�
		int sourcepoint = 0;         //���ڼ�ס��ǰ�Ľڵ�Ԫ�ص����
		int looptime = 0;             //���ڶ�ѭ������
		for (int i = 0; i < number; i++)
		{
			while (looptime <= 6)
			{
				for (int a = 0; a < number; a++)
				{
					if (neighbor[sourcepoint][a] == 1)  //������ھ�
					{
						if (sum + array[sourcepoint][a] <= array[i][a])//ͬʱ���������·��
						{
							array[i][a] = sum + array[sourcepoint][a];
						}
					}
				}
				for (int a = 0; a < number; a++)
				{
					if (min >= array[i][a] && ifwork[a] == 0)
					{
						min = array[i][a];
						sequence = a;
					}
				}
				ifwork[sequence] = 1;
				sum = array[i][sequence];    //����ɽڵ㵽ԭ�����̾���
				sourcepoint = sequence;    //�����½ڵ���л�
				min = 100;
				looptime++;
			}
			looptime = 0;           //�˴���������ֵ
			min = 100;
			sum = 0;
			sourcepoint = i + 1;
			sequence = i + 1;
			for (int a = 0; a < number; a++)
			{
				if (a == i + 1)
				{
					ifwork[a] = 1;
				}
				else
				{
					ifwork[a] = 0;
				}
			}
		} 
		printf("THE answer is :\n\n");        //���
		for (int i = 0; i < number; i++)
		{
			for (int a = 0; a < number; a++)
			{
				printf("The shortest distance between protein %d and protein %d is %d \n", i, a, array[i][a]);
			}
			printf("\n");
		}
	}
	else if (mode == 2)     //�ļ�����ʽ�������ļ���ʽ��Ϊn*n�ľ���
	{
		FILE* b = fopen(name, "r");
		int** array = new int* [number];
		int** neighbor = new int* [number];
		for (int i = 0; i < number; i++)
		{
			array[i] = new int[number];    //�����·������ÿһ��Ԫ��a[i][j]�����˵���i��j֮������·��
		}
		for (int i = 0; i < number; i++)
		{
			neighbor[i] = new int[number];
		}                                                     //�ھӾ���չ����ÿ�����׵��ھ���˭
		for (int i = 0; i < number; i++)
		{
			for (int a = 0; a < number; a++)
			{
				neighbor[i][a] = 0;                    //�ھӾ�������ȫ����ʼ��Ϊ0
			}
		}
		int line = 0;
		int row = 0;
		int temp = 0;
		char** matrix = new char* [number * number+1];   //��ָ̬������Ĵ���
		char string[99];
		while (fgets(string, 99, b))   //���϶�ȡ�ļ���ÿһ�У�ͬʱ�����ַ����Ĳ��
		{
			matrix[temp] = strtok(string, " ");
			array[line][row] = atoi(matrix[temp]);   //��ת��Ϊ���֣����浽�����У����о����ʼ��
			row++;
			temp++;
			while (matrix[temp] = strtok(NULL, " "))
			{
				array[line][row] = atoi(matrix[temp]);
				temp++;
				row++;
			}
			line++;
			row = 0;
		}
		fseek(b, 0, 0);
		fclose(b);
		for (int i = 0; i < number; i++)
		{
			for (int a = 0; a < number; a++)
			{
				if (array[i][a] < 99 && array[i][a]>0)   //�������·����������ھӾ������Ϣ
				{
					neighbor[i][a] = 1;
					neighbor[a][i] = 1;
				}
			}
		}
		int* ifwork = new int[number];                             //�����������ȷ���Ƿ��Ѿ����ĳ��Ԫ�صļ���
		for (int i = 0; i < number; i++)                          //��ʼ����������Ѿ�����˼���
		{
			if (i == 0)
			{
				ifwork[i] = 1;
			}
			else
			{
				ifwork[i] = 0;
			}
		}
		int sum = 0;           //֮��Ĳ�����������ͬ
		int min = 100;
		int sequence = 0;
		int sourcepoint = 0;
		int where = -1;
		int looptime = 0;
		for (int i = 0; i < number; i++)
		{
			while (looptime <= 6)
			{
				for (int a = 0; a < number; a++)
				{
					if (neighbor[sourcepoint][a] == 1)  //������ھ�
					{
						if (sum + array[sourcepoint][a] <= array[i][a])
						{
							array[i][a] = sum + array[sourcepoint][a];
						}
					}
				}
				for (int a = 0; a < number; a++)
				{
					if (min >= array[i][a] && ifwork[a] == 0)
					{
						min = array[i][a];
						sequence = a;
					}
				}
				ifwork[sequence] = 1;
				sum = array[i][sequence];
				sourcepoint = sequence;
				min = 100;
				looptime++;
			}
			looptime = 0;
			min = 100;
			sum = 0;
			sourcepoint = i + 1;
			sequence = i + 1;
			for (int a = 0; a < number; a++)
			{
				if (a == i + 1)
				{
					ifwork[a] = 1;
				}
				else
				{
					ifwork[a] = 0;
				}
			}
		}
		printf("THE answer is :\n\n");
		for (int i = 0; i < number; i++)
		{
			for (int a = 0; a < number; a++)
			{
				printf("The shortest distance between protein %d and protein %d is %d \n", i, a, array[i][a]);
			}
			printf("\n");
		}
	}
}
void floyd(int number,int mode,char *name)
{
	if (mode==1)
	{
		int** array = new int* [number];   //�����ʼ������
		for (int i = 0; i < number; i++)
		{
			array[i] = new int[number];
		}
		for (int i = 0; i < number; i++)              //�������·�����飬���г�ʼ��
		{                                      //����Ԫ��array[i][a]ָ��ǰ������i��������a�Ĺ�����̾���
			for (int a = i; a < number; a++)
			{
				if (i == a)
				{
					array[i][a] = 0;
					a++;
					if (a >= number)
					{
						break;
					}
				}
				printf("Please enter the distance between protein %d and protein %d:", i, a);
				scanf("%d", &array[i][a]);
				getchar();                                    //�û���������
				array[a][i] = array[i][a];
				if (array[i][a] > 99 || array[i][a] <= 0)             //��������Ч����
				{
					printf("Wrong number!Try it again!\n");
					a--;
				}
			}
		}
		for (int i = 0; i < number; i++)
		{
			for (int j = 0; j < number; j++)
			{
				for (int k = 0; k < number; k++)
				{
					if (array[i][j]>=array[i][k]+array[k][j]&&i!=j)
					{
						array[i][j] = array[i][k] + array[k][j];
					}
				}
			}
		}
		printf("THE answer is :\n\n");
		for (int i = 0; i < number; i++)
		{
			for (int a = 0; a < number; a++)
			{
				printf("The shortest distance between protein %d and protein %d is %d \n", i, a, array[i][a]);
			}
			printf("\n");
		}
	}
	else if (mode==2)
	{
		FILE* b = fopen(name, "r");
		int** array = new int* [number];
		int** neighbor = new int* [number];
		for (int i = 0; i < number; i++)
		{
			array[i] = new int[number];    //�����·������ÿһ��Ԫ��a[i][j]�����˵���i��j֮������·��
		}
		int line = 0;
		int row = 0;
		int temp = 0;
		char** matrix = new char* [number * number + 1];   //��ָ̬������Ĵ���
		char string[99];
		while (fgets(string, 99, b))   //���϶�ȡ�ļ���ÿһ�У�ͬʱ�����ַ����Ĳ��
		{
			matrix[temp] = strtok(string, " ");
			array[line][row] = atoi(matrix[temp]);   //��ת��Ϊ���֣����浽�����У����о����ʼ��
			row++;
			temp++;
			while (matrix[temp] = strtok(NULL, " "))
			{
				array[line][row] = atoi(matrix[temp]);
				temp++;
				row++;
			}
			line++;
			row = 0;
		}
		fseek(b, 0, 0);
		fclose(b);
		for (int i = 0; i < number; i++)
		{
			for (int j = 0; j < number; j++)
			{
				for (int k = 0; k < number; k++)
				{
					if (array[i][j] >= array[i][k] + array[k][j] && i != j)
					{
						array[i][j] = array[i][k] + array[k][j];
					}
				}
			}
		}
		printf("THE answer is :\n\n");
		for (int i = 0; i < number; i++)
		{
			for (int a = 0; a < number; a++)
			{
				printf("The shortest distance between protein %d and protein %d is %d \n", i, a, array[i][a]);
			}
			printf("\n");
		}
	}
}
void BellmanFord(Graph* graph, int source)
{
	int V = graph->num_of_vertice, E = graph->edges.size();
	int* array = new int[V];
	for (int i = 0; i < V; i++)
	{
		if (i==source)
		{
			array[i] = 0;
		}
		else
		{
			array[i] = -1;
		}
	}
	for (int i = 0; i < E; i++)
	{
		if (graph->edges[i].source==source)
		{
			array[graph->edges[i].destination] = graph->edges[i].weight;
		}
		else if (graph->edges[i].destination == source)
		{
			array[graph->edges[i].source] = graph->edges[i].weight;
		}
	}
	for (int i = 0; i < V; i++)
	{
		if (array[i]==-1)
		{
			array[i] = 10000;
		}
	}
	vector<int> StoreDistance(array,array+V);
	StoreDistance[source] = 0;

	//step2 �ɳ�
	for (int i = 0; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edges[j].source;
			int v = graph->edges[j].destination;
			int weight = graph->edges[j].weight;

			if (StoreDistance[u] + weight <StoreDistance[v])
				StoreDistance[v] = StoreDistance[u] + weight;
		}
	}

	//step3 ��鸺Ȩ��
	for (int i = 0; i < E; i++) {
		int u = graph->edges[i].source;
		int v = graph->edges[i].destination;
		int weight = graph->edges[i].weight;

		if (StoreDistance[u] + weight < StoreDistance[v])
			std::cout << "\nThis graph contains negative edge cycle\n";
	}

	printf("\nVertex\t\tDistance from Source %d \n",source);    //�������
	for (int i = 0; i < V; ++i) {
		printf(" %d \t\t %d \n", i, StoreDistance[i]);
	}
}
