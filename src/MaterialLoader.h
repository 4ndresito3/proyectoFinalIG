#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "Shaders.h"

class MaterialLoader {
private:
    Material mluz;
    Material ruby;
    Material gold;

public:
    MaterialLoader();
    ~MaterialLoader();

    void loadMaterials();

    Material getMluz() const;
    Material getRuby() const;
    Material getGold() const;
};

#endif /* MATERIALLOADER_H */
