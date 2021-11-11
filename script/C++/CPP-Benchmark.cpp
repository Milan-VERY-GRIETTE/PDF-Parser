#include <iostream>
#include <vector>
#include <fstream>
#include <ctime> 
#include <chrono>

int main()
{
    std::cout << "Debut du benchmark. Veuillez patienter..." << std::endl;

    // Seed
    srand(time(NULL));

    // Create and fill
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> matrix;
    std::vector<int> tempLine;

    for (int i = 0; i < 1000; i++) {
        tempLine.clear();
        for (int j = 0; j < 1000; j++) {
            tempLine.push_back((rand() % 10000));
        }
        matrix.push_back(tempLine);
    }

    // Display first time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Test 1 (matrice aleatoire): " << duration1.count() << "ms" << std::endl;


    // Write to file
    start = std::chrono::high_resolution_clock::now();

    std::fstream outFile;
    outFile.open("cpp-benchmark.txt", std::ios::out);
    if (!outFile) {
        std::cerr << "Erreur: impossible d'écrire le fichier de benchmark" << std::endl;
        exit(1);
    }

    for (auto i : matrix) {
        for (auto j : i) {
            outFile << j << " ";
        }
        outFile << std::endl;
    }
    outFile.close();

    // Display second time
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Test 2 (ecriture): " << duration2.count() << "ms" << std::endl;


    // Read file
    start = std::chrono::high_resolution_clock::now();
    
    std::fstream inFile;
    inFile.open("cpp-benchmark.txt", std::ios::in);
    if (!inFile) {
        std::cerr << "Erreur: impossible de lire le fichier de benchmark" << std::endl;
        exit(1);
    }

    std::string tempValue;
    while (!inFile.good()) {
        inFile >> tempValue;
    }
    inFile.close();

    // Display third time
    stop = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Test 3 (lecture): " << duration3.count() << "ms" << std::endl;

    std::cout << "Temps d execution total: " << duration1.count() + duration2.count() + duration3.count() << "ms" << std::endl;
}   
