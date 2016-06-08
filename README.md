# Robby-the-robot
A genetic algorithm to evolve a soda can cleaning robot.

## Compiling
To compile main program: `gcc robby_ga.c functions.c -o ROBBY`.

The main program generates two files __report.dat__ and __strategy.dat__.

To compile the plotting program: `gcc plot_strategy.c functions.c -o PLOT_STRATEGY`.

The plotting program uses gnuplot gif terminal to plot a given _strategy.dat_ file via terminal arguments.

## Robby cleaning session after a 200,000 generation evolution
![alt tag](https://github.com/puillitoto/Robby-the-robot/blob/master/cleaning_session_200000.gif)
