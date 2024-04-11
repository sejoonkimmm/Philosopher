# Philosopher
Multi-threading and Mutex Learning with C


## Mandatory part
• One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.

• The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping 
while thinking, they are not eating nor sleeping and, of course, while sleeping, they are not eating nor thinking.

• There are also forks on the table. There are as many forks as philosophers.

• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.

• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.

• Every philosopher needs to eat and should never starve.

• Philosophers don’t speak with each other.

• Philosophers don’t know if another philosopher is about to die.

• No need to say that philosophers should avoid dying

• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.

• A displayed state message should not be mixed up with another message.

• A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.

• Again, philosophers should avoid dying! Your program must not have any data races.

## Execute file
- make all : Build
- make fclean : Delete all source files and execute file
- make re : Delete sources file and execute file -> remake execute file

## Arguments
- first arguments : number of philosophers
- second arguments: time to die
- third arguments: time to eat
- fourth arguments: time to sleep
- fifth arguments: number of times each philosopher must eat

## Execute program


https://github.com/sejoonkimmm/Philosopher/assets/117820621/cff478c1-5320-462a-8196-4f656e539b37

- In this case, A philosopher's life span is 410ms, the time to eat is 200ms, and the time to sleep is 200ms, so not all philosophers die.



https://github.com/sejoonkimmm/Philosopher/assets/117820621/4f702df2-1cac-4d4f-9639-4708e4280d73

### Case with 4 Philosophers

When there are four philosophers seated around a table with a fork between each of them, there are a total of four forks available.

Philosophers need two forks to eat - one on the left and one on the right. In a scenario with four philosophers, each can pick up one fork simultaneously, and the last philosopher will not have two forks available to start eating.

Consequently, three philosophers can eat while the remaining one continues to think (or sleep).

As each philosopher finishes eating and puts down the forks, the waiting philosopher can then start to eat.

In this manner, all philosophers can take turns eating and hence, all can survive.

### Case with 4 Philosophers

On the other hand, if there are only three philosophers, there would be only three forks available since there is one fork between each philosopher.

If each philosopher picks up the fork to their right at the same time, all forks will be in use, and none of the philosophers will be able to pick up a left fork to start eating.

In this situation, since all are holding only one fork, none can begin eating.

If this deadlock persists, the philosophers will starve, and eventually, they will die as their life span of 410ms expires.

This situation is known as a deadlock, which is a well-documented problem in the dining philosophers issue, and various algorithms and strategies have been proposed to prevent it.

In summary, with four philosophers, there is always one philosopher waiting to eat and thinking, which prevents a deadlock. However, with three philosophers, all picking up the forks simultaneously leads to a deadlock and eventual death.

Lastly, after a philosopher dies, the program must halt, and the time of death for any philosopher should not exceed their lifespan by more than 10ms.

