/*******************************************************************/
/*                CUSatelliteNetwork Implementation                 */
/*******************************************************************/
/* TODO: Implement the member functions of class CUSatelliteNetwork */
/*       This class uses a linked-list of CUSatellite nodes to      */
/*       represent communication paths between Satellites           */
/*******************************************************************/

#include "CUSatelliteNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
CUSatelliteNetwork::CUSatelliteNetwork() 
{
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUSatelliteNetwork::isEmpty()
{
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new Satellite to the network
 *   between the Satellite previous and the Satellite that follows it in the network.
 * @param previous - name of the Satellite that comes before the new Satellite
 * @param SatelliteName - name of the new Satellite 
 * @param distance - distance of satellite from earth
 * @return none
 */
void CUSatelliteNetwork::addSatelliteInfo(string previous, string satelliteName, int distance) 
{     
    // TODO: Copy-paste your solution from Assignment 3
    CUSatellite* newSatellite = new CUSatellite;
    newSatellite->name = satelliteName;
    newSatellite->distanceFromEarth = distance;
    newSatellite->next = nullptr;
    newSatellite->numberMessages = 0;

    if(previous == ""){
        newSatellite->next = head;
        head = newSatellite;
        cout << "adding: " << satelliteName << " (HEAD)" << endl;
    }else{
        if(head == nullptr){
            cout << "Cannot add new node; previous node not found because list is empty." << endl;
            delete newSatellite;
            return;
        }

        CUSatellite* temp = head;
        while(temp != nullptr && temp->name != previous){
            temp = temp->next;
        }

        if(temp == nullptr){
            cout << "Cannot add new node; previous node not found\n" << endl;
            delete newSatellite;
        }else{
            newSatellite->next = temp->next;
            temp->next = newSatellite;
            cout << "adding: " << satelliteName << " (prev: " << previous << ")" << endl;
        }
    }
}

/*

 * Purpose: populates the network with the predetermined CUSatellites
 * @param none
 * @return none
 */
void CUSatelliteNetwork::loadDefaultSetup()
{
    deleteEntireNetwork();
    // TODO: Copy-paste your solution from Assignment 3
    addSatelliteInfo("", "MAVEN", 9);
    addSatelliteInfo("", "JUNO", 4);
    addSatelliteInfo("", "PIONEER", 5);
    addSatelliteInfo("", "GALILEO", 6);
    addSatelliteInfo("", "KEPLER", 10);
    addSatelliteInfo("", "TESS", 2);
}

/*
 * Purpose: Search the network for the specified Satellite and return a pointer to that node
 * @param SatelliteName - name of the Satellite to look for in the network
 * @return pointer to node of SatelliteName, or NULL if not found
 *
 */
CUSatellite* CUSatelliteNetwork::searchForSatellite(string satelliteName)
{
    // TODO: Copy-paste your solution from Assignment 3
    CUSatellite* temp = head;
    while(temp != nullptr){
        if(temp->name == satelliteName){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

/*
 * Purpose: Relay a message through the linked list until the specified Satellite
 * @param string receiver - name of the Satellite 
 * @return none
 */
void CUSatelliteNetwork::transmitInfo(string receiver)
{
    // TODO: Copy-paste your solution from Assignment 3
    CUSatellite* temp = head;
    bool found = false;

    if(head == nullptr){
        cout << "Empty list" << endl;
        return;
    }

    while(temp != nullptr){
        if(temp->name == receiver){
            found = true;
            break;
        }
        temp = temp->next;
    }

    if(!found){
        cout << "Satellite not found" << endl;
        return;
    }

    temp = head;
    while(temp != nullptr){
        temp->message = "distance of " + temp->name + " from earth is " + to_string(temp->distanceFromEarth);
        temp->numberMessages++;

        cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << endl;

        if(temp->name == receiver){
            //found = true;
            break;
        }
        temp = temp->next;
    }
}

/*

 * Purpose: prints the current list in an organized manner
 * @param none
 * @return none

 */
void CUSatelliteNetwork::printNetwork() 
{
    /* finished. do not touch. */
    cout << "== CURRENT PATH ==" << endl;

    if (head)
    {
        CUSatellite* temp = head;
        
        while (temp)
        {
            cout << temp->name << "(" << temp->distanceFromEarth << ") -> ";
            temp = temp->next;
        }
        cout << "NULL";
    }
    else
    {
        cout << "nothing in path";
    }

    cout << endl << "===" << endl;


}

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the Satellite in the network with the specified name.
 * @param SatelliteName - name of the Satellite to delete in the network
 * @return none
 */
void CUSatelliteNetwork::deleteCUSatellite(string satelliteName) 

{
    // TODO: Complete this function
    if(head == nullptr){
        cout << "Satellite does not exist." << endl;
        return;
    }

    CUSatellite* toDelete = head;
    CUSatellite* temp = nullptr;

    if(head->name == satelliteName){
        head = head->next; //moves head to next node
        delete toDelete; //delete old head
        return;
    }

    while(toDelete != nullptr){
        if(toDelete->name == satelliteName){
            if(temp != nullptr){
                temp->next = toDelete->next;
            }
            delete toDelete; //delete found node
            return;
        }

        temp = toDelete; //moves previous to current node
        toDelete = toDelete->next; //moves to next node
    }
    
    cout << "Satellite does not exist." << endl;
}

/*
 * Purpose: deletes all Satellites in the network starting from the head Satellite.

 * @param: none
 * @return: none
 */
void CUSatelliteNetwork::deleteEntireNetwork()
{
    // TODO: Complete this function
    if(head == nullptr){
        //cout << "Empty List" << endl;
        return;
    }

    CUSatellite* toDelete = head;
    CUSatellite* temp = nullptr;

    while(temp != nullptr){
        if(temp != nullptr){
            temp->next = toDelete->next;
        }
        delete toDelete; //deletes current node
        temp = toDelete; //moves previous to current node
        toDelete = toDelete->next; //moves to next node
    }

    head = nullptr;
    return;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool CUSatelliteNetwork::detectLoop() 
{
    // TODO: Complete this function
    CUSatellite* slow = head;
    CUSatellite* fast = head;

    while(fast != nullptr && fast->next != nullptr){
        fast = fast->next->next;
        slow = slow->next;

        if(fast == slow){
            return true;
        }
    }
    return false;
}

/*
* Purpose: Creates a loop from last node to the Satellite specified.
* @param SatelliteName - name of the Satellite to loop back to
* returns the last node before loop creation (to break the loop)
*/
CUSatellite* CUSatelliteNetwork::createLoop(string satelliteName) 
{
    // TODO: Complete this function
    if(head == nullptr){
        return nullptr;
    }
    
    CUSatellite* temp = head;
    CUSatellite* loop = nullptr;
    CUSatellite* last = nullptr;

    while(temp != nullptr){
        if(temp->name == satelliteName){
            loop = temp;
        }
        if(temp->next == nullptr){
            last = temp;
        }
        temp = temp->next; //move to next node
    }

    if(loop != nullptr){
        last->next = loop; //creates loop
        return last; //returns last node before loop created
    }else{
        //cout << "Satellite not found." << endl;
        return nullptr;
    }
}

/*
 * Purpose: Take the chunk of nodes from start index to end index and
 *          move that chunk to the end of the List
 * @param: start_index, end_index - indices of start node and the end node
 * @return: none
 */
void CUSatelliteNetwork::readjustNetwork(int start, int end)
{
    // TODO: Complete this function
    if(head == nullptr){
        cout << "Linked List is Empty" << endl;
        return;
    }

    if(start > end){
        cout << "Invalid indices" << endl;
        return;
    }

    CUSatellite* temp = head;
    int len = 0;

    while(temp != nullptr){ //calculates length of list
        len++;
        temp = temp->next;
    }

    if(end >= len || end < 0){
        cout << "Invalid end index" << endl;
        return;
    }

    if(start >= len || start < 0){
        cout << "Invalid start index" << endl;
        return;
    }
    
    int index = 0;
    temp = head;
    CUSatellite* prevStart = nullptr;
    CUSatellite* startPt = nullptr;
    CUSatellite* nextEnd = nullptr;
    CUSatellite* endPt = nullptr;

    while(temp != nullptr){
        if(index == start - 1){
            prevStart = temp;
        }
        if(index == start){
            startPt = temp;
        }
        if(index == end){
            endPt = temp;
            nextEnd = endPt->next;
            endPt->next = nullptr;
        }
        temp = temp->next;
        index++;
    }

    if(start == 0){
        head = nextEnd;
    }else{
        prevStart->next = nextEnd;
    }

    temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }

    temp->next = startPt;
}

/*
 * Purpose: Destructor to delete the entire list on program termination
 * @param none
 * @return none
 */
CUSatelliteNetwork::~CUSatelliteNetwork()
{
    // TODO: Complete this function
    
}