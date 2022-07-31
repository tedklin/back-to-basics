package tree.b_nontrivial.Q230_KthSmallestElementBST;

import tree.TreeNode;

public class Solution {

    int numNodesSeenSoFar;
    int kthSmallestVal;

    public int kthSmallest(TreeNode root, int k) {
        numNodesSeenSoFar = 0;
        kthSmallestVal = -1;  // dummy initializer

        kthSmallestHelper(root, k);

        return kthSmallestVal;
    }

    public void kthSmallestHelper(TreeNode node, int k) {
        if (node == null) {
            return;
        }

        kthSmallestHelper(node.left, k);
        numNodesSeenSoFar++;
        if (numNodesSeenSoFar == k) {
            kthSmallestVal = node.val;
        }
        if (numNodesSeenSoFar >= k) {
            return;
        }
        kthSmallestHelper(node.right, k);
    }

}
