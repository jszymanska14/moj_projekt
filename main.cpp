#include <iostream>
#include <vector>
#include <limits>
#include "kolkoikrzyzyk.h"

using namespace std;

int main() {
    int boardSize, winLength;
    cout << "Podaj rozmiar planszy: ";
    cin >> boardSize;
    cout << "Podaj długość rzędu do wygranej: ";
    cin >> winLength;

    playGame(boardSize, winLength);

    return 0;
}
