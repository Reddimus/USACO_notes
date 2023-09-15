# Run file with: Get-Content sample.in | python P3_2020-Stuck_In_A_Rut.py

n = int(input().strip())
cow_data = []
for _ in range(n):
	data = input().split()
	direction = data[0]
	x = int(data[1])
	y = int(data[2])
	cow_data.append((direction, x, y))

east_cows = [i for i in range(n) if cow_data[i][0] == 'E']
north_cows = [i for i in range(n) if cow_data[i][0] == 'N']

x_coordinates = [cow_data[i][1] for i in range(n)]
y_coordinates = [cow_data[i][2] for i in range(n)]

east_cows.sort(key=lambda j: y_coordinates[j])
north_cows.sort(key=lambda j: x_coordinates[j])

stopped = [False] * n
amount_stopped = [0] * n

for j in east_cows:
	for k in north_cows:
		if (not stopped[j]) and (not stopped[k]) and (x_coordinates[k] > x_coordinates[j]) and (y_coordinates[j] > y_coordinates[k]):
			if (x_coordinates[k] - x_coordinates[j]) > (y_coordinates[j] - y_coordinates[k]):
				stopped[j] = True
				amount_stopped[k] += (1 + amount_stopped[j])
			elif (x_coordinates[k] - x_coordinates[j]) < (y_coordinates[j] - y_coordinates[k]):
				stopped[k] = True
				amount_stopped[j] += (1 + amount_stopped[k])
			
for amnt_stp in amount_stopped:
	print(amnt_stp)