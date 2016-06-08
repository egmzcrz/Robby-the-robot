#define rnd() (double)rand()/RAND_MAX
#define random_at_most(max) rand() % (max+1)
/*
Robby is a cleaning robot living in a 10 by 10 room. In 200 steps,
Robby, has to pick up as much trash as he can. */
#define ROOM_SIZE 10
#define STEPS_MAX 200
int room[ROOM_SIZE][ROOM_SIZE];

/*When Robby, correctly, picks up trash he gains 10 points, but if he hits the wall
he loses 5 points. If Robby picks trash where there is none to pick then he
loses 1 point. */
#define CLEAN_WRONGLY    -1
#define CRASH            -5
#define CLEAN_CORRECTLY  10

/*
Robby sees 5 squares in his vecinity:
North, South, East, West, Current. */

//Each square can have three different states:
#define EMPTY 0
#define CAN   1
#define WALL  2

//In total there are 3^5 = 243 situations (some of them impossible)
#define GENOME_SIZE 243
typedef struct genotype
{
  int gene[GENOME_SIZE];
  double fitness;
} genotype;

//For each of the above situations Robby can take the following actions:
#define UP      0
#define DOWN    1
#define LEFT    2
#define RIGHT   3
#define STAY    4
#define RANDOM  5
#define CLEAN   6

/*
For example, consider 2 different situations:
_______________________________________  ______________
Current | North | South  | East | West    Some Action
---------------------------------------  --------------
EMPTY      CAN     EMPTY    CAN    EMPTY       UP
WALL       WALL    WALL     WALL   WALL        STAY

This situations can be encoded in a numeric system of base 3.
The first one would be encoded and mapped to the number 30.
0(3^4) + 1(3^3) + 0(3^2) + 1(3^1) + 0(3^0) = 30 -> UP
The second one should then be equal to 242 -> STAY. */
#define CURRENT 81  //3^4
#define NORTH   27  //3^3
#define SOUTH   9   //3^2
#define EAST    3   //3^1
#define WEST    1   //3^0

/*
The space of solutions then consist of 7^243 strategies, that is,
for each of the 243 strategies there are 7 possible actions to take.*/

//Number of strategies per generation.
#define POP_SIZE 15
//Maximum number of generations.
#define GENERATION_MAX 2000
//Probability to mutate.
#define MUTATION_PROBABILITY 0.02

unsigned long mix(unsigned long a, unsigned long b, unsigned long c);

void init_room();
void fitness(genotype *strategy);
int clean(genotype *strategy);
