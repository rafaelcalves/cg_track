#include <glm/glm.hpp>
#include <mesh/group.h>
class Mesh {
    private:
        glm::vec3 vertices [];
        glm::vec3 normals [];
        glm::vec2 mappings [];
        Group groups [];
};