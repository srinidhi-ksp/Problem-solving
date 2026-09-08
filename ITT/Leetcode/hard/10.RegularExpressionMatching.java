class Solution {
    public boolean isMatch(String s, String p) {
        if (s == null || p == null) {
            return false;
        }

        int m = s.length();
        int n = p.length();

        // dp[i][j] represents if s[0...i-1] matches p[0...j-1]
        boolean[][] dp = new boolean[m + 1][n + 1];

        // Base case: An empty string matches an empty pattern
        dp[0][0] = true;

        // Base case: Handle patterns like a*, a*b*, or c*a*b* matching an empty string s
        for (int j = 1; j <= n; j++) {
            if (p.charAt(j - 1) == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                char sChar = s.charAt(i - 1);
                char pChar = p.charAt(j - 1);

                // If characters match directly or pattern has '.'
                if (pChar == sChar || pChar == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                } 
                // If we encounter a '*' wild card
                else if (pChar == '*') {
                    // Scenario 1: Count '*' and its preceding character as 0 occurrences
                    dp[i][j] = dp[i][j - 2];

                    // Scenario 2: If the preceding character matches sChar (or is '.')
                    char precedingChar = p.charAt(j - 2);
                    if (precedingChar == sChar || precedingChar == '.') {
                        // Combine Scenario 1 (0 occurrences) and Scenario 2 (1+ occurrences)
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }
}
