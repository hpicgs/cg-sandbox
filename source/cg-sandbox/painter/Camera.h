
#pragma once

#include <QtGlobal>
#include <QObject>

#include <QSize>
#include <QVector3D>
#include <QMatrix4x4>

#include "util/CachedValue.h"


class Camera : public QObject
{
    Q_OBJECT

public:
    Camera(
        const QVector3D & eye    = QVector3D(0.0, 0.0, 1.0)
    ,   const QVector3D & center = QVector3D(0.0, 0.0, 0.0) 
    ,   const QVector3D & up     = QVector3D(0.0, 1.0, 0.0));

    virtual ~Camera();

    const QVector3D & eye() const;
    void setEye(const QVector3D & eye);
    const QVector3D & center() const;
    void setCenter(const QVector3D & center);
    const QVector3D & up() const;
    void setUp(const QVector3D & up);

    float zNear() const;
    void setZNear(float zNear);
    float zFar() const;
    void setZFar(float zFar);

    float fovy() const;
    void setFovy(float fovy);

    const QSize & viewport() const;
    void setViewport(const QSize & viewport);

    // lazy matrices getters

    const QMatrix4x4 & view() const;
    const QMatrix4x4 & projection() const;
    const QMatrix4x4 & viewProjection() const;
    const QMatrix4x4 & viewInverted() const;
    const QMatrix4x4 & projectionInverted() const;
    const QMatrix4x4 & viewProjectionInverted() const;

    void update();

signals:
    void changed();

protected:
    void dirty(bool update = true);
    void invalidateMatrices();

protected:
    bool m_dirty;

    QVector3D m_eye;
    QVector3D m_center;
    QVector3D m_up;

    float m_fovy;
    float m_aspect;
    float m_zNear;
    float m_zFar;
    QSize m_viewport;

    mutable CachedValue<QMatrix4x4> m_view;
    mutable CachedValue<QMatrix4x4> m_viewInverted;
    mutable CachedValue<QMatrix4x4> m_projection;
    mutable CachedValue<QMatrix4x4> m_projectionInverted;
    mutable CachedValue<QMatrix4x4> m_viewProjection;
    mutable CachedValue<QMatrix4x4> m_viewProjectionInverted;
};
