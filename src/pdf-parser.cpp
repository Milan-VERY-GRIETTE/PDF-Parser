#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <regex>


std::string findTitle(std::string path) {
    
    std::string ligne;
    std::string title;
    std::smatch m;
    std::ifstream monFlux(path);
    std::regex update("Update");
    std::regex search("Search");
    std::regex representations("Representations");
    std::regex space("Space");
    std::regex lattices("Lattices");
    std::regex speech("SPEECH");
    std::regex tasks("Tasks");
    std::regex binary("Binary");
    std::regex references("References");
    std::regex arXiv("arXiv");

    if(monFlux) {
        for (unsigned int i= 1; i < 10; i++) {
            getline(monFlux, ligne); 

            if (regex_search(ligne,m,update)) {
                title = title + " " + ligne; 
            } else if(regex_search(ligne,m,search)) {
                title = ligne; 
            } else if(regex_search(ligne,m,representations) || regex_search(ligne,m,space)) {

                if (regex_search(title,m,arXiv)) {
                    title = "";
                    title = ligne;
                } else { 
                    title = title + " " + ligne; 
                } 

            } else if(regex_search(ligne,m,lattices)) {
                title = title + " " + ligne;
            } else if(regex_search(ligne,m,speech)) {
                title = title + " " + ligne; 
            } else if(regex_search(ligne,m,tasks) || regex_search(ligne,m,binary)) {

                if (title == "LETTER") {
                    title = "";
                    title = ligne;
                } else { 
                    title = title + " " + ligne; 
                }   

            } else if(regex_search(ligne,m,references)) {
                title = title + " " + ligne;
            } else if(i == 1) {
                title = ligne; 
            } 
        }

        return title;
    } else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return "";
    }
}


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
        system(("pdftotext " + inputPath + f + " temp_plain/" + f.substr(0, f.size() - 3) + "txt").c_str());
        plainFiles.push_back("temp_plain/" + f.substr(0, f.size() - 3) + "txt");
    }
    
    for (auto f : plainFiles) {
        std::cout << findTitle(f) << std::endl;
    }

    // TODO: INFO RECUPERATION

    // removing the temporary folder
    system("rm -r temp_plain");

    // replacing the output folder
    system("rm -r output; mkdir output");

    // TODO: RESULTS WRITING
}
