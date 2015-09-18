#include "Camera.h"

#include <cassert>

Camera::Camera(
    const QVector3D & eye
,   const QVector3D & center
,   const QVector3D & up)
: m_dirty(false)

, m_eye(eye)
, m_center(center)
, m_up(up)

, m_fovy(40.f)
, m_aspect(1.f)
, m_zNear(0.1f)
, m_zFar(64.0f)
{
}

Camera::~Camera()
{
}

void Camera::invalidateMatrices()
{
    m_view.invalidate();
    m_viewInverted.invalidate();
    m_projection.invalidate();
    m_projectionInverted.invalidate();
    m_viewProjection.invalidate();
    m_viewProjectionInverted.invalidate();
}

void Camera::dirty(bool update)
{
    m_dirty = true;

    if (update)
    {
        this->update();
    }
}

const QVector3D & Camera::eye() const
{
    return m_eye;
}

void Camera::setEye(const QVector3D & eye)
{
    m_eye = eye;

    dirty();
}

const QVector3D & Camera::center() const
{
    return m_center;
}

void Camera::setCenter(const QVector3D & center)
{
    m_center = center;

    dirty();
}

const QVector3D & Camera::up() const
{
    return m_up;
}

void Camera::setUp(const QVector3D & up)
{
    m_up = up;

    dirty();
}

float Camera::zNear() const
{
    return m_zNear;
}

void Camera::setZNear(const float zNear)
{
    m_zNear = zNear;
    assert(m_zNear > 0.0 && m_zFar > m_zNear);

    dirty();
}

float Camera::zFar() const
{
    return m_zFar;
}

void Camera::setZFar(const float zFar)
{
    m_zFar = zFar;
    assert(m_zFar > m_zNear);

    dirty();
}

float Camera::fovy() const
{
    return m_fovy;
}

void Camera::setFovy(const float fovy)
{
    m_fovy = fovy;
    assert(m_fovy > 0.0);

    dirty();
}

const QSize & Camera::viewport() const
{
    return m_viewport;
}

void Camera::setViewport(const QSize & viewport)
{
    m_aspect = viewport.width() / qMax<float>(static_cast<float>(viewport.height()), 1.f);
    m_viewport = viewport;

    dirty();
}

void Camera::update()
{
    if (!m_dirty)
    {
        return;
    }

    invalidateMatrices();

    m_dirty = false;

    emit(changed());
}

const QMatrix4x4 & Camera::view() const
{
    if (m_dirty)
    {
        const_cast<Camera*>(this)->update();
    }
    
    if (!m_view.isValid())
    {
        m_view.value().setToIdentity();
	    m_view.value().lookAt(m_eye, m_center, m_up);
	    m_view.validate();
    }

    return m_view.value();
}

const QMatrix4x4 & Camera::projection() const
{
    if (m_dirty)
    {
        const_cast<Camera*>(this)->update();
    }

    if (!m_projection.isValid())
    {
	    m_projection.value().setToIdentity();
	    m_projection.value().perspective(m_fovy, m_aspect, m_zNear, m_zFar);
	    m_projection.validate();
    }

    return m_projection.value();
}

const QMatrix4x4 & Camera::viewProjection() const
{
    if (m_dirty)
    {
        const_cast<Camera*>(this)->update();
    }

    if (!m_viewProjection.isValid())
    {
    	m_viewProjection.setValue(projection() * view());
    }
    
    return m_viewProjection.value();
}

const QMatrix4x4 & Camera::viewInverted() const
{
    if (m_dirty)
    {
        const_cast<Camera*>(this)->update();
    }

    if (!m_viewInverted.isValid())
    {
        m_viewInverted.setValue(view().inverted());
    }

    return m_viewInverted.value();
}

const QMatrix4x4 & Camera::projectionInverted() const
{
    if (m_dirty)
    {
        const_cast<Camera*>(this)->update();
    }

    if (!m_projectionInverted.isValid())
    {
        m_projectionInverted.setValue(projection().inverted());
    }

    return m_projectionInverted.value();
}

const QMatrix4x4 & Camera::viewProjectionInverted() const
{
    if (m_dirty)
    {
        const_cast<Camera*>(this)->update();
    }

    if (!m_viewProjectionInverted.isValid())
    {
        m_viewProjectionInverted.setValue(viewProjection().inverted());
    }

    return m_viewProjectionInverted.value();
}
