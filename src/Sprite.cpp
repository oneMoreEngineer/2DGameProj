#include "Sprite.h"

bool TriangleShape::inside(vector<glm::vec3> p, glm::vec3 a, glm::mat4 T) {
    glm::vec4 p2 = glm::inverse(T) * glm::vec4(a, 1);
    glm::vec3 v1 = glm::normalize(p[0] - p2);
    glm::vec3 v2 = glm::normalize(p[1] - p2);
    glm::vec3 v3 = glm::normalize(p[2] - p2);
    float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
    float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
    float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
    if (a1 < 0 && a2 < 0 && a3 < 0) return true;
    else return false;
}

void TriangleShape::draw() {
    ofPushMatrix();
    ofMultMatrix(getMatrix());
    ofDrawTriangle(verts[0], verts[1], verts[2]);
    ofPopMatrix();
}

bool Sprite::inside(vector<glm::vec3> p, glm::vec3 a, glm::mat4 T) {

    return TriangleShape::inside(p, a, T);

}
