// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.

// khai bao thu vien
#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "afxsock.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <vector>
#include <fstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4996) // tranh loi C4996 do dung mot so ham chua chuan

// The one and only application object

CWinApp theApp;

using namespace std;

struct Account {
    string username;
    string password;
    string type;
}; // kieu du lieu dung de client dang nhap

struct City {
    string name;
    string country;
}; // kieu du lieu thanh pho

struct Date {
    int day;
    int month;
    int year;
}; // kieu du lieu ngay

struct Weather {
    string city;
    Date date;
    string status;
    int temperature;
}; // kieu du lieu thoi tiet

void check_host_name(int hostname) { //This function returns host name for local computer
    if (hostname == -1) {
        perror("gethostname");
        exit(1);
    }
}

void check_host_entry(struct hostent* hostentry) { //find host info from host name
    if (hostentry == NULL) {
        perror("gethostbyname");
        exit(1);
    }
}

void IP_formatter(char* IPbuffer) { //convert IP string to dotted decimal format
    if (NULL == IPbuffer) {
        perror("inet_ntoa");
        exit(1);
    }
}

string getIPAddress() { // chuyen IP thanh string
    char host[256];
    char* IP;
    struct hostent* host_entry;
    int hostname;
    hostname = gethostname(host, sizeof(host)); //find the host name
    check_host_name(hostname);
    host_entry = gethostbyname(host); //find host information
    check_host_entry(host_entry);
    IP = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0])); //Convert into IP string
    return IP;
}

vector<string> split(string haystack, string separator) { // ham tach chuoi thanh cac thanh phan
    vector<string> tokens;
    int start = 0;
    while (true) {
        size_t pos = haystack.find(separator, start);
        if (pos != string::npos) {
            string token = haystack.substr(start, pos - start);
            tokens.push_back(token);
            start = pos + separator.size();
        }
        else {
            string token = haystack.substr(start, haystack.size() - start);
            tokens.push_back(token);
            break;
        }
    }
    return tokens;
}

vector<Account> readUserData(ifstream& fin) { // doc du lieu tu file user
    fin.open("user_account.txt");
    vector<Account> account;
    while (true) {
        string line;
        getline(fin, line);
        if (line.size() == 0)
            break;
        vector<string> tokens = split(line, " | ");
        Account temp;
        temp.username = tokens[0];
        temp.password = tokens[1];
        temp.type = tokens[2];
        account.push_back(temp);
    }
    fin.close();
    return account;
}

vector<City> readCityData(ifstream& fin) { // doc du lieu tu file city
    fin.open("city.txt");
    vector<City> city;
    while (true) {
        string line;
        getline(fin, line);
        if (line.size() == 0)
            break;
        vector<string> tokens = split(line, " | ");
        City temp;
        temp.name = tokens[0];
        temp.country = tokens[1];
        city.push_back(temp);
    }
    fin.close();
    return city;
}

vector<Weather> readWeatherData(ifstream& fin) { // doc du lieu tu file weather
    fin.open("weather.txt");
    vector<Weather> weather;
    while (true) {
        string line;
        getline(fin, line);
        if (line.size() == 0)
            break;
        vector<string> tokens = split(line, " | ");
        Weather temp;
        temp.city = tokens[0];
        vector<string> date = split(tokens[1], "/");
        temp.date.day = stoi(date[0]);
        temp.date.month = stoi(date[1]);
        temp.date.year = stoi(date[2]);
        temp.status = tokens[2];
        temp.temperature = stoi(tokens[3]);
        weather.push_back(temp);
    }
    fin.close();
    return weather;
}

void writeUserData(ofstream& fout, vector<Account> data) { // ghi du lieu ra file user
    fout.open("user_account.txt");
    for (int i = 0; i < data.size(); i++) 
        fout << data[i].username << " | " << data[i].password << " | " << data[i].type << endl;
    fout.close();
}

void writeCityData(ofstream& fout, vector<City> data) { // ghi du lieu ra file city
    fout.open("city.txt");
    for (int i = 0; i < data.size(); i++)
        fout << data[i].name << " | " << data[i].country << endl;
    fout.close();
}

