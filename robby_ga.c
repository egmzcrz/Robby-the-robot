#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

int main(int argc, char const *argv[])
{
  int i,j;
  srand(mix(clock(), time(NULL), getpid()));
  FILE *report = fopen("report.dat","w");
  FILE *strategy_out = fopen("strategy.dat","w");

  fprintf(report, "POPULATION SIZE:           %i\n", POP_SIZE);
  fprintf(report, "MAXIMUM GENERATION:        %i\n", GENERATION_MAX);
  fprintf(report, "PROBABILITY OF MUTATION:   %.2f\n\n", MUTATION_PROBABILITY);
  fprintf(report,"FIRST GENERATION\n");
  genotype population[POP_SIZE];
  for (i = 0; i < POP_SIZE; ++i)
  {
    for (j = 0; j < GENOME_SIZE; ++j)
      population[i].gene[j] = random_at_most(6);
    fitness(&population[i]);
    fprintf(report,"%f\n", population[i].fitness);
  }
  //Evolution:
  int generation;
  int best, second_best;
  for (generation = 1; generation <= GENERATION_MAX; ++generation)
  {
    ///////////////////////////////
    //"Not so" natural selection//
    ///////////////////////////////
    best = population[1].fitness > population[0].fitness;
    second_best = !best;
    for (i = 2; i < POP_SIZE; ++i)
    {
      if (population[i].fitness > population[second_best].fitness)
      {
        if (population[i].fitness > population[best].fitness)
        {
          second_best = best;
          best = i;
        }
        else
          second_best = i;
      }
    }
    /*
    //Natural Selection:
    double weight[POP_SIZE];
    double WEIGHT_TOTAL = 0;
    for (i = 0; i < POP_SIZE; ++i)
    {
      weight[i] = population[i].fitness + 1000;
      WEIGHT_TOTAL += weight[i];
    }
    for (i = 0; i < POP_SIZE; ++i)
      weight[i] /= WEIGHT_TOTAL;
    double cumulative_weight = 0.0;
    double random1 = rnd();
    double random2 = rnd();
    int flag1 = 1, flag2 = 1;
    for (i = 0; i < POP_SIZE; ++i)
    {
      cumulative_weight += weight[i];
      if (flag1 && random1 <= cumulative_weight)
      {
        best = i;
        flag1 = 0;
      }
      if (flag2 && random2 <= cumulative_weight)
      {
        second_best = i;
        flag2 = 0;
      }
    }
    */
    //Save the 2 best individuals
    int strategy1[GENOME_SIZE-1];
    int strategy2[GENOME_SIZE-1];
    for (i = 0; i < GENOME_SIZE; ++i)
    {
      strategy1[i] = population[best].gene[i];
      strategy2[i] = population[second_best].gene[i];
    }
    //Crossover to repopulate
    for (i = 0; i <= POP_SIZE-2; i+=2)
    {
      int random_xover = random_at_most(GENOME_SIZE);
      for (j = 0; j < random_xover; ++j)
      {
        population[i].gene[j] = strategy1[j];
        population[i+1].gene[j] = strategy2[j];
        if (rnd() < MUTATION_PROBABILITY)
          population[i].gene[j] = random_at_most(6);
        if (rnd() < MUTATION_PROBABILITY)
          population[i+1].gene[j] = random_at_most(6);
      }
      for (j = random_xover; j < GENOME_SIZE; ++j)
      {
        population[i].gene[j] = strategy2[j];
        population[i+1].gene[j] = strategy1[j];
        if (rnd() < MUTATION_PROBABILITY)
          population[i].gene[j] = random_at_most(6);
        if (rnd() < MUTATION_PROBABILITY)
          population[i+1].gene[j] = random_at_most(6);
      }
      fitness(&population[i]);
      fitness(&population[i+1]);
    }
  }
  fprintf(report,"\nLAST GENERATION\n");
  for (i = 0; i < POP_SIZE; ++i)
    fprintf(report,"%f\n", population[i].fitness);
  fclose(report);

  best = 0;
  for (i = 1; i < POP_SIZE; ++i)
  {
    if (population[i].fitness > population[best].fitness)
      best = i;
  }
  for (i = 0; i < GENOME_SIZE; ++i)
    fprintf(strategy_out, "%i", population[best].gene[i]);
  fclose(strategy_out);

  return 0;
}