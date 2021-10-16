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
        cout << "La lecture du fichier est prête." << endl;
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
