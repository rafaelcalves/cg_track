//
// Created by Correa, Rafael on 19/05/20.
//

#ifndef CG_TRACK_CONFIGURATION_H
#define CG_TRACK_CONFIGURATION_H

#define OBJ_MESA "mesa/mesa01.obj"
#define OBJ_PAINTBALL "paintball/cenaPaintball.obj"

#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <structure/scene.h>
#include <structure/objReader.h>

class Configuration {
public:
    Scene* init(string configPath){
        Scene* scene = new Scene();
        int WIDTH = 800;
        int HEIGHT = 600;
        scene -> screenSize = new glm::vec2 (WIDTH,HEIGHT);

        GlfwConfig glfw;
        glfw.init(*scene -> screenSize);
        scene -> window = glfw.getWindow();
        GlewConfig glew;
        glew.init();

        scene -> shader = new Shader("shaders/model_loading.vs", "shaders/model_loading.fs");
        scene -> shader -> use();
        scene -> objects = new vector<Mesh*>();

        scene -> camera =  new Camera(glm::vec3(1.0f, 20.0f, 50.0f));

        Model* modelTable = new Model(0.0f, 0.66f, {-10.16f, .0f, -2.68f});
        ObjReader tableReader(OBJ_MESA);
        Mesh* table = tableReader.read(modelTable);
        table -> model = *modelTable;
        scene -> objects->push_back(table);

        modelTable = new Model( 0.0f, 0.66f, {10.16f, .0f, -2.68f});
        modelTable -> dynamic = true;
        scene -> objects -> push_back(duplicateObject(modelTable, table));

        Model* modelPaintball = new Model(0.0f, 0.66f, {0.00f, 0.0f, -2.68f});
        modelPaintball->scenario = true;
        ObjReader paintballReader(OBJ_PAINTBALL);
        Mesh* paintball = paintballReader.read(modelPaintball);
        paintball -> model = *modelPaintball;
        scene -> objects -> push_back(paintball);

        return scene;
    }
    Mesh* duplicateObject(Model* modelData, Mesh *origin) {
        Mesh* newMesh = new Mesh(modelData);
        newMesh->copy(origin);
        newMesh -> model.boundingBox = origin -> model.boundingBox;
        return newMesh;
    }

};


#endif //CG_TRACK_CONFIGURATION_H
