class Solution {
    public String longestPalindrome(String s) {
        if (s == null || s.length() < 1) {
            return "";
        }
        
        int start = 0;
        int end = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // Case 1: Odd-length palindromes (centered at character i)
            int len1 = expandAroundCenter(s, i, i);
            
            // Case 2: Even-length palindromes (centered between characters i and i+1)
            int len2 = expandAroundCenter(s, i, i + 1);
            
            // Get the maximum length found from this position
            int maxLen = Math.max(len1, len2);
            
            // If we found a palindrome longer than our previous best, update boundaries
            if (maxLen > (end - start + 1)) {
                start = i - (maxLen - 1) / 2;
                end = i + maxLen / 2;
            }
        }
        
        // Return the substring using our tracked boundaries
        return s.substring(start, end + 1);
    }
    
    // Helper function to expand outwards and return the length of the palindrome
    private int expandAroundCenter(String s, int left, int right) {
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        // Returns the length of the valid palindromic substring found
        return right - left - 1;
    }
}
