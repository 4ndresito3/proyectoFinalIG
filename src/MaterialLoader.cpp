#include "MaterialLoader.h"

MaterialLoader::MaterialLoader() {}
MaterialLoader::~MaterialLoader() {}

void MaterialLoader::loadMaterials() {
    mluz.ambient   = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.diffuse   = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.specular  = glm::vec4(0.0, 0.0, 0.0, 1.0);
    mluz.emissive  = glm::vec4(1.0, 1.0, 1.0, 1.0);
    mluz.shininess = 1.0;

    ruby.ambient   = glm::vec4(0.174500, 0.011750, 0.011750, 1.0);
    ruby.diffuse   = glm::vec4(0.614240, 0.041360, 0.041360, 1.0);
    ruby.specular  = glm::vec4(0.727811, 0.626959, 0.626959, 1.0);
    ruby.emissive  = glm::vec4(0.000000, 0.000000, 0.000000, 1.0);
    ruby.shininess = 76.8;

    gold.ambient   = glm::vec4(0.247250, 0.199500, 0.074500, 1.00);
    gold.diffuse   = glm::vec4(0.751640, 0.606480, 0.226480, 1.00);
    gold.specular  = glm::vec4(0.628281, 0.555802, 0.366065, 1.00);
    gold.emissive  = glm::vec4(0.000000, 0.000000, 0.000000, 1.00);
    gold.shininess = 51.2;

    page.ambient   = glm::vec4(0.25, 0.20, 0.15, 1.0);
    page.diffuse   = glm::vec4(0.90, 0.85, 0.80, 1.0);
    page.specular  = glm::vec4(0.20, 0.20, 0.20, 1.0);
    page.emissive  = glm::vec4(0.00, 0.00, 0.00, 1.0);
    page.shininess = 10.0;
}

Material MaterialLoader::getMluz() const { 
    return mluz; 
}
Material MaterialLoader::getRuby() const { 
    return ruby; 
}
Material MaterialLoader::getGold() const { 
    return gold; 
}

Material MaterialLoader::getPage() const {
    return page;
}
