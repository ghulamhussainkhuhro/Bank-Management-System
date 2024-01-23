#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<iomanip>
using namespace std;

class Bank{
private:
    int total;
    string id;
    struct Person {
        string name, ID, address;
        int contact, cash;
    } person[100];

public:
    Bank(){
        total = 0;
    }

    void choice();
    void perData();
    void show();
    void search();
    void transaction();
    void del();
    void saveDataToFile();
    void loadDataFromFile();
};

int main(){
    
    cout<<setiosflags(ios::right);
    cout<<setfill('*');
    cout<<"\v\v\n";
    cout<<"\t\t\t********************************************\n";
    cout<<"\t\t\t*         Bank Management System           *\n";
    cout<<"\t\t\t********************************************\n";
    cout<<"\t\t\t*Name : Ghulam Hussain Khuhro              *\n";
    cout<<"\t\t\t********************************************\n";
    cout<<"\t\t\t*Roll number : 23sw050                     *\n";
    cout<<"\t\t\t********************************************\n";
    cout<<"\t\t\t*Project Instructor : Sir Sajjad Ali       *\n";
    cout<<"\t\t\t********************************************\n";

    Bank b;
    b.loadDataFromFile();
    b.choice();

    return 0;
}

void Bank::choice(){
    char ch;
    while (1){
        cout<<"\n\nEnter action you want to perform :"<<endl;
        cout<<"1. Create new account"<<endl;
        cout<<"2. View customer list"<<endl;
        cout<<"3. Check the details of an existing account"<<endl;
        cout<<"4. Perform transactions"<<endl;
        cout<<"5. Delete an existing account"<<endl;
        cout<<"6. Exit"<<endl;

        ch=getch();

        switch(ch) {
        case '1':
            perData();
            saveDataToFile();
            break;
        case '2':
            show();
            break;
        case '3':
            search();
            break;
        case '4':
            transaction();
            saveDataToFile();
            break;
        case '5':
            del();
            saveDataToFile();
            break;
        case '6':
            cout << "Program Ended." << endl;
            exit(0);
        default:
            cout << "Invalid choice!\t\tProgram Ended.";
        }
    }
}

void Bank::perData() {
    cout<<"Enter data of person "<<total+1<<endl;
    cout<<"Enter your name: ";
    cin>>person[total].name;
    cout<<"ID: ";
    cin>>person[total].ID;
    cout<<"Address: ";
    cin>>person[total].address;
    cout<<"Contact: ";
    cin>>person[total].contact;
    cout<<"Total Cash: ";
    cin>>person[total].cash;
    total++;
}

void Bank::show() {
    for(int i = 0; i < total; i++) {
        cout<<"Data of person "<<i+1<<endl;
        cout<<"Name: "<<person[i].name<<endl;
        cout<<"ID: "<<person[i].ID<<endl;
        cout<<"ADDRESS: "<<person[i].address<<endl;
        cout<<"CONTACT: "<<person[i].contact<<endl;
        cout<<"TOTAL CASH "<<person[i].cash<<endl;
    }
}

void Bank::search(){
    cout<<"Enter ID of person you want to search: ";
    cin>>id;
    for(int i = 0; i < total; i++){
        if(id==person[i].ID){
            cout<<"Data of person "<<i+1<<endl;
            cout<<"Name: "<<person[i].name<<endl;
            cout<<"ID: "<<person[i].ID<<endl;
            cout<<"ADDRESS: "<<person[i].address<<endl;
            cout<<"CONTACT: "<<person[i].contact<<endl;
            cout<<"TOTAL CASH: "<<person[i].cash<<endl;
            return;
        }
    }
    cout<<"No such record found."<<endl;
}

void Bank::transaction() {
    int cash;
    char ch;
    cout<<"Enter ID of person for the transaction: ";
    cin>>id;
    for(int i=0; i<total; i++) {
        if(id==person[i].ID) {
            cout<<"Name: "<<person[i].name<<endl;
            cout<<"ADDRESS: "<<person[i].address<<endl;
            cout<<"CONTACT: " <<person[i].contact<<endl;
            cout<<"\nExisting cash: "<<person[i].cash<<endl;
            cout<<"Press 1 to deposit\nPress 2 to withdraw"<<endl;
            ch=getch();
            switch (ch) {
            case '1':
                cout<<"How much cash you want to deposit: ";
                cin>>cash;
                person[i].cash+=cash;
                cout<<"Your new cash after deposit is "<<person[i].cash<<endl;
                return;
            case '2':
                cout<<"How much cash you want to withdraw: ";
                cin>>cash;
                if(cash > person[i].cash){
                    cout<<"Your existing cash is just "<<person[i].cash<<endl;
                    Sleep(3000);
                    return;
                }
                person[i].cash-=cash;
                cout<<"Your new cash after withdrawal is "<<person[i].cash<<endl;
                return;
            default:
                cout<<"Invalid input"<<endl;
                return;
            }
        }
    }
    cout<<"No such record found."<<endl;
}

void Bank::del(){
    char ch;
    cout<<"Press 1 to remove a specific record\nPress 2 to remove all records"<<endl;
    ch=getch();
    switch (ch){
    case '1':
        cout<<"Enter ID of person you want to delete data: ";
        cin>>id;
        for(int i = 0; i < total; i++){
            if(id==person[i].ID){
                for(int j=i; j<total - 1; j++){
                    person[j]=person[j+1];
                }
                total--;
                cout<<"Record deleted successfully!"<<endl;
                return;
            }
        }
        cout<<"No such record found!"<<endl;
        break;
    case '2':
        total=0;
        cout<<"All records deleted successfully!"<<endl;
        break;
    default:
        cout<<"Invalid input"<<endl;
        break;
    }
}

void Bank::saveDataToFile(){
    ofstream outFile("bank_data.txt");
    if (!outFile.is_open()){
        cout<<"Error opening file for writing."<<endl;
        return;
    }
    for (int i = 0;i<total;i++){
        outFile<<person[i].name<<" "
                <<person[i].ID <<" "
                <<person[i].address<<" "
                <<person[i].contact<<" "
                <<person[i].cash<<endl;
    }
    outFile.close();
}

void Bank::loadDataFromFile(){
    ifstream inFile("bank_data.txt");
    if(!inFile.is_open()){
        cout<<"No previous data found."<<endl;
        return;
    }
    while (inFile>>person[total].name
                 >>person[total].ID
                 >>person[total].address
                 >>person[total].contact
                 >>person[total].cash) {
        total++;
    }
    inFile.close();
}

