#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
public slots:
    void fileOpen(QString path);
private slots:
    void on_actionViewZoomIn_triggered();
    void on_actionViewZoomOut_triggered();
    void on_actionViewFitView_triggered();
    void on_actionView100_triggered();
    void on_actionViewPrintSize_triggered();
    void on_actionFileNew_triggered();
    void on_actionFileOpen_triggered();
private:
    Ui::MainWindow *ui;
    bool loadFile(const QString &fileName);
    QActionGroup *Tools;
};

#endif // MAINWINDOW_H
