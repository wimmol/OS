import threading
import time
import random


def wait():
    time.sleep(random.uniform(0, 1))


class Fork:
    def __init__(self):
        self.locker = threading.Lock()

    def pick_up(self):
        self.locker.acquire()

    def put_on(self):
        self.locker.release()


class Philosopher:
    def __init__(self, index):
        self.index = index
        self.hunger_rate = 0

    def on_the_table(self):
        while True:
            print(f'{self} thinking')
            wait()
            print(f'{self} is hungry')
            while True:
                if ask(self.index):
                    forks[self.index].pick_up()
                    forks[(self.index - 1) % 5].pick_up()
                    self.hunger_rate = 0
                    print(f'{self} eating')
                    wait()
                    forks[self.index].put_on()
                    forks[(self.index - 1) % 5].put_on()
                    print(f'{self} finished eating')
                    break
                else:
                    self.hunger_rate = self.hunger_rate + 1
                    print(f'{self} cant eat now')
                    wait()

    def __repr__(self):
        return threading.currentThread().name


def ask(index):
    forks_is_blocked = forks[index].locker.locked() or forks[(index - 1) % 5].locker.locked()
    next_neighbor_is_more_hungry = philosophers[index].hunger_rate < philosophers[(index + 1) % 5].hunger_rate
    previous_neighbor_is_more_hungry = philosophers[index].hunger_rate < philosophers[(index - 1) % 5].hunger_rate
    if forks_is_blocked or next_neighbor_is_more_hungry or previous_neighbor_is_more_hungry:
        return False
    else:
        return True


forks = []
philosophers = []

for i in range(5):
    forks.append(Fork())

for i in range(5):
    philosophers.append(Philosopher(i))

for philosopher in philosophers:
    threading.Thread(target=philosopher.on_the_table).start()
