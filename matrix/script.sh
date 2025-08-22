#! /bin/bash
echo "MatrixSize,ExecutionTime" >execution_times.csv
for j in {1..10}; do
  for i in 10 100 200 400 600 800 1000 2000; do
    START=$(date +%s.%N)
    ./matrix $i
    END=$(date +%s.%N)
    EXECUTION_TIME=$(echo "$END - $START" | bc)
    echo "$i,$EXECUTION_TIME" >>execution_times.csv
  done
done
