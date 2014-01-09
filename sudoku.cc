#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int UNASSIGNED = 0;
const int ROWS = 9;
const int COLS = 9;
const int SQUARE_ROWS = 3;
const int SQUARE_COLS = 3;

class Board {
 public:
  Board() : rows_(ROWS), cols_(COLS) {
    board_ = vector<vector<int> > (rows_, vector<int> (cols_, UNASSIGNED));
  }
  inline ostream& Print(ostream &out) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j)
        out << board_[i][j] << " ";
      out << endl;
    }
  }
  inline int rows() const { return rows_; }
  inline int cols() const { return cols_; }
  inline vector<vector<int> > board() const { return board_; }
  int GetValue(int row, int col) const;
  void SetValue(int row, int col, int value);
  void Init();

 private:
  vector<vector<int> > board_;
  const int rows_, cols_;
};

int Board::GetValue(int row, int col) const {
  return board_[row - 1][col - 1];
}

void Board::SetValue(int row, int col, int value) {
  board_[row - 1][col - 1] = value;
}

void Board::Init() {
  string s, strm;
  while(cin >> s) {
    strm += s;
  }
  if (strm.size() != rows_ * cols_) {
    cout << "Input doesn't match board size, initialization failed!" << endl;
    exit(1);
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      board_[i][j] = strm[i * cols_ + j] - '0';
    }
  }
}

bool FindUnassignedLocation(const Board &board, int &row, int &col) {
  for (int i = 1; i <= board.rows(); ++i) {
    for (int j = 1; j <= board.cols(); ++j)
      if (board.GetValue(i, j) == UNASSIGNED) {
        row = i;
        col = j;
        return true;
      }
  }
  return false;
}

bool NoLineConflicts(const Board &board, int row, int col, int num) {
  bool conflict_flag = false;
  for (int i = 1; i <= board.rows(); ++i)
    if (board.GetValue(i, col) == num) conflict_flag = true;
  for (int i = 1; i <= board.cols(); ++i)
    if (board.GetValue(row, i) == num) conflict_flag = true;
  return !conflict_flag;
}
 
bool NoSquareConflicts(const Board &board, int row, int col, int num) {
  bool conflict_flag = false;
  int row_base = (row - 1) / SQUARE_ROWS * SQUARE_ROWS + 1;
  int col_base = (col - 1) / SQUARE_COLS * SQUARE_COLS + 1;
  for (int i = row_base; i < row_base + SQUARE_ROWS; ++i)
    for (int j = col_base; j < col_base + SQUARE_COLS; ++j)
      if (board.GetValue(i, j) == num) conflict_flag = true;
  return !conflict_flag;
}   

bool NoConflicts(const Board &board, int row, int col, int num) {
  return NoLineConflicts(board, row, col, num) && NoSquareConflicts(board, row, col, num);
}

bool SolveSudoku(Board &board) {
  int row, col;
  if (!FindUnassignedLocation(board, row, col))
    return true;
  for (int num = 1; num <= 9; ++num) {
    if (NoConflicts(board, row, col, num)) {
      board.SetValue(row, col, num);
      if (SolveSudoku(board)) return true;
      board.SetValue(row, col, UNASSIGNED);
    }
  }
  return false;
}

int main() {
  Board board;
  board.Init();
  SolveSudoku(board);
  board.Print(cout);
  return 0;
}
