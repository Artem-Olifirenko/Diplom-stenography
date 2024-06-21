#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
    void browseAudioFile();
    void browseDataFile();
    void encrypt();
    void decrypt();

private:
    QLineEdit *audioFilePath;
    QLineEdit *dataFilePath;
};

#endif // MAINWINDOW_H
