#include <iostream>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;


void menu();
void login();
void signin();
void admin();
void showcar();
void newcar();
void delcar();
void user();
void newadmin();
void rentcar();
void retern_car();
void delete_admin();
void showadmin();



void showadmin() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

        con->setSchema("user");


        // Значение, по которому вы хотите выполнить выборку
        string searchValue = "1";
        // Название таблицы и колонки, в которой вы хотите искать
        string tableName = "people";
        string columnName = "admin";

        // SQL-запрос SELECT с условием WHERE
        string selectQuery = "SELECT * FROM " + tableName + " WHERE " + columnName + " = ?";

        // Создание объекта PreparedStatement и выполнение запроса
        sql::PreparedStatement* stmt;
        stmt = con->prepareStatement(selectQuery);
        stmt->setString(1, searchValue);
        sql::ResultSet* result = stmt->executeQuery();

        // Обработка результатов
        while (result->next()) {
            // Чтение данных из ResultSet
            std::string columnValue = result->getString(columnName);
            cout << "ID: " << result->getInt("id") << ", name: " << result->getString("name") << endl;
        }

        // Освобождение ресурсов
        delete result;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
    std::cout << "SQL Exception: " << e.what() << std::endl;
    }

}



void delete_admin() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");
    showadmin();
    int idToSelect;
    cout << "Введите ID пользователя для выбора: ";
    cin >> idToSelect;

    // Создание подготовленного запроса с параметром
    sql::PreparedStatement* stmt;
    stmt = con->prepareStatement("SELECT * FROM people WHERE id = ?");
    stmt->setInt(1, idToSelect);

    // Выполнение запроса
    string newValue = "0";
    std::string tableName = "people";
    std::string columnName = "admin";

    // SQL-запрос UPDATE для обновления значения по ID
    std::string updateQuery = "UPDATE " + tableName + " SET " + columnName + " = ? WHERE id = ?";
    try {
        sql::PreparedStatement* stmt;
        stmt = con->prepareStatement(updateQuery);
        stmt->setString(1, newValue);
        stmt->setInt(2, idToSelect);
        stmt->executeUpdate();
        cout << "Админ удалён";
        Sleep(1500);
        system("cls");
        admin();
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Exception: " << e.what() << std::endl;
    }


    delete con;
    delete stmt;
}


void retern_car() {
    string avail = "";
    showcar();
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");
    int idToSelect;
    
    cout << "Введите ID арендованной машины: ";
    cin >> idToSelect;
    string updateQuery = "UPDATE car SET availability = ? WHERE id = ?";

    // Создание объекта PreparedStatement и выполнение запроса
    sql::PreparedStatement* stmt;
    stmt = con->prepareStatement(updateQuery);
    stmt->setString(1, avail);
    stmt->setInt(2, idToSelect);
    stmt->executeUpdate();
    cout << "Спасибо за использование наших услуг" << endl;
    system("cls");
    user();

    delete con;
    delete stmt;
}

void rentcar() {
    showcar();
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");
    
    
    string avail = "x";
    int idToSelect;
    cout << "Введите ID строки для выбора: ";
    cin >> idToSelect;

    // Создание подготовленного запроса с параметром
    sql::PreparedStatement* stmt;
    stmt = con->prepareStatement("SELECT * FROM car WHERE id = ?");
    stmt->setInt(1, idToSelect);

    // Выполнение запроса
    sql::ResultSet* res = stmt->executeQuery();

    // ==================
    string columnName = "availability";

    // SQL-запрос SELECT для получения значения колонки по ID
    
    try {
        string selectQuery = "SELECT " + columnName + " FROM car WHERE id = ?";
        sql::PreparedStatement* stmt;
        stmt = con->prepareStatement(selectQuery);
        stmt->setInt(1, idToSelect);
        sql::ResultSet* result = stmt->executeQuery();
        if (result->next()) {
            string columnValue = result->getString(columnName);
            if (columnValue == "") {
                if (res->next()) {
                    cout << "ID: " << res->getInt("id") << ", model: " << res->getString("model") << ", nomer: " << res->getInt("nomer") << ", day_money: " << res->getString("day_money") << "$" << endl;
                    string updateQuery = "UPDATE car SET availability = ? WHERE id = ?";
                    // Создание объекта PreparedStatement и выполнение запроса
                    sql::PreparedStatement* stmt;
                    stmt = con->prepareStatement(updateQuery);
                    stmt->setString(1, avail);
                    stmt->setInt(2, idToSelect);
                    stmt->executeUpdate();
                    Sleep(1000);
                    system("cls");
                    user();
                }
                else {
                    cout << "Строка с ID " << idToSelect << " не найдена." << endl;
                }
        
            }
            else {
                cout << "Эта машина уже орендованна. \nВыберите машину без этого обозначентя 'x'" << endl;
                Sleep(3000);
                system("cls");
                rentcar();
            }
        }
        else {
            cout << "Запись с указанным ID не найдена." << endl;
        }
             
    }
    catch (sql::SQLException& e) {
            cout << "SQL Exception: " << e.what() << endl;
    }
        
    // Освобождение ресурсов
    delete res;
    delete stmt;
    delete con;

}


