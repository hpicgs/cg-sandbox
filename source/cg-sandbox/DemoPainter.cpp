#include "DemoPainter.h"

DemoPainter::DemoPainter()
{
}

DemoPainter::~DemoPainter()
{
}

void DemoPainter::initialize()
{
}

void DemoPainter::deinitialize()
{
}

const OpenGLContextDescription & DemoPainter::context() const
{
    static OpenGLContextDescription description = {
        3, 2, true, true, false
    };

    return description;
}

const QStringList & DemoPainter::extensions() const
{
    static QStringList extensionList;

    return extensionList;
}

void DemoPainter::paint(CyclicTime::value_type /*time*/)
{

}

void DemoPainter::resize(const QSize & /*size*/)
{

}
