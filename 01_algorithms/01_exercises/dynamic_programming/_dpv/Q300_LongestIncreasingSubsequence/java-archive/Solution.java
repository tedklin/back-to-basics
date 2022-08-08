package dynamic_programming._dpv.Q300_LongestIncreasingSubsequence;

public class Solution {

    public int lengthOfLIS(int[] nums) {
        int[] lenLisTable = new int[nums.length];  // lenLisTable[i] = length of LIS ending at i
        for (int i = 0; i < nums.length; i++) {
            int maxLenPrefixLis = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    maxLenPrefixLis = Math.max(maxLenPrefixLis, lenLisTable[j]);
                }
            }
            lenLisTable[i] = 1 + maxLenPrefixLis;
        }

        int maxLenLis = 1;
        for (int lenLis : lenLisTable) {
            maxLenLis = Math.max(maxLenLis, lenLis);
        }
        return maxLenLis;
    }

}
