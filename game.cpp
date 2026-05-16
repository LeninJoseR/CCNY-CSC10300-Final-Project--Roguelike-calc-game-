#include "game.h"

// shows the title
void printTitle() {
    cout << endl;
    cout << "==========================================" << endl;
    cout << "        CALCULUS EQUATION FIGHT" << endl;
    cout << "==========================================" << endl;
    cout << "     +    -    *    /    dx    integral" << endl;
    cout << endl;
}

// shows the final exam picture
void printFinalArt() {
    cout << endl;
    cout << "  __________________________" << endl;
    cout << " |                          |" << endl;
    cout << " |       FINAL EXAM         |" << endl;
    cout << " |   CALC 1 + CALC 2 + 3    |" << endl;
    cout << " |__________________________|" << endl;
    cout << endl;
}

// waits for enter
void pause() {
    cout << endl;
    cout << "Press ENTER to keep going...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// fixes bad typing
void fixInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// gets a number choice
int getChoice(int low, int high) {
    int choice;

    while (true) {
        cout << "> ";
        cin >> choice;

        // if input runs out
        if (cin.eof()) {
            cout << endl << "No more input. Game closed." << endl;
            exit(0);
        }

        // if they type letters
        if (cin.fail()) {
            fixInput();
            cout << "Please type a number." << endl;
        } else if (choice < low || choice > high) {
            fixInput();
            cout << "Pick a number from " << low << " to " << high << "." << endl;
        } else {
            fixInput();
            return choice;
        }
    }
}

// random number from 1 to high
int randomNumber(int high) {
    return rand() % high + 1;
}

// shows your stats
void showStats(Player player) {
    cout << endl;
    cout << "Name: " << player.name << endl;
    cout << "Level: " << player.level << endl;
    cout << "XP: " << player.xp << "/40" << endl;
    cout << "HP: " << player.hp << endl;
    cout << "Focus: " << player.focus << endl;
    cout << "Score: " << player.score << endl;
}

// shows your items
void showItems(Player player) {
    cout << endl;
    cout << "Items:" << endl;

    for (int i = 0; i < (int)player.items.size(); i++) {
        cout << i + 1 << ". " << player.items[i] << endl;
    }
}

// explains the game
void showHelp() {
    cout << endl;
    cout << "How to play:" << endl;
    cout << "Answer calculus questions to hurt the equation." << endl;
    cout << "When you choose fight, the Calc 1, 2, or 3 topic is random." << endl;
    cout << "If the equation is still alive, it attacks you." << endl;
    cout << "Winning fights gives XP and levels." << endl;
    cout << "Resting helps HP, but it does not give XP." << endl;
    cout << "Some equations drop hint cards and answer keys." << endl;
    cout << "Later rounds have stronger equations." << endl;
    cout << "Try to survive 20 rounds and beat the final exam." << endl;
}

// intro story
void intro() {
    cout << "You are studying for a calculus final." << endl;
    cout << "The review sheet becomes alive." << endl;
    cout << "Now you have to fight random Calc 1, Calc 2, and Calc 3 equations." << endl;
    cout << "This is simple. Just survive and get a good score." << endl;
    pause();
}

// menu for each round
void mainMenu(Player &player, int round) {
    cout << endl;
    cout << "--------------- ROUND " << round << " OF 20 ---------------" << endl;
    showStats(player);

    cout << endl;
    cout << "Choose what to do:" << endl;
    cout << "1. Fight a random Calc 1, 2, or 3 equation" << endl;
    cout << "2. Rest" << endl;
    cout << "3. Find an item" << endl;
    cout << "4. Calculator guessing game" << endl;
    cout << "5. Show inventory and help" << endl;

    int choice = getChoice(1, 5);

    // does whatever number you picked
    if (choice == 1) {
        randomFight(player, round);
    } else if (choice == 2) {
        rest(player);
    } else if (choice == 3) {
        findItem(player);
    } else if (choice == 4) {
        randomMiniGame(player);
    } else {
        showItems(player);
        showHelp();
    }
}

// picks a random calc fight
void randomFight(Player &player, int round) {
    int num = randomNumber(3);
    Enemy enemy = getCalc1Enemy();

    // picks the random calc topic
    if (num == 1) {
        cout << "Random topic: Calc 1" << endl;
        enemy = getCalc1Enemy();
    } else if (num == 2) {
        cout << "Random topic: Calc 2" << endl;
        enemy = getCalc2Enemy();
    } else {
        cout << "Random topic: Calc 3" << endl;
        enemy = getCalc3Enemy();
    }

    // later rounds get harder
    makeHarder(enemy, round);
    fight(player, enemy);
}

// random Calc 1 enemy
Enemy getCalc1Enemy() {
    int num = randomNumber(10);

    if (num == 1) {
        return Enemy("Calc 1 Limit", "lim x->0 sin(x)/x = ?", "1",
                     "0", "1", "does not exist", 2, 1, 20, 7);
    } else if (num == 2) {
        return Enemy("Calc 1 Derivative", "d/dx of x^3 = ?", "3x^2",
                     "x^2", "3x^2", "x^3", 2, 1, 22, 8);
    } else if (num == 3) {
        return Enemy("Calc 1 Integral", "integral of 2x dx = ?", "x^2+c",
                     "2", "x^2+c", "2x+c", 2, 1, 22, 8);
    } else if (num == 4) {
        return Enemy("Calc 1 Critical Point", "critical points happen when f'(x) = ?", "0",
                     "0", "1", "infinity", 1, 1, 24, 9);
    } else if (num == 5) {
        return Enemy("Calc 1 Chain Rule", "d/dx of sin(x^2) = ?", "2xcos(x^2)",
                     "cos(x^2)", "2xcos(x^2)", "2xsin(x)", 2, 1, 25, 10);
    } else if (num == 6) {
        return Enemy("Calc 1 Slope", "slope of y = 5x + 2 is ?", "5",
                     "2", "5", "7", 2, 1, 21, 8);
    } else if (num == 7) {
        return Enemy("Calc 1 Power Rule", "d/dx of x^5 = ?", "5x^4",
                     "x^4", "5x^4", "5x^5", 2, 1, 24, 9);
    } else if (num == 8) {
        return Enemy("Calc 1 Second Derivative", "if f(x)=x^3, f''(x)=?", "6x",
                     "3x^2", "6x", "6", 2, 1, 26, 10);
    } else if (num == 9) {
        return Enemy("Calc 1 Tangent Line", "a tangent line uses the function value and what?", "derivative",
                     "integral", "derivative", "series", 2, 1, 24, 9);
    } else {
        return Enemy("Calc 1 Area", "an integral can find area under a what?", "curve",
                     "point", "curve", "slope", 2, 1, 23, 9);
    }
}

// random Calc 2 enemy
Enemy getCalc2Enemy() {
    int num = randomNumber(10);

    if (num == 1) {
        return Enemy("Calc 2 U Sub", "using u in an integral is called what?", "u-sub",
                     "u-sub", "chain rule", "dot product", 1, 2, 26, 10);
    } else if (num == 2) {
        return Enemy("Calc 2 Series", "first term of e^x Maclaurin series = ?", "1",
                     "x", "0", "1", 3, 2, 27, 10);
    } else if (num == 3) {
        return Enemy("Calc 2 Geometric Series", "geometric series converges when |r| < ?", "1",
                     "1", "0", "10", 1, 2, 28, 11);
    } else if (num == 4) {
        return Enemy("Calc 2 Parts", "integration by parts starts with what two letters?", "uv",
                     "dx", "uv", "du", 2, 2, 29, 11);
    } else if (num == 5) {
        return Enemy("Calc 2 Polar Area", "polar area uses r to what power?", "2",
                     "1", "2", "3", 2, 2, 30, 12);
    } else if (num == 6) {
        return Enemy("Calc 2 Divergence Test", "if terms do not go to 0, the series does what?", "diverges",
                     "converges", "diverges", "equals 1", 2, 2, 31, 12);
    } else if (num == 7) {
        return Enemy("Calc 2 Ratio Test", "ratio test uses the limit of a(n+1) over what?", "a(n)",
                     "a(n)", "x", "dx", 1, 2, 32, 12);
    } else if (num == 8) {
        return Enemy("Calc 2 Trig Integral", "integral of cos(x) dx = ?", "sin(x)+c",
                     "sin(x)+c", "-sin(x)+c", "cos(x)+c", 1, 2, 30, 11);
    } else if (num == 9) {
        return Enemy("Calc 2 Taylor", "Taylor series uses derivatives at a what?", "point",
                     "vector", "point", "matrix", 2, 2, 33, 13);
    } else {
        return Enemy("Calc 2 Improper Integral", "an improper integral has infinity or a bad what?", "discontinuity",
                     "slope", "discontinuity", "variable", 2, 2, 34, 13);
    }
}

// random Calc 3 enemy
Enemy getCalc3Enemy() {
    int num = randomNumber(10);

    if (num == 1) {
        return Enemy("Calc 3 Partial Derivative", "partial derivative symbol looks like what letter?", "d",
                     "d", "x", "r", 1, 3, 31, 12);
    } else if (num == 2) {
        return Enemy("Calc 3 Gradient", "gradient points in direction of fastest what?", "increase",
                     "decrease", "increase", "rotation", 2, 3, 32, 12);
    } else if (num == 3) {
        return Enemy("Calc 3 Dot Product", "dot product of perpendicular vectors = ?", "0",
                     "0", "1", "-1", 1, 3, 33, 13);
    } else if (num == 4) {
        return Enemy("Calc 3 Double Integral", "double integrals can find area or what?", "volume",
                     "slope", "volume", "derivative", 2, 3, 34, 13);
    } else if (num == 5) {
        return Enemy("Calc 3 Variables", "Calc 3 usually has more than one what?", "variable",
                     "variable", "answer", "textbook", 1, 3, 35, 14);
    } else if (num == 6) {
        return Enemy("Calc 3 Cross Product", "cross product makes a vector perpendicular to the two original what?", "vectors",
                     "numbers", "vectors", "graphs", 2, 3, 36, 14);
    } else if (num == 7) {
        return Enemy("Calc 3 Level Curve", "a level curve keeps z equal to a constant what?", "value",
                     "value", "slope", "integral", 1, 3, 35, 13);
    } else if (num == 8) {
        return Enemy("Calc 3 Triple Integral", "triple integrals often find 3D what?", "volume",
                     "volume", "slope", "limit", 1, 3, 38, 15);
    } else if (num == 9) {
        return Enemy("Calc 3 Directional Derivative", "directional derivative uses gradient dot a unit what?", "vector",
                     "vector", "circle", "series", 1, 3, 37, 15);
    } else {
        return Enemy("Calc 3 Max Min", "Calc 3 max/min problems can use Lagrange what?", "multipliers",
                     "multipliers", "rectangles", "polars", 1, 3, 40, 16);
    }
}

// final boss question
Enemy getFinalEnemy() {
    return Enemy("Final Exam Equation",
                 "d/dx of x^2 plus dot product of perpendicular vectors = ?",
                 "2x+0", "2x+0", "x^2+1", "0", 1, 4, 75, 15);
}

// makes enemies stronger later
void makeHarder(Enemy &enemy, int round) {
    int bonus = round / 4;

    enemy.hp = enemy.hp + bonus * 3;
    enemy.attack = enemy.attack + bonus;
}

// fight loop
void fight(Player &player, Enemy enemy) {
    cout << endl;
    cout << "A " << enemy.name << " appears!" << endl;

    while (player.hp > 0 && enemy.hp > 0) {
        cout << endl;
        cout << enemy.name << " HP: " << enemy.hp << endl;
        cout << "1. Answer the question" << endl;
        cout << "2. Use an item" << endl;
        cout << "3. Random guess attack" << endl;

        int choice = getChoice(1, 3);

        // answer, use item, or guess
        if (choice == 1) {
            answerQuestion(player, enemy);
        } else if (choice == 2) {
            useItem(player, enemy);
        } else {
            int damage = randomNumber(12);
            cout << "You guessed and did " << damage << " damage." << endl;
            enemy.hp = enemy.hp - damage;
            addFocus(player, -5);
        }

        // if it is alive it hits you
        if (enemy.hp > 0) {
            enemyAttack(player, enemy);
        }
    }

    // after you win, get rewards
    if (player.hp > 0) {
        winBattle(player, enemy);
    }
}

// asks the question
void answerQuestion(Player &player, Enemy &enemy) {
    cout << endl;
    cout << enemy.question << endl;
    cout << "1. " << enemy.choice1 << endl;
    cout << "2. " << enemy.choice2 << endl;
    cout << "3. " << enemy.choice3 << endl;

    int answer = getChoice(1, 3);

    // right answer does damage
    if (answer == enemy.rightChoice) {
        int damage = 15 + randomNumber(8) + player.level * 3;
        cout << "Correct! You did " << damage << " damage." << endl;
        enemy.hp = enemy.hp - damage;
        addFocus(player, 3);
    } else {
        cout << "Wrong. The answer was " << enemy.answer << "." << endl;
        addFocus(player, -8);
    }

    // if it lives, change question
    if (enemy.hp > 0) {
        changeQuestion(enemy);
    }
}

// changes question but keeps hp
void changeQuestion(Enemy &enemy) {
    int oldHp = enemy.hp;
    int oldAttack = enemy.attack;
    string oldQuestion = enemy.question;
    Enemy newEnemy = enemy;

    // tries not to repeat
    for (int i = 0; i < 10; i++) {
        if (enemy.level == 1) {
            newEnemy = getCalc1Enemy();
        } else if (enemy.level == 2) {
            newEnemy = getCalc2Enemy();
        } else if (enemy.level == 3) {
            newEnemy = getCalc3Enemy();
        } else {
            newEnemy = getFinalEnemy();
        }

        if (newEnemy.question != oldQuestion) {
            break;
        }
    }

    enemy.name = newEnemy.name;
    enemy.question = newEnemy.question;
    enemy.answer = newEnemy.answer;
    enemy.choice1 = newEnemy.choice1;
    enemy.choice2 = newEnemy.choice2;
    enemy.choice3 = newEnemy.choice3;
    enemy.rightChoice = newEnemy.rightChoice;
    enemy.level = newEnemy.level;
    enemy.hp = oldHp;
    enemy.attack = oldAttack;

    cout << "The equation changes into a new question." << endl;
}

// uses an item
void useItem(Player &player, Enemy &enemy) {
    cout << endl;

    // these are the best items
    if (hasItem(player, "answer key")) {
        cout << "You used an answer key. Correct choice: " << enemy.rightChoice << endl;
        cout << "It also does 25 damage." << endl;
        enemy.hp = enemy.hp - 25;
        removeItem(player, "answer key");
    } else if (hasItem(player, "hint card")) {
        cout << "You used a hint card." << endl;
        cout << "Hint: the answer is choice " << enemy.rightChoice << "." << endl;
        cout << "The hint card does 10 damage." << endl;
        enemy.hp = enemy.hp - 10;
        removeItem(player, "hint card");
    } else if (hasItem(player, "derivative sheet") && enemy.name.find("Derivative") != string::npos) {
        cout << "You used the derivative sheet. 22 damage." << endl;
        enemy.hp = enemy.hp - 22;
    } else if (hasItem(player, "integral sheet") && enemy.name.find("Integral") != string::npos) {
        cout << "You used the integral sheet. 22 damage." << endl;
        enemy.hp = enemy.hp - 22;
    } else if (hasItem(player, "vector sheet") && enemy.name.find("Calc 3") != string::npos) {
        cout << "You used the vector sheet. 22 damage." << endl;
        enemy.hp = enemy.hp - 22;
    } else {
        cout << "You used your pencil. 6 damage." << endl;
        enemy.hp = enemy.hp - 6;
    }
}

// enemy hits you
void enemyAttack(Player &player, Enemy enemy) {
    int damage = enemy.attack + randomNumber(4);
    cout << "The equation attacks you for " << damage << " damage." << endl;
    addHp(player, -damage);
}

// gives score xp and drops
void winBattle(Player &player, Enemy enemy) {
    int points = 10;

    // harder calc gives more points
    if (enemy.name.find("Calc 2") != string::npos) {
        points = 15;
    }

    if (enemy.name.find("Calc 3") != string::npos) {
        points = 20;
    }

    if (enemy.name.find("Final") != string::npos) {
        points = 50;
    }

    cout << endl;
    cout << "You beat " << enemy.name << "!" << endl;
    cout << "You got " << points << " points." << endl;

    player.score = player.score + points;
    addXp(player, points);
    getDrop(player, enemy);
    addFocus(player, 5);
}

// heals but no xp
void rest(Player &player) {
    cout << endl;
    cout << "You rest for a little bit." << endl;
    cout << "HP +12 and Focus +10" << endl;
    addHp(player, 12);
    addFocus(player, 10);
}

// finds random item
void findItem(Player &player) {
    cout << endl;

    int num = randomNumber(6);

    if (num == 1) {
        cout << "You found a derivative sheet." << endl;
        player.items.push_back("derivative sheet");
    } else if (num == 2) {
        cout << "You found an integral sheet." << endl;
        player.items.push_back("integral sheet");
    } else if (num == 3) {
        cout << "You found a vector sheet." << endl;
        player.items.push_back("vector sheet");
    } else if (num == 4) {
        cout << "You found coffee. Focus +15." << endl;
        addFocus(player, 15);
    } else if (num == 5) {
        cout << "You found a hint card." << endl;
        player.items.push_back("hint card");
    } else {
        cout << "You found an answer key." << endl;
        player.items.push_back("answer key");
    }
}

// random mini game
void randomMiniGame(Player &player) {
    cout << endl;
    cout << "Calculator guessing game!" << endl;
    cout << "Guess a number from 1 to 5." << endl;

    int secret = randomNumber(5);
    int guess = getChoice(1, 5);

    if (guess == secret) {
        cout << "You got it right. Score +15." << endl;
        player.score = player.score + 15;
    } else {
        cout << "Wrong. The number was " << secret << "." << endl;
        cout << "HP -8." << endl;
        addHp(player, -8);
    }
}

// final after 20 rounds
void finalExam(Player &player) {
    printFinalArt();
    cout << "You survived the 20 rounds." << endl;

    // so you cant just rest the whole time
    if (player.level < 4) {
        cout << "But you are only level " << player.level << "." << endl;
        cout << "You rested too much and did not practice enough equations." << endl;
        cout << "Now you fail" << endl;
        
        
        player.hp = 0;
        return;
    }

    cout << "Now you have to fight the final exam equation." << endl;

    Enemy finalEnemy = getFinalEnemy();
    fight(player, finalEnemy);

    if (player.hp > 0 && player.score >= 160) {
        goodEnding(player);
    } else if (player.hp > 0) {
        normalEnding(player);
    }
}

// normal win
void normalEnding(Player player) {
    cout << endl;
    cout << "ENDING: You passed the calculus final." << endl;
    cout << "Final score: " << player.score << endl;
}

// better win
void goodEnding(Player player) {
    cout << endl;
    cout << "ENDING: You did really good on the calculus final." << endl;
    cout << "Final score: " << player.score << endl;
}

// lose ending
void badEnding(Player player) {
    cout << endl;
    cout << "ENDING: The calculus equations beat you." << endl;
    cout << "You failed your calc final" << endl;
    cout << "Your mom say you had one job" << endl;
    cout << "Final score: " << player.score << endl;
}

// checks for item
bool hasItem(Player player, string item) {
    for (int i = 0; i < (int)player.items.size(); i++) {
        if (player.items[i] == item) {
            return true;
        }
    }

    return false;
}

// deletes used item
void removeItem(Player &player, string item) {
    for (int i = 0; i < (int)player.items.size(); i++) {
        if (player.items[i] == item) {
            player.items.erase(player.items.begin() + i);
            return;
        }
    }
}

// makes text easier to check
string lowerNoSpaces(string word) {
    string newWord = "";

    for (int i = 0; i < (int)word.length(); i++) {
        char letter = word[i];

        if (letter != ' ') {
            if (letter >= 'A' && letter <= 'Z') {
                letter = letter + 32;
            }

            newWord = newWord + letter;
        }
    }

    return newWord;
}

// changes hp
void addHp(Player &player, int amount) {
    player.hp = player.hp + amount;

    if (player.hp > player.maxHp) {
        player.hp = player.maxHp;
    }
}

// changes focus
void addFocus(Player &player, int amount) {
    player.focus = player.focus + amount;

    if (player.focus > 100) {
        player.focus = 100;
    }

    if (player.focus < 0) {
        player.focus = 0;
    }
}

// adds xp
void addXp(Player &player, int amount) {
    player.xp = player.xp + amount;
    cout << "XP +" << amount << endl;

    // 40 xp equals 1 level
    while (player.xp >= 40) {
        player.xp = player.xp - 40;
        player.level = player.level + 1;
        player.maxHp = player.maxHp + 10;
        player.hp = player.maxHp;
        player.focus = 100;

        cout << "LEVEL UP! You are now level " << player.level << "." << endl;
        cout << "Your max HP went up and your HP/focus refilled." << endl;
    }
}

// random drop after fight
void getDrop(Player &player, Enemy enemy) {
    int num = randomNumber(6);

    if (num == 1) {
        cout << enemy.name << " dropped a hint card." << endl;
        player.items.push_back("hint card");
    } else if (num == 2) {
        cout << enemy.name << " dropped an answer key." << endl;
        player.items.push_back("answer key");
    } else if (num == 3 && enemy.name.find("Derivative") != string::npos) {
        cout << enemy.name << " dropped a derivative sheet." << endl;
        player.items.push_back("derivative sheet");
    } else if (num == 4 && enemy.name.find("Integral") != string::npos) {
        cout << enemy.name << " dropped an integral sheet." << endl;
        player.items.push_back("integral sheet");
    } else if (num == 5 && enemy.name.find("Calc 3") != string::npos) {
        cout << enemy.name << " dropped a vector sheet." << endl;
        player.items.push_back("vector sheet");
    } else {
        cout << enemy.name << " dropped coffee. Focus +10." << endl;
        addFocus(player, 10);
    }
}
