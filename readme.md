*This project has been created as part of the 42 curriculum by spaipur-.*

## Description
This project explores the basics of threading a process. It implements the classic Dining Philosophers problem using threads and mutexes to manage shared resources (forks) and prevent deadlocks.

## Instructions
1. Compile the project using `make`.
2. Run the executable: `./philo [n_philos] [time_die] [time_eat] [time_sleep] [optional_must_eat]`.
   Example: `./philo 5 800 200 200`

## Resources
- [The Dining Philosophers Problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Pthread Library Documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- **AI Usage**: AI was used for understanding how to debug race conditions, explaining `pthread_mutex` logic, and high-precision timing functions (`precise_usleep`).