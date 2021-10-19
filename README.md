# PDF-Parser
Parseur PDF d’articles scientifiques en format texte.
Réalisé par:
- Théo QUEZEL-PERRON
- Anthony NAVARRO
- Milan VERY-GRIETTE

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

Exemple d'utilisation du programme : 
```
./pdf-parser <chemin vers le dossier>
./pdf-parser ../../Documents/Articles/
```

## Explication

L'exécution du programme se déroule en plusieurs phases:
- Récupération du chemin passé en argument
- Listage de tous les fichiers PDF présents dans ce dossier
- Parsing de ces fichiers en fichiers textes via l'outil "pdftotext"
- Recherche et l'extraction du titre du PDF depuis le fichier parsé
- Recherche et l'extraction de l'abstract du PDF depuis le fichier parsé
- Écriture dans un dossier "output" d'un fichier texte contenant le nom du fichier original, son titre et son abstract
