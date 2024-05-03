#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <Windows.h>
#include <regex>
using namespace std;

class Animal {
public:
    int id;
    string name;
    string species;
    int age;
    string health;

    Animal(int id, string name, string species, int age, string health)
        : id(id), name(name), species(species), age(age), health(health) {}
};

class Shelter {
private:
    vector<Animal> animals;
public:
    void addAnimal(const Animal& newAnimal) {
        animals.push_back(newAnimal);
        cout << "Животное успешно добавлено." << endl;
    }

    void removeAnimal(int id) {
        for (auto it = animals.begin(); it != animals.end(); ++it) {
            if (it->id == id) {
                animals.erase(it);
                cout << "Животное успешно удалено." << endl;
                return;
            }
        }
        cout << "Животное не найдено." << endl;
    }

    void updateAnimal(int id, const string& newName, const string& newHealth) {
        for (auto& animal : animals) {
            if (animal.id == id) {
                animal.name = newName;
                animal.health = newHealth;
                cout << "Животное успешно обновлено." << endl;
                return;
            }
        }
        cout << "Животное не найдено." << endl;
    }

    Animal* getAnimal(int id) {
        for (auto& animal : animals) {
            if (animal.id == id) {
                return &animal;
            }
        }
        cout << "Животное не найдено." << endl;
        return nullptr;
    }

    void listAnimals() {
        if (animals.empty()) {
            cout << "В приюте нет животных." << endl;
            return;
        }
        for (const auto& animal : animals) {
            cout << "ID: " << animal.id << ", Имя: " << animal.name << ", Тип: " << animal.species << ", Возраст: " << animal.age << ", Здоровье: " << animal.health << endl;
        }
    }

    void searchAnimalByID(int id) {
        Animal* foundAnimal = getAnimal(id);
        if (foundAnimal != nullptr) {
            cout << "Найдено животное с ID " << id << ":" << endl;
            cout << "Имя: " << foundAnimal->name << ", Тип: " << foundAnimal->species << ", Возраст: " << foundAnimal->age << ", Здоровье: " << foundAnimal->health << endl;
        }
    }

    void printSeparator() {
        cout << "------------------------------------------------" << endl;
    }
};

class ShelterManager {
private:
    Shelter shelter;

    void displayMenu() {
        shelter.printSeparator();
        cout << "1. Добавить животное\n";
        cout << "2. Удалить животное\n";
        cout << "3. Обновить животное\n";
        cout << "4. Посмотреть всех животных\n";
        cout << "5. Поиск животного по ID\n";
        cout << "6. Выйти\n";
    }

    bool isNumeric(const string& str) {
        regex numeric_regex("\\d+");
        return regex_match(str, numeric_regex);
    }

    int getUserChoice() {
        displayMenu();
        string input;
        cout << "Введите свой выбор: ";
        cin >> input;
        if (!isNumeric(input) || input.length() != 1) {
            cout << "Неверный ввод. Пожалуйста, введите число от 1 до 6." << endl;
            return -1; 
        }
        return stoi(input);
    }

    void addAnimal() {
        int id, age;
        string idStr, ageStr, name, species, health;
        cout << "Введите ID: ";
        cin >> idStr;
        if (!isNumeric(idStr)) {
            cout << "Ошибка ввода ID. Пожалуйста, введите числовое значение." << endl;
            return;
        }
        id = stoi(idStr);
        cout << "Введите имя: ";
        cin.ignore();
        getline(cin, name);
        if (name.empty()) {
            cout << "Ошибка: имя не может быть пустым." << endl;
            return;
        }
        cout << "Введите тип животного: ";
        getline(cin, species);
        if (species.empty()) {
            cout << "Ошибка: тип животного не может быть пустым." << endl;
            return;
        }
        cout << "Введите возраст: ";
        cin >> ageStr;
        if (!isNumeric(ageStr)) {
            cout << "Ошибка ввода возраста. Пожалуйста, введите числовое значение." << endl;
            return;
        }
        age = stoi(ageStr);
        if (age <= 0) {
            cout << "Ошибка ввода возраста. Пожалуйста, введите положительное число." << endl;
            return;
        }
        cout << "Введите состояние здоровья: ";
        cin.ignore();
        getline(cin, health);
        if (health.empty()) {
            cout << "Ошибка: состояние здоровья не может быть пустым." << endl;
            return;
        }
        Animal newAnimal(id, name, species, age, health);
        shelter.addAnimal(newAnimal);
    }

    void removeAnimal() {
        int id;
        string idStr;
        cout << "Введите ID животного, которое хотите удалить: ";
        cin >> idStr;
        if (!isNumeric(idStr)) {
            cout << "Ошибка ввода ID. Пожалуйста, введите числовое значение." << endl;
            return;
        }
        id = stoi(idStr);
        shelter.removeAnimal(id);
    }

    void updateAnimal() {
        int id;
        string idStr, newName, newHealth;
        cout << "Введите ID животного, которое хотите обновить: ";
        cin >> idStr;
        if (!isNumeric(idStr)) {
            cout << "Ошибка ввода ID. Пожалуйста, введите числовое значение." << endl;
            return;
        }
        id = stoi(idStr);
        cout << "Введите новое имя: ";
        cin.ignore();
        getline(cin, newName);
        if (newName.empty()) {
            cout << "Ошибка: новое имя не может быть пустым." << endl;
            return;
        }
        cout << "Введите новое состояние здоровья: ";
        getline(cin, newHealth);
        if (newHealth.empty()) {
            cout << "Ошибка: новое состояние здоровья не может быть пустым." << endl;
            return;
        }
        shelter.updateAnimal(id, newName, newHealth);
    }

    void listAnimals() {
        shelter.listAnimals();
    }

    void searchAnimalByID() {
        int id;
        string idStr;
        cout << "Введите ID животного для поиска: ";
        cin >> idStr;
        if (!isNumeric(idStr)) {
            cout << "Ошибка ввода ID. Пожалуйста, введите числовое значение." << endl;
            return;
        }
        id = stoi(idStr);
        shelter.searchAnimalByID(id);
    }

public:
    void start() {
        int choice;
        do {
            choice = getUserChoice();
            if (choice == -1) 
                continue;
            switch (choice) {
            case 1:
                addAnimal();
                break;
            case 2:
                removeAnimal();
                break;
            case 3:
                updateAnimal();
                break;
            case 4:
                listAnimals();
                break;
            case 5:
                searchAnimalByID();
                break;
            case 6:
                cout << "Работа программы завершена." << endl;
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, выберите еще раз." << endl;
            }
        } while (choice != 6);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "Russian");
    ShelterManager manager;
    manager.start();
    return 0;
}
