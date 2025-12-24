#include <iostream>
#include <vector>
#include <limits>

int getHourglassMaxSum(const std::vector<std::vector<int>>& matrix) {
    int result = std::numeric_limits<int>::min();
    int rows = matrix.size() - 2;
    int columns = matrix[0].size() - 2;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int sum = matrix[i][j] + matrix[i][j + 1] + matrix[i][j + 2]
                    + matrix[i + 1][j + 1]
                    + matrix[i + 2][j] + matrix[i + 2][j + 1] + matrix[i + 2][j + 2];

            if (sum > result) {
                result = sum;
            }
        }
    }

    return result;
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0, 0},
        {0, 0, 2, 4, 4, 0},
        {0, 0, 0, 2, 0, 0},
        {0, 0, 1, 2, 4, 0}
    };

    int result = getHourglassMaxSum(matrix);
    std::cout << result << std::endl;
    return 0;
}
