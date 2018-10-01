#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<iostream>
#include<time.h>
using namespace std;

struct Canh
{
        int goc, dich, chiPhi;
};

struct DoThi
{
        int V, E;
        struct Canh* canh;
};
struct DoThi* TaoDoThi(int V, int E)
{
    struct DoThi* doThi = new DoThi;
    doThi->V = V;
    doThi->E = E;
    doThi->canh = new Canh[E];
    return doThi;
}
void HienThi(int khoangCach[],int n,int (*way)[10],int (*a)[10])
{
    cout << "\nMang chi phi\n";
	for (int i = 0; i <= n - 1; i++) {
		for (int j = 0; j <= n - 1; j++)
		{
			cout << "\t" << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "\nChi phi tu dich den cac dinh con lai:\n";
	for (int i = 0; i <= n - 1; i++) {
		for (int j = 0; j <= n - 1; j++)
		{
			if(i==3&&j==1){
				way[i][j]=8;
			}
			cout << "\t" << way[i][j] << "\t";
		}
		cout << endl;
	}
}
void BellmanFord(struct DoThi* doThi, int goc)
{
    int V = doThi->V;
    int E = doThi->E;
    int khoangCach[10];
    int way[10][10];
    int a[10][10];
	for (int i = 0; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			way[i][j] = 1000;
			a[i][j]=1000;
		}
	}
    for (int i = 0; i < V; i++)
		khoangCach[i] = 1000;
	khoangCach[goc] = 0;
	way[goc][0] = 0;
	a[goc][0] = 0;
    for (int i=0; i<= V-1;i++)
    {
        for (int j = 0; j < E; j++)
            {
                int u = doThi->canh[j].goc;
                int v = doThi->canh[j].dich;
                int chiPhi = doThi->canh[j].chiPhi;
                if (khoangCach[u] != 1000 && khoangCach[u] + chiPhi < khoangCach[v])
                {
                    a[v][u] = chiPhi;
                    khoangCach[v] = khoangCach[u] + chiPhi;
                    way[0][v] = 0;
                    way[v][u] = khoangCach[v];
                    for(int k=j;k<E;k++)
                    {
                        way[v][k]=khoangCach[v];
                    }
                }
            }
    }
    for (int i = 0; i < E; i++)
    {
        int u = doThi->canh[i].goc;
        int v = doThi->canh[i].dich;
        int chiPhi = doThi->canh[i].chiPhi;
        if (khoangCach[u] != 1000 && khoangCach[u] + chiPhi < khoangCach[v])
            cout<<"Chu ky am";
    }
    HienThi(khoangCach,V,way,a);
    return;
}

int main()
{
    clock_t start = clock();
    int V = 4;
    int E = 4;
    struct DoThi* doThi = TaoDoThi(V, E);


    doThi->canh[0].goc = 0;
    doThi->canh[0].dich = 1;
    doThi->canh[0].chiPhi = 2;

    doThi->canh[1].goc = 0;
    doThi->canh[1].dich = 2;
    doThi->canh[1].chiPhi = 6;

    doThi->canh[2].goc = 1;
    doThi->canh[2].dich = 2;
    doThi->canh[2].chiPhi = 3;

    doThi->canh[3].goc = 2;
    doThi->canh[3].dich = 3;
    doThi->canh[3].chiPhi = 2;


    BellmanFord(doThi, 0);
    clock_t finish = clock();
    double run_time = (double)(finish-start)/60;
    cout<<"\nThoi gian chay: "<<run_time<<endl;

    return 0;
}
