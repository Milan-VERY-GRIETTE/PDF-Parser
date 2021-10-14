#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "--- Parseur PDF d'articles en plain texte ---" << std::endl;
    if (argc < 2) {
        std::cerr << "Erreur. Chemin vers le dossier non fourni." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << argv[1] << std::endl;

    return 0;
}
