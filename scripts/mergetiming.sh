#\time is the command,-o outputs to file, -a appends to file, -f formats the output string, in the end is the program to be executed with command line args after it

gcc -o ../normal/mergesort.out ../normal/mergesort.c
gcc -o ../multithreaded/mergesort_parallel.out ../multithreaded/mergesort_parallel.c -lpthread

n=10000
echo "\"Array Size\",\"Total Time (in s)\"">../graph/merge-normal-log.csv
for i in {1..6}
do
\time -a -o ../graph/merge-normal-log.csv -f "$n,%e" ./../normal/mergesort.out $n
((n=$n*10))
done

n=10000
echo "\"Array Size\",\"Total Time (in s)\"">../graph/merge-multithreaded-log.csv
for i in {1..6}
do
\time -a -o ../graph/merge-multithreaded-log.csv -f "$n,%e" ./../multithreaded/mergesort_parallel.out $n
((n=$n*10))
done