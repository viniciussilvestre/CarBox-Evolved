#include "../Util/cg.h"
#include <string>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>
#include "../Util/Const.h"
#include <cmath>

class AABB
{
    private:
        std::string id;
        vetor3 center;
        vetor3 extends;
        vetor3 m_speed = {0, 0, 0};
        vetor3 m_direction = {0, 0 ,-1};
        vetor3 m_jump = {0, 0.25, 0};
        vetor3 m_fall = {0, -0.25, 0};
        std::vector<vetor3> boxCoords;
        float m_yaw;
        float m_scl = carSpeed;
        float m_PI = 3.14159265;
        float height;

    public:
        explicit AABB(std::string newId, vetor3 center, vetor3 distances);
        ~AABB();
        AABB();

        vetor3 getCenter();
        vetor3 getDistances();
        void update(float leftRightDirection, vetor3 camPosVec);
        void setId(std::string newId);
        [[nodiscard]] const std::string &getId() const;
        void forward();
        void jump();
        void fall();
        void backward();
        void setCenter(vetor3 centerCoords);
        void setDistances(vetor3 centerDistances);
        void drawBox() const;
        void createBox();
        void reset(vetor3 camPosVec);
        void setSpeed(float newSpeed);

    private:
        static vetor3 rotate(vetor3 point, float ang, vetor3 axis);
        [[nodiscard]] float cvtToRad(float ang) const;
};
