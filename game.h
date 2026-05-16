#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// this is the player
class Player {
public:
    // player stats
    string name;
    int hp;
    int maxHp;
    int focus;
    int score;
    int level;
    int xp;

    // stuff you pick up
    vector<string> items;

    // sets up the player
    Player(string n) {
        name = n;
        maxHp = 100;
        hp = 100;
        focus = 50;
        score = 0;
        level = 1;
        xp = 0;
        items.push_back("pencil");
    }
};

// this is the enemy equations
class Enemy {
public:
    // enemy name
    string name;

    // question and answer
    string question;
    string answer;

    // multiple choice stuff
    string choice1;
    string choice2;
    string choice3;
    int rightChoice;

    // which calc class it is
    int level;

    // enemy hp and damage
    int hp;
    int attack;

    // sets up an enemy
    Enemy(string n, string q, string a, string c1, string c2, string c3, int right, int lvl, int h, int atk) {
        name = n;
        question = q;
        answer = a;
        choice1 = c1;
        choice2 = c2;
        choice3 = c3;
        rightChoice = right;
        level = lvl;
        hp = h;
        attack = atk;
    }
};

// function list
void printTitle();
void printFinalArt();
void pause();
void fixInput();
int getChoice(int low, int high);
int randomNumber(int high);
void showStats(Player player);
void showItems(Player player);
void showHelp();
void intro();
void mainMenu(Player &player, int round);
void randomFight(Player &player, int round);
Enemy getCalc1Enemy();
Enemy getCalc2Enemy();
Enemy getCalc3Enemy();
Enemy getFinalEnemy();
void makeHarder(Enemy &enemy, int round);
void fight(Player &player, Enemy enemy);
void answerQuestion(Player &player, Enemy &enemy);
void changeQuestion(Enemy &enemy);
void useItem(Player &player, Enemy &enemy);
void enemyAttack(Player &player, Enemy enemy);
void winBattle(Player &player, Enemy enemy);
void rest(Player &player);
void findItem(Player &player);
void randomMiniGame(Player &player);
void finalExam(Player &player);
void normalEnding(Player player);
void goodEnding(Player player);
void badEnding(Player player);
bool hasItem(Player player, string item);
void removeItem(Player &player, string item);
string lowerNoSpaces(string word);
void addHp(Player &player, int amount);
void addFocus(Player &player, int amount);
void addXp(Player &player, int amount);
void getDrop(Player &player, Enemy enemy);

#endif
