
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

void AbstractPainter::setCamera(Camera * camera)
{
    m_camera = camera;
}

Camera * AbstractPainter::camera()
{
    return m_camera;
}
