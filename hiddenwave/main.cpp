#include <iostream>
#include "headers/main.h"
#include "headers/Algorithm.h"
#include <QApplication>
#include "headers/mainwindow.h"
#include <QMessageBox>

using namespace std;

void help(string packageName){
	cout << "Usage: " << packageName << " [-h] [-i AUDIOFILE] [-m SECRETMSG] [-o OUTFILE]\n\nArguments:\n"
    "   -h                Show this help message and exit\n"
    "   -i    INPUTFILE     Select Audio File\n"
    "   -m    SECRETMSG     Enter Your Message\n"
	"   -f    SECRETFILE    Select the Secret File\n"
    "   -o    OUTPUTFILE    Name of the output file (with .wav extension)\n\n" << endl;
}

int ArgsHandler(int argc, char** argv) {
	// int mode; // hide mode (message)
	if (argc == 7) {
		if ((string) argv[1] == "-i" && (string) argv[3] == "-m" && (string) argv[5] == "-o") {
			return 1; // hide mode (message)
		} else if ((string) argv[1] == "-i" && (string) argv[3] == "-f" && (string) argv[5] == "-o") {
			return 3; // hide mode (file)
		} else {
			help((string) argv[0]);
		}
	} else if (argc == 3) {
		if ((string) argv[1] == "-i") {
			return 2; // extract mode (message or file)			
		} else {
			help((string) argv[0]);
			exit(0);
		}
	}
	else {
		help((string) argv[0]);
		exit(0);
	}
	return 0;
}

int FileHandler(int mode, char** argv, QWidget* w) {
	string message, outfile, fileExt, inputExt, inputfile;
	inputfile = (string) argv[2];
	ifstream binStreamFile;
	streampos binFileSize;
	vector<char> msgBuffer;

	if (mode == 3) {
		fileExt = GetFileExtension(string(argv[4]));
		inputExt = GetFileExtension(string(argv[2]));

		binStreamFile.open(string(argv[4]), ios::binary);
		binFileSize = binStreamFile.tellg();
		msgBuffer.reserve(binFileSize); // Reserve the amount of memory for file size on vector.
	}

	// loading the input file in the stream
	ifstream input(inputfile, ios::binary);
	if (!input.is_open()) {
		cout << "[\033[0;91m-\033[0;0m] \033[0;91mError Encountered while opening the file...\033[0;0m" << endl;
		return 0;
	}

	// copying the audio file into a buffer and closing it.
	vector<char> buffer((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));
	if (mode == 3) {
		msgBuffer.assign((istreambuf_iterator<char>(binStreamFile)), (istreambuf_iterator<char>()));
		binStreamFile.close();
	}
	input.close();

	// Modes:
	// 1 => Hide a String
	// 2 => Hide a File or Binary
	// 3 => Extract the file

	if (mode == 1) {
		message = (string) argv[4];
		inputExt = GetFileExtension((string) argv[2]);
		int status = PlayWithWaveBuffer(buffer, message, inputExt);
		if (status == SUCCESS) {
			QMessageBox::information(w, "Info", "Data Hidden Successfully...\nCleaning Memory...");
		} else if (status == ERROR) {
			QMessageBox::information(w, "Error", "Something went wrong...\nCleaning Memory...");
		}
	} else if (mode == 3) {
		int status = PlayWithWaveBuffer(buffer, msgBuffer, fileExt, inputExt);
		if (status == SUCCESS) {
			QMessageBox::information(w, "Info", "Data Hidden Successfully...\nCleaning Memory...");
		} else if (status == ERROR) {
			QMessageBox::information(w, "Error", "Something went wrong...\nCleaning Memory...");
		}
	} else if (mode == 2) {
		int status = FindHiddenMessage(buffer);
		if (status == SUCCESS) {
			QMessageBox::information(w, "Info", "Data Extracted Successfully...\nCleaning Memory...");
		} else if (status == ERROR) {
			QMessageBox::information(w, "Error", "Something went wrong...\nCleaning Memory...");
		}
	}

	// Force remove the buffer from memory
	vector<char>().swap(buffer);
	vector<char>().swap(msgBuffer);
	return 0;
}

int main(int argc, char** argv) {
	QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
	return 0;
}

string GetFileExtension(const string& fileName) {
	if (fileName.find_last_of(".") != string::npos) {
		return fileName.substr(fileName.find_last_of(".") + 1);
	}
	return "";
}
