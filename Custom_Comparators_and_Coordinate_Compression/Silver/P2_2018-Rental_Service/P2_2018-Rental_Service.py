# Custom Comparators + Sort + Greedy approach
# T: O(n * m), M: O(n + m + r) 
# Where n is num of cows, m is num of shops, and r is num of neighbors

class Shop:
	def __init__(self, demand: int, rate: int) -> None:
		self.demand = demand
		self.rate = rate

# Open input file
with open('rental.in', 'r') as f:
	# Read first line: n = num of cows, m = num of shops, r = num of neighbors
	n, m, r = map(int, f.readline().split())
	# For the next n lines track milk produced per cow
	milk = [int(f.readline()) for jugs in range(n)]
	# For the next m lines track demand of milk and rate of milk from shops
	shops = [Shop(*map(int, f.readline().split())) for shop_customer in range(m)]
	# For the next r lines track neighbor rent a cow rate
	rent = [int(f.readline()) for neighbor_customer in range(r)]

# We always want to look at the cow that can potentially produce the most milk first
milk.sort(reverse=True)
shops.sort(reverse=True, key=lambda s: s.rate)
rent.sort(reverse=True)

# Calculate maximum revenue
revenue = 0
cached_price = False
cow_idx, shop_idx, rent_idx = 0, 0, 0
while (cow_idx < n):
	if not cached_price:
		# Calculate potential revenue if cow were to be milked
		jugs = milk[cow_idx]
		jugs_price = 0
		last_sold = 0
		temp_idx = shop_idx
		while temp_idx < m:
			sold = min(jugs, shops[temp_idx].demand)
			jugs_price += sold * shops[temp_idx].rate
			jugs -= sold
			if jugs == 0:
				last_sold = sold
				break
			temp_idx += 1

	# Compare rent a cow price to potential milked price
	if rent_idx < r and rent[rent_idx] > jugs_price:
		revenue += rent[rent_idx]
		cached_price = True	# save unused price for next iteration
		rent_idx += 1
		n -= 1	# rent cow that produces the least milk
	else:
		revenue += jugs_price
		shop_idx = temp_idx
		if temp_idx < m:
			shops[shop_idx].demand -= last_sold
		cached_price = False
		cow_idx += 1

# Write maximum profit to rental output file 
print(revenue, file=open('rental.out', 'w'))

'''
# Expanded solution
# T: O(n * m), M: O(n + m + r), where n is the number of cows, m is the number of shops, and r is the number of neighbors
class Shop:
	def __init__(self, demand: int, rate: int) -> None:
		self.demand = demand
		self.rate = rate

# Open input file
with open('Custom_Comparators_and_Coordinate_Compression/Silver/P2_2018-Rental_Service/rental.in', 'r') as f:
	# read first line: n = num of cows, m = num of shops, r = num of neighbors
	n, m, r = map(int, f.readline().split())
	print(f'number of cows = n = {n}, number of shops = m = {m}, number of neighbors = r = {r}')
	# For the next n lines track milk produced per cow
	milk = [0] * n
	for cow in range(n):
		milk[cow] = int(f.readline())
	print('milk produced per cow in gallons:')
	print(milk)
	# For the next m lines track demand of milk and price of milk from shops
	shops = [0] * m
	for customer in range(m):
		shops[customer] = Shop(*map(int, f.readline().split()))
	print('Quantity demand of milk gallons and cents per gallon from shops:')
	for shop in shops:
		print(f'({shop.demand}, {shop.rate})', end=' ')
	print()
	# For the next r lines track neighbor rent a cow rate
	rent = [0] * r
	for neighbor in range(r):
		rent[neighbor] = int(f.readline())
	print('Neighbor rent a cow cents per day rate:')
	print(rent)
print()

# Sort in reverse, we always want to milk the cow that produces the most milk
milk.sort(reverse=True)
shops.sort(reverse=True, key=lambda s: s.rate)
rent.sort(reverse=True)

print('After sorting:')
print('milk produced per cow in gallons:')
print(milk)
print('Quantity demand of milk gallons and cents per gallon from shops:')
for shop in shops:
	print(f'({shop.demand}, {shop.rate})', end=' ')
print()
print('Neighbor rent a cow cents per day rate:')
print(rent)
print()

# Calculate maximum profit
money = 0
cached_price = 0
cow_idx, rent_idx, shop_idx = 0, 0, 0
while cow_idx < n:
	if cached_price:
		jugs_price = cached_price
	else:
		# Calculate potential profit if cow were to be milked
		jugs = milk[cow_idx]
		tmp_jugs = int(jugs)
		jugs_price = 0
		tmp_idx = shop_idx
		last_amt = 0
		while tmp_idx < m:
			sold = min(jugs, shops[tmp_idx].demand)
			jugs_price += sold * shops[tmp_idx].rate
			jugs -= sold
			if jugs == 0:
				last_amt = sold
				break
			tmp_idx += 1
	
	print(f'Observe Cow #{cow_idx} that can produce {tmp_jugs} gallons of milk:	gallons of milk max price = {jugs_price}, rent a cow price {rent[rent_idx]}')

	# if renting a cow is more profitable than selling milk
	if rent_idx < r and rent[rent_idx] > jugs_price:
		print(f'Cow #{n} that produces {milk[n-1]}, rented for {rent[rent_idx]}')
		money += rent[rent_idx]
		rent_idx += 1
		cached_price = jugs_price
		n -= 1

	else:
		print(f'Cow #{cow_idx} that produces {milk[cow_idx]}, sold milk for {jugs_price}')
		money += jugs_price
		shop_idx = tmp_idx
		if tmp_idx < m:
			shops[shop_idx].demand -= last_amt
		cached_price = 0
		cow_idx += 1
	print()

# Write maximum profit to rental output file
print(money, file=open('Custom_Comparators_and_Coordinate_Compression/Silver/P2_2018-Rental_Service/rental.out', 'w'))
'''