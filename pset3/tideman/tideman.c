#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_path(int win, int lose, int step);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(candidates[a], name) == 0)
        {
            ranks[rank] = a;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int a = 0; a < candidate_count; a++)
    {
        for (int b = a + 1; b < candidate_count; b++)
        {
            preferences[ranks[a]][ranks[b]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int a = 0; a < candidate_count; a++)
    {
        for (int b = candidate_count - 1; b > a; b--)
        {
            if (preferences[a][b] > preferences[b][a])
            {
                pairs[pair_count].winner = a;
                pairs[pair_count].loser = b;
                pair_count++;
            }
            else if (preferences[b][a] > preferences[a][b])
            {
                pairs[pair_count].winner = b;
                pairs[pair_count].loser = a;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair tmp;
    for (int j =  0; j < pair_count - 2; j++)
    {
        for (int i = 1; i < pair_count - j - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[i - 1].winner][pairs[i - 1].loser])
            {
                tmp = pairs[i - 1];
                pairs[i - 1] = pairs[i];
                pairs[i] = tmp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int y = 0; y < pair_count; y++)
    {
        if (y == 0)
        {
            locked[pairs[y].winner][pairs[y].loser] = true;
        }
        if (y > 0)
        {
            if (check_path(pairs[y].winner, pairs[y].loser, y) == false)
            {
                locked[pairs[y].winner][pairs[y].loser] = true;
            }
        }
    }
    return;
}

bool check_path(int win, int lose, int step)
{
    for (int a = step - 1; a >= 0; a--)
    {
        if (pairs[a].loser == win && locked[pairs[a].winner][pairs[a].loser] == true)
        {
            win = pairs[a].winner;
        }
        if (lose == win)
        {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int w = 0; w < candidate_count; w++)
    {
        bool all_false = false;

        for (int e = 0; e < candidate_count; e++)
        {
            if (locked[e][w] == true)
            {
                all_false = true;
            }
        }
        if (all_false == false)
        {
            printf("%s\n", candidates[w]);
            return;
        }
    }
    return;
}