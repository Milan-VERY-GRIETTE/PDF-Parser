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

    std::string inputPath = argv[1];

    // PDF paths recuperation
    std::vector<std::string> pdfFiles;

    if (auto dir = opendir(argv[1])) {
        std::cout << "> Chemin valide, détection des fichiers PDF..." << std::endl;
        std::string filePath = "";
        while (auto f = readdir(dir)) {
            filePath = f->d_name;
            if (filePath.size() > 5 && filePath.substr(filePath.size() - 4) == ".pdf") {
                pdfFiles.push_back(filePath);
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

    std::cout << "> " << pdfFiles.size() << " fichier(s) PDF..." << std::endl;


    // creating the temporary folders
    system("mkdir temp_plain");

    // process all the pdf files with pdf2txt
    std::vector<std::string> plainFiles;

    for (auto f : pdfFiles) {
        system(("pdf2txt " + inputPath + f + " -t text -A -L 1 -o temp_plain/" + f.substr(0, f.size() - 3) + "txt").c_str());
        plainFiles.push_back("temp_plain/" + f.substr(0, f.size() - 3) + "txt");
    }
    
    for (auto f : plainFiles) {
        std::cout << f << std::endl;
    }

    // TODO: INFO RECUPERATION

    // removing the temporary folder
    system("rm -r temp_plain");

    // replacing the output folder
    system("rm -r output; mkdir output");

    // TODO: RESULTS WRITING
}
