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

    rubyAlpha.ambient   = glm::vec4(0.174500, 0.011750, 0.011750, 0.4);
    rubyAlpha.diffuse   = glm::vec4(0.614240, 0.041360, 0.041360, 0.4);
    rubyAlpha.specular  = glm::vec4(0.727811, 0.626959, 0.626959, 0.4);
    rubyAlpha.emissive  = glm::vec4(0.000000, 0.000000, 0.000000, 0.4);
    rubyAlpha.shininess = 76.8;

    gold.ambient   = glm::vec4(0.247250, 0.199500, 0.074500, 1.0);
    gold.diffuse   = glm::vec4(0.751640, 0.606480, 0.226480, 1.0);
    gold.specular  = glm::vec4(0.628281, 0.555802, 0.366065, 1.0);
    gold.emissive  = glm::vec4(0.000000, 0.000000, 0.000000, 1.0);
    gold.shininess = 51.2;

    goldAlpha.ambient   = glm::vec4(0.247250, 0.199500, 0.074500, 0.4);
    goldAlpha.diffuse   = glm::vec4(0.751640, 0.606480, 0.226480, 0.4);
    goldAlpha.specular  = glm::vec4(0.628281, 0.555802, 0.366065, 0.4);
    goldAlpha.emissive  = glm::vec4(0.000000, 0.000000, 0.000000, 0.4);
    goldAlpha.shininess = 51.2;

    page.ambient   = glm::vec4(0.25, 0.20, 0.15, 1.0);
    page.diffuse   = glm::vec4(0.90, 0.85, 0.80, 1.0);
    page.specular  = glm::vec4(0.20, 0.20, 0.20, 1.0);
    page.emissive  = glm::vec4(0.00, 0.00, 0.00, 1.0);
    page.shininess = 10.0;

    wall.ambient   = glm::vec4(0.0, 0.1, 0.06, 0.5);
    wall.diffuse   = glm::vec4(0.0, 0.50980392, 0.50980392, 0.5);
    wall.specular  = glm::vec4(0.50196078, 0.50196078, 0.50196078, 0.5);
    wall.emissive  = glm::vec4(0.0, 0.0, 0.0, 0.5); 
    wall.shininess = 32.0;

}

Material MaterialLoader::getMluz() const { 
    return mluz; 
}
Material MaterialLoader::getRuby() const { 
    return ruby; 
}

Material MaterialLoader::getRubyAlpha() const {
    return rubyAlpha;
}

Material MaterialLoader::getGold() const { 
    return gold; 
}

Material MaterialLoader::getGoldAlpha() const {
    return goldAlpha;
}

Material MaterialLoader::getPage() const {
    return page;
}
Material MaterialLoader::getWall() const {
    return wall;
}
