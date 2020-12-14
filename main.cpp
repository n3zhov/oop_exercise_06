#include "trapeze.hpp"
#include "vector.hpp"
#include "allocator.hpp"
#include <iostream>
using namespace std;
/*
 * Ежов Н П М8О-204Б-19
 * Разработать шаблоны классов согласно варианту задания.
 * Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат.
 * Классы должны иметь публичные поля.
 * Фигуры являются фигурами вращения, т.е. равносторонними (кроме трапеции и прямоугольника).
 * Для хранения координат фигур необходимо использовать шаблон  pair.
 * Создать шаблон динамической коллекцию, согласно варианту задания:
    1.	Коллекция должна быть реализована с помощью умных указателей (shared_ptr, weak_ptr).
    Опционально использование unique_ptr;
    2.	В качестве параметра шаблона коллекция должна принимать тип данных - фигуры;
    Вариант 28: трапеция, динамический массив, очередь
 */

int main() {
    int command;
    CustomVector<Trapeze<int>, CustomAllocator<Trapeze<int>, 20>> vec;
    cout << "This program created for demonstrating template collection work.\n" <<
         "Enter 1, if you want to add figure in vector\nEnter 2, and max_area to print count of figures, which area is smaller than max_area"
         << " on the screen, " << "\nEnter 3,"
         << " if you want to delete last figure, \nEnter 4, to print all figures\nEnter 5, to display this help text "
         << "once again\nEnter 6, and after that index of the figure which you want to see\nEnter 7, if you  want to exit the program\n"
         << "Enter 8, and index of figure, which you want to erase\n";
    while(true){
        cin >> command;
        cout.flush();
        switch(command){
            case 1:{
                Trapeze<int>figure;
                try {
                    cin >> figure;
                    vec.push_back(figure);
                } catch (exception &e) {
                    cout << e.what() << endl;
                    break;
                }
                cout << "Figure added successfully" << endl;;
            }
                break;
            case 2:{
                double max_area;
                cin >> max_area;
                size_t ans = count_if(vec.begin(), vec.end(), [max_area](Trapeze<int> &trp) {
                    return trp.area() < max_area;
                });
                cout << "Count of objects less than " << max_area << " area is " << ans << endl;
            }
                break;
            case 3:{
                try{
                    vec.pop_back();
                }
                catch(exception &e) {
                    cout << e.what() << endl;
                    break;
                }
                cout << "Figure deleted successfully" << endl;;
            }
                break;
            case 4:{
                for_each(vec.begin(), vec.end(), [](auto &trp) {
                    cout << trp << endl;
                });
            }
                break;
            case 5:{
                cout << "This program created for demonstrating template collection work.\n" <<
                     "Enter 1, if you want to add figure in vector\nEnter 2, to print area of all figures on the screen, " << "\nEnter 3,"
                     << " if you want to delete last figure, \nEnter 4, to print all figures \nEnter 5, to display this help text "
                     << "once again\nEnter 6, and after that index of the figure which you want to see\nEnter 7, if you  want to exit the program\n";
            }
                break;
            case 6:{
                int index;
                cin >> index;
                cout << vec[index];
            }
                break;
            case 7:{
                return 0;
            }
            case 8:{
                int index;
                cin >> index;
                try {
                    auto it = next(vec.begin(), index);
                    vec.erase(it);
                } catch (exception &e) {
                    cout << e.what() << endl;
                    break;
                }
                cout << "Figure successfully erased!" << endl;
            }
                break;
            default:{
                cout << "Error, wrong command number" << endl;;
                continue;
            }
        }
    }
}