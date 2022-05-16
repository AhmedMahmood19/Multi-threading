import pandas as pd
import numpy as np
# import csv

# path = 'merge-normal-log.csv'
# with open(path, 'r') as f:
#     reader = csv.reader(f, delimiter=',')
#     headers = next(reader)
#     data = np.array(list(reader)).astype(float)
    
# print(headers)
# data = pd.read_csv("merge-normal-log.csv", delimiter=",")
# print()
# data.plot(x='data.columns[0]', y='data.columns[1]')

df=pd.DataFrame([1,4,6,8])
df.hist()
# import matplotlib.pyplot as plt

# x = np.linspace(0, 20, 100)
# plt.plot(x, np.sin(x))
# plt.show()