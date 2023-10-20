//
// Created by Julia Szymańska on 02/06/2023.
//

#ifndef KOLKOIKRZYZYK_KOLKOIKRZYZYK_H
#define KOLKOIKRZYZYK_KOLKOIKRZYZYK_H

#include <iostream>
#include <vector>
#include <limits>

// Klasa reprezentująca pole na planszy
class Field {
public:
    int row;
    int col;
    char value;

    Field(int r, int c, char v) : row(r), col(c), value(v) {}

    // Operator porównania dla klasy Field
    bool operator==(const Field& other) const {
        return row == other.row && col == other.col && value == other.value;
    }
};


// Klasa reprezentująca planszę
class Board {
private:
    int size;  // Rozmiar planszy
    int winLength;  // Długość rzędu do wygranej
    std::vector<std::vector<char>> board;  // Dwuwymiarowy wektor reprezentujący planszę

public:
    Board(int s, int w) : size(s), winLength(w) {
        // Inicjalizacja planszy pustymi polami
        board.resize(size, std::vector<char>(size, ' '));
    }

    // Metoda do wyświetlania aktualnego stanu planszy
    void displayBoard() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Metoda do sprawdzania, czy plansza jest pełna
    bool isBoardFull() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    // Metoda do sprawdzania, czy dany rząd zawiera wygrywającą kombinację znaków
    bool isWinningRow(const std::vector<char>& row) const {
        for (int i = 0; i <= size - winLength; i++) {
            bool isWinning = true;
            char first = row[i];
            if (first == ' ')
                continue;
            for (int j = i + 1; j < i + winLength; j++) {
                if (row[j] != first) {
                    isWinning = false;
                    break;
                }
            }
            if (isWinning)
                return true;
        }
        return false;
    }

    // Metoda do sprawdzania, czy plansza zawiera wygraną kombinację znaków
    bool hasWinner() const {
        // Sprawdzanie wierszy
        for (int i = 0; i < size; i++) {
            std::vector<char> row;
            for (int j = 0; j < size; j++) {
                row.push_back(board[i][j]);
            }
            if (isWinningRow(row))
                return true;
        }

        // Sprawdzanie kolumn
        for (int i = 0; i < size; i++) {
            std::vector<char> column;
            for (int j = 0; j < size; j++) {
                column.push_back(board[j][i]);
            }
            if (isWinningRow(column))
                return true;
        }

        // Sprawdzanie przekątnych
        std::vector<char> diagonal1;
        std::vector<char> diagonal2;
        for (int i = 0; i < size; i++) {
            diagonal1.push_back(board[i][i]);
            diagonal2.push_back(board[i][size - i - 1]);
        }
        if (isWinningRow(diagonal1) || isWinningRow(diagonal2))
            return true;

        return false;
    }

    // Metoda do wykonania ruchu przez gracza
    void makeMove(const Field& field, char player) {
        board[field.row][field.col] = player;
    }

    // Metoda do cofnięcia ruchu
    void undoMove(const Field& field) {
        board[field.row][field.col] = ' ';
    }

    // Metoda zwracająca dostępne ruchy
    std::vector<Field> getAvailableMoves() const {
        std::vector<Field> availableMoves;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == ' ')
                    availableMoves.push_back(Field(i, j, ' '));
            }
        }
        return availableMoves;
    }

    // Metoda do oceny planszy
    int evaluateBoard() const {
        if (hasWinner())
            return std::numeric_limits<int>::max();  // Wygrana
        else if (isBoardFull())
            return 0;  // Remis
        else
            return 1;  // Plansza niepełna
    }
};

// Funkcja wykonująca algorytm MinMax z alfa-beta cięciami
int minimax(Board& board, int depth, int alpha, int beta, bool isMaxPlayer) {
    // Sprawdzanie warunku zakończenia rekurencji
    int score = board.evaluateBoard();
    if (score != 1)
        return score;

    // Jeśli ruch dla maksymalnego gracza
    if (isMaxPlayer) {
        int maxScore = std::numeric_limits<int>::min();
        std::vector<Field> moves = board.getAvailableMoves();
        for (const auto& move : moves) {
            board.makeMove(move, 'X');
            int currentScore = minimax(board, depth + 1, alpha, beta, false);
            maxScore = std::max(maxScore, currentScore);
            alpha = std::max(alpha, currentScore);
            board.undoMove(move);
            if (beta <= alpha)
                break;  // Alfa-beta cięcie
        }
        return maxScore;
    }
        // Jeśli ruch dla minimalnego gracza
    else {
        int minScore = std::numeric_limits<int>::max();
        std::vector<Field> moves = board.getAvailableMoves();
        for (const auto& move : moves) {
            board.makeMove(move, 'O');
            int currentScore = minimax(board, depth + 1, alpha, beta, true);
            minScore = std::min(minScore, currentScore);
            beta = std::min(beta, currentScore);
            board.undoMove(move);
            if (beta <= alpha)
                break;  // Alfa-beta cięcie
        }
        return minScore;
    }
}

// Funkcja wykonująca ruch komputera
void makeComputerMove(Board& board) {
    int maxScore = std::numeric_limits<int>::min();
    std::vector<Field> moves = board.getAvailableMoves();
    Field bestMove(-1, -1, ' ');

    for (const auto& move : moves) {
        board.makeMove(move, 'X');
        int currentScore = minimax(board, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false);
        if (currentScore > maxScore) {
            maxScore = currentScore;
            bestMove = move;
        }
        board.undoMove(move);
    }

    board.makeMove(bestMove, 'X');
    std::cout << "Komputer wykonuje ruch (X): [" << bestMove.row << ", " << bestMove.col << "]" << std::endl;
}

// Funkcja wykonująca ruch gracza
void makePlayerMove(Board& board) {
    int row, col;
    std::cout << "Podaj rząd i kolumnę (oddzielone spacją): ";
    std::cin >> row >> col;

    Field move(row, col, ' ');

    while (board.getAvailableMoves().end() == std::find(board.getAvailableMoves().begin(), board.getAvailableMoves().end(), move)) {
        std::cout << "Nieprawidłowy ruch! Spróbuj ponownie." << std::endl;
        std::cout << "Podaj rząd i kolumnę (oddzielone spacją): ";
        std::cin >> row >> col;
        move = Field(row, col, ' ');
    }

    board.makeMove(move, 'O');
}

// Funkcja rozpoczynająca grę
void playGame(int boardSize, int winLength) {
    Board board(boardSize, winLength);
    std::cout << "Rozpoczyna grę: Gracz (O)" << std::endl;
    std::cout << "Plansza:" << std::endl;
    board.displayBoard();

    while (!board.hasWinner() && !board.isBoardFull()) {
        makePlayerMove(board);
        std::cout << "Plansza:" << std::endl;
        board.displayBoard();

        if (board.hasWinner() || board.isBoardFull())
            break;

        makeComputerMove(board);
        std::cout << "Plansza:" << std::endl;
        board.displayBoard();
    }

    if (board.hasWinner())
        std::cout << "Wygrał komputer (X)!" << std::endl;
    else
        std::cout << "Remis!" << std::endl;
}

#endif //KOLKOIKRZYZYK_KOLKOIKRZYZYK_H
