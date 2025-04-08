# 📡 pipex

**pipex** est un projet qui consiste à implémenter un simulateur de pipeline entre des processus en utilisant les pipes Unix. L'objectif est de recréer le comportement de la commande `|` (pipe) dans un terminal, permettant ainsi de chaîner plusieurs commandes entre elles.

## 🛠️ Objectif

L'objectif de ce projet est de créer une application qui peut gérer l'exécution de plusieurs commandes dans un pipeline, où la sortie de chaque commande est envoyée en entrée à la commande suivante, à l'instar de l'utilisation de la commande `|` dans un shell.

## 🧩 Fonctionnalités Implémentées

- Le projet implémente un pipeline entre plusieurs commandes, permettant d'exécuter une commande après l'autre.
- La gestion des erreurs est incluse pour les cas de mauvais arguments, de fichiers inexistants ou de commandes invalides.
- Les processus sont gérés à l'aide des appels système Unix comme `fork()`, `exec()`, et `pipe()`.
- Le projet simule un comportement similaire à celui de `|` dans un shell classique.

## 🧪 Compilation et Utilisation

### Compilation

Le projet utilise un `Makefile` pour faciliter la compilation.

```bash
make
```

Pour nettoyer les fichiers objets :

```bash
make clean
```

Pour supprimer tous les fichiers compilés (objets + exécutable) :

```bash
make fclean
```

Pour recompiler le projet :

```bash
make re
```

### 📄 Utilisation

Le programme prend en charge deux fichiers d'entrée et les commandes à exécuter via un pipeline. Par exemple :

```bash
./pipex file1 cat wc -l file2
```
Ce programme va :

1. Lire `file1` comme entrée
2. Passer cette entrée à la commande `cat`
3. Passer la sortie de `cat` à `wc -l`
4. Écrire la sortie dans `file2`
