import matplotlib.pyplot as plt

"""
Elapsed Time vs Number of Processes (Example Data)
    1. 1024 Doubles:
        ◦ 2 processes: 0.000003 seconds
        ◦ 4 processes: 0.000007 seconds
        ◦ 6 processes: 0.000009 seconds
    2. 2048 Doubles:
        ◦ 2 processes: 0.000003 seconds
        ◦ 4 processes: 0.000008 seconds
        ◦ 6 processes: 0.000009 seconds
"""

# Elapsed Time (seconds) vs Number of Processes (with Fixed Message Size)
# Data for elapsed time vs number of processes with fixed message size
process_counts = [2, 4, 6]
times_fixed_message_size = [0.000003, 0.000007, 0.000009]  # Elapsed time in seconds

plt.plot(process_counts, times_fixed_message_size, marker='o', label='Message Size: 1024 doubles')

plt.xlabel('Number of Processes')
plt.ylabel('Elapsed Time (seconds)')
plt.title('MPI Reduction Performance vs Number of Processes\n(Fixed Message Size: 1024 doubles)')
plt.legend()
plt.grid(True)
plt.savefig("reduce_performance_fixed_message.png")
plt.show()



"""
Message Size vs Elapsed Time (Example Data)
    1. 2 Processes:
        ◦ 512 bytes: 0.000003 seconds
        ◦ 1024 bytes: 0.000003 seconds
        ◦ 2048 bytes: 0.000004 seconds
    2. 4 Processes:
        ◦ 512 bytes: 0.000005 seconds
        ◦ 1024 bytes: 0.000006 seconds
        ◦ 2048 bytes: 0.000010 seconds
"""

# Message Size vs Elapsed Time (with Fixed Number of Processes)
# Data for message size vs elapsed time with fixed number of processes
message_sizes = [512, 1024, 2048]  # Message sizes in doubles
times_fixed_processes = [0.000005, 0.000006, 0.000010]  # Elapsed time in seconds

plt.plot(message_sizes, times_fixed_processes, marker='o', label='Number of Processes: 4')

plt.xscale('log')  # Use log scale for message size
plt.xlabel('Message Size (doubles)')
plt.ylabel('Elapsed Time (seconds)')
plt.title('MPI Reduction Performance vs Message Size\n(Fixed Number of Processes: 4)')
plt.legend()
plt.grid(True)
plt.savefig("reduce_performance_fixed_processes.png")
plt.show()


