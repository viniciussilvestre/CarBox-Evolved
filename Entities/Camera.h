#include "../Util/cg.h"
#include <GL/freeglut.h>
#include "../Util/Const.h"

class Camera
{
    private:
        vetor3 m_pos;
        vetor3 m_dir;
        vetor3 m_left;
        vetor3 m_up;
        vetor3 m_speed;
        float m_scl = carSpeed;
        float m_yaw;
        float m_PI = 3.14159265;

    public:
        explicit Camera(vetor3 pos);
        ~Camera();

        vetor3 getMPos();
        vetor3 getMDir();
        void activate();
        void forward();
        void jump();
        void backward();
        void updateYaw(float dYaw);
        void update();
        void resetCamera();
        void cameraFrontView();
        void cameraBackView();
        void upView();
        void setMDir(vetor3 newMDir);
        vetor3 getSpeed();

    private:
        [[nodiscard]] float cvtToRad(float ang) const;
};
