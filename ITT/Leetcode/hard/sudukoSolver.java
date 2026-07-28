public class Solution {
    public void solveSudoku(char[][] board) {
        if (board == null || board.length == 0) {
            return;
        }
        solve(board);
    }

    private boolean solve(char[][] board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c; // Put candidate

                            // Recursively solve for the next empty cells
                            if (solve(board)) {
                                return true; // Solution found!
                            } else {
                                board[i][j] = '.'; // Step 4: Backtrack
                            }
                        }
                    }
                    return false; 
                }
            }
        }
        return true; 
    }

    private boolean isValid(char[][] board, int row, int col, char c) {
        int boxRowStart = 3 * (row / 3);
        int boxColStart = 3 * (col / 3);

        for (int i = 0; i < 9; i++) {
   
            if (board[row][i] == c) return false;
        
            if (board[i][col] == c) return false;
           
            if (board[boxRowStart + i / 3][boxColStart + i % 3] == c) return false;
        }
        return true;
    }
}
