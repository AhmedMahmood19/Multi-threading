#\time is the cmd,-o outputs to file, -a appends to file, -f formats the output string, in the end is the program to be executed with command line args after it
n=10000
for i in {1..6}
do
\time -a -o log.txt -f "Total Time(s): %e\nUser Mode Time(s): %U\nKernel Mode Time(s): %S\nMax RSS(KB): %M\nAvg RSS(KB): %t\nAvg Total memory use(KB): %K\n" ./normal/abc $n
((n=$n*10))
done