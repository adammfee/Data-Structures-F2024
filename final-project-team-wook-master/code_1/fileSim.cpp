#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "fileSim.hpp"
#include <vector>



// ===========Lifecycle methods===========

FileSim::FileSim(int _diskSize) : numCollisions(0) {
    diskSize = _diskSize;

    root = new Inode;
    root->parentNode = nullptr;
    root->name = "(root)";
    root->creationTime = time(NULL);
    root->modTime = root->creationTime;
    root->isDirectory = true;
    currentDir = root;
    currentUsedDiskMemory = 0;

    // Add Hash Table intialization
    tableSize = 5;
    table = new HashNode*[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

int recursiveDelete(Inode *node) {
    int memoryFreed = node->fileSize;
    for (int i = 0; i < node->childNodes.size(); i++) {
        memoryFreed += recursiveDelete(node->childNodes[i]);
    }

    delete node;
    return memoryFreed;
}

FileSim::~FileSim() {
    // Any postprocessing that may be required
    recursiveDelete(root);
    for (int i = 0; i < tableSize; i++) { // delete all associated ll in table
        HashNode* current = table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table; // delete table
}

// ===========Helper methods===========

int FileSim::makeNode(std::string name, bool isDirectory) { // make sure added file doesn't exceed capacity
    for (int i = 0; i < currentDir->childNodes.size(); i++){
        if (currentDir->childNodes[i]->name == name) {
            cout << "Duplicate name: " << name << endl;
            return 0;
        }
    }

    if (currentUsedDiskMemory + 1 > diskSize) {
        cout << "No space left on disk!" << endl;
        return 0;
    }

    int size = 1;

    if (!isDirectory) {
        for (int i = 1; i < name.size(); i++) {
            size++;
        }
    }

    Inode* newNode = new Inode; // create instance of new node and set attributes accordingly
    newNode->name = name;
    newNode->creationTime = time(NULL);
    newNode->fileSize = size;
    newNode->isDirectory = isDirectory;
    newNode->parentNode = currentDir;
    newNode->modTime = newNode->creationTime;

    currentDir->childNodes.push_back(newNode);
    currentUsedDiskMemory++;

    insertItem(name, newNode);

    return 0;
}

Inode* getChild(Inode* parent, std::string name) {
    return nullptr;
}

Inode* FileSim::pathToNode(std::string path) {
    // Returns the node pointed to by `path`.
    //
    // `path` may be...
    //    1. The special path '..', which returns the parent of the current
    //       directory, or the current directory if there is no parent.
    //    2. An absolute path in the format /dir1/dir2/...
    //       where / is the root and /dir1 is a child directory of the root.
    //    3. A relative path (a file in the current working directory)

    // 1
    if (path == "..") {
        return currentDir->parentNode;
    }

    // 2 & 3
    Inode *node;
    if (path.front() == '/') {
        node = root; // 2
        path = path.substr(1);
        
    } else {
        node = currentDir; // 3
        //cout << "node: " << node->name << endl;
    }

    std::stringstream pathStream(path);
    std::string pathSegment;
    std::vector<std::string> seglist;

    while (std::getline(pathStream, pathSegment, '/')) {
        if (Inode* child = getChild(node, pathSegment)) {
            node = child;
        } else {
            return nullptr;
        }
    }
    //cout << "updated node:" << node->name << endl;
    return node;
}

std::string FileSim::nodeToPath(Inode *node) {
    // Returns an absolute path given a node
    if (!node->parentNode) {
        // Root
        return "/";
    }

    std::string path = "";
    while (node->parentNode) {
        path.insert(0, "/" + node->name);
        node = node->parentNode;
    }
    return path;
}

void treeHelper(Inode* node, int level) {
    // Recursively print the node's contents
    if (!node) {
        return;
    }

    if (node->name == "(root)") {
        cout << " " << node->name << endl;
    }

    level += 1;

    for (int i = 0; i < node->childNodes.size(); i++) {
        cout << "- " << node->childNodes[i]->name << endl;
        treeHelper(node->childNodes[i], level);
    }
}

std::string timeToString(time_t t) {
    return std::string();
}

// ===========Public API===========

int FileSim::touch(std::string fileName) {
    return makeNode(fileName, false);
}

int FileSim::mkdir(std::string dirName) {
    return makeNode(dirName, true);
}

void FileSim::ls() {
    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        cout << currentDir->childNodes[i]->name << endl;
    }
}

void FileSim::pwd() {
    vector<Inode*> curDir;
    Inode* temp = currentDir;

    while (temp != root){
        curDir.push_back(temp);
        temp = temp->parentNode;
    }

    if (!curDir.size()){
        cout << "/";
    }
    
    for (int i = curDir.size() - 1; i >= 0; i--){
        cout << "/" << curDir[i]->name;
    }

    cout << endl;
}

void FileSim::tree() {
    treeHelper(currentDir, 0);
}

int FileSim::cat(std::string path) {
    Inode* target = NULL;

    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        if (currentDir->childNodes[i]->name == path) {
            target = currentDir->childNodes[i];
            break;
        }
    }

    if (!target) {
        cout << "cat: " << path << ": No such file or directory" << endl;
        return 0;
    }

    if (target->isDirectory) {
        cout << "cat: " << target->name << ": Is a directory" << endl;
        return 0;
    }

    cout << target->fileData << endl;

    return 0;
}

int FileSim::stat(std::string path) {
    Inode* targetFile = NULL;
    
    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        if (currentDir->childNodes[i]->name == path) {
            targetFile = currentDir->childNodes[i];
            break;
        }
    }

    if (!targetFile) {
        cout << "stat: " << path << ": no such file or directory" << endl;
        return 0;
    }

    cout << "--------------" << path << "--------------" << endl;
    cout << "Name: " << targetFile->name << endl;
    cout << "File Size: " << targetFile->fileSize << endl;
    cout << "File Type: " << targetFile->fileData << endl;
    cout << "Creation Time: " << targetFile->creationTime << endl;
    cout << "Mod Time: " << targetFile->modTime << endl;
    cout << "Parent Directory: " << targetFile->parentNode->name << endl;

    return 0;
}

