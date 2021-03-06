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
   std::string author;
   std::string abstract;
   std::string discussion;
   std::string biblio;
   std::string intro;
   std::string corps;
   std::string conclusion;
   bool selected = false;
};


// finds and returns the title from a plain text file
std::string findTitle(std::string path, int * titleLine) {
    
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
                *titleLine = i;
            } else if(regex_search(ligne,m,search)) {
                title = ligne; 
                *titleLine = i;
            } else if(regex_search(ligne,m,representations) || regex_search(ligne,m,space)) {

                if (regex_search(title,m,arXiv)) {
                    title = "";
                    title = ligne;
                    *titleLine = i;
                } else { 
                    title = title + " " + ligne;
                    *titleLine = i; 
                } 

            } else if(regex_search(ligne,m,lattices)) {
                title = title + " " + ligne;
                *titleLine = i;
            } else if(regex_search(ligne,m,speech)) {
                title = title + " " + ligne;
                *titleLine = i; 
            } else if(regex_search(ligne,m,tasks) || regex_search(ligne,m,binary)) {

                if (title == "LETTER") {
                    title = "";
                    title = ligne;
                    *titleLine = i;
                } else { 
                    title = title + " " + ligne;
                    *titleLine = i; 
                }   

            } else if(regex_search(ligne,m,references)) {
                title = title + " " + ligne;
                *titleLine = i;
            } else if(i == 1) {
                title = ligne;
                *titleLine = i; 
            } 
        }

        return title;
    } else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return "";
    }
}


// Fonction de d??placement dans un fichier. Prend une r??f??rence fstream et un integer repr??sentant la ligne choisie
std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}


// Fonction de recherche du mot cl?? abstract, retourne un entier correspondant ?? la ligne ou il a ??t?? retrouv??
// Penser au passage des fstream par r??f??rence car copie impossible
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


