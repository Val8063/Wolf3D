# Wolf3D

Bienvenue sur le projet **Wolf3D** !  
Ce dépôt contient une version personnelle du jeu vidéo classique **Wolfenstein 3D**, adaptée et développée à des fins pédagogiques.  
Ce document vous guidera pour comprendre ce projet, même si vous n’avez pas de connaissances en programmation ou en jeux vidéo.

---

## Qu’est-ce que Wolfenstein 3D ?

Wolfenstein 3D est un jeu vidéo sorti en 1992, considéré comme l’un des premiers jeux de tir à la première personne (FPS).  
Vous incarnez un personnage vu à travers ses propres yeux, qui explore des labyrinthes, affronte des ennemis et tente de s’échapper d’un château.

---

## À propos de ce projet

Ce projet propose une **recréation du gameplay de Wolfenstein 3D** en utilisant des techniques de programmation modernes et pédagogiques.  
L’objectif est d’apprendre les bases du fonctionnement d’un moteur 3D simple et de découvrir comment on crée un jeu vidéo de ce type.

---

## Fonctionnalités principales

- **Vue à la première personne** : vous voyez l’environnement comme si vous étiez dans la peau du personnage.
- **Déplacement** : déplacez-vous dans des couloirs en 3D simulée.
- **Exploration de labyrinthes** : trouvez la sortie tout en évitant les obstacles.
- **Graphismes rétro** : les graphismes imitent le style pixelisé des années 90.
- **Interface simple** : le jeu se contrôle au clavier (flèches directionnelles, espace, etc.).

---

## Pour qui est fait ce projet ?

- Les personnes curieuses de comprendre les bases d’un moteur 3D.
- Les débutant(e)s en programmation qui souhaitent voir un exemple concret de projet.
- Les nostalgiques des jeux vidéo classiques.
- Toute personne intéressée par la création de jeux vidéo simples.

---

## Structure du projet

Voici une explication simple des principaux dossiers/fichiers du projet :

- **src/** : le code source principal du jeu.
- **assets/** : contient les images et sons utilisés dans le jeu.
- **README.md** : ce fichier d’introduction.
- **Makefile** : fichier permettant de compiler (transformer le code en programme exécutable).

---

## Comment exécuter le jeu ?

Aucune connaissance technique poussée n’est requise, mais il faut suivre quelques étapes de base :

1. **Télécharger le projet**  
   Cliquez sur le bouton vert "Code" puis "Download ZIP" ou utilisez Git si vous connaissez.

2. **Installer les prérequis**  
   Ce projet nécessite généralement un ordinateur sous Windows, Linux ou Mac avec un compilateur C (ex: gcc) et la bibliothèque graphique SDL2.

3. **Compiler le projet**  
   Ouvrez un terminal/console à l’intérieur du dossier du projet et tapez :
   ```
   make
   ```
   Cela va générer un fichier exécutable.

4. **Lancer le jeu**  
   Sur la console, tapez :
   ```
   ./wolf3d
   ```
   Le jeu devrait s’ouvrir dans une nouvelle fenêtre.

---

## Questions courantes

- **Ai-je besoin de savoir programmer ?**  
  Non, ce guide est fait pour les novices. Suivez simplement les étapes ci-dessus.

- **Sur quel système d’exploitation puis-je jouer ?**  
  Sur la plupart des ordinateurs (Windows, Linux, Mac), à condition d’avoir les prérequis installés.

- **Puis-je modifier le jeu ?**  
  Oui, mais il faudra quelques connaissances en langage C.

---

## Pour aller plus loin

Si vous souhaitez en apprendre plus :

- Sur le fonctionnement des moteurs 3D simples (technique du « raycasting » utilisée dans Wolfenstein 3D)
- Sur la programmation en langage C
- Sur la création de jeux vidéo

N’hésitez pas à explorer le code source, à lire les commentaires et à rechercher des tutoriels en ligne.

---

## Remerciements

- Le jeu original Wolfenstein 3D, développé par id Software.
- Les nombreux guides et tutoriels disponibles en ligne pour apprendre à programmer.

---

**Bon jeu et bonne découverte !**
