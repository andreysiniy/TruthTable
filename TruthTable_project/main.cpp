#include <QCoreApplication>
#include "node.h"
#include "truthtable.h"

// Функция unpackString распаковывает выражение, представленное в обратной польской записи, возвращает указатель на корень выражения и список переменных
Node* unpackString(QString input, QStringList &variables);

int main(int argc, char *argv[])
{
    QCoreApplication aa(argc, argv);

    QString input = "A NOT B AND C OR";
    QStringList variablesN;
    Node* root = unpackString(input, variablesN);

   /* Node *a = new Node(VAR, "a");
    Node *notA = new Node(NOT, "NOT a", a);
    Node *b = new Node(VAR, "b");
    Node *andBnotA = new Node(AND, "NOT a AND b", notA, b);
    Node *c = new Node(VAR, "c");
    Node *andBnotAorC = new Node(OR, "(NOT a AND b) OR c", andBnotA, c);


    QStringList variables = {"a", "b"};
    TruthTable cool;
    cool.root = andBnotA;
    cool.variables = variables;
    cool.nodesAmount = 4;



    QString fileName = "truth_table.csv";
    cool.writeTruthTableToCSV(cool.generateTruthTable(), variables, fileName); */
    return aa.exec();
}

Node* unpackString(QString input, QStringList &variables)
{
    // Инициализация пустого списка узлов
    QList<Node*> nodeList;
    // Разбиваем строку на токены
    QStringList tokens = input.split(" ", Qt::SkipEmptyParts);
    // Для каждого токена
    foreach (QString token, tokens) {
        // Создаем пустой узел
        Node* newNode = new Node(VAR, token, NULL, NULL);

        // Если токен не является операцией
        if (token != "NOT" && token != "AND" && token != "OR" && token != "XOR" &&
                token != "NAND" && token != "NOR" && token != "EQU") {
            // Считать тип операции текущего узла переменной
            newNode->type = VAR;
            // Добавить название переменной в список переменных
            variables.append(newNode->name);
            // Если токен - операция NOT
        } else if (token == "NOT") {
            // Считать тип операции текущего узла операцией NOT
            newNode->type = NOT;
            // Считать "правым" потомком последний записанный в список узел, извлечь его из списка узлов
            newNode->right = nodeList.takeLast();
            // Формирование имени узла
            // Если правый потомок - переменная, то скобки в названии не нужны
            if (newNode->right->type == VAR)
                // Формирование имени по принципу "тип операции" + пробел + "имя правого потомка"
                newNode->name = token + " " + newNode->right->name;
            // Иначе - добавить скобки к названию
            else
                // Формирование имени по принципу "тип операции" + пробел + "(имя правого потомка)"
                newNode->name = token + " (" + newNode->right->name + ")";
        } else { // Если токен - другой тип операции
            // Присвоить тип операции текущего узла по токену
            newNode->type = static_cast<NodeType>(tokens.indexOf(token) - 1); // Должно было делать чото умнное, но чото не делает
            // Извлечь из списка "правого" потомка - последний записанный в список узел
            newNode->right = nodeList.takeLast();
            // Извлечь из списка "левого" потомка - следующий в списке узел
            newNode->left = nodeList.takeLast();
            // Формирование имени узла по принципу "имя левого потомка" + пробел + "тип операции" + пробел + "имя правого потомка" (добавляем скобки к имени потомков при необходимости)
            // Инициализировать пустую строку
            newNode->name = "";
            // Если левый потомок - переменная, то скобки в названии не нужны
            if (newNode->left->type == VAR)
                newNode->name += newNode->left->name;
            else //  Если левый потомок - любая другая операция, то добавить скобки к его названию
                newNode->name += ("(" + newNode->left->name + ")");
            // Добавить тип операции с пробелами к названию
            newNode->name += (" " + token + " ");
            // Если правый потомок - переменная, то скобки в названии не нужны
            if (newNode->right->type == VAR)
                newNode->name += newNode->right->name;
            else //  Если правый потомок - любая другая операция, то добавить скобки к его названию
                newNode->name += ("(" + newNode->right->name + ")");
        }
        // Добавить текущий узел в список
        nodeList.append(newNode);
    }
    // Вернуть единственный оставшийся узел в списке, являющимся корнем
    return nodeList.last();
}
