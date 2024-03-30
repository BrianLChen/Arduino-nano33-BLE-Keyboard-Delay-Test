#include <iostream>
#include "SerialPort.hpp"
#include <stdio.h>
// #include <string.h>
#include <cstring>
#include <chrono>
#include <string>//字符串操作需要
#include <conio.h>//_kbhit()需要


using namespace std;

char* portName = "\\\\.\\COM7";
string arduino_port = "\\\\.\\COM7";

#define MAX_DATA_LENGTH 255

char incomingData[MAX_DATA_LENGTH];

//Control signals for turning on and turning off the led
//Check arduino code
char ledON[] = "ON\n";
char ledOFF[] = "OFF\n";

//Arduino SerialPort object
SerialPort *arduino;

//Blinking Delay
const unsigned int BLINKING_DELAY = 1000;

//If you want to send data then define "SEND" else comment it out
#define SEND

// void exampleReceiveData(void)
// {
//     int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
//     printf("%s", incomingData);
//     Sleep(10);
// }

// void exampleWriteData(unsigned int delayTime)
// {
//     arduino->writeSerialPort(ledON, MAX_DATA_LENGTH);
//     Sleep(delayTime);
//     arduino->writeSerialPort(ledOFF, MAX_DATA_LENGTH);
//     Sleep(delayTime);
// }

// void autoConnect(void)
// {
//     //better than recusion
//     //avoid stack overflows
//     while(1) {
//         // ui - searching
//         std::cout << "Searching in progress";
//         // wait connection
//         while (!arduino->isConnected()) {
//             Sleep(100);
//             std::cout << ".";
//             // arduino = new SerialPort(portName);
//         }

//         //Checking if arduino is connected or not
//         if (arduino->isConnected()) {
//             std::cout  << std::endl << "Connection established at port " << portName << std::endl;
//         }

//         #ifdef SEND
//             while(arduino->isConnected()) exampleWriteData(BLINKING_DELAY);
//         #else // SEND
//             while(arduino->isConnected()) exampleReceiveData();
//         #endif // SEND
//     }
// }

bool key_check()
{
    while(1)
    {
        if (_kbhit())//非阻塞获取用户输入
		{
			char cTake = _getche();//获取输入字符,并回显		
			if (cTake == 'a' || cTake == 'A')
			{
                return true;
				cout << "button \" q \" pressed " << endl;
				
			}
		}
    }
        return false;
}

int main()
{
    // arduino = new SerialPort(portName);
    SerialPort keyboard_test(portName);
    if(keyboard_test.isConnected())
    {
        cout << "串口连接成功" << endl;
    }
    else
    {
        cout << "串口连接失败" << endl;
        return 0;
    }

    // keyboard_test.writeSerialPort("1", MAX_DATA_LENGTH);
    // keyboard_test.readSerialPort(incomingData,MAX_DATA_LENGTH);
    // cout << incomingData << endl;

    // while (1)
    // {
    // keyboard_test.writeSerialPort("1", MAX_DATA_LENGTH);
    // Sleep(1000);
    // keyboard_test.writeSerialPort("0", MAX_DATA_LENGTH);
    // Sleep(1000);        
    // }
    double duration1[10], duration2[10];
    chrono::_V2::system_clock::time_point start_time, end_time;
    
    for(int i = 0; i < 10; i++)
    {
        cout << "------ Test1 " << i+1 << " start. ------" << endl;
        start_time = std::chrono::system_clock::now();
        keyboard_test.writeSerialPort("1", 16);
        key_check();
        end_time = chrono::system_clock::now();
        auto delay = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        duration1[i] = double(delay.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den;
        cout << "------ Test1 " << i+1 << " finished, " << 10-i-1 << " remains ------" << endl;
        cout << "Delay = " << duration1[i] << endl;
        Sleep(1000);
    }

    for(int i = 0; i < 10; i++)
    {
        cout << "------ Test2 " << i+1 << " start. ------" << endl;
        keyboard_test.writeSerialPort("1", 16);
        start_time = std::chrono::system_clock::now();
        key_check();
        end_time = chrono::system_clock::now();
        auto delay = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        duration2[i] = double(delay.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den;
        cout << "------ Test2 " << i+1 << " finished, " << 10-i-1 << " remains ------" << endl;
        cout << "Delay = " << duration2[i] << endl;

        Sleep(1000);
    }

    double sum = 0;
    for(int i = 0; i < 10; i++)
    {
        sum += duration1[i];
        sum += duration2[i];
    }

    cout << "Delay of the keyboard is " << sum/20 << endl;

    system("pause");

    return 0;
    // autoConnect();   
}