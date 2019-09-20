//
// Created by heini on 19-09-2019.
//

#ifndef TAREA2_CENTEREDCAMERA_H
#define TAREA2_CENTEREDCAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    ROLL_IN,
    ROLL_OUT,
};

// Default camera values
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;

#define PI 3.1415


//I used a mix of euler angles and spherical coordinates to move the camera position and normal angles
//I know that using spherical coordinates it's quite expensive. If I had more time I would improve it.
class CenteredCamera {
public:
    // Camera attributes
    float Rad;
    float Theta;
    float Phi;
    float Roll;
    glm::vec3 Center;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;

    CenteredCamera(glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f), float radius = 7.0f, float theta = -PI, float phi = -PI) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
    {
        Roll = 0;
        Rad = radius;
        Theta = theta;
        Phi = phi;
        Center = center;

        updateCameraVectors();
    }

    glm::vec3 getCameraPosition(){
        return glm::vec3(Rad*sin(Theta)*cos(Phi),Rad*sin(Theta)*sin(Phi),Rad*cos(Theta));
    }

    glm::mat4 GetViewMatrix()
    {
        glm::vec3 Position = getCameraPosition();
        return glm::lookAt(Position, Position + Front, Up)*glm::eulerAngleX(Roll);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Phi +=  velocity;
        if (direction == BACKWARD)
            Phi -=  velocity;
        if (direction == LEFT)
            Theta -= velocity;
        if (direction == RIGHT)
            Theta += velocity;
        if (direction == ROLL_IN)
            Roll += velocity;
        if (direction == ROLL_OUT)
            Roll -= velocity;
        updateCameraVectors();
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {

    }

    void ProcessMouseScroll(float yoffset)
    {
        Rad += yoffset * MovementSpeed;
        if(Rad < 1.0) Rad = 1.0;
        updateCameraVectors();
    }

private:
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        glm::vec3 Position = getCameraPosition();

        // update the front vector
        front = Center - Position;
        Front = glm::normalize(front);

        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::vec3(cos(Theta)*cos(Phi),cos(Theta)*sin(Phi),-sin(Theta)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

        Up    = glm::normalize(glm::cross(Right, Front));
    }
};

#endif //TAREA2_CENTEREDCAMERA_H
