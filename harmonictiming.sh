#\time is the cmd,-o outputs to file, -a appends to file, -f formats the output string, in the end is the program to be executed with command line args after it

gcc -o normal/harmonic.out normal/harmonic.c
gcc -o multithreaded/harmonic_parallel.out multithreaded/harmonic_parallel.c -lpthread

n=1000000
echo "\"Array Size\",\"Total Time (in s)\"">graph/harmonic-normal-log.csv
for i in {1..11}
do
\time -a -o graph/harmonic-normal-log.csv -f "$n,%e" ./normal/harmonic.out $n
((n=$n*2))
done

n=1000000
echo "\"Array Size\",\"Total Time (in s)\"">graph/harmonic-multithreaded-log.csv
for i in {1..11}
do
\time -a -o graph/harmonic-multithreaded-log.csv -f "$n,%e" ./multithreaded/harmonic_parallel.out $n
((n=$n*2))
done