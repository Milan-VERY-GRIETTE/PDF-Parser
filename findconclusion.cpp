
int findconclusion(std::fstream &of, int start){
    std::string bodyfind;
    std::string lower_bodyfind;
    //Diverse string on étaient créées afin de convenir au différents types de pdf existant
    std::string s2 = "conclusion";
    std::string s3 = "summary";
    std::string s4 = "resume";
   
    bool found = false;
    int line = start;
    if (of.is_open()) {
        getline(of, bodyfind);
        std::locale loc;
        while (!found){
            for (std::string::size_type i=0; i<bodyfind.length(); ++i){
                lower_bodyfind += tolower(bodyfind[i],loc);
                
            }
           
            if (lower_bodyfind.find(s2) != std::string::npos   || lower_bodyfind.find(s3) != std::string::npos &&lower_bodyfind.find(s4) != std::string::npos) {
              found = true;
            }
          
            else{
                bodyfind.clear();
                getline(of, bodyfind);
                line++;
            }
        }
        of.clear();
        of.seekg(0);
        int skipped = 0;
        GotoLine(of, line-1);
        getline(of, bodyfind);

        while (bodyfind == "\n" || bodyfind == "1\n" || bodyfind == "" || bodyfind == "1." || bodyfind == "1" )
        {
            skipped--;
            GotoLine(of, line + skipped);
            getline(of, bodyfind);
        }
        return line + skipped;
        
    }
    else {
        std::cerr << "> Erreur : Impossible d'ouvrir le fichier temporaire." << std::endl;
        return 0;
    }
}
