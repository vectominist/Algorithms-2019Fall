# PA1
Author: Heng-Jui Chang
Date: 2019.10.11

This program supports four different sorting methods: insertion sort, merge sort, quick sort and heap sort.

## Directories

```
bin/	  executable binary
doc/	  reports
inputs/   input data (unsorted)
outputs/  output result (sorted)
lib/	  library
src/ 	  source C++ codes
utility/  checker
```

## How to compile?

Then compile the demo, simply follow the following steps.
```
make
```


## How to run?
```
./bin/NTU_sort -[IS|MS|QS|HS] <input_file_name> <output_file_name>
```

## How to verify the results

```
cd utility/
./PA1_Result_Checker <input_file> <result_file_name>
```

## Other
If your code run well for small test case but get **Segmentation Fault** for the large test case, you can use the the following commend to increase the stack size to 256MB:
```
ulimit -s 262144
```
