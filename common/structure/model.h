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
        int iteration = 0;
        vector<glm::vec3>* route = nullptr;

        void move(float deltaTime){
            elapsedTime += deltaTime;

            if(route) {
                iteration++;
                if(iteration == route->size()) iteration=0;
                glm::vec3 nextPosition = route->at(iteration);
                nextPosition.y += 1.0f;
                calculateDirection(translate, nextPosition);
                translate = nextPosition;
            } else {
                if(elapsedTime > 20)
                    visible = false;
                translate.x = calculateNextPosition(direction.x, translate.x);
                translate.y = calculateNextPosition(direction.y, translate.y);
                translate.z = calculateNextPosition(direction.z, translate.z);
            }

        }

        void calculateDirection(glm::vec3 position, glm::vec3 direction) {
            GLfloat dx = direction.x - position.x;
            GLfloat dz = direction.z - position.z;

            GLfloat angle = glm::atan(dz, dx);

            this-> rotation = new float(-angle + 5);
        }

        void handleCollision(Model* model){
            if (model -> dynamic) {
                model -> visible = false;
            } else {
                this->reflect(model);
            }
        }

        bool hasCollided(Model* model){
            float distance = getDistance(&model->translate, &this-> translate);
            float radiusSum = model->getBorder() + this -> getBorder();
            return (distance < radiusSum);
        }

        glm::vec3 getOrigin(){
            return this->translate + this->boundingBox->getOrigin();
        }

        void reflect(Model* model){
            glm::vec3 origin = model->getOrigin();
            glm::vec3 normal = glm::normalize(this -> translate - origin);
            this -> direction = glm::reflect(this -> direction, normal);
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