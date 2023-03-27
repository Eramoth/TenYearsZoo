#  Zoo Simulator 3000
Axelle Refeyton & Yohan Velay

## Avertissement

Ce repo est un clone d'un ancien projet effectué pendant notre première année d'étude en informatique. Ce projet a dû être réalisé dans un temps très restreint. Il ne représente donc pas le niveau de code de ses créateurs.

## Comment lancer le jeu

Le jeu fonctionne principalement sur windows (en utilisant la commande de clear associer "cls").
Un utilisateur sur linux risque de voir "Command not found" 

Pour la compilation il suffit d'utiliser `g++` et de lancer le `.exe` qui en resulte

```
g++ *.cpp -o ZooSimulator3000
.\ZooSimulator3000.exe
```

## Consigne

Le but etais de créer un simulateur de gestion de zoo sur 10 ans qui se joue en tour par tour (chaque tour représentant 1 mois.)

Chaque mois le joueur peut effectuer 6 actions :
- 1. Acheter un animal
- 2. Vendre un animal
- 3. Acheter de la nourriture
- 4. Acheter des cages
- 5. Vendre des cages
- 6. Terminer le tours

En plus de ces actions, chaque mois comprends des evenements habituels (comme la reception de visiteurs, ..), des evenements récurrents (naissance, fin de vie d'un animal, etc..) et des evenements particuliers (Incendie, Vol et autre..)

## Ressources

- Trello: https://trello.com/invite/b/EWATeXSr/ec59764912430d9722bd5ccb687ec27f/tenyearszoo

- Repo: https://git.ytrack.learn.ynov.com/AREFYTON/TenYearsZoo
