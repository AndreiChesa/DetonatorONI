#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

ifstream f("detonator.in");
ofstream g("detonator.out");

const int NMAX = 1005;
int q, n;
int mat[NMAX][NMAX];
int viz[NMAX][NMAX];
int minime[NMAX][NMAX];

int main()
{
	f >> q;
	for (int b = 1; b <= q; b++)
	{
		f >> n;
		set<pair<pair<int,int>, pair<int, int>>> s;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= i; j++)
			{
				viz[i][j] = 0;
				f >> mat[i][j];

				int val = mat[i][j];
				if (j < i)
				{
					val = min(val, minime[i - 1][j]);
				}
				if (j > 1)
				{
					val = min(val, minime[i - 1][j - 1]);
				}
				minime[i][j] = val;

				if (i == n)
				{
					s.insert({ {val,mat[i][j]}, {i, j} });
				}
			}
		}

		int time = 1;
		int required = 1e9;
		int spare = 1e9;

		while (!s.empty())
		{
			int x = s.begin()->second.first;
			int y = s.begin()->second.second;
			int val = mat[x][y];
			s.erase(s.begin());
			if (time > val)
			{
				required = min(required,val - time);
			}
			else if(time <= val)
			{
				spare = min(val - time,spare);
			}
			viz[x][y] = 1;
			if (viz[x][y + 1] == 1 && !viz[x-1][y])
			{
				int x1 = x - 1, y1 = y;
				int val = mat[x1][y1];
				if (y1 < x1)
				{
					val = min(val, minime[x1 - 1][y1]);
				}
				if (y1 > 1)
				{
					val = min(val, minime[x1 - 1][y1 - 1]);
				}
				s.insert({ {val,mat[x1][y1]}, {x - 1, y} });
			}
			if (viz[x][y-1] == 1 && !viz[x-1][y-1])
			{
				int x1 = x - 1, y1 = y-1;
				int val = mat[x1][y1];
				if (y1 < x1)
				{
					val = min(val, minime[x1 - 1][y1]);
				}
				if (y1 > 1)
				{
					val = min(val, minime[x1 - 1][y1 - 1]);
				}
				s.insert({ {val,mat[x1][y1]}, {x - 1, y - 1} });
			}
			time++;
		}
		if (required != 1e9)
		{
			g << required;
		}
		else {
			g << spare;
		}
		g << '\n';
	}
}
