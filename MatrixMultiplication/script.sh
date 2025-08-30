#! /bin/bash
echo "10, 100, 200, 500, 1000, 2000" >execution_times.csv
for j in {1..10}; do
  for i in 10 100 200 500 1000 2000; do
    ./serial.exe $i >>execution_times.csv
  done
  echo "" >>execution_times.csv
done
