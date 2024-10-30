import matplotlib.pyplot as plt

# Sample data (replace with your actual results)
process_counts = [2, 4, 6]
times = [0.096738, 0.076443, 0.066525]

plt.plot(process_counts, times, marker='o', linestyle='-', color='b')
plt.xlabel('Number of Processes')
plt.ylabel('Elapsed Time (seconds)')
plt.title('MPI Broadcast Performance with Fixed Message Size')
plt.grid(True)

# Save the figure as a PNG image
plt.savefig("broadcast_performance.png")
