*This project has been created as part of the 42 curriculum by muayna*

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
* `make fclean` will delete all object files and the file named `philo`.
* `make clean` will delete all object files.
* `make re` will compile the files again and produce a file named `philo`.

### Usage
./philo philo_count time_to_die time_to_eat time_to_sleep eat_count(not required)
./philo 4 200 100 20
./philo 199 500 200 100 17

## Resources

I mostly used AI to ask questions. In other words, I had it scan the internet for me to speed things up. Other than that, I wrote all the code myself. This was the resource I looked at the most.

## 🤖 AI Usage

AI tools (specifically LLMs) were utilized during the development of this project to accelerate the research process, clarify complex multi-threading concepts, and debug edge cases. However, all project code was written manually from scratch, ensuring a deep, firsthand understanding of data races and synchronization.

## Garbage Collector
The garbage_collector system I used in this project was taken from this repo: [garbage_collector](https://github.com/muh4mmedemin/garbage_collector)
I had used this garbage_collector in the minishell project, and I added and used the exact same one in my individual project as well. Details are available on the project page of the gb.
Garbage_collector made by [yademirk](https://github.com/YeDemirkiran) & [muayna](https://github.com/muh4mmedemin)

https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
