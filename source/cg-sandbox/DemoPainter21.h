#pragma once

#include "painter/AbstractPainter.h"

#include <QOpenGLFunctions_2_1>

#include "painter/OpenGL.h"

class DemoPainter21 : public AbstractPainter
{
public:
    DemoPainter21();
    virtual ~DemoPainter21();

    virtual void initialize(QOpenGLContext * context) override;
    virtual void deinitialize() override;

    virtual const OpenGLContextDescription & context() const override;
    virtual const QStringList & extensions() const override;

    virtual void paint(CyclicTime::value_type time) override;
    virtual void resize(const QSize & size) override;

protected:
    QOpenGLFunctions_2_1 * m_gl;
};
