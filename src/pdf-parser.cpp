#include <vector>
#include <string>
#include <iostream>
#include <fstream> 

struct File {
   std::string fileName;
   std::string plainPath;
   std::string title;
   std::string abstract;
};


//Fonction écriture dans un fichier prenant en paramètre un path et un vecteur de structure File
void writeInFile(std::vector<File> &files, std::string path){
    for (auto &f : files) {
        //concaténation du path et du nom du fichier afin de créer le fichier dans le dossier correspondant
        //ATTENTION sous windows chemin se note avec \ et non /
        std::string txt = path + "\\" + f.fileName.substr(0, f.fileName.size() - 3) + "txt";
        std::cout << txt.c_str() << std::endl;
        std::ofstream outfile (txt.c_str(), std::ofstream::out);
        outfile << "Nom du fichier: " << f.fileName << std::endl;
        outfile << "Titre: " << f.title << std::endl;
        outfile << "Abstract: " << std::endl << f.abstract << std::endl;
    }
    
}

int main(int argc, char const *argv[])
{
    std::vector<File> files;
    File f, f1;
    f.fileName = "test.pdf";
    f.abstract = "ezfde fezfzeferz ger gregf ezrfgzegf zezfzegf gzreg zeg ze gzeg zergezr gezgz fe \n zefze fzefg fgez gfzef egf zgf zefg \n  efkbzefiuybeziznapdoejpajéaoipz   bnfhmzsrbnb\n";
    f.title = "Wahou";
    f1.fileName = "azdazd.pdf";
    f1.abstract = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
    f1.title = "BLAHBLAHBLAH";
    files.push_back(f);
    files.push_back(f1);
    writeInFile(files, "test");
    return 0;
}
