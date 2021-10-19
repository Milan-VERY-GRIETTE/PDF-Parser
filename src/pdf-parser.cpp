#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include <limits>

using namespace std;

//Fonction de déplacement dans un fichier. Prend une référence fstream et un integer représentant la ligne choisi
std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

//fonction de recherche du mot clé abstract retourne un entier correspondant à la ligne ou il a été retrouvé
//Penser au passage des fstream par référence car copie impossible
int findAbstract(fstream &of){
    string abstract;
    string lower_abstract;
    string s2 = "abstract";
    bool found = false;
    int line = 0;
    if (of.is_open())
    {
        of.clear();
        of.seekg(0);
        getline(of, abstract);
        locale loc;
        while (!found){
            //Fonction de mise en minuscule d'une string
            for (string::size_type i=0; i<abstract.length(); ++i){
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
        cerr << "Erreur fichier non ouvrable" << endl;
        return 0;
    }
}

//fonction de recherche du mot clé introduction retourne un entier correspondant à la ligne ou il a été retrouvé
int findIntro(fstream &of){
    string abstract;
    string lower_abstract;
    string s2 = "introduction";
    bool found = false;
    int line = 0;
    if (of.is_open())
    {
        getline(of, abstract);
        locale loc;
        while (!found){
            for (string::size_type i=0; i<abstract.length(); ++i){
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
        cerr << "Erreur fichier non ouvrable" << endl;
        return 0;
    }
}

//fonction de recherche du mot clé université/ecole retourne un entier correspondant à la ligne ou il a été retrouvé
int findUni(fstream &of){
    string abstract;
    string lower_abstract;
    string s2 = "university";
    string s3 = "school";
    bool found = false;
    int line = 0;
    if (of.is_open())
    {
        getline(of, abstract);
        locale loc;
        while (!found){
            for (string::size_type i=0; i<abstract.length(); ++i){
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
              
        if (line > 100)
        {
            of.clear();
            of.seekg(0);
            return 0;
        }
        else
        {
            of.clear();
            of.seekg(0);
            return line;
        }
    }
    else {
        cerr << "Erreur fichier non ouvrable" << endl;
        return 0;
    }
    
    
}

//fonction d'extraction de contenue entre deux ligne d'un fichier passé en paramètre
string extractAbstract(fstream &of, int start, int end){
    string abstract, extracted;
    string lower_abstract;
    bool found = false;
    int line = start;
    if (of.is_open())
    {
        while (line <= end){
            getline(of, extracted);
            //Concatenation
            abstract = abstract + "\n" + extracted;
            line++;
        }
        //cout << abstract;
    }
    return abstract;   
}

//Choix de la création de diverses fonction de recherche car fonctionnement différent en cas d'echec de match
int main(int argc, char const *argv[])
{
    fstream of;
    //sera remplacer lors du merge
    of.open("Das_Martin.txt");
    int start = findAbstract(of);
    //prise en compte de la possibilité d'echec de match de abstract
    if (start == 0){
        start = findUni(of);
    }
    //la fonction intégre une gestion en cas d'echec de match du mot clé
    int end = findIntro(of);
    GotoLine(of, start);
    cout << start << " " << end << endl;
    extractAbstract(of, start, end);
    return 0;
}
