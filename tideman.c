#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

int preferences[9][9]; //preferences[0][1] = 5 has the number of people who prefer candidate[0] over candidate[1]
bool locked[9][9]; //locked[0][2] = true means candidate[0] has an edge pointing to candidate[2]

typedef struct
{
    int winner;
    int loser;
}
pair; //candidates index of winner & loser pair

string candidates[9]; //list of all candidates
pair pairs[9 * (8) / 2]; //pairs of candidates

//global variables
int numOfCandidates = 0;
int pairCount = 0;
int candidateCount = 0;
int source = 0;


//functions
bool vote (int rank, string name, int ranks[]);
void recordPreferences (int ranks[]);
void addPairs(void);
bool sortPairs (int start, int end, pair pivot);
void lockedPairs (void);
void printWinner(void);
void swap(pair *a, pair *b);

//main
int main (int argc, string argv[])
{
    numOfCandidates = argc - 1;
    string candidateName;
    int numOfVoters = 0;
    int i = 0, n = 0;
    int ranks[9] = {0}; //ranks[0] = 3 means that the voter ranked candidates[3] as their first choice
    if (argc >= 2)
    {
        for (i = 0; i < numOfCandidates; i++)
        {
            candidates[i] = argv[i + 1];
        }
        numOfVoters = atoi(get_string("Number of voters: "));
        //get voter ballots
        for (i = 0; i < numOfVoters; i++)
        {
            n = 0;
            while (n < numOfCandidates)
            {
                candidateName = get_string("Rank %i: ", n+1);
                if (vote(n, candidateName, ranks)) //call vote
                {
                    n++;
                }
                else
                {
                    printf("Invalid vote\n");
                }
            }
            printRanks(ranks);
            recordPreferences(ranks); //record the preferences of the voter in the preferences array
            printPreferences(numOfCandidates);
            printf("\n");
        }
        printPreferences(numOfCandidates);
        addPairs();
        printfPairs(numOfCandidates);
        if (sortPairs(0, pairCount, &pairs[0]))
        {
            lockedPairs();
            printWinner();
        }
    }
}

bool vote (int rank, string name, int ranks[])
{
    int i = 0;
    for (i = 0; i < numOfCandidates; i++)
    {
        if (strcmp(candidates[i], name) == 0)//if name is found
        {
            ranks[rank] = i; //stores the index of the candidate that is ranked as rank
            return true;
        }
    }
    return false;
}

void recordPreferences (int ranks[])
{
    int i = 0, j = i+1;
    for (i = 0; i < numOfCandidates-1; i++) //loop through ranks
    {
        for (j = i+1; j < numOfCandidates; j++) //start from position i and loop through (every candidate after i is ranked below i)
        {
            //rank[i] = 3, rank[j] = 5 --> the voter ranked candidates[3] above candidates[5]
            //preferences[3][5]++ --> number of people who prefer candidates[3] over candidates[5] increases by one
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void addPairs(void)
{
    int i = 0, j = 0;
    for (i = 0; i < numOfCandidates; i++)
    {
        for (j = i; j < numOfCandidates; j++)
        {
            if (preferences[i][j] > preferences[j][i])//if there are people who prefer candidates[i] over candidates[j]
            {
                pairs[pairCount].winner = i; //index of winner candidate
                pairs[pairCount].loser = j; //index of loser candidate
                pairCount ++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pairCount].winner = j;
                pairs[pairCount].loser = i;
                pairCount++;
            }
        }
    }
}

bool sortPairs (int start, int end, pair *pivot)
{
    //reference sort.c
    /*
    //sort pairs depending on what is in preferences
    int i = start, j = end-1;
    int numi = 0, numj = 0;
    int pivotNum = preferences[pivot.winner][pivot.loser] - preferences[pivot.loser][pivot.winner];
    while (true)
    {
        j--;
        while (i < end)
        {
            //find how many voters ranked winner over loser vs how many ranked loser over winner
            //find strength of victory
            numi = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            if (numi < pivotNum) //find num that is less than pivot
            {
                break;
            }
            else
            {
                i++;
            }
        }
        while (j > start)
        {
            numj = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (numj > pivotNum) //find num that is greater than pivot
            {
                break;
            }
            else
            {
                j--;
            }
        }
        if (i > j)
        {
            break;
        }
        swap(&pairs[i], &pairs[j]); //swap the 2
        swapCount++;
        i++;
    }
    if ((j > start) && (i == end))
    {
        swap(pivot, &pairs[j]); //swap final j with pivot, pivot is now in sorted position
    }
    else if ((i != end) && (j != start))
    {
        swap(pivot, &pairs[j]); //swap final j with pivot, pivot is now in sorted position
    }
    else
    {
        swap(&pivot, &pairs[j]); //swap final j with pivot, pivot is now in sorted position
        //quick sort left half
        sortPairs(start, j, &pairs[start]);
        //quick sort right half
        sortPairs(j + 1, end, &pairs[j + 1]);
        return true;
    }
    */
}

void lockedPairs (void)
{
    source = pairs[0].winner;
    int i = 0;
    int count = 0;
    for (i = 0; i < pairCount; i++)
    {
        if (count != numOfCandidates - 1)
        {
            //locked[winnercandidate index][losercandidate index] = true
            locked[pairs[i].winner][pairs[i].loser] = true;
            count++;
            if (pairs[i].loser == source)
            {
                source = pairs[i].winner;
            }
        }
    }
}

void printWinner(void)
{
    printf("%s\n", candidates[source]);
}

void swap(pair *a, pair *b)
{
    pair tmp = *a;
    *a = *b;
    *b = tmp;
}