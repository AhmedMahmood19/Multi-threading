echo -e "\nNote:All Values must be Positive Integers in range [1,1000000000]\n"
echo "::Input range of array size to plot a graph for harmonic progression::"
read -p "Enter Max: " Max
read -p "Enter Min: " Min
if [[ ! $Max =~ ^[0-9]+$ || ! $Min =~ ^[0-9]+$ || $Max -gt 1000000000 || $Min -gt 1000000000 || $Max -lt 1 || $Min -lt 1 || $Max -le $Min ]] ; then
    echo "Incorrect Input! Exiting program"
    exit
fi
#compile the needed programs
gcc -o ../normal/harmonic.out ../normal/harmonic.c
gcc -o ../multithreaded/harmonic_parallel.out ../multithreaded/harmonic_parallel.c -lpthread
#setup headers for csv
echo "\"Array Size\",\"Total Time (in s)\"">../graph/harmonic-normal-log.csv
#save the Min value
N=$Min
#keep multiplying Min by 10 until u go over max at which point you just use max
while [[ $Min -lt $Max ]]
do
#\time is the command,-o outputs to file, -a appends to file, -f formats the output string, in the end is the program to be executed with command line args after it
    \time -a -o ../graph/harmonic-normal-log.csv -f "$Min,%e" ./../normal/harmonic.out $Min
    Min=$(( $Min * 10 ))
done
\time -a -o ../graph/harmonic-normal-log.csv -f "$Max,%e" ./../normal/harmonic.out $Max

#now make the file for parallel version
echo "\"Array Size\",\"Total Time (in s)\"">../graph/harmonic-multithreaded-log.csv
Min=$N
while [[ $Min -lt $Max ]]
do
    \time -a -o ../graph/harmonic-multithreaded-log.csv -f "$Min,%e" ./../multithreaded/harmonic_parallel.out $Min
    Min=$(( $Min * 10 ))
done
\time -a -o ../graph/harmonic-multithreaded-log.csv -f "$Max,%e" ./../multithreaded/harmonic_parallel.out $Max

python3 harmonic_graph.py