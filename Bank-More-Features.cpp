#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>


using namespace std;

void MenueScreen();
void GoBackToMenu();
void GoBackTrancactionScreen();
void TransactionsMenuScreen();

const string FileName = "Client.txt";
string Delemeter = "#//#";

enum enClientList { CList = 1, AddNewC = 2, DelC = 3, UpDateC = 4, FindC = 5, Transaction = 6, Exit = 7 };
enum enTransactionList { eDeposit = 1, eWithdraw = 2, eTotalBalnces = 3, eMainMenu = 4 };
struct stClient
{
    string AccountNumber = "";
    string PINCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool IsDeleted = false;


};
void ClearScreen()
{
    system("cls");
}
string ReadAccountNumber()
{
    string Acc = "";
    cout << "Enter your Account Number ?: ";
    cin >> Acc;
    return Acc;
}
vector< string> SpliteString(string st, string Delemeter)
{
    vector <string> vString;
    string word = "";
    int pos = 0;
    while ((pos = st.find(Delemeter)) != string::npos)
    {
        word = st.substr(0, pos);
        if (word != "")
        {
            vString.push_back(word);
        }
        st.erase(0, pos + Delemeter.length());
    }
    if (st != "")
    {
        vString.push_back(st);
    }

    return vString;
}
stClient ConverLineToRecord(string Line, string Delemeter)
{
    stClient Client;
    vector <string> vString = SpliteString(Line, Delemeter);
    Client.AccountNumber = vString[0];
    Client.PINCode = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = stod(vString[4]);

    return Client;

}
vector<stClient> ReadDataFromFile()
{
    vector<stClient> vClient;

    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        stClient Client;
        string Line;
        while (getline(MyFile, Line))
        {
            Client = ConverLineToRecord(Line, Delemeter);
            if (Client.IsDeleted == false)
            {
                Client = ConverLineToRecord(Line, Delemeter);
                vClient.push_back(Client);
            }

        }
        MyFile.close();
    }

    return vClient;

}
vector<stClient> SaveClientData(vector<stClient> &vClient)
{
    

    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        stClient Client;
        string Line;
        while (getline(MyFile, Line))
        {
            Client = ConverLineToRecord(Line, Delemeter);
            if (Client.IsDeleted == false)
            {
                Client = ConverLineToRecord(Line, Delemeter);
                vClient.push_back(Client);
            }

        }
        MyFile.close();
    }

    return vClient;

}
bool IsAccountExistByAccountNumber(string AccNum)
{
    vector<stClient> vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        stClient Client;
        string Line;
        while (getline(MyFile, Line))
        {
            Client = ConverLineToRecord(Line, Delemeter);

            if (Client.AccountNumber == AccNum)
            {
                MyFile.close();
                return true;
            }
            vClient.push_back(Client);
        }
        MyFile.close();

    }

    return false;
}
bool MarkDeletedAccount(vector<stClient>& vClient, string AccNum)
{

    for (stClient& Acc : vClient)
    {
        if (AccNum == Acc.AccountNumber)
        {
            Acc.IsDeleted = true;
            return true;
        }

    }
    return false;
}
bool FindClientByAccountNumber(vector <stClient> vClient, string& num, stClient& Client)
{

    for (stClient& Data : vClient)
    {
        if (Data.AccountNumber == num)
        {
            Client = Data;
            return true;
        }

    }
    return false;
}
stClient GetClientInfo()
{

    stClient Client;
    cout << "Enter your Account Number : ";
    getline(cin >> ws, Client.AccountNumber);
    while (IsAccountExistByAccountNumber(Client.AccountNumber))
    {
        cout << "The Client with Account Number [" << Client.AccountNumber << "] is already exist Enter another Account number";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter your PIN Code : ";
    getline(cin, Client.PINCode);
    cout << "Enter your Name : ";
    getline(cin, Client.Name);
    cout << "Enter your Phone ";
    getline(cin, Client.Phone);
    cout << "Enter your Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}
stClient ChangeClientRecord(string AccNum)
{
    stClient Client;
    Client.AccountNumber = AccNum;

    cout << "Enter your PIN Code : ";
    getline(cin >> ws, Client.PINCode);
    cout << "Enter your Name : ";
    getline(cin, Client.Name);
    cout << "Enter your Phone ";
    getline(cin, Client.Phone);
    cout << "Enter your Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}
string ClientFromRecordToLine(stClient Client, string Delemeter = "#//#")
{
    string Line = "";
    Line = Client.AccountNumber + Delemeter;
    Line += Client.PINCode + Delemeter;
    Line += Client.Name + Delemeter;
    Line += Client.Phone + Delemeter;
    Line += to_string(Client.AccountBalance);

    return Line;
}
void AddClientToFile(string Data, string FileName)
{


    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << Data << endl;

        MyFile.close();

    }


}
void PrintClientInfo(stClient Client)
{

    cout << "|" << setw(15) << left << Client.AccountNumber
        << " |" << setw(10) << left << Client.PINCode
        << " |" << setw(25) << left << Client.Name
        << " |" << setw(10) << left << Client.Phone
        << " |" << setw(10) << left << Client.AccountBalance << endl;

    cout << "\n____________________________________________________________________________________\n";

}
void ClientList()
{
    vector<stClient> vClient = ReadDataFromFile();
    cout << "                           Client List  (" << vClient.size() << ") Client(s)                       \n";
    cout << "____________________________________________________________________________________\n\n";
    cout << "|" << setw(15) << left << " Account Number"
        << " |" << setw(10) << left << " PIN code"
        << " |" << setw(25) << left << " Client Name"
        << " |" << setw(10) << left << " Phone"
        << " |" << setw(10) << left << " Balance" << endl;
    cout << "____________________________________________________________________________________\n";


    for (stClient& Client : vClient)
    {
        PrintClientInfo(Client);
        cout << endl;
    }


}
void AddClient()
{

    stClient Data = GetClientInfo();
    AddClientToFile(ClientFromRecordToLine(Data), FileName);
}
void AddClients()
{
    char	AddNewClient = 'y';
    do {
        system("cls");
        cout << "Add New Client :\n\n";

        AddClient();
        cout << "\nClient Added Seccussfully , Do you want to add new client? :";
        cin >> AddNewClient;
    } while (tolower(AddNewClient) == 'y');
}

void AddNewClientScreen()
{
    vector<stClient> vClient = ReadDataFromFile();


    stClient Client;
    cout << "=============================\n";
    cout << "   Add New Client Screen\n";
    cout << "=============================\n";
    cout << "Adding New Client :\n\n";

    AddClients();




}
void PrintClientRecord(stClient& Client)
{
    cout << "The following are the client deatils :\n";
    cout << "_______________________________________\n";

    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "PIN code        : " << Client.PINCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;


    cout << "_______________________________________\n";

}
void AddClientToFile(vector<stClient>& vClient, string FileName)
{

    string Line = "";
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (stClient& Client : vClient)
        {
            if (Client.IsDeleted == false)
            {
                Line = ClientFromRecordToLine(Client);
                MyFile << Line << endl;
            }

        }


        MyFile.close();

    }


}
vector<stClient> LoadDataFromFileAfterDeleteClient(string AccNum)
{

    vector<stClient> vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {

        stClient Client;
        string Line;

        while (getline(MyFile, Line))
        {
            Client = ConverLineToRecord(Line, Delemeter);
            if (Client.IsDeleted == false)
            {
                vClient.push_back(Client);
            }

        }
        MyFile.close();
    }
    return vClient;
}
void DeleteAccountNumber(vector< stClient>& v, stClient Data)
{
    string st = "";
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (stClient& Client : v)
        {
            if (Client.IsDeleted == false)
            {
                st = ClientFromRecordToLine(Client);
                MyFile << st << endl;
            }

        }
        MyFile.close();
    }

}
bool DeletAccountNumber(stClient Client, string num, vector< stClient>& v)
{

    char IsUpdate;
    if (FindClientByAccountNumber(v, num, Client))
    {
        PrintClientRecord(Client);
        cout << "\n\nAre you sure do you want to update this account: y/n ? ";
        cin >> IsUpdate;
        if (toupper(IsUpdate) == 'Y')
        {

            MarkDeletedAccount(v, num);

            DeleteAccountNumber(v, Client);

            v = LoadDataFromFileAfterDeleteClient(num);
            cout << "\nClient Update Successfully\n\n";
            return true;
        }

    }
    else
    {
        cout << "The Account number (" << num << ") is not found";
    }
    return false;
}
void DeleteClientScreen()
{

    vector<stClient> vClient = ReadDataFromFile();
    string AccNum = ReadAccountNumber();
    stClient Client;
    cout << "____________________________________\n";
    cout << "        Delete Client Screen        \n";
    cout << "____________________________________\n";


    if (FindClientByAccountNumber(vClient, AccNum, Client))
    {
        DeletAccountNumber(Client, AccNum, vClient);
    }
    else
    {
        cout << "The Client with Account Number [" << AccNum << "] is not found.\n";

    }

}
bool MarkUpdatedAccount(vector<stClient>& vClient, string AccNum)
{
    for (stClient& Client : vClient)
    {
        if (AccNum == Client.AccountNumber)
        {
            Client.IsDeleted = true;
            return true;
        }
    }
    return false;
}
void  UpdateAccountNumber(vector< stClient>& v, stClient Data)
{
    string st = "";
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (stClient& Client : v)
        {
            
 st = ClientFromRecordToLine(Client);
            MyFile << st << endl;
            
           

        }
        MyFile.close();
    }

}
void  UpdateAccountBalance(vector< stClient>& v, stClient Data, string AccNum)
{
    string st = "";
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (stClient& Client : v)
        {
            if (AccNum == Client.AccountNumber)
            {
                Client.AccountBalance = Data.AccountBalance;
            }
            st = ClientFromRecordToLine(Client);
            MyFile << st << endl;

        }
        MyFile.close();
    }

}
bool UpdateClients(stClient Client, string num, vector< stClient>& v)
{

    char IsUpdate;
    if (FindClientByAccountNumber(v, num, Client))
    {
        PrintClientRecord(Client);
        cout << "\n\nAre you sure do you want to update this account: y/n ? ";
        cin >> IsUpdate;
        if (toupper(IsUpdate) == 'Y')
        {
            for (stClient& Client : v)
            {
                if (Client.AccountNumber == num)
                {
                    Client = ChangeClientRecord(num);
                    break;
                }

            }

            UpdateAccountNumber(v, Client);


            cout << "\nClient Update Successfully.\n\n";
            return true;
        }

    }
    else
    {
        cout << "The Account number (" << num << ") is not found";
    }
    return false;
}

