#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>


int preferences[100][9];
int numOfCandidates = 0;
int numOfVoters = 0;
int rankIncr = 0;

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[9];

bool vote (int voter, int rank, string name);
void tabulate (void);
bool printWinner (void);
int findMin (void);
bool isTie (int min);
void eliminate (int min);


int main(int argc, string argv[])
{
    bool findWinner;
    int i = 0, n = 0, min = 0;
    string candidateName;
    numOfCandidates = argc-1;
    if (argc >=2)
    {
        for (i = 0; i < numOfCandidates; i++)
        {
            candidates[i].name = argv[i + 1];
        }
        numOfVoters = atoi(get_string("Number of voters: "));
        for (i = 0; i < numOfVoters; i++)
        {
            n = 0;
            while (n < numOfCandidates)
            {
                candidateName = get_string("Rank %i: ", n+1);
                if (vote (i, n, candidateName))
                {
                    n++;
                }
                else
                {
                    printf("Invalid vote.\n");
                }
            }
            print("\n");
        }
        tabulate();
        while(!printWinner())
        {
            min = findMin();
            if(isTie(min))
            {
                for (i = 0; i < numOfCandidates; i++)
                {
                    if (candidates[i].eliminated == 0)
                    {
                        printf ("%s\n", candidates[i].name);
                        break;
                    }
                }
            }
            eliminate(min);
        };
    }
}

bool vote (int voter, int rank, string name)
{
    int i = 0;
    for (i = 0; i < numOfCandidates; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i; //index[2][0] = 0 (3rd voter ranked candidates[0] first)
            return true;
        }
    }
    return false;
}

void tabulate (void)
{
    int i = 0, j = 0, n = 0;
    for (i = 0; i < numOfVoters; i++)
    {
        candidates[preferences[i][0]].votes++; //add 1 to the number of votes for that candidate
    }
    return;
}

bool printWinner (void)
{
    int i = 0;
    for (i = 0; i < numOfCandidates; i++)
    {
        if (candidates[i].votes > (float) numOfVoters/2) //if any candidate has more than 50% of the votes
        {
            printf ("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

int findMin (void)
{
    int i = 0;
    int min = candidates[0].votes;
    for (i = 0; i < numOfCandidates; i++)
    {
        if ((candidates[i].eliminated == 0) && (candidates[i].votes < min))
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

bool isTie (int min)
{
    bool ret = true;
    int i = 0;
    for (i = 0; i < numOfCandidates; i++)
    {
        if ((candidates[i].eliminated == 0) && (candidates[i].votes != min))
        {
            ret = false;
        }
    }

    return ret;
}

void eliminate (int min)
{
    int i = 0, j = 0, k= 0;
    for (i = 0; i < numOfCandidates; i++)
    {
        if ((candidates[i].eliminated == 0) && (candidates[i].votes == min)) //if the candidate's votes are the minimum number
        {
            candidates[i].eliminated = 1;
            for (j = 0; j < numOfVoters; j++)
            {
                if (preferences[j][0] == i)
                {
                    for (k = 0; k < numOfCandidates; k ++)
                    {
                        preferences[j][k] = preferences[j][k+1];
                    }
                    candidates[preferences[j][0]].votes++;
                }

            }
        }
    }
}

