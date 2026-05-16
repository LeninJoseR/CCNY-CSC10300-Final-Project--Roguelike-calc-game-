#include "game.h"

int main() {
    // makes random stuff actually random
    srand(time(0));

    // shows the title
    printTitle();

    // asks for your name
    string name;
    cout << "What is your name? ";
    getline(cin, name);

    // if they type nothing it just says Student
    if (name == "") {
        name = "Student";
    }

    // makes the player
    Player player(name);

    // starts the story
    intro();

    // these are the 20 rounds
    for (int round = 1; round <= 20; round++) {
        // if you die then stop
        if (player.hp <= 0) {
            break;
        }

        // shows the menu
        mainMenu(player, round);
        pause();
    }

    // if you live you take the final
    if (player.hp > 0) {
        finalExam(player);
    }

    // if you died you get the bad ending
    if (player.hp <= 0) {
        badEnding(player);
    }

    return 0;
}
