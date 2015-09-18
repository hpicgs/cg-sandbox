#pragma once

#include <QOpenGLWidget>

class QSurfaceFormat;

class OpenGLContextDescription;
class AbstractPainter;

class Camera;
class Navigation;
class ChronoTimer;
class CyclicTime;

class Canvas : public QOpenGLWidget
{
    Q_OBJECT

public:
    Canvas(const QSurfaceFormat & format, AbstractPainter * painter);
    Canvas(const OpenGLContextDescription & description, AbstractPainter * painter);
    virtual ~Canvas();

    static QSurfaceFormat createFormat(const OpenGLContextDescription & description);

    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

    void setActive(bool on);

signals:
    void fpsUpdate(float fps);
    void mouseUpdate(const QPoint & mouse);
    void timeUpdate(float timef);

protected:
    AbstractPainter * m_painter;

    bool m_active;
    bool m_continuousRepaint;
    QScopedPointer<ChronoTimer> m_fpsTimer;
    QScopedPointer<CyclicTime> m_virtualTime;

protected:
    virtual void keyPressEvent        (QKeyEvent   * event) override;
    virtual void keyReleaseEvent      (QKeyEvent   * event) override;
    virtual void mouseMoveEvent       (QMouseEvent * event) override;
    virtual void mousePressEvent      (QMouseEvent * event) override;
    virtual void mouseReleaseEvent    (QMouseEvent * event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent * event) override;
    virtual void wheelEvent           (QWheelEvent * event) override;
};
