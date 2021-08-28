#include "Lighting.h"

Lighting::Lighting()
{
	light_ambient = { 0.2, 0.2, 0.2, 1.0 };
	light_specular = { 1.0, 1.0, 1.0, 1.0 };
	const_attenuation = 1.0;
	linear_attenuation = 0.0;
	quadratic_attenuation = 0.0;
}
