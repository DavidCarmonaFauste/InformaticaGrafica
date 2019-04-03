#include "Material.h"



Material::Material()
{
}


void Material::setCooper()
{
	ambient = glm::fvec4(0.19125, 00735, 0.0225,12.8);
	diffuse = glm::fvec4(0.714, 0.27048, 0.0828, 12.8);
	specular = glm::fvec4(0.256777, 0.137622, 0.086014, 12.8);
}
