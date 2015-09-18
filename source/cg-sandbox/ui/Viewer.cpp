#include "Viewer.h"

#include <sstream>
#include <iomanip>
#include <cassert>


#include <QOpenGLContext>
#include <QShortcut>
#include <QSettings>
#include <QLabel>
#include <QVector3D>

#include "ui_Viewer.h"

#include "Application.h"
#include "Canvas.h"
#include "painter/AbstractPainter.h"

namespace 
{
    const QString SETTINGS_GEOMETRY ("Geometry");
    const QString SETTINGS_STATE    ("State");
}

Viewer::Viewer(QWidget * parent
,    Qt::WindowFlags flags)

: QMainWindow(parent, flags)
, m_ui(new Ui_Viewer)
, m_currentCanvas(nullptr)
, m_fullscreenShortcut(nullptr)
, m_swapIntervalShortcut(nullptr)
, m_toggleTimeShortcut(nullptr)
, m_reloadShadersShortcut(nullptr)
{
    m_ui->setupUi(this);
    setWindowTitle(Application::applicationName() + " " + Application::applicationVersion());

    setup();

    restore();

    updateAfterFullScreenToggle();
}

Viewer::~Viewer()
{
    store();

    setCentralWidget(nullptr); // TODO: needed?
}

void Viewer::addPainter(const QString & name, AbstractPainter * painter)
{
    Canvas * canvas = new Canvas(painter->context(), painter);

    m_registeredPainters << RegisteredPainter{
        name,
        painter,
        canvas
    };

    m_ui->canvasSelection->addTab(canvas, name);

    connect(canvas, SIGNAL(fpsUpdate(float)), this, SLOT(fpsChanged(float)));
    connect(canvas, SIGNAL(timeUpdate(float)), this, SLOT(timeChanged(float)));
}

void Viewer::restore()
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings s;

    restoreGeometry(s.value(SETTINGS_GEOMETRY).toByteArray());
    restoreState(s.value(SETTINGS_STATE).toByteArray());
}

void Viewer::store()
{
    QSettings s;
    s.setValue(SETTINGS_GEOMETRY, saveGeometry());
    s.setValue(SETTINGS_STATE, saveState());
}

void Viewer::setup()
{
    connect(m_ui->canvasSelection, SIGNAL(currentChanged(int)), this, SLOT(canvasChanged(int)));

    // ToDo: this seems to be a generic problem (should be done by qt main window itself but....)
    //       We need to parse all available shortcuts via any menubars and connect those...

    m_fullscreenShortcut.reset(new QShortcut(m_ui->toggleFullScreenAction->shortcut(), this));
    connect(m_fullscreenShortcut.data(), &QShortcut::activated, this, &Viewer::toggleFullScreen);

    m_swapIntervalShortcut.reset(new QShortcut(m_ui->toggleSwapIntervalAction->shortcut(), this));
    connect(m_swapIntervalShortcut.data(), &QShortcut::activated, this, &Viewer::toggleSwapInterval);

    m_toggleTimeShortcut.reset(new QShortcut(m_ui->toggleTimeAction->shortcut(), this));
    connect(m_toggleTimeShortcut.data(), &QShortcut::activated, this, &Viewer::toggleTime);

    //m_reloadShadersShortcut.reset(new QShortcut(m_ui->reloadShaders->shortcut(), this));
    //connect(m_reloadShadersShortcut.data(), &QShortcut::activated, this, &Viewer::reloadShaders);


    m_objLabel = new QLabel(m_ui->statusbar);
    m_ui->statusbar->addPermanentWidget(m_objLabel);
    m_mouseLabel = new QLabel(m_ui->statusbar);
    m_ui->statusbar->addPermanentWidget(m_mouseLabel);
    m_timeLabel = new QLabel(m_ui->statusbar);
    m_ui->statusbar->addPermanentWidget(m_timeLabel);
    m_fpsLabel = new QLabel(m_ui->statusbar);
    m_ui->statusbar->addPermanentWidget(m_fpsLabel);

    show();
}

void Viewer::fpsChanged(float fps)
{
    m_fpsLabel->setText(QString(" %1 fps ")
        .arg(fps, 4, 'f', 0, QChar('0')));
}

void Viewer::mouseChanged(const QPoint & mouse)
{
    m_mouseLabel->setText(QString(" %1 %2 mouse ")
        .arg(mouse.x(), 4, 10, QChar('0')).arg(mouse.y(), 4, 10, QChar('0')));
}

void Viewer::timeChanged(float time)
{
    m_timeLabel->setText(QString("time %1").arg(time, 1, 'f', 3, '0'));
}

void Viewer::objChanged(const QVector3D & obj)
{
    m_objLabel->setText(QString(" %1%2 %3%4 %5%6 xyz ")
        .arg(obj.x() > 0 ? " " : "").arg(obj.x())
        .arg(obj.y() > 0 ? " " : "").arg(obj.y())
        .arg(obj.z() > 0 ? " " : "").arg(obj.z()));
}

void Viewer::on_toggleFullScreenAction_triggered(bool /*checked*/)
{
    toggleFullScreen();
}

void Viewer::toggleFullScreen()
{
    if (isFullScreen())
    {
        showNormal();
    }
    else
    {
        showFullScreen();
    }

    updateAfterFullScreenToggle();
}

void Viewer::updateAfterFullScreenToggle()
{
    // TODO: required?
    m_ui->menubar->setVisible(isFullScreen());
    m_ui->statusbar->setVisible(isFullScreen());

    m_ui->menubar->setVisible(!isFullScreen());
    m_ui->statusbar->setVisible(!isFullScreen());
    m_fullscreenShortcut->setEnabled(isFullScreen());
    m_swapIntervalShortcut->setEnabled(isFullScreen());
    m_toggleTimeShortcut->setEnabled(isFullScreen());
}

void Viewer::on_toggleSwapIntervalAction_triggered(bool /*checked*/)
{
    toggleSwapInterval();
}

void Viewer::toggleSwapInterval()
{
}

void Viewer::on_toggleTimeAction_triggered(bool /*checked*/)
{
    toggleTime();
}

void Viewer::toggleTime()
{
    //if (!m_time->isRunning())
    //    m_time->start();
    //else
    //    m_time->pause();
}

void Viewer::on_restartTimeAction_triggered(bool /*checked*/)
{
    //const bool wasRunning(m_time->isRunning());
    //m_time->reset();

    //if (wasRunning)
    //    m_time->start();
}

void Viewer::on_quitAction_triggered(bool /*checked*/)
{
    QApplication::quit();
}

void Viewer::on_reloadShaders_triggered(bool /*checked*/)
{
    reloadShaders();
}

void Viewer::reloadShaders()
{
    //FileAssociatedShader::allChanged();
}

void Viewer::canvasChanged(int index)
{
    if (m_currentCanvas)
    {
        m_currentCanvas->setActive(false);
    }

    m_currentCanvas = m_registeredPainters.value(index).canvas;

    if (m_currentCanvas)
    {
        m_currentCanvas->setActive(true);
    }
}
