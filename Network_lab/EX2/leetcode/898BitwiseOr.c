class Solution {
    public int subarrayBitwiseORs(int[] arr) {

        // Stores all unique OR values of all subarrays
        Set<Integer> result = new HashSet<>();

        // Stores OR values of subarrays ending at previous index
        Set<Integer> current = new HashSet<>();

        for (int num : arr) {

            Set<Integer> next = new HashSet<>();

            // Start new subarray with current element
            next.add(num);

            // Extend all previous subarrays
            for (int val : current) {
                next.add(val | num);
            }

            // Update current set
            current = next;

            // Add all values to final answer set
            result.addAll(current);
        }

        return result.size();
    }
}
