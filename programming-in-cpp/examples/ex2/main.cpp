#include<iostream>
#include<string.h>
 
using namespace std;
 
// A function to swap character values of the string using references.
void swap (char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
 
// A function to print permutation using recursion technique.
void Permute(char *a, int i, int n) 
{
	int j; 
 
	if (i == n-1)
		cout<<"\n"<<a;
	else
	{
		for (j = i; j < n; j++)
		{
			// Swap the character at ith index with every other value to get all the possible permutations.
			swap(a[i], a[j]);
			Permute(a, i + 1, n);
			swap(a[i], a[j]);
		}
	}
}
 
int main()
{
	char str[]= "abcdefghijklmnopqrstuvwxyz";
	int len =4, count = 1;
 
		
 
	// Call permute() function to print all the permutation.
	Permute(str, 0, len);
 
	return 0;
}