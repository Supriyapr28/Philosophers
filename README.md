*This project has been created as part of the 42 curriculum by spaipur-.*

## Description
This project explores the basics of threading a process. It implements the classic Dining Philosophers problem using threads and mutexes to manage shared resources (forks) and prevent deadlocks.

how can we prevent dealocks?

These four conditions are necessary for a deadlock to occur:

- mutual exclusion (no fork can be simultaneously used by multiple philosophers)
- resource holding (the philosophers hold a fork while waiting for the second)
- non-preemption (no philosopher can take a fork from another), and
- circular wait (each philosopher may be waiting on the philosopher to their left)

A solution must negate at least one of those four conditions. In practice, negating mutual exclusion or non-preemption somehow can give a valid solution, but most theoretical treatments assume that those assumptions are non-negotiable, instead attacking resource holding or circular waiting (often both)

## Instructions
1. Compile the project using 
```
make
```

2. Run the executable
```bash
 ./philo [n_philos] [time_die] [time_eat] [time_sleep] [optional_must_eat]
   Example: `./philo 5 800 200 200`
```
3. Memory leak checks

```bash
# Race-condition checks
valgrind --tool=helgrind ./philo 4 410 200 200

# Memory checks
valgrind --leak-check=full --show-leak-kinds=all ./philo 4 410 200 200
```
## Resources
- [The Dining Philosophers Problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Pthread Library Documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Mutex (Pthreads)](https://www.youtube.com/watch?v=raLCgPK-Igc&t=424s)
- **AI Usage**: AI was used for understanding how to debug race conditions.