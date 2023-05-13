#include <QCoreApplication>
#include "node.h"
#include "truthtable.h"


int main(int argc, char *argv[])
{
    QCoreApplication aa(argc, argv);

    Node *a = new Node(VAR, "a");
    Node *notA = new Node(NOT, "NOT a", a);
    Node *b = new Node(VAR, "b");
    Node *andBnotA = new Node(AND, "NOT a AND b", notA, b);

    QStringList variables = {"a", "b"};
    TruthTable cool;
    cool.root = andBnotA;
    cool.variables = variables;

    cool.generateTruthTable(andBnotA, variables, 4);

    return aa.exec();
}
