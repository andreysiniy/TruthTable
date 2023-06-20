#include <QtTest>
#include <../TruthTable_project/truthtable.h>
// add necessary includes here

class generateTruthTable_tests : public QObject
{
    Q_OBJECT

private slots:
    void test_generateTruthTable_twoNodes();
    void test_generateTruthTable_fewNodes();
    void test_generateTruthTable_singleVarOperation();
    void test_generateTruthTable_opTypeNameContainsAnotherOpType();
    void test_generateTruthTable_CLanguageRulesVarName();
};



void generateTruthTable_tests::test_generateTruthTable_twoNodes()
{
    TruthTable input;
    input.nodesAmount = 2;
    input.variables = {"A"};
    Node a(VAR, "A", nullptr, nullptr);
    Node nota(NOT, "NOT A", nullptr, &a);
    input.root = &nota;
    QList<QMap<QString,bool>> expectedList =
    {
        {
            {"A", false},
            {"NOT A", true},
        },
        {
            {"A", true},
            {"NOT A", false},
        },
    };
    QCOMPARE(input.generateTruthTable(), expectedList);
}

void generateTruthTable_tests::test_generateTruthTable_fewNodes()
{
    TruthTable input;
    input.nodesAmount = 5;
    input.variables = {"A","B","C"};
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(AND, "A AND B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node aandborc(OR, "(A AND B) OR C", &aandb, &c);
    input.root = &aandborc;
    QList<QMap<QString,bool>> expectedList =
    {
        {
            {"A", false},
            {"B", false},
            {"C", false},
            {"(A AND B) OR C", false},
            {"A AND B", false}
        },
        {
            {"A", true},
            {"B", false},
            {"C", false},
            {"(A AND B) OR C", false},
            {"A AND B", false}
        },
        {
            {"A", false},
            {"B", true},
            {"C", false},
            {"(A AND B) OR C", false},
            {"A AND B", false}
        },
        {
            {"A", true},
            {"B", true},
            {"C", false},
            {"(A AND B) OR C", true},
            {"A AND B", true}
        },
        {
            {"A", false},
            {"B", false},
            {"C", true},
            {"(A AND B) OR C", true},
            {"A AND B", false}
        },
        {
            {"A", true},
            {"B", false},
            {"C", true},
            {"(A AND B) OR C", true},
            {"A AND B", false}
        },
        {
            {"A", false},
            {"B", true},
            {"C", true},
            {"(A AND B) OR C", true},
            {"A AND B", false}
        },
        {
            {"A", true},
            {"B", true},
            {"C", true},
            {"(A AND B) OR C", true},
            {"A AND B", true}
        }
    };

    QCOMPARE(input.generateTruthTable(), expectedList);
}

void generateTruthTable_tests::test_generateTruthTable_singleVarOperation()
{
    TruthTable input;
    input.nodesAmount = 4;
    input.variables = {"A","B"};
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aORb(OR, "A OR B", &a, &b);
    Node NOTaORb(NOT, "NOT (A OR B)", nullptr, &aORb);
    input.root = &NOTaORb;
    QList<QMap<QString,bool>> expectedList =
    {
        {
            {"A", false},
            {"B", false},
            {"A OR B", false},
            {"NOT (A OR B)", true}
        },
        {
            {"A", true},
            {"B", false},
            {"A OR B", true},
            {"NOT (A OR B)", false}
        },
        {
            {"A", false},
            {"B", true},
            {"A OR B", true},
            {"NOT (A OR B)", false}
        },
        {
            {"A", true},
            {"B", true},
            {"A OR B", true},
            {"NOT (A OR B)", false}
        }
    };
    QCOMPARE(input.generateTruthTable(), expectedList);
}

void generateTruthTable_tests::test_generateTruthTable_opTypeNameContainsAnotherOpType()
{
    TruthTable input;
    input.nodesAmount = 5;
    input.variables = {"A","B","C"};
    Node a(VAR, "A", nullptr, nullptr);
    Node b(VAR, "B", nullptr, nullptr);
    Node aandb(OR, "A OR B", &a, &b);
    Node c(VAR, "C", nullptr, nullptr);
    Node aandborc(NOR, "(A OR B) NOR C", &aandb, &c);
    input.root = &aandborc;
    QList<QMap<QString,bool>> expectedList =
    {
        {
            {"A", false},
            {"B", false},
            {"C", false},
            {"(A OR B) NOR C", true},
            {"A OR B", false}
        },
        {
            {"A", true},
            {"B", false},
            {"C", false},
            {"(A OR B) NOR C", false},
            {"A OR B", true}
        },
        {
            {"A", false},
            {"B", true},
            {"C", false},
            {"(A OR B) NOR C", false},
            {"A OR B", true}
        },
        {
            {"A", true},
            {"B", true},
            {"C", false},
            {"(A OR B) NOR C", false},
            {"A OR B", true}
        },
        {
            {"A", false},
            {"B", false},
            {"C", true},
            {"(A OR B) NOR C", false},
            {"A OR B", false}
        },
        {
            {"A", true},
            {"B", false},
            {"C", true},
            {"(A OR B) NOR C", false},
            {"A OR B", true}
        },
        {
            {"A", false},
            {"B", true},
            {"C", true},
            {"(A OR B) NOR C", false},
            {"A OR B", true}
        },
        {
            {"A", true},
            {"B", true},
            {"C", true},
            {"(A OR B) NOR C", false},
            {"A OR B", true}
        }
    };

    QCOMPARE(input.generateTruthTable(), expectedList);
}

void generateTruthTable_tests::test_generateTruthTable_CLanguageRulesVarName()
{
    TruthTable input;
    input.nodesAmount = 5;
    input.variables = {"A_1","b2","cC3"};
    Node a(VAR, "A_1", nullptr, nullptr);
    Node b(VAR, "b2", nullptr, nullptr);
    Node aandb(OR, "A_1 OR b2", &a, &b);
    Node c(VAR, "cC3", nullptr, nullptr);
    Node aandborc(NOR, "(A_1 OR b2) NOR cC3", &aandb, &c);
    input.root = &aandborc;
    QList<QMap<QString,bool>> expectedList =
    {
        {
            {"A_1", false},
            {"b2", false},
            {"cC3", false},
            {"(A_1 OR b2) NOR cC3", true},
            {"A_1 OR b2", false}
        },
        {
            {"A_1", true},
            {"b2", false},
            {"cC3", false},
            {"(A_1 OR b2) NOR cC3", false},
            {"A_1 OR b2", true}
        },
        {
            {"A_1", false},
            {"b2", true},
            {"cC3", false},
            {"(A_1 OR b2) NOR cC3", false},
            {"A_1 OR b2", true}
        },
        {
            {"A_1", true},
            {"b2", true},
            {"cC3", false},
            {"(A_1 OR b2) NOR cC3", false},
            {"A_1 OR b2", true}
        },
        {
            {"A_1", false},
            {"b2", false},
            {"cC3", true},
            {"(A_1 OR b2) NOR cC3", false},
            {"A_1 OR b2", false}
        },
        {
            {"A_1", true},
            {"b2", false},
            {"cC3", true},
            {"(A_1 OR b2) NOR cC3", false},
            {"A_1 OR b2", true}
        },
        {
            {"A_1", false},
            {"b2", true},
            {"cC3", true},
            {"(A_1 OR b2) NOR cC3", false},
            {"A_1 OR b2", true}
        },
        {
            {"A_1", true},
            {"b2", true},
            {"cC3", true},
            {"(A_1 OR b2) NOR cC3", false},
            {"A_1 OR b2", true}
        }
    };

    QCOMPARE(input.generateTruthTable(), expectedList);
}


QTEST_APPLESS_MAIN(generateTruthTable_tests)

#include "tst_generatetruthtable_tests.moc"
