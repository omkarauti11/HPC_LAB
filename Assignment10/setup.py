import numpy as np
import os

def create_matrix_file(filename, rows=512, cols=512):
    # Create the directory if it doesn't exist
    directory = os.path.dirname(filename)
    if not os.path.exists(directory):
        os.makedirs(directory)

    # Generate a matrix of random floating-point numbers
    matrix = np.random.rand(rows, cols)
    
    # Write the matrix to the file
    with open(filename, 'w') as f:
        for row in matrix:
            row_str = ' '.join(f'{val:.6f}' for val in row)
            f.write(row_str + '\n')

# Create sample/in1 and sample/in2 files
create_matrix_file('sample/in1')
create_matrix_file('sample/in2')

print("Files sample/in1 and sample/in2 have been created if they did not exist.")
