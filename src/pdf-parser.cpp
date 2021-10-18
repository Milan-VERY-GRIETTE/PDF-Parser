using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include<algorithm>
#include <regex>


string findTitle(string path) {
    
    string ligne;
    string title;
    smatch m;
    ifstream monFlux(path);
    regex update("Update");
    regex search("Search");
    regex representations("Representations");
    regex space("Space");
    regex lattices("Lattices");
    regex speech("SPEECH");
    regex tasks("Tasks");
    regex binary("Binary");
    regex references("References");
    regex arXiv("arXiv");


    if(monFlux)  
    {
        for (unsigned int i= 1; i < 10; i++) {

            getline(monFlux, ligne); 
            if (regex_search(ligne,m,update))
            {
                title = title + " " + ligne; 

            } else if(regex_search(ligne,m,search)) {

                title = ligne; 

            } else if(regex_search(ligne,m,representations) || regex_search(ligne,m,space)) {
                
                if (regex_search(title,m,arXiv))
                {
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
                
                if (title == "LETTER")
                {
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

        cerr << "ERREUR : Impossible d'ouvrir le fichier." << endl;
        return "";
    }

}

int main(int argc, char const *argv[])
{
    string title;
    string tab[11] = {"data/Boudin-Torres-2006.txt", 
    "data/Das_Martins.txt", 
    "data/Eissen_2002_Analysis_of_clustering_algorithms.txt", 
    "data/Gonzalez_2018_Wisebe.txt", 
    "data/Iria_Juan-Manuel_Gerardo.txt", 
    "data/mikheev.txt", 
    "data/Mikolov.txt", 
    "data/Nasr.txt", 
    "data/Stolcke_1996_Automatic_linguistic.txt",
    "data/Torres-moreno1998.txt", 
    "data/Torres.txt"};

    for (size_t i = 0; i < 11 ; i++)
    {
        title = findTitle(tab[i]);
        cout << title << endl;
    }
    
    return 0;
}
