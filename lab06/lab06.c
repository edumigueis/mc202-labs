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

// Compare strings ignoring cases
int noCaseStrCmp(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        char c1 = *str1;
        char c2 = *str2;

        // Convert characters to lowercase
        if ('A' <= c1 && c1 <= 'Z')
            c1 += 32;
        if ('A' <= c2 && c2 <= 'Z')
            c2 += 32;
        // Compare each character in order
        if (c1 != c2)
            return c1 - c2;
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

int compare(const void *s1, const void *s2)
{
    const struct TeamScores *team1 = (const struct TeamScores *)s1;
    const struct TeamScores *team2 = (const struct TeamScores *)s2;

    // Compare points
    if (team1->points != team2->points)
        return team2->points - team1->points;
    // Compare wins
    if (team1->wins != team2->wins)
        return team2->wins - team1->wins;
    // Compare goal diff
    short goalDifference1 = team1->goalsDone - team1->goalsTaken;
    short goalDifference2 = team2->goalsDone - team2->goalsTaken;
    if (goalDifference1 != goalDifference2) // goal diff
        return goalDifference2 - goalDifference1;
    // Compare goals
    if (team1->goalsDone != team2->goalsDone)
        return team2->goalsDone - team1->goalsDone;
    // Compare less games
    if (team1->gameCount != team2->gameCount) // number of games played
        return team1->gameCount - team2->gameCount;

    // Compare names
    return noCaseStrCmp(team1->name, team2->name); // compare ignoring letter cases
}

struct TeamScores *calcScores(char participants[][MAX_PART_SIZE], struct Game *games, short participantCount, short gameCount)
{
    struct TeamScores *res = calloc(participantCount, sizeof(struct TeamScores));
    // calloc for allocating and initializing
    if (res == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (short i = 0; i < participantCount; i++)
    {
        // res contains player list.
        strcpy(res[i].name, participants[i]);
    }

    for (short i = 0; i < gameCount; i++)
    {
        for (short a = 0; a < participantCount; a++)
        {
            // match that to the games list to only update the struct with the games that player participated in
            if (strcmp(games[i].team1, res[a].name) == 0 || strcmp(games[i].team2, res[a].name) == 0)
            {
                short isTeam1 = strcmp(games[i].team1, res[a].name) == 0;
                short goalsFor = isTeam1 ? games[i].goals1 : games[i].goals2;
                short goalsAgainst = isTeam1 ? games[i].goals2 : games[i].goals1;

                // Updating the scores based on game data
                if (goalsFor > goalsAgainst)
                {
                    res[a].wins++;
                    res[a].points += 3;
                }
                else if (goalsFor == goalsAgainst)
                {
                    res[a].ties++;
                    res[a].points += 1;
                }
                else
                    res[a].defeats++;

                res[a].goalsTaken += goalsAgainst;
                res[a].goalsDone += goalsFor;
                res[a].gameCount++; // that player played one more game
            }
        }
    }
    return res;
}

// sorting the results by the criteria defined in the compare function
struct TeamScores *getStandings(struct TeamScores *results, short count)
{
    qsort(results, count, sizeof(struct TeamScores), compare);
    return results;
}

// printing TeamScores one-by-one
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

        short participantCount = 0;
        scanf("%3hd", &participantCount);
        char participants[participantCount][MAX_PART_SIZE];
        getchar(); // Consume the newline character
        for (short i = 0; i < participantCount; i++)
        {
            fgets(participants[i], MAX_PART_SIZE + 1, stdin);    // reading with newline
            participants[i][strcspn(participants[i], "\n")] = 0; // removing newline
        }

        short gameCount = 0;
        scanf("%4hd", &gameCount);
        struct Game *games = calloc(gameCount, sizeof(struct Game));
        for (int i = 0; i < gameCount; i++)
        {
            getchar();
            scanf("%30[^#]#%hd@%hd#%30[^\n]", games[i].team1, &games[i].goals1, &games[i].goals2, games[i].team2);
        }
        printf(inputCount == 0 ? "%s\n" : "\n%s\n", name);
        printStandings(                                                       // print all results
            getStandings(                                                     // order participants by criteria
                calcScores(participants, games, participantCount, gameCount), // calculate participants data
                participantCount),
            participantCount);

        free(games);
        inputCount++;
    }
    return 0;
}