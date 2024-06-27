#ifndef QB_BACKEND_HPP
#define QB_BACKEND_HPP

#include <iostream>
#include "paint.hpp"
#include "QB_Banners.hpp"
#include <vector>
#include <algorithm>
#include <exception>
#include <sstream>
#include <cmath>

using std::istringstream;
using std::vector;
using std::cout, std::cin, std::endl;
using std::cerr;
using std::string;
using std::remove;
using std::getline;
using std::invalid_argument, std::runtime_error;

class QB_BackEnd {
    vector<string> queryList; // Queries Container
    vector<double> answerList; // Output Container
    vector<string> syntaxList; // Contains Help Messages about query Syntax.
    vector<double> leftOperands; // Contains The Operands To The Left Side Of Operator
    vector<char> operators; // Operators Container
    vector<double> rightOperands; //Contains The Operands To The Right Side Of Operator
    vector<string> warningList; // Contains A List Of Warnings To Warn Users About Misuse.
    bool is_compilation_error_encountered = false;

    void interpretQueries() // A Function To Interpret Queries And Then Populate The Respective Containers
    {
        leftOperands.clear();
        operators.clear();
        rightOperands.clear();
        vector<string> copyQueryList = queryList;
        auto removeSpaces = [](vector<string> &copy) {
            char space = ' ';
            for (auto &query: copy)
                query.erase(remove(query.begin(), query.end(), space), query.end());
        };
        auto populateContainers = [&]() {
            istringstream iss;
            double leftOperand = 0;
            double rightOperand = 0;
            char Operator = '\0';
            for (auto &query: copyQueryList) {
                iss.str(query);
                leftOperand = 0;
                rightOperand = 0;
                Operator = '\0';
                iss >> leftOperand >> Operator >> rightOperand;
                leftOperands.emplace_back(leftOperand);
                operators.emplace_back(Operator);
                rightOperands.emplace_back(rightOperand);
                iss.clear();
            }
        };
        removeSpaces(copyQueryList);
        populateContainers();
    }

    static double factorial(double &param) // Calculate Factorial Of +ve Real Numbers Using Gamma Function.
    {
        return tgamma(param + 1);
    }

    static double nCr(double &n, double &r) // Calculate nCr
    {
        double numerator = factorial(n);
        double denominator = factorial(r);
        double x = n - r;
        denominator *= factorial(x);
        return numerator / denominator;
    }

    static double nPr(double &n, double &r) // Calculate nPr
    {
        double numerator = factorial(n);
        double x = n - r;
        double denominator = factorial(x);
        return numerator / denominator;
    }

    void calculate_Answers(double &leftOperand, const char &Operator, double &rightOperand,
                           const int &index) { // Calculate Answers
        if (Operator == '+') {
            double sum = leftOperand + rightOperand;
            answerList.emplace_back(sum);
        } else if (Operator == '-') {
            double diff = leftOperand - rightOperand;
            answerList.emplace_back(diff);
        } else if (Operator == '*') {
            double product = leftOperand * rightOperand;
            answerList.emplace_back(product);
        } else if (Operator == '/') {
            double div = leftOperand / rightOperand;
            answerList.emplace_back(div);
        } else if (Operator == '!') {
            double fact = factorial(leftOperand);
            answerList.emplace_back(fact);
        } else if (Operator == '^') {
            double power = pow(leftOperand, rightOperand);
            answerList.emplace_back(power);
        } else if (Operator == 'R') {
            double rootIndex = 1 / rightOperand;
            double final = pow(leftOperand, rootIndex);
            answerList.emplace_back(final);
        } else if (Operator == 'C') {
            double combination = nCr(leftOperand, rightOperand);
            answerList.emplace_back(combination);
        } else if (Operator == 'P') {
            double permutation = nPr(leftOperand, rightOperand);
            answerList.emplace_back(permutation);
        } else if (Operator == 'L') {
            double log = log10(leftOperand);
            log /= log10(rightOperand);
            answerList.emplace_back(log);
        } else {
            paintText::red();
            cerr << "Compilation Terminated Due To Misunderstood Query Given Below." << endl;
            cerr << "Misunderstood Query: " << queryList[index] << endl;
            cerr << "You Can Correct It In Edit Menu By Providing The Position/Index/ID Of Query In The Edit Menu."
                 << endl;
            cerr << "Query ID For Correction: " << index + 1 << endl << endl;
            is_compilation_error_encountered = true;
            paintText::default_color();
            return;
        }
    }

public:
    QB_BackEnd() {
        syntaxList.emplace_back("Sum Syntax: [Left Operand] + [Right Operand]");
        syntaxList.emplace_back("Subtract Syntax: [Left Operand] - [Right Operand]");
        syntaxList.emplace_back("Product Syntax: [Left Operand] * [Right Operand]");
        syntaxList.emplace_back("Division Syntax: [Left Operand] / [Right Operand] ; [Right Operand] !=  0");
        syntaxList.emplace_back("Factorial Syntax: [Left Operand]! ; [Left Operand] >= 0");
        syntaxList.emplace_back("Power Syntax: [Left Operand] ^ [Right Operand]");
        syntaxList.emplace_back(
                "Root Syntax: [Left Operand] R [Right Operand] ;  [Right Operand]  belongs to Natural Numbers");
        syntaxList.emplace_back(
                "Combination Syntax: [Left Operand] C [Right Operand] ; [Left Operand] >= [Right Operand]");
        syntaxList.emplace_back(
                "Permutation Syntax: [Left Operand] P [Right Operand] ; [Left Operand] >= [Right Operand]");
        syntaxList.emplace_back(
                "Log Syntax: [Left Operand] L [Right Operand] ; [Right Operand] is Base > 0, [Left Operand] > 0");
        syntaxList.emplace_back("Input Stopping Command / Query: end");
        warningList.emplace_back("\nWarnings That Could Be Generated By Compiler:\n");
        warningList.emplace_back(
                "Warning No 1: This Warning Is Related To Misunderstood Query.\n This Happens Only When An Unknown Query Is Encountered By Compiler.\n");
        warningList.emplace_back(
                "Warning No 2: This Warning Is Related To Null / Blank Query List.\n If The Compiler Encounters A Blank Query List Then It Will Print 'Nothing To Compile !' In Red Color.\n");
        warningList.emplace_back(
                "Warning No 3: This Warning Is Also Related To Null / Blank Query List.\n When Query List Is Empty , The Edit Option Will Print Will Print '!** No Queries Found **!' In Red Color.\n");
        warningList.emplace_back(
                "Warning No 4: This Warning Is Related To A Controlled Segmentation Fault\n When Editing A Query You Need To Enter The Correct Index As Flagged By Compiler.\n");
        warningList.emplace_back(
                "Warning No 5: Queries That Contains More Than One Operator Like: [Left Operand] ++ [Right Operand] Will Be \n Ignored By Compiler. Similarly In The Case Of Every Operator.\n  So Please Be Careful While Entering Queries Because This May Lead To Unexpected Result.\n");

    }

