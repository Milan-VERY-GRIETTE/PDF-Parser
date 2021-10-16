using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include<algorithm>


void findTitle(string path) {
    
    string ligne;
    ifstream monFlux(path);

    if(monFlux)  
    {
        for (unsigned int i=1; i< 16; i++) {

            getline(monFlux, ligne); 
            cout << ligne << " " << i << endl;            
        
        }
    } else {
        cerr << "ERREUR : Impossible d'ouvrir le fichier." << endl;
    }

}


int main(int argc, char const *argv[])
{
    string path = "data/Boudin-Torres-2006.txt";
    findTitle(path);
    return 0;
}
