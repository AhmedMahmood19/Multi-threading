import matplotlib.pyplot as plt
import pandas as pd
df1=pd.read_csv("../graph/merge-normal-log.csv")
df2=pd.read_csv("../graph/merge-multithreaded-log.csv")
ax = df1.plot(x="Array Size",y="Total Time (in s)",label="Single-Threaded",color="dodgerblue",alpha=1,linewidth=2)
df2.plot(x="Array Size",y="Total Time (in s)",label="Multi-Threaded",color="darkorange",alpha=0.5,linewidth=5,ax=ax,figsize=(15,10),fontsize=14,title="Merge Sort")
plt.ylabel("Time (In Seconds)", fontsize=18)
plt.xlabel("Number of Elements in Array", fontsize=18)
ax.title.set_fontsize(26)       #fontsize of "Merge Sort"
ax.legend(loc=2, prop={'size': 18}) #fontsize of legend "Single threaded etc"
ax.ticklabel_format(useMathText=True)   #replaces 1e9 with x10^9 
plt.savefig("../graph/merge-graph.png")
plt.show()