int FileSim::edit(std::string path, std::string newValue) { // last test case keeps failing, it's esssentially trying to name file A to B and then rename after from A to C which doesn't make sense
    // Overwrite the file with a new value
    Inode* target = NULL;

    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        if (currentDir->childNodes[i]->name == path) {
            target = currentDir->childNodes[i];
            //cout << "Found target" << endl;
            break;
        }
    }

    if (!target) {
        cout << "edit: " << path << ": No such file or directory" << endl;
        return 0;
    }

    int newSize = newValue.size() + 1; // edits the file size by length of string size plus one
    int oldSize = target->fileSize;

    if (currentUsedDiskMemory + newSize - oldSize > diskSize) { // ensures new length doesn't exceed disk size
        cout << "edit: No more space left on disk" << endl;
        return 0;
    }

    if (target->isDirectory) { // if target is directory, unable to edit it
        cout << "edit: " << target->name << ": Is a directory" << endl;
        return 0;
    }

    // set file data accordingly
    target->name = newValue;
    target->fileSize = newSize;
    currentUsedDiskMemory = currentUsedDiskMemory - oldSize + newSize;

    return 1;
}

int FileSim::cd(std::string dirPath) {
    Inode* target = NULL;
    bool fileFound = false;
    
    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        if (currentDir->childNodes[i]->name == dirPath) {
            target = currentDir->childNodes[i];
            fileFound = true;
            break;
        }
    }

    if (dirPath == "..") {
        currentDir = currentDir->parentNode;
        return 1;
    }

    if (!target && !fileFound) {
        cout << "cd: no such file or directory: " << dirPath << endl;
        return 0;
    }

    if (!target->isDirectory && fileFound) {
        cout << "cd: not a directory: " << dirPath << endl;
        return 0;
    }

    currentDir = target;

    return 1;
}

int FileSim::rm(std::string path, bool recursive) {
    Inode* target = NULL;

    if (path == "." || path == "..") {
        cout << "rm: '.' and '..' may not be removed" << endl;
        return 0;
    }
    
    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        if (currentDir->childNodes[i]->name == path) {
            target = currentDir->childNodes[i];
            
            if (target->isDirectory && !recursive) {
                cout << "rm: " << path << ": is a directory" << endl;
                return 0;
            }

            currentDir->childNodes.erase(currentDir->childNodes.begin() + i);
            break;
        }
    }

    if (!target) {
        cout << "rm: " << path << ": No such file or directory" << endl;
        return 0;
    }

    removeFromHashTable(path);
    currentUsedDiskMemory -= recursiveDelete(target); // deletes the memory along with the file in the tree

    return 1;
}

