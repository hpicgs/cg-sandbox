#pragma once

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

class Navigation
{
public:
    Navigation();
    virtual ~Navigation();

    virtual void keyPressEvent        (QKeyEvent   * event);
    virtual void keyReleaseEvent      (QKeyEvent   * event);
    virtual void mouseMoveEvent       (QMouseEvent * event);
    virtual void mousePressEvent      (QMouseEvent * event);
    virtual void mouseReleaseEvent    (QMouseEvent * event);
    virtual void mouseDoubleClickEvent(QMouseEvent * event);
    virtual void wheelEvent           (QWheelEvent * event);
};
