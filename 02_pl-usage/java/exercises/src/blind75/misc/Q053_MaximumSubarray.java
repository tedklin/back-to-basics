package blind75.misc;

public class Q053_MaximumSubarray {

    public int maxSubArray(int[] nums) {
        int globalMaxSum = nums[0];
        int localMaxSum = nums[0];
        for (int i = 1; i < nums.length; i++) {
            localMaxSum = Math.max(nums[i], localMaxSum + nums[i]);
            globalMaxSum = Math.max(globalMaxSum, localMaxSum);
        }
        return globalMaxSum;
    }

}