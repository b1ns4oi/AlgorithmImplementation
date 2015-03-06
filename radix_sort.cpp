
#include <iostream>
#include <algorithm>
#include <iterator>

using std::max_element;
using std::cout;
using std::cin;
using std::endl;
using std::copy;

void counting_sort_helper(int pow, int *a, int *b, int n)
{
	int i;
	int c[10] = { 0 };
	for(i = 0; i < n; ++i)
		c[a[i]%pow/(pow/10)]++;
	for(i = 1; i < 10; ++i) 
		c[i] += c[i-1];
	for(i = n-1; i >= 0; --i) {
		b[c[a[i]%pow/(pow/10)]-1] = a[i];
		c[a[i]%pow/(pow/10)]--;
	}
}

// radix sort the n elements in a[]
// note: this version couldn't deal with negative elements 
int* radix_sort(int *a, int n)
{
	int max = *max_element(a, a+n);
	int *b = new int[n];
	// flag: true--elements now in a[]; false--elements now in b[]
	bool flag = true;

	for(int i = 10; max > 0; max /= 10, i *= 10, flag = !flag) {
		if(flag) 
			counting_sort_helper(i, a, b, n);
		else
			counting_sort_helper(i, b, a, n);
	}
	if(flag)
		delete[] b;
	return (flag ? a : b);
}


int main()
{
	int a[] = { 861, 28, 9, 10, 10000, 3 };
	int size = sizeof(a)/sizeof(a[0]);
	
	int *ret = radix_sort(a, size);
	copy(ret, ret+size, std::ostream_iterator<int>(cout, "\n"));

	if(ret != a)
		delete[] ret;
}