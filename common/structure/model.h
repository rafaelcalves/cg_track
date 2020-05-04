#ifndef MODEL_H
#define MODEL_H

class Model {
    public:
        Model() {}

        Model(float rotation, float scale, glm::vec3 translate){
            this -> rotation = new float(rotation);
            this -> scale = new float(scale);
            this -> translate = translate;
        }

        Model(float rotation, float scale, glm::vec3 translate, glm::vec3 direction){
            this -> rotation = new float(rotation);
            this -> scale = new float(scale);
            this -> translate = translate;
            this -> direction = direction;
        }

        float* rotation;
        float* scale;
        glm::vec3 translate;
        glm::vec3 direction;

        void move(float elapsedTime){
            translate.x = calculateNextPosition(direction.x, translate.x);
            translate.y = calculateNextPosition(direction.y, translate .y);
        }

        GLfloat calculateNextPosition(GLfloat direction, GLfloat lastPosition){
            GLfloat result = .03f * sin(direction) + lastPosition;
            return result;
        }
};
#endif