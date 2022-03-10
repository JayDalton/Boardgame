#pragma once

#include <memory>

#include "source/engine.h"

#include "model.h"

class FastFloor : public ogl::GameEngine
{
public:
   FastFloor(std::string_view title);

   bool createUser() override;
   
   bool updateUser() override;

private:
   PlateAccess m_cache;

   std::vector<ogl::Drawable> m_plates;
};

