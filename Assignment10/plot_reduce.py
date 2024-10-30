import matplotlib.pyplot as plt


# Elapsed Time (seconds) vs Number of Processes (with Fixed Message Size)
# Data for elapsed time vs number of processes with fixed message size
process_counts = [2, 4, 8]
times_fixed_message_size = [0.000002, 0.000016, 0.000045]  # Elapsed time in seconds

plt.plot(process_counts, times_fixed_message_size, marker='o', label='Message Size: 1024 doubles')

plt.xlabel('Number of Processes')
plt.ylabel('Elapsed Time (seconds)')
plt.title('MPI Reduction Performance vs Number of Processes\n(Fixed Message Size: 1024 doubles)')
plt.legend()
plt.grid(True)
plt.savefig("reduce_performance_fixed_message.png")
plt.show()




# Message Size vs Elapsed Time (with Fixed Number of Processes)
# Data for message size vs elapsed time with fixed number of processes
message_sizes = [1024.0, 2048.0]  # Message sizes in doubles
times_fixed_processes = [0.000016, 0.000015]  # Elapsed time in seconds

plt.plot(message_sizes, times_fixed_processes, marker='o', label='Number of Processes: 4')

plt.xscale('log')  # Use log scale for message size
plt.xlabel('Message Size (doubles)')
plt.ylabel('Elapsed Time (seconds)')
plt.title('MPI Reduction Performance vs Message Size\n(Fixed Number of Processes: 4)')
plt.legend()
plt.grid(True)
plt.savefig("reduce_performance_fixed_processes.png")
plt.show()


