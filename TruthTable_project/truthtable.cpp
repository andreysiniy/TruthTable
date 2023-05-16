#include "truthtable.h"
#include <QMap>

TruthTable::TruthTable()
{

}

QList<QMap<QString, bool>> TruthTable::generateCombinations(QStringList variables)
{
    // Инициализируем пустой список combinations, в который будут добавляться сгенерированные комбинации.
    QList<QMap<QString, bool>> combinations;
    // Вычисляем количество переменных numVariables, переданных в функцию через параметр variables.
    int numVariables = variables.size();
    // Вычисляем количество возможных комбинаций numCombinations, которые могут быть сгенерированы на основе количества переменных.
    // Это значение вычисляется как 2 в степени numVariables.
    int numCombinations = 1 << numVariables;
    // Запускаем цикл от 0 до numCombinations - 1. Внутри цикла будут генерироваться все возможные комбинации.
    for (int i = 0; i < numCombinations; i++)
    {
        // В каждой итерации цикла создаем пустой QMap объект combination, который будет представлять одну комбинацию переменных.
        QMap<QString, bool> combination;
        // Запускаем вложенный цикл от 0 до numVariables - 1. Внутри цикла будут генерироваться значения переменных в данной комбинации.
        for (int k = 0; k < numVariables; k++)
        {
            /* Генерируем значение переменной, используя оператор побитового сдвига влево << и оператор побитового И &.
             * Для каждой переменной k значение генерируется так: i & (1 << k). Этот код проверяет, установлен ли k-й бит числа i.
             * Если значение бита равно 1, то мы устанавливаем переменной значение true в комбинации, иначе значение false. */
            combination[variables[k]] = (i & (1 << k)) != 0;
        }
        // Добавляем сгенерированную комбинацию в список combinations с помощью функции append.
        combinations.append(combination);
    }
    // Возвращаем список всех сгенерированных комбинаций combinations.
    return combinations;
}

QList<QMap<QString, bool>> TruthTable::generateTruthTable()
{
    // Генерируем комбинации значений переменных
    QList<QMap<QString, bool>> combinations = generateCombinations(this->variables);

    // Проходимся по узлам дерева операций
    for (int i = 0; i < this->nodesAmount - this->variables.length(); i++)
    {
        // Находим узел с самой низкоуровневой операцией
        Node *currentOperation = this->root->lowestOperationType();

        // Проходимся по всем комбинациям значений переменных
        for (int k = 0; k < combinations.length(); k++)
        {
            // Вычисляем значение текущей операции для данной комбинации переменных
            combinations[k][currentOperation->name] = currentOperation->evaluate(currentOperation, combinations[k]);
        }

        // После вычисления значения, узел операции становится переменной
        currentOperation->type = VAR;
        currentOperation->left = nullptr;
        currentOperation->right = nullptr;
    }

    // Возвращаем полученные комбинации значений
    return combinations;
}
