class Solution {
    public int reverse(int x) {
        int reversed = 0;
        
        while (x != 0) {
            int pop = x % 10; // Extract the last digit
            x /= 10;          // Remove the last digit from x
            
            // Check for positive overflow boundary
            if (reversed > Integer.MAX_VALUE / 10 || (reversed == Integer.MAX_VALUE / 10 && pop > 7)) {
                return 0;
            }
            
            // Check for negative underflow boundary
            if (reversed < Integer.MIN_VALUE / 10 || (reversed == Integer.MIN_VALUE / 10 && pop < -8)) {
                return 0;
            }
            
            // Safe to append the digit
            reversed = reversed * 10 + pop;
        }
        
        return reversed;
    }
}
