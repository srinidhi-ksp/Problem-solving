num_cases = int(input("Enter number of cases: "))
case_count = 0

while case_count < num_cases:
    X = int(input("Enter prize factor X: "))
    results = input("Enter game results (14 chars): ")

    c_points = 0
    n_points = 0

    # Process each of the 14 games
    i = 0
    while i < 14:
        outcome = results[i]
        if outcome == 'C':
            c_points += 2
        elif outcome == 'N':
            n_points += 2
        else: # It's a draw 'D'
            c_points += 1
            n_points += 1
        i += 1
    if c_points > n_points:
        prize = 60 * X
    elif n_points > c_points:
        prize = 40 * X
    else:
        prize = 55 * X

    print(prize)
    case_count += 1
