#include "shape.hpp"

#include <GL/glew.h>

#include <functional>
#include <numeric>

ogl::Shape::~Shape()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

void ogl::Shape::bindBuffer(std::vector<unsigned>&& indices)
{
   m_indices = indices;
   m_indexSize = indices.size();
   m_vertexSize = m_vertices.size();

   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_VBO);
   glGenBuffers(1, &m_EBO);

   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   glBufferData(GL_ARRAY_BUFFER, getVerticesByteSize(), m_vertices.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesByteSize(), m_indices.data(), GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
   glEnableVertexAttribArray(0);

   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   // texture coord attribute
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
   glEnableVertexAttribArray(2);

   //auto Format = [](std::string str, auto value) {
   //   return std::move(str) + ',' + std::to_string(value);
   //};
   //std::cout << std::format("\n--OLD--------------------------");
   std::cout << std::format("\nVAO: {}, VBO: {}, EBO: {}, IndexSize: {}, VertexSize: {}", m_VAO, m_VBO, m_EBO, m_indexSize, m_vertexSize);
   //std::cout << std::format("\nIndexList: {}", std::accumulate(std::next(m_indices.begin()), m_indices.end(), std::to_string(m_indices[0]), Format));
   //std::cout << std::format("\nVertexList: {}", std::accumulate(std::next(m_vertices.begin()), m_vertices.end(), std::to_string(m_vertices[0]), Format));

   //m_indices.clear();
   m_vertices.clear();
}

//void ogl::Shape::bindBuffer(
//   const std::vector<Element>& vertices, 
//   const std::vector<IndexType>& indices)
//{
//   m_indexSize = indices.size();
//
//   //glGenVertexArrays(1, &m_VAO);
//   //glGenBuffers(1, &m_VBO);
//   //glGenBuffers(1, &m_EBO);
//
//   //glBindVertexArray(m_VAO);
//
//   //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//   //glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
//
//   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * indices.size(), indices.data(), GL_STATIC_DRAW);
//
//   //// position attribute
//   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
//   //glEnableVertexAttribArray(0);
//
//   //// color attribute
//   //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
//   //glEnableVertexAttribArray(1);
//
//   //// texture coord attribute
//   //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
//   //glEnableVertexAttribArray(2);
//}

//ogl::Buffer::~Buffer()
//{
//   //freeBuffer();
//}

void ogl::Buffer::freeBuffer()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
   m_VAO = m_VBO = m_EBO = 0;
}

void ogl::Buffer::bindBuffer(const std::vector<Element>& elementList, const std::vector<IndexType>& indexList)
{
   std::vector<VertexType> vertexBuffer;
   vertexBuffer.reserve(elementList.size() * sizeof(VertexType));
   for (auto&& element : elementList)
   {
      std::copy(element.cbegin(), element.cend(), std::back_inserter(vertexBuffer));
   }

   m_indexSize = indexList.size();
   m_vertexSize = vertexBuffer.size();

   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_VBO);
   glGenBuffers(1, &m_EBO);

   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   glBufferData(GL_ARRAY_BUFFER, getVerticesByteSize(), vertexBuffer.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesByteSize(), indexList.data(), GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)0);
   glEnableVertexAttribArray(0);

   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   // texture coord attribute
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(6 * sizeof(float)));
   glEnableVertexAttribArray(2);

   //auto Format = [](std::string str, auto value) {
   //   return std::move(str) + ',' + std::to_string(value);
   //};
   //std::cout << std::format("\n--NEW--------------------------");
   std::cout << std::format("\nBufferId: {}, VBO: {}, EBO: {}, IndexSize: {}, VertexSize: {}", m_VAO, m_VBO, m_EBO, m_indexSize, m_vertexSize);
   //std::cout << std::format("\nIndexList: {}", std::accumulate(std::next(indexList.begin()), indexList.end(), std::to_string(indexList[0]), Format));
   //std::cout << std::format("\nVertexList: {}", std::accumulate(std::next(vertexBuffer.begin()), vertexBuffer.end(), std::to_string(vertexBuffer[0]), Format));
}

void ogl::Buffer::render()
{
   glBindVertexArray(m_VAO);
   glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, 0);
   //glDrawElements(GL_LINE_STRIP, m_indexSize, GL_UNSIGNED_INT, 0);
}
