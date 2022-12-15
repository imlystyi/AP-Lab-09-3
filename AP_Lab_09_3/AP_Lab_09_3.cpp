// Якубовський Владислав, ІКНІ, РІ-11, АП, ЛР 09.3, варіант 24
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

enum Position { PR_MANAGER, DESIGNER, IT_SPECIALIST };

string positions[]{ "PR-менеджер", "Дизайнер", "IT-спеціаліст" };

struct Worker
{
    string surname = "", initials = "";
    Position position = PR_MANAGER;

    int sinceWorksYear = 2010, wage = 12000;
};

void DisplayListOfWorkers(Worker* workers, const int workersCount)
{
    cout << "\n=======================================================================================" <<
        "\n| № |    Прізвище    | Ініціали |    Посада    | Рік прийому | Заробітна плата (грн.) |" << 
        "\n---------------------------------------------------------------------------------------" << endl;

    for (int ii = 0; ii < workersCount; ii++)
    {
        cout << "| " << setw(2) << ii + 1
            << "| " << setw(15) << workers[ii].surname
            << "| " << setw(9) << workers[ii].initials
            << "| " << setw(13) << positions[workers[ii].position]
            << "| " << setw(12) << workers[ii].sinceWorksYear
            << "| " << setw(23) << workers[ii].wage << "|" << endl;
    }

    cout << "=======================================================================================" << endl;
}

void EditListOfWorkers(Worker* workers, int &workersCount)
{
    int menuItem, workerNumber, specializationNumber;

    do
    {
        cout << "\nВиберіть дію:" <<
        "\n[1] - редагувати дані про певного службовця" << 
        "\n[2] - додати нового службовця у список" << 
        "\n[3] - вилучити певного службовця зі списку" << 
        "\n[0] - вихід з режиму коригування" << endl;

        cout << "\nВведіть значення: "; cin >> menuItem;

        switch (menuItem)
        {
        case 1:
            cout << "\nШвидкий список службовців: " << endl;

            for (int ii = 0; ii < workersCount; ii++)
                cout << ii + 1 << ". " << workers[ii].surname << " " << workers[ii].initials << endl;

            cout << "\nВведіть номер службовця, дані про якого хочете редагувати: "; cin >> workerNumber; workerNumber--;
            cout << "Введіть нове прізвище для службовця: "; cin >> workers[workerNumber].surname;
            cout << "Введіть нові ініціали для службовця: "; cin >> workers[workerNumber].initials;
            cout << "Введіть нову посаду (1 - PR-менеджер, 2 - Дизайнер, 3 - IT-спеціаліст) для службовця: "; cin >> specializationNumber;            
            cout << "Введіть новий рік прийому для службовця: "; cin >> workers[workerNumber].sinceWorksYear;
            cout << "Введіть нову заробітну плату для службовця: "; cin >> workers[workerNumber].wage;

            workers[workerNumber].position = (Position)(specializationNumber - 1);

            break;

        case 2:
            workersCount += 1;

            cout << "\nВведіть прізвище нового службовця: "; cin >> workers[workersCount - 1].surname;
            cout << "Введіть ініціали нового службовця: "; cin >> workers[workersCount - 1].initials;
            cout << "Введіть посаду (1 - PR-менеджер, 2 - Дизайнер, 3 - IT-спеціаліст) нового службовця: "; cin >> specializationNumber;            
            cout << "Введіть рік прийому нового службовця: "; cin >> workers[workersCount - 1].sinceWorksYear;
            cout << "Введіть заробітну плату нового службовця: "; cin >> workers[workersCount - 1].wage;

            workers[workersCount - 1].position = (Position)(specializationNumber - 1);

            break;

        case 3:
            cout << "\nШвидкий список службовців: " << endl;

            for (int ii = 0; ii < workersCount; ii++)
                cout << ii + 1 << ". " << workers[ii].surname << " " << workers[ii].initials << endl;

            cout << "\nВведіть номер працівника, якого необхідно видалити: "; cin >> workerNumber;

            swap(workers[workerNumber], workers[workersCount - 1]);
            
            workersCount--;

            break;

        case 0:
            break;

        default:
            cout << "\nПомилка! Оберіть пункт меню правильно!";
        }
    } while (menuItem != 0);
}

void DisplayInformationAboutWorker(Worker* workers, const int workersCount, string searchedSurname)
{
    for (int ii = 0; ii < workersCount; ii++)
    {
        if (workers[ii].surname == searchedSurname)
        {
            cout << "\nІнформація про службовця: " <<
                "\n1) прізвище та ініціали: " << workers[ii].surname << " " << workers[ii].initials <<
                "\n2) посада: " << positions[workers[ii].position] <<
                "\n3) рік прийому: " << workers[ii].sinceWorksYear <<
                "\n4) заробітна плата: " << workers[ii].wage << " грн." << endl;

            return;
        }
    }

    cout << "\nСлужбовця з таким прізвищем немає.\n";
}

