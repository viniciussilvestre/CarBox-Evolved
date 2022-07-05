#ifndef CAR_CONST_H
#define CAR_CONST_H

int const resX = 1920;
int const resY = 1080;
int const initialWinPosX = 320;
int const initialWinPosY = 120;
int const keyPressedSize = 256;
vetor3 const outerCenter = {0, 0, 0}; // NOLINT(cert-err58-cpp)
vetor3 const outerDistances = {26, 26, 26}; // NOLINT(cert-err58-cpp)
vetor3 const carCollisionBoxDistances = {0.5, 0.3, 1.1}; // NOLINT(cert-err58-cpp)
vetor3 const cameraInitialPos = {-22, 2, 17}; // NOLINT(cert-err58-cpp)
vetor3 const cameraBackInitialPos = {-22, 2, 17}; // NOLINT(cert-err58-cpp)
vetor3 const cameraTopInitialPos = {0, 8, 0}; // NOLINT(cert-err58-cpp)
vetor3 const cameraTopMDir = {0, -1, 0}; // NOLINT(cert-err58-cpp)
vetor3 const cameraBackMDir = {0, 0, 1}; // NOLINT(cert-err58-cpp)
float const carSpeed = 0.20;
int const zFar = 500;
float const zNear = 0.1;
float const leftRightSpeed = 1.5;
float const upDownSpeed = 2.5;
float const maxHeight = 7;
GLfloat const angle = 90;
float const fps = 60;

#endif //CAR_CONST_H
