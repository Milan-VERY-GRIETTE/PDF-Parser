# PDF-Parser
Parseur PDF d’articles scientifiques en format texte ou XML.
Réalisé par:
- Théo QUEZEL-PERRON
- Anthony NAVARRO
- Milan VERY-GRIETTE
- Bouchra EL HOUARI

## Prérequis

- Un OS UNIX
- L'outil pdftotext installé

## Compilation

Le programme est écrit en C++.
Il peut être compilé avec n'importe quel compilateur C++.

Exemple de compilation avec le compilateur g++ :
```
g++ -o pdf-parser src/pdf-parser.cpp
```

## Utilisation

Le programme est conçu pour fonctionner sous un système d'exploitation UNIX.
Son fonctionnement avec d'autres systèmes n'est pas garanti.

Le programme prend en argument d'entrée un chemin vers un dossier contenant un ou des fichiers PDF.
Un dossier nommé "output" et contenant les résultats sera généré à l'issue de l'exécution du programme.
Ce dossier sera situé à la racine du fichier exécutable.

Le programme peut produire trois types de sorties: l'une en TXT , une autre en XML et une dernière en XML également, mais contenant plus de détails.

La sélection du type de sortie se fait avec le deuxième argument d'entrée: `-t` pour une sortie TXT (par défaut), `-x` pour une sortie en XML et `-xd` pour une sortie en XML avec plus d'informations.

Les sorties TXT et XML donnent les informations suivantes:
- Nom du fichier
- Titre
- Auteur
- Abstract
- Bibliographie

La sortie XML avec détails donne les informations suivantes:
- Nom du fichier
- Titre
- Auteur
- Abstract
- Introduction
- Corps
- Discussion
- Conclusion
- Bibliographie

Au démarrage, le programme laisse le choix entre prendre tous les fichiers du répertoire fourni, ou bien en sélectionner certains.

Exemple d'utilisation du programme : 
```
./pdf-parser <chemin vers le dossier> <type de sortie>
./pdf-parser ../../Documents/Articles/
./pdf-parser ../../Documents/Articles/ -x
./pdf-parser ../Mes_Artcles/ -xd
```

## Explication

L'exécution du programme se déroule en plusieurs phases:
- Récupération du chemin passé en argument
- Récupération du type de sortie demandé
- Choix des fichiers à traiter (tous, ou une sélection)
- Listage de tous les fichiers PDF présents dans ce dossier
- Parsing de ces fichiers en fichiers textes via l'outil "pdftotext"
- Recherche et extraction des informations relatives au PDF depuis le fichier parsé, selon le niveau de détail choisi
- Écriture dans un dossier "output" d'un fichier texte ou xml contenant lesdites informations
- 