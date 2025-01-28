# Random Walk Simulation

In this project plots with simulations of randomized walks are generated.

## Description

"A random walk is a mathematical object, known as a stochastic or random process, that describes a path that consists of a succession of random steps on some mathematical space such as the integers. An elementary example of a random walk is the random walk on the integer number line, which starts at 0 and at each step moves +1 or -1 with equal probability" ([Source](https://www.geeksforgeeks.org/random-walk-implementation-python/)).

This project aims to simulate a random walk simulation with different options and further implementations. The main implementations are:

1. Simulation of **multiple random walkers** with different speeds
2. **High randomization** of speeds, start points, colorization etc.
3. Enabling **options** to simulate the random walk of your needs like different neighborhood movement patterns (Neumann/Moore), enabling random start points, running the code multiple times, saving the plot and/or results automatically...
4. TBD: 3D walks
5. TBD: impenetrable objects

## Getting Started

To run the program every machine having at least Python 3.9 installed is suitable. Your Python environment should additionally include the libraries **numpy**, **matplotlib** and **pandas**. The rest should be included in the python installation. If you are using Linux or Mac, you should check the relative paths beforehand.

### Installing

Create your virtual python environment and clone the repository. You should then be ready to execute the program.

## Execution

The program is structured as explained below:

- variables for the number of walks and steps are defined (user-generated)
- the user can specify if a plot should be saved and how many times the code should be executed in total
- additionally the movement pattern can be chosen (4 or 8 directions)
- this leads to the definition of two arrays in form of x and y-coordinates with zeros..
- ..that are filled with random generated values through a for-loop for each walker
- the starting point in form of x and y can be randomized for each walk, otherwise all walkers start at 0,0
- the randomized choice of speed is implemented in the loop and is randomized for every walker
- with the definition of the class Walkers a detailed dataframe for every walk is generated which contains information about the type of walker, the starting point and the speed
- finally the dataframe can be saved as a CSV-file and the walks are plotted together in one figure
- if the user specified that there should be multiple runs, this process is automatically repeated

### Calling
Call the program without any arguments to access the help within the terminal with information on how to use the optional arguments:

```
$ python src/main.py

usage: main.py [-h] [-s Steps] [-w Walkers] [-m Movepattern] [-xy Startpoint] [-p Save plot] [-r Runs]

Simulate a random walk with n walkers for n steps. You can use the following options to change the simulation to your needs. Have fun!

optional arguments:
<<<<<<< HEAD
  -h, --help            show this help message and exit

  -s Steps, integer     Integer | Number of total steps every walker shall take.
                        Default value: 1000
  -w Walkers, integer   Integer | Number of total walkers to be created.
                        Default value: 1
  -m Movepattern, bool  Boolean | Choose neighborhood movement pattern between
                        Neumann (4 directions, false) or
                        Moore (8 directions, true, default)
  -xy Startpoint, bool  Boolean | Do you want different (random) start points for
                        each walker (true, default) or
                        let all plots start at 0,0 (false)?
  -p Save plot, bool    Boolean | Do you want to automatically save the plot locally
                        (in ./data/)? Use true/false. Default: false
  -r Runs, integer      Integer | Total runs of the script (generate multiple plots if
                        wished). Default value: 1
=======
  -h, --help      show this help message and exit
  -s Steps        Integer | Number of total steps every walker shall take. Default value: 1000
  -w Walkers      Integer | Number of total walkers to be created. Default value: 1
  -m Movepattern  Boolean | Choose neighborhood movement pattern between Neumann (4 directions, false) or Moore (8 directions, true, default)
  -xy Startpoint  Boolean | Do you want different (random) start points for each walker (true, default) or let all plots start at 0,0 (false)?
  -p Save plot    Boolean | Do you want to automatically save the plot locally (./data/)? Use true/false. Default: false
  -csv Save csv   Boolean | Do you want to automatically save the results as csv-file locally (./data/)? Use true/false. Default: false
  -r Runs         Integer | Total runs of the script (generate multiple plots if wished). Default value: 1
>>>>>>> 69b4521fbe8972619f3f511f600468fdc26eb50a
```

## Results

Due to the high randomization of the simulation the following possible results are shown only exemplarily.

### Example 1
Options: 25 walkers, 25000 steps, default values and saving the plot

```
$ python src/main.py -s 25000 -w 25 -p true
```
![25walkers](./data/random_walkers_25w_25000s_1.png)

### Example 2
Options: 10000 steps, 12 walkers, start point at 0,0, movement pattern Neumann and saving the plot
```
$ python src/main.py -s 10000 -w 12 -xy false -m false -p true
```
![15walkers](./data/random_walkers_12w_10000s_1.png)

### Example 3
With default values only
```
$ python src/main.py
...
You can run the program with the default values.
Want to run it now? Use y/n: y
```
![1walker](./data/random_walkers_1w_1000s_1.png)