void newadmin() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");
    showadmin();
    int idToSelect;
    cout << "Введите ID пользователя для выбора: ";
    cin >> idToSelect;

    // Создание подготовленного запроса с параметром
    sql::PreparedStatement* stmt;
    stmt = con->prepareStatement("SELECT * FROM people WHERE id = ?");
    stmt->setInt(1, idToSelect);

    // Выполнение запроса
    string newValue = "1";
    std::string tableName = "people";
    std::string columnName = "admin";

    // SQL-запрос UPDATE для обновления значения по ID
    std::string updateQuery = "UPDATE " + tableName + " SET " + columnName + " = ? WHERE id = ?";
    try {
        sql::PreparedStatement* stmt;
        stmt = con->prepareStatement(updateQuery);
        stmt->setString(1, newValue);
        stmt->setInt(2, idToSelect);
        stmt->executeUpdate();
        string idinstr = to_string(idToSelect);
        cout << "Пользователь под id: " + idinstr + " добавлен в спмсок админов";
        Sleep(1500);
        system("cls");
        admin();
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Exception: " << e.what() << std::endl;
    }

    delete con;
    delete stmt;
}

void user() {
    int x;
    cout << "1. rent car" << endl;
    cout << "2. вернуть автро" << endl;
    cout << "3. menu" << endl;
    cout << "4. exit" << endl;
    cin >> x;
    if (x == 1) {
        system("cls");
        rentcar();        
    }
    else if (x == 2) {
        system("cls");
        retern_car();
    }
    else if (x == 3) {
        system("cls");
        menu();
    }
    else if (x == 4) {
        system("cls");
        exit(0);
    }
    else {
        cout << "ERROR" << endl;
        Sleep(2000);
        system("cls");
        user();
    }
}



void delcar() {
    showcar();
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");

    int idToSelect;
    cout << "Введите ID строки для выбора: ";
    cin >> idToSelect;

    // Создание подготовленного запроса с параметром
    sql::PreparedStatement* stmt;
    stmt = con->prepareStatement("SELECT * FROM car WHERE id = ?");
    stmt->setInt(1, idToSelect);

    // Выполнение запроса
    sql::ResultSet* res = stmt->executeQuery();

    // Вывод данных
    if (res->next()) {
        string deleteQuery = "DELETE FROM car WHERE id = ?";

        // Создание объекта PreparedStatement и выполнение запроса
        sql::PreparedStatement* stmt;
        stmt = con->prepareStatement(deleteQuery);
        stmt->setInt(1, idToSelect);
        stmt->executeUpdate();
        Sleep(2600);
        system("cls");
        admin();
    }
    else {
        cout << "Строка с ID " << idToSelect << " не найдена." << endl;
        admin();
    }

    // Освобождение ресурсов
    delete res;
    delete stmt;
    delete con;

}


void showcar() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");

    sql::Statement* stmt;
    stmt = con->createStatement();


    sql::ResultSet* res;
    res = stmt->executeQuery("SELECT * FROM car");

    while (res->next()) {
        cout << "ID: " << res->getInt("id") << ", model: " << res->getString("model") << ", nomer: " << res->getInt("nomer") << ", day_money: " << res->getString("day_money") << "$" << ", availability: " << res->getString("availability") << endl;
    }
    delete res;
    delete stmt;
    delete con;
}

void newcar() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");
    // Регистрация новой машины
    string model;
    int nomer, day_money;
    cout << "Введите модель машины: ";
    cin >> model;
    cout << "Введите номер: ";
    cin >> nomer;    
    cout << "Введите оплату за день: ";
    cin >> day_money;

    sql::PreparedStatement* stmt;
    stmt = con->prepareStatement("INSERT INTO car (model, nomer, day_money) VALUES (?, ?, ?)");
    stmt->setString(1, model);
    stmt->setInt(2, nomer);
    stmt->setInt(3, day_money);
    stmt->executeUpdate();

    cout << "Машина добавлена!" << endl;
    system("cls");
    admin();
    delete con;
    delete stmt;

}



