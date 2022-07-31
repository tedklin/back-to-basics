package array;

import java.util.HashMap;
import java.util.Map;

public class Q001_TwoSum {

    public int[] twoSumNaive(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target) {
                    return new int[]{i, j};
                }
            }
        }
        return null;
    }

    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> seenValueToIndexMap = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (seenValueToIndexMap.containsKey(target - nums[i])) {
                return new int[]{i, seenValueToIndexMap.get(target - nums[i])};
            }
            seenValueToIndexMap.put(nums[i], i);
        }
        return null;
    }

}
