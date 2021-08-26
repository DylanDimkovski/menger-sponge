#include "Material.h"


void Material::apply_material()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(mat_ambient));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(mat_diffuse));
    glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(mat_specular));
    glMaterialfv(GL_FRONT, GL_SHININESS, &shine);
}
