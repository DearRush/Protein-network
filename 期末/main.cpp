#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
#include<stdio.h>
#include"lib.h"
using namespace std;


int main()
{
	//һЩ���ڳ��������
	printf("**********PROTEIN NETWORK'S SHORTEST PATH CALCULATING PROGRAM***********\n\n"); 
	printf("                                           ----------------------BY GROUP 7\n\n");
	printf("This program is created to solve the shortest distance in the proteins network\n\n"); 
	char input = 'a';
	while (input!='q')
	{
		printf("Firstly,please enter your choice of the algorithm you want\n");           //һЩ����
		printf("d represents the Dijkstra algorithm.\n");
		printf("b represents the Bellman-Ford algorithm.\n");
		printf("f represents the Flolyd  algorithm.\n");
		printf("q represents the exit operation\n");
		scanf("%c", &input);                                                           //��ȡ�û�����
		getchar();
		if (input=='d')
		{
			int number=leading(&input);
			if (input=='1')                                       //����ʽ����
			{
				printf("Then you need to enter the distace between every two proteins:\n\n");
				printf("Be aware that if two proteins are not neighbors, then set the distace between them 99)\n\n");
				dij(number,1,NULL);
			}
			else if (input=='2')                     //�ļ�����ʽ����
			{
				printf("Please enter the name of the file:");
				char name[100];
				scanf("%s", name);
				getchar();
				dij(number, 2, name);
			}
			else                              //�û������������ַ�
			{
				printf("Enter the correct choice we want!\n\n");
			}
		}
		else if (input=='b')
		{
			Graph graph;                                  //����ͼ�ĸ�������
			int num_of_edge, source;
			printf("Enter number of vertices in graph\n");
			scanf("%d",&graph.num_of_vertice);
			getchar();
			cout << "Enter number of edges in graph\n";
			scanf("%d", &num_of_edge);
			getchar();
			graph.edges.resize(2*num_of_edge);
			cout << "Enter your source vertex number\n";
			scanf("%d", &source);
			getchar();

			for (int i = 0; i <2*num_of_edge; i++) {
				cout << "\nEnter edge " << i/2 << " properties Source, destination, weight respectively\n";
				scanf("%d",&graph.edges[i].source);
				getchar();
				scanf("%d",&graph.edges[i].destination);
				getchar();
				scanf("%d",&graph.edges[i].weight);
				i++;
				graph.edges[i].source = graph.edges[i - 1].destination;
				graph.edges[i].destination = graph.edges[i - 1].source;
				graph.edges[i].weight = graph.edges[i - 1].weight;
			}
			for (int i = 0; i < graph.num_of_vertice; i++) {
				BellmanFord(&graph, i);
			}
		}
		else if (input=='f')
		{
			int number = leading(&input);
			if (input == '1')                                       //����ʽ����
			{
				printf("Then you need to enter the distace between every two proteins:\n\n");
				printf("Be aware that if two proteins are not neighbors, then set the distace between them 99)\n\n");
				floyd(number, 1,NULL);
			}
			else if (input == '2')                     //�ļ�����ʽ����
			{
				printf("Please enter the name of the file:");
				char name[100];
				scanf("%s", name);
				getchar();
				floyd(number, 2,name);
			}
			else                              //�û������������ַ�
			{
				printf("Enter the correct choice we want!\n\n");
			}
		}
		else if (input=='q')                 //�˳�
		{
			printf("Thanks for your use!The program is about to close down.\n\n");
			break;
		}
		else                         //�û�ѡ���������Ƕ���ѡ��
		{
			printf("You did not enter the correct choice we want!Retry it again��\n\n");
		}
	}
	

}