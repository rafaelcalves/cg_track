//
// Created by Correa, Rafael on 21/06/20.
//

#ifndef CG_TRACK_TXTREADER_H
#define CG_TRACK_TXTREADER_H
using namespace std;


class TxtReader : public FileReader<vector<glm::vec3>*>{
public:
    TxtReader(string filePath) : FileReader(filePath) {

    }
    vector<glm::vec3>* read(){
        this -> points = new vector<glm::vec3>;
        FileReader::processFile();

        return points;
    }

private:
    vector<glm::vec3>* points;

    Vec3StreamReader vec3Reader;

    void handleToken(stringstream* stream){
        string token = stringReader.read(stream);

        if(token == "v"){
            handlePoint(stream);
        }
    }

    void handlePoint(stringstream* stream){
        glm::vec3 point = vec3Reader.read(stream);
        this -> points -> push_back(point);
    }
};


#endif //CG_TRACK_TXTREADER_H
