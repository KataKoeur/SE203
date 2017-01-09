# SE203 Dépôt Git

Bienvenue sur le gitLab de Erwan CHERIAUX !

# Makefile (pour le 25/11/2016)

Consultable dans le dossier exercice_Makefile/
Ecriture d'un makefile avec Variables, Règles et dépendances.

# Exercises sur l'assembleur (pour le 09/12/2016)

Consultable dans le dossier exos_assembleur/
Traduction de 2 codes C en assembleur ARM.

# Exercices sur l'analyse d'une compilation C (pour le 13/12/2016)

Consultable dans le dossier exos_c/

# TD : Mise en œuvre d'une application embarquée

Consultable dans le dossier bare-metal/

Vous allez développer sur des cartes FRDM-KL46Z. Ces cartes sont basées sur un microcontrôleur de Freescale, le MKL46Z256VLL4. Un microcontrôleur est un circuit intégré rassemblant un coeur de processeur ainsi que plusieurs périphériques usuels. En l'occurrence le coeur de processeur est un ARM Cortex M0+ associé à plusieurs périphériques.

## Introduction

Mise en place du dossier de travail.
Création d'un Makefile, d'un .gdbinit et d'un répertoire regroupant toute la documentation.

Il faut penser à ajouter la ligne "set auto-load safe-path /" dans le son .gdbinit local pour retirer la protection par défaut.

## Création d'un executable

Création d'un linker script charger de réaliser le mapping mémoire.
On place tout le code dans la zone mémoire RAMH (0x20000000).
Pour vérifier que notre programme est logé au bon endroit, il faut compiler le programme en 2 temps (les objets puis l'exécutable) pour ensuite faire un objdump -h. Penser à ajouter le flag -nostdlib lors de l'édition de liens.

Utilisation d'un crt0.s pour initialiser le pointeur de pile (sp) à l'adresse la plus haute de la zone mémoire RAML et mettre à 0 la BSS.
Sur ARM, le pointeur de pile est full descending. Cela signifie que le pointeur va se décrémenter de 4 puis ajouter la nouvelle donnée dans la pile.
