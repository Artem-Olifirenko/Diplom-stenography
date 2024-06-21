// guard header
#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#include <vector>
#include <string>
#include <fstream>
#include <QWidget>

std::string GetFileExtension(const std::string& fileName);
int FileHandler(int mode, char** argv, QWidget* w);
int ArgsHandler(int argc, char** argv);

#endif // __MAIN_H_INCLUDED__