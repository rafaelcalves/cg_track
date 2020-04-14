#include <math.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
class Reflection {
    public:
        Reflection(GLfloat directionX, GLfloat directionY, GLfloat speed){
            direction.x = directionX;
            direction.y = directionY;
            lastPosition.x = .0f;
            lastPosition.y = .0f;
            this -> speed = speed;
        }

        glm::mat4 calculateReflectedMatrix(glm::mat4 matrix){
            direction.x = getReflectiondirection(lastPosition.x, direction.x);
            direction.y = getReflectiondirection(lastPosition.y, direction.y);

            matrix[3][0] = calculateNextPosition(speed, direction.x, lastPosition.x);
            matrix[3][1] = calculateNextPosition(speed, direction.y, lastPosition.y);
            lastPosition.x = matrix[3][0];
            lastPosition.y = matrix[3][1];
            return matrix;
        }
    private: 
        glm::vec2 direction;
        glm::vec2 lastPosition;
        GLfloat speed;

        GLfloat getReflectiondirection(GLfloat lastPosition, GLfloat direction){
            if (hasHitAWall(lastPosition)) {
                GLfloat normal = getNormal(lastPosition);
                return calculateReflection(normal, direction);
            }
            return direction;
        }
        GLfloat calculateNextPosition(GLfloat speed, GLfloat direction, GLfloat lastPosition){
            GLfloat result = speed * sin(direction) + lastPosition;
            return result;
        }
        GLfloat hasHitAWall(GLfloat lastPosition){ 
            return fabs(lastPosition) + 0.5f > 1.0f;
        }
        GLfloat getNormal(GLfloat lastPosition){
        return lastPosition > 0 ? 1 : -1;
        }
        GLfloat calculateReflection(GLfloat normal, GLfloat direction){
            return 2 * normal * (normal * - direction) + direction;
        }
};