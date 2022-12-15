// ����������� ���������, ��Ͳ, в-11, ��, �� 09.3, ������ 24
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

enum Position { PR_MANAGER, DESIGNER, IT_SPECIALIST };

string positions[]{ "PR-��������", "��������", "IT-���������" };

struct Worker
{
    string surname = "", initials = "";
    Position position = PR_MANAGER;

    int sinceWorksYear = 2010, wage = 12000;
};

void DisplayListOfWorkers(Worker* workers, const int workersCount)
{
    cout << "\n=======================================================================================" <<
        "\n| � |    �������    | ������� |    ������    | г� ������� | �������� ����� (���.) |" << 
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
        cout << "\n������� ��:" <<
        "\n[1] - ���������� ��� ��� ������� ���������" << 
        "\n[2] - ������ ������ ��������� � ������" << 
        "\n[3] - �������� ������� ��������� � ������" << 
        "\n[0] - ����� � ������ �����������" << endl;

        cout << "\n������ ��������: "; cin >> menuItem;

        switch (menuItem)
        {
        case 1:
            cout << "\n������� ������ ����������: " << endl;

            for (int ii = 0; ii < workersCount; ii++)
                cout << ii + 1 << ". " << workers[ii].surname << " " << workers[ii].initials << endl;

            cout << "\n������ ����� ���������, ��� ��� ����� ������ ����������: "; cin >> workerNumber; workerNumber--;
            cout << "������ ���� ������� ��� ���������: "; cin >> workers[workerNumber].surname;
            cout << "������ ��� ������� ��� ���������: "; cin >> workers[workerNumber].initials;
            cout << "������ ���� ������ (1 - PR-��������, 2 - ��������, 3 - IT-���������) ��� ���������: "; cin >> specializationNumber;            
            cout << "������ ����� �� ������� ��� ���������: "; cin >> workers[workerNumber].sinceWorksYear;
            cout << "������ ���� �������� ����� ��� ���������: "; cin >> workers[workerNumber].wage;

            workers[workerNumber].position = (Position)(specializationNumber - 1);

            break;

        case 2:
            workersCount += 1;

            cout << "\n������ ������� ������ ���������: "; cin >> workers[workersCount - 1].surname;
            cout << "������ ������� ������ ���������: "; cin >> workers[workersCount - 1].initials;
            cout << "������ ������ (1 - PR-��������, 2 - ��������, 3 - IT-���������) ������ ���������: "; cin >> specializationNumber;            
            cout << "������ �� ������� ������ ���������: "; cin >> workers[workersCount - 1].sinceWorksYear;
            cout << "������ �������� ����� ������ ���������: "; cin >> workers[workersCount - 1].wage;

            workers[workersCount - 1].position = (Position)(specializationNumber - 1);

            break;

        case 3:
            cout << "\n������� ������ ����������: " << endl;

            for (int ii = 0; ii < workersCount; ii++)
                cout << ii + 1 << ". " << workers[ii].surname << " " << workers[ii].initials << endl;

            cout << "\n������ ����� ����������, ����� ��������� ��������: "; cin >> workerNumber;

            swap(workers[workerNumber], workers[workersCount - 1]);
            
            workersCount--;

            break;

        case 0:
            break;

        default:
            cout << "\n�������! ������ ����� ���� ���������!";
        }
    } while (menuItem != 0);
}

void DisplayInformationAboutWorker(Worker* workers, const int workersCount, string searchedSurname)
{
    for (int ii = 0; ii < workersCount; ii++)
    {
        if (workers[ii].surname == searchedSurname)
        {
            cout << "\n���������� ��� ���������: " <<
                "\n1) ������� �� �������: " << workers[ii].surname << " " << workers[ii].initials <<
                "\n2) ������: " << positions[workers[ii].position] <<
                "\n3) �� �������: " << workers[ii].sinceWorksYear <<
                "\n4) �������� �����: " << workers[ii].wage << " ���." << endl;

            return;
        }
    }

    cout << "\n��������� � ����� �������� ����.\n";
}

void SortListOfWorkers(Worker* workers, int workersCount, int mode)
{
    switch (mode)
    {
    case 1:
        // ����� 1 - ���������� �� ��������
        for (int ii = 0; ii < workersCount - 1; ii++)
            for (int jj = 0; jj < workersCount - ii - 1; jj++)
                if (workers[jj].surname < workers[jj + 1].surname)
                    swap(workers[jj], workers[jj + 1]);

        break;

    case 2:
        // ����� 2 - ���������� �� ��������� ������
        for (int ii = 0; ii < workersCount - 1; ii++)
            for (int jj = 0; jj < workersCount - ii - 1; jj++)
                if (workers[jj].wage < workers[jj + 1].wage)
                    swap(workers[jj], workers[jj + 1]);

        break;

    case 3:
        // ����� 3 - ���������� �� ����� ������� �� ������
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

    workers[0].surname = "���������"; workers[0].initials = "�.�."; workers[0].position = DESIGNER; workers[0].sinceWorksYear = 2014; workers[0].wage = 12100;
    workers[1].surname = "���������"; workers[1].initials = "�.�."; workers[1].position = IT_SPECIALIST; workers[1].sinceWorksYear = 2018; workers[1].wage = 18300;
    workers[2].surname = "�������"; workers[2].initials = "�.�."; workers[2].position = PR_MANAGER; workers[2].sinceWorksYear = 2013; workers[2].wage = 17600;
    workers[3].surname = "��������"; workers[3].initials = "�.�."; workers[3].position = IT_SPECIALIST; workers[3].sinceWorksYear = 2012; workers[3].wage = 16200;

    int menuItem, mode;

    string searchedSurname;

    char filename[100];

    do
    {
        cout << "\n������� ��:" <<
            "\n[1] - ���������� ������ ����������" <<
            "\n[2] - ��������� ������ ����������"
            "\n[3] - ���� �� ����� ���������� ��� ��������� �� ���� ��������"
            "\n[4] - ����� ����� ������ � ����"
            "\n[5] - ���������� ����� ������ �� �����" <<
            "\n[6] - ���� ������ ���������� �� �����" <<
            "\n[0] - ����� �� ���������� ������ ��������\n" << endl;

        cout << "������ ��������: "; cin >> menuItem;

        switch (menuItem)
        {
        case 1:
            EditListOfWorkers(workers, workersCount);
            
            break;

        case 2:
            cout << "\n������ ����� ���������� (1 - �� ��������, 2 - �� ��������� ������, 3 - �� ����� ������� �� ������): "; cin >> mode;

            SortListOfWorkers(workers, workersCount, mode);

            break;

        case 3:           
            cout << "\n������ ������� �������� ����������: "; cin >> searchedSurname;

            DisplayInformationAboutWorker(workers, workersCount, searchedSurname);

            break;

        case 4:
            cin.sync();

            cout << "\n������ ��'� ����� ��� ����������: "; cin >> filename; 

            SaveToFile(workers, workersCount, filename);

            break;

        case 5:
            cin.sync();

            cout << "������ ��'� ����� ��� ������������: "; cin >> filename;

            LoadFromFile(workers, workersCount, filename);

            break;

        case 6:
            DisplayListOfWorkers(workers, workersCount);

            break;

        case 0:
            break;

        default:
            cout << "\n�������! ������ ����� ���� ���������!" << endl;
        }
    } while (menuItem != 0);
}

