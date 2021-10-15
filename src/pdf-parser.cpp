#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>

int main(int argc, char const *argv[])
{
    std::cout << "--- Parseur PDF d'articles en plain texte ---" << std::endl;

    // Argument check
    if (argc < 2) {
        std::cerr << "> Erreur. Chemin vers le dossier non fourni." << std::endl;
        exit(EXIT_FAILURE);
    }

    // PDF paths recuperation
    std::vector<std::string> files;

    if (auto dir = opendir(argv[1])) {
        std::cout << "> Chemin valide, détection des fichiers PDF..." << std::endl;
        std::string filePath = "";
        while (auto f = readdir(dir)) {
            filePath = f->d_name;
            if (filePath.size() > 5 && filePath.substr(filePath.size() - 4) == ".pdf") {
                files.push_back(filePath);
            }
            else {
                continue;
            }    
        }
        closedir(dir);
    } else {
        std::cerr << "> Erreur. Le chemin fourni n'est pas valide." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "> " << files.size() << " fichier(s) PDF..." << std::endl;

    return 0;
}
