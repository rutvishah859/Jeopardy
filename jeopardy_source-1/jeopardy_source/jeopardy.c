/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    // sort the players array in decending order of score
    for (int i = 0; i < num_players; i++) {
        player maxScore = players[i];
        for (int j = i + 1; j < num_players; j++) {
            if (players[j].score > maxScore.score) {
                player temp = players[j];
                players[j] = maxScore;
                maxScore = temp;
                players[i] = maxScore;
                
            }
        }
    }

    for (int i = 0; i < num_players; i++) {
        printf("%s - $%d\n", players[i].name, players[i].score);
    }
}


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];

    // Display the game introduction and initialize the questions
    initialize_game();
    
    printf("-----------Welcome to Jeopardy!-----------\n");
    
    // Prompt for players names
    // initialize each of the players in the array
    for (int i = 0; i < NUM_PLAYERS; i++){
    	printf("Enter player name: ");
    	scanf("%[^\n]%*c", players[i].name);
    	players[i].score = 0;
    }
    
    // Perform an infinite loop getting command input from users until game ends
    while (true){
        // if all the questions defined have been answered exit the game
        if (allQuestionsAnswered()){
            break;
        }
        // reset vars for each iteration of the loop
        char selected_player[BUFFER_LEN] = { 0 };
        char category[BUFFER_LEN] = { 0 };
        int value;
        char answer[BUFFER_LEN] = { 0 };

        // display categories
        printf("-----------Categories-----------\n");
    	display_categories();
        printf("\n");
        
        // select player
        do {
            printf("Enter a valid player name: ");
            scanf("%[^\n]%*c", selected_player);
        } while(!player_exists(players, NUM_PLAYERS, selected_player));
        
        // display question for given category and value
        do {
            printf("Enter a valid category: ");
            scanf("%[^\n]%*c", category);

            printf("Enter a valid dollar value associated to a category: ");
            scanf("%d%*c", &value);
        } while(!display_question(category, value));
        
        printf("Enter answer starting with the prefix 'what is' or 'who is': ");
        // take input after prefix who is or what is
        scanf("%*s is %[^\n]%*c", answer);
        // if the answer is valid display 'Correct' otherwise display 'Inncorrect'
        if (valid_answer(category, value, answer)) {
            printf("Correct\n");
            update_score(players, NUM_PLAYERS, selected_player, value);
        }
        else {
            printf("Inncorrect\n");
        }
    }
    printf("-----------Final Scores-----------\n");
    show_results(players, NUM_PLAYERS);
    return EXIT_SUCCESS;
}
