#include <iostream>
using namespace std;

class Monster {
private:
  string name, type, size, align;
  int ac;
  float hp;
  double cr;
  friend class Game;

public:
  Monster() {} // Constructor vacío
  Monster(string name, double cr, string type, string size, int ac, float hp,
          string align)
      : name(name), cr(cr), type(type), size(size), ac(ac), hp(hp),
        align(align) {}

  // Devuelve el nombre del monstruo
  string getName() { return name; }

  // Establece los puntos de vida del monstruo
  void setHP(float newHP) { hp = newHP; }

  // Obtiene los puntos de vida actuales del monstruo
  float getHP() { return hp; }

  // Sobrecarga del operador '<' para comparar monstruos por nombre (const)
  bool operator<(const Monster &other) const { return this->name < other.name; }

  // Sobrecarga del operador '>' para comparar monstruos por nombre (const)
  bool operator>(const Monster &other) const { return this->name > other.name; }

   // Sobrecarga del operador de inserción
  friend ostream &operator<<(ostream &salida, Monster &m);
};

// Definición de la sobrecarga del operador de inserción
ostream &operator<<(ostream &salida, Monster &m) {
  salida << m.name << " : " << m.cr << " : " << m.type << " : " << m.size
         << " : " << m.ac << " : " << m.hp << " : " << m.align << endl;
  return salida;
}
