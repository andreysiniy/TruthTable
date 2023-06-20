#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H
#include "node.h"
#include "errorhandler.h"
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>

class TruthTable
{
public:
    Node *root;
    QStringList variables;
    int nodesAmount;


    QList<QMap<QString, bool>> generateCombinations();
    QList<QMap<QString, bool>> generateTruthTable();
    void writeTruthTableToCSV(const QList<QMap<QString, bool>>& truthTable, const QString& fileName);

    TruthTable();
};

#endif // TRUTHTABLE_H
