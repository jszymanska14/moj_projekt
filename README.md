# moj_projekt

Projekt "Gra w Kółko i Krzyżyk z Algorytmem MinMax"

Opis:
Ten projekt to implementacja popularnej gry w Kółko i Krzyżyk (Tic-Tac-Toe) z wykorzystaniem algorytmu MinMax i alfa-beta cięć do sterowania ruchami komputera. Gra jest napisana w języku C++ i jest przeznaczona do gry pomiędzy graczem a komputerem.

Funkcje:
Możliwość rozpoczęcia gry o różnych rozmiarach planszy i długości rzędu do wygranej.
Algorytm MinMax z alfa-beta cięciami dla przeciwnika komputera.
Wyświetlanie planszy w trakcie gry.
Rozpoznawanie zwycięstwa lub remisu.

Funkcja minmax():
• Wykorzystuje algorytm MinMax z alfa-beta cięciami do szukania optymalnego ruchu dla
kompuetera
• Rekurencyjnie przeszukuje drzewo możliwych ruchów, oceniając każdy z nich
• Parametry funkcji to aktualny stan planszy board, głębokość rekurencji depth, wartość alfa i beta dla
cięć alfa-beta (alpha i beta) oraz flaga wskazująca, czy ruch jest dla maksymalnego gracza
isMaxPlayer
• Jeśli osiągnięty jest warunek zakończenia rekurencji (wygrana, remis lub plansza niepełna),
zwracana jest odpowiednia wartość
• Dla maksymalnego gracza(komputera), przeszukiwane są wszystkie dostępne ruchy, a następnie
wybierany jest ruch o najwyższej wartości oceny
• Dla minimalnego gracza, postępowanie jest analogiczne, ale wybierany jest ruch o najni
• ższej wartości oceny
• Wykorzystywane są alfa-beta cięcia, aby przyspieszyć przeszukiwanie drzewa, eliminując
niepotrzebne gałęzie
