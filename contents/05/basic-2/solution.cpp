#include <bits/stdc++.h>
using namespace std;
#define rep(i, m, n) for (int i = (m); i < (n); i++)
int partition(int A[], int p, int r)
{
	int x = A[r];
	int i = p - 1;
	rep(j, p, r)
	{
		if (A[j] <= x)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	return i + 1;
}

void quicksort(int A[], int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

int main()
{
	int N;
	int A[100010];
	cin >> N;
	rep(i, 0, N)
	{
		cin >> A[i];
	}

	quicksort(A, 0, N - 1);
	rep(i, 0, N)
	{
		cout << A[i] << " \n"[i == N - 1];
	}
}