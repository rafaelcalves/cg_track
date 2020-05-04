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
