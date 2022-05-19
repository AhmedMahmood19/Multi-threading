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

##############################################

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

##############################################

gcc -o ../normal/harmonic.out ../normal/harmonic.c
gcc -o ../multithreaded/harmonic_parallel.out ../multithreaded/harmonic_parallel.c -lpthread

n=1000000
echo "\"Array Size\",\"Total Time (in s)\"">../graph/harmonic-normal-log.csv
for i in {1..11}
do
\time -a -o ../graph/harmonic-normal-log.csv -f "$n,%e" ./../normal/harmonic.out $n
((n=$n*2))
done

n=1000000
echo "\"Array Size\",\"Total Time (in s)\"">../graph/harmonic-multithreaded-log.csv
for i in {1..11}
do
\time -a -o ../graph/harmonic-multithreaded-log.csv -f "$n,%e" ./../multithreaded/harmonic_parallel.out $n
((n=$n*2))
done

###############################################

python3 quick_graph.py
python3 merge_graph.py
python3 harmonic_graph.py