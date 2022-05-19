import matplotlib.pyplot as plt
import pandas as pd
df1=pd.read_csv("merge-normal-log.csv")
df2=pd.read_csv("merge-multithreaded-log.csv")
ax = df1.plot(x="Array Size",y="Total Time (in s)",label="Single-Threaded",color="green")
df2.plot(x="Array Size",y="Total Time (in s)",label="Multi-Threaded",color="purple",ax=ax,figsize=(15,10),fontsize=14,title="Merge Sort")
plt.ylabel("Time (In Seconds)", fontsize=18)
plt.xlabel("Number of Elements in Array", fontsize=18)
ax.title.set_fontsize(26)       #fontsize of "Merge Sort"
ax.legend(loc=2, prop={'size': 18}) #fontsize of legend "Single threaded etc"
ax.ticklabel_format(useMathText=True)   #replaces 1e9 with x10^9 
plt.ylim(0, 250)    #sets limit of y axis
plt.xlim(0, 1.1e9)  #sets limit of x axis
plt.savefig('merge-graph.png')
plt.show()