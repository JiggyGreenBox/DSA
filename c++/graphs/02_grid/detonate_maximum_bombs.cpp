/*
2101. Detonate the Maximum Bombs
    [https://leetcode.com/problems/detonate-the-maximum-bombs/description/]

You are given a list of bombs. The range of a bomb is defined as the 
area where its effect can be felt. This area is in the shape of a 
circle with the center as the location of the bomb.

The bombs are represented by a 0-indexed 2D integer array bombs where 
bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and 
Y-coordinate of the location of the ith bomb, whereas ri denotes the 
radius of its range.

You may choose to detonate a single bomb. When a bomb is detonated, 
it will detonate all bombs that lie in its range. These bombs will 
further detonate the bombs that lie in their ranges.

Given the list of bombs, return the maximum number of bombs that can 
be detonated if you are allowed to detonate only one bomb.


*/

/*

2101. Detonate the Maximum Bombs
    we are given bombs [0..n-1]

        for each bomb we have a coordinate
            we have a radius

            for each other bomb[i]
                we can get dist as d = sqrtRoot[] (x2-x1)^2 + (y2-y1)^2]

                then (x[i]-x)^2 + (y[i]-y)^2 <= radius
                    valid
                        push into adj[]

        then for each adj
            we have to travel the graph
                because b1...b2, b2 can further denotate b5
            ans = max(count of nei)

*/

/*
2101 Detonate Maximum Bombs

For every bomb i:
    check every bomb j

        can i detonate j?
            ↓
        distance² <= radius[i]²
            ↓
        add directed edge i → j

After graph construction:

for every bomb i:
    DFS/BFS from i
    count reachable bombs

answer = maximum count
*/