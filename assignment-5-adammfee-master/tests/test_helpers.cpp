#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/WordDecoder.hpp"
#include "../code_2/WaitlistQueue.hpp"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

string test_push(string* arr, int length)
{
    WordDecoder calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    Letter * temp = calc.getStackHead();
    cout << "Print stack from top to bottom:" << endl;
    while(temp != NULL){
        cout << temp->letter << endl;
        temp = temp->next;
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}

string test_pop(string* arr, int length)
{
    WordDecoder calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    int flag = 0;
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            string num = calc.getStackHead()->letter;
            cout << num << endl;
            calc.pop();
            flag++;
            if(flag > 10000){
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}

string test_peek(string* arr, int length)
{
    WordDecoder calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            if(calc.peek()){
                string num = calc.peek()->letter;
                cout << num << endl;
                calc.pop();
            }
            else{
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;  
}

string test_all(string* arr, int length)
{
    WordDecoder calc;
    testing::internal::CaptureStdout();
    
   
    for(int i=0;i<2;i++)
    {
        cout<<"push: "<<arr[i]<<endl;
        calc.push(arr[i]);
    }
    
    cout<<"poping thrice "<<endl;
    calc.pop();
    calc.pop();
    calc.pop();
    
    for(int i=2;i<length;i++)
    {
        cout<<"push: "<<arr[i]<<endl;
        calc.push(arr[i]);
    }
    
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            if(calc.peek()){
                string num = calc.peek()->letter;
                cout << num << endl;
                calc.pop();
            }
            else{
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}


string test_evaluate(string* arr, int length)
{
    WordDecoder calc;
     testing::internal::CaptureStdout();
    calc.evaluate(arr, length);
       
    // string ss="";
    // for(int i=0;i<length;i++)
    // {
    //     ss = ss + arr[i]+" ";
    // }
    
    // if(status)
    // {
    //     cout << ss<<"= " << calc.peek()->letter << endl;
    //     calc.pop();
    //     cout<< "After computation poping"<<endl;
    //     if(!calc.peek()) 
    //         cout << "Correct!" << endl;
    //     else 
    //         cout << "should be empty." << endl;
    // }
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}


string test_consQ(){
    testing::internal::CaptureStdout();
    WaitlistQueue wq(5);
    int front = wq.getQueueFront();
    int back = wq.getQueueEnd();
    if(front == -1 and back == -1) cout << "Correct!" << endl;
    else cout << "front and back are not -1, check constructor" << endl;
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_enQ(string course, int length){
    
    WaitlistQueue wq(length);
    testing::internal::CaptureStdout();
   
    for(int i=0; i<length; i++)
    {
        string c = course + to_string(i);
        wq.enqueue(c);
    }
    string* q = wq.getQueue();
    int front = wq.getQueueFront();
    int size = wq.size();
    cout << "Print queue from front to back:" << endl;
    for(int i = front; i <= (front + size - 1) % length; i++)
        cout << q[i] << endl;

    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_deQ(string course, int length, int dequeue)
{
    WaitlistQueue wq(length);
    testing::internal::CaptureStdout();
   
    for(int i = 0; i < length; i++)
    {
        string c = course + to_string(i);
        wq.enqueue(c);
    }
    
    cout<< "dequeuing "<< dequeue <<" times"<<endl;
    for(int i = 0; i < dequeue; i++)
    {
        wq.dequeue();
    }
    int front = wq.getQueueFront();
    string* q = wq.getQueue();
    int size = wq.size();

    if(length > dequeue)
    {
        cout << "Print queue from front to back:" << endl;
        for(int i = front; i <= (front + size - 1) % length; i++) cout << q[i] << endl;
    }
    
    string output = testing::internal::GetCapturedStdout();
    return output;   
}

string test_peekQ(string course, int length, int deQ)
{
    WaitlistQueue wq; //by default size is 5 so not passing length to constructor
    testing::internal::CaptureStdout();
     
    cout << "enqueuing " << length << " elements" << endl;
    for(int i = 0; i < length; i++)
    {
        string c = course+to_string(i);
        wq.enqueue(c);
    }
    
    cout << "dequeuing " << deQ << " times" << endl;
    for(int i = 0; i < deQ; i++)
    {
        wq.dequeue();
    }
    
    cout << "peeking in the queue" << endl;
    string it = wq.peek();
    
    if(it != "<EMPTY QUEUE>")
    {
        cout << "Front of the queue: " << it << endl;
    } else {
        cout << it << endl;
    }
    string output = testing::internal::GetCapturedStdout();

    return output;
}
    
    
string test_allQ(string course, string* op, int length)
{
    WaitlistQueue wq(length);
    testing::internal::CaptureStdout();

    int enq = 0;
    for(int i = 0; i < length; i++)
    {
        if(op[i] == "E")
        {
            string c = course + to_string(enq);
            cout << "Enqueue(" << c << ")" << endl;
            wq.enqueue(c);
            enq++;
        }
        else if(op[i] == "D")
        {
            cout << "Dequeue" << endl;
            wq.dequeue();
        }
        else if(op[i] == "P")
        {
            cout << "Peek" << endl;
            string it = wq.peek();
            cout << it << endl;
        }
    }
    string full = wq.isFull() ? "true" : "false";
    cout << "Queue is full? " << full << endl;
    
    string empty = wq.isEmpty() ? "true" : "false";
    cout << "Queue is empty? " << empty << endl;
    
    cout << "Queue size: " << wq.size() << endl;
    cout << "Queue front index: " << wq.getQueueFront() << endl;
    cout << "Queue back index: " << wq.getQueueEnd() << endl;
    
    string output = testing::internal::GetCapturedStdout();
    return output;
}