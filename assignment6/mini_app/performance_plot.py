#!/usr/bin/python
import subprocess
import matplotlib
matplotlib.use('Agg')
import pylab as plt
import numpy as np
results = {}
import os
sizes = [64, 128, 256]
for size in sizes:
    results[size] = []

    for num_threads in range(1, 11):
        os.putenv("OMP_NUM_THREADS", str(num_threads))
        result = subprocess.Popen(
            "mpirun -np 1 ./main {} {} 100 0.01".format(size, size).split(), stdout=subprocess.PIPE).communicate()[0]
        results[size].append(result.decode('utf-8'))

# print(results[64][0].split()[37])

times = {}
threads = np.arange(1, 11, 1)
threads = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
for size in sizes:
    times[size] = []
    for num_threads in range(0, 10):
        times[size].append(results[size][num_threads].split()[57])

# 1: 57
# 2: 72
# 4: 102
#print(threads, np.array(times[64]).size)

for size in sizes:
    plt.plot(threads, times[size], label=str(size))
plt.xlabel('Number of Threads')
plt.ylabel('Time [s]')
plt.title('Performance')
plt.legend(loc='upper right')
fig = plt.gcf()
fig.savefig('pyplot.png', dpi=72)
