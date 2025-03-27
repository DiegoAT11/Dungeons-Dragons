class Mazmorra {
public:
  LinkedList<Monster> monsters;

  // Método para ordenar la lista de monstruos por puntos de vida (HP) de mayor a menor.
  void sort() {
    for (int i = 0; i < monsters.size(); i++) {
      for (int j = 0; j < monsters.size() - 1; j++) {
        Monster a = monsters.get(j);
        Monster b = monsters.get(j + 1);
        // Compara los puntos de vida (HP) de los monstruos
        if (a.getHP() < b.getHP()) {
          Monster temp = monsters.get(j + 1);
          monsters.set(j + 1, monsters.get(j));
          monsters.set(j, temp);
        }
      }
    }
  }
};
