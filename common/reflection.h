#include <math.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
class Reflection {
    public:
        Reflection(GLfloat speedX, GLfloat speedY){
            speed.x = speedX;
            speed.y = speedY;
            lastPosition.x = .0f;
            lastPosition.y = .0f;
        }

        glm::mat4 calculateReflectedMatrix(glm::mat4 matrix, double elapsedSeconds){
            speed.x = getReflectionPosition(lastPosition.x, speed.x);
            speed.y = getReflectionPosition(lastPosition.y, speed.y);

            matrix[3][0] = calculateNextPosition(elapsedSeconds, speed.x, lastPosition.x);
            matrix[3][1] = calculateNextPosition(elapsedSeconds, speed.y, lastPosition.y);
            lastPosition.x = matrix[3][0];
            lastPosition.y = matrix[3][1];
            return matrix;
        }
    private: 
        glm::vec2 speed;
        glm::vec2 lastPosition;

        GLfloat getReflectionPosition(GLfloat lastPosition, GLfloat speed){
            if (hasHitAWall(lastPosition)) {
                GLfloat normal = getNormal(lastPosition);
                return calculateReflection(normal, speed);
            }
            return speed;
        }
        GLfloat calculateNextPosition(GLfloat elapsedSeconds, GLfloat speed, GLfloat lastPosition){
            return elapsedSeconds * speed + lastPosition;
        }
        GLfloat hasHitAWall(GLfloat lastPosition){ 
            return fabs(lastPosition) + 0.5f > 1.0f;
        }
        GLfloat getNormal(GLfloat lastPosition){
        return lastPosition > 0 ? 1 : -1;
        }
        GLfloat calculateReflection(GLfloat normal, GLfloat speed){
            return 2 * normal * (normal * - speed) + speed;
        }
};