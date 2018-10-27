#include <iostream>
#include <vector>

void Get_Matrix(std::vector<std::vector<float> >& Matrix, int N) {
    Matrix.resize(N);
    int i, j;
    for (i = 0; i < N; i++) {
        Matrix[i].resize(N);
        for (j = 0; j < i; j++) {
            std::cin >> Matrix[i][j];
        }
        for (j = i + 1; j < N; j++) {
            std::cin >> Matrix[i][j];
        }
    }
}

void Copy_Matrix(std::vector<std::vector<float> >& Matrix,
                 std::vector<std::vector<float> >& Reverse_Matrix, int N)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            Reverse_Matrix[i][j] = Matrix[i][j];
        }
    }
}

void Performing_Modified_Floyd(std::vector<std::vector<float> >& Matrix, int N)
{
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (Matrix[j][k] == -1) {
                    if ((Matrix[j][i] != -1) && (Matrix[i][k] != -1)) {
                        Matrix[j][k] = Matrix[j][i] * Matrix[i][k];
                    }
                }
                else {
                    if ((Matrix[j][i] * Matrix[i][k] < Matrix[j][k]) &&
                        ((Matrix[j][i] > 0) && (Matrix[i][k] > 0))) {
                    Matrix[j][k] = Matrix[j][i] * Matrix[i][k];
                    }
                }
            }
        }
    }
}

void Fill_Reverse_Matrix(std::vector<std::vector<float> >& Reverse_Matrix,
                         std::vector<std::vector<float> >& Matrix, int N)
{
    int i, j;
    Reverse_Matrix.resize(N);
    for (i = 0; i < N; i++) {
        Reverse_Matrix[i].resize(N);
        for (j = 0; j < N; j++) {
            Reverse_Matrix[i][j] = 1 / (Matrix[i][j]);
        }
    }
}

void Supplement_Matrix(std::vector<std::vector<float> >& Matrix, int N)
{
    int i;
    for (i = 0; i < N; i++) {
        Matrix[i][i] = 1;
    }
}

void Print_Matrix(std::vector<std::vector<float> >& Matrix, int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Print_Answer(std::vector<std::vector<float> >& Matrix,
                  std::vector<std::vector<float> >& Reverse_Matrix, int N)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if ((Matrix[i][j] * Reverse_Matrix[j][i] < 1) && (Matrix[i][j] * Reverse_Matrix[i][j] > 0)) {
                std::cout << "YES";
                return;
            }
        }
    }
    std::cout << "NO";
}

int main()
{
    int N;
    std::vector<std::vector<float> > Matrix;
    std::vector<std::vector<float> > Reverse_Matrix;
    std::cin >> N;
    Get_Matrix(Matrix, N);
    Supplement_Matrix(Matrix, N);
    Fill_Reverse_Matrix(Reverse_Matrix, Matrix, N);
    Copy_Matrix(Reverse_Matrix, Matrix, N);
    Performing_Modified_Floyd(Reverse_Matrix, N);
    Print_Answer(Matrix, Reverse_Matrix, N);

    return 0;
}
