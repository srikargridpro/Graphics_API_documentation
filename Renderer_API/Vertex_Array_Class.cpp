#ifndef _VERTEX_ARRAY_CLASS_CPP_
#define _VERTEX_ARRAY_CLASS_CPP_

#include <cassert>
#include "Vertex_Array_Class.hpp"

namespace Renderer_API {

std::vector<float>* VertexArray::BuildVertexArray(std::vector<float>* position = nullptr,
                                                  std::vector<float>* color = nullptr,
                                                  std::vector<float>* normal = nullptr) 
{
    assert(this->layout != NONE
           && "Set Layout of VertexArray.layout = Renderer_API::VertexArray::<args = {V, VC, VN, VCN}>");
    assert(position != nullptr && "No Positon array is given");

    if(this->layout == 2 || this->layout == 4) {
       assert(color != nullptr
              && "Color Array data not given but Layout is set to load Color Data [VC] or [VCN]");
       assert(color->size() == position->size()
             && "Sizeof ColorArrayData != Sizeof PositionArrayData"); 
     }

    if(this->layout == 3 || this->layout == 4) {
       assert(normal != nullptr
              && "Normal Array data not given but Layout is set to load Normal Data [VN] or [VCN]");
       assert(normal->size() == position->size()
              && "Sizeof NormalArrayData != Sizeof PositionArrayData"); 
    }

    for(std::size_t vertex_id = 0; vertex_id < (position->size())/3; ++vertex_id )
       {
         this->vertex_array.push_back((*position)[vertex_id+0]);
         this->vertex_array.push_back((*position)[vertex_id+1]);
         this->vertex_array.push_back((*position)[vertex_id+2]);

         if(color != nullptr)
           {
             this->vertex_array.push_back((*color)[vertex_id+0]);
             this->vertex_array.push_back((*color)[vertex_id+1]);
             this->vertex_array.push_back((*color)[vertex_id+2]);
           }

         if(normal != nullptr)
           {
             this->vertex_array.push_back((*normal)[vertex_id+0]);
             this->vertex_array.push_back((*normal)[vertex_id+1]);
             this->vertex_array.push_back((*normal)[vertex_id+2]);
           }

       } 
       
     return &this->vertex_array;     
}


bool VertexArray::Vertex::update()
{
   x  = this->position[0] ; y = this->position[1] ; z = this->position[2];
   r  = this->color[0]    ; g = this->color[1]    ; b = this->color[2] ;
   n1 = this->normal[0]   ; n2 = this->normal[1]  ; n3 = this->normal[2];
  
   return true;
}


bool VertexArray::Vertex::setPosition(float x, float y, float z) 
{
 if(layout > 0) {
 this->x = x;  this->y = y;  this->z = z;
 this->position[0] = x; this->position[1] = y; this->position[2] = z;
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;

 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = 0 ;
   (*(this->vertex_array_head))[index*stride_len + i + offset] = this->position[i];
 }
 return true;
 }
 return false;
}


bool VertexArray::Vertex::setColor(float r, float g, float b) 
{
 if(layout == 2 || layout == 4) {
 this->r = r;  this->g = g;  this->b = b;
 this->color[0] = r; this->color[1] = g; this->color[2] = b;
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = 3 ;
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->color[i];
 }
 return true;
 }
 return false;
}


bool VertexArray::Vertex::setNormal(float n1, float n2, float n3) 
{
 if(layout == 3 || layout == 4) {
 this->n1 = n1;  this->n2 = n2;  this->n3 = n3;
 this->normal[0] = n1; this->normal[1] = n2; this->normal[2] = n3;
 
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = (layout == 3) ? 3 : 6 ;
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->normal[i];
 }
 return true;
 }
 return false; 
}

}// namespace Renderer_API
#endif
