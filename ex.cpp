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
	task &= p[3][0][5];
	task &= p[3][5][8];
	task &= p[2][2][6];
	task &= p[3][2][4];
	task &= p[2][0][0];
	task &= p[1][8][0];
	task &= p[3][3][1];

	//1-доп
	task &= p[1][1][4];
	task &= p[1][3][7];
	task &= p[0][8][2];
	task &= p[0][5][7];
	task &= p[2][3][1];
	task &= p[1][7][1];

	//2
	for(unsigned i = 0; i < N; i++)
		task &= !(p[2][i][6] ^ p[1][i][6]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[3][i][3] ^ p[0][i][3]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[0][i][6] ^ p[1][i][2]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[3][i][7] ^ p[0][i][5]) ;
	for(unsigned i = 0; i < N; i++)
		task &= !(p[0][i][7] ^ p[2][i][7]) ;

	//2-доп
	//-----

	//3
	for(unsigned i = 0; i < N; i++)
	{
		if(i != 2 && i != 5 && i != 8)
			task &= !(p[3][i][0] ^ p[1][i+1][1]) ;
		else
			task &= !(p[3][i][0]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i != 2 && i != 5 && i != 8)
			task &= !(p[1][i][5] ^ p[1][i+1][4]) ;
		else
			task &= !(p[1][i][5]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[2][i][7] ^ p[2][i+2][4]) ;
		else
			task &= !(p[2][i][7]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[1][i][8] ^ p[2][i+2][4]) ;
		else
			task &= !(p[1][i][8]);
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[3][i][2] ^ p[3][i+2][1]) ;
		else
			task &= !(p[3][i][2]);
	}

	//3-Доп
	for(unsigned i = 0; i < N; i++)
	{
		if(i == 1 || i == 2 || i == 4 || i == 5)
			task &= !(p[0][i][7] ^ p[0][i+2][3]) ;
		else
			task &= !(p[0][i][7]);
	}


	//4
	bdd temp = bddfalse;
	bool left = false, right = false;
	for(unsigned i = 0; i < N; i++)
	{
		right = i != 2 && i != 5 && i != 8;
		left = i == 1 || i == 2 || i == 4 || i == 5;
		if(right)
		{
			temp |= !(p[2][i][5] ^ p[0][i+1][4]) ;
		}
		if(left)
		{
			temp |= !(p[2][i][5] ^ p[0][i+2][4]) ;
		}
		if(!right && !left)
		{
			task &= !(p[2][i][5]);
		}
		else
		{
			task &= temp;
			temp = bddfalse;
		}
			
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i != 2 && i != 5 && i != 8)
		{
			temp |= !(p[0][i][8] ^ p[3][i+1][1]) ;
		}
		if(i == 1 || i == 2 || i == 4 || i == 5)
		{
			temp |= !(p[0][i][8] ^ p[3][i+2][1]) ;
		}
		if(!(i != 2 && i != 5 && i != 8) && !(i == 1 || i == 2 || i == 4 || i == 5))
		{
			task &= !(p[0][i][8]);
		}
		else
		{
			task &= temp;
			temp = bddfalse;
		}
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i != 2 && i != 5 && i != 8)
		{
			temp |= !(p[3][i][2] ^ p[0][i+1][0]) ;
		}
		if(i == 1 || i == 2 || i == 4 || i == 5)
		{
			temp |= !(p[3][i][2] ^ p[0][i+2][0]) ;
		}
		if(!(i != 2 && i != 5 && i != 8) && !(i == 1 || i == 2 || i == 4 || i == 5))
		{
			task &= !(p[3][i][2]);
		}
		else
		{
			task &= temp;
			temp = bddfalse;
		}
	}
	for(unsigned i = 0; i < N; i++)
	{
		if(i != 2 && i != 5 && i != 8)
		{
			temp |= !(p[1][i][1] ^ p[1][i+1][0]) ;
		}
		if(i == 1 || i == 2 || i == 4 || i == 5)
		{
			temp |= !(p[1][i][1] ^ p[1][i+2][0]) ;
		}
		if(!(i != 2 && i != 5 && i != 8) && !(i == 1 || i == 2 || i == 4 || i == 5))
		{
			task &= !(p[1][i][1]);
		}
		else
		{
			task &= temp;
			temp = bddfalse;
		}
	}
	//4-доп
	//---------

	//Границы значений параметров
	bdd tmp = bddfalse;
	for(unsigned i = 0; i < N; i++)
	{
		for(unsigned j = 0; j < M; j++)
		{
			for(unsigned k = 0; k < N; k++)
			{
				tmp |= p[j][i][k];
			}
			task &= tmp;
			tmp = bddfalse;
		}
	}

	//Каждое значение - уникальное
	for(unsigned i = 0; i < M; i++)
	{
		for(unsigned j = 0; j < N; j++)
		{
			for(unsigned k = 0; k < N; k++)
			{
				for(unsigned m = j+1; m < N; m++)
				{
					task &= (p[i][j][k] >> !(p[i][m][k])); 
				}
			}
		}
	}
	
	double satcount = (double)bdd_satcount(task);
	printf("%lf\n", satcount);

	out.open("out.txt");
	out<<satcount<<" solutions:\n"<<endl;
	if (satcount) bdd_allsat(task, fun);
	out.close();

	bdd_done(); 
}


char var[N_VAR];

void print(void)
{
	for (unsigned i = 0; i < N; i++)
	{
		out<<i<<": ";
		for (unsigned j = 0; j < M; j++)
		{
			unsigned J = i*M*LOG_N + j*LOG_N;
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