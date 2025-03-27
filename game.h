#include "list.h"
#include "monster.h"
#include "player.h"
#include "spell.h"
#include "mazmorra.h"
#include "AVL.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Game {
private:
  LinkedList<Monster> monster;
  LinkedList<Mazmorra> dungeon;
  LinkedList<Spell> spell;
  LinkedList<Player> players;
  AVL<Monster> defeatedMonsters;
  int D20 = rand() % 20 + 1;
  int totalMonsters = 0;

public:
  //Método para cargar monstruos desde un archivo CSV
  void cargaMonsters(LinkedList<Monster> &monsters) {
    string linea, token;
    fstream archivo("monsters.csv", ios::in);
    if (archivo.is_open()) {
      getline(archivo, linea);

      while (getline(archivo, linea)) {
        stringstream strdata(linea);
        string name;
        getline(strdata, name, ',');
        string cr;
        getline(strdata, cr, ',');
        string type;
        getline(strdata, type, ',');
        string size;
        getline(strdata, size, ',');
        string ac;
        getline(strdata, ac, ',');
        string hp;
        getline(strdata, hp, ',');
        string align;
        getline(strdata, align, ',');

        Monster m(name, stod(cr), type, size, stoi(ac), stof(hp), align);
        monsters.addLast(m);
      }
    } else {
      cout << "File not found" << endl;
    }
  }

  //Método para cargar hechizos/habilidades desde un archivo CSV
  void cargaSpells(LinkedList<Spell> &spells) {
    string linea, token;
    fstream archivo("spells.csv", ios::in);
    if (archivo.is_open()) {
      getline(archivo, linea);

      while (getline(archivo, linea)) {
        stringstream strdata(linea);
        string index;
        getline(strdata, index, ',');
        string type;
        getline(strdata, type, ',');
        string name;
        getline(strdata, name, ',');
        string hpDice;
        getline(strdata, hpDice, ',');
        string lpDice;
        getline(strdata, lpDice, ',');

        Spell s(stoi(index), type, name, stoi(hpDice), stoi(lpDice));
        spells.addLast(s);
      }
    } else {
      cout << "File not found" << endl;
    }
  }

  //Método para crear un calabozo con un número aleaotorio de mazmorras, cada una con un número aleatorio de monstruos
  void createDungeon(LinkedList<Monster> &monsters) { 
    srand(time(0));
    for (int i = 0; i < D20; i++) {
      int D6 = rand() % 6 + 1;
      Mazmorra mazmorra;
      for (int j = 0; j < D6; j++) {
        int index = rand() % monsters.size();
        mazmorra.monsters.addLast(monsters.get(index));
      }
      mazmorra.sort();
      dungeon.addLast(mazmorra);
      totalMonsters += mazmorra.monsters.size(); 
    }
  }

  //Método para iniciar y correr el juego
  void gameStart() {
    Player player;
    cargaMonsters(monster);
    cargaSpells(spell);
    createDungeon(monster);
    int posTotal = 0;
    int monsterDice;
    int playerDice;
    int gameOption;
    float damage;
    int healing;
    float monsterLife;
    int spellSelect;
    float newHP = 0.0;
    int newLP = 0;
    char answer;

    cout << "\nWELCOME TO DUNGEONS & DRAGONS" << endl;
    
    //Crear jugadores
    for (int i = 0; i < 3; i++) {
      cout << "\nEnter player name: ";
      cin >> player.name;

      // Asignar puntos de vida y puntos de ataque iniciales aleatorios
      player.lp = 8 + rand() % 13;
      player.hp = 8 + rand() % 13;

      int type = 0;
      while (type < 1 || type > 3) {
        cout << "\nEnter your race: " << endl;
        cout << "\n1 - Elf"
             << "\n2 - Human"
             << "\n3 - Dwarf\n"
             << endl;
        cin >> type;
        if (type < 1 || type > 3) {
          cout << "Invalid option. Try Again" << endl;
        }
      }

      if (type == 1) {
        player.setRace("Elf");
      } else if (type == 2) {
        player.setRace("Human");
      } else if (type == 3) {
        player.setRace("Dwarf");
      }

      cout << "\nWelcome to the game " << player.name << " the " << player.race << endl;
      players.addLast(player);
    }

    cout << "\nTHE GAME HAS STARTED!!" << endl;
    players.print();

    int numDungeons = D20; // Numero total de mazmorras
    cout << "\nNumber of mazmorras in the dungeon: " << numDungeons << endl;
    
    // Bucle principal del juego
    while ((players.get(0).lp > 0 || players.get(1).lp > 0 || players.get(2).lp > 0) && defeatedMonsters.length() < totalMonsters) {
      int moveDice = rand() % numDungeons + 1;
      posTotal += moveDice;
      posTotal = posTotal % numDungeons; // Para no sobrepasar el número de mazmorras
      cout << "\nThe group of players have rolled the dice" << endl;
      cout << "They moved " << moveDice << " spaces" << endl;
      cout << "They are in Mazmorra Number " << posTotal + 1 << endl;

      // Obtener y mostrar la mazmorra actual
      Mazmorra currentMazmorra = dungeon.get(posTotal);
      cout << "\nMazmorra size: " << currentMazmorra.monsters.size() << endl;
      currentMazmorra.monsters.print();

      // Iterar sobre los monstruos en la mazmorra actual
      for (int i = 0; i < currentMazmorra.monsters.size(); i++) {
        Monster currentMonster = currentMazmorra.monsters.get(i);
        // Elige aleatoriamente un jugador para luchar contra el monstruo
        Player currentPlayer;
        int playerIndex = rand() % players.size();
        currentPlayer = players.get(playerIndex);
        currentPlayer.agamottoEye();

        // Verificar si el jugador actual está muerto y seleccionar otro si es necesario
        if ((currentPlayer.lp <= 0) && (players.get(0).lp > 0 || players.get(1).lp > 0 || players.get(2).lp > 0)) {
          do {
            playerIndex = rand() % players.size();
            currentPlayer = players.get(playerIndex);
            currentPlayer.agamottoEye();
          } while (currentPlayer.lp <= 0);
        }

        // Enfrentamiento entre el jugador y el monstruo 
        while ((currentMonster.hp > 0) && (currentPlayer.lp > 0)) {
          // Tirar un dado de 10 caras para el daño del monstruo
          srand(time(0));
          int D10 = rand() % 10 + 1;
          monsterDice = D10;
          cout << "\nThe monster " << currentMonster.name << " has attacked you!!" << endl;
          cout << "Monster damage: " << monsterDice << endl;
          currentPlayer.lp -= monsterDice;
          cout << "Current player: " << currentPlayer.name << endl;
          cout << "Your life points have decreased" << endl;

          // Checar si el jugador ha muerto
          if (currentPlayer.lp <= 0) {
            currentPlayer.setLp(0);
            cout << "Current lp: " << currentPlayer.lp << endl;
            cout << currentPlayer.name << " have died" << endl;

            // Preguntar si se desea usar el ojo de Agamotto si el jugador no lo ha usado
            if (currentPlayer.usedAgamotto == false) {
              cout << "Would you like to use Agomotto's Eye? [Y]/[N]:" << endl;
              cin >> answer;
              answer = tolower(answer);

              // Dar la opción de usar ojo de Agamoto o pasar al siguiente jugador cuando un jugador muere
              if (answer == 'y') {
                currentPlayer.useAgamottoEye();
                cout << "\n" << currentPlayer.name << " has used his Agamotto's Eye" << endl;
                cout << "His life points and hit points have been restored" << endl;
                cout << "Life points: " << currentPlayer.lp << " Hit points: " << currentPlayer.hp << endl;
                players.set(playerIndex, currentPlayer);
              } else {
                players.set(playerIndex, currentPlayer);
                // Seleccionar otro jugador si el actual está muerto
                if ((currentPlayer.lp <= 0) && (players.get(0).lp > 0 || players.get(1).lp > 0 ||
                     players.get(2).lp > 0)) {
                  do {
                    playerIndex = rand() % players.size();
                    currentPlayer = players.get(playerIndex);
                    currentPlayer.agamottoEye();
                  } while (currentPlayer.lp <= 0);
                }
              }
            }
            players.set(playerIndex, currentPlayer);
            // Seleccionar otro jugador si el actual está muerto
            if ((currentPlayer.lp <= 0) && (players.get(0).lp > 0 || players.get(1).lp > 0 ||
                 players.get(2).lp > 0)) {
              do {
                playerIndex = rand() % players.size();
                currentPlayer = players.get(playerIndex);
                currentPlayer.agamottoEye();
              } while (currentPlayer.lp <= 0);
            }
          } else {
            players.set(playerIndex, currentPlayer);
            cout << "Current Player lp: " << currentPlayer.lp << endl;
          }

          //Si el jugador actual está vivo, es su turno de atacar
          if (currentPlayer.lp > 0) {
            cout << "\n------------------------" << endl;
            cout << "¡Now it's your turn " << currentPlayer.name << " !" << endl;
            playerDice = rand() % 15 + 1;
            cout << "1. Attack cycle" << endl;
            cout << "2. Use spell or hability" << endl;
            cout << "Choose an option: " << endl;
            cin >> gameOption;

            // Switch para manejar las opciones de ataque del jugador
            switch (gameOption) {
              case 1: {
                // Ataque normal
                damage = currentPlayer.hp * playerDice;
                // Actualizar vida del monstruo
                cout << "\nLife of monster was: " << currentMonster.hp << endl;
                monsterLife = currentMonster.hp - damage;
                if (monsterLife < 0) {
                  monsterLife = 0;
                }
  
                currentMonster.setHP(monsterLife);
                currentMazmorra.monsters.set(i, currentMonster);
                dungeon.set(posTotal, currentMazmorra);
                cout << "Dice result: " << playerDice << endl;
                cout << "You made a damage of: " << damage << endl;
                cout << "Current life of monster is: " << monsterLife << endl;
  
                // Si el monstruo ha muerto se agrega al AVL y se aumenta el HP del jugador
                if (currentMonster.getHP() == 0) {
                  defeatedMonsters.insert(currentMonster);
                  cout << "The monster has died" << endl;
                  newHP = currentPlayer.hp + (currentMonster.cr / 10);
                  currentPlayer.setHp(newHP);
                  cout << "New hp: " << currentPlayer.hp << endl;
                  players.set(playerIndex, currentPlayer);
                }
                break;
              } // Finaliza Case 1
              case 2: {
                // Usar hechizo o habilidad
                cout << "List of spells and habilities you have: " << endl;
                spell.print();
                spellSelect = 0;
                while (spellSelect != -1) {
                  damage = healing = 0;
                  cout << "Select one of the spells or habilities: " << endl;
                  cin >> spellSelect;
  
                  if (spellSelect > 0 && spellSelect <= 15) {
                    cout << "selection: " << spellSelect << endl;
                    if (spell.get(spellSelect - 1).type == "hechizo") {
                      // Daño por hechizo
                      damage = (spell.get(spellSelect - 1).hpDice) * playerDice;
                      cout << "Dice result: " << playerDice << endl;
                      cout << "Damage done: " << damage << endl;
                    } else if (spell.get(spellSelect - 1).type == "habilidad") {
                      // Curación por habilidad
                      healing = (spell.get(spellSelect - 1).lpDice) * playerDice;
                      cout << "Dice result: " << playerDice << endl;
                      cout << "Life recovery: " << healing << endl;
                      cout << "Previous life points: " << currentPlayer.lp << endl;
                      newLP = currentPlayer.lp + healing;
                      currentPlayer.setLp(newLP);
                      cout << "New life points: " << currentPlayer.lp << endl;
                      players.set(playerIndex, currentPlayer);
                    }
  
                    // Actualizar vida del monstruo
                    cout << "Life of monster was: " << currentMonster.hp << endl;
                    monsterLife = currentMonster.hp - damage;
                    if (monsterLife < 0) {
                      monsterLife = 0;
                    }
  
                    currentMonster.setHP(monsterLife);
                    currentMazmorra.monsters.set(i, currentMonster);
                    dungeon.set(posTotal, currentMazmorra);
                    cout << "You made a damage of: " << damage << endl;
                    cout << "Current life of monster is: " << monsterLife << endl;
  
                    // Si el monstruo ha muerto se agrega al AVL y se aumenta el HP del jugador
                    if (currentMonster.getHP() == 0) {
                      defeatedMonsters.insert(currentMonster);
                      cout << "The monster has died" << endl;
                      newHP = currentPlayer.hp + (currentMonster.cr / 10);
                      currentPlayer.setHp(newHP);
                      cout << "New hp: " << currentPlayer.hp << endl;
                      players.set(playerIndex, currentPlayer);
                    }
                    break;
                  }
                }
              } // Finaliza Case 2
            } // Finaliza switch
          } // Finaliza la condición if que nos indica que si el jugador actual está vivo, es su turno de atacar
        } // Finaliza el bucle while que controla el enfrentamiento entre el jugador y el monstruo 
      } // Finaliza el bucle for que itera sobre los monstruos en la mazmorra actual
    } // Finaliza el bucle (while) principal del juego

    //Fin del juego
    cout << "\nTHE GAME HAS END!!!" << endl;

    //Mensaje sobre si los jugadores han ganado o perdido la partida
    if(defeatedMonsters.length() == totalMonsters){
      cout << "\nCongratulations, you have defeated all the monsters!!!" << endl;
    } else{
      cout << "\nSorry :(, you have been defeated. Good luck next time!" << endl;
    }

    //Resumen del desempeño de los jugadores
    cout << "\nHere is a resume of your performance:  " << endl;
    players.print();
    for (int i = 0; i < players.size(); i++) {
      if(players.get(i).usedAgamotto == true){
        cout << "\n" << players.get(i).name << " used the Agamotto Eye" << endl;
      }
      else{
        cout << "\n" << players.get(i).name << " didn't use the Agamotto Eye" << endl;
      }
    }

    // Se imprimen los estados guardados en el "Ojo de Agamotto" de cada jugador 
    cout << "\nAgamotto of " << players.get(0).name << endl;
    players.get(0).agamotto.print();
    cout << "\nAgamotto of " << players.get(1).name << endl;
    players.get(1).agamotto.print();
    cout << "\nAgamotto of " << players.get(2).name << endl;
    players.get(2).agamotto.print();

    // Se imprimen todos los monstruos derrotados (ordenados en orden alfabético)
    cout << "\n DEFEATED MONSTERS " << endl;
    cout << " Number of defeated monsters: " << defeatedMonsters.length() << endl;
    cout << " : ";
    defeatedMonsters.inOrden();

    // Se imprime el estatus del calabozo, de cada mazmorra, y cada monstruo
    cout << "\nMAZMORRAS STATUS " << endl;
    for (int i = 0; i < dungeon.size(); i++) {
      cout << "----------------------------------------" << endl;
      cout << "Number of mazmorra: " << 1 + i << endl;
      dungeon.get(i).monsters.print();
    }
  } // Acaba game start
};
