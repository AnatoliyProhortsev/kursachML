#pragma comment(lib, "libbdd.a")
#include "bdd.h"
#include <fstream>

using namespace std;

#define N_VAR 144
#define N 9			
#define M 4			
#define LOG_N 4

ofstream out;

void fun(char* varset, int size);

int main(void)
{
	bdd_init(10000, 1000);
	bdd_setvarnum(N_VAR);
	
	bdd p[M][N][N];

	unsigned I = 0;
	for (unsigned i = 0; i < N; i++)
	{
		for (unsigned j = 0; j < N; j++)
		{
			for(unsigned m = 0; m < M; m++)
			{
				p[m][i][j] = bddtrue;
				for (unsigned k = 0; k < LOG_N; k++) p[m][i][j] &= ((j >> k) & 1) ? bdd_ithvar(I + m*LOG_N + k) : bdd_nithvar(I + m*LOG_N + k) ;
			}
		}
		I += LOG_N*M;
	}

	bdd task = bddtrue;
	//1
	task &= p[0][2][7];
	task &= p[2][4][8];
	task &= p[0][5][4];
	task &= p[3][5][0];
	task &= p[1][8][8];
	task &= p[1][4][1];
	task &= p[2][5][1];

	//1-доп
	task &= p[3][4][5];
	task &= p[0][7][1];
	task &= p[2][3][3];
	task &= p[2][7][7];

	//2
	for(unsigned i = 0; i < N; i++)
		task &= !(p[1][i][6] ^ p[2][i][3]) ;

	for(unsigned i = 0; i < N; i++)
		task &= !(p[3][i][7] ^ p[1][i][6]) ;

	for(unsigned i = 0; i < N; i++)
		task &= !(p[3][i][6] ^ p[1][i][3]) ;

	for(unsigned i = 0; i < N; i++)
		task &= !(p[2][i][3] ^ p[1][i][6]) ;

	for(unsigned i = 0; i < N; i++)
		task &= !(p[3][i][8] ^ p[0][i][2]) ;

	//2-доп
	for(unsigned i = 0; i < N; i++)
		task &= !(p[0][i][3] ^ p[3][i][2]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[0][i][5] ^ p[1][i][8]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[2][i][2] ^ p[1][i][2]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[3][i][5] ^ p[0][i][0]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[2][i][1] ^ p[0][i][4]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[2][i][7] ^ p[3][i][3]) ;


	//3
	for(unsigned i = 0; i < N; i++)
	{
		if(i != 2 && i != 5 && i != 8)
			task &= !(p[1][i][3] ^ p[2][i+1][6]) ;
		else
			task &= !(p[1][i][3]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[3][i][5] ^ p[2][i+2][0]) ;
		else
			task &= !(p[3][i][5]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[3][i][8] ^ p[3][i+2][7]) ;
		else
			task &= !(p[3][i][8]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[2][i][4] ^ p[3][i+2][5]) ;
		else
			task &= !(p[2][i][4]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[3][i][1] ^ p[3][i+2][8]) ;
		else
			task &= !(p[3][i][1]);
	}

	//3-Доп
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[0][i][5] ^ p[1][i+2][5]) ;
		else
			task &= !(p[0][i][5]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[0][i][4] ^ p[3][i+2][6]) ;
		else
			task &= !(p[0][i][4]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[2][i][4] ^ p[2][i+2][8]) ;
		else
			task &= !(p[2][i][4]);
	}

	//4
	// for(unsigned i = 0; i < N; i++)
	// {
	// 	if(i != 2 && i != 5 && i != 8)
	// 		task &= !(p[2][i][1] ^ p[0][i+1][8]) ;
	// 	else if(i == 1 || i == 2 || i == 4 || i == 5)
	// 		task &= !(p[2][i][1] ^ p[0][i+2][8]) ;
	// 	else
	// 		task &= !(p[2][i][1]);
	// }
	// for(unsigned i = 0; i < N; i++)
	// {
	// 	if(i != 2 && i != 5 && i != 8)
	// 		task &= !(p[2][i][4] ^ p[0][i+1][7]) ;
	// 	else if(i == 1 || i == 2 || i == 4 || i == 5)
	// 		task &= !(p[2][i][4] ^ p[0][i+2][7]) ;
	// 	else
	// 		task &= !(p[2][i][4]);
	// }
	// for(unsigned i = 0; i < N; i++)
	// {
	// 	if(i != 2 && i != 5 && i != 8)
	// 		task &= !(p[1][i][2] ^ p[2][i+1][1]) ;
	// 	else if(i == 1 || i == 2 || i == 4 || i == 5)
	// 		task &= !(p[1][i][2] ^ p[2][i+2][1]) ;
	// 	else
	// 		task &= !(p[1][i][2]);
	// }
	// for(unsigned i = 0; i < N; i++)
	// {
	// 	if(i != 2 && i != 5 && i != 8)
	// 		task &= !(p[1][i][4] ^ p[1][i+1][1]) ;
	// 	else if(i == 1 || i == 2 || i == 4 || i == 5)
	// 		task &= !(p[1][i][4] ^ p[1][i+2][1]) ;
	// 	else
	// 		task &= !(p[1][i][4]);
	// }

	//4-доп
	// for(unsigned i = 0; i < N; i++)
	// {
	// 	if(i != 2 && i != 5 && i != 8)
	// 		task &= !(p[3][i][7] ^ p[1][i+1][0]) ;
	// 	else if(i == 1 || i == 2 || i == 4 || i == 5)
	// 		task &= !(p[3][i][7] ^ p[1][i+2][0]) ;
	// 	else
	// 		task &= !(p[3][i][7]);
	// }
	// for(unsigned i = 0; i < N; i++)
	// {
	// 	if(i != 2 && i != 5 && i != 8)
	// 		task &= !(p[0][i][7] ^ p[3][i+1][7]) ;
	// 	else if(i == 1 || i == 2 || i == 4 || i == 5)
	// 		task &= !(p[0][i][7] ^ p[3][i+2][7]) ;
	// 	else
	// 		task &= !(p[0][i][7]);
	// }
	// for(unsigned i = 0; i < N; i++)
	// {
	// 	if(i != 2 && i != 5 && i != 8)
	// 		task &= !(p[0][i][5] ^ p[1][i+1][3]) ;
	// 	else if(i == 1 || i == 2 || i == 4 || i == 5)
	// 		task &= !(p[0][i][5] ^ p[1][i+2][3]) ;
	// 	else
	// 		task &= !(p[0][i][5]);
	// }	
	
	double satcount = (double)bdd_satcount(task);
	printf("%lf\n", satcount);

	// out.open("out.txt");
	// out<<satcount<<" solutions:\n"<<endl;
	// if (satcount) bdd_allsat(task, fun);
	// out.close();

	bdd_done(); 
}


char var[N_VAR];

void print(void)
{
	for (unsigned i = 0; i < N; i++)
	{
		out<<i<<": ";
		for (unsigned j = 0; j < N; j++)
		{
			unsigned J = i*N*LOG_N + j*LOG_N;
			unsigned num = 0;
			for (unsigned k = 0; k < LOG_N; k++) num += (unsigned)(var[J + k] << k);
			out<<num<<' ';
		}
		out<<endl;
	}
	out<<endl;
}

void build(char* varset, unsigned n, unsigned I)
{
	if (I == n - 1)
	{
		if (varset[I] >= 0)
		{
			var[I] = varset[I];
			print();
			return;
		}
		var[I] = 0;
		print();
		var[I] = 1;
		print();
		return;
	}
	if (varset[I] >= 0) 
	{
		var[I] = varset[I];
		build(varset, n, I + 1);
		return;
	}
	var[I] = 0;
	build(varset, n, I + 1);
	var[I] = 1;
	build(varset, n, I + 1);
}

void fun(char* varset, int size)
{
	build(varset, size, 0);
}