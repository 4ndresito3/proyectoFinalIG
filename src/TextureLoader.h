#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include "Texture.h"

class TextureLoader {
private:
    // Imágenes individuales (Texture objects)
    Texture imgNoEmissive;
    Texture imgRuby;
    Texture imgGold;
    Texture imgEarth;
    Texture imgChess;
    Texture imgCubeDiffuse;
    Texture imgCubeSpecular;
    Texture imgWindow;
    Texture imgWallDiffuse;
    Texture imgWallSpecular;
    Texture imgWallNormal;
    Texture imgStaffDiffuse;
    Texture imgStaffSpecular;
    Texture imgStaffNormal;
    Texture imgStaffEmissive;
    Texture imgCrystalDiffuse;
    Texture imgCrystalSpecular;
    Texture imgCrystalNormal;
    Texture imgCrystalEmissive;
    Texture imgBrownLeatherDiffuse;
    Texture imgBrownLeatherSpecular;
    Texture imgBrownLeatherNormal;
    Texture imgStoneWallDiffuse;
    Texture imgStoneWallSpecular;
    Texture imgStoneWallNormal;
    Texture imgWoodDiffuse;
    Texture imgWoodSpecular;
    Texture imgWoodNormal;
    Texture imgGreyRockDiffuse;
    Texture imgGreyRockSpecular;
    Texture imgGreyRockNormal;
    Texture imgBlueCottonDiffuse;
    Texture imgBlueCottonSpecular;
    Texture imgBlueCottonNormal;

    // Structs Textures combinados
    Textures texRuby;
    Textures texGold;
    Textures texEarth;
    Textures texChess;
    Textures texCube;
    Textures texWindow;
    Textures texWall;
    Textures texStaff;
    Textures texCrystal;
    Textures texCover;
    Textures texStoneWall;
    Textures texWood;
    Textures texGreyRock;
    Textures texBlueCotton;

public:
    // Constructor y Destructor
    TextureLoader();
    ~TextureLoader();

    // Carga todas las texturas
    void loadTextures();

    // Getters para obtener cada tipo de textura
    Textures getRuby() const;
    Textures getGold() const;
    Textures getEarth() const;
    Textures getChess() const;
    Textures getCube() const;
    Textures getWindow() const;
    Textures getWall() const;
    Textures getStaff() const;
    Textures getCrystal() const;
    Textures getCover() const;
    Textures getStoneWall() const;
    Textures getWood() const;
    Textures getGreyRock() const;
    Textures getBlueCotton() const;
};

#endif /* TEXTURELOADER_H */
