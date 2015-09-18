
#include "AbstractPainter.h"

#include <cassert>

#include "Camera.h"
#include "interaction/Navigation.h"

AbstractPainter::AbstractPainter()
: m_camera(nullptr)
{
}
 
AbstractPainter::~AbstractPainter()
{
}

Camera * AbstractPainter::createCamera()
{
    return new Camera();
}

Navigation * AbstractPainter::createNavigation()
{
    return nullptr;
}

Camera * AbstractPainter::camera()
{
    return m_camera.data();
}

Navigation * AbstractPainter::navigation()
{
    return m_navigation.data();
}
