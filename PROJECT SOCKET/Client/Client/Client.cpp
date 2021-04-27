// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.

// khai bao thu vien
#include "pch.h" 
#include "framework.h"
#include "Client.h"
#include "afxsock.h"
#include <conio.h>
#include <string>
#include "stdlib.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4996) // tranh loi C4996 do dung mot so ham chua chuan

// The one and only application object

CWinApp theApp;

using namespace std;

int showMenu() { // hien thi menu dang ky
    cout << "\t\t\t\t\tMENU\n";
    cout << "1.Login\n";
    cout << "2.Register\n";
    cout << "3.Exit\n";
    int option;
    bool flag = true;
    do {
        if (!flag)
            cout << "Your choice is invalid\n";
        cout << "Enter your choice: ";
        cin >> option;
        if (flag)
            flag = false;
    } while (option < 1 || option > 3);
    return option;
}

int showMenuClient() { // hien thi menu yeu cau server
    cout << "\t\t\t\t\tMENU\n";
    cout << "1.Receive list of city and weather in current day\n";
    cout << "2.Receive list of city and weather in input date\n";
    cout << "3.Receive weather in the city in 1 week\n";
    cout << "4.Exit\n\n";
    int option;
    bool flag = true;
    do {
        if (!flag)
            cout << "Your choice is invalid\n";
        cout << "Enter your choice: ";
        cin >> option;
        if (flag)
            flag = false;
    } while (option < 1 || option > 4);
    return option;
}

int showMenuAdmin() { // hien thi menu admin
    cout << "\t\t\t\t\tMENU\n";
    cout << "1.Add city\n";
    cout << "2.Update weather with input date\n";
    cout << "3.Update weather in 1 week\n";
    cout << "4.Exit\n";
    int option;
    bool flag = true;
    do {
        if (!flag)
            cout << "Your choice is invalid\n";
        cout << "Enter your choice: ";
        cin >> option;
        if (flag)
            flag = false;
    } while (option < 1 || option > 4);
    return option;
}

vector<string> inputUserData() { // nhap username, password
    vector<string> res;
    string username, password;
    cout << "Enter your username: ";
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, password);
    res.push_back(username);
    res.push_back(password);
    return res;
}

void sendData(CSocket& client, vector<string> data) { // gui username, password cho server
    vector<int> size_data;
    size_data.push_back(data[0].size());
    size_data.push_back(data[1].size());
    client.Send(&size_data[0], sizeof(int), 0);
    client.Send(data[0].c_str(), size_data[0], 0);
    client.Send(&size_data[1], sizeof(int), 0);
    client.Send(data[1].c_str(), size_data[1], 0);
}

