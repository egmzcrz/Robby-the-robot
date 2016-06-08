#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

int main(int argc, char const *argv[])
{
  srand(mix(clock(), time(NULL), getpid()));
  int i,j,k;
  FILE *strategy_io = fopen(argv[1],"r");
  int strategy[GENOME_SIZE];
  for (int i = 0; i < GENOME_SIZE; ++i)
    strategy[i] = fgetc(strategy_io) - '0';
  fclose(strategy_io);

  FILE *gnuplot = popen("gnuplot","w");
  fprintf(gnuplot,"%s\n %s\n %s\n %s\n %s\n",
    "set terminal gif animate delay 20",
    "unset key",
    "set xrange [0:9]",
    "set yrange [0:9]",
    "set output 'cleaning_session.gif'");

  init_room();
  //Robby's position
  int x = 0;
  int y = 0;
  for (i = 0; i < STEPS_MAX; ++i)
  {
    fprintf(gnuplot, "plot '-' w p pt 3 ps 1, '-' w p pt 5 ps 2 lc rgb 'black'\n");
    for (j = 0; j < ROOM_SIZE; ++j)
    {
      for (k = 0; k < ROOM_SIZE; ++k)
      {
        if (room[j][k] != 0)
          fprintf(gnuplot, "%i %i\n", j, k);
      }
    }
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "%i %i\ne\n", x, y);
    int n = y == 0            ? WALL : room[x][y-1];
    int s = y == ROOM_SIZE-1  ? WALL : room[x][y+1];
    int w = x == 0            ? WALL : room[x-1][y];
    int e = x == ROOM_SIZE-1  ? WALL : room[x+1][y];
    int c = room[x][y];

    int situation = c*CURRENT + n*NORTH + s*SOUTH + e*EAST + w*WEST;
    int action = strategy[situation];
    if (action == RANDOM)
      action = random_at_most(RIGHT);
    if((action == UP && n == WALL) || (action == DOWN && s == WALL)||
      (action == LEFT && w == WALL) || (action == RIGHT && e == WALL)||
      action == STAY || (action == CLEAN && c == EMPTY))
      continue;

    switch(action)
    {
      case UP: y += -1; break;
      case DOWN: y+= +1; break;
      case LEFT: x += -1; break;
      case RIGHT: x += +1; break;
      case CLEAN: room[x][y] = EMPTY; break;
    }
  }
  pclose(gnuplot);
  return 0;
}