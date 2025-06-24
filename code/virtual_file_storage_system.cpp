#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

const int DISK_SIZE = 10 * 1024 * 1024; // 10MB disk size
const int METADATA_SIZE = 1 * 1024 * 1024; // 1MB for metadata
const int TRACKER_SIZE = 1 * 1024 * 1024; // 1MB for free block tracker
const int FILE_DATA_SIZE = DISK_SIZE - METADATA_SIZE - TRACKER_SIZE; // 8MB for file data

struct File
{
    string name;
    int startAddress;
    int size;
};

class VirtualFileSystem
{
    private:
    vector<File> files;
    char* disk;
    bool* freeBlocks;
    string metadataFilePath = "File_system.bin";

    public:
    VirtualFileSystem() {
        disk = new char[DISK_SIZE];
        freeBlocks = new bool[FILE_DATA_SIZE];
        
        for (int i = 0; i < FILE_DATA_SIZE; ++i)
        {
            freeBlocks[i] = true; // Initially, all blocks are free
        }

        // Initialize metadata
        ifstream file(metadataFilePath, ios::binary);
        if (!file) {
            // Create a new disk
            ofstream newFile(metadataFilePath, ios::binary);
            newFile.close();
        }
    }

    ~VirtualFileSystem() {
        delete[] disk;
        delete[] freeBlocks;
    }

    int findFreeBlock(int size) {
        int freeCount = 0;
        for (int i = 0; i < FILE_DATA_SIZE; ++i) {
            if (freeBlocks[i]) {
                freeCount++;
                if (freeCount == size) {
                    return i - size + 1; // Return the starting address
                }
            }
            else {
                freeCount = 0;
            }
        }
        return -1; // No space found
    }

    void createFile(string name, string content) {
        int contentSize = content.size();
        if (contentSize > FILE_DATA_SIZE) {
            cout << "Error: File content exceeds available space!" << endl;
            return;
        }

        int requiredBlocks = (contentSize + 511) / 512; // Round up to nearest block
        int startAddress = findFreeBlock(requiredBlocks);

        if (startAddress == -1) {
            cout << "Error: Not enough space on the disk!" << endl;
            return;
        }

        // Store file metadata
        File file;
        file.name = name;
        file.startAddress = startAddress;
        file.size = contentSize;
        files.push_back(file);

        // Store file content in the disk
        for (int i = 0; i < contentSize; ++i) {
            disk[startAddress + i] = content[i];
            freeBlocks[startAddress + i] = false;
        }
        cout << "File created successfully!" << endl;
    }

    void listFiles() {
        if (files.empty()) {
            cout << "No files found." << endl;
            return;
        }
        for (const auto& file : files) {
            cout << "File: " << file.name << ", Size: " << file.size << " bytes" << endl;
        }
    }

    void viewFile(string name) {
        for (const auto& file : files) {
            if (file.name == name) {
                cout << "File content of " << name << ":" << endl;
                for (int i = 0; i < file.size; ++i) {
                    cout << disk[file.startAddress + i];
                }
                cout << endl;
                return;
            }
        }
        cout << "File not found!" << endl;
    }

    void deleteFile(string name) {
        for (auto it = files.begin(); it != files.end(); ++it) {
            if (it->name == name) {
                // Mark the blocks as free
                for (int i = 0; i < it->size; ++i) {
                    freeBlocks[it->startAddress + i] = true;
                }
                files.erase(it);
                cout << "File deleted successfully!" << endl;
                return;
            }
        }
        cout << "File not found!" << endl;
    }

    void deleteAllFiles() {
        files.clear();
        fill(freeBlocks, freeBlocks + FILE_DATA_SIZE, true);
        cout << "All files have been deleted!" << endl;
    }

    void resetSystem() {
        deleteAllFiles();
        ofstream newFile(metadataFilePath, ios::binary);
        newFile.close();
        cout << "System has been reset!" << endl;
    }

    void copyToWindows(string name) {
        // Find the file by name
        for (const auto& file : files) {
            if (file.name == name) {
                // Create a new file in the Windows file system
                ofstream outFile(name, ios::binary);
                if (outFile.is_open()) {
                    for (int i = 0; i < file.size; ++i) {
                        outFile.put(disk[file.startAddress + i]);
                    }
                    cout << "File copied to Windows successfully!" << endl;
                }
                else {
                    cout << "Error: Could not open file to save on Windows." << endl;
                }
                return;
            }
        }
        cout << "File not found!" << endl;
    }

    void copyFromWindows(string filename) {
        // Read the file from Windows
        ifstream inFile(filename, ios::binary);
        if (!inFile.is_open()) {
            cout << "Error: Could not open file from Windows." << endl;
            return;
        }

        // Read content into a string
        string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();

        // Check if there is enough space to store the file
        createFile(filename, content);
    }
};

int main() {
    VirtualFileSystem vfs;
    int choice;

    do {
        cout << "Menu:\n";
        cout << "1. Create a new file\n";
        cout << "2. List files\n";
        cout << "3. View file\n";
        cout << "4. Delete file\n";
        cout << "5. Delete all files (reset system)\n";
        cout << "6. Copy file from virtual disk to Windows\n";
        cout << "7. Copy file from Windows to virtual disk\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();  // To ignore the newline character from the previous input

        if (choice == 1) {
            string name, content;
            cout << "Enter file name: ";
            getline(cin, name);
            cout << "Enter file content: ";
            getline(cin, content);
            vfs.createFile(name, content);
        }
        else if (choice == 2) {
            vfs.listFiles();
        }
        else if (choice == 3) {
            string name;
            cout << "Enter file name to view: ";
            getline(cin, name);
            vfs.viewFile(name);
        }
        else if (choice == 4) {
            string name;
            cout << "Enter file name to delete: ";
            getline(cin, name);
            vfs.deleteFile(name);
        }
        else if (choice == 5) {
            vfs.resetSystem();
        }
        else if (choice == 6) {
            string name;
            cout << "Enter file name to copy to Windows: ";
            getline(cin, name);
            vfs.copyToWindows(name);
        }
        else if (choice == 7) {
            string filename;
            cout << "Enter file name to copy from Windows: ";
            getline(cin, filename);
            vfs.copyFromWindows(filename);
        }
        else if (choice == 8) {
            cout << "Exiting system." << endl;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