void admin() {
    int x;
    cout << "1. exit" << endl;
    cout << "2. new car" << endl;
    cout << "3. delete car" << endl;
    cout << "4. new admin" << endl;
    cout << "5. menu" << endl;
    cout << "6. delete admin" << endl;
    cout << "7. show admin" << endl;
    cin >> x;
    if (x == 1) {
        system("cls");
        exit(0);
    }
    else if (x == 2) {
        system("cls");
        newcar();
    }
    else if (x == 3) {
        system("cls");
        delcar();
    }
    else if (x == 4) {
        newadmin();
    }
    else if (x == 5) {
        system("cls");
        menu();
    }else if (x == 6) {
        system("cls");
        delete_admin();
    }
    else if (x == 7) {
        showadmin();
    }
    else {
        int i;
        for (i = 0; i <= 100; i++) {
            cout << "ERROR" << endl;
        }
        system("cls");
        admin();
    }
}
//MENU
void menu() {
    int x;
    cout << "1.Login" << endl;
    cout << "2.sign in" << endl;
    cout << "3.exit" << endl;
    cin >> x;
    if (x == 1) {
        system("cls");
        login();
    }
    else if (x == 2) {
        system("cls");
        signin();
    }
    else if (x == 3) {
        exit(0);
    }
}

void login(){
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");

    // Вход пользователя
    string username, password;
    cout << "Введите имя пользователя: ";
    cin >> username;
    cout << "Введите пароль: ";
    cin >> password;

    string columnName = "admin";
    sql::Statement* stmt;
    stmt = con->createStatement();
    sql::ResultSet* res;
    res = stmt->executeQuery("SELECT * FROM people WHERE name = '" + username + "' AND password = '" + password + "'");

    try {
        string selectQuery = "SELECT " + columnName + " FROM people WHERE name = ? AND password = ?";

        sql::PreparedStatement* stmt;
        stmt = con->prepareStatement(selectQuery);
        stmt->setString(1, username);
        stmt->setString(2, password);
        sql::ResultSet* res = stmt->executeQuery();
        if (res->next()) {
            string columnValue = res->getString(columnName);
            if (columnValue == "0") {
                cout << "Добро пожаловать " + username + "!" << endl;
                sql::Statement* stmt;
                stmt = con->createStatement();


                sql::ResultSet* res;
                res = stmt->executeQuery("SELECT * FROM people WHERE name = '" + username + "' AND password = '" + password + "'");

                while (res->next()) {
                    cout << "Ваш id: " + res->getString("id");
                }
                Sleep(3000);
                system("cls");
                delete res;
                delete stmt;
                delete con;
                user();
            }
            else if (columnValue == "1") {
                cout << "Добро пожаловать " + username + "!" << endl;
                sql::Statement* stmt;
                stmt = con->createStatement();
                sql::ResultSet* res;
                res = stmt->executeQuery("SELECT * FROM people WHERE name = '" + username + "' AND password = '" + password + "'");

                while (res->next()) {
                    cout << "Ваш id: " + res->getString("id");
                }
                delete stmt;
                delete res;
                delete con;
                Sleep(3000);
                system("cls");
                admin();
            }
        }
        else {
            cout << "Ошибка входа. Проверьте имя пользователя и пароль." << endl;
            Sleep(3000);
            delete stmt;
            delete con;
            system("cls");
            menu();
        }
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << endl;
    }
    delete res;
    delete stmt;
    delete con;
}

void signin() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3308", "root", "root");

    con->setSchema("user");
    // Регистрация нового пользователя
    string username, password, admin = "0";
    cout << "Введите имя пользователя: ";
    cin >> username;
    cout << "Введите пароль: ";
    cin >> password;

    sql::PreparedStatement* stmt;
    stmt = con->prepareStatement("INSERT INTO people (name, password, admin) VALUES (?, ?, ?)");
    stmt->setString(1, username);
    stmt->setString(2, password);
    stmt->setString(3, admin);
    stmt->executeUpdate();
    if (password.length() >= 3) {
        cout << "Регистрация успешна!" << endl;
        system("cls");
        menu();
    }
    else {
        cout << "Пароль должен быть больше трёх символов" << endl;
        Sleep(2000);
        system("cls");
        menu();
    }
    delete con;
    delete stmt;
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}