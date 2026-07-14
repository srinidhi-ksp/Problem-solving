import java.util.Collections;
import java.util.PriorityQueue;

class MedianFinder {
    private PriorityQueue<Integer> smallMaxHeap; // Stores the smaller half
    private PriorityQueue<Integer> largeMinHeap; // Stores the larger half

    public MedianFinder() {
        // Max-heap needs Collections.reverseOrder() in Java
        this.smallMaxHeap = new PriorityQueue<>(Collections.reverseOrder());
        this.largeMinHeap = new PriorityQueue<>();
    }
    
    public void addNum(int num) {
        // Step 1: Always add to the max-heap first
        smallMaxHeap.add(num);
        
        // Step 2: Balance check - ensure every element in smallMaxHeap <= elements in largeMinHeap
        largeMinHeap.add(smallMaxHeap.poll());
        
        // Step 3: Maintain size property (smallMaxHeap size >= largeMinHeap size)
        if (smallMaxHeap.size() < largeMinHeap.size()) {
            smallMaxHeap.add(largeMinHeap.poll());
        }
    }
    
    public double findMedian() {
        // If total size is odd, the median is the top of the max-heap
        if (smallMaxHeap.size() > largeMinHeap.size()) {
            return smallMaxHeap.peek();
        }
        // If total size is even, take the average of both tops
        return (smallMaxHeap.peek() + largeMinHeap.peek()) / 2.0;
    }
}
