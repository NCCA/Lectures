#ifndef TEXTURE_H__
#define TEXTURE_H__
#include <string>
#include <unordered_map>

class Texture
{
public :
  static Texture* getTexture(const std::string &_type);
  // just to demo the process
  static void printCurrentTexture();
private :
    static std::unordered_map<std::string,Texture*> m_textures;
    // the type of this texture (i.e. the name)
    std::string m_name;

  // note: constructor private forcing one to use static getTexture()
    Texture(const std::string &_t) : m_name( _t ) {}
};

#endif
