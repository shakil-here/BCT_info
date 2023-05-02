/* *******************************************************

Author
  Name : Shakil Hossain
  Email: mhossain223670@bscse.uiu.ac.bd

Before Using this code don't forgate to thanks the author

***********************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Player
{
    char name[MAX_NAME_LENGTH];
    int age;
    int matches_played;
    int total_runs;
    int highest_run;
    int average_run;
    int wickets;
    char role[MAX_NAME_LENGTH];
};
int get_allrounder(const struct Player *players, int num_players, int index);
int read_players(const char *filename, struct Player *players, int max_players);
void print_player(const struct Player *player);
void print_all_players(const struct Player *players, int num_players);
void print_mep(const struct Player *players, int num_players);
void print_ncp(const struct Player *players, int num_players);
void print_tsp(const struct Player *players, int num_players);
void print_hhp(const struct Player *players, int num_players);
void print_hrtp(const struct Player *players, int num_players);
void print_mvp(const struct Player *players, int num_players);
int calculate_value(const struct Player *player);
void print_allrounders(const struct Player *players, int num_players);
int get_newcomer_player(const struct Player *players, int num_players);
int get_top_scorer_player(const struct Player *players, int num_players);
int get_hard_hitter_player(const struct Player *players, int num_players);
int get_highest_run_taker_player(const struct Player *players, int num_players);
int get_most_valuable_player(struct Player *players, int num_players);
int calculate_value(const struct Player *player);
int main()
{
    char filename[MAX_NAME_LENGTH];
    printf("Enter the name of the input file: ");
    scanf("%s", filename);

    struct Player players[50];
    int num_players = read_players(filename, players, 50);

    if (num_players < 0)
    {
        printf("Exiting...\n");
        exit(1);
    };

    while (1)
    {
        printf("\nChoose an option:\n");
        printf("1. Show All Players\n");
        printf("2. Show A Particular player information (Provide Player Name)\n");
        printf("3. Show the MOST Experienced Player (MEP)\n");
        printf("4. Show the New Commer Player (NCP)\n");
        printf("5. Show the Top Scorer Player (TSP)\n");
        printf("6. Show the Hard Hitter Player (HHP)\n");
        printf("7. Show the Highest Run Taker Player (HRTP)\n");
        printf("8. Show the MOST Valuable Player (MVP)\n");
        printf("9. Show the Allrounders\n");
        printf("10. Exit/Quit\n");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            print_all_players(players, num_players);
            break;
        case 2:
        {
            char name[MAX_NAME_LENGTH];
            getchar();
            printf("Enter the name of the player: ");
            fgets(name, 49, stdin);
            name[strcspn(name, "\n")] = '\0';

            int found = 0;
            for (int i = 0; i < num_players; i++)
            {
                if (strcmp(name, players[i].name) == 0)
                {
                    print_player(&players[i]);
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("Player not found.\n");
            }
            break;
        }
        case 3:
            print_mep(players, num_players);
            break;
        case 4:
            print_ncp(players, num_players);
            break;
        case 5:
            print_tsp(players, num_players);
            break;
        case 6:
            print_hhp(players, num_players);
            break;
        case 7:
            print_hrtp(players, num_players);
            break;
        case 8:
            print_mvp(players, num_players);
            break;
        case 9:
            print_allrounders(players, num_players);
            break;

        case 10:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
            break;
        }
    }

    return 0;
}

int read_players(const char *filename, struct Player *players, int max_players)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Failed to open file %s\n", filename);
        return -1;
    }

    int num_players = 0;
    char line[100];
    int count = 0;

    int i = 0;
    while (fgets(line, sizeof(line), fp))
    {
        int tline = 0;
        if (num_players == max_players)
        {
            printf("Error: Maximum number of players reached\n");
            break;
        }
        struct Player player;

        if (i == 1 || i == count + 1)
        {

            sscanf(line, "%49[^'\n']", player.name);
        }
        if (i == 2 || i == count + 2)
        {
            sscanf(line, "%d", &player.age);
        }

        if (i == 3 || i == count + 3)
        {

            sscanf(line, "%49[^'\n']", player.role);
        }

        if (i == 4 || i == count + 4)
        {
            sscanf(line, "%d", &player.matches_played);
        }

        if (i == 5 || i == count + 5)
        {
            sscanf(line, "%d", &player.total_runs);
        }
        if (i == 6 || i == count + 6)
        {
            sscanf(line, "%d", &player.highest_run);
            tline = 1;
            count += 6;
        }

        i++;
        if (tline == 1)
        {
            players[num_players] = player;
            num_players++;
        }
    }

    fclose(fp);
    return num_players;
}

void print_player(const struct Player *player)
{
    printf("%-34s\t%2d \t%4d \t%5d \t%4d \n", player->name, player->age, player->matches_played,
           player->total_runs, player->highest_run);
}

void print_all_players(const struct Player *players, int num_players)
{
    printf("%-34s \t%2s \t%4s \t%5s \t%4s \n", "Name", "Age", "Mat", "Runs", "HS");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < num_players; i++)
    {
        print_player(&players[i]);
    }
}

int get_most_experienced_player(const struct Player *players, int num_players)
{
    int most_experienced_player_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (players[i].matches_played > players[most_experienced_player_index].matches_played)
        {
            most_experienced_player_index = i;
        }
    }
    return most_experienced_player_index;
}

int get_newcomer_player(const struct Player *players, int num_players)
{
    int newcomer_player_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (players[i].age < players[newcomer_player_index].age)
        {
            newcomer_player_index = i;
        }
    }
    return newcomer_player_index;
}

int get_top_scorer_player(const struct Player *players, int num_players)
{
    int top_scorer_player_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (players[i].total_runs > players[top_scorer_player_index].total_runs)
        {
            top_scorer_player_index = i;
        }
    }
    return top_scorer_player_index;
}

int get_hard_hitter_player(const struct Player *players, int num_players)
{
    int hard_hitter_player_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (((float)players[i].total_runs / players[i].matches_played) >
            (float)players[hard_hitter_player_index].total_runs / players[hard_hitter_player_index].matches_played)
        {
            hard_hitter_player_index = i;
        }
    }
    return hard_hitter_player_index;
}
int get_allrounder(const struct Player *players, int num_players, int index)
{

    for (int i = 0; i < num_players; i++)
    {
        if (i == index)
        {
            if (strcasecmp(players[i].role, "All-rounder") == 0)
            {
                return 1;
            }
        }
    }
}
int get_highest_run_taker_player(const struct Player *players, int num_players)
{
    int highest_run_taker_player_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (players[i].highest_run > players[highest_run_taker_player_index].highest_run)
        {
            highest_run_taker_player_index = i;
        }
    }
    return highest_run_taker_player_index;
}

int get_most_valuable_player(struct Player *players, int num_players)
{
    int mvp_index = 0;
    float mvp_value = 0.0;

    for (int i = 0; i < num_players; i++)
    {
        float player_value = players[i].age + players[i].matches_played + players[i].total_runs + players[i].highest_run +
                             (float)players[i].total_runs / players[i].matches_played + (float)players[i].highest_run / players[i].age +
                             (float)players[i].wickets / players[i].matches_played;

        if (player_value > mvp_value)
        {
            mvp_index = i;
            mvp_value = player_value;
        }
    }

    return mvp_index;
}
int calculate_value(const struct Player *player)
{
    int value = player->age + player->matches_played + player->total_runs + player->highest_run;
    float avg_runs = (float)player->total_runs / player->matches_played;
    float avg_highest_run = (float)player->highest_run / player->age;
    value += (int)(avg_runs + avg_highest_run);
    int alrvalue = 0;
    if (strcmp(player->role, "All-rounder") == 0)
    {
        alrvalue = 50;
    }
    value += alrvalue;
    return value;
}

void print_mep(const struct Player *players, int num_players)
{
    int mep_index = get_most_experienced_player(players, num_players);
    printf("MOST Experienced Player (MEP):\n");
    printf("%-34s \t%2s \t%4s \t%5s \t%4s \n", "Name", "Age", "Mat", "Runs", "HS");
    printf("--------------------------------------------------------------------------\n");
    print_player(&players[mep_index]);
}
void print_ncp(const struct Player *players, int num_players)
{
    int ncp_index = get_newcomer_player(players, num_players);
    printf("New Comer Player (NCP):\n");
    printf("%-34s \t%2s \t%4s \t%5s \t%4s \n", "Name", "Age", "Mat", "Runs", "HS");
    printf("--------------------------------------------------------------------------\n");
    print_player(&players[ncp_index]);
}
void print_tsp(const struct Player *players, int num_players)
{
    int top_scorer_index = get_top_scorer_player(players, num_players);
    printf("%-34s \t%2s \t%4s \t%5s \t%4s \n", "Name", "Age", "Mat", "Runs", "HS");
    printf("--------------------------------------------------------------------------\n");
    print_player(&players[top_scorer_index]);
}
void print_hrtp(const struct Player *players, int num_players)
{
    int highest_runs_index = get_highest_run_taker_player(players, num_players);

    printf("The player with the highest runs taken is:\n");
    printf("%-34s \t%2s \t%4s \t%5s \t%4s \n", "Name", "Age", "Mat", "Runs", "HS");
    printf("--------------------------------------------------------------------------\n");
    print_player(&players[highest_runs_index]);
}
void print_mvp(const struct Player *players, int num_players)
{
    int mvp_index = 0;
    int mvp_value = calculate_value(&players[0]);

    for (int i = 1; i < num_players; i++)
    {
        int value = calculate_value(&players[i]);
        if (value > mvp_value)
        {
            mvp_value = value;
            mvp_index = i;
        }
    }

    printf("Most Valuable Player: %s\n", players[mvp_index].name);
    printf("Value: %d\n", mvp_value);
}

void print_hhp(const struct Player *players, int num_players)
{

    int hhp_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (((float)players[i].total_runs / players[i].matches_played) >
            (float)players[hhp_index].total_runs / players[hhp_index].matches_played)
        {
            hhp_index = i;
        }
    }

    printf("Hard Hitter Player:\n");
    printf("%-34s \t%2s \t%4s \t%5s \t%4s \n", "Name", "Age", "Mat", "Runs", "HS");
    printf("--------------------------------------------------------------------------\n");
    print_player(&players[hhp_index]);
}
int get_top_scorer(const struct Player *players, int num_players)
{
    int top_scorer_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (players[i].total_runs > players[top_scorer_index].total_runs)
        {
            top_scorer_index = i;
        }
    }
    return top_scorer_index;
}
int get_highest_runs_player(const struct Player *players, int num_players)
{
    int highest_runs_player_index = 0;
    for (int i = 1; i < num_players; i++)
    {
        if (players[i].total_runs > players[highest_runs_player_index].total_runs)
        {
            highest_runs_player_index = i;
        }
    }
    return highest_runs_player_index;
}

void print_allrounders(const struct Player *players, int num_players)
{
    printf("%-34s \t%2s \t%4s \t%5s \t%4s \n", "Name", "Age", "Mat", "Runs", "HS");
    printf("--------------------------------------------------------------------------\n");
    struct Player allrounders[num_players];
    int num_allrounders = 0;

    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].role, "All-rounder") == 0)
        {
            allrounders[num_allrounders] = players[i];
            num_allrounders++;
        }
    }

    for (int i = 0; i < num_allrounders; i++)
    {

        printf("%-34s \t%2d \t%4d \t%5d \t%4d \n", allrounders[i].name, allrounders[i].age, allrounders[i].matches_played,
               allrounders[i].total_runs, allrounders[i].highest_run);
    }
}


