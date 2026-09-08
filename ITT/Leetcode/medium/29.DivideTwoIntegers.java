class Solution {
    public int divide(int dividend, int divisor) {
        // 1. Handle the only overflow case up front
        if (dividend == Integer.MIN_VALUE && divisor == -1) {
            return Integer.MAX_VALUE;
        }

        // 2. Figure out if the final answer should be negative
        boolean isNegative = (dividend < 0) ^ (divisor < 0);

        // 3. Turn numbers positive using 'long' so we don't break limits
        long amt = Math.abs((long) dividend);
        long div = Math.abs((long) divisor);
        int quotient = 0;

        // 4. The Main Loop
        while (amt >= div) {
            long tempDiv = div;
            int count = 1;

            // Keep doubling the divisor until it's about to exceed 'amt'
            while (amt >= (tempDiv + tempDiv)) {
                tempDiv += tempDiv; // Double the value
                count += count;     // Double the count
            }

            // Subtract the giant chunk we found
            amt -= tempDiv;
            // Add the count to our total answer
            quotient += count;
        }

        // 5. Apply the negative sign if needed
        return isNegative ? -quotient : quotient;
    }
}