void writeWeatherData(ofstream& fout, vector<Weather> weather) { // ghi du lieu ra file weather
    fout.open("weather.txt");
    for (int i = 0; i < weather.size(); i++)
        fout << weather[i].city << " | " << weather[i].date.day << "/" << weather[i].date.month << "/" << weather[i].date.year << " | " << weather[i].status << " | " << weather[i].temperature << endl;
    fout.close();
}

bool receiveData(char*& username, char*& password, int& size_username, int& size_password, CSocket& client) { // nhan username va password client nhap
    int byte = client.Receive(&size_username, sizeof(int), 0);
    if (byte == SOCKET_ERROR)
        return false;
    username = new char[size_username + 1];
    username[size_username] = '\0';
    client.Receive(username, size_username, 0);
    client.Receive(&size_password, sizeof(int), 0);
    if (byte == SOCKET_ERROR)
        return false;
    password = new char[size_password + 1];
    password[size_password] = '\0';
    client.Receive(password, size_password, 0);
    return true;
}

void sendMessage(CSocket& client, char* msg) { // gui thong bao cho client
    int len = strlen(msg);
    client.Send(&len, sizeof(int), 0);
    client.Send(msg, len, 0);
}

bool isSmaller(Date a, Date b) { // so sanh hai ngay
    if (a.year < b.year)
        return true;
    if (a.year == b.year && a.month < b.month)
        return true;
    if (a.year == b.year && a.month == b.month && a.day < b.day)
        return true;
    return false;
}

void bubbleSort(vector<Weather>& weather) { // sap xep theo thu tu ngay tang dan
    for (int i = 1; i < weather.size(); i++) {
        bool flag = true;
        for (int j = weather.size() - 1; j >= i; j--) {
            if (isSmaller(weather[j].date, weather[j-1].date)) {
                swap(weather[j], weather[j - 1]);
                flag = false;
            }
        }
        if (flag == true)
            break;
    }
}

bool isLeapYear(Date a) { // kiem tra nam nhuan
    return (a.year % 4 == 0 || a.year % 100 == 0 && a.year % 400 != 0);
}

Date getCurrentDate() { // lay thoi gian hien tai
    Date date;
    time_t now = time(0);
    tm* t = localtime(&now);
    date.year = 1900 + t->tm_year;
    date.month = 1 + t->tm_mon;
    date.day = t->tm_mday;
    return date;
}

