#include "LightsManager.h"

LightsManager::LightsManager() {
    // Luz ambiental global
    lightG.ambient = glm::vec3(0.5, 0.5, 0.5);

    lightD.resize(1);
    lightP.resize(1);
    lightF.resize(3);

    // Luces direccionales
    lightD[0].direction = glm::vec3(-1.0, 0.0, 0.0);
    lightD[0].ambient   = glm::vec3( 0.1, 0.1, 0.1);
    lightD[0].diffuse   = glm::vec3( 0.7, 0.7, 0.7);
    lightD[0].specular  = glm::vec3( 0.7, 0.7, 0.7);
    // Luces posicionales
    lightP[0].position    = glm::vec3(0.0, 3.0, 0.0);
    lightP[0].ambient     = glm::vec3(0.2, 0.2, 0.2);
    lightP[0].diffuse     = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].specular    = glm::vec3(0.9, 0.9, 0.9);
    lightP[0].c0          = 1.00;
    lightP[0].c1          = 0.22;
    lightP[0].c2          = 0.20;
    // Luces focales
    // lightF[0] = Luz de cámara (linterna) - se actualiza en renderScene
    lightF[0].position    = glm::vec3(0.0,  0.0,  0.0);
    lightF[0].direction   = glm::vec3(0.0,  0.0, -1.0);
    lightF[0].ambient     = glm::vec3(0.1,  0.1,  0.1);
    lightF[0].diffuse     = glm::vec3(0.8,  0.8,  0.8);
    lightF[0].specular    = glm::vec3(1.0,  1.0,  1.0);
    lightF[0].innerCutOff = 12.5;
    lightF[0].outerCutOff = 17.5;
    lightF[0].c0          = 1.000;
    lightF[0].c1          = 0.09;
    lightF[0].c2          = 0.032;
    // lightF[1] = Luz focal fija en la escena
    lightF[1].position    = glm::vec3( 4.0,  2.0,  7.0);
    lightF[1].direction   = glm::vec3(-5.0, -1.9, -3.5);
    lightF[1].ambient     = glm::vec3( 1.0,  1.0,  1.0);
    lightF[1].diffuse     = glm::vec3( 5.0,  5.0,  5.0);
    lightF[1].specular    = glm::vec3( 5.0,  5.0,  5.0);
    lightF[1].innerCutOff = 5.0;
    lightF[1].outerCutOff = lightF[1].innerCutOff + 4.0;
    lightF[1].c0          = 1.000;
    lightF[1].c1          = 0.080;
    lightF[1].c2          = 0.032;
    // lightF[2] = Luz focal frontal para el libro (desactivada por defecto)
    lightF[2].position    = glm::vec3( 0.0,  100.0,  0.0);
    lightF[2].direction   = glm::vec3( 0.0, -1.0, -1.0);
    lightF[2].ambient     = glm::vec3( 0.0,  0.0,  0.0);
    lightF[2].diffuse     = glm::vec3( 0.0,  0.0,  0.0);
    lightF[2].specular    = glm::vec3( 0.0,  0.0,  0.0);
    lightF[2].innerCutOff = 15.0;
    lightF[2].outerCutOff = 25.0;
    lightF[2].c0          = 1.000;
    lightF[2].c1          = 0.050;
    lightF[2].c2          = 0.020;
}

LightsManager::~LightsManager(){}

void LightsManager::addLightD(const Light& light) {
    lightD.push_back(light);
}
void LightsManager::addLightP(const Light& light) {
    lightP.push_back(light);
}
void LightsManager::addLightF(const Light& light) {
    lightF.push_back(light);
}

void LightsManager::updateCameraLight(const glm::vec3& position, const glm::vec3& direction) {
    // Actualiza la luz focal de la cámara (lightF[0]) con la posición y dirección de la cámara
    if (lightF.size() > 0) {
        lightF[0].position = position;
        lightF[0].direction = glm::normalize(direction);
    }
}

void LightsManager::setLightDDirection(int index, const glm::vec3& direction) {
    // Cambia la dirección de la luz direccional (para simular rotación del sol)
    if (index >= 0 && index < static_cast<int>(lightD.size())) {
        lightD[index].direction = glm::normalize(direction);
    }
}

void LightsManager::turnOffDirectionalLights() {
    for (auto& light : lightD) {
        light.ambient  = glm::vec3(0.0, 0.0, 0.0);
        light.diffuse  = glm::vec3(0.0, 0.0, 0.0);
        light.specular = glm::vec3(0.0, 0.0, 0.0);
    }
}

void LightsManager::turnOffPositionalLights() {
    for (auto& light : lightP) {
        light.ambient  = glm::vec3(0.0, 0.0, 0.0);
        light.diffuse  = glm::vec3(0.0, 0.0, 0.0);
        light.specular = glm::vec3(0.0, 0.0, 0.0);
    }
}

void LightsManager::setSpellLight(const glm::vec3& position) {
    if (lightF.size() > 1) {
        lightF[1].position   = position;
        lightF[1].direction  = glm::vec3(-1.0, -1.0, -1.0); 
        lightF[1].ambient    = glm::vec3(1.0, 1.0, 1.0);
        lightF[1].diffuse    = glm::vec3(1.0, 1.0, 1.0);
        lightF[1].specular   = glm::vec3(1.0, 1.0, 1.0);
        lightF[1].innerCutOff = 50.0;
        lightF[1].outerCutOff = 100.0;
        lightF[1].c0         = 1.000;
        lightF[1].c1         = 0.020;
        lightF[1].c2         = 0.005;
    }
}

void LightsManager::setFrontSpotlight() {
    if (lightF.size() > 2) {
        lightF[2].position   = glm::vec3(-1.6, 2.7, 0.0);
        lightF[2].direction  = glm::vec3(0.0, 0.0, -1.0); 
        lightF[2].ambient    = glm::vec3(0.5, 0.5, 0.5);
        lightF[2].diffuse    = glm::vec3(1.5, 1.5, 1.5);
        lightF[2].specular   = glm::vec3(1.0, 1.0, 1.0);
        lightF[2].innerCutOff = 5.0;
        lightF[2].outerCutOff = 10.0;
    }
}

void LightsManager::turnOffFrontSpotlight() {
    if (lightF.size() > 2) {
        lightF[2].position   = glm::vec3(0.0, 100.0, 0.0);
        lightF[2].ambient    = glm::vec3(0.0, 0.0, 0.0);
        lightF[2].diffuse    = glm::vec3(0.0, 0.0, 0.0);
        lightF[2].specular   = glm::vec3(0.0, 0.0, 0.0);
    }
}