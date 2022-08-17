#include "application.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QSysInfo>
#include <QDebug>
#include <QSettings>

CApplication::CApplication(int &argc, char *argv[]) : QApplication(argc, argv) {
    window = new MainWindow;
    connect(this, SIGNAL(fileOpen(QString)), window, SLOT(fileOpen(QString)));
}

CApplication::~CApplication() {
    delete window;
}

bool CApplication::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::FileOpen:
        _FileOpen(static_cast<QFileOpenEvent *>(event)->file());
        return true;
    default:
        return QApplication::event(event);
    }
}

void CApplication::_FileOpen(const QString &filename) {
    emit fileOpen(filename);
}

int CApplication::exec() {
    window->show();
    return QApplication::exec();
}

QString CApplication::resourcesPath() {
    QFileInfo fi(QCoreApplication::applicationDirPath()+"/../Resources");
    fi.makeAbsolute();
    //qDebug() << fi.absoluteFilePath();
    return fi.absoluteFilePath();
}

bool CApplication::isOSX107() {
    /*if (QSysInfo::MacintoshVersion <= QSysInfo::MV_10_7)*/ return true;
    //return false;
}
