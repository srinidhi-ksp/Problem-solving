public class Solution {
    public int longestValidParentheses(String s) {
        if (s == null || s.length() < 2) {
            return 0;
        }
        
        int n = s.length();
        int[] dp = new int[n];
        int maxLen = 0;
        
        // Start from index 1 because no valid substring can end at index 0
        for (int i = 1; i < n; i++) {
            if (s.charAt(i) == ')') {
                // Case 1: Substring ends with "()"
                if (s.charAt(i - 1) == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } 
                // Case 2: Substring ends with "))"
                else {
                    int lookBack = i - dp[i - 1] - 1;
                    // Check if there is a matching '(' at the lookBack index
                    if (lookBack >= 0 && s.charAt(lookBack) == '(') {
                        int beforeLookBack = (lookBack >= 1) ? dp[lookBack - 1] : 0;
                        dp[i] = dp[i - 1] + 2 + beforeLookBack;
                    }
                }
                // Track the maximum length found so far
                maxLen = Math.max(maxLen, dp[i]);
            }
        }
        
        return maxLen;
    }
}