void UpDatedClientScreen()
{
    vector<stClient> vClient = ReadDataFromFile();
    stClient Client;
    string AccNum = ReadAccountNumber();
    cout << "____________________________________\n";
    cout << "       Client Update Screen         \n";
    cout << "____________________________________\n";


    if (FindClientByAccountNumber(vClient, AccNum, Client))
    {
        UpdateClients(Client, AccNum, vClient);
    }
    else
    {
        cout << "The Account Number [" << AccNum << "] is not found.\n";
    }


}
void FindClientScreen()
{
    vector<stClient>  vClient = ReadDataFromFile();
    stClient Client;
    string AccNum = ReadAccountNumber();
    cout << "_________________________________________\n";
    cout << "           Find Clinet Screen            \n";
    cout << "_________________________________________\n\n";


    if (FindClientByAccountNumber(vClient, AccNum, Client))
    {
        PrintClientRecord(Client);
    }
    else
    {
        cout << "Client with Account number [" << AccNum << "] is not found";
    }


}
void ExitScreen()
{
    cout << "_______________________________________\n";
    cout << "          Programm Ends  :-)            \n";
    cout << "_______________________________________\n";


}
bool DepositOperation(vector <stClient>& vClient, string num, double DepositAmount)
{

    for (stClient& Data : vClient)
    {
        if (Data.AccountNumber == num)
        {
            Data.AccountBalance += DepositAmount;
            AddClientToFile(vClient,FileName);
            cout << "Done successfully new balance is " << Data.AccountBalance << endl;
            return true;
        }

    }
    return false;
}

