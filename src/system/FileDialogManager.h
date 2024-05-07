#ifndef UIEDITOR_FILEDIALOGMANAGER_H
#define UIEDITOR_FILEDIALOGMANAGER_H


// TODO IMPLEMENT OTHER SYSTEMS
#include <string>
#include <windows.h>

class FileDialogManager {
public:
    static std::string OpenFileDialog();
    static std::string OpenFileDialog(const std::string& title);
    static std::string OpenFileDialog(const std::string& title, const std::string& filter);
};


#endif //UIEDITOR_FILEDIALOGMANAGER_H
