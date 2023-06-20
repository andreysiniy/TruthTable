#include <QtTest>
#include <../TruthTable_project/truthtable.h>
// add necessary includes here

class generateCombinations_tests : public QObject
{
    Q_OBJECT


private slots:
    void test_generateCombinations_singleVariable();
    void test_generateCombinations_fewVariables();
    void test_generateCombinations_variablesNamesCLanguage();
};



void generateCombinations_tests::test_generateCombinations_singleVariable()
{
    TruthTable input;
    input.variables = {"A"};
    QList<QMap<QString,bool>> expectedList;
    QMap<QString,bool> combination1;
    combination1["A"] = false;
    expectedList.append(combination1);
    QMap<QString,bool> combination2;
    combination2["A"] = true;
    expectedList.append(combination2);

    QCOMPARE(input.generateCombinations(), expectedList);
}

void generateCombinations_tests::test_generateCombinations_fewVariables()
{
    TruthTable input;
    input.variables = {"A","B","C"};
    QList<QMap<QString,bool>> expectedList =
    {
        {
            {"A", false},
            {"B", false},
            {"C", false}
        },
        {
            {"A", true},
            {"B", false},
            {"C", false}
        },
        {
            {"A", false},
            {"B", true},
            {"C", false},
        },
        {
            {"A", true},
            {"B", true},
            {"C", false},
        },
        {
            {"A", false},
            {"B", false},
            {"C", true},
        },
        {
            {"A", true},
            {"B", false},
            {"C", true},
        },
        {
            {"A", false},
            {"B", true},
            {"C", true},
        },
        {
            {"A", true},
            {"B", true},
            {"C", true},
        }
    };


    QCOMPARE(input.generateCombinations(), expectedList);
}

void generateCombinations_tests::test_generateCombinations_variablesNamesCLanguage()
{
    TruthTable input;
    input.variables = {"a1","B_2","Cc"};
    QList<QMap<QString,bool>> expectedList =
    {
        {
            {"a1", false},
            {"B_2", false},
            {"Cc", false}
        },
        {
            {"a1", true},
            {"B_2", false},
            {"Cc", false}
        },
        {
            {"a1", false},
            {"B_2", true},
            {"Cc", false},
        },
        {
            {"a1", true},
            {"B_2", true},
            {"Cc", false},
        },
        {
            {"a1", false},
            {"B_2", false},
            {"Cc", true},
        },
        {
            {"a1", true},
            {"B_2", false},
            {"Cc", true},
        },
        {
            {"a1", false},
            {"B_2", true},
            {"Cc", true},
        },
        {
            {"a1", true},
            {"B_2", true},
            {"Cc", true},
        }
    };


    QCOMPARE(input.generateCombinations(), expectedList);
}

QTEST_APPLESS_MAIN(generateCombinations_tests)

#include "tst_generatecombinations_tests.moc"
