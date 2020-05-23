#ifndef MODEL_H
#define MODEL_H

#include <structure/boundingBox.h>
#include <structure/camera.h>
class Model {
    public:
        Model() {
            this -> boundingBox = new BoundingBox();
        }

        Model(float rotation, float scale, glm::vec3 translate){
            this -> rotation = new float(rotation);
            this -> scale = new float(scale);
            this -> translate = translate;
            this -> boundingBox = new BoundingBox();
        }

        Model(float rotation, float scale, glm::vec3 translate, glm::vec3 direction){
            this -> rotation = new float(rotation);
            this -> scale = new float(scale);
            this -> translate = translate;
            this -> boundingBox = new BoundingBox();
            this -> direction = direction;
        }

        float* rotation;
        float* scale;
        glm::vec3 translate;
        glm::vec3 direction;
        int visible = true;
        float elapsedTime = 0;
        int dynamic = false;
        int scenario = false;
        BoundingBox* boundingBox;

        void move(float deltaTime){
            translate.x = calculateNextPosition(direction.x, translate.x);
            translate.y = calculateNextPosition(direction.y, translate.y);
            translate.z = calculateNextPosition(direction.z, translate.z);
            elapsedTime += deltaTime;
            if(elapsedTime > 20)
                visible = false;
        }

        void handleCollision(Model* model, Camera* camera){
            if (model -> dynamic) {
                model -> visible = false;
            } else {
                this->reflect(camera);
            }
        }

        bool hasCollided(Model* model){
            float distance = getDistance(&model->translate, &this-> translate);
            float radiusSum = model->getBorder() + this -> getBorder();
            return (distance < radiusSum);
        }

        void reflect(Camera* camera){
            this -> direction = glm::cross(this -> direction, glm::normalize(glm::cross(camera->Right, camera->Front)));
        }

        float getBorder() {
            return boundingBox -> getBorder(*this -> scale);
        }

        float getDistance(glm::vec3* pointA, glm::vec3* pointB){
            glm::vec3 distance = {pointA -> x - pointB -> x,
                                  pointA -> y - pointB -> y,
                                  pointA -> z - pointB -> z};
            return sqrt(pow(distance.x,2) + pow(distance.y,2) + pow(distance.z,2));
        }

        GLfloat calculateNextPosition(GLfloat direction, GLfloat lastPosition){
            GLfloat result = .9f * sin(direction) + lastPosition;
            return result;
        }
};
#endif