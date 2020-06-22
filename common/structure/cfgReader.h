#ifndef CG_TRACK_CFGREADER_H
#define CG_TRACK_CFGREADER_H
using namespace std;

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
            handleScreen(stream);
        } else if (token == "camera") {
            handleCamera(stream);
        } else if (token == "vs") {
            handleVertexShader(stream);
        } else if (token == "fs") {
            handleFragmentShader(stream);
        } else if (token == "reader") {
            handleReader(stream);
        } else if (token == "model") {
            handleModel();
        } else if (token == "rotation") {
            handleRotation(stream);
        } else if (token == "scale") {
            handleScale(stream);
        } else if (token == "translate") {
            handleTranslate(stream);
        } else if (token == "dynamic") {
            handleDynamic();
        } else if (token == "scenario") {
            handleScenario();
        } else if (token == "readerIndex") {
            handleReaderIndex(stream);
        }
    }

    void handleDynamic() { currentModel-> dynamic = true; }

    void handleScenario() { currentModel-> scenario = true; }

    void handleReaderIndex(stringstream *stream) {
        int index = (int)(floatReader.read(stream));
        readerIndex = index;
    }

    void handleTranslate(stringstream *stream) {
        glm::vec3 translate = vec3Reader.read(stream);
        currentModel-> translate = translate;
    }

    void handleScale(stringstream *stream) {
        GLfloat* scale = new GLfloat(floatReader.read(stream));
        currentModel-> scale = scale;
    }

    void handleRotation(stringstream *stream) {
        GLfloat* rotation = new GLfloat(floatReader.read(stream));
        currentModel-> rotation = rotation;
    }

    void handleModel() {
        if(currentModel){
            scene-> objects -> push_back(readers-> at(readerIndex) -> read(currentModel));
            currentModel = new Model();
        }
        currentModel = new Model();
    }

    void handleReader(stringstream *stream) {
        string filePath = stringReader.read(stream);
        readers-> push_back(new ObjReader(filePath));
    }

    void handleFragmentShader(stringstream *stream) {
        fragmentShaderPath = stringReader.read(stream);
        if (vertexShaderPath != "")
            scene->initShader(vertexShaderPath, fragmentShaderPath);
    }

    void handleVertexShader(stringstream *stream) {
        vertexShaderPath = stringReader.read(stream);
        if (fragmentShaderPath != "")
            scene->initShader(vertexShaderPath, fragmentShaderPath);
    }

    void handleCamera(stringstream *stream) {
        glm::vec3 cameraValues = vec3Reader.read(stream);
        scene->camera = new Camera(cameraValues);
    }

    void handleScreen(stringstream *stream) {
        glm::vec2 screenSize = vec2Reader.read(stream);
        scene->screenSize = new glm::vec2(screenSize);
        initOpenGL();
    }

    void initOpenGL() {
        GlfwConfig glfw;
        glfw.init(*scene-> screenSize);
        scene-> window = glfw.getWindow();
        GlewConfig glew;
        glew.init();
    }
};


#endif //CG_TRACK_CFGREADER_H