    void simulate_queriesInput() { // Simulate Queries Input From User
        queryList.clear();
        int index = 1;
        string query;
        cin.ignore();
        while (true) {
            cout << "Query " << index << ":";
            getline(cin, query);
            if (query == "end") {
                break;
            }
            queryList.emplace_back(query);
            index++;
            query.clear();
        }
    }

    void edit_Query() // edit query at position in case of compilation error
    {
        if (!queryList.empty()) {

            string newQuery;
            size_t pos;
            cout << "\nEnter The Index As Flagged By Compiler During Error: ";
            cin >> pos;
            pos -= 1;
            bool is_pos_out_of_range = pos > queryList.size();
            if (!is_pos_out_of_range) {
                cout << "Query " << pos + 1 << ": ";
                cin.ignore();
                getline(cin, newQuery);
                queryList[pos] = newQuery;
                paintText::green();
                interpretQueries();
                cout << "\nQuery Successfully Updated !";
                cout << "\n Now Try Recompiling All The Queries !\n";
                paintText::default_color();
                return;
            }
            paintText::red();
            cerr << "\n!-- Segmentation Fault: Index Out Of Range ! --!\n";
            paintText::default_color();
            return;
        }
        paintText::red();
        cerr << "\n!** No Queries Found **!\n";
        paintText::default_color();
    }

    static void exit_Calculator() //Show Credits and  Exit Calculator
    {
        auto showCredits = []() {
            paintText::light_green();
            cout << "\n\n\t\t\t** CREDITS **\n";
            cout << "\t\t ** Thank You For Using QB Calculator **\n";
            cout << "\t\t ** Made By Muhammad Talha **\n";
            cout << "\t\t ** Coded In C++ [Version 23] **\n";
            cout << "\t\t ** Source Code Available On GitHub **\n";
            cout << "\t\t ** GUI Version Coming Soon ! **\n";
            cout << "\t\t\t ** CREDITS **\n\n\n";
            paintText::default_color();
        };
        system("cls");
        QB_Banners::credits_Banner();
        showCredits();
    }

    void show_Help_And_Warnings() // Help users About The Syntax Of Queries And Warnings About Misunderstood Queries.
    {
        paintText::gray();
        for (auto &syntax: syntaxList) {
            cout << syntax << endl;
        }
        paintText::light_red();
        for (const auto &warning: warningList) {
            cout << warning << endl;
        }
        paintText::default_color();
    }

    void compile_Queries() // Compile Queries And Then Print The Final Output.
    {
        is_compilation_error_encountered = false;
        answerList.clear();
        if (!queryList.empty()) {
            interpretQueries();
            for (size_t i = 0;
                 i < queryList.size(); ++i) { // because all containers all the same size except the syntax one.
                calculate_Answers(leftOperands.at(i), operators.at(i), rightOperands.at(i), static_cast<int>(i));
            }
            cout << endl;
            auto printOutput = [this]() {
                for (size_t i = 0; i < queryList.size(); ++i) {
                    if (!is_compilation_error_encountered)
                        cout << queryList[i] << " = " << answerList[i] << endl;
                }
            };
            printOutput();
            return;
        }
        paintText::red();
        cerr << "\nNothing To Compile !\n";
        paintText::default_color();
    }

};

#endif
