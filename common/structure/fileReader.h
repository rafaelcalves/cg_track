#ifndef FILEREADER_H
#define FILEREADER_H
using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

template <typename T>
class FileReader {
    public: 
        string filePath;
        StringStreamReader stringReader;
        virtual T read() = 0;

        FileReader(string filePath){
            this -> filePath = filePath; 
        }
    
        virtual void handleToken(stringstream* stream) = 0;

        void processFile(){
            ifstream arq(this -> filePath);
            while(!arq.eof()){
                stringstream lineStream = getLineStream(&arq);
                handleToken(&lineStream);
            }
        }

        stringstream getLineStream(ifstream* fileStream){
            string line;
            getline(*fileStream, line);
            stringstream lineStream;
            lineStream << line;
            return lineStream;
        }

        void setFilePath(string filePath){
            this -> filePath = filePath;
        } 

        string getFileDirectory(){
            size_t lastSlashPosition = this -> filePath.find_last_of("/\\");
            return filePath.substr(0,lastSlashPosition);
        }

        string getFileExtension(string filePath) {
        // Find the last position of '.' in given string
            size_t pos = filePath.rfind('.');
        // If last '.' is found
            if (pos != string::npos) {// return the substring
                 return filePath.substr(pos);
            }
        // In case of no extension return empty string
        return "";
    }
};
#endif