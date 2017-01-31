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

Création d'un linker script chargé de réaliser le mapping mémoire.
On place tout le code dans la zone mémoire RAMH (0x20000000).
Pour vérifier que notre programme est logé au bon endroit, il faut compiler le programme en 2 temps (les objets puis l'exécutable) pour ensuite faire un objdump -h. Penser à ajouter le flag -nostdlib lors de l'édition de liens.

Utilisation d'un crt0.s pour initialiser le pointeur de pile (sp) à l'adresse la plus haute de la zone mémoire RAML et mettre à 0 la BSS.
Sur ARM, le pointeur de pile est full descending. Cela signifie que le pointeur va se décrémenter de 4 puis ajouter la nouvelle donnée dans la pile.

# Utilisation des LEDs

Pour utiliser un périphérique tel que les LEDs, il faut:
- Activer l'horloge de leurs ports
- Configurer leurs broches en GPIO (mode entrée/sortie)
- Configurer leurs broches en sortie (car ce sont des LEDs)
- Agire sur leurs broches de sorte pour modifier leurs valeurs

Les LEDs s'allument à 0 et s'éteignent à 1.
- LED verte: port D, broche 5
- LED rouge: port E, broche 29

On ne peut pour l'instant pas lancer le programme sont mettre de breakpoint.

# Horloge

Ajout d'un fichier objet magique qui active les horloges et permet de lancer le programme sans breakpoint.

# UART

Calcule de l'oversampling:

   Oversampling = (MGCPLLCLK/2)/(SBR * (OSR+1))

avec  MGCPLLCLK/2  = 24MHz
      Oversampling = 115200

Les deux meilleurs jeux de donnée pour SBR et OSR sont:

- SBR = 7  et OSR = 28
- SBR = 29 et OSR = 6

* Voir Oversampling.ods

Dans les 2 cas, on obtient un Oversampling de 118226.601.
Ce qui est bien une valeur comprise entre 115200 et 118656 (avec 3%)

La fonction uart_putchar() fonctionne bien.
La fonction uart_getchar() fonctionne bien tant que l'on ne lui envoie pas plusieurs caracteres en même temps.
La fonction uart_puts() fonctionne très bien
La fonction uart_gets() fonctionne très bien, néanmoins, le programme se bloque lorsque l'on n'envoie pas le bon nombre de caractères (variable size).

Effectivement, le programme reste bloqué sur l'attente que le buffer de réception soit plein.
De plus, il faut bien prendre en compte que CuteCom envoie par défaut un retour chariot (\n) qui compte comme un caractère dans la chaine récupérée.

Le test checksum.py à été validé !
Pour vérifier cela, il suffit de lancer le programme en continu (c) sur la carte.
Il faut ensuite lancer le script python checksum.
Enfin, il faut afficher la variable sum dans gdb afin de constater que la valeur est la même que celle retourner par le script python.
HOURAAA!!!

# Matrice de LEDs

Pour brancher correctement la matrice de LEDs sur le controleur DM163, il faut veuiller à mettre le pin 1 de la matrice de LEDs sur le pin 1 BLEUE du controleur DM163.

Remarque: une fois toutes les lignes activées, il suffit de modifier la variable rgb_color et de l'appliquer à une seule ligne pour que toutes les autres lignes prennent en compte la modification.

Pour la partie test_static_image, l'image obtenue est en mirroire de l'image du TP. Je dois donc afficher les lignes dans l'ordre inverse pour obtenir l'image à l'identique.

# IRQ

Il faut faire pointer VTOR sur notre table de vecteur pour redéfinir nos propres handlers.
Il faut cependant désactiver les interruptions de la NMI qui a une trop grande priorité par rapport aux autre interruptions.
Pour cela, nous vérifions que les octets suivants sont bien réécrits dans la section flash_config;

ffffffff ffffffff ffffffff fefbffff

Pour pouvoir déclencher une interruption, il faut aligner la table des vecteurs avec une adresse contenant 7 zéros en bit de poids faible.
Cela est indispensable car les 7 premiers bits de VTOR sont réservés. Pour cela on ajoute à notre table des vecteurs:

__attribute__((aligned(256)))

L'interruption du bouton SW1 appelle le handler PORTA_IRQHandler au lieu du handler PORTCD_IRQHandler... malgré l'activation du bit 31eme handler.
Le problème est maintenant résolu, il y avait un élément en trop dans la table des vecteurs.

# UART + IRQ + LED !

On souhaite avoir un oversampling de 38400.
On calcule donc les valeurs suivantes:

- OSR = 24 et SBR = 25

La lecture des 3 fichiers se fait sans problème avec la commande cat one_frame.bin > /dev/ttyACM0:

- many_frames.bin = Hello World !
- final.bin       = Bravo ! La suite est sur http://sen.enst.fr/cc2

J'ai toutefois remarqué que certaine LED change d'état après un certain temps allumé. Cela est sûrement dû au fait que la carte recois du bruis sur le port série et cela se traduit en une modification de l'objet global qui est ensuite affiché sur la matrice.

# Timers

Le PIT fonctionne correctement, on obtient différentes fréquences d'intérruptions avec les valeurs suivantes dans le registre PIT_LDVAL0:

freq = 1Hz,   reg = 0x016e3600
freq = 70Hz,  reg = 0x00053b49
freq = 560Hz, reg = 0x0000a769 (soit 70Hz * 8)

Je trouve que la fréquence de 70Hz n'est pas suffisante pour afficher correctement les animations sur la matrice de LED.
Cela n'est pourtant pas de sens puisque 24 images par seconde devraient amplement suffire. Avec 70 images par seconde, on est bien au-dessus de la limite.
J'ai constaté avec cutecom que certains octets ne sont pas lus par l'Uart, ce qui décale tout !
Il faudrait prioriser les interruptions de l'Uart sur ceux du PIT.

Le problème venait bien des priorités non respecté. Cela fonctionne beaucoup mieux.
Reste encore le problème de l'affichage car la dernière ligne affichée à une couleur bien plus intense que les autres car elle est allumée plus longtemps.

Pour résoudre le problème d'affichage, j'ai décidé de multiplier par 8 le nombre d'interruption du PIT et de n'afficher qu'une seule ligne par interruption. Cela permet d'avoir une bonne répartition du temps d'affichage de chaque ligne.

# Horloges

Le programme se lance sans problème particulier, je peux même voir ma LED rouge clignoter lorsque j'appuie sur le boutton adéquat.
Cependant, un SIGTRAP apparaît une seconde après avoir lancé le programme.
Il est probable qu'un watchdog déclenche cette interruption. C'est pourquoi je dois la désactiver dans le but d'observer ma LED clignoter à la fréquence d'un Herz afin de valider une bonne initialisation des horloges.

Après désactivation du watchdog, je remarque que ma LED clignote bien à 1Hz.

# Flash

Il faut mettre dans la section .flash_program le .texte les .rodata et les .data tandis que la .bss reste dans la RAM.
De plus il faut mettre la table des vecteurs dans une section spécifique qui se trouve à l'adresse 0.
On peut, après compilation, vérifier que l'on n'écrit pas dans des zones sensible de la flash avec la commande "arm-none-eabi-objdump -x main.elf | less".

Une fois le programme logé en flash, je peux débrancher et rebrancher la carte et voir le programme se lancer automatiquement
