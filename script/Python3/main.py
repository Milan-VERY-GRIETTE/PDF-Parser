# This is a sample Python script.

# Press Maj+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import time
from random import randrange


def test():
    start1 = time.time()
    grille = []
    for line in range(1000):
        nvline = []
        for col in range(1000):
            nvline.append(randrange(10000))
        grille.append(nvline)
    end2 = time.time()
    elapsed1 = end2 - start1

    print(f'Création et Remplissage : {elapsed1:.2} ns')

    start2 = time.time()
    fichier = open("data.txt", "a")
    for line in grille:
        fichier.write(str(line) + '\n')
    end2 = time.time()
    elapsed2 = end2 - start2
    print(f'Ecriture du fichier : {elapsed2:.2} s')

    start3 = time.time()
    with open("data.txt", "r") as file:
            file.read()
    end3 = time.time()
    elapsed3 = end3 - start3
    print(f'Lecture du fichier : {elapsed3:.2} s')
    total = elapsed1 + elapsed2 + elapsed3

    print(f'Temps d\'exécution : {total:.2} s')


def clean():

    print('Voulez-vous recommencer le test ? (o ou n)')
    response = input()

    if response == "o":
        with open("data.txt", "r+") as file:
            file.truncate(0)
            file.seek(0)
        test()
        clean()
    elif response == "n":
        print('Fin du test')
        with open("data.txt", "r+") as file:
            file.truncate(0)
            file.seek(0)
    else:
        print('Veuillez choisir o pour refaire le test ou n pour terminé le test')
        clean()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    test()
    clean()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
