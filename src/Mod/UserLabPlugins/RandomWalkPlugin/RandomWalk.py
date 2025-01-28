# -*- coding: utf-8 -*-
"""Class to represent a walker with all functions to simulate walking"""

import numpy as np
import math
import time

class Walker:
    """Walker geometry"""

    def __init__(self, total_steps):
        """
        Constructs a Walker object with a randomly chosen starting point (x, y) and speed
        :param total_steps: the number of steps the walker has to walk
        :param n_walkers: the number of walkers that have to be created
        """
        self.steps = (
            total_steps + 1
        )  # one step should be array[1], not array[0], therefore add 1 step
        # the speed is randomly chosen in the range between min_speed and max_speed for every walker created (there can be Superhumans with a value up to +2.5% over max_speed)
        self.min_speed = 1
        self.max_speed = 3
        self.walker_speed = self.get_random_speed()
        # creating two arrays for containing x and y coordinates and fill them with 0s, first value of the arrays is the randomly chosen startpoint respectively
        self.x = np.zeros(self.steps)
        self.y = np.zeros(self.steps)
        self._check_arguments()

    def _check_arguments(self):
        """Test whether the types of values for the creation of the objects are correct"""
        if (
            not isinstance(self.steps, (int))
            and isinstance(self.startx, (int))
            and isinstance(self.starty, (int))
            and isinstance(self.walker_speed, (float))
        ):
            raise ValueError

    def get_random_speed(self):
        """
        Randomly choose a speed value in range min and max walkerspeed
        :return: a randomly chosen value between min_speed and max_speed + 2.5% (for superhumans to occur)
        """
        return round(
            np.random.uniform(
                self.min_speed, self.max_speed + (self.max_speed * 0.025)
            ),
            2,
        )

    def get_random_startpoint(self):
        """Randomly choose a starting point in range -sqrt and sqrt of the steps. Used to keep the plot relatively compact (responsive)."""
        return np.random.randint(-math.sqrt(self.steps), math.sqrt(self.steps))

    def get_random_direction(self, movepattern):
        """
        Choose randomly between two movement patterns (Moore with 8 directions and Neumann with 4 directions)
        :return: a value from the specified movement set which can be used in plan_next_step()
        """
        if movepattern == "true":
            moveset = [
                "East",
                "Southeast",
                "South",
                "Southwest",
                "West",
                "Northwest",
                "North",
                "Northeast",
            ]
        else:
            moveset = ["East", "South", "West", "North"]
        return np.random.choice(moveset)

    def plan_next_step(self, direction, step):
        """
        Plans the next step in the Moore neighborhood by using the randomized get_random_direction()
        :param direction: return value of get_random_direction()
        :param step: index value of random_walk()
        """
        if direction == "East":
            self.x[step] = self.x[step - 1] + self.walker_speed
            self.y[step] = self.y[step - 1]
        elif direction == "Southeast":
            self.x[step] = self.x[step - 1] + self.walker_speed
            self.y[step] = self.y[step - 1] - self.walker_speed
        elif direction == "South":
            self.x[step] = self.x[step - 1]
            self.y[step] = self.y[step - 1] - self.walker_speed
        elif direction == "Southwest":
            self.x[step] = self.x[step - 1] - self.walker_speed
            self.y[step] = self.y[step - 1] - self.walker_speed
        elif direction == "West":
            self.x[step] = self.x[step - 1] - self.walker_speed
            self.y[step] = self.y[step - 1]
        elif direction == "Northwest":
            self.x[step] = self.x[step - 1] - self.walker_speed
            self.y[step] = self.y[step - 1] + self.walker_speed
        elif direction == "North":
            self.x[step] = self.x[step - 1]
            self.y[step] = self.y[step - 1] + self.walker_speed
        elif direction == "Northeast":
            self.x[step] = self.x[step - 1] + self.walker_speed
            self.y[step] = self.y[step - 1] + self.walker_speed

    def random_walk(self, move_pattern, random_start):
        """Put together get_random_direction() and plan_next_step() to simulate walking"""
        if random_start == "true":
            self.x[0] = self.get_random_startpoint()
            self.y[0] = self.get_random_startpoint()
        for step in range(1, self.steps):  # start with step after startpoint
            self.plan_next_step(self.get_random_direction(move_pattern), step)

    def walker_type(self):
        """Returns the type of walker based on the randomly chosen speeds of the walker objects in the range of min and max speed"""
        calc = (
            self.max_speed - self.min_speed
        ) * 0.25  # calculate 25% of the total speed range
        if self.walker_speed < (self.min_speed + calc):  # 25% probability
            walker_type = "Slow Walker"
        elif (
            (self.min_speed + calc) <= self.walker_speed < (self.max_speed - calc)
        ):  # 50% probability
            walker_type = "Normal Walker"
        elif (
            (self.max_speed - calc) <= self.walker_speed <= self.max_speed
        ):  # 25% probability
            walker_type = "Fast Walker"
        else:
            walker_type = "Superhuman"  # can get values outside the speed range (up to +2.5% of max speed possible)
        return walker_type

    def __str__(self):
        """Returns a formatted string with details about the Walker object"""
        return "{}, Start coordinates: x={:0.2f}/y={:0.2f}, speed={}".format(
            self.walker_type(), self.x[0], self.y[0], self.walker_speed
        )


def generateRandomWalk(total_steps,
        n_walkers,
        move_pattern,
        random_start,
        total_runs):
    """
    Generates random walkers, calculates their path, saves them in a dataframe and plots them into a plot
    :return: csv-file with walkers and their attributes and a plot with all walkers
    """
    starttime = time.time()
    allResults = []
    array = []
    speedArray = []
    motionTypeArray = []
    allSpeedArray = []
    allMotionTypeArray = []

    # enabling the script to run multiple times
    for run_num in range(total_runs):
        run_num += 1
        walkers = {}
        # creating multiple instances of walkers
        for walker_num in range(n_walkers):
            new_walker = Walker(total_steps=total_steps)
            new_walker.random_walk(move_pattern, random_start)
            array.append(new_walker.x.tolist())
            array.append(new_walker.y.tolist())
            speedArray.append(new_walker.walker_speed)
            motionTypeArray.append(new_walker.walker_type())
        stoptime = time.time()
        allResults.append(array)
        allSpeedArray.append(speedArray)
        allMotionTypeArray.append(motionTypeArray)

        # Print out the information to user
        if n_walkers == 1:
            print(
                "Finished computing the Random Walk Simulation with {} walker & {} steps.\n The script took {:0.2f} seconds to run.".format(
                    n_walkers, total_steps, stoptime - starttime
                )
            )
        else:
            print(
                "Finished computing the Random Walk Simulation with {} walkers & {} steps.\n The script took {:0.2f} seconds to run.".format(
                    n_walkers, total_steps, stoptime - starttime
                )
            )
        return (allResults, allSpeedArray, allMotionTypeArray)
    
        # plot_all_walkers(total_steps, n_walkers, want_plot_saved, run_num)
        
# generateRandomWalk(total_steps = 1000, n_walkers = 2,  move_pattern = True, random_start = True, total_runs = 1)