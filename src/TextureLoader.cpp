#include "TextureLoader.h"
#include "Texture.h"
#include "Shaders.h"

// Constructor
TextureLoader::TextureLoader() {
    // El constructor solo inicializa el objeto, la carga se hace en loadTextures()
}

// Destructor
TextureLoader::~TextureLoader() {
    // Los objetos Texture se encargan de liberar sus propios recursos
}

// Carga todas las texturas
void TextureLoader::loadTextures() {
    // Cargar todas las imágenes individuales (Texture objects)
    imgNoEmissive.initTexture("resources/textures/imgNoEmissive.png");
    imgRuby.initTexture("resources/textures/imgRuby.png");
    imgGold.initTexture("resources/textures/imgGold.png");
    imgEarth.initTexture("resources/textures/imgEarth.png");
    imgChess.initTexture("resources/textures/imgChess.png");
    imgCubeDiffuse.initTexture("resources/textures/imgCubeDiffuse.png");
    imgCubeSpecular.initTexture("resources/textures/imgCubeSpecular.png");
    imgWindow.initTexture("resources/textures/imgWindow.png");
    imgWallDiffuse.initTexture("resources/textures/imgWallDiffuse.png");
    imgWallSpecular.initTexture("resources/textures/imgWallSpecular.png");
    imgWallNormal.initTexture("resources/textures/imgWallNormal.png");
    imgStaffDiffuse.initTexture("resources/textures/imgStaffDiffuse.png");
    imgStaffSpecular.initTexture("resources/textures/imgStaffSpecular.png");
    imgStaffNormal.initTexture("resources/textures/imgStaffNormal.png");
    imgStaffEmissive.initTexture("resources/textures/imgStaffEmissive.png");
    imgCrystalDiffuse.initTexture("resources/textures/imgCrystalDiffuse.png");
    imgCrystalSpecular.initTexture("resources/textures/imgCrystalSpecular.png");
    imgCrystalNormal.initTexture("resources/textures/imgCrystalNormal.png");
    imgCrystalEmissive.initTexture("resources/textures/imgCrystalEmissive.png");
    imgBrownLeatherDiffuse.initTexture("resources/textures/BrownLeatherDiffuse.png");
    imgBrownLeatherSpecular.initTexture("resources/textures/BrownLeatherSpecular.png");
    imgBrownLeatherNormal.initTexture("resources/textures/BrownLeatherNormal.png");
    imgStoneWallDiffuse.initTexture("resources/textures/StoneWallDiffuse.png");
    imgStoneWallSpecular.initTexture("resources/textures/StoneWallSpecular.png");
    imgStoneWallNormal.initTexture("resources/textures/StoneWallNormal.png");
    imgWoodDiffuse.initTexture("resources/textures/WoodDiffuse.png");
    imgWoodSpecular.initTexture("resources/textures/WoodSpecular.png");
    imgWoodNormal.initTexture("resources/textures/WoodNormal.png");
    imgGreyRockDiffuse.initTexture("resources/textures/GreyRockDiffuse.png");
    imgGreyRockSpecular.initTexture("resources/textures/GreyRockSpecular.png");
    imgGreyRockNormal.initTexture("resources/textures/GreyRockNormal.png");
    
    // Ruby
    texRuby.diffuse   = imgRuby.getTexture();
    texRuby.specular  = imgRuby.getTexture();
    texRuby.emissive  = imgNoEmissive.getTexture();
    texRuby.normal    = 0;
    texRuby.shininess = 76.8;

    // Gold
    texGold.diffuse   = imgGold.getTexture();
    texGold.specular  = imgGold.getTexture();
    texGold.emissive  = imgNoEmissive.getTexture();
    texGold.normal    = 0;
    texGold.shininess = 51.2;

    // Earth
    texEarth.diffuse   = imgEarth.getTexture();
    texEarth.specular  = imgEarth.getTexture();
    texEarth.emissive  = imgNoEmissive.getTexture();
    texEarth.normal    = 0;
    texEarth.shininess = 10.0;

    // Chess
    texChess.diffuse   = imgChess.getTexture();
    texChess.specular  = imgChess.getTexture();
    texChess.emissive  = imgNoEmissive.getTexture();
    texChess.normal    = 0;
    texChess.shininess = 10.0;

    // Cube
    texCube.diffuse    = imgCubeDiffuse.getTexture();
    texCube.specular   = imgCubeSpecular.getTexture();
    texCube.emissive   = imgNoEmissive.getTexture();
    texCube.normal     = 0;
    texCube.shininess  = 10.0;

    // Window
    texWindow.diffuse   = imgWindow.getTexture();
    texWindow.specular  = imgWindow.getTexture();
    texWindow.emissive  = imgWindow.getTexture();
    texWindow.normal    = 0;
    texWindow.shininess = 10.0;

    // Wall
    texWall.diffuse   = imgWallDiffuse.getTexture();
    texWall.specular  = imgWallSpecular.getTexture();
    texWall.emissive  = imgNoEmissive.getTexture();
    texWall.normal    = imgWallNormal.getTexture();
    texWall.shininess = 51.2;

    // Staff
    texStaff.diffuse   = imgStaffDiffuse.getTexture();
    texStaff.specular  = imgStaffSpecular.getTexture();
    texStaff.emissive  = imgStaffEmissive.getTexture();
    texStaff.normal    = imgStaffNormal.getTexture();
    texStaff.shininess = 32.0;

    // Crystal
    texCrystal.diffuse   = imgCrystalDiffuse.getTexture();
    texCrystal.specular  = imgCrystalSpecular.getTexture();
    texCrystal.emissive  = imgCrystalEmissive.getTexture();
    texCrystal.normal    = imgCrystalNormal.getTexture();
    texCrystal.shininess = 76.8;

    // Cover (Brown Leather)
    texCover.diffuse   = imgBrownLeatherDiffuse.getTexture();
    texCover.specular  = imgBrownLeatherSpecular.getTexture();
    texCover.emissive  = imgNoEmissive.getTexture(); 
    texCover.normal    = imgBrownLeatherNormal.getTexture();
    texCover.shininess = 26.0;

    // Stone Wall
    texStoneWall.diffuse   = imgStoneWallDiffuse.getTexture();
    texStoneWall.specular  = imgStoneWallSpecular.getTexture();
    texStoneWall.emissive  = imgNoEmissive.getTexture();
    texStoneWall.normal    = imgStoneWallNormal.getTexture();
    texStoneWall.shininess = 90.0;

    // Wood
    texWood.diffuse   = imgWoodDiffuse.getTexture();
    texWood.specular  = imgWoodSpecular.getTexture();
    texWood.emissive  = imgNoEmissive.getTexture();
    texWood.normal    = imgWoodNormal.getTexture();
    texWood.shininess = 25.0;

    // Grey Rock
    texGreyRock.diffuse   = imgGreyRockDiffuse.getTexture();
    texGreyRock.specular  = imgGreyRockSpecular.getTexture();
    texGreyRock.emissive  = imgNoEmissive.getTexture();
    texGreyRock.normal    = imgGreyRockNormal.getTexture();
    texGreyRock.shininess = 5.0;
}

// Getters para cada tipo de textura
Textures TextureLoader::getRuby() const {
    return texRuby;
}

Textures TextureLoader::getGold() const {
    return texGold;
}

Textures TextureLoader::getEarth() const {
    return texEarth;
}

Textures TextureLoader::getChess() const {
    return texChess;
}

Textures TextureLoader::getCube() const {
    return texCube;
}

Textures TextureLoader::getWindow() const {
    return texWindow;
}

Textures TextureLoader::getWall() const {
    return texWall;
}

Textures TextureLoader::getStaff() const {
    return texStaff;
}

Textures TextureLoader::getCrystal() const {
    return texCrystal;
}

Textures TextureLoader::getCover() const {
    return texCover;
}

Textures TextureLoader::getStoneWall() const {
    return texStoneWall;
}

Textures TextureLoader::getWood() const {
    return texWood;
}

Textures TextureLoader::getGreyRock() const {
    return texGreyRock;
}