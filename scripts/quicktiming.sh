#\time is the command,-o outputs to file, -a appends to file, -f formats the output string, in the end is the program to be executed with command line args after it

gcc -o ../normal/quicksort.out ../normal/quicksort.c
gcc -o ../multithreaded/quicksort_parallel.out ../multithreaded/quicksort_parallel.c -lpthread

n=10000
echo "\"Array Size\",\"Total Time (in s)\"">../graph/quick-normal-log.csv
for i in {1..6}
do
\time -a -o ../graph/quick-normal-log.csv -f "$n,%e" ./../normal/quicksort.out $n
((n=$n*10))
done

n=10000
echo "\"Array Size\",\"Total Time (in s)\"">../graph/quick-multithreaded-log.csv
for i in {1..6}
do
\time -a -o ../graph/quick-multithreaded-log.csv -f "$n,%e" ./../multithreaded/quicksort_parallel.out $n
((n=$n*10))
done