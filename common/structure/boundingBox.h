#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
class BoundingBox {
    public:
        glm::vec3* maxVertex = nullptr;
        glm::vec3* minVertex = nullptr;

        void process(glm::vec3* vertex) {
            if(minVertex){
                processMaxVertex(vertex);
                processMinVertex(vertex);
                return;
            }
            minVertex = new glm::vec3 (*vertex);
            maxVertex = new glm::vec3 (*vertex);
            return;
        }

        glm::vec3 getOrigin(){
            float originX =  (maxVertex -> x + minVertex -> x)/2;
            float originY =  (maxVertex -> y + minVertex -> y)/2;
            float originZ =  (maxVertex -> z + minVertex -> z)/2;
            glm::vec3 origin(originX,originY,originZ);
            return origin;
        };

        float getBorder(float scale){
            float distance = getDistance(maxVertex, minVertex);
            return (distance / 2) * scale;
        }

        float getDistance(glm::vec3* pointA, glm::vec3* pointB){
            glm::vec3 distance = {maxVertex -> x - minVertex -> x,
                                  maxVertex -> y - minVertex -> y,
                                  maxVertex -> z - minVertex -> z};
            return sqrt(pow(distance.x,2) + pow(distance.y,2) + pow(distance.z,2));
        }

    private:
        void processMinVertex(glm::vec3* vertex) {
            processMin(&vertex -> x, &minVertex -> x);
            processMin(&vertex -> y, &minVertex -> y);
            processMin(&vertex -> z, &minVertex -> z);
        }

        void processMaxVertex(glm::vec3* vertex) {
            processMax(&vertex -> x, &maxVertex -> x);
            processMax(&vertex -> y, &maxVertex -> y);
            processMax(&vertex -> z, &maxVertex -> z);
        }

        void processMin(GLfloat* value, GLfloat* minValue) {
            if (*value < *minValue) {
                *minValue = *value;
            }
        }

        void processMax(GLfloat* value, GLfloat* minValue) {
            if (*value > *minValue) {
                *minValue = *value;
            }
        }
};
#endif
