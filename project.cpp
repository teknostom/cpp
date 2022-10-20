// Tom Evaldsson PAGPT21 PA1414 LP1 2022

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "headerfiles/formatter.h"
#include "headerfiles/Rules.h"
#include "io.h"
#include "fcntl.h"
#include <chrono>
int main(int argc, char **argv)
{
    std::string filename = "";
    std::string output = "output.tex";
    std::string config = "config.json";
    bool timer = false;
    bool debug = false;
    bool help = false;
    //Handle all flags
    if(argc <= 1) help = true;
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            //Parse flags
            if(argv[i][1] == 'o'){
                output = argv[i+1];
                i++;
            }
            if(argv[i][1] == 't'){
                timer = true;
            }
            if(argv[i][1] == 'd'){
                debug = true;
            }
            if(argv[i][1] == 'h'){
                help = true;
            }
            if(argv[i][1] == 'c'){
                config = argv[i+1];
                i++;
            }
        }else{
            if(filename != ""){
                std::cout << "Multiple files specified." << std::endl;
                std::exit(0);
            }
            filename = argv[i];
        }
    }
    if(help){
        _setmode(_fileno(stdout), _O_U8TEXT);
        const wchar_t MID = L'\x251C';
        const wchar_t END = L'\x2514';
        const wchar_t line = L'\x2574';
        std::wcout <<    "This is the help command." << std::endl <<
                        MID << line << "-o: Enter a filename after this flag to specify output." << std::endl <<
                        MID << line << "-c: Enter a filename after this flag to specify config." << std::endl <<
                        MID << line << "-t: This flag allows timer to be shown." << std::endl <<
                        MID << line << "-d: This flag allows debug mode to be set." << std::endl <<
                        END << line << "-h: This flag shows the help menu, it cannot be used in execution." << std::endl;
        std::exit(0);
    }
    //Handle filename;
    if(filename == ""){
        std::cout << "No file specified" << std::endl;
        std::exit(0);
    }
    if(filename.substr(filename.length() - 4, 4) != ".tex"){
        std::cout << "The file specified is not a tex file." << std::endl;
        std::exit(0);
    }
    
    

    auto start = std::chrono::steady_clock::now();
    auto startin = std::chrono::steady_clock::now();
    //Setup file reading
    std::string linebuffer;
    std::ifstream File(filename);
    //Check if file is good:
    int k = 95;

    //Read file;
    file workingfile = file();

    while(std::getline(File, linebuffer)){
        workingfile.addline(linebuffer);
    }
    File.close();
    if(debug == true) std::cout << "[1/1] File has been read. {" << filename << "}" << std::endl;

    //format file
    Rules r = Rules(config);
    Formatter f = Formatter();
    auto endin = std::chrono::steady_clock::now();
    auto startfo = std::chrono::steady_clock::now();
    workingfile = f.formatFile(workingfile, r, debug);
    auto endfo = std::chrono::steady_clock::now();
    
    //all output
    auto startou = std::chrono::steady_clock::now();
    std::ofstream op(output);
    
    for(int i = 0; i < workingfile.getlinecount(); i++){
        op << workingfile.getline(i) << ((i>=workingfile.getlinecount()) ? "" : "\n");
    }
    workingfile.reset();
    
	const wchar_t MID = L'\x251C';
	const wchar_t END = L'\x2514';
    op.close();
    auto endou = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    if(debug == true) std::cout << "[1/1] File has been written. {" << output << "}" << std::endl;
    _setmode(_fileno(stdout), _O_U8TEXT);
    if(timer == true)std::wcout << "Total:        "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl
        << "reading:      " << MID << std::chrono::duration_cast<std::chrono::milliseconds>(endin - startin).count() << " ms" << std::endl
        << "formatting:   " << MID << std::chrono::duration_cast<std::chrono::milliseconds>(endfo - startfo).count() << " ms" << std::endl
        << "outputting:   " << END << std::chrono::duration_cast<std::chrono::milliseconds>(endou - startou).count()
        << " ms" << std::endl;
    return 0;
}