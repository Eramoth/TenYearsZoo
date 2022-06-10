// QUESTIONS A POSER
// Gestion d'erreurs avec destruction
// destructeurs
// quand l'entité est kill, est-ce que les pointeurs y référant aussi ?
// ^^^ est-ce que la case de l'array le contenant se vide ?
// game function : vaut-il mieux les mettre dans zoo ?
// string/int input error handler
// achat animal : créer l'objet et vendre des copies ? créer juste les paramètres ?

// POSSIBLE DE RAJOUTER DES EVENTS/MODIF UN PEU DES TRUCS

/* actions possibles : 
    - [DONE] achat/vente animal
    - [DONE] achat nourriture
    - [DONE] achat/vente habitat
    - [DONE] passer au prochain tour (mois)
*/

/* évènements possibles :
    - [WIP] Grossesse
    - Naissance
    - Mort infantile
    - [DONE] Fin de vie individu
    - [WIP] Surpopulation
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
        cout << "\n----------------\n" << game->parseDate() << "\n" << endl;
        string update;
        if (game->getMonth() == STARTING_MONTH && game->getYear() == STARTING_YEAR)
        {
            // initialization
        }
        else
        {
            // update = game->getZoo()->monthlyUpdate(game->getMonth());
            update = game->monthlyUpdate();
            cout << update << endl;
            this_thread::sleep_for(chrono::seconds(3));
        }
        game->menu(update);

        game->nextTurn();
    }
    cout << "Congratulations ! Your zoo didn't blew up ! Well done !" << endl
    << "Do you wanna retry ?" << endl;
    int retry;
    cin >> retry;
    // do something
}