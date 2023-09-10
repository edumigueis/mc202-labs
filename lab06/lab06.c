#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PART_SIZE 31 // Maximum number of subpalindromes

struct Game
{
    char team1[MAX_PART_SIZE];
    char team2[MAX_PART_SIZE];
    short goals1;
    short goals2;
};

struct TeamScores
{
    char name[MAX_PART_SIZE];
    short points;
    short gameCount;
    short wins;
    short ties;
    short defeats;
    short goalsDone;
    short goalsTaken;
};

int compare(const void *s1, const void *s2)
{
    const struct TeamScores *team1 = (const struct TeamScores *)s1;
    const struct TeamScores *team2 = (const struct TeamScores *)s2;

    // Compare points
    if (team1->points != team2->points)
    {
        return team2->points - team1->points;
    }

    // Compare wins
    if (team1->wins != team2->wins)
    {
        return team2->wins - team1->wins;
    }

    // Compare goal diff
    int goalDifference1 = team1->goalsDone - team1->goalsTaken;
    int goalDifference2 = team2->goalsDone - team2->goalsTaken;
    if (goalDifference1 != goalDifference2)
    {
        return goalDifference2 - goalDifference1;
    }

    // Compare goals
    if (team1->goalsDone != team2->goalsDone)
    {
        return team2->goalsDone - team1->goalsDone;
    }

    // Compare less games
    if (team1->gameCount != team2->gameCount)
    {
        return team1->gameCount - team2->gameCount;
    }

    // Compare names
    return strcmp(team1->name, team2->name);
}

struct TeamScores *calcScores(char participants[][MAX_PART_SIZE], struct Game *games, short participantCount, short gameCount)
{
    struct TeamScores *res = malloc(participantCount * sizeof(struct TeamScores));
    for (short i = 0; i < participantCount; i++)
    {
        strcpy(res[i].name, participants[i]);
    }

    for (short i = 0; i < gameCount; i++)
    {
        for (int a = 0; a < participantCount; a++)
        {
            if (strcmp(games[i].team1, res[a].name) == 0)
            {
                if (games[i].goals1 > games[i].goals2)
                {
                    res[a].wins++;
                    res[a].points += 3;
                }
                else if (games[i].goals1 == games[i].goals2)
                {
                    res[a].ties++;
                    res[a].points += 1;
                }
                else
                {
                    res[a].defeats++;
                }

                res[a].goalsTaken += games[i].goals2;
                res[a].goalsDone += games[i].goals1;
                res[a].gameCount++;
            }
            if (strcmp(games[i].team2, res[a].name) == 0)
            {
                if (games[i].goals1 > games[i].goals2)
                {
                    res[a].defeats++;
                }
                else if (games[i].goals1 == games[i].goals2)
                {
                    res[a].ties++;
                    res[a].points += 1;
                }
                else
                {
                    res[a].wins++;
                    res[a].points += 3;
                }
                res[a].goalsTaken += games[i].goals1;
                res[a].goalsDone += games[i].goals2;
                res[a].gameCount++;
            }
        }
    }
    return res;
}

struct TeamScores *getStandings(struct TeamScores *results, short count)
{
    qsort(results, count, sizeof(struct TeamScores), compare);
    return results;
}

void printStandings(struct TeamScores *results, short count)
{
    for (short i = 0; i < count; i++)
    {
        printf("%hd) %s, %hdp, %hdj (%hd-%hd-%hd), %hds (%hd-%hd)\n",
               i + 1, results[i].name, results[i].points, results[i].gameCount, results[i].wins,
               results[i].ties, results[i].defeats, results[i].goalsDone - results[i].goalsTaken, results[i].goalsDone, results[i].goalsTaken);
    }
    free(results);
}

int main(void)
{
    short n;
    scanf("%3hd", &n);
    short inputCount = 0;
    while (inputCount < n)
    {
        char name[100];
        getchar(); // Consume the newline character
        scanf("%100[^\n]", name);

        short participantCount;
        scanf("%2hd", &participantCount);
        char participants[participantCount][MAX_PART_SIZE];
        for (short i = 0; i < participantCount; i++)
            scanf("%30s", participants[i]);

        short gameCount;
        scanf("%3hd", &gameCount);
        struct Game games[gameCount];
        for (int i = 0; i < gameCount; i++)
        {
            getchar();
            scanf("%30[^#]#%hd@%hd#%30s", games[i].team1, &games[i].goals1, &games[i].goals2, games[i].team2);
        }
        printf("%s\n", name);
        printStandings(getStandings(calcScores(participants, games, participantCount, gameCount), participantCount), participantCount);
        inputCount++;
    }
    return 0;
}