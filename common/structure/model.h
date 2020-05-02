#ifndef MODEL_H
#define MODEL_H

class Model {
    public:
        Model() {}

        Model(float rotation, float scale, glm::vec3* translate){
            this -> rotation = new float(rotation);
            this -> scale = new float(scale);
            this -> translate = translate;
        }

        float* rotation;
        float* scale;
        glm::vec3* translate;
};
#endif