# Robby-the-robot
A genetic algorithm to evolve a soda can cleaning robot.

## Compiling
In terminal:
```bash
gcc robby_ga.c functions.c -o ROBBY
./ROBBY
```

The main program, ROBBY, generates two files: __report.dat__ and __strategy.dat__. Report.dat just shows some stats used in the program while strategy.dat encodes how Robby must move.

##Visualizing
In terminal:
```bash
gcc plot_strategy.c functions.c -o PLOT_STRATEGY
./PLOT_STRATEGY strategy.dat
```

## Robby's cleaning session after a 20,000 generation evolution
![alt tag](https://github.com/puillitoto/Robby-the-robot/blob/master/cleaning_session.gif)