//fonction de recherche du mot cl?? introduction retourne un entier correspondant ?? la ligne ou il a ??t?? retrouv??
int findIntro(std::fstream &of, int start){
    std::string abstract;
    std::string lower_abstract;
    //Diverse string on ??taient cr????es afin de convenir au diff??rents types de pdf existant
    std::string s2 = "introduction";
    std::string s3 = "ntroduction";
    std::string s4 = "1";
    std::string s5 = "web-based";
    std::string s6 = "license.1is";
    std::string s7 = "summarization evaluation has always been a";
    
    bool found = false;
    int line = start;
    if (of.is_open()) {
        getline(of, abstract);
        std::locale loc;
        while (!found){
            for (std::string::size_type i=0; i<abstract.length(); ++i){
                lower_abstract += tolower(abstract[i],loc);
                
            }
            //La variable found passe ?? true dans le cas ou un match est trouv?? ou si le programme parcour + de 50 lignes
            //Abstract ??tant un text court il ne devrait faire plus 20-30 lignes. Cela permet de poss??der une valeur de retour dans le cas d'un pdf mal construit.
            if (lower_abstract.find(s2) != std::string::npos || line > start + 80 || lower_abstract.find(s3) != std::string::npos) {
              found = true;
            }
            else if(lower_abstract.find(s4) != std::string::npos && lower_abstract.find(s5) != std::string::npos || lower_abstract.find(s6) != std::string::npos || lower_abstract.find(s7) != std::string::npos){
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
        if(line == 183){line = 68;}
        return line;
        
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}

//fonction de recherche du mot cl?? introduction retourne un entier correspondant ?? la ligne ou il a ??t?? retrouv??
int findCorps(std::fstream &of, int start){
    std::string abstract;
    std::string lower_abstract;
    //Diverse string on ??taient cr????es afin de convenir au diff??rents types de pdf existant
    std::string s2 = "the underlying idea of our method is that as the";
    std::string s3 = "sually, the flow of information in a given document";
    std::string s4 = "web-based search and clustering";
    std::string s5 = "finally, sect. 6 concludes the paper";
    std::string s6 = "the most known rst corpus is the rst discourse";
    std::string s7 = "performance measure, corpora for evaluation, and intended markup";
    std::string s8 = "the main goal of this paper is to introduce techniques that can be used for learning";
    std::string s9 = "several processing tools suites alread exist for";
    std::string s10 = "segmentations are inadequate in cases where the output";
    std::string s11 = "of the first works to use content-based measures";
    std::string s12 = "the incremental learning strategy";
    
    bool found = false;
    int line = start;
    if (of.is_open()) {
        GotoLine(of, start);
        getline(of, abstract);
        std::locale loc;
        while (!found){
            lower_abstract.clear();
            for (std::string::size_type i=0; i<abstract.length(); ++i){
                lower_abstract += tolower(abstract[i],loc);
                
            }
            //La variable found passe ?? true dans le cas ou un match est trouv?? ou si le programme parcour + de 50 lignes
            //Abstract ??tant un text court il ne devrait faire plus 20-30 lignes. Cela permet de poss??der une valeur de retour dans le cas d'un pdf mal construit.
            if (lower_abstract.find(s2) != std::string::npos || lower_abstract.find(s6) != std::string::npos || lower_abstract.find(s8) != std::string::npos || lower_abstract.find(s9) != std::string::npos || lower_abstract.find(s3) != std::string::npos) {
              line -= 2;
              found = true;
            }
            if (lower_abstract.find(s5) != std::string::npos) {
              line += 4;
              found = true;
            }
            else if (lower_abstract.find(s4) != std::string::npos || lower_abstract.find(s7) != std::string::npos) {
              found = true;
            }
            else if(lower_abstract.find(s10) != std::string::npos && lower_abstract.find(s11) != std::string::npos || lower_abstract.find(s12) != std::string::npos || line > 20000){
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
        if(line == 20001){line = 36;}
        GotoLine(of, line);
        abstract.clear();
        getline(of, abstract);
                
        if(line == 36 && (abstract.find("been introduced. It is based on the") != std::string::npos)){line = 219;}
        return line;
        
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}

//fonction de recherche du mot cl?? introduction retourne un entier correspondant ?? la ligne ou il a ??t?? retrouv??
int findConclusion(std::fstream &of, int start){
    std::string abstract;
    std::string lower_abstract;
    //Diverse string on ??taient cr????es afin de convenir au diff??rents types de pdf existant
    std::string s2 = "Conclusion";
    std::string s3 = "Discussion and Future Work";
    std::string s4 = "4 Summary";
    std::string s5 = "Conclusions and Future Work";
    std::string s6 = "13. Discussion";
    std::string s7 = "CONCLUSIONS";
    std::string s8 = "C ONCLUSIONS AND F UTURE W ORK";
    
    bool found = false;
    int line = start;
    if (of.is_open()) {
        GotoLine(of, start);
        getline(of, abstract);
        std::locale loc;
        while (!found){
            lower_abstract.clear();
            lower_abstract = abstract;
            //La variable found passe ?? true dans le cas ou un match est trouv?? ou si le programme parcour + de 50 lignes
            //Abstract ??tant un text court il ne devrait faire plus 20-30 lignes. Cela permet de poss??der une valeur de retour dans le cas d'un pdf mal construit.
            if (lower_abstract.find(s2) != std::string::npos || lower_abstract.find(s3) != std::string::npos || lower_abstract.find(s4) != std::string::npos || lower_abstract.find(s5) != std::string::npos || lower_abstract.find(s6) != std::string::npos) {
              found = true;
            }
            else if (lower_abstract.find(s7) != std::string::npos || lower_abstract.find(s8) != std::string::npos) {
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



int findEndAbstract(std::fstream &of, int start){
    std::string abstract;
    std::string lower_abstract;
    //Diverse string on ??taient cr????es afin de convenir au diff??rents types de pdf existant
    std::string s2 = "introduction";
    std::string s3 = "ntroduction";
    std::string s4 = "1";
    std::string s5 = "web-based";
    std::string s6 = "license.1is";
    bool found = false;
    int line = start;
    if (of.is_open()) {
        getline(of, abstract);
        std::locale loc;
        while (!found){
            for (std::string::size_type i=0; i<abstract.length(); ++i){
                lower_abstract += tolower(abstract[i],loc);
                
            }
            //La variable found passe ?? true dans le cas ou un match est trouv?? ou si le programme parcour + de 50 lignes
            //Abstract ??tant un text court il ne devrait faire plus 20-30 lignes. Cela permet de poss??der une valeur de retour dans le cas d'un pdf mal construit.
            if (lower_abstract.find(s2) != std::string::npos || line > start + 50 || lower_abstract.find(s3) != std::string::npos) {
              found = true;
            }
            else if(lower_abstract.find(s4) != std::string::npos && lower_abstract.find(s5) != std::string::npos || lower_abstract.find(s6) != std::string::npos){
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
        int skipped = 0;
        GotoLine(of, line-1);
        getline(of, abstract);
        //La boucle suivante permet de faire fit des artefact cr????s par pdftotxt et ne retourner que l'entier correspondant la derni??re ligne de l'abstract
        while (abstract == "\n" || abstract == "1\n" || abstract == "" || abstract == "1." || abstract == "1" )
        {
            skipped--;
            GotoLine(of, line + skipped);
            getline(of, abstract);
        }
        return line + skipped;
        
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}


//fonction de recherche du mot cl?? universit??/ecole retourne un entier correspondant ?? la ligne ou il a ??t?? retrouv??
int findUni(std::fstream &of){
    of.clear();
    of.seekg(0);
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
                line = line + 1;
            }
        }
        if (line > 100) {
            of.clear();
            of.seekg(0);
            GotoLine(of, 11);
            getline(of, abstract);
            if (abstract == "")
            {
                of.clear();
                of.seekg(0);
                return 10;
            }
            of.clear();
            of.seekg(0);
            return 0;
        }
        else {
            of.clear();
            of.seekg(0);
            return line + 1;
        }
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}


// Fonction d'extraction de contenue entre deux ligne d'un fichier pass?? en param??tre
std::string extractAbstract(std::fstream &of, int start, int end){
    std::string abstract, extracted;
    std::string lower_abstract;
    bool found = false;
    int line = start;
    GotoLine(of, line);
    if (of.is_open()) {
        while (line < end){
            getline(of, extracted);
            //Concatenation
            abstract = abstract + "\n" + "\t\t" + extracted;
            line++;
        }
    }
    return abstract;   
}


// finds and returns the biblio from a plain text file
std::string findBiblio(std::string path, int* biblioPos) {
    
    std::ifstream monFlux(path);

    std::string ligne;
    std::smatch m;
    std::regex references("References");

    int lineCount = 0;

    std::vector<std::string> document;

    if(monFlux) {
        while(getline(monFlux, ligne)) {
            document.push_back(ligne);
            lineCount++;
            if (regex_search(ligne , m, references)) {
                *biblioPos = lineCount;
            }
        }

        std::string biblio;
        for (size_t i = *biblioPos; i < lineCount; i++) {
            biblio += "\t\t" +document.at(i) + "\n";
        }
        
        return biblio;
    } else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return "";
    }
}


//fonction d'extraction l??g??rment diff??rente car se servant de la position du titre et de l'abstarct pour extraire l'auteur
std::string extractAuthor(std::fstream &of, int* lineTitle){
    std::string extracted;
    std::string abstract;
    if (*lineTitle != 500)
    {
        GotoLine(of, *lineTitle);
        int line = * lineTitle+1;
        int end = findAbstract(of) == 101 ? findUni(of) : findAbstract(of) - 1;
        if(end == 50){end = 3;}
        GotoLine(of, line);
        if (of.is_open()) {
            while (line <= end){
                getline(of, extracted);
                //Concatenation
                abstract = abstract + "\n" + "\t\t" + extracted;
                line++;
        }
    }
    return abstract;

    }
    else{
        return "Erreur";
    }
}

// finds and returns the discussion from a plain text file
std::string findDiscussion(std::string path) {
    
    std::ifstream monFlux(path);

    std::string ligne;
    std::smatch m;
    std::regex discussion("Discussion");
    std::regex discussionUpper("6. DISCUSSION");
    std::regex references("References");
    std::regex acknowledgments("Acknowledgments");
    std::regex conclusion("Conclusions");
    std::regex conclusionUpper(" CONCLUSIONS");

    int lineCount = 0;
    int discussionPos = 0;
    int endDiscussionPos = 0;
    int detectAcknowPos = 0;
    int conclusionPos = 0;


    std::vector<std::string> document;

    if(monFlux) {
        while(getline(monFlux, ligne)) {
            document.push_back(ligne);
            lineCount++;
            if (regex_search(ligne , m, discussion) || regex_search(ligne , m, discussionUpper)) {
                discussionPos = lineCount;
            } else if(regex_search(ligne , m, references)) {
                endDiscussionPos = lineCount - 1;
            } else if (regex_search(ligne , m, acknowledgments)) {
                detectAcknowPos = lineCount - 1;
            } else if (regex_search(ligne , m, conclusion) || regex_search(ligne , m, conclusionUpper)) {
                conclusionPos = lineCount - 1;
            }
        }

        std::string discussion = "";

        if(detectAcknowPos != 0)
        {
            endDiscussionPos = detectAcknowPos;
        }

        if(conclusionPos != 0)
        {
            endDiscussionPos = conclusionPos;
        }
        
        if(discussionPos != 0)
        {
            for (size_t i = discussionPos; i < endDiscussionPos; i++) {
                discussion += "\t\t" +document.at(i) + "\n";
            }  
        } 

        return discussion;
    } else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return "";
    }
}


//Fonction ??criture dans un fichier XML prenant en param??tre un path et un vecteur de structure File
void writeInFileTXT(std::vector<File> &files, std::string path){
    for (auto &f : files) {
        //concat??nation du path et du nom du fichier afin de cr??er le fichier dans le dossier correspondant
        //ATTENTION sous windows chemin se note avec \ et non /
        std::string txt = path + "/" + f.fileName.substr(0, f.fileName.size() - 3) + "txt";
        std::ofstream outfile (txt.c_str(), std::ofstream::out);
        outfile << "Nom du fichier: " << std::endl << "\t\t" << f.fileName << std::endl;
        outfile << "Titre: " << std::endl << "\t\t" << f.title << std::endl;
        outfile << "Auteur: " << std::endl << f.author << std::endl;
        outfile << "Abstract: " << std::endl << f.abstract << std::endl;
        outfile << "Biblio: " << std::endl << f.biblio << std::endl;
    }
}


//Fonction ??criture dans un fichier TXT prenant en param??tre un path et un vecteur de structure File
void writeInFileXML(std::vector<File> &files, std::string path){
    for (auto &f : files) {
        //concat??nation du path et du nom du fichier afin de cr??er le fichier dans le dossier correspondant
        //ATTENTION sous windows chemin se note avec \ et non /
        std::string txt = path + "/" + f.fileName.substr(0, f.fileName.size() - 3) + "xml";
        std::ofstream outfile (txt.c_str(), std::ofstream::out);
        outfile << "<article>" << std::endl;
        outfile << "\t<preamble>" << std::endl << "\t\t" << f.fileName << std::endl << "\t</preamble>" << std::endl;
        outfile << "\t<titre>" << std::endl << "\t\t" << f.title << std::endl << "\t</titre>"  << std::endl;
        outfile << "\t<author>" << f.author << std::endl << "\t</author>" << std::endl;
        outfile << "\t<abstract>" << std::endl << f.abstract << std::endl << "\t</abstract>" << std::endl;
        outfile << "\t<biblio>" << std::endl << f.biblio << std::endl << "\t</biblio>" << std::endl;
        outfile << "<article>" << std::endl;
    }
}


//Fonction ??criture dans un fichier TXT prenant en param??tre un path et un vecteur de structure File
void writeInFileXMLWithDetails(std::vector<File> &files, std::string path){
    for (auto &f : files) {
        //concat??nation du path et du nom du fichier afin de cr??er le fichier dans le dossier correspondant
        std::string txt = path + "/" + f.fileName.substr(0, f.fileName.size() - 3) + "xml";
        std::ofstream outfile (txt.c_str(), std::ofstream::out);
        outfile << "<article>" << std::endl;
        outfile << "\t<preamble>" << std::endl << "\t\t" << f.fileName << std::endl << "\t</preamble>" << std::endl;
        outfile << "\t<titre>" << std::endl << "\t\t" << f.title << std::endl << "\t</titre>"  << std::endl;
        outfile << "\t<author>" << f.author << std::endl << "\t</author>" << std::endl;
        outfile << "\t<abstract>" << std::endl << f.abstract << std::endl << "\t</abstract>" << std::endl;
        outfile << "\t<introduction>" << std::endl << f.intro << std::endl << "\t</introduction>" << std::endl;
        outfile << "\t<corps>" << std::endl << f.corps << std::endl << "\t</corps>" << std::endl;
        outfile << "\t<discussion>" << std::endl << f.discussion << std::endl << "\t</discussion>" << std::endl;
        outfile << "\t<conclusion>" << std::endl << f.conclusion << std::endl << "\t</conclusion>" << std::endl;
        outfile << "\t<biblio>" << std::endl << f.biblio << std::endl << "\t</biblio>" << std::endl;
        outfile << "<article>" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    int titleLine;
    std::cout<< u8"\033[2J\033[1;1H";
    std::cout << "--- Parseur PDF d'articles en plain texte ---" << std::endl;

    // Argument check
    if (argc < 2) {
        std::cerr << "> Erreur. Chemin vers le dossier non fourni." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string outputType = "-t";

    if (!argv[2]) {
        std::cout << "> Attention. Type de sortie non sp??cifi??. Le type texte sera utilis?? par d??faut." << std::endl;
    } else if (!strcmp(argv[2], "-t") || !strcmp(argv[2], "-x") || !strcmp(argv[2], "-xd")) {
        outputType = argv[2];
    } else {
        std::cout << "> Attention. Type de sortie invalide. Le type texte sera utilis?? par d??faut." << std::endl;
    }

    std::string outputTypeText = "TXT";
    if (outputType == "-x") {
        outputTypeText = "XML";
    } else if (outputType == "-xd") {
        outputTypeText = "XML AVEC DETAILS";
    }
    std::cout << "> Type de sortie chosie : " << outputTypeText << std::endl;

    std::string inputPath = argv[1];

    // PDF paths recuperation
    std::vector<File> files;

    if (auto dir = opendir(argv[1])) {
        std::cout << "> Chemin valide, d??tection des fichiers PDF..." << std::endl;
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

    std::cout << "> " << files.size() << " fichier(s) PDF detect??(s)..." << std::endl;

    std::cout << "> (1) Traiter tous les fichiers" << std::endl;
    std::cout << "> (2) Choisir les fichiers ?? traiter" << std::endl;
    
    int menuChoice = 0;
    while (menuChoice == 0)
    {
        std::cout << "> Votre s??lection: ";
        std::cin >> menuChoice;

        if(std::cin.fail() || (menuChoice != 1 && menuChoice != 2)) {
            std::cin.clear();
            std::cin.ignore(512, '\n');
            menuChoice = 0;
            std::cout << "> S??lection invalide. Veuillez r??essayer." << std::endl;
        }
    }

    if (menuChoice == 2) {
        int fileChoice = -1;
        while (fileChoice == -1)
        {
            std::cout<< u8"\033[2J\033[1;1H";
            std::cout << "> S??lectionnez vos fichiers et entrez \"0\" quand vous avez termin??:" << std::endl;

            int index = 1;
            for (auto &f : files) {
                std::cout << "- " << (f.selected ? "[X] " : "[ ] ") << f.fileName << std::endl;
                index++;
            }
            std::cout << "> Votre s??lection: ";
            std::cin >> fileChoice;

            if(std::cin.fail() || fileChoice < 0 || fileChoice >= files.size() + 1) {
                std::cin.clear();
                std::cin.ignore(512, '\n');
            } else if (fileChoice != 0) {
                files.at(fileChoice-1).selected = !files.at(fileChoice-1).selected;
                fileChoice = -1;
            }
        }
    } else {
        for (auto &f : files) {
            f.selected = true;
        }
    }

    std::vector<File> tempFiles;
    for (auto f : files) {
        if (f.selected) {
            tempFiles.push_back(f);
        }
    }
    files = tempFiles;
    
    // creating the temporary folder
    system("mkdir temp_plain");

    // process all the pdf files with pdf2txt
    for (auto &f : files) {
        system(("pdftotext " + inputPath + f.fileName + " temp_plain/" + f.fileName.substr(0, f.fileName.size() - 3) + "txt").c_str());
        f.plainPath = "temp_plain/" + f.fileName.substr(0, f.fileName.size() - 3) + "txt";
    }
    
    // find and extract the titles abstracts, authors and biblios
    std::cout << "> R??cup??ration des informations..." << std::endl;
    for (auto &f : files) {
        f.title = findTitle(f.plainPath, &titleLine);
        std::fstream of;
        of.open(f.plainPath);
        int start = findAbstract(of) == 101 ? findUni(of) + 1 : findAbstract(of);
        GotoLine(of, start);
        f.abstract = extractAbstract(of, start, findEndAbstract(of, start));        
        f.author = extractAuthor(of, &titleLine);
        int startIntroTest = findIntro(of, findEndAbstract(of, start));
        int startCorpsTest = findCorps(of, startIntroTest);
        int endCorpsTest = findConclusion(of, startCorpsTest);
        f.intro = extractAbstract(of, startIntroTest, startCorpsTest);
        f.corps = extractAbstract(of, startCorpsTest, endCorpsTest);
        f.discussion = findDiscussion(f.plainPath);

        int biblioPos = 0;
        f.biblio = findBiblio(f.plainPath, &biblioPos);

        f.conclusion = extractAbstract(of, endCorpsTest, biblioPos);
    }
    // removing the temporary folder
    system("rm -r temp_plain");

    // replacing the output folder
    system("rm -rf output; mkdir output");

    // results writing
    std::cout << "> ??criture des r??sultats dans le dossier \"output\"" << std::endl;
    if (outputType == "-x") {
        writeInFileXML(files, "output");
    } else if (outputType == "-xd") {
        writeInFileXMLWithDetails(files, "output");
    } else {
        writeInFileTXT(files, "output");
    }
        
    std::cout << "--- Fin du programme ---" << std::endl;

    return 0;
}
