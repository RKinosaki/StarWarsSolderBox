import math

samples = 100
start_pos = 20
end_pos = 92
pos_range = abs(end_pos - start_pos)

step = 1/(samples-1)

waypoints = []


for i in range(samples):
    x = i*step
    y = -(math.cos(math.pi*x)-1)/2
    if(start_pos>end_pos):
        y=abs(y*pos_range - start_pos)
    else:
        y = y*pos_range + start_pos
    y = round(y, 0)
    waypoints.append(y)


print(waypoints)