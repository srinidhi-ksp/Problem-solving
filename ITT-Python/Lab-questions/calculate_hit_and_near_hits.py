def calculate_hits_and_near_hits(code, guess):
    """
    Calculates hits (correct position) and near hits (wrong position)
    for a given code and guess string.
    """
    hits = 0
    near_hits = 0
    
    # Store length to avoid calling len() repeatedly
    n = len(code)
    
    # Lists to keep track of characters that are already used in a hit or near hit
    code_used = [False] * n
    guess_used = [False] * n

    # Step 1: Calculate Hits (Correct digit in correct position)
    for i in range(n):
        if guess[i] == code[i]:
            hits += 1
            code_used[i] = True
            guess_used[i] = True

    # Step 2: Calculate Near Hits (Correct digit in wrong position)
    for i in range(n):
        if not guess_used[i]:
            for j in range(n):
                if not code_used[j] and guess[i] == code[j]:
                    near_hits += 1
                    code_used[j] = True
                    # guess_used[i] = True # Not strictly necessary here, but good practice
                    break

    return f"{hits}H{near_hits}N"

def main():
    print("--- Hit & Near Hit Game ---")
    
    # Get user input for the secret code
    code = input("Enter the secret code: ").strip()
    
    while True:
        # Get user input for the guess
        guess = input("Enter your guess: ").strip()
        
        # Validation
        if len(code) != len(guess):
            print(f"Error: Guess must be exactly {len(code)} digits long.")
            continue
        if not guess.isdigit():
            print("Error: Guess must contain only digits.")
            continue

        # Calculate result
        result = calculate_hits_and_near_hits(code, guess)
        print(f"Output: {result}")
        
        # End game if guessed correctly
        if result == f"{len(code)}H0N":
            print("Congratulations! You guessed it.")
            break

if __name__ == "__main__":
    main()

