#ifndef CAPPLICATION_H
#define CAPPLICATION_H
#include <QObject>
#include <QApplication>
#include "mainwindow.h"
#include <QFileOpenEvent>
#include <QMainWindow>
#include <QDebug>

class CApplication : public QApplication
{
    Q_OBJECT
public:
    CApplication(int &argc, char *argv[]);
    ~CApplication();
    MainWindow *window;
    int exec();
    static QString resourcesPath();
    static bool isOSX107();
signals:
    void fileOpen(QString filename);
protected:
    bool event(QEvent *);
private:
    void _FileOpen(const QString &filename);
};

#endif // CAPPLICATION_H
