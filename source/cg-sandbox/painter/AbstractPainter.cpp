
#include "AbstractPainter.h"

#include <cassert>

#include "Camera.h"


AbstractPainter::AbstractPainter()
: m_camera(nullptr)
{
}
 
AbstractPainter::~AbstractPainter()
{
}

Camera * AbstractPainter::camera()
{
    return m_camera.data();
}
