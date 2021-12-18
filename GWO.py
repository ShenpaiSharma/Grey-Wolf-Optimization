import random
import math
import copy
import sys
 

# rastrigin function
def fitness_rastrigin(position):
  fitness_value = 0.0
  for i in range(len(position)):
    xi = position[i]
    fitness_value += (xi * xi) - (10 * math.cos(2 * math.pi * xi)) + 10
  return fitness_value
 
 
# wolf class
class wolf:
  def __init__(self, fitness, dim, minx, maxx, seed):
    self.rnd = random.Random(seed)
    self.position = [0.0 for i in range(dim)]
 
    for i in range(dim):
      self.position[i] = ((maxx - minx) * self.rnd.random() + minx)
 
    self.fitness = fitness(self.position) # curr fitness
 


# grey wolf optimization (GWO)
def gwo(fitness, max_iter, n, dim, minx, maxx):
    rnd = random.Random(0)
 
    # create n random wolves
    population = [ wolf(fitness, dim, minx, maxx, i) for i in range(n)]
 
    # On the basis of fitness values of wolves
    # sort the population to get the 3 best wolves namely alpha, beta, delta
    population = sorted(population, key = lambda temp: temp.fitness)
 
    alpha_wolf, beta_wolf, delta_wolf = copy.copy(population[: 3])
 

    Iter = 0
    while Iter < max_iter:
 
        # after every 10 iterations
        # print iteration number and best fitness value so far
        if Iter % 10 == 0 and Iter > 1:
            print("Iter = " + str(Iter) + " best fitness = %.3f" % alpha_wolf.fitness)
 
        # linearly decreased from 2 to 0 so that 1st we emphasize on exploration
        # then on exploitation
        a = 2*(1 - Iter/max_iter)
 
        # updating each population member with the help of best three members
        for i in range(n):
            A1, A2, A3 = a * (2 * rnd.random() - 1), a * (
              2 * rnd.random() - 1), a * (2 * rnd.random() - 1)
            C1, C2, C3 = 2 * rnd.random(), 2*rnd.random(), 2*rnd.random()
 
            X1 = [0.0 for i in range(dim)]
            X2 = [0.0 for i in range(dim)]
            X3 = [0.0 for i in range(dim)]
            Xnew = [0.0 for i in range(dim)]
            for j in range(dim):
                D_alpha = abs(C1 - alpha_wolf.position[j] - population[i].position[j])
                D_beta = abs(C2 - beta_wolf.position[j] - population[i].position[j])
                D_delta = abs(C3 - delta_wolf.position[j] - population[i].position[j])

                X1[j] = alpha_wolf.position[j] - A1 * D_alpha
                X2[j] = beta_wolf.position[j] - A2 * D_beta
                X3[j] = delta_wolf.position[j] - A3 * D_delta

                Xnew[j]+= X1[j] + X2[j] + X3[j]
             
            for j in range(dim):
                Xnew[j]/=3.0
             
            # fitness calculation of new solution
            fnew = fitness(Xnew)
 
            # greedy selection
            if fnew < population[i].fitness:
                population[i].position = Xnew
                population[i].fitness = fnew
                 
        # On the basis of fitness values of wolves
        # sort the population in asc order
        population = sorted(population, key = lambda temp: temp.fitness)
 
        # best 3 solutions will be called as
        # alpha, beta and delta
        alpha_wolf, beta_wolf, delta_wolf = copy.copy(population[: 3])
         
        Iter+= 1
    # end-while
 
    # returning the best solution
    return alpha_wolf.position
           
#----------------------------
 
 
dim = 3
fitness = fitness_rastrigin

 
num_particles = 50
max_iter = 200
 
print("Setting num_particles = " + str(num_particles))
print("Setting max_iter    = " + str(max_iter))
 
 
 
best_position = gwo(fitness, max_iter, num_particles, dim, -10.0, 10.0)
 
print("\nGWO completed\n")
print("\nBest solution found:")
print(["%.6f"%best_position[k] for k in range(dim)])
err = fitness(best_position)
print("fitness of best solution = %.6f" % err)
 
print("\nEnd GWO for rastrigin\n")
 
