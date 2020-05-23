#ifndef OBJREADER_H
#define OBJREADER_H
using namespace std;

#include <structure/mesh.h>
#include <structure/mtlReader.h>
#include <structure/streamReader.h>

class ObjReader : public FileReader<Mesh*>{
    public:
        ObjReader(string filePath) : FileReader(filePath){

        }

        Mesh* read(Model* model){
            string path = __fs::filesystem::current_path();
            this -> mesh = new Mesh(model);
            this -> currentGroup = new Group();
            return read();
        }

        Mesh* read(){
            this -> currentGroup = new Group();
            FileReader::processFile();
            this -> mesh -> insertGroup(currentGroup);
            return mesh;
        }
    private: 
        Mesh* mesh;
        Group* currentGroup;
        vector<Material*>* materials;

        Vec3StreamReader vec3Reader;
        Vec2StreamReader vec2Reader;
        FaceStreamReader faceReader;

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
            this -> mesh -> materialLibPath = &materialLibPath;
            this -> materials = loadMaterialsFromPath(&materialLibPath);
        }

        void handleGroupMtl(stringstream* stream){
            string materialName = stringReader.read(stream);
            this -> currentGroup -> setMaterial(materialName, this -> materials);
        }

        vector<Material*>* loadMaterialsFromPath(string* path){
            string objDirectory = getFileDirectory();
            string mtlLibFullPath = objDirectory + "/" + *path;
            MtlReader mtlReader(mtlLibFullPath);
            return mtlReader.read();
        }

};
#endif