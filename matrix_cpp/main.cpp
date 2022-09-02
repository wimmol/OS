#include <iostream>
#include <vector>
#include <thread>
#include <cassert>

using namespace std;

using Matrix = vector<vector<int>>;

int count_cell(Matrix& A, Matrix& B, Matrix& C, int row, int col) {
	int res = 0;

	for (int k = 0; k < A[row].size(); ++k)
		res += A[row][k] * B[k][col];

	printf("C[%2d][%2d] = %d\n", row, col, res);
	C[row][col] = res;

	return res;
}

Matrix multiply_matrix(Matrix& A, Matrix& B) {
    assert(A[0].size() == B.size());
	size_t n = A.size(), k = B[0].size();
	Matrix C(n, vector<int>(k));
	vector<thread> threads;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < k; ++j)
			threads.emplace_back(count_cell, ref(A), ref(B), ref(C), i, j);

	for (thread& current_thread : threads)
        current_thread.join();

	return C;

}

Matrix random_fill(unsigned int n, unsigned int m) {
	Matrix M(n, vector<int>(m));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			M[i][j] = 1 + rand() % 100;

	return M;
}

void print(Matrix& M) {
	for (auto & i : M) {
		printf("[ ");
		for (int j : i)
			printf("%9d ", j);
        printf("]\n");
	}
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

	Matrix A = random_fill(n, m);
	Matrix B = random_fill(m, k);

	Matrix C = multiply_matrix(A, B);

    print(C);

	return 0;
}
