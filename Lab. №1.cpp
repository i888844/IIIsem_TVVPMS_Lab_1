#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

class cube
{
private:
    int sides;
    double* probability, * ort;
public:
    cube()
    {
        sides = 6;
        probability = new double[sides];
        ort = new double[sides];
        double sum = 0;
        for (int i = 0; i < sides - 1; i++)
        {
            probability[i] = 1.0 / sides;
            sum += probability[i];
            ort[i] = sum;
        }
        probability[sides - 1] = 1 - sum;
        ort[sides - 1] = 1;
    }
    cube(int cube_sides)
    {
        if (cube_sides > 1)
        {
            sides = cube_sides;
        }
        else
        {
            sides = 6;
        }
        probability = new double[sides];
        ort = new double[sides];
        double sum = 0;
        for (int i = 0; i < sides - 1; i++)
        {
            probability[i] = 1.0 / sides;
            sum += probability[i];
            ort[i] = sum;
        }
        probability[sides - 1] = 1 - sum;
        ort[sides - 1] = 1;
    }
    cube(int cube_sides, int dominant_side, double probability_side)
    {
        double sum = 0;
        if (cube_sides > 1 && dominant_side > 0 && dominant_side <= cube_sides && probability_side > 0 && probability_side < 1)
        {
            sides = cube_sides;
            probability = new double[sides];
            ort = new double[sides];
            double p = (1 - probability_side) / (sides - 1);
            for (int i = 0; i < sides - 1; i++)
            {
                if ((i + 1) == dominant_side)
                {
                    probability[i] = probability_side;
                }
                else
                {
                    probability[i] = p;
                }
                sum += probability[i];
                ort[i] = sum;
            }
        }
        else
        {
            sides = 6;
            probability = new double[sides];
            ort = new double[sides];
            for (int i = 0; i < sides - 1; i++)
            {
                probability[i] = 1.0 / sides;
                sum += probability[i];
                ort[i] = sum;
            }
        }
        probability[sides - 1] = 1 - sum;
        ort[sides - 1] = 1;

    }
    cube(cube &object)
    {
        sides = object.sides;
        probability = new double[sides];
        ort = new double[sides];
        for (int i = 0; i < sides; i++)
        {
            probability[i] = object.probability[i];
            ort[i] = object.ort[i];
        }
    }
    ~cube()
    {
        delete[]probability;
        delete[]ort;
    }
    int get_sides()
    {
        return sides;
    }
    double get_probability_side(int side_number)
    {
        if (side_number > 0 && side_number <= sides)
        {
            return (probability[side_number - 1]);
        }
        return 0;
    }
    void output()
    {
        cout << "Количество сторон: " << sides <<  endl;
        for (int i = 0; i < sides; i++)
        {
            cout << i + 1 << "     " << probability[i] << endl;
        }
    }
    int roll()
    {
        double x = (double)rand()/RAND_MAX;
        for (int i = 0; i < sides; i++)
        {
            if (x <= ort[i])
            {
                return (i + 1);
            }
        }
        return 1;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    int cmd = 0, sides = 0;
    int i = 0, roll_amount = 0, * results;
    double dominant_side = 0, probability_side = 0;
    cout << "Выберите куб: 1 - с равным весом граней, 2 - с доминирующей гранью." << endl;
    cout << "Введите номер команды: ";
    cin >> cmd;
    while (cmd != 1 && cmd != 2)
    {
        cout << "[Ошибка]: введён неверный номер команды. Введите номер команды: ";
        cin >> cmd;
    }
    switch (cmd)
    {
        case 1:
        {
            cout << "Введите кол-во граней: ";
            cin >> sides;
            cube a(sides);

            results = new int[a.get_sides()];
            for (i = 0; i < a.get_sides(); i++)
            {
                results[i] = 0;
            }
            cout << "Введите количество бросков: ";
            cin >> roll_amount;
            while (roll_amount <= 0)
            {
                cout << "[Ошибка]: количество бросков должно быть больше 0. Введите количество бросков: ";
                cin >> roll_amount;
            }
            for (i = 0; i < roll_amount; i++)
            {
                results[a.roll() - 1]++;
            }
            cout << "Номер грани     Количество бросков     Вероятность выпадения (теор.)     Вероятность выпадения (практ.)     Отклонение" << endl;
            for (i = 0; i < a.get_sides(); i++)
            {
                double theoretic_probability = a.get_probability_side(i + 1), practic_probability = (double)results[i] / roll_amount;
                cout << "      " << i + 1 << "                 " << results[i] << "                 " << theoretic_probability << "                           " << practic_probability << "                           " << fabs(theoretic_probability - practic_probability) << endl;
            }
            delete[]results;
            break;
        }
        case 2:
        {
            cout << "Введите кол-во граней: ";
            cin >> sides;
            cout << "Введите номер доминантной грани: ";
            cin >> dominant_side;
            cout << "Ведите вес доминантной грани: ";
            cin >> probability_side;
            cube a(sides, dominant_side, probability_side);
            results = new int[a.get_sides()];
            for (i = 0; i < a.get_sides(); i++)
            {
                results[i] = 0;
            }
            cout << "Введите количество бросков: ";
            cin >> roll_amount;
            while (roll_amount <= 0)
            {
                cout << "[Ошибка]: количество бросков должно быть больше 0. Введите количество бросков: ";
                cin >> roll_amount;
            }
            for (i = 0; i < roll_amount; i++)
            {
                results[a.roll() - 1]++;
            }
            cout << "Номер грани     Количество бросков     Вероятность выпадения (теор.)     Вероятность выпадения (практ.)     Отклонение" << endl;
            for (i = 0; i < a.get_sides(); i++)
            {
                double theoretic_probability = a.get_probability_side(i + 1), practic_probability = (double)results[i] / roll_amount;
                cout << "      " << i + 1 << "                 " << results[i] << "                 " << theoretic_probability << "                           " << practic_probability << "                           " << fabs(theoretic_probability - practic_probability) << endl;
            }
            delete[]results;
            break;
        }
    }
    return 0;
}