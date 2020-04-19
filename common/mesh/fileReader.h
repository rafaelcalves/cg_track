#ifndef FILEREADER_H
#define FILEREADER_H
using namespace std;

template <typename T>
class FileReader {
    public: 
        string filePath;
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
};
#endif