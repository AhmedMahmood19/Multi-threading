import matplotlib.pyplot as plt
import pandas as pd
df1=pd.read_csv("quick-normal-log.csv")
df2=pd.read_csv("quick-multithreaded-log.csv")
ax = df1.plot(x="Array Size",y="Total Time (in s)",label="Single-Threaded",color="green")
df2.plot(x="Array Size",y="Total Time (in s)",label="Multi-Threaded",color="purple",ax=ax,figsize=(15,10),fontsize=14,title="Quick Sort")
plt.ylabel("Time (In Seconds)", fontsize=18)
plt.xlabel("Number of Elements in Array", fontsize=18)
ax.title.set_fontsize(26)  
ax.legend(loc=2, prop={'size': 18})
ax.ticklabel_format(useMathText=True)
plt.ylim(0, 200)    
plt.xlim(0, 1.1e9)  
plt.show()