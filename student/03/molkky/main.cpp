#include "player.hh"
#include <cstdlib>
#include <iostream>
#include <string>


int main()
{
    Player player1 = Player("Matti");
    Player player2 = Player("Teppo");
    Player* in_turn = 0;

    int turn = 1;
    while (true)
    {
        if (turn % 2 != 0)
        {
            in_turn = &player1;
        }
        else
        {
            in_turn = &player2;
        }

        std::cout << "Enter the score of player " << in_turn->get_name()
                  << " of turn " << turn << ": ";
        int pts = 0;
        std::cin >> pts;

        in_turn->add_points(pts);
        if (in_turn->has_won())
        {
            std::cout << "Game over! The winner is " << in_turn->get_name() << "!" << std::endl;
            return EXIT_SUCCESS;
        }

        std::cout << std::endl;
        std::cout << "Scoreboard after turn " << turn << ":" << std::endl;
        std::cout << player1.get_name() << ": " << player1.get_points() << "p" << std::endl;
        std::cout << player2.get_name() << ": " << player2.get_points() << "p" << std::endl;
        std::cout << std::endl;

        turn += 1;
    }

    return EXIT_SUCCESS;
}
