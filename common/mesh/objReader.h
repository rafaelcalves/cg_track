#ifndef OBJREADER_H
#define OBJREADER_H
using namespace std;

#include <mesh/mesh.h>
#include <mesh/mtlReader.h>
#include <mesh/streamReader.h>

class ObjReader {
    public:
        void setFilePath(string filePath){
            this -> filePath = filePath;
        }

        Mesh* read(){
            this -> mesh = new Mesh;
            this -> currentGroup = new Group();
            ifstream arq(this -> filePath);
            while(!arq.eof()){
                stringstream lineStream = getLineStream(&arq);
                handleToken(&lineStream);
            }
            mesh -> insertGroup(currentGroup);
            return mesh;
        }
    private: 
        string filePath;
        Mesh* mesh;
        Group* currentGroup;
        vector<Material*>* materials;

        StringStreamReader stringReader;
        Vec3StreamReader vec3Reader;
        Vec2StreamReader vec2Reader;
        FaceStreamReader faceReader;

        stringstream getLineStream(ifstream* fileStream){
            string line;
            getline(*fileStream, line);
            stringstream lineStream;
            lineStream << line;
            return lineStream;
        }

        void handleToken(stringstream* stream){
            string token = stringReader.read(stream);
            if(token == "v"){
                handleVertex(stream);
            } else if (token == "vn") {
                handleNormal(stream);
            } else if (token == "vt") {
                handleTexture(stream);
            } else if (token == "f") {
                handleFace(stream);
            } else if (token == "g"){
                handleGroup(stream);
            } else if (token == "mtllib"){
                handleMtlLib(stream);
            } else if (token == "usemtl"){
                handleGroupMtl(stream);
            }
        }

        void handleVertex(stringstream* stream){
            glm::vec3 vertex = vec3Reader.read(stream);
            this -> mesh->insertVertex(vertex);
        }

        void handleNormal(stringstream* stream){
            glm::vec3 normal = vec3Reader.read(stream);
            this -> mesh->insertNormal(normal);
        }

        void handleTexture(stringstream* stream){
            glm::vec2 mapping = vec2Reader.read(stream);
            this -> mesh -> insertMapping(mapping);
        }

        void handleFace(stringstream* stream){
            Face* face = faceReader.read(stream);
            this -> currentGroup -> insertFace(face);
        }

        void handleGroup(stringstream* stream){
            string name = stringReader.read(stream);
            if(this -> currentGroup -> hasFaces()){
                this -> mesh -> insertGroup(currentGroup);
            }
            this -> currentGroup = new Group(name);
        }

        void handleMtlLib(stringstream* stream){
            string materialLibPath = stringReader.read(stream);
            this -> mesh -> setMaterialLib(materialLibPath);
            this -> materials = loadMaterialsFromPath(&materialLibPath);
        }

        void handleGroupMtl(stringstream* stream){
            string materialName = stringReader.read(stream);
            this -> currentGroup -> setMaterial(materialName, this -> materials);
        }

        string getObjDirectory(){
            size_t lastSlashPosition = this -> filePath.find_last_of("/\\");
            return filePath.substr(0,lastSlashPosition);
        }

        vector<Material*>* loadMaterialsFromPath(string* path){
            string objDirectory = getObjDirectory();
            string mtlLibFullPath = objDirectory + "/" + *path;
            MtlReader mtlReader(mtlLibFullPath);
            return mtlReader.read();
        }

};
#endif