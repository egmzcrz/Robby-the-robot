#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
  a=a-b;  a=a-c;  a=a^(c >> 13);
  b=b-c;  b=b-a;  b=b^(a << 8);
  c=c-a;  c=c-b;  c=c^(b >> 13);
  a=a-b;  a=a-c;  a=a^(c >> 12);
  b=b-c;  b=b-a;  b=b^(a << 16);
  c=c-a;  c=c-b;  c=c^(b >> 5);
  a=a-b;  a=a-c;  a=a^(c >> 3);
  b=b-c;  b=b-a;  b=b^(a << 10);
  c=c-a;  c=c-b;  c=c^(b >> 15);
  return c;
}

void init_room()
{
  //Fill room with cans;
  int i,j;
  for (i = 0; i < ROOM_SIZE; ++i)
  {
    for (j = 0; j < ROOM_SIZE; ++j)
      room[i][j] = random_at_most(1);
  }
}

int clean(genotype *strategy)
{
  int i;
  init_room();
  //Robby's position
  int x = 0;
  int y = 0;
  int points = 0;
  for (i = 0; i < STEPS_MAX; ++i)
  {
    int s =           y == 0 ? WALL : room[x][y-1];
    int n = y == ROOM_SIZE-1 ? WALL : room[x][y+1];
    int w =           x == 0 ? WALL : room[x-1][y];
    int e = x == ROOM_SIZE-1 ? WALL : room[x+1][y];
    int c = room[x][y];
    int situation = c*CURRENT + n*NORTH + s*SOUTH + e*EAST + w*WEST;
    //Robby's updated position
    int action = strategy -> gene[situation];
    if (action == RANDOM)
      action = random_at_most(RIGHT);
    if((action == UP && n == WALL) || (action == DOWN && s == WALL)||
      (action == LEFT && w == WALL) || (action == RIGHT && e == WALL))
    {
      points += CRASH;
      continue;
    }
    switch(action)
    {
      case UP: y += +1; break;
      case DOWN: y += -1; break;
      case LEFT: x += -1; break;
      case RIGHT: x += 1; break;
      case STAY: break;
      case CLEAN:
      points += c == CAN ? CLEAN_CORRECTLY : CLEAN_WRONGLY;
      room[x][y] = EMPTY;
      break;
    }
  }
  return points;
}

void fitness(genotype *strategy)
{
  /* Fitness is the average of the total
  points of 100 cleaning sessions.
  The bigger the average the better. */
  int i;
  int cleaning_sessions = 100;
  int total_points = 0;
  for (i = 0; i < cleaning_sessions; ++i)
    total_points += clean(strategy);
  strategy -> fitness = (double)total_points/cleaning_sessions;
}
