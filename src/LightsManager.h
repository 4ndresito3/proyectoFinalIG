#ifndef LIGHTS_MANAGER_H
#define LIGHTS_MANAGER_H

#include "Shaders.h"
#include <vector>
class LightsManager {
private:
    std::vector<Light> lightD;
    std::vector<Light> lightP;
    std::vector<Light> lightF;
    Light lightG;
    int findLightIndex(const Light& light);
public:
    LightsManager();
    ~LightsManager();
    Light getLightG() const { return lightG; }
    Light getLightD(int index) const { return lightD[index]; }
    Light getLightP(int index) const { return lightP[index]; }
    Light getLightF(int index) const { return lightF[index]; }

    size_t getNumLightD() const { return lightD.size(); }
    size_t getNumLightP() const { return lightP.size(); }
    size_t getNumLightF() const { return lightF.size(); }

    void addLightD(const Light& light);
    void addLightP(const Light& light);
    void addLightF(const Light& light);

    // Actualiza la luz focal de la cámara (linterna)
    void updateCameraLight(const glm::vec3& position, const glm::vec3& direction);
    
    // Cambia la dirección de la luz direccional (sol)
    void setLightDDirection(int index, const glm::vec3& direction);
};
#endif /*LIGHTS_MANAGER_H*/