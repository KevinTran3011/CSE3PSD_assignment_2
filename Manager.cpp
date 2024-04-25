#include <iostream>
#include <string>
#include "TakeAwayChargeVisitor.h" take
#include "Manager.h"
#include "FoodMaker.h"
#include "CoffeeMaker.h"
#include "TeaMaker.h"

class InteractiveManagerTester
{
public:
    void runTests()
    {
        Manager manager;
        Order order;
        TakeawayChargeVisitor takeawayVisitor;
        bool takeaway = false;

        std::cout << "Welcome!\n";
        std::cout << "Do you want to eat in or take away? (Enter 'eat in' or 'take away')\n";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "take away")
        {
            takeaway = true;
        }

        while (true)
        {
            std::cout << "1- Add food\n";
            std::cout << "2- Add drink\n";
            if (order.getTotalItems() > 0)
            {
                std::cout << "3- Pay\n";
            }
            std::cout << "4- Exit and delete order\n";

            int option;
            std::cin >> option;

            if (option == 1)
            {
                // Add food to order
                std::string foodType;
                std::cout << "Enter food type (sandwich or tiramisu): ";
                std::cin >> foodType;

                if (foodType == "sandwich")
                {
                    SandwichMaker *sandwichMaker = new SandwichMaker(takeaway);
                    OrderItem *sandwichItem = manager.createOrderItem(sandwichMaker, nullptr);
                    manager.addItemToOrder(order, sandwichItem);
                    if (takeaway)
                    {
                        sandwichItem->accept(&takeawayVisitor);
                    }
                }
                else if (foodType == "tiramisu")
                {
                    TiramisuMaker *tiramisuMaker = new TiramisuMaker(takeaway);
                    OrderItem *tiramisuItem = manager.createOrderItem(tiramisuMaker, nullptr);
                    manager.addItemToOrder(order, tiramisuItem);
                    if (takeaway)
                    {
                        tiramisuItem->accept(&takeawayVisitor);
                    }
                }
                else
                {
                    std::cout << "Invalid food type. Please enter 'sandwich' or 'tiramisu'.\n";
                    continue;
                }
            }
            else if (option == 2)
            {
                // Add drink to order
                std::string drinkType;
                std::string teaType;
                std::string coffeeType;
                std::string addMilkInput;
                std::string addSugarInput;
                bool addMilk;
                bool addSugar;

                std::cout << "Enter drink type (tea or coffee): ";
                std::cin >> drinkType;

                if (drinkType == "tea")
                {
                    std::cout << "What type of tea (chai or matcha): ";
                    std::cin >> teaType;
                }
                else if (drinkType == "coffee")
                {
                    std::cout << "What type of coffee (black or white): ";
                    std::cin >> coffeeType;
                }
                else
                {
                    std::cout << "Invalid drink type. Please enter 'tea' or 'coffee'.\n";
                    continue;
                }

                std::cout << "Add milk? (Y/N): ";
                std::cin >> addMilkInput;
                addMilk = (addMilkInput == "Y" || addMilkInput == "y");

                std::cout << "Add sugar? (Y/N): ";
                std::cin >> addSugarInput;
                addSugar = (addSugarInput == "Y" || addSugarInput == "y");

                if (drinkType == "tea")
                {
                    TeaMaker *teaMaker = new TeaMaker(teaType, addMilk, addSugar);
                    OrderItem *teaItem = manager.createOrderItem(nullptr, teaMaker);
                    manager.addItemToOrder(order, teaItem);
                    if (takeaway)
                    {
                        teaItem->accept(&takeawayVisitor);
                    }
                }
                else
                {
                    CoffeeMaker *coffeeMaker = new CoffeeMaker(coffeeType, addMilk, addSugar);
                    OrderItem *coffeeItem = manager.createOrderItem(nullptr, coffeeMaker);
                    manager.addItemToOrder(order, coffeeItem);
                    if (takeaway)
                    {
                        coffeeItem->accept(&takeawayVisitor);
                    }
                }
            }
            else if (option == 3 && order.getTotalItems() > 0)
            {
                // Calculate total price
                double totalPrice = manager.calculateTotal(order);
                std::cout << "Total price: " << totalPrice << std::endl;
                break;
            }
            else if (option == 4)
            {
                // Exit and delete order
                break;
            }
        }
    }
};

int main()
{
    InteractiveManagerTester tester;
    tester.runTests();
    return 0;
}