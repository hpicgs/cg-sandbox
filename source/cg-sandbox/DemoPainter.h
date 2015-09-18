#pragma once

#include "painter/AbstractPainter.h"

class DemoPainter : public AbstractPainter
{
public:
    DemoPainter();
    virtual ~DemoPainter();

    virtual void initialize() override;
    virtual void deinitialize() override;

    virtual const OpenGLContextDescription & context() const override;
    virtual const QStringList & extensions() const override;

    virtual void paint(CyclicTime::value_type time) override;
    virtual void resize(const QSize & size) override;
};
