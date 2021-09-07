#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <format>
#include <numbers>

#include <filesystem>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <GL/glew.h>

namespace ogl
{
   //using Size = glm::u32vec2;
   using SizeF = glm::vec2;
   using Color = glm::vec4;
   using Vertex = glm::vec3;
   using Coords = glm::vec2;

   struct Size
   {
      int x{ 0 }, y{ 0 };
      auto operator<=>(const Size&) const = default;
   };

   struct Colors {
      static constexpr Color White{ 1.0f, 1.0f, 1.0f, 1.0f };
      static constexpr Color Black{ 0.0f, 0.0f, 0.0f, 1.0f };
      static constexpr Color Red{ 1.0f, 0.0f, 0.0f, 1.0f };
      static constexpr Color Green{ 0.0f, 1.0f, 0.0f, 1.0f };
      static constexpr Color Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
   };
}