void SortListOfWorkers(Worker* workers, int workersCount, int mode)
{
    switch (mode)
    {
    case 1:
        // Режим 1 - сортування за прізвищем
        for (int ii = 0; ii < workersCount - 1; ii++)
            for (int jj = 0; jj < workersCount - ii - 1; jj++)
                if (workers[jj].surname < workers[jj + 1].surname)
                    swap(workers[jj], workers[jj + 1]);

        break;

    case 2:
        // Режим 2 - сортування за заробітною платою
        for (int ii = 0; ii < workersCount - 1; ii++)
            for (int jj = 0; jj < workersCount - ii - 1; jj++)
                if (workers[jj].wage < workers[jj + 1].wage)
                    swap(workers[jj], workers[jj + 1]);

        break;

    case 3:
        // Режим 3 - сортування за роком прийому на роботу
        for (int ii = 0; ii < workersCount - 1; ii++)
            for (int jj = 0; jj < workersCount - ii - 1; jj++)
                if (workers[jj].sinceWorksYear < workers[jj + 1].sinceWorksYear)
                    swap(workers[jj], workers[jj + 1]);

        break;
    }
}

void SaveToFile(Worker* workers, const int size, const char* filename)
{
    ofstream fout(filename, ios::binary);

    fout.write((char*)&size, sizeof(size));

    for (int ii = 0; ii < size; ii++)
        fout.write((char*)&workers[ii], sizeof(Worker));

    fout.close();
}

void LoadFromFile(Worker* &workers, int& size, const char* filename)
{
    delete [] workers;

    ifstream fin(filename, ios::binary);

    fin.read((char*)&size, sizeof(size));

    workers = new Worker[size];

    for (int ii = 0; ii < size; ii++)
        fin.read((char*)&workers[ii], sizeof(Worker));

    fin.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int _size = 99, workersCount = 4;

    Worker* workers = new Worker[_size];

    workers[0].surname = "Рильський"; workers[0].initials = "І.І."; workers[0].position = DESIGNER; workers[0].sinceWorksYear = 2014; workers[0].wage = 12100;
    workers[1].surname = "Магомедов"; workers[1].initials = "Х.А."; workers[1].position = IT_SPECIALIST; workers[1].sinceWorksYear = 2018; workers[1].wage = 18300;
    workers[2].surname = "Іванова"; workers[2].initials = "Г.О."; workers[2].position = PR_MANAGER; workers[2].sinceWorksYear = 2013; workers[2].wage = 17600;
    workers[3].surname = "Петренко"; workers[3].initials = "П.П."; workers[3].position = IT_SPECIALIST; workers[3].sinceWorksYear = 2012; workers[3].wage = 16200;

    int menuItem, mode;

    string searchedSurname;

    char filename[100];

    do
    {
        cout << "\nВиберіть дію:" <<
            "\n[1] - коригувати список службовців" <<
            "\n[2] - сортувати список службовців"
            "\n[3] - вивід на екран інформації про службовця за його прізвищем"
            "\n[4] - запис даних списку у файл"
            "\n[5] - зчитування даних списку із файлу" <<
            "\n[6] - вивід списку службовців на екран" <<
            "\n[0] - вихід та завершення роботи програми\n" << endl;

        cout << "Введіть значення: "; cin >> menuItem;

        switch (menuItem)
        {
        case 1:
            EditListOfWorkers(workers, workersCount);
            
            break;

        case 2:
            cout << "\nВведіть режим сортування (1 - за прізвищем, 2 - за заробітною платою, 3 - за роком прийому на роботу): "; cin >> mode;

            SortListOfWorkers(workers, workersCount, mode);

            break;

        case 3:           
            cout << "\nВведіть прізвище шуканого працівника: "; cin >> searchedSurname;

            DisplayInformationAboutWorker(workers, workersCount, searchedSurname);

            break;

        case 4:
            cin.sync();

            cout << "\nВведіть ім'я файлу для збереження: "; cin >> filename; 

            SaveToFile(workers, workersCount, filename);

            break;

        case 5:
            cin.sync();

            cout << "Введіть ім'я файлу для завантаження: "; cin >> filename;

            LoadFromFile(workers, workersCount, filename);

            break;

        case 6:
            DisplayListOfWorkers(workers, workersCount);

            break;

        case 0:
            break;

        default:
            cout << "\nПомилка! Оберіть пункт меню правильно!" << endl;
        }
    } while (menuItem != 0);
}

