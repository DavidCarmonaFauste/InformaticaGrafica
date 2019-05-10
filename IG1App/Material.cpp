#include "Material.h"



void Material::setCooper()
{
	ambient = glm::fvec4(0.19125, 0.0735, 0.0225,1);
	diffuse = glm::fvec4(0.7038, 0.27048, 0.0828, 1);
	specular = glm::fvec4(0.256777, 0.137622, 0.086014, 1);

	expF = 12.8;
}

void Material::setSilver()
{
	ambient = glm::fvec4(0.19225, 0.19225, 0.19225, 1);
	diffuse = glm::fvec4(0.50754, 0.50754, 0.50754, 1);
	specular = glm::fvec4(0.508273, 0.508273, 0.508273, 1);

	expF = 51.2;
}
