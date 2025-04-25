#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 10;

enum ItemType { EMPTY, COIN, ENEMY, HP, DEFENSE, ATTACK };

struct Item {
    ItemType type;
    char symbol;
};

class Player {
public:
    int x, y;
    int hp = 10, attack = 1, defense = 0, coins = 0;

    Player(int x = 0, int y = 0) : x(x), y(y) {}

    void move(char dir) {
        switch (dir) {
        case 'w': if (x > 0) x--; break;
        case 's': if (x < SIZE - 1) x++; break;
        case 'a': if (y > 0) y--; break;
        case 'd': if (y < SIZE - 1) y++; break;
        }
    }
};

class Game {
private:
    vector<vector<Item>> field;
    Player player;

public:
    Game() : field(SIZE, vector<Item>(SIZE, { EMPTY, '.' })), player(0, 0) {
        srand(time(0));
        placeItems(COIN, 'C', 5);
        placeItems(ENEMY, 'E', 5);
        placeItems(HP, 'H', 3);
        placeItems(DEFENSE, 'D', 3);
        placeItems(ATTACK, 'A', 3);
    }

    void placeItems(ItemType type, char symbol, int count) {
        while (count > 0) {
            int i = rand() % SIZE;
            int j = rand() % SIZE;
            if (field[i][j].type == EMPTY && (i != 0 || j != 0)) {
                field[i][j] = { type, symbol };
                count--;
            }
        }
    }

    void draw() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i == player.x && j == player.y) cout << 'P';
                else cout << field[i][j].symbol;
            }
            cout << endl;
        }
        cout << "HP: " << player.hp << " ATK: " << player.attack << " DEF: " << player.defense << " COINS: " << player.coins << endl;
    }

    void play() {
        while (player.hp > 0) {
            draw();
            cout << "Move (w/a/s/d): ";
            char move;
            cin >> move;
            player.move(move);
            interact();
        }
        cout << "Game Over!\n";
    }

    void interact() {
        Item& item = field[player.x][player.y];
        switch (item.type) {
        case COIN: player.coins++; break;
        case ENEMY: {
            int damage = max(1, 2 - player.defense);
            player.hp -= damage;
            cout << "Attacked by enemy! Lost " << damage << " HP!\n";
            break;
        }
        case HP: player.hp += 2; break;
        case DEFENSE: player.defense++; break;
        case ATTACK: player.attack++; break;
        default: break;
        }
        item = { EMPTY, '.' };
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
