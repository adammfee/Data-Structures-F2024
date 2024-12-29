#include "MovieTree.hpp"
#include <iostream>
#include <fstream>


using namespace std;
/* ------------------------Starter Code function---------- */
LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn =new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}

void preorderTraversalHelper(TreeNode * root) {
	if (root == NULL) 
    {
		return;
	}
    cout << root->titleChar << " ";
    preorderTraversalHelper(root->leftChild);
    preorderTraversalHelper(root->rightChild);
}

void MovieTree::preorderTraversal() {
	preorderTraversalHelper(root);
	cout << endl;
}

TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

/* --------------------------Constructor---------------------------- */
MovieTree::MovieTree()
{
    root = NULL;
}

/* --------------------------Destructor---------------------------- */

void MovieTree:: rdelete(TreeNode *node)
{
	//TODO
    if (!node) {
        return;
    }

    rdelete(node->leftChild);
    rdelete(node->rightChild);

    /*cout << "Linked list " << node->titleChar << ":" << endl;
    printLL(node, node->titleChar);*/

    LLMovieNode* toDelete = node->head;
    LLMovieNode* temp = NULL;

    while (toDelete != NULL) {
        temp = toDelete->next;
        //cout << "Deleting: " << toDelete->title << endl;
        delete toDelete;
        toDelete = temp;
    }

    node->head = NULL;

    //cout << "Deleting treenode " << node->titleChar << endl;

    delete node;
    node = NULL;
}

MovieTree::~MovieTree()
{
	//TODO
    rdelete(root);
    root = NULL;
}

/* -------------------------showMovieCollection----------------------------- */
void MovieTree::printMovieInventoryHelper(TreeNode* node)
{
	//TODO
    if (!node) {
        return;
    }

    LLMovieNode* temp;

    printMovieInventoryHelper(node->leftChild);
    if (!node->head) {
        return;
    } else {
        temp = node->head;
        cout << "Movies starting with letter: " << node->titleChar << endl;
        while (temp){
            cout << " >> " << temp->title << " " << temp->rating << endl;
            temp = temp->next;
        }
    }
    printMovieInventoryHelper(node->rightChild);
}

void MovieTree::showMovieCollection()
{
	//TODO
    if (!root) {
        return;
    }

    printMovieInventoryHelper(root);
}

/*void MovieTree::printLL(TreeNode* current) { //don't need anymore
    if (!current) {
        return;
    }

    LLMovieNode* temp = current->head;
    //printLL(current->leftChild);
    cout << "Current node: " << current->titleChar << endl;
    if (temp == NULL) {
        cout << "No nodes in " << current->titleChar << endl;
    }
        while (temp != NULL) {
            cout << temp->title << endl;
            temp = temp->next;
        }
}*/

/* --------------------------insertMovie---------------------------- */
TreeNode* MovieTree::addHelper(TreeNode *root, TreeNode* parentpointer, int _ranking, string _title, int _year, float _rating)
{
	//TODO
    LLMovieNode* newMovie = new LLMovieNode; //creates new movie to be added to LL
    newMovie->ranking = _ranking;
    newMovie->rating = _rating;
    newMovie->title = _title;
    newMovie->year = _year;

    if (!root) { //if no root node then add a node with title[0]
        root = new TreeNode;
        root->titleChar = _title[0];
        root->parent = parentpointer;
        root->head = newMovie;
        return root;
    }

    if (root->titleChar == _title[0]) {
        LLMovieNode* temp = root->head;
        LLMovieNode* prev = NULL;

        while (temp && (temp->title < _title)) { //if there is pop LL then cycle through until placed in the right spot
            prev = temp;
            temp = temp->next;
        }

        if (!prev) {
            newMovie->next = root->head;
            root->head = newMovie;
        } else {
            prev->next = newMovie;
            newMovie->next = temp;
        }
        return root;

    } else if (root->titleChar > _title[0]) {
        delete newMovie;
        root->leftChild = addHelper(root->leftChild, root, _ranking, _title, _year, _rating);
    } else {
        delete newMovie;
        root->rightChild = addHelper(root->rightChild, root, _ranking, _title, _year, _rating);
    }

    return root;
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating)
{
	//TODO
    if (!root) {
        root = addHelper(root, NULL, ranking, title, year, rating);    
    } else {
        addHelper(root, NULL, ranking, title, year, rating);
    }
}

