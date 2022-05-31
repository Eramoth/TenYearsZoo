// QUESTIONS A POSER
// Gestion d'erreurs avec destruction
// destructeurs
// quand l'entité est kill, est-ce que les pointeurs y référant aussi ?
// ^^^ est-ce que la case de l'array le contenant se vide ?
// game function : vaut-il mieux les mettre dans zoo ?
// string/int input error handler
// achat animal : créer l'objet et vndre des copies ? créer juste les paramètres ?

// POSSIBLE DE RAJOUTER DES EVENTS/MODIF UN PEU DES TRUCS

/* actions possibles : 
    - [WIP] achat/vente animal
    - [DONE] achat nourriture
    - [WIP] achat/vente habitat
    - [DONE] passer au prochain tour (mois)
*/

/* évènements possibles :
    - [WIP] Grossesse
    - Naissance
    - Mort infantile
    - Fin de vie individu
    - Surpopulation
    - Maladie
*/

/* aléas exceptionnels (par mois)
   - Incendie, 1%, -1 habitat
   - Vol, 1%, -1 animal
   - Nuisibles, 20%, -10% graines
   - Viande avariée, 10%, -20% viande
*/

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "config.h"
#include "game.h"
#include "ianimal.h"
#include "zoo.h"

using namespace std;

int main()
{
    system("cls");
    // initialization
    Game* game = new Game();
    game->startGame();

    // turn loop

    while (game->getMonth() + game->getYear() * 12 <= LAST_MONTH + LAST_YEAR * 12)
    {
        cout << "\n----------------\n"
             << game->parseDate() << "\n"
             << endl;

        string update = game->getZoo()->monthlyUpdate();
        cout << update << endl;
        this_thread::sleep_for(chrono::seconds(3));
        game->menu(update);

        game->nextTurn();
    }
}