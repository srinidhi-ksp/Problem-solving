class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        // Ensure nums1 is the smaller array to minimize the binary search range
        if (nums1.length > nums2.length) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.length;
        int n = nums2.length;
        int totalLeft = (m + n + 1) / 2;
        
        int low = 0;
        int high = m;
        
        while (low <= high) {
            // Cut point in nums1
            int i = low + (high - low) / 2;
            // Corresponding cut point in nums2
            int j = totalLeft - i;
            
            // Boundary values around the cuts
            int left1 = (i == 0) ? Integer.MIN_VALUE : nums1[i - 1];
            int right1 = (i == m) ? Integer.MAX_VALUE : nums1[i];
            
            int left2 = (j == 0) ? Integer.MIN_VALUE : nums2[j - 1];
            int right2 = (j == n) ? Integer.MAX_VALUE : nums2[j];
            
            // Check if we found the perfect partition
            if (left1 <= right2 && left2 <= right1) {
                // If total number of elements is odd
                if ((m + n) % 2 != 0) {
                    return Math.max(left1, left2);
                }
                // If total number of elements is even
                return (Math.max(left1, left2) + Math.min(right1, right2)) / 2.0;
            } 
            // We cut too far right in nums1, move left
            else if (left1 > right2) {
                high = i - 1;
            } 
            // We cut too far left in nums1, move right
            else {
                low = i + 1;
            }
        }
        
        return 0.0;
    }
}
