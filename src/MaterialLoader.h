#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "Shaders.h"

class MaterialLoader {
private:
    Material mluz;
    Material ruby;
    Material rubyAlpha;
    Material gold;
    Material goldAlpha;
    Material page;
    Material wall;

public:
    MaterialLoader();
    ~MaterialLoader();

    void loadMaterials();

    Material getMluz() const;
    Material getRuby() const;
    Material getRubyAlpha() const;
    Material getGold() const;
    Material getGoldAlpha() const;
    Material getPage() const;
    Material getWall() const;
};

#endif /* MATERIALLOADER_H */