Date findTomorrow(Date a) { // tim ngay tiep theo
    Date res;
    switch (a.month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10: {
        if (a.day == 31) {
            res.day = 1;
            res.month = a.month + 1;
            res.year = a.year;
        }
        else {
            res.day = a.day + 1;
            res.month = a.month;
            res.year = a.year;
        }
        break;
    }
    case 4:
    case 6:
    case 9:
    case 11: {
        if (a.day == 30) {
            res.day = 1;
            res.month = a.month + 1;
            res.year = a.year;
        }
        else {
            res.day = a.day + 1;
            res.month = a.month;
            res.year = a.year;
        }
        break;
    }
    case 12: {
        if (a.day == 31) {
            res.day = 1;
            res.month = 1;
            res.year = a.year + 1;
        }
        else {
            res.day = a.day + 1;
            res.month = a.month;
            res.year = a.year;
        }
        break;
    }
    case 2: {
        if (a.day == 28) {
            if (isLeapYear(a)) {
                res.day = 29;
                res.month = 2;
                res.year = a.year;
            }
            else {
                res.day = 1;
                res.month = 3;
                res.year = a.year;
            }
        }
        else if (a.day == 29) {
            res.day = 1;
            res.month = 3;
            res.year = a.year;
        }
        else {
            res.day = a.day + 1;
            res.month = a.month;
            res.year = a.year;
        }
    }
    }
    return res;
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
            CSocket* client, server; // server la socket chinh, client la socket giao tiep voi cac client
            int numberClient, port;
            cout << "Enter number of client: ";
            cin >> numberClient; // nhap so luong client
            client = new CSocket[numberClient];
            cout << "Enter port: ";
            cin >> port; // nhap port server
            cin.ignore(1);
            server.Create(port, SOCK_STREAM, NULL); // tao socket server
            server.Bind(port);
            server.Listen(); // bat tin hieu 
            cout << "IP Address: " << getIPAddress() << endl;
            cout << "Port: " << port << endl;
            cout << "Waiting for connection!!!\n";
            for (int i = 0; i < numberClient; i++) {
                server.Accept(client[i]); // chap nhan ket noi tu client
                cout << "Client " << i + 1 << " connect successfully!!!\n";
            }
            int count = 0;
            while (count < numberClient) { // thao tac voi tung client
                cout << "Continue or quit: ";
                string require;
                bool init = true;
                do {
                    getline(cin, require);
                    if (require == "quit") {
                        cout << "Server disconnected to all clients!!!\n";
                        init = false;
                        for (int i = count; i < numberClient; i++) {
                            client[i].Send(&init, sizeof(bool), 0);
                            client[i].Close();
                        }
                        server.Close();
                        delete[] client;
                        return nRetCode;
                    }
                } while (require != "continue" && require != "quit");
                client[count].Send(&init, sizeof(bool), 0);
                char notice[] = "Please login to server!!!";
                int size = strlen(notice);
                client[count].Send(&size, sizeof(int), 0); // gui do dai thong bao cho client
                client[count].Send(notice, size, 0); // gui thong bao yeu cau dang nhap
                bool flag = true;
                bool admin = false; // bien kiem tra xem phai admin khong
                do {
                    int option;
                    client[count].Receive(&option, sizeof(int), 0); // nhan yeu cau tu client (1: dang nhap, 2: dang ky, 3: thoat)
                    ifstream fin;
                    ofstream fout;
                    vector<Account> account = readUserData(fin); // doc danh sach client trong file txt
                    char* password = NULL,* username = NULL;
                    int size_username, size_password;
                    if (option == 1) { // kiem tra dang nhap
                        bool check = true;
                        bool test = receiveData(username, password, size_username, size_password, client[count]); // nhan username, password tu client
                        if (!test) {
                            cout << "Client " << count + 1 << " disconnected to server!!!\n";
                            flag = false;
                            client[count].Close();
                            break;
                        }
                        Account data;
                        data.username = username;
                        data.password = password;
                        for (int i = 0; i < account.size(); i++) { // kiem tra xem account co ton tai?
                            if (account[i].username == data.username && account[i].password == data.password) {
                                if (account[i].type == "user")
                                    cout << "Client " << count + 1 << " login successfully!!!\n";
                                else {
                                    cout << "Admin login successfully!!!\n";
                                    admin = true;
                                }
                                char msg[] = "Login successfully";
                                sendMessage(client[count], msg); // neu kiem tra co thu gui thong bao thanh cong cho client
                                client[count].Send(&admin, sizeof(bool), 0);
                                check = false;
                                break;
                            }
                        }
                        if (check) { // neu kiem tra khong ton tai tai khoan thi gui thong bao cho client
                            char msg[] = "Username or password is incorrect!!!";
                            sendMessage(client[count], msg);
                            client[count].Send(&admin, sizeof(bool), 0);
                        }
                        delete[] username;
                        delete[] password;
                        if (!check) // dang nhap thanh cong thi thoat qua trinh kiem tra cua server
                            break;
                    }
                    else if (option == 2) { // kiem tra dang ky
                        bool check = true;
                        bool test = receiveData(username, password, size_username, size_password, client[count]); // nhan username, password nhap tu client
                        if (!test) {
                            cout << "Client " << count + 1 << " disconnected to server!!!\n";
                            flag = false;
                            client[count].Close();
                            break;
                        }
                        Account data;
                        data.username = username;
                        data.password = password;
                        data.type = "user";
                        for (int i = 0; i < account.size(); i++) { // kiem tra xem tai khoan ton tai hay chua
                            if (account[i].username == data.username) { 
                                char msg[] = "Account has already existed!!!";
                                sendMessage(client[count], msg); // gui thong bao tai khoan ton tai
                                check = false;
                                break;
                            }
                        }
                        if (check) { // neu tai khoan chua ton tai thi dang ky thanh cong
                            cout << "Client " << count + 1 << " create account successfully!!!\n";
                            char msg[] = "Account is created successfully!!!";
                            sendMessage(client[count], msg); // gui thong bao cho client
                            account.push_back(data);
                            writeUserData(fout, account); // ghi thong tin tai khoan vao file txt
                        }
                        delete[] username;
                        delete[] password;
                        if (check)
                            break;
                    }
                    else { // client ngat ket noi
                        cout << "Client " << count + 1 << " disconnected to server!!!\n";
                        flag = false;
                        client[count].Close();
                        break;
                    }
                } while (true);
                if (flag) {
                    if (admin) { // truong hop nguoi dung la admin
                        while (true) {
                            bool check = true;
                            int option;
                            int byte = client[count].Receive(&option, sizeof(int), 0); // nhan yeu cau cua admin
                            if (byte == SOCKET_ERROR) {
                                cout << "Admin disconnected to server\n";
                                check = false;
                                client[count].Close();
                                break;
                            }
                            switch (option) {
                            case 1: { // yeu cau them thanh pho
                                ifstream fin;
                                ofstream fout;
                                vector<City> city = readCityData(fin); // doc file city
                                City temp;
                                int len;
                                int byte = client[count].Receive(&len, sizeof(int), 0); // nhan do dai ten thanh pho them vao
                                if (byte == SOCKET_ERROR) {
                                    cout << "Admin disconnected to server!!!\n";
                                    client[count].Close();
                                    check = false;
                                    break;
                                }
                                char* city_name = new char[len + 1];
                                client[count].Receive(city_name, len, 0); // nhan ten thanh pho them vao
                                city_name[len] = '\0';
                                byte = client[count].Receive(&len, sizeof(int), 0); // nhan do dai quoc gia
                                if (byte == SOCKET_ERROR) {
                                    cout << "Admin disconnected to server!!!\n";
                                    client[count].Close();
                                    check = false;
                                    break;
                                }
                                char* country = new char[len + 1];
                                client[count].Receive(country, len, 0); // nhan ten quoc gia cua thanh pho do
                                country[len] = '\0';
                                temp.name = city_name;
                                temp.country = country;
                                bool flag = true;
                                for (int i = 0; i < city.size(); i++) {
                                    if (strcmp(city_name, city[i].name.c_str()) == 0 && strcmp(country, city[i].country.c_str()) == 0) { // truong hop thanh pho da co o server
                                        char msg[] = "City has already existed in server";
                                        sendMessage(client[count], msg);
                                        flag = false;
                                    }
                                }
                                if (flag) { // truong hop thanh pho chua co trong server
                                    cout << "Admin adds city successfully\n";
                                    char msg[] = "Add successfully";
                                    sendMessage(client[count], msg);
                                    city.push_back(temp);
                                    writeCityData(fout, city);
                                }
                                delete[] city_name;
                                delete[] country;
                                break;
                            }
                            case 2: { // update theo ngay
                                ifstream fin;
                                ofstream fout;
                                vector<City> city = readCityData(fin); // doc file city
                                vector<Weather> weather = readWeatherData(fin); // doc file weather
                                int len;
                                int byte = client[count].Receive(&len, sizeof(int), 0); // nhan do dai ngay admin nhap
                                if (byte == SOCKET_ERROR) {
                                    cout << "Admin disconnected to server!!!\n";
                                    client[count].Close();
                                    check = false;
                                    break;
                                }
                                char* temp = new char[len + 1];
                                client[count].Receive(temp, len, 0); // nhan ngay admin nhap
                                temp[len] = '\0';
                                string input = temp;
                                delete[] temp;
                                vector<string> tokens = split(input, "/"); // tach string thanh date
                                Date date; 
                                date.day = stoi(tokens[0]);
                                date.month = stoi(tokens[1]);
                                date.year = stoi(tokens[2]);
                                vector<int> res;
                                for (int i = 0; i < weather.size(); i++) { // luu cac thong tin cap nhat da xuat hien trong file weather
                                    if (date.day == weather[i].date.day && date.month == weather[i].date.month && date.year == weather[i].date.year)
                                        res.push_back(i);
                                }
                                len = city.size();
                                client[count].Send(&len, sizeof(int), 0);
                                for (int i = 0; i < city.size(); i++) { // gui danh sach thanh pho cho admin
                                    len = city[i].name.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].name.c_str(), len, 0);
                                    len = city[i].country.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].country.c_str(), len, 0);
                                }
                                for (int i = 0; i < city.size(); i++) { // cap nhat cho tung thanh pho
                                    bool flag = true;
                                    for (int j = 0; j < res.size(); j++) {
                                        if (city[i].name == weather[res[j]].city) { // cap nhat du lieu trong file weather
                                            byte = client[count].Receive(&len, sizeof(len));
                                            if (byte == SOCKET_ERROR) {
                                                cout << "Admin disconnected to server!!!\n";
                                                client[count].Close();
                                                check = false;
                                                break;
                                            }
                                            char* status = new char[len + 1];
                                            client[count].Receive(status, len, 0);
                                            status[len] = '\0';
                                            byte = client[count].Receive(&weather[res[j]].temperature, sizeof(int), 0);
                                            if (byte == SOCKET_ERROR) {
                                                cout << "Admin disconnected to server!!!\n";
                                                client[count].Close();
                                                check = false;
                                                break;
                                            }
                                            weather[res[j]].status = status;
                                            delete[] status;
                                            flag = false;
                                            break;
                                        }
                                    }
                                    if (!check)
                                        break;
                                    if (flag) { // them du lieu vao file weather
                                        Weather temp;
                                        byte = client[count].Receive(&len, sizeof(int), 0);
                                        if (byte == SOCKET_ERROR) {
                                            cout << "Admin disconnected to server!!!\n";
                                            client[count].Close();
                                            check = false;
                                            break;
                                        }
                                        char* status = new char[len + 1];
                                        client[count].Receive(status, len, 0);
                                        status[len] = '\0';
                                        temp.city = city[i].name;
                                        temp.date.day = date.day;
                                        temp.date.month = date.month;
                                        temp.date.year = date.year;
                                        temp.status = status;
                                        byte = client[count].Receive(&temp.temperature, sizeof(int), 0);
                                        if (byte == SOCKET_ERROR) {
                                            cout << "Admin disconnected to server!!!\n";
                                            client[count].Close();
                                            check = false;
                                            break;
                                        }
                                        weather.push_back(temp);
                                        delete[] status;
                                    }
                                }
                                if (!check)
                                    break;
                                bubbleSort(weather); // sap xep lai du lieu
                                writeWeatherData(fout, weather); // ghi vao file
                                cout << "Admin updates data in " << input << " successfully!!!\n";
                                break;
                            }
                            case 3: { // cap nhat du lieu cua mot thanh pho trong vong mot tuan
                                ifstream fin;
                                ofstream fout;
                                vector<City> city = readCityData(fin); // doc file city
                                vector<Weather> weather = readWeatherData(fin); // doc file weather
                                int len = city.size();
                                client[count].Send(&len, sizeof(int), 0); 
                                for (int i = 0; i < city.size(); i++) { // gui danh sach thanh pho
                                    len = city[i].name.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].name.c_str(), len, 0);
                                    len = city[i].country.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].country.c_str(), len, 0);
                                }
                                int byte = client[count].Receive(&len, sizeof(int), 0); // nhan do dai thanh pho admin nhap
                                if (byte == SOCKET_ERROR) {
                                    cout << "Admin disconnected to server!!!\n";
                                    client[count].Close();
                                    check = false;
                                    break;
                                }
                                char* city_name = new char[len + 1];
                                client[count].Receive(city_name, len, 0); // nhan thanh pho admin nhap
                                city_name[len] = '\0';
                                Date current = getCurrentDate(); // lay ngay hien tai
                                vector<Date> date;
                                date.push_back(current);
                                for (int i = 0; i < 6; i++) { // luu danh sach 7 ngay vao vector
                                    Date temp = findTomorrow(date[i]);
                                    date.push_back(temp);
                                }
                                vector<int> pos;
                                for (int i = 0; i < weather.size(); i++) { // luu thong tin cac vi tri da co trong file
                                    if (strcmp(weather[i].city.c_str(), city_name) == 0) {
                                        for (int j = 0; j < 7; j++) {
                                            if (date[j].day == weather[i].date.day && date[j].month == weather[i].date.month && date[j].year == weather[i].date.year)
                                                pos.push_back(i);
                                        }
                                    }
                                }
                                for (int i = 0; i < date.size(); i++) { // gui danh sach ngay cho admin
                                    client[count].Send(&date[i].day, sizeof(int), 0);
                                    client[count].Send(&date[i].month, sizeof(int), 0);
                                    client[count].Send(&date[i].year, sizeof(int), 0);
                                }
                                int j = 0;
                                for (int i = 0; i < 7; i++) {
                                    if (j < pos.size()) { // truong hop vector vi tri van chua duyet het
                                        if (date[i].day == weather[pos[j]].date.day && date[i].month == weather[pos[j]].date.month && date[i].year == weather[pos[j]].date.year) { // truong hop cap nhat du lieu trong file
                                            byte = client[count].Receive(&len, sizeof(int), 0);
                                            if (byte == SOCKET_ERROR) {
                                                cout << "Admin disconnected to server!!!\n";
                                                client[count].Close();
                                                check = false;
                                                break;
                                            }
                                            char* status = new char[len + 1];
                                            client[count].Receive(status, len, 0);
                                            status[len] = '\0';
                                            weather[pos[j]].status = status;
                                            byte = client[count].Receive(&weather[pos[j]].temperature, sizeof(int), 0);
                                            if (byte == SOCKET_ERROR) {
                                                cout << "Admin disconnected to server!!!\n";
                                                client[count].Close();
                                                check = false;
                                                break;
                                            }
                                            delete[] status;
                                            j++;
                                        }
                                        else { // truong hop them vao file
                                            Weather temp;
                                            temp.city = city_name;
                                            temp.date = date[i];
                                            byte = client[count].Receive(&len, sizeof(int), 0);
                                            if (byte == SOCKET_ERROR) {
                                                cout << "Admin disconnected to server!!!\n";
                                                client[count].Close();
                                                check = false;
                                                break;
                                            }
                                            char* status = new char[len + 1];
                                            client[count].Receive(status, len, 0);
                                            status[len] = '\0';
                                            temp.status = status;
                                            byte = client[count].Receive(&temp.temperature, sizeof(int), 0);
                                            if (byte == SOCKET_ERROR) {
                                                cout << "Admin disconnected to server!!!\n";
                                                client[count].Close();
                                                check = false;
                                                break;
                                            }
                                            weather.push_back(temp);
                                            delete[] status;
                                        }
                                    }
                                    else { // truong hop duyet het vector thi chi can them vao file
                                        Weather temp;
                                        temp.city = city_name;
                                        temp.date = date[i];
                                        byte = client[count].Receive(&len, sizeof(int), 0);
                                        if (byte == SOCKET_ERROR) {
                                            cout << "Admin disconnected to server!!!\n";
                                            client[count].Close();
                                            check = false;
                                            break;
                                        }
                                        char* status = new char[len + 1];
                                        client[count].Receive(status, len, 0);
                                        status[len] = '\0';
                                        temp.status = status;
                                        byte = client[count].Receive(&temp.temperature, sizeof(int), 0);
                                        if (byte == SOCKET_ERROR) {
                                            cout << "Admin disconnected to server!!!\n";
                                            client[count].Close();
                                            check = false;
                                            break;
                                        }
                                        weather.push_back(temp);
                                        delete[] status;
                                    }
                                }
                                if (!check)
                                    break;
                                bubbleSort(weather); // sap xep lai du lieu
                                writeWeatherData(fout, weather); // ghi vao file
                                cout << "Admin updates data " << city_name << " city in 1 week successfully!!!\n";
                                delete[] city_name;
                                break;
                            }
                            default: { // admin yeu cau thoat
                                cout << "Admin disconnected to server!!!\n";
                                client[count].Close();
                                check = false;
                            }
                            }
                            if (!check)
                                break;
                        }
                    }
                    else { // truong hop khong la admin
                        while (true) {
                            bool check = true;
                            int option;
                            int byte = client[count].Receive(&option, sizeof(int), 0); // nhan yeu cau tu client
                            if (byte == SOCKET_ERROR) {
                                cout << "Client " << count + 1 << " disconnected to server!!!\n";
                                check = false;
                                client[count].Close();
                                break;
                            }
                            switch (option) {
                            case 1: {
                                int len;
                                ifstream fin;
                                Date date = getCurrentDate();
                                vector<Weather> weather = readWeatherData(fin); // doc file weather
                                vector<City> city = readCityData(fin); // doc file city
                                len = city.size();
                                client[count].Send(&len, sizeof(int), 0); // gui so luong city
                                for (int i = 0; i < city.size(); i++) { // gui danh sach city cho client
                                    len = city[i].name.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].name.c_str(), len, 0);
                                    len = city[i].country.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].country.c_str(), len, 0);
                                }
                                vector<Weather> ans;
                                for (int i = 0; i < weather.size(); i++) { // tim thong tin theo ngay yeu cau
                                    if (weather[i].date.day == date.day && weather[i].date.month == date.month && weather[i].date.year == date.year)
                                        ans.push_back(weather[i]);
                                }
                                len = ans.size();
                                client[count].Send(&len, sizeof(int), 0); // gui so luong thanh pho dat yeu cau
                                if (len == 0) {
                                    cout << "Print list of city and weather on " << date.day << "/" << date.month << "/" << date.year << " for client " << count + 1 << " successfully!!!\n";
                                    break;
                                }
                                for (int i = 0; i < ans.size(); i++) { // gui danh sach thoi tiet theo ngay yeu cau
                                    len = ans[i].city.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(ans[i].city.c_str(), len, 0);
                                    client[count].Send(&date.day, sizeof(int), 0);
                                    client[count].Send(&date.month, sizeof(int), 0);
                                    client[count].Send(&date.year, sizeof(int), 0);
                                    len = ans[i].status.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(ans[i].status.c_str(), len, 0);
                                    len = ans[i].temperature;
                                    client[count].Send(&len, sizeof(int), 0);
                                }
                                cout << "Print list of city and weather on " << date.day << "/" << date.month << "/" << date.year << " for client " << count + 1 << " successfully!!!\n";
                                break;
                            }
                            case 2: { // doc du lieu file city va tra ve thong tin thoi tiet theo ngay yeu cau cua client
                                int len;
                                ifstream fin;
                                int byte = client[count].Receive(&len, sizeof(int), 0); // nhan do dai ngay client yeu cau
                                if (byte == SOCKET_ERROR) {
                                    cout << "Client " << count + 1 << " disconnected to server!!!\n";
                                    check = false;
                                    client[count].Close();
                                    break;
                                }
                                char* temp = new char[len + 1];
                                client[count].Receive(temp, len, 0); // nhan ngay client yeu cau
                                temp[len] = '\0';
                                string input = temp;
                                vector<string> tokens = split(input, "/");
                                delete[] temp;
                                Date date;
                                date.day = stoi(tokens[0]);
                                date.month = stoi(tokens[1]);
                                date.year = stoi(tokens[2]);
                                vector<Weather> weather = readWeatherData(fin); // doc file weather
                                vector<City> city = readCityData(fin); // doc file city
                                len = city.size();
                                client[count].Send(&len, sizeof(int), 0); // gui so luong city
                                for (int i = 0; i < city.size(); i++) { // gui danh sach city cho client
                                    len = city[i].name.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].name.c_str(), len, 0);
                                    len = city[i].country.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].country.c_str(), len, 0);
                                }
                                vector<Weather> ans;
                                for (int i = 0; i < weather.size(); i++) { // tim thong tin theo ngay yeu cau
                                    if (weather[i].date.day == date.day && weather[i].date.month == date.month && weather[i].date.year == date.year)
                                        ans.push_back(weather[i]);
                                }
                                len = ans.size();
                                client[count].Send(&len, sizeof(int), 0); // gui so luong thanh pho dat yeu cau
                                if (len == 0) {
                                    cout << "Print list of city and weather on " << input << " for client " << count + 1 << " successfully!!!" << endl;
                                    break;
                                }
                                for (int i = 0; i < ans.size(); i++) { // gui danh sach thoi tiet theo ngay yeu cau
                                    len = ans[i].city.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(ans[i].city.c_str(), len, 0);
                                    len = ans[i].status.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(ans[i].status.c_str(), len, 0);
                                    len = ans[i].temperature;
                                    client[count].Send(&len, sizeof(int), 0);
                                }
                                cout << "Print list of city and weather on " << input << " for client " << count + 1 << " successfully!!!" << endl;
                                break;
                            }
                            case 3: {
                                ifstream fin;
                                vector<City> city = readCityData(fin); // doc file city
                                vector<Weather> weather = readWeatherData(fin); // doc file weather
                                int len = city.size();
                                client[count].Send(&len, sizeof(int), 0); // gui so luong city
                                for (int i = 0; i < city.size(); i++) { // gui danh sach city cho client
                                    len = city[i].name.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].name.c_str(), len, 0);
                                    len = city[i].country.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(city[i].country.c_str(), len, 0);
                                }
                                int byte = client[count].Receive(&len, sizeof(int), 0);
                                if (byte == SOCKET_ERROR) {
                                    cout << "Client " << count + 1 << " disconnected to server!!!\n";
                                    check = false;
                                    client[count].Close();
                                    break;
                                }
                                char* city_name = new char[len + 1];
                                client[count].Receive(city_name, len, 0);
                                city_name[len] = '\0';
                                Date temp = getCurrentDate();
                                vector<Date> date;
                                date.push_back(temp);
                                for (int i = 0; i < 6; i++) {
                                    temp = findTomorrow(date[i]);
                                    date.push_back(temp);
                                }
                                vector<Weather> res;
                                for (int i = 0; i < weather.size(); i++) {
                                    if (strcmp(city_name, weather[i].city.c_str()) == 0) {
                                        for (int j = 0; j < 7; j++) {
                                            if (date[j].day == weather[i].date.day && date[j].month == weather[i].date.month && date[j].year == weather[i].date.year)
                                                res.push_back(weather[i]);
                                        }
                                    }
                                }
                                len = res.size();
                                client[count].Send(&len, sizeof(int), 0);
                                if (len == 0) {
                                    cout << "Print weather of " << city_name << " in 1 week successfully" << endl;
                                    break;
                                }
                                for (int i = 0; i < res.size(); i++) { // gui danh sach thoi tiet theo ngay yeu cau
                                    client[count].Send(&res[i].date.day, sizeof(int), 0);
                                    client[count].Send(&res[i].date.month, sizeof(int), 0);
                                    client[count].Send(&res[i].date.year, sizeof(int), 0);
                                    len = res[i].status.size();
                                    client[count].Send(&len, sizeof(int), 0);
                                    client[count].Send(res[i].status.c_str(), len, 0);
                                    client[count].Send(&res[i].temperature, sizeof(int), 0);
                                }
                                cout << "Print weather of " << city_name << " in 1 week successfully" << endl;
                                delete[] city_name;
                                break;
                            }
                            default: { // client yeu cau exit
                                cout << "Client " << count + 1 << " disconnected to server\n";
                                client[count].Close();
                                check = false;
                            }
                            }
                            if (!check)
                                break;
                        }
                    }
                }
                count++;
            }
            server.Close();
            delete[] client;
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