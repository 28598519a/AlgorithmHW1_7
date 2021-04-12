#include <iostream>
#include <ctime>
using namespace std;

int p[500];
void simpleunion(int i, int j)
{
	p[i] = j;
}

int simplefind(int i)
{
	while (p[i] >= 0) i = p[i];
	return i;
}

void weightedunion(int i, int j)
{
	int temp = p[i] + p[j];
	if (p[i] > p[j])
	{
		p[i] = j;
		p[j] = temp;
	}
	else
	{
		p[j] = i;
		p[i] = temp;
	}
}

int collapsingfind(int i)
{
	int r = i;
	while (p[r] > 0) r = p[r];
	while (i != r)
	{
		int s = p[i];
		p[i] = r;
		i = s;
	}
	return i;
}

bool vaild(int r1, int r2)
{
	if (r1 != r2)
	{
		if (p[r1] < 0 && p[r2] < 0)
		{
			return true;
		}
		else if (p[r1] < 0)
		{
			while (p[r2] >= 0)
			{
				if (p[r2] == r1 || r1 == r2) return false;
				r2 = p[r2];
			}
		}
		else if (p[r2] < 0)
		{
			while (p[r1] >= 0)
			{
				if (p[r1] == r2 || r1 == r2) return false;
				r1 = p[r1];
			}
		}
		else
		{
			return false;
		}
	}
	else return false;
	return true;
}

int main()
{
	double t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;
	for (int k = 0; k < 50; k++) {
		double Start, End;
		srand(time(NULL));

		for (int i = 0; i < 500; i++)
		{
			p[i] = -1;
		}

		Start = clock();
		for (int i = 0; i < 8000; i++)
		{
			int r1 = rand() % 500;
			int r2 = rand() % 500;

			if (r1 != r2 && p[r1] < 0 && p[r2] < 0)
			{
				simpleunion(r1, r2);
			}
		}
		End = clock();
		t1 += (End - Start);

		Start = clock();
		for (int i = 0; i < 200000; i++) simplefind(rand() % 500);
		End = clock();
		t2 += (End - Start);

		Start = clock();
		for (int i = 0; i < 200000; i++) simplefind(rand() % 500);
		End = clock();
		t3 += (End - Start);

		for (int i = 0; i < 500; i++)
		{
			p[i] = -1;
		}

		Start = clock();
		for (int i = 0; i < 8000; i++)
		{
			int r1 = rand() % 500;
			int r2 = rand() % 500;

			if (r1 != r2 && p[r1] < 0 && p[r2] < 0)
			{
				weightedunion(r1, r2);
			}
		}
		End = clock();
		t4 += (End - Start);

		Start = clock();
		for (int i = 0; i < 200000; i++) simplefind(rand() % 500);
		End = clock();
		t5 += (End - Start);

		Start = clock();
		for (int i = 0; i < 200000; i++) simplefind(rand() % 500);
		End = clock();
		t6 += (End - Start);
	}
	cout << "Time (SimpleUnion) : " << t1/50 << " ms\n";
	cout << "Time (SimpleUnion + SimpleFind) : " << t2/50 << " ms\n";
	cout << "Time (SimpleUnion + CollapsingFind) : " << t3/50 << " ms\n";
	cout << "Time (WeightedUnion) : " << t4/50 << " ms\n";
	cout << "Time (WeightedUnion + SimpleFind) : " << t5/50 << " ms\n";
	cout << "Time (WeightedUnion + CollapsingFind) : " << t6/50 << " ms\n";
	return 0;
}