#include <iostream>
using namespace std;

int main();
int input_grid();
int validate_grid();
int solve_cell(int row, int column);
int is_valid(int row, int column, int value);
void print_grid();

int original[9][9], grid[9][9];

int main() {
    cout << "Enter rows line by line. Use numbers for known cells, ";
    cout << "zero or dot for missing cells.\n";

    if (!input_grid()) {
        cout << "Error: unable to input grid\n";
        return 0;
    }

    cout << "\nValidating puzzle... ";
    if (!validate_grid()) {
        cout << "invalid!\n";
        return 0;
    }

    cout << "valid.\n\nSolving following puzzle:\n";
    print_grid();

    if (!solve_cell(0, 0)) {
        cout << "\nUnfortunately, your puzzle is unsolvable\n";
        return 0;
    }

    cout << "\nPuzzle solved:\n";
    print_grid();
    return 0;
}

int input_grid() {
    char character;
    int row = 0, column = 0;

    while (row < 9) {
        if (column == 0) {
            cout << "Row " << row + 1 << ": ";
        }
        cin >> character;

        if ((character >= '0' && character <= '9') || character == '.') {
            if (column > 8) {
                cout << "Error: Each row has maximum 9 cells\n";
                return 0;
            }

            original[row][column] = grid[row][column] = (character == '.') ? 0 : character - '0';
            column++;
            if (column == 9) {
                row++;
                column = 0;
            }
        }
    }

    return 1;
}

int validate_grid() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] && !is_valid(i, j, grid[i][j]))
                return 0;
        }
    }
    return 1;
}

int solve_cell(int row, int column) {
    if (column == 9) {
        column = 0;
        row++;
    }
    if (row == 9)
        return 1;

    if (original[row][column] != 0)
        return solve_cell(row, column + 1);

    for (int num = 1; num <= 9; num++) {
        if (is_valid(row, column, num)) {
            grid[row][column] = num;
            if (solve_cell(row, column + 1))
                return 1;
        }
        grid[row][column] = 0;
    }
    return 0;
}

int is_valid(int row, int column, int value) {
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == value && i != column) return 0;
        if (grid[i][column] == value && i != row) return 0;
    }

    int r = (row / 3) * 3;
    int c = (column / 3) * 3;
    for (int i = r; i < r + 3; i++)
        for (int j = c; j < c + 3; j++)
            if (grid[i][j] == value && !(i == row && j == column))
                return 0;

    return 1;
}

void print_grid() {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) cout << "+-------+-------+-------+\n";
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) cout << "| ";
            if (grid[i][j] != 0) cout << grid[i][j] << " ";
            else cout << ". ";
        }
        cout << "|\n";
    }
    cout << "+-------+-------+-------+\n";
}
