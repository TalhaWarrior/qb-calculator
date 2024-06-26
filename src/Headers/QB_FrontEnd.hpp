#ifndef QB_FRONTEND_HPP
#define QB_FRONTEND_HPP

#include "../Headers/QB_BackEnd.hpp"
#include "../Headers/QB_Banners.hpp"
#include<chrono>
#include<thread>

using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

class QB_FrontEnd : private QB_BackEnd {
    int mainMenuChoice;

    static void clearScreen() {
        system("cls");
    }

    static void countdown() {
        std::cout << "Exiting in " << 5 << " seconds" << std::flush;
        for (int i = 5 - 1; i >= 0; --i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "\rExiting in " << i << " seconds" << std::flush;
        }
        std::cout << "\n";
    }

    bool is_run = false;
public:
    [[nodiscard]] bool isRunning() const {
        return is_run;
    }

    QB_FrontEnd() {
        mainMenuChoice = 0;
        is_run = true;
    }

    void mainMenu() {
        loopMenu:
        system("cls");
        QB_Banners::calculator_Banner();
        paintText::green();
        cout << "\n**** Welcome to Query Based Calculator ****\n";
        cout << "\tWhere Queries Are Written To Fetch Calculations !\n\n";
        paintText::red();
        cout << "TIP: If You Are Using This Calculator For First Time Then Consider Using 'General Help' Menu !\n\n";
        paintText::green();
        cout << "Use The Following Options To Navigate Through Different Menus\n\n";
        paintText::default_color();
        cout << "\t      *** MAIN MENU OPTIONS *** \n";
        cout << "\t1. Query Pad ** Where Queries Are Written **\n";
        cout << "\t2. General Help ** To Know About How To Use This Calculator **\n";
        cout << "\t3. Compile Queries ** To Compile Queries And Print Output **\n";
        cout << "\t4. Edit Query ** In Order Of Misunderstood Query Error **\n";
        cout << "\t5. Exit ** To Exit The Program **\n\n";
        paintText::red();
        cout
                << "!-- Avoid Entering A Character As Choice Input --!\n ** If You Don't Trust Me Then Give It A Try And See Yourself **. \n\n";
        paintText::default_color();
        cout << "Enter Your Choice : ";
        cin >> mainMenuChoice;
        if (mainMenuChoice != 1 && mainMenuChoice != 2 && mainMenuChoice != 3 && mainMenuChoice != 4 &&
            mainMenuChoice != 5) {
            paintText::red();
            cout << "\nUnrecognized Option Encountered !! ";
            cout << "Try Entering Correct Option Again !\n";
            paintText::default_color();
            sleep_for(milliseconds(250));
            system("cls");
            goto loopMenu;
        }
    }

    void subMenu() {
        auto queryPad = [this]() {
            clearScreen();
            QB_Banners::queryPad_Banner();
            paintText::light_green();
            cout << "\n** This Is The Query Pad **\n\t Here Queries Are Fed By User To Calculator\n";
            simulate_queriesInput();
        };
        auto syntaxHelp = [this]() {
            clearScreen();
            QB_Banners::syntaxHelp_Banner();
            cout << "\n\n";
            show_Help_And_Warnings();
            paintText::green();
            cout << "\n!-- Press Any Key To Go Back To Main Menu --!";
            system("pause > 0");
        };

        auto compileInput = [this]() {
            clearScreen();
            QB_Banners::output_Banner();
            paintText::light_green();
            compile_Queries();
            paintText::default_color();
            cout << "\n!-- Press Any Key To Go Back To Main Menu --!";
            system("pause > 0");
        };

        auto edit = [this]() {
            clearScreen();
            QB_Banners::editMenu_Banner();
            edit_Query();
            cout << "\n!-- Press Any Key To Go Back To Main Menu --!";
            system("pause > 0");
        };
        bool is_not_quiting = false;
        auto quit = [&]() {
            clearScreen();
            QB_Banners::exit_Banner();
            paintText::light_yellow();
            char surety;
            cout << "\nDo You Really Want To Exit ? (Y/N) : ";
            cin >> surety;
            if (surety == 'Y' || surety == 'y') {
                exit_Calculator();
                is_run = false;
            } else
                is_not_quiting = true;
        };
        auto handleSubMenuType = [&]() {
            if (mainMenuChoice == 1)
                queryPad();
            else if (mainMenuChoice == 2)
                syntaxHelp();
            else if (mainMenuChoice == 3)
                compileInput();
            else if (mainMenuChoice == 4)
                edit();
            else if (mainMenuChoice == 5) {
                quit();
                if (!is_not_quiting) {
                    paintText::red();
                    countdown();
                    paintText::default_color();
                    exit(0);
                }
            }
        };
        handleSubMenuType();
    }
};

#endif
