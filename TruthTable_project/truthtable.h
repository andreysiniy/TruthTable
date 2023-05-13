#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H
#include "node.h"
#include <QString>
#include <QStringList>

class TruthTable
{
public:
    Node *root;
    QStringList variables;



    QList<QMap<QString, bool>> generateCombinations(QStringList variables);
    void generateTruthTable(Node *root, QStringList variables, int nodesAmount);

    TruthTable();
};

#endif // TRUTHTABLE_H
