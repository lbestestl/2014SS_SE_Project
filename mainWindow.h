#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();
    
private:
    Ui::mainWindow *ui;

private slots:
    void newDSM();
    void openDSM();
    void saveDSM();
    void saveAsDSM();
    void newClustering();
    void openClustering();
    void saveClustering();
    void saveAsClustering();
    void exitProgram();
    void redraw();
    void showRowLabels();
    void about();
    void expandAll();
    void collapseAll();
    void group();
    void ungroup();
    void moveUp();
    void moveDown();
    void addEntity();
    void deleteEntity();
};

#endif // MAINWINDOW_H
