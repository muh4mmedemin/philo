This project has been created as part of the 42 curriculum by muayna

---

## 📝 Description 

The purpose of this project is for us to understand the concept of threads in C language. In this project, we are solving the philo problem. To go into detail, each philosopher is a thread, and there must be as many forks as the number of philosophers. Also, the table must be round. Philosophers can only eat, sleep, and think. The user can provide these inputs in order: 

* `philo_count` 
* `time_to_die` 
* `time_to_eat` 
* `time_to_sleep` 
* `eat_count` (not mandatory)

Our goal is to keep the philosophers alive for as long as possible within these rules.

---

## ⚙️ Instructions

Make and cc must be available on your computer. 

* The `make` command will compile all files and produce a file named `philo`.
* `Make fclean` will delete all object files and the file named `philo`.
* `make clean` will delete all object files.
* `make re` will compile the files again and produce a file named `philo`.

### Usage
./philo philo_count time_to_die time_to_eat time_to_sleep eat_count(not required)
./philo 4 200 100 20
./philo 199 500 200 100 17

## Resources

I mostly used AI to ask questions. In other words, I had it scan the internet for me to speed things up. Other than that, I wrote all the code myself. This was the resource I looked at the most.

https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
