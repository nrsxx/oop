#include <iostream>
#include <fstream>
#include <vector>


void Get_Matrix(std::vector<std::vector<int> >& Matrix, int N, std::ifstream& in) {
    Matrix.resize(N);
    int i, j;
    for (i = 0; i < N; i++) {
        Matrix[i].resize(N);
        for (j = 0; j < N; j++) {
            in >> Matrix[i][j];
        }
    }
}

void Fill_Matrix(std::vector<std::vector<int> >& Matrix, int N) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (Matrix[j][i] + Matrix[i][k] < Matrix[j][k]) {
                    Matrix[j][k] = Matrix[j][i] + Matrix[i][k];
                }
            }
        }
    }
}

void Print_Matrix(std::vector<std::vector<int> >& Matrix, int N, std::ofstream& out) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            out << Matrix[i][j] << " ";
        }
        out << std::endl;
    }
}

int main() {
    int N;
    std::vector<std::vector<int> > Matrix;
    std::ofstream out;
    out.open("floyd.out");
    std::ifstream in;
    in.open("floyd.in");
    in >> N;

    Get_Matrix(Matrix, N, in);

    Fill_Matrix(Matrix, N);

    Print_Matrix(Matrix, N, out);
    in.close();
    out.close();
    return 0;
}
