#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <regex>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include <limits>


// struct used to store the data as objects
struct File {
   std::string fileName;
   std::string plainPath;
   std::string title;
   std::string abstract;
};


// finds and returns the title from a plain text file
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




// Fonction de déplacement dans un fichier. Prend une référence fstream et un integer représentant la ligne choisie
std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

// Fonction de recherche du mot clé abstract, retourne un entier correspondant à la ligne ou il a été retrouvé
// Penser au passage des fstream par référence car copie impossible
int findAbstract(std::fstream &of){
    std::string abstract;
    std::string lower_abstract;
    std::string s2 = "abstract";
    bool found = false;
    int line = 0;
    if (of.is_open()) {
        of.clear();
        of.seekg(0);
        getline(of, abstract);
        std::locale loc;
        while (!found){
            //Fonction de mise en minuscule d'une string
            for (std::string::size_type i=0; i<abstract.length(); ++i){
                lower_abstract += tolower(abstract[i],loc);
            }
            if (lower_abstract.find(s2) != std::string::npos || line > 100) {
              found = true;
            }
            else{
                abstract.clear();
                getline(of, abstract);
                line++;
            }
        }
        of.clear();
        of.seekg(0);
        return line;
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}

//fonction de recherche du mot clé introduction retourne un entier correspondant à la ligne ou il a été retrouvé
int findIntro(std::fstream &of, int start){
    std::string abstract;
    std::string lower_abstract;
    std::string s2 = "introduction";
    bool found = false;
    int line = 0;
    if (of.is_open()) {
        getline(of, abstract);
        std::locale loc;
        while (!found){
            for (std::string::size_type i=0; i<abstract.length(); ++i){
                lower_abstract += tolower(abstract[i],loc);
            }
            if (lower_abstract.find(s2) != std::string::npos || line > start + 20) {
              found = true;
            }
            else{
                abstract.clear();
                getline(of, abstract);
                line++;
            }
        }
        of.clear();
        of.seekg(0);
        return line;
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}

//fonction de recherche du mot clé université/ecole retourne un entier correspondant à la ligne ou il a été retrouvé
int findUni(std::fstream &of){
    std::string abstract;
    std::string lower_abstract;
    std::string s2 = "university";
    std::string s3 = "school";
    bool found = false;
    int line = 0;
    if (of.is_open())
    {
        getline(of, abstract);
        std::locale loc;
        while (!found){
            for (std::string::size_type i=0; i<abstract.length(); ++i){
                lower_abstract += tolower(abstract[i],loc);
            }
            if (lower_abstract.find(s2) != std::string::npos || lower_abstract.find(s3) != std::string::npos || line > 100) {
              found = true;
            }
            else{
                abstract.clear();
                getline(of, abstract);
                line++;
            }   
        }
              
        if (line > 100) {
            of.clear();
            of.seekg(0);
            return 0;
        }
        else {
            of.clear();
            of.seekg(0);
            return line;
        }
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}

// Fonction d'extraction de contenue entre deux ligne d'un fichier passé en paramètre
std::string extractAbstract(std::fstream &of, int start, int end){
    std::string abstract, extracted;
    std::string lower_abstract;
    bool found = false;
    int line = start;
    if (of.is_open()) {
        while (line <= end){
            getline(of, extracted);
            //Concatenation
            abstract = abstract + "\n" + extracted;
            line++;
        }
    }
    return abstract;   
}


//Fonction écriture dans un fichier prenant en paramètre un path et un vecteur de structure File
void writeInFile(std::vector<File> &files, std::string path){
    for (auto &f : files) {
        //concaténation du path et du nom du fichier afin de créer le fichier dans le dossier correspondant
        //ATTENTION sous windows chemin se note avec \ et non /
        std::string txt = path + "/" + f.fileName.substr(0, f.fileName.size() - 3) + "txt";
        std::ofstream outfile (txt.c_str(), std::ofstream::out);
        outfile << "Nom du fichier: " << f.fileName << std::endl;
        outfile << "Titre: " << f.title << std::endl;
        outfile << "Abstract: " << std::endl << f.abstract << std::endl;
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
    std::vector<File> files;

    if (auto dir = opendir(argv[1])) {
        std::cout << "> Chemin valide, détection des fichiers PDF..." << std::endl;
        std::string filePath = "";
        while (auto f = readdir(dir)) {
            filePath = f->d_name;
            if (filePath.size() > 5 && filePath.substr(filePath.size() - 4) == ".pdf") {
                File tempFile;
                tempFile.fileName = filePath;
                files.push_back(tempFile);
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

    // creating the temporary folder
    system("mkdir temp_plain");

    // process all the pdf files with pdf2txt
    for (auto &f : files) {
        system(("pdftotext " + inputPath + f.fileName + " temp_plain/" + f.fileName.substr(0, f.fileName.size() - 3) + "txt").c_str());
        f.plainPath = "temp_plain/" + f.fileName.substr(0, f.fileName.size() - 3) + "txt";
    }
    
    // find and extract all the titles
    std::cout << "> Récupération des titres et des abstracts..." << std::endl;
    for (auto &f : files) {
        f.title = findTitle(f.plainPath);

        std::fstream of;
        of.open(f.plainPath);
        int start = findAbstract(of) == 0 ? findUni(of) : findAbstract(of);
        GotoLine(of, start);
        findIntro(of, start);
        f.abstract = extractAbstract(of, start, findIntro(of, start));
    }

    // removing the temporary folder
    system("rm -r temp_plain");

    // replacing the output folder
    system("rm -r output; mkdir output");

    // results writing
    std::cout << "> Écriture des résultats dans le dossier \"output\"" << std::endl;
    writeInFile(files, "output");

    std::cout << "--- Fin du programme ---" << std::endl;

    return 0;
}