int FileSim::mv(std::string originPath, std::string destPath) {
    Inode* targetOrigin = NULL;
    bool origin = false;

    if ("/" + originPath == destPath) {
        cout << "mv: " << destPath << ": Already exists!" << endl;
        return 0;
    }

    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        if (currentDir->childNodes[i]->name == originPath) {
            targetOrigin = currentDir->childNodes[i];
            origin = true;
        }
    }

    if (!origin) {
        cout << "mv: " << originPath << ": No such file or directory" << endl;
        return 0;
    }

    for (int i = originPath.size() - 1; i >= 0; i--) {
        if (originPath[i] == '.') { // changing the name of a file
            targetOrigin->name = destPath;
            return 1;
        }
    }

    for (int i = 0; i < currentDir->childNodes.size(); i++) {
        if ("/" + currentDir->childNodes[i]->name + "/" + originPath == destPath) {
            targetOrigin->parentNode = currentDir->childNodes[i];
            return 1;
        }
    }

    Inode* destDir = pathToNode(destPath);
    targetOrigin->parentNode = destDir;
    destDir->childNodes.push_back(targetOrigin);

    return 1;
}

// search needs editing - after removing a file/dir, searching for that causes termination std::bad_alloc
void FileSim::search(std::string key) {
    HashNode* node = searchItem(key);

    if (!node) {
        cout << "No such file or directory: " << key << endl;
        return;
    }

    while (node != NULL) {
        if (node->key == key) {
            pwd();
        }
        node = node->next;
    }
}

// ===========Hash Table===========

// helper
void FileSim::removeFromHashTable(std::string key) {
    unsigned int index = hashFunction(key);
    HashNode* prev = NULL;
    HashNode* current = table[index];

    while (current != NULL) {
        if (current->key == key) {
            if (!prev) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// creates new node in hash table 
HashNode *FileSim::createNode(std::string _key, Inode *_iptr, HashNode *_next) {
    HashNode* newNode = new HashNode;
    newNode->key = _key;
    newNode->iptr = _iptr;
    newNode->next = _next;
    return newNode;
}

// Hash Function
unsigned int FileSim::hashFunction(string s) {
    unsigned int hash = s.size();
    return (hash % tableSize);
}

// Search Method
HashNode *FileSim::searchItem(string key) {
    unsigned int index = hashFunction(key);
    HashNode* temp = table[index];

    for (int i = 0; i < tableSize; i++) { // loops through the table
        unsigned int probeIndex = (index + i) % tableSize; 
        if (table[probeIndex]) { // if the current hash is a bucket then check if it's the key
            if (table[probeIndex]->key == key) {
                return table[probeIndex]; // key found
            }
        }
    }

    return nullptr; // key not found
}

// Insert new record
bool FileSim::insertItemLinear(std::string _key, Inode *_iptr) {
    unsigned int index = hashFunction(_key);

    for (int i = 0; i < tableSize; i++) {
        unsigned int probeIndex = (index + i) % tableSize;

        if (!table[probeIndex] || table[probeIndex]->key == _key) {
            if (!table[probeIndex]) {
                numCollisions++;
            }

            table[probeIndex] = createNode(_key, _iptr, NULL);
            numElements++;
            return true;
        }
    }

    resizeHashTable();
    cout << "Hash table has been resized, your file should be added." << endl;

    return false;
}

bool FileSim::insertItemQuadratic(std::string _key, Inode *_iptr) {
    unsigned int index = hashFunction(_key);

    for (int i = 0; i < tableSize; i++) {
        unsigned int probeIndex = (index + i * i) % tableSize;

        if (!table[probeIndex] || table[probeIndex]->key == _key) {
            numCollisions++;
        }

        table[probeIndex] = createNode(_key, _iptr, NULL);
        return true;
    }
    
    resizeHashTable();
    cout << "Hash table has been resized, your file should be added." << endl;

    return false;
}

bool FileSim::insertItemChaining(std::string _key, Inode *_iptr) {
    if (!searchItem(_key)) {
        unsigned int index = hashFunction(_key);
        HashNode* nw = createNode(_key, _iptr, NULL);
        if (!table[index]) {
            table[index] == nw;
        } else {
            nw->next = table[index];
            table[index] = nw;
        }
        return true;
    } else {
        cout << "Duplicate entry" << endl;
        return false;
    }
}

//Resize the table
void FileSim::resizeHashTable() {
    int oldSize = tableSize;
    tableSize *= 2;
    HashNode** oldTable = table;

    table = new HashNode*[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = NULL;
    }

    numCollisions = 0;

    for (int i = 0; i < oldSize; i++) {
        HashNode* current = oldTable[i];
        while (current != NULL) {
            insertItemLinear(current->key, current->iptr);
            current = current->next;
        }
    }

    delete[] oldTable;
}

void FileSim::resetCollisions() {
    numCollisions = 0;
}

int FileSim::getCollisions() const {
    return numCollisions;
}