
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

// n -- number of elements in a[]
// k -- elements' upper bound(i.e. no element in a[] is larger than k)
int* counting_sort(int *a, int n, int k)
{
	int i, j;
	int c[k+1];
	for(i = 0; i <= k; ++i)
		c[i] = 0;
	// build counting array c[]
	for(i = 0; i < n; ++i)
		c[a[i]]++;
	for(i = 1; i <= k; ++i)
		c[i] += c[i-1];

	int *ret = new int[n];
	for(i = n-1; i >= 0; --i) {
		ret[c[a[i]]-1] = a[i];
		c[a[i]]--;
	}
	return ret;
}

int main()
{
	int a[] = { 1};
	int size = sizeof(a)/sizeof(a[0]);
	int *ret = counting_sort(a, size, 10);
	copy(ret, ret+size, ostream_iterator<int>(cout, "\n"));
	delete ret;
}