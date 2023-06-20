#include <QtTest>
#include <../TruthTable_project/node.h>

// add necessary includes here

class evaluate_tests : public QObject
{
    Q_OBJECT

private slots:
    void test_evaluate_singleVarOperation();
    void test_evaluate_twoVarOperation();
    void test_evaluate_fewVariables();
    void test_evaluate_singleNode();
    void test_evaluate_fewOperationsDepth();
    void test_evaluate_variablesValueZeros();
    void test_evaluate_variablesValueOnes();
    void test_evaluate_variablesValueCombined();

};

void evaluate_tests::test_evaluate_singleVarOperation()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node nota(NOT, "NOT A", nullptr, &a);
    QMap<QString, bool> combo;
    combo["A"] = false;
    QCOMPARE(nota.evaluate(&nota, combo), true);
}

void evaluate_tests::test_evaluate_twoVarOperation()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    QMap<QString, bool> combo;
    combo["A"] = false;
    combo["B"] = true;
    QCOMPARE(aandb.evaluate(&aandb, combo), false);
}

void evaluate_tests::test_evaluate_fewVariables()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    QMap<QString, bool> combo;
    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);
    combo["A"] = true;
    combo["B"] = false;
    combo["C"] = true;
    QCOMPARE(aandborc.evaluate(&aandborc, combo), true);
}

void evaluate_tests::test_evaluate_singleNode()
{
    Node a(VAR, "A", nullptr, nullptr);
    QMap<QString, bool> combo;
    combo["A"] = false;
    QCOMPARE(a.evaluate(&a, combo), false);
}

void evaluate_tests::test_evaluate_fewOperationsDepth()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node d(VAR, "D", nullptr, nullptr);
    QMap<QString, bool> combo;
    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);
    Node aandborcxord(XOR, "((A AND B) OR C) XOR D", &aandborc, &d);
    combo["A"] = false;
    combo["B"] = true;
    combo["C"] = true;
    combo["D"] = true;
    QCOMPARE(aandborcxord.evaluate(&aandborcxord, combo), false);
}

void evaluate_tests::test_evaluate_variablesValueZeros()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node d(VAR, "D", nullptr, nullptr);
    QMap<QString, bool> combo;
    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);
    Node aandborcxord(XOR, "((A AND B) OR C) XOR D", &aandborc, &d);
    combo["A"] = false;
    combo["B"] = false;
    combo["C"] = false;
    combo["D"] = false;
    QCOMPARE(aandborcxord.evaluate(&aandborcxord, combo), false);
}

void evaluate_tests::test_evaluate_variablesValueOnes()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node d(VAR, "D", nullptr, nullptr);
    QMap<QString, bool> combo;
    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);
    Node aandborcxord(XOR, "((A AND B) OR C) XOR D", &aandborc, &d);
    combo["A"] = true;
    combo["B"] = true;
    combo["C"] = true;
    combo["D"] = true;
    QCOMPARE(aandborcxord.evaluate(&aandborcxord, combo), false);
}

void evaluate_tests::test_evaluate_variablesValueCombined()
{
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node d(VAR, "D", nullptr, nullptr);
    QMap<QString, bool> combo;
    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);
    Node aandborcxord(XOR, "((A AND B) OR C) XOR D", &aandborc, &d);
    combo["A"] = false;
    combo["B"] = true;
    combo["C"] = false;
    combo["D"] = true;
    QCOMPARE(aandborcxord.evaluate(&aandborcxord, combo), true);
}

QTEST_APPLESS_MAIN(evaluate_tests)

#include "tst_evaluate_tests.moc"
