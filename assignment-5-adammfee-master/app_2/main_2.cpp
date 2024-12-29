#include "../code_2/WaitlistQueue.hpp"
#include <iostream>

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu(){
    cout << "*----------------------------------------*" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Peek" << endl;
    cout << "4. Resize" << endl;
    cout << "5. Quit" << endl;
    cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
    // DO NOT MODIFY THIS.
    if(argc > 2)
    {
        freopen(argv[2],"r",stdin);
    }
    
    /* TODO */
    int initialQueueSize = stoi(argv[1]);

    WaitlistQueue queue(initialQueueSize);
    int choice = 0;
    int size;
    string value;
    string* q;

    while (choice != 5) {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to add into queue:" << endl;
                cin >> value;
                queue.enqueue(value);
                break;

            case 2:
                queue.dequeue();
                break;

            case 3:
                cout << queue.peek() << endl;
                break;

            case 4:
                cout << "Enter the new capacity:" << endl;
                int newCapacity;
                cin >> newCapacity;
                cout << "Resizing from " << queue.capacity() << " to " << newCapacity << endl;
                queue.resize(newCapacity);
                break;

            case 5:
                cout << "Quitting..." << endl;
                cout << "Contents of the queue:" << endl;
                q = queue.getQueue();
                size = queue.size();
                
                for (int i = 0; i < size; i++) {
                    cout << q[i] << endl;
                }

                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                break;
        }
    }
    
    return 0;
}