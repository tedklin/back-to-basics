package blind75.tree;

import java.util.Stack;

public class Q230_KthSmallestElementBST {

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