/* ------------------------removeMovieRecord------------------------------ */
void MovieTree::removeMovieRecord(std::string title)
{
    //TODO
    TreeNode* temp = root;
    LLMovieNode* toDelete = NULL;
    LLMovieNode* crawler = NULL;

    if (!temp) {
        cout << "Movie not found." << endl;
        return;
    }

    while (temp != NULL) {
        if (title[0] < temp->titleChar) {
            temp = temp->leftChild;
        } else if (title[0] > temp->titleChar) {
            temp = temp->rightChild;
        } else {
            toDelete = temp->head;

            if (toDelete != NULL && toDelete->title == title) { //edge case with one node in LL
                temp->head = toDelete->next;
                delete toDelete;
                /*if (temp->head == NULL) { 
                    cout << "[INFO] Calling removeBSTNode for " << title[0] << endl; I have zero fucking idea why this seg faults if i uncomment it
                    removeBSTNode(title[0]);
                }*/
                return;
            } else {
                while (toDelete != NULL) {
                    crawler = toDelete;
                    toDelete = toDelete->next;
                    if (toDelete->title == title) {
                        crawler->next = toDelete->next;
                        delete toDelete;
                        return;
                    }
                }
                cout << "Movie not found." << endl;
                return;
            }
        }
    }
}

/* ------------------------removeBSTNode------------------------------ */
void MovieTree::removeLLnodes(TreeNode* node){
    //TODO
    if (!node) {
        return;
    }

    LLMovieNode* temp = NULL;
    LLMovieNode* toDelete = node->head;

    while (toDelete != NULL) {
        temp = toDelete->next;
        delete toDelete;
        toDelete = temp;
    }

    node->head = NULL;
}

TreeNode* MovieTree::getSuccessor(TreeNode* node){
    //TODO
    if (!node || !node->rightChild) {
        return NULL;
    }

    while (node->leftChild != NULL) {
        node = node->leftChild;
    }

    return node;
}

TreeNode* MovieTree::removeBSTNodeHelper(TreeNode* node, TreeNode* parent, char titleFirstLetter){
    //TODO
    if (!node) {
        cout << "[ERROR] Attempted to delete a node that was never allocated." << endl;
        return NULL;
    }

    if (node->titleChar > titleFirstLetter) { // look at current node children
        node->leftChild = removeBSTNodeHelper(node->leftChild, node, titleFirstLetter);
    } else if (node->titleChar < titleFirstLetter) {
        node->rightChild = removeBSTNodeHelper(node->rightChild, node, titleFirstLetter);
    } else { // found node
        if (node->head != NULL) {
            removeLLnodes(node);
        }

        if (node->leftChild == NULL && node->rightChild == NULL) { // edge case with no children
            delete node;
            return NULL;
        } else if (node->leftChild != NULL && node->rightChild == NULL) { // left child
            TreeNode* temp = node->leftChild;
            delete node;
            return temp;
        } else if (node->leftChild == NULL && node->rightChild != NULL) { // right child
            TreeNode* temp = node->rightChild;
            delete node;
            return temp;
        } else { // both children
            TreeNode* successor = getSuccessor(node->rightChild);
            node->titleChar = successor->titleChar;
            node->head = successor->head;

            successor->head = NULL;
            node->rightChild = removeBSTNodeHelper(node->rightChild, node, successor->titleChar);
            return node;
        }
    }
    return node;
}

void MovieTree::removeBSTNode(char titleFirstLetter){
    //TODO
    root = removeBSTNodeHelper(root, NULL, titleFirstLetter);
    if (!root) {
        cout << "Tree is now empty" << endl;
    }
    return;
}


/* --------------------------rightRotation---------------------------- */
void MovieTree::rightRotation(TreeNode* curr)
{
	//TODO
    if (!curr || !curr->leftChild) {
        return;
    }

    TreeNode* leftChild = curr->leftChild;
    TreeNode* leftRightSubtree = leftChild->rightChild;

    leftChild->rightChild = curr;
    curr->leftChild = leftRightSubtree;

    if (leftRightSubtree != NULL) {
        leftRightSubtree->parent = curr;
    }
    leftChild->parent = curr->parent;

    if (curr->parent != NULL) {
        if (curr == curr->parent->leftChild) {
            curr->parent->leftChild = leftChild;
        } else {
            curr->parent->rightChild = leftChild;
        }
    } else {
        root = leftChild;
    }

    curr->parent = leftChild;
}
