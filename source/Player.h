#pragma once

#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include <math.h>
#include <map>

class Player{
    private:
        float position[3] = {8.0, 5.0, 7.0};
        float heading[3] = {0.0, 0.0, 0.0};
        float lookDirection[3] = {0.0, 0.0, 0.0};
        float movementSpeed = 1.0 / 60.0;
        float rotationSpeed = 1.0 / 60.0;

    public:
        Player(float moveSpeed, float rotationSpeed, float startingPosition[3]){
            position[0] = startingPosition[0];
            position[1] = startingPosition[1];
            position[2] = startingPosition[2];

            movementSpeed = movementSpeed;
            rotationSpeed = rotationSpeed;
        }

        void update(std::map<int, bool>& keys){
            if(keys[GLFW_KEY_UP] == true){
                heading[2] += rotationSpeed;
            }
            if(keys[GLFW_KEY_DOWN] == true){
                heading[2] -= rotationSpeed;
            }
            if(keys[GLFW_KEY_LEFT] == true){
                heading[0] += rotationSpeed;
            }
            if(keys[GLFW_KEY_RIGHT] == true){
                heading[0] -= rotationSpeed;
            }

            if(keys[GLFW_KEY_UP] == true){
                position[0] += cos(heading[1]) * ;
            }
        }
};