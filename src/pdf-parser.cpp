#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <locale>
#include <limits>

using namespace std;

// std::fstream& GotoLine(std::fstream& file, unsigned int num){
//     file.seekg(std::ios::beg);
//     for(int i=0; i < num - 1; ++i){
//         file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     }
//     return file;
// }


int findAbstract(fstream &of){
    //of.open("Das_Martin.txt");
    string abstract;
    string lower_abstract;
    string s2 = "aim";
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
    }
    else {
        cerr << "Erreur fichier non ouvrable" << endl;
        return 0;
    }
    if (line != 0)
    {
        of.clear();
        of.seekg(0);
        return line;
    }
    else
    {
        of.clear();
        of.seekg(0);
        return 0;
    }   
}

int findIntro(fstream &of){
    string abstract;
    string lower_abstract;
    string s2 = "1958";
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
    }
    else {
        cerr << "Erreur fichier non ouvrable" << endl;
        return 0;
    }
    if (line != 0)
    {
        of.clear();
        of.seekg(0);
        return line;
    }
    else
    {
        of.clear();
        of.seekg(0);
        return 0;
    }   
}

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
            if (lower_abstract.find(s2) != std::string::npos || lower_abstract.find(s3) != std::string::npos) {
              found = true;
            }
            else{
                abstract.clear();
                getline(of, abstract);
                line++;
            }   
        }      
        if (line != 0)
        {
            of.clear();
            of.seekg(0);
            return line;
        }
        else
        {
            of.clear();
            of.seekg(0);
            return 0;
        }
    }
    else {
        cerr << "Erreur fichier non ouvrable" << endl;
        return 0;
    }
    
    
}

// int extractAbstract(fstream &of, int start, int end){
//     string abstract, extracted;
//     string lower_abstract;
//     bool found = false;
//     int line = start;
//     if (of.is_open())
//     {
//         while (line <= end){
//             getline(of, extracted);
//             abstract = abstract + "\n" + extracted;
//             line++;
//         }
//         cout << abstract;
//     }
//     return 0;   
// }


int main(int argc, char const *argv[])
{
    fstream of;
    of.open("Das_Martin.txt");
    int start = findAbstract(of);
    if (start == 0){
        start = findUni(of);
    }
    int end = findIntro(of);
    // GotoLine(of, start);
    // cout << start << " " << end << endl;
    // extractAbstract(of, start, end);
    return 0;
}
