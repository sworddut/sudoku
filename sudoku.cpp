#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <numeric>

// 判断是否为完全平方数
bool isPerfectSquare(int num) {
    int sqrt_num = static_cast<int>(std::sqrt(num));
    return sqrt_num * sqrt_num == num;
}

class Grid {
public:
    std::vector<std::vector<int>> grid;
    int BOX_SIZE;
    int GRID_SIZE;

    Grid(const std::vector<std::vector<int>>& gridInput) {
        _check(gridInput);
        grid = gridInput;
        BOX_SIZE = static_cast<int>(std::sqrt(grid.size()));
        GRID_SIZE = grid.size();
    }

    // 获取行
    std::vector<std::vector<int>> getRows() const {
        return grid;
    }

    // 获取列
    std::vector<std::vector<int>> getColumns() const {
        std::vector<std::vector<int>> columns(GRID_SIZE, std::vector<int>(GRID_SIZE));
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                columns[j][i] = grid[i][j];
            }
        }
        return columns;
    }

    // 获取所有盒子
    std::vector<std::vector<int>> getBoxes() const {
        std::vector<std::vector<int>> boxes;
        for (int boxRow = 0; boxRow < BOX_SIZE; ++boxRow) {
            for (int boxCol = 0; boxCol < BOX_SIZE; ++boxCol) {
                std::vector<int> box;
                for (int i = 0; i < BOX_SIZE; ++i) {
                    for (int j = 0; j < BOX_SIZE; ++j) {
                        box.push_back(grid[boxRow * BOX_SIZE + i][boxCol * BOX_SIZE + j]);
                    }
                }
                boxes.push_back(box);
            }
        }
        return boxes;
    }

    std::vector<int> getRow(int row) const {
        return grid[row];
    }

    std::vector<int> getColumn(int col) const {
        std::vector<int> column(GRID_SIZE);
        for (int i = 0; i < GRID_SIZE; ++i) {
            column[i] = grid[i][col];
        }
        return column;
    }

    std::vector<int> getBox(int row, int col) const {
        int boxRow = row / BOX_SIZE;
        int boxCol = col / BOX_SIZE;
        return getBoxes()[boxRow * BOX_SIZE + boxCol];
    }

    static std::vector<std::vector<int>> getEmptyGrid(int num) {
        return std::vector<std::vector<int>>(num, std::vector<int>(num, 0));
    }

    static std::vector<std::vector<std::vector<int>>> getEmptyInferenceGrid(int num) {
        return std::vector<std::vector<std::vector<int>>>(num, std::vector<std::vector<int>>(num, std::vector<int>()));
    }

protected:
    void _check(const std::vector<std::vector<int>>& grid) const {
        if (grid.empty() || !isPerfectSquare(grid.size())) {
            throw std::runtime_error("Invalid Grid");
        }
    }
};

class Sudoku : public Grid {
public:
    Sudoku(const std::string& input) : Grid(parse(input)) {
        if (!_check()) {
            throw std::runtime_error("Invalid Sudoku");
        }
    }

    std::vector<std::vector<std::vector<int>>> getInference() {
        std::vector<std::vector<std::vector<int>>> inference = Grid::getEmptyInferenceGrid(GRID_SIZE);
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (grid[i][j] == 0) {
                    inference[i][j] = _getCandidate(i, j);
                }
            }
        }
        return inference;
    }

    void show() {
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                std::cout << '|';
                if (grid[i][j] == 0)
                    std::cout << '_';
                else
                    std::cout << grid[i][j];
            }
            std::cout << '|' << std::endl;
        }
    }

    void inferenceShow() {
        auto inference = getInference();
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                for (auto num : inference[i][j])
                    std::cout << num<<' ';
                std::cout << '|';
            }
            std::cout <<'|' << std::endl;
        }
    }

    static std::vector<std::vector<int>> parse(const std::string& input) {
        if (!_checkStr(input)) {
            throw std::runtime_error("Invalid Input");
        }

        int size = static_cast<int>(std::sqrt(input.length()));
        std::vector<std::vector<int>> grid = getEmptyGrid(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j] = input[i * size + j] - '0'; // 将字符转换为整数
            }
        }
        return grid;
    }

private:
    bool _check() const {
        return std::all_of(grid.begin(), grid.end(), [this](const std::vector<int>& row) {
            return std::all_of(row.begin(), row.end(), [this](int val) {
                return val >= 0 && val <= GRID_SIZE;
                });
            });
    }

    std::vector<int> _getCandidate(int row, int col) {
        std::vector<int> candidate(GRID_SIZE);
        std::iota(candidate.begin(), candidate.end(), 1);

        auto box = getBox(row, col);
        auto column = getColumn(col);
        auto rowVals = getRow(row);

        auto endIt = std::remove_if(candidate.begin(), candidate.end(), [&](int num) {
            return std::find(box.begin(), box.end(), num) != box.end() ||
                std::find(column.begin(), column.end(), num) != column.end() ||
                std::find(rowVals.begin(), rowVals.end(), num) != rowVals.end();
            });

        candidate.erase(endIt, candidate.end());
        return candidate; // 返回第一个候选项，实际可能需要返回多个
    }

    static bool _checkStr(const std::string& input) {
        return !input.empty() && input.size() > 0 && isPerfectSquare(input.length());
    }

};


int main()
{
    std::string input = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
    auto sudoku = Sudoku(input);
    sudoku.show();
    sudoku.inferenceShow();
}