bool DepositOp(vector<stClient>  vClient,double Amount, string AccNum)
{
    char IsDeposit = 'y';
   
    cout << "\nAre you sure do you want to perfor this transaction ? Y/N: ";
    cin >> IsDeposit;
    if (toupper(IsDeposit) == 'Y')
    {
        DepositOperation(vClient, AccNum,Amount);
     
        return true;
    }
    return false;
}
void DepositScreen()
{
 vector<stClient>  vClient = ReadDataFromFile();
    stClient Client;
    
  

    cout << "_____________________________________\n";
    cout << "\t Deposit Screen\n";
    cout << "_____________________________________\n";

string AccNum =  ReadAccountNumber();

    while (! FindClientByAccountNumber(vClient, AccNum, Client))
    {
        cout << "Client with [" << AccNum << "] dose not exist. \n";

        AccNum = ReadAccountNumber();

    }
    PrintClientRecord(Client);
    double Amount = 0;
    cout << "\n Please Enter deposite amount ?: ";
    cin >> Amount;


    DepositOp(vClient,Amount  ,AccNum);

}
void WithdrawScreen()
{
    vector<stClient>  vClient = ReadDataFromFile();
    stClient Client;



    cout << "_____________________________________\n";
    cout << "\t Withdraw Screen\n";
    cout << "_____________________________________\n";

    string AccNum = ReadAccountNumber();

    while (FindClientByAccountNumber(vClient, AccNum, Client) == 0)
    {
        cout << "Client with [" << AccNum << "] dose not exist. \n";

        AccNum = ReadAccountNumber();

    }

    PrintClientRecord(Client);
    double Amount = 0;
    cout << "\nPlease Enter Withdraw amount ?: ";
    cin >> Amount;
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount excees the balance ,you can withdraw up to " << Client.AccountBalance << endl;
        cout << "Please Enter Another Amount : ";
        cin >> Amount;
    }
    DepositOp(vClient,( -1 * Amount), AccNum);

}
void PrintClientsForTotalBalances(stClient Client)
{

    cout << "|" << setw(15) << left << Client.AccountNumber
        << " |" << setw(25) << left << Client.Name
        << " |" << setw(30) << left << Client.AccountBalance << endl;

    cout << "\n____________________________________________________________________________________\n";
}
void TotalBalancesScreen()
{
    double TotalBalances = 0;
    vector<stClient> vClient = ReadDataFromFile();
    cout << "                           Client List  (" << vClient.size() << ") Client(s)                       \n";
    cout << "____________________________________________________________________________________\n\n";
    cout << "|" << setw(15) << left << " Account Number"
        << " |" << setw(25) << left << " Client Name"
        << " |" << setw(30) << left << " Balance" << endl;
    cout << "____________________________________________________________________________________\n";


    for (stClient& Client : vClient)
    {
        PrintClientsForTotalBalances(Client);
        cout << endl;
        TotalBalances += Client.AccountBalance;
    }

    cout << "\nTotal Balances = " << to_string(TotalBalances) << endl;
}
short ReadTransactionscreen()
{
    short Chose = 0;
    do {
        cout << "Chose What do you want to do ? [1 to 4] ? ";
        cin >> Chose;
    } while (Chose <= 0 || Chose > 4);
    return Chose;
}
void PerforTransaction(enTransactionList List)
{
    switch (List)
    {
    case enTransactionList::eDeposit:
    {
        ClearScreen();
        DepositScreen();
        GoBackTrancactionScreen();
        break;
    }
    case enTransactionList::eWithdraw:
    {
        ClearScreen();
        WithdrawScreen();
        GoBackTrancactionScreen();
        break;
    }
    case enTransactionList::eTotalBalnces:
    {
        ClearScreen();
        TotalBalancesScreen();
        GoBackTrancactionScreen();
        break;
    }
    case enTransactionList::eMainMenu:
    {
        ClearScreen();
        MenueScreen();
        break;
    }

    }
}
void GoBackTrancactionScreen()
{
    
    system("pause");
    ClearScreen();
TransactionsMenuScreen();

}
void TransactionsMenuScreen()
{
    cout << "============================================\n";
    cout << "\t  Transaction Menu Screen  \n";
    cout << "============================================\n";
    cout << "[1] Deposit.\n";
    cout << "[2] Withdraw.\n";
    cout << "[3] Total Balances.\n";
    cout << "[4] Main Menu.\n";
    cout << "============================================\n";

    PerforTransaction((enTransactionList)ReadTransactionscreen());

}
short ReadMainOption()
{
    short Chose = 0;
    do {
        cout << "Chose What do you want to do ? [1 to 7] ? ";
        cin >> Chose;
    } while (Chose <= 0 || Chose > 7);
    return Chose;
}
void PerforMainMenu(enClientList Client)
{
    switch (Client)
    {
    case enClientList::CList:

    {
        ClearScreen();
        ClientList();
        GoBackToMenu();
        break;
    }
    case enClientList::AddNewC:
    {
        ClearScreen();
        AddNewClientScreen();
        GoBackToMenu();
        break;
    }
    case enClientList::DelC:
    {
        ClearScreen();
        DeleteClientScreen();
        GoBackToMenu();
        break;
    }
    case enClientList::UpDateC:
    {
        ClearScreen();
        UpDatedClientScreen();
        GoBackToMenu();
        break;
    }
    case enClientList::FindC:
    {
        ClearScreen();
        FindClientScreen();
        GoBackToMenu();
        break;
    }
    case enClientList::Exit:
    {
        ClearScreen();
        ExitScreen();

        break;
    }
    case enClientList::Transaction:
    {
        ClearScreen();
        TransactionsMenuScreen();

    }
    }
}
void GoBackToMenu()
{

    system("pause");
    ClearScreen();
    MenueScreen();
}
void MenueScreen()
{

    cout << "===============================\n";
    cout << "       Main Menue Screen       \n";
    cout << "===============================\n";
    cout << "    [1] Show Clinet List.      \n";
    cout << "    [2] Add New Clients.       \n";
    cout << "    [3] Delete Clients.        \n";
    cout << "    [4] Update Client Info.    \n";
    cout << "    [5] Find Client.           \n";
    cout << "    [6] Transactions           \n";
    cout << "    [7] Exit                   \n";
    cout << "===============================\n";

    PerforMainMenu((enClientList)ReadMainOption());

}

int main()
{

    MenueScreen();



}