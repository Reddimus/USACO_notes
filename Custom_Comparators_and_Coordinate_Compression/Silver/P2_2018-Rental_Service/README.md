# USACO 2018 January Contest, Silver
## Problem 2. Rental Service

Farmer John realizes that the income he receives from milk production is insufficient to fund the growth of his farm, so to earn some extra money, he launches a cow-rental service, which he calls "USACOW" (pronounced "Use-a-cow").

Farmer John has `N` cows `(1≤N≤100,000)`, each capable of producing some amount of milk every day. The `M` stores near FJ's farm `(1≤M≤100,000)` each offer to buy a certain amount of milk at a certain price. Moreover, Farmer John's `R` `(1≤R≤100,000)` neighboring farmers are each interested in renting a cow at a certain price.

Farmer John has to choose whether each cow should be milked or rented to a nearby farmer. Help him find the maximum amount of money he can make per day.

**INPUT FORMAT (file rental.in):**  

The first line in the input contains `N`, `M`, and `R`. The next `N` lines each contain an integer `ci` `(1≤ci≤1,000,000)`, indicating that Farmer John's ith cow can produce `ci` gallons of milk every day. The next `M` lines each contain two integers `qi` and `pi` `(1≤qi,pi≤1,000,000)`, indicating that the ith store is willing to buy up to qi gallons of milk for pi cents per gallon. Keep in mind that Farmer John can sell any amount of milk between zero and `qi` gallons to a given store. The next `R` lines each contain an integer `ri` `(1≤ri≤1,000,000)`, indicating that one of Farmer John's neighbors wants to rent a cow for `ri` cents per day.

**OUTPUT FORMAT (file rental.out):**  

The output should consist of one line containing the maximum profit Farmer John can make per day by milking or renting out each of his cows. Note that the output might be too large to fit into a standard 32-bit integer, so you may need to use a larger integer type like a "long long" in C/C++.  

**SAMPLE INPUT:**  
```
5 3 4  
6  
2  
4  
7  
1  
10 25  
2 10  
15 15  
250  
80  
100  
40  
```
**SAMPLE OUTPUT:**  
```
725  
```
Farmer John should milk cows #1 and #4, to produce 13 gallons of milk. He should completely fill the order for 10 gallons, earning 250 cents, and sell the remaining three gallons at 15 cents each, for a total of 295 cents of milk profits.

Then, he should rent out the other three cows for 250, 80, and 100 cents, to earn 430 more cents. (He should leave the request for a 40-cent rental unfilled.) This is a total of 725 cents of daily profit.

http://www.usaco.org/index.php?page=viewproblem2&cpid=787