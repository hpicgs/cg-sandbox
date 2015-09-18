
#pragma once

#include <QMainWindow>
#include <QScopedPointer>
#include <QLabel>
#include <QShortcut>
#include <QList>

class Ui_Viewer;

class AbstractPainter;
class Canvas;

class Viewer : public QMainWindow
{
    Q_OBJECT

    struct RegisteredPainter
    {
        QString name;
        AbstractPainter * painter;
        Canvas * canvas;
    };

public:
    Viewer(QWidget * parent = nullptr
    ,   Qt::WindowFlags flags = 0);

    virtual ~Viewer();

    void addPainter(const QString & name, AbstractPainter * painter);

public slots:
    void fpsChanged(float fps);
    void mouseChanged(const QPoint & mouse);
    void objChanged(const QVector3D & obj);
    void timeChanged(float timef);

protected slots:
    void on_toggleFullScreenAction_triggered(bool checked);
    void toggleFullScreen();
    void on_toggleSwapIntervalAction_triggered(bool checked);
    void toggleSwapInterval();
    void on_toggleTimeAction_triggered(bool checked);
    void toggleTime();
    void on_reloadShaders_triggered(bool checked);
    void reloadShaders();

    void on_restartTimeAction_triggered(bool checked);
    void on_quitAction_triggered(bool checked);

protected:
    void setup();

    void store();
    void restore();

    void updateAfterFullScreenToggle();

protected:
	const QScopedPointer<Ui_Viewer> m_ui;
    QList<RegisteredPainter> m_registeredPainters;

    QLabel * m_fpsLabel;
    QLabel * m_mouseLabel;
    QLabel * m_timeLabel;
    QLabel * m_objLabel;

    QScopedPointer<QShortcut> m_fullscreenShortcut;
    QScopedPointer<QShortcut> m_swapIntervalShortcut;
    QScopedPointer<QShortcut> m_toggleTimeShortcut;
    QScopedPointer<QShortcut> m_reloadShadersShortcut;
};
