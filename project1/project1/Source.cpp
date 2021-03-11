#define _USE_MATH_DEFINES
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <math.h>
#include <cassert>

using namespace std;

template <typename T>
class matrix
{
public:
	matrix(size_t rows, size_t cols) : array(rows) {
		for (auto& thisRow : array)
			thisRow.resize(cols);
	}

	matrix(vector<vector<T>> v) : array{ v } { }
	matrix(vector<vector<T>>&& v) : array{ std::move(v) } { }

	const vector<T>& operator[](size_t row) const {
		return array[row];
	}

	vector<T>& operator[](size_t row) {
		return array[row];
	}

	size_t numrows() const {
		return array.size();
	}
	size_t numcols() const {
		return numrows() ? array[0].size() : 0;
	}

	void matprt() const {
		for (size_t i = 0; i < numrows(); ++i) {
			for (size_t j = 0; j < numcols(); ++j) {
				cout << array[i][j] << "   ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
private:
	vector<vector<T>> array;
};
#endif

/* Standard matrix multiplication. */
matrix<double> operator*(const matrix<double>& a, const matrix<double>& b) {
	size_t nra = a.numrows();
	size_t nca = a.numcols();
	size_t nrb = b.numrows();
	size_t ncb = b.numcols();

	if (nca != nrb) {
		cerr << "nca != nrb in matrix multiplication. Exiting." << endl;
		exit(1);
	}

	matrix<double> c(nra, ncb);

	for (size_t i = 0; i < nra; ++i) {
		for (size_t j = 0; j < ncb; ++j) {
			c[i][j] = 0.0;
			for (size_t k = 0; k < nca; ++k)
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	return c;
}

/* Complex matrix multiplication. */
matrix<complex<double>> operator*(const matrix<complex<double>>& a, const matrix<complex<double>>& b) {
	size_t nra = a.numrows();
	size_t nca = a.numcols();
	size_t nrb = b.numrows();
	size_t ncb = b.numcols();

	if (nca != nrb) {
		cerr << "nca != nrb in matrix multiplication. Exiting." << endl;
		exit(1);
	}

	matrix<complex<double>> c(nra, ncb);

	for (size_t i = 0; i < nra; ++i) {
		for (size_t j = 0; j < ncb; ++j) {
			c[i][j] = 0.0;
			for (size_t k = 0; k < nca; ++k)
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	return c;
}

/* Complex element-wise matrix multiplication. */
matrix<complex<double>> operator^(matrix<complex<double>> a, matrix<complex<double>> b) {
	size_t nra = a.numrows();
	size_t nca = a.numcols();
	size_t nrb = b.numrows();
	size_t ncb = b.numcols();

	if ((nra != nrb) || (nca != ncb)) {
		cerr << "rows and columns must be the same for elementwise multiplication. Exiting." << endl;
		exit(1);
	}

	matrix<complex<double>> c(nra, nca);

	for (size_t i = 0; i < nra; ++i) {
		for (size_t j = 0; j < nca; ++j) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}

	return c;
}

/* Returns real part of complex matrix. */
matrix<double> to_real(matrix<complex<double>>& a) {
	size_t M = a.numrows(), N = a.numcols();
	matrix<double> a_real(M, N);

	for (size_t i = 0; i < M; ++i) {
		for (size_t j = 0; j < N; ++j) {
			a_real[i][j] = real(a[i][j]);
		}
	}

	return a_real;
}

/* Converts standard matrix to complex matrix by adding 0i to each element. */
matrix<complex<double>> to_complex(matrix<double>& a) {
	size_t M = a.numrows(), N = a.numcols();
	matrix<complex<double>> a_complex(M, N);

	for (size_t i = 0; i < M; ++i) {
		for (size_t j = 0; j < N; ++j) {
			a_complex[i][j] = complex<double>(a[i][j], 0.0);
		}
	}

	return a_complex;
}

/* Computes dft of complex matrix. */
matrix<complex<double>> dft(matrix<complex<double>> a) {
	size_t M = a.numrows(), N = a.numcols();
	matrix<complex<double>> P(M, M), Q(N, N);

	for (size_t u = 0; u < M; ++u) {
		for (size_t m = 0; m < M; ++m) {
			P[u][m] = (1.0 / M) * complex<double>(cos(-2.0 * M_PI * double(u * m) / M), sin(-2.0 * M_PI * double(u * m) / M));
		}
	}

	for (size_t v = 0; v < N; ++v) {
		for (size_t n = 0; n < N; ++n) {
			Q[v][n] = (1.0 / N) * complex<double>(cos(-2.0 * M_PI * double(v * n) / N), sin(-2.0 * M_PI * double(v * n) / N));
		}
	}

	return P * a * Q;
}

/* Computes inverse dft of complex matrix. */
matrix<complex<double>> idft(matrix<complex<double>> a) {
	size_t M = a.numrows(), N = a.numcols();
	matrix<complex<double>> P(M, M), Q(N, N);

	for (size_t u = 0; u < M; ++u) {
		for (size_t m = 0; m < M; ++m) {
			P[u][m] = complex<double>(cos(2.0 * M_PI * double(u * m) / M), sin(2.0 * M_PI * double(u * m) / M));
		}
	}

	for (size_t v = 0; v < N; ++v) {
		for (size_t n = 0; n < N; ++n) {
			Q[v][n] = complex<double>(cos(2.0 * M_PI * double(v * n) / N), sin(2.0 * M_PI * double(v * n) / N));
		}
	}

	return P * a * Q;
}

/* Computes circular convolution of 2 complex matrices. */
matrix<complex<double>> c_conv(matrix<complex<double>> a, matrix<complex<double>> b) {
	size_t M = a.numrows(), N = a.numcols();
	matrix<complex<double>> g(M, N);

	for (size_t m = 0; m < M; ++m) {
		for (size_t n = 0; n < N; ++n) {
			for (size_t u = 0; u < M; ++u) {
				for (size_t v = 0; v < N; ++v) {
					g[m][n] += (1.0/(M*N)) * a[(m - u + M) % M][(n - v + N) % N] * b[u][v];
				}
			}
		}
	}

	return g;
}

/* Computes ssd error of two complex matrices. */
double ssd_error(matrix<complex<double>> a, matrix<complex<double>> a_) {
	size_t M = a.numrows(), N = a.numcols();
	double error = 0;

	for (size_t m = 0; m < M; ++m) {
		for (size_t n = 0; n < N; ++n) {
			error += pow((real(a[m][n]) - real(a_[m][n])), 2);
		}
	}

	return error;
}

int main() {
	size_t M, N;
	ifstream fin;
	double error;

	fin.open("input.txt");

	if (!fin) {
		cerr << "cannot open file input.txt." << endl;
		exit(1);
	}

	fin >> M >> N;

	matrix<double> f(M, N), h(M, N);
	matrix<complex<double>> F(M, N), H(M, N), f_(M, N), h_(M, N), G(M, N), g(M, N), g_(M, N);

	for (size_t i = 0; i < M; ++i) {
		for (size_t j = 0; j < N; ++j) {
			fin >> f[i][j];
		}
	}

	for (size_t i = 0; i < M; ++i) {
		for (size_t j = 0; j < N; ++j) {
			fin >> h[i][j];
		}
	}

	F = dft(to_complex(f));		// compute dft of f

	cout << "F: " << endl;
	F.matprt();

	f_ = idft(F);				// compute inverse dft of F

	cout << "f': " << endl;
	to_real(f_).matprt();

	H = dft(to_complex(h));		// compute dft of h

	cout << "H: " << endl;
	H.matprt();

	h_ = idft(F);				// compute inverse dft of H

	cout << "h': " << endl;
	to_real(h_).matprt();

	G = F ^ H;					// perform element-wise multiplication of F and H
	g = idft(G);				// compute inverse dft of G
	
	cout << "g: " << endl;
	to_real(g).matprt();

	g_ = c_conv(to_complex(f), to_complex(h));	// compute circular convolution of f and h
	cout << "g': " << endl;
	to_real(g_).matprt();

	error = ssd_error(g, g_);	// compute ssd error of g and g'
	cout << "ssd error: " << error << endl;

	fin.close();

	return 0;
}
