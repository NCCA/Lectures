#include "Texture.h"
#include <iostream>

//now we can use the static member variable
std::unordered_map<std::string,Texture*> Texture::m_textures;


Texture* Texture::getTexture(const std::string& _type)
{
  // try to find an existing instance; if not found std::map will return types.end()

  auto it = m_textures.find(_type);
  Texture *t;
  if (it == m_textures.end())
  { // if no instance with the proper type was found, make one
    t = new Texture(_type); // lazy initialization part
  m_textures[_type] = t;
  }
  else
  { //if already had an instance
    t = it->second; //The return value will be the found texture
  }
  return t;
}

void Texture::printCurrentTexture()
{
  if (!m_textures.empty())
  {
    std::cout << "Number of instances made = " << m_textures.size() << std::endl;
//    for (std::map<std::string,Texture*>::iterator iter = m_textures.begin(); iter != m_textures.end(); ++iter)
//    {
//        std::cout << (*iter).first << std::endl;
//    }
    for (auto t : m_textures )
      std::cout << t.first << std::endl;
    std::cout << std::endl;
  }
}
