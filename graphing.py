#
#   Tony Misic 500759917 
#   Daniel Bellissimo 500749419
#   CPS841 Assignment 3 Question 2
#   Algorithm to graph all values for comparisons
#
from bokeh.plotting import figure, output_file, show
file = open("output/mc.txt", "r")
data = file.readlines()
x_data = []
y_data = []
count = 1
for string in data:
    new_data = string.split(" ")
    x_data.append(new_data[0])
    y_data.append(float(new_data[1]) / count) # returns average can be changed
    count += 1
file.close()

file2 = open("output/sarsa.txt", "r")
data2 = file2.readlines()
x_data2 = []
y_data2 = []
count2 = 1
for string in data2:
    new_data2 = string.split(" ")
    x_data2.append(new_data2[0])
    y_data2.append(float(new_data2[1]) / count2) # returns average can be changed
    count2 += 1
file2.close()

file3 = open("output/q.txt", "r")
data3 = file3.readlines()
x_data3 = []
y_data3 = []
count3 = 1
for string3 in data3:
    new_data3 = string3.split(" ")
    x_data3.append(new_data3[0])
    y_data3.append(float(new_data3[1]) / count3) # returns average can be changed
    count3 += 1

file3.close()

output_file("output.html")
p = figure(title="Reinforcement Learning A3", width=1500, height=800,x_axis_label='Rounds', y_axis_label='Average')
labels = ["Monte-Carlo", "SARSA", "Q-Learning"]
colors = ["firebrick", "navy", "green"]
data = [[x_data,y_data], [x_data2,y_data2], [x_data3,y_data3]]
for name, color, d in zip(labels, colors, data):
    p.line(d[0], d[1], line_width=2, color=color, legend=name)
p.legend.location = "top_left"
p.legend.click_policy="hide"
show(p)