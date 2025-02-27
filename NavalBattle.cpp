#include <iostream>
#include <cstdlib>
#include <ctime>

// Размер игрового поля
const int FIELD_SIZE = 10;

// Глобальные массивы для игровых полей
bool field_1[FIELD_SIZE][FIELD_SIZE];
bool field_2[FIELD_SIZE][FIELD_SIZE];

// Функция для очистки игрового поля
void clearField(bool field[FIELD_SIZE][FIELD_SIZE]) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field[i][j] = false; // false означает пустую клетку
        }
    }
}

// Функция для отображения игрового поля
void displayField(bool field[FIELD_SIZE][FIELD_SIZE], int player) {
    std::cout << "Player " << player << "'s field:\n";
    std::cout << "  ";
    for (int i = 0; i < FIELD_SIZE; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < FIELD_SIZE; i++) {
        std::cout << i << " ";
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j]) {
                std::cout << "X "; // X означает корабль
            } else {
                std::cout << ". "; // . означает пустую клетку
            }
        }
        std::cout << "\n";
    }
}

// Функция для размещения одного корабля
bool placeShip(bool field[FIELD_SIZE][FIELD_SIZE], int size, int x1, int y1, int x2, int y2) {
    // Проверка, можно ли разместить корабль по заданным координатам
    if (x1 == x2) { // Горизонтальное размещение
        if (y2 - y1 != size - 1 || y2 >= FIELD_SIZE) {
            std::cout << "Invalid coordinates for horizontal placement.\n";
            return false;
        }
        for (int i = y1; i <= y2; i++) {
            if (field[x1][i]) {
                std::cout << "Cannot place ship here; cell is occupied.\n";
                return false;
            }
        }
        for (int i = y1; i <= y2; i++) {
            field[x1][i] = true;
        }
    } else if (y1 == y2) { // Вертикальное размещение
        if (x2 - x1 != size - 1 || x2 >= FIELD_SIZE) {
            std::cout << "Invalid coordinates for vertical placement.\n";
            return false;
        }
        for (int i = x1; i <= x2; i++) {
            if (field[i][y1]) {
                std::cout << "Cannot place ship here; cell is occupied.\n";
                return false;
            }
        }
        for (int i = x1; i <= x2; i++) {
            field[i][y1] = true;
        }
    } else {
        std::cout << "Diagonal placement is not allowed.\n";
        return false;
    }
    return true;
}

// Функция для размещения всех кораблей
void placeAllShips(bool field[FIELD_SIZE][FIELD_SIZE], int player) {
    int ships[] = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4}; // Размеры кораблей
    int count = sizeof(ships) / sizeof(ships[0]);
    
    std::cout << "Player " << player << ", place your ships:\n";
    
    for (int i = 0; i < count; i++) {
        int size = ships[i];
        int x1, y1, x2, y2;
        
        if (size == 1) {
            std::cout << "Enter coordinates for a ship of size " << size << " (e.g., 3 4): ";
            std::cin >> x1 >> y1;
            x2 = x1; y2 = y1;
        } else {
            std::cout << "Enter start and end coordinates for a ship of size " << size << " (e.g., 3 4–3 6): ";
            std::cin >> x1 >> y1 >> x2 >> y2;
        }
        
        while (!placeShip(field, size, x1, y2, x2, y1)) {
            if (size == 1) {
                std::cout << "Enter coordinates for a ship of size " << size << " (e.g., 3 4): ";
                std::cin >> x1 >> y1;
                x2 = x1; y2 = y1;
            } else {
                std::cout << "Enter start and end coordinates for a ship of size " << size << " (e.g., 3 4–3 6): ";
                std::cin >> x1 >> y1 >> x2 >> y2;
            }
        }
    }
    
    displayField(field, player);
}

// Функция для выстрела по координатам
bool shoot(bool field[FIELD_SIZE][FIELD_SIZE], int x, int y) {
    if (field[x][y]) {
        field[x][y] = false; // Уничтожение корабля
        std::cout << "Hit!\n";
        return true;
    } else {
        std::cout << "Miss!\n";
        return false;
    }
}

// Функция для проверки победы
bool checkWin(bool field[FIELD_SIZE][FIELD_SIZE]) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j]) {
                return false; // Есть ещё корабли
            }
        }
    }
    return true; // Все корабли уничтожены
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел
    
    clearField(field_1);
    clearField(field_2);
    
    placeAllShips(field_1, 1);
    placeAllShips(field_2, 2);
    
    int currentPlayer = 1;
    while (true) {
        std::cout << "\nPlayer " << currentPlayer << "'s turn:\n";
        int x, y;
        std::cout << "Enter coordinates to shoot (e.g., 3 4): ";
        std::cin >> x >> y;
        
        if (currentPlayer == 1) {
            if (shoot(field_2, x, y)) {
                // Если попал, то снова ходит текущий игрок
                if (checkWin(field_2)) {
                    std::cout << "Player 1 wins!\n";
                    break;
                }
            } else {
                currentPlayer = 2; // Смена игрока
            }
        } else {
            if (shoot(field_1, x, y)) {
                if (checkWin(field_1)) {
                    std::cout << "Player 2 wins!\n";
                    break;
                }
            } else {
                currentPlayer = 1; // Смена игрока
            }
        }
    }
    
    return 0;
}
