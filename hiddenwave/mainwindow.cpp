#include "headers/mainwindow.h"
#include "headers/main.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *audioFileLayout = new QHBoxLayout();
    QLabel *audioFileLabel = new QLabel("Audio File:");
    audioFilePath = new QLineEdit();
    QPushButton *browseAudioButton = new QPushButton("Browse");
    audioFileLayout->addWidget(audioFileLabel);
    audioFileLayout->addWidget(audioFilePath);
    audioFileLayout->addWidget(browseAudioButton);
    mainLayout->addLayout(audioFileLayout);

    QHBoxLayout *dataFileLayout = new QHBoxLayout();
    QLabel *dataFileLabel = new QLabel("Data File:");
    dataFilePath = new QLineEdit();
    QPushButton *browseDataButton = new QPushButton("Browse");
    dataFileLayout->addWidget(dataFileLabel);
    dataFileLayout->addWidget(dataFilePath);
    dataFileLayout->addWidget(browseDataButton);
    mainLayout->addLayout(dataFileLayout);

    QPushButton *encryptButton = new QPushButton("Encrypt");
    QPushButton *decryptButton = new QPushButton("Decrypt");
    mainLayout->addWidget(encryptButton);
    mainLayout->addWidget(decryptButton);

    connect(browseAudioButton, &QPushButton::clicked, this, &MainWindow::browseAudioFile);
    connect(browseDataButton, &QPushButton::clicked, this, &MainWindow::browseDataFile);
    connect(encryptButton, &QPushButton::clicked, this, &MainWindow::encrypt);
    connect(decryptButton, &QPushButton::clicked, this, &MainWindow::decrypt);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::browseAudioFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Audio File"), "", tr("Audio Files (*.wav)"));
    if (!fileName.isEmpty()) {
        audioFilePath->setText(fileName);
    }
}

void MainWindow::browseDataFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), "", tr("All Files (*)"));
    if (!fileName.isEmpty()) {
        dataFilePath->setText(fileName);
    }
}

char** vectorToCharArray(const std::vector<std::string>& vec) {
    // Выделяем память для массива указателей
    char** charArray = new char*[vec.size()];

    // Копируем строки из вектора в массив char*
    for (size_t i = 0; i < vec.size(); ++i) {
        charArray[i] = new char[vec[i].size() + 1]; // +1 для '\0'
        std::strcpy(charArray[i], vec[i].c_str());
    }

    return charArray;
}

// Функция для освобождения памяти, выделенной для char**
void freeCharArray(char** charArray, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        delete[] charArray[i];
    }
    delete[] charArray;
}

void MainWindow::encrypt() {
    QString audioFile = audioFilePath->text();
    QString dataFile = dataFilePath->text();

    std::vector<std::string> vec = {"hiddenwave", "-i", audioFile.toStdString().c_str(), "-f", dataFile.toStdString().c_str(), "-o", "output.wav"};

    int argc = vec.size();
    char** argv = vectorToCharArray(vec);
    int mode = ArgsHandler(argc, argv);
    FileHandler(mode, argv, this);

    freeCharArray(argv, argc);
}

void MainWindow::decrypt() {
    QString audioFile = audioFilePath->text();

    std::vector<std::string> vec = {"hiddenwave", "-i", audioFile.toStdString().c_str()};

    int argc = vec.size();
    char** argv = vectorToCharArray(vec);
    int mode = ArgsHandler(argc, argv);
    FileHandler(mode, argv, this);

    freeCharArray(argv, argc);
}
