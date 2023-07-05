'''
USACO 2017 January Contest, Silver
Problem 1. Cow Dance Show

After several months of rehearsal, the cows are just about ready to put on their annual dance 
performance; this year they are performing the famous bovine ballet "Cowpelia".

The only aspect of the show that remains to be determined is the size of the stage. A stage 
of size K can support K cows dancing simultaneously. The N cows in the herd (1≤N≤10,000) 
are conveniently numbered 1…N in the order in which they must appear in the dance. Each 
cow i plans to dance for a specific duration of time d(i). Initially, cows 1…K appear 
on stage and start dancing. When the first of these cows completes her part, she leaves 
the stage and cow K+1 immediately starts dancing, and so on, so there are always K cows 
dancing (until the end of the show, when we start to run out of cows). The show ends when 
the last cow completes her dancing part, at time T.

Clearly, the larger the value of K, the smaller the value of T. Since the show cannot last 
too long, you are given as input an upper bound Tmax specifying the largest possible value 
of T. Subject to this constraint, please determine the smallest possible value of K.

INPUT FORMAT (file cowdance.in):
The first line of input contains N and Tmax, where Tmax is an integer of value at most 1 million.

The next N lines give the durations d(1)…d(N) of the dancing parts for cows 1…N. Each d(i) 
value is an integer in the range 1…100,000.

It is guaranteed that if K=N, the show will finish in time.

OUTPUT FORMAT (file cowdance.out):
Print out the smallest possible value of K
 such that the dance performance will take no more than Tmax
 units of time.
SAMPLE INPUT:
5 8
4
7
8
6
4
SAMPLE OUTPUT:
4
'''