bool receiveMessage(CSocket& client, char*& message) { // nhan thong bao tu server
    int len;
    int byte = client.Receive(&len, sizeof(int), 0);
    if (byte == SOCKET_ERROR) 
        return false;
    message = new char[len + 1];
    message[len] = '\0';
    client.Receive(message, len, 0);
    return true;
}

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else // code o phan nay
        {
            AfxSocketInit(NULL); // khoi tao Socket
            CSocket client;
            int port;
            char IPAddress[16];
            client.Create(); // tao Socket
            cout << "Enter IP: ";
            gets_s(IPAddress); // nhap IP server
            cout << "Enter port: ";
            cin >> port; // nhap cong server
            cin.ignore(1);
            // chuyen doi dia chi IP tu char* sang const SOCKADDR*
            const char* ip = (const char*)IPAddress;
            wchar_t* wip = new wchar_t[strlen(ip) + 1];
            mbstowcs(wip, ip, strlen(ip) + 1);
            //
            client.Connect(wip, port); // ket noi server
            delete[] wip;
            cout << "Waiting for server!!!\n"; 
            int size;
            bool init;
            int byte = client.Receive(&init, sizeof(bool), 0);
            if (byte == SOCKET_ERROR || !init) {
                cout << "Server disconnected to client!!!\n";
                client.Close();
                return nRetCode;
            }
            byte = client.Receive(&size, sizeof(int), 0); // nhan do dai thong bao yeu cau dang nhap
            if (byte == SOCKET_ERROR) {
                cout << "Server disconnected to client!!!\n";
                client.Close();
                return nRetCode;
            }
            char* notice = new char[size + 1];
            notice[size] = '\0';
            client.Receive(notice, size, 0); // nhan thong bao
            cout << notice << endl;
            cout << "Press any key to continue!!!\n";
            delete[] notice;
            bool admin = false;
            do {
                _getch();
                system("cls");
                int option = showMenu(); // hien thi menu
                client.Send(&option, sizeof(int), 0); // gui lua chon cua client cho server
                _getch();
                system("cls");
                cin.ignore(1);
                if (option == 1) { // yeu cau dang nhap
                    vector<string> data = inputUserData(); // nhap username, password
                    sendData(client, data); // gui username, password
                    char* message = NULL;
                    bool flag = receiveMessage(client, message); // nhan thong bao tu server
                    if (!flag) {
                        cout << "Server disconnected to client!!!\n";
                        client.Close();
                        return nRetCode;
                    }
                    cout << message << endl;
                    client.Receive(&admin, sizeof(bool), 0);
                    if (strcmp(message, "Username or password is incorrect!!!") != 0) { // dang nhap that bai
                        delete[] message;
                        break;
                    }
                    delete[] message;
                }
                else if (option == 2) { // yeu cau dang ky
                    vector<string> data = inputUserData(); // gui username, password
                    sendData(client, data); // gui du lieu cho server
                    char* message = NULL;
                    bool flag = receiveMessage(client, message); // nhan thong bao tu server
                    if (!flag) {
                        cout << "Server disconnected to client!!!\n";
                        client.Close();
                        return nRetCode;
                    }
                    cout << message << endl;
                    if (strcmp(message, "Account has already existed!!!") != 0) { // dang ky that bai
                        delete[] message;
                        break;
                    }
                    delete[] message;
                }
                else { // thoat khoi he thong
                    client.Close();
                    return nRetCode;
                }
            } while (true);
            if (admin) { // truong hop client la admin
                while (true) {
                    _getch();
                    system("cls");
                    int option = showMenuAdmin(); // nhap yeu cau
                    client.Send(&option, sizeof(int), 0); // gui yeu cau
                    if (option == 1) { // yeu cau them thanh pho
                        cin.ignore(1);
                        string city, country;
                        cout << "\nEnter city's name: "; // nhap ten thanh pho
                        getline(cin, city);
                        cout << "Enter country: "; // nhap quoc gia
                        getline(cin, country);
                        int len = city.size(); // gui thong tin vua nhap cho server
                        client.Send(&len, sizeof(int), 0);
                        client.Send(city.c_str(), len, 0);
                        len = country.size();
                        client.Send(&len, sizeof(int), 0);
                        client.Send(country.c_str(), len, 0);
                        byte = client.Receive(&len, sizeof(int), 0); // nhan do dai thong bao tu server
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        char* msg = new char[len + 1];
                        client.Receive(msg, len, 0); // nhan thong bao tu server
                        msg[len] = '\0';
                        cout << endl << msg << endl; 
                        delete[] msg;
                    }
                    else if (option == 2) { // update du lieu theo ngay
                        cin.ignore(1);
                        string date;
                        cout << "\nEnter date (DD/MM/YYYY): "; // nhap ngay
                        getline(cin, date);
                        int len = date.size();
                        client.Send(&len, sizeof(len), 0); // gui do dai ngay
                        client.Send(date.c_str(), len, 0); // gui ngay
                        vector<string> city;
                        byte = client.Receive(&len, sizeof(int), 0);
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        cout << endl;
                        for (int i = 1; i <= len; i++) { // nhan danh sach thanh pho
                            int temp;
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* city_name = new char[temp + 1];
                            client.Receive(city_name, temp, 0);
                            city_name[temp] = '\0';
                            city.push_back(city_name);
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* country = new char[temp + 1];
                            client.Receive(country, temp, 0);
                            country[temp] = '\0';
                            cout << i << ". " << city_name << " - " << country << endl;
                            delete[] city_name;
                            delete[] country;
                        }
                        for (int i = 0; i < city.size(); i++) { // update lai du lieu cac thanh pho trong ngay
                            string weather;
                            int temperature;
                            cout << endl;
                            cout << "City: " << city[i] << endl;
                            cout << "Weather: ";
                            getline(cin, weather);
                            cout << "Temperature: ";
                            cin >> temperature;
                            if (i != city.size() - 1)
                                cin.ignore(1);
                            len = weather.size();
                            client.Send(&len, sizeof(int), 0);
                            client.Send(weather.c_str(), len, 0);
                            client.Send(&temperature, sizeof(int), 0);
                        }
                        cout << "\nUpdate successfully\n";
                    }
                    else if (option == 3) { // update du lieu theo thanh pho trong vong 1 tuan gan nhat
                        cin.ignore(1);
                        int len;
                        cout << endl;
                        byte = client.Receive(&len, sizeof(int), 0); // nhan danh sach thanh pho tu server
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        for (int i = 1; i <= len; i++) {
                            int temp;
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* city_name = new char[temp + 1];
                            client.Receive(city_name, temp, 0);
                            city_name[temp] = '\0';
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* country = new char[temp + 1];
                            client.Receive(country, temp, 0);
                            country[temp] = '\0';
                            cout << i << ". " << city_name << " - " << country << endl;
                            delete[] city_name;
                            delete[] country;
                        }
                        cout << endl;
                        cout << "Enter city which you want to update: "; // nhap ten thanh pho
                        string city;
                        getline(cin, city);
                        len = city.size(); 
                        client.Send(&len, sizeof(int), 0); // gui do dai thanh pho
                        client.Send(city.c_str(), len, 0); // gui thanh pho
                        cout << endl;
                        vector<string> date;
                        for (int i = 0; i < 7; i++) { // nhan danh sach ngay
                            int day, month, year;
                            byte = client.Receive(&day, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            byte = client.Receive(&month, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            byte = client.Receive(&year, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            string temp = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
                            date.push_back(temp);
                        }
                        for (int i = 0; i < 7; i++) { // update du lieu
                            cout << "\nCity: " << city << endl;
                            cout << "Date: " << date[i] << endl;
                            string weather;
                            int temperature;
                            cout << "Weather: ";
                            getline(cin, weather);
                            cout << "Temperature: ";
                            cin >> temperature;
                            if (i != 6)
                                cin.ignore(1);
                            len = weather.size();
                            client.Send(&len, sizeof(int), 0);
                            client.Send(weather.c_str(), len, 0);
                            client.Send(&temperature, sizeof(int), 0);
                        }
                        cout << "\nUpdate successfully!!!";
                    }
                    else { // truong hop admin thoat
                        client.Close();
                        return nRetCode;
                    }
                }
            }
            else {
                while (true) {
                    _getch();
                    system("cls");
                    int option = showMenuClient();  // nhap yeu cau
                    client.Send(&option, sizeof(int), 0); // gui yeu cau cho server
                    if (option == 1) {
                        int len;
                        byte = client.Receive(&len, sizeof(int), 0);
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        for (int i = 1; i <= len; i++) { // nhan danh sach cac thanh pho
                            int temp;
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* city = new char[temp + 1];
                            client.Receive(city, temp, 0);
                            city[temp] = '\0';
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* country = new char[temp + 1];
                            client.Receive(country, temp, 0);
                            country[temp] = '\0';
                            cout << "\n" << i << ". " << city << " - " << country;
                            delete[] city;
                            delete[] country;
                        }
                        cout << endl;
                        int count;
                        byte = client.Receive(&count, sizeof(int), 0); // nhan so luong thong tin thoa yeu cau
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        if (count == 0)
                            cout << "\nDon't have data for this date";
                        else {
                            for (int i = 1; i <= count; i++) { // nhan thong tin thoi tiet theo ngay da nhap
                                byte = client.Receive(&len, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                char* city = new char[len + 1];
                                client.Receive(city, len, 0);
                                city[len] = '\0';
                                string date;
                                int day, month, year;
                                byte = client.Receive(&day, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                byte = client.Receive(&month, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                byte = client.Receive(&year, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
                                byte = client.Receive(&len, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                char* weather = new char[len + 1];
                                client.Receive(weather, len, 0);
                                weather[len] = '\0';
                                byte = client.Receive(&len, sizeof(len), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                cout << "\n" << i << ". " << city << " - " << date << " - " << weather << " - " << len;
                                delete[] city;
                                delete[] weather;
                            }
                            cout << "\n\nReceive data successfully!!!\n";
                        }
                    }
                    else if (option == 2) { // nhap ngay va yeu cau tra ve thong tin thoi tiet ngay do
                        cin.ignore(1);
                        cout << "\nEnter date (DD/MM/YYYY): "; // nhap ngay
                        string date;
                        getline(cin, date);
                        int len = date.size();
                        client.Send(&len, sizeof(int), 0); // gui do dai ngay
                        client.Send(date.c_str(), len, 0); // gui ngay
                        byte = client.Receive(&len, sizeof(int), 0);
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        for (int i = 1; i <= len; i++) { // nhan danh sach cac thanh pho
                            int temp;
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* city = new char[temp + 1];
                            client.Receive(city, temp, 0);
                            city[temp] = '\0';
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* country = new char[temp + 1];
                            client.Receive(country, temp, 0);
                            country[temp] = '\0';
                            cout << "\n" << i << ". " << city << " - " << country;
                            delete[] city;
                            delete[] country;
                        }
                        cout << endl;
                        int count;
                        byte = client.Receive(&count, sizeof(int), 0); // nhan so luong thong tin thoa yeu cau
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        if (count == 0)
                            cout << "\nDon't have data for this date";
                        else {
                            for (int i = 1; i <= count; i++) { // nhan thong tin thoi tiet theo ngay da nhap
                                byte = client.Receive(&len, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                char* city = new char[len + 1];
                                client.Receive(city, len, 0);
                                city[len] = '\0';
                                byte = client.Receive(&len, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                char* weather = new char[len + 1];
                                client.Receive(weather, len, 0);
                                weather[len] = '\0';
                                byte = client.Receive(&len, sizeof(len), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                cout << "\n" << i << ". " << city << " - " << date << " - " << weather << " - " << len;
                                delete[] city;
                                delete[] weather;
                            }
                            cout << "\n\nReceive data successfully!!!\n";
                        }
                    }
                    else if (option == 3) {
                        int len;
                        byte = client.Receive(&len, sizeof(int), 0);
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        for (int i = 1; i <= len; i++) { // nhan danh sach cac thanh pho
                            int temp;
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* city = new char[temp + 1];
                            client.Receive(city, temp, 0);
                            city[temp] = '\0';
                            byte = client.Receive(&temp, sizeof(int), 0);
                            if (byte == SOCKET_ERROR) {
                                cout << "Server disconnected to client!!!\n";
                                client.Close();
                                return nRetCode;
                            }
                            char* country = new char[temp + 1];
                            client.Receive(country, temp, 0);
                            country[temp] = '\0';
                            cout << "\n" << i << ". " << city << " - " << country;
                            delete[] city;
                            delete[] country;
                        }
                        cout << endl;
                        cin.ignore(1);
                        cout << "\nEnter name's city: ";
                        string city;
                        getline(cin, city);
                        len = city.size();
                        client.Send(&len, sizeof(int), 0); // gui do dai thanh pho
                        client.Send(city.c_str(), len, 0); // gui ten thanh pho
                        int count;
                        byte = client.Receive(&count, sizeof(int), 0);
                        if (byte == SOCKET_ERROR) {
                            cout << "Server disconnected to client!!!\n";
                            client.Close();
                            return nRetCode;
                        }
                        if (count == 0) 
                            cout << "\nDon't have data for this city in 1 week";
                        else {
                            cout << endl;
                            for (int i = 1; i <= count; i++) {
                                string date;
                                int day, month, year;
                                byte = client.Receive(&day, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                byte = client.Receive(&month, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                byte = client.Receive(&year, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
                                byte = client.Receive(&len, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                char* status = new char[len + 1];
                                client.Receive(status, len, 0);
                                status[len] = '\0';
                                int temperature;
                                byte = client.Receive(&temperature, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Server disconnected to client!!!\n";
                                    client.Close();
                                    return nRetCode;
                                }
                                cout << city << " - " << date << " - " << status << " - " << temperature << endl;
                                delete[] status;
                            }
                            cout << "\nReceive data successfully!!!\n";
                        }      
                    }
                    else {
                        client.Close();
                        return nRetCode;
                    }
                }
            }
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}