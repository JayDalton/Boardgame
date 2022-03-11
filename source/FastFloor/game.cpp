#include "game.h"
#include <random>

#include "source/shapes/rectangle.hpp"


FastFloor::FastFloor(std::string_view title)
   : GameEngine(title)
{
}

bool FastFloor::createUser()
{
   std::random_device rd;
   std::mt19937 eng(rd());
   std::uniform_real_distribution<> distArea(-3, +3);
   std::uniform_real_distribution<> distSize(0.5, 4);
   std::uniform_real_distribution<> distColor(0, 1);

   auto bufferId1 = createSquare(ogl::Colors::White);
   auto bufferId2 = createSquare(ogl::Colors::Green);
   auto bufferId3 = createRect({1.5, 0.7}, ogl::Colors::Red);
   auto bufferId4 = createRect({0.5, 1.7}, ogl::Colors::Blue);
   auto bufferId5 = createHexagon(ogl::Colors::Red);

   auto shaderId1 = createShader("shader/Complex.vs", "shader/Complex.fs");
   auto shaderId2 = createShader("shader/Complex.vs", "shader/Colored.fs");
   auto textureId1 = createTexture("images/container.jpg");
   auto textureId2 = createTexture("images/awesomeface.png");

   for (auto idx{0}; idx < 3; idx++)
   {
      ogl::SizeF size{distSize(eng), distSize(eng)};
      ogl::Vertex pos{distArea(eng), distArea(eng), 0.f};
      ogl::Color color{distColor(eng), distColor(eng), distColor(eng), 1.0f};

      ogl::Drawable plate;
      plate.m_position = pos;
      plate.m_shader = shaderId2;
      plate.m_texture1 = textureId2;
      //plate2.m_texture2 = textureId1;
      //plate.m_buffer = createSquare(color);
      //plate.m_buffer = createRect(size, color);
      plate.m_buffer = bufferId1;
      m_plates.push_back(plate);
      m_objects.push_back(plate);

   }

   //GamePlate plate{};
   //m_cache.createHexagons(4, plate);
   //const auto member = m_cache.mapPayground(plate);
   //m_objects.insert(m_objects.end(), member.cbegin(), member.cend());

   return true;
}

bool FastFloor::updateUser()
{
   static int counter{ 0 };

   //setWindowTitle(std::format("{:5}", counter++));

   //for (auto&& object : m_plates)
   //{
   //   render(object);
   //}

   return true;
}

