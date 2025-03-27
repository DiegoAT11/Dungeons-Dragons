#include <iostream>
using namespace std;

class Player {
private:
  string name;
  string race;
  float hp;
  int lp;
  Stack<Player> agamotto;
  bool usedAgamotto;
  friend class Game;

public:
  Player() : name(" "), race(" "), hp(), lp(), usedAgamotto(false) {}

  void setName(string _name) { this->name = _name; }

  void setRace(string _race) { this->race = _race; }

  void setHp(float _hp) { this->hp = _hp; }

  void setLp(int _lp) { this->lp = _lp; }

  int getLP() { return this->lp; }

  // Método para guardar el estado actual del jugador en el stack
  void agamottoEye() {
    if (!usedAgamotto) {
      agamotto.push(*this);
    } else {
      usedAgamotto = true;
    }
  }

  // Método para restaurar un estado previo del jugador desde el stack
  void useAgamottoEye() {
    cout << "Select a previous state to restore:" << endl;
    int stateNumber = 1;
    int choice;
    Stack<Player> tempStack;
    int agam_size = agamotto.size();

    while (!agamotto.is_empty()) {
      Player player = agamotto.pop();
      cout << stateNumber << ". " << player << endl;
      tempStack.push(player); // Guarda los elementos en una pila temporal
      stateNumber++;
    }

    cout << "Enter the number of the state to restore: ";
    cin >> choice;
    Player player;
    if (choice >= 1 && choice < stateNumber) {
      for (int i = agam_size; i >= 1; i--) {
        if (i == choice) {
          player = tempStack.pop();
          *this = player;
          this->agamotto.push(player);
          usedAgamotto = true;
        } else {
          this->agamotto.push(tempStack.pop());
        }
      }
    } else {
      cout << "Invalid choice. No state was restored." << endl;
    }
  }

// Sobrecarga del operador de inserción
  friend ostream &operator<<(ostream &salida, Player &p);
};

// Definición de la sobrecarga del operador de inserción
ostream &operator<<(ostream &salida, Player &p) {
  salida << p.name << " : " << p.race << " : " << p.hp << " : " << p.lp;
  return salida;
}
