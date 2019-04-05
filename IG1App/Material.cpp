#include "Material.h"



void Material::setCooper()
{
	ambient = glm::fvec4(0.19125, 00735, 0.0225,1);
	diffuse = glm::fvec4(0.714, 0.27048, 0.0828, 1);
	specular = glm::fvec4(0.256777, 0.137622, 0.086014, 1);
}
