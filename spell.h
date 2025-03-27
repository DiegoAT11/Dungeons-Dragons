#include <iostream>
using namespace std;

class Spell {
private:
  int index;
  string type;
  string name;
  int hpDice;
  int lpDice;
  friend class Game;

public:
  Spell() {} // Constructor vacío
  Spell(int index, string type, string name, int hpDice, int lpDice)
      : index(index), type(type), name(name), hpDice(hpDice), lpDice(lpDice) {}

  // Método de sobrecarga del operador de inserción
  friend ostream &operator<<(ostream &salida, Spell &s);
};

// Definición del método de sobrecarga del operador de inserción
ostream &operator<<(ostream &salida, Spell &s) {
  salida << s.index << " : " << s.type << " : " << s.name << " : " << s.hpDice
         << " : " << s.lpDice;
  return salida;
}