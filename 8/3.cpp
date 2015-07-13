#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<int>& A) {
	const int N = A.size();
	for (int j=N; j>= 0;--j) {
		int m = j;
		for (int i = 0; i<j; ++i) {
			if (A[i] < A[m]) m=i;
		}
		swap(A[j], A[m]);
	}
}

int main (int argc, char** argv) {
	vector<int> test = {10,20,1,7,13,6,18};
	
	for (auto &t : test) {
		cout << t << " ";
	}
	
	cout << endl;
	
	selectionSort(test);
	
	for (auto &t : test) {
		cout << t << " ";
	}
	
	return 0;
}