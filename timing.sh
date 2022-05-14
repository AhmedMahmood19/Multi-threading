#\time is the cmd,-o outputs to file, -a appends to file, -f formats the output string, in the end is the program to be executed with command line args after it

gcc -o normal/mergesort.out normal/mergesort.c
gcc -o multithreaded/Tmergesort.out multithreaded/Tmergesort.c -lpthread

n=10000
echo "\"Size\",\"Total Time (in s)\",\"Max RSS (in KB)\"">merge-normal-log.csv
for i in {1..6}
do
\time -a -o merge-normal-log.csv -f "$n,%e,%M" ./normal/mergesort.out $n
((n=$n*10))
done

n=10000
echo "\"Size\",\"Total Time (in s)\",\"Max RSS (in KB)\"">merge-multithreaded-log.csv
for i in {1..6}
do
\time -a -o merge-multithreaded-log.csv -f "$n,%e,%M" ./multithreaded/Tmergesort.out $n
((n=$n*10))
done