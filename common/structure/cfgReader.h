#ifndef CG_TRACK_CFGREADER_H
#define CG_TRACK_CFGREADER_H
using namespace std;
#define OBJ_MESA "mesa/mesa01.obj"
#define OBJ_PAINTBALL "paintball/cenaPaintball.obj"

#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <structure/scene.h>
#include <structure/objReader.h>

class CfgReader : public FileReader<Scene*>{
public:
    CfgReader(string filePath) : FileReader(filePath) {

    }
    Scene* read(){
        this -> scene = new Scene();
        this -> readers = new vector<ObjReader*>();
        this -> currentModel = nullptr;
        FileReader::processFile();
        scene -> objects -> push_back(readers -> at(readerIndex) -> read(currentModel));

        return scene;
    }

private:
    Scene* scene;
    Model* currentModel;
    int readerIndex;
    vector<ObjReader*>* readers;

    Vec2StreamReader vec2Reader;
    Vec3StreamReader vec3Reader;
    FloatStreamReader floatReader;

    string vertexShaderPath;
    string fragmentShaderPath;

    void handleToken(stringstream* stream) {
        string token = stringReader.read(stream);

        if (token == "screen") {
            glm::vec2 screenSize = vec2Reader.read(stream);
            scene->screenSize = new glm::vec2(screenSize);
            initOpenGL();
        } else if (token == "camera") {
            glm::vec3 cameraValues = vec3Reader.read(stream);
            scene->camera = new Camera(cameraValues);
        } else if (token == "vs") {
            vertexShaderPath = stringReader.read(stream);
            if (fragmentShaderPath != "")
                scene->initShader(vertexShaderPath, fragmentShaderPath);
        } else if (token == "fs") {
            fragmentShaderPath = stringReader.read(stream);
            if (vertexShaderPath != "")
                scene->initShader(vertexShaderPath, fragmentShaderPath);
        } else if (token == "reader") {
            string filePath = stringReader.read(stream);
            readers -> push_back(new ObjReader(filePath));
        } else if (token == "model") {
            if(currentModel){
                scene -> objects -> push_back(readers -> at(readerIndex) -> read(currentModel));
                currentModel = new Model();
            }
            currentModel = new Model();
        } else if (token == "rotation") {
            GLfloat* rotation = new GLfloat(floatReader.read(stream));
            currentModel -> rotation = rotation;
        } else if (token == "scale") {
            GLfloat* scale = new GLfloat(floatReader.read(stream));
            currentModel -> scale = scale;
        } else if (token == "translate") {
            glm::vec3 translate = vec3Reader.read(stream);
            currentModel -> translate = translate;
        } else if (token == "dynamic") {
            currentModel -> dynamic = true;
        } else if (token == "scenario") {
            currentModel -> scenario = true;
        } else if (token == "readerIndex") {
            int index = (int)(floatReader.read(stream));
            readerIndex = index;
        }
    }

    void initOpenGL() const {
        GlfwConfig glfw;
        glfw.init(*scene-> screenSize);
        scene-> window = glfw.getWindow();
        GlewConfig glew;
        glew.init();
    }

    Mesh* duplicateObject(Model* modelData, Mesh *origin) {
        Mesh* newMesh = new Mesh(modelData);
        newMesh->copy(origin);
        newMesh -> model.boundingBox = origin -> model.boundingBox;
        return newMesh;
    }

};


#endif //CG_TRACK_CFGREADER_H
