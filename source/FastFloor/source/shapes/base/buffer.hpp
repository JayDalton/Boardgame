#pragma once

#include "common.hpp"

namespace ogl 
{
   struct Buffer
   {
      using ItemType = float;
      using IndexType = unsigned;

      // Element: x, y, z, r, g, b, u, v
      //using Element = std::array<ElemItemType, 8>;

      // Element: vx, vy, vz, nx, ny, nz, cr, cg, cb, tu, tv
      using Element = std::array<ItemType, 11>;

      void useBuffer();
      void freeBuffer();
      void bindBuffer(
         const std::vector<Element>& vertices,
         const std::vector<IndexType>& indices
      );

      std::int32_t getVerticesByteSize() const
      {
         return sizeof(ItemType) * m_vertexSize;
      }

      std::int32_t getIndicesByteSize() const
      {
         return sizeof(IndexType) * m_indexSize;
      }

      static Element create(Vertex vertex, Vertex normal, Color color, Coords coords)
      {
         return {
            vertex.x, vertex.y, vertex.z,
            normal.x, normal.y, normal.z,
            color.r, color.g, color.b,
            coords.x, coords.y
         };
      };

      static Element create(Vertex vertex, Color color, Coords coords)
      {
         Vertex normal{ 0.0f, 0.0f, 1.0f };

         return {
            vertex.x, vertex.y, vertex.z,
            normal.x, normal.y, normal.z,
            color.r, color.g, color.b,
            coords.x, coords.y
         };
      };

      static Element create(Vertex vertex, Color color)
      {
         Vertex normal{ 0.0f, 0.0f, 1.0f };
         auto coords{ (glm::vec2{vertex} - glm::vec2{-1.0f, -1.0f}) * 0.5f };

         return {
            vertex.x, vertex.y, vertex.z,
            normal.x, normal.y, normal.z,
            color.r, color.g, color.b,
            coords.x, coords.y
         };
      };

   protected:
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };

   private:
      unsigned m_indexSize{0};
      unsigned m_vertexSize{0};
   };
}


