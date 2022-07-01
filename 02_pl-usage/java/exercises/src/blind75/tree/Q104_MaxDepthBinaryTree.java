package blind75.tree;

public class Q104_MaxDepthBinaryTree {
    public int maxDepth(TreeNode root) {
        if (root == null) {
            return 0;
        }
        return maxDepthHelper(root, 1);
    }

    public int maxDepthHelper(TreeNode node, int depthSoFar) {
        if (node.left == null && node.right == null) {
            return depthSoFar;
        } else if (node.left == null) {
            return maxDepthHelper(node.right, depthSoFar + 1);
        } else if (node.right == null) {
            return maxDepthHelper(node.left, depthSoFar + 1);
        }
        return Math.max(maxDepthHelper(node.left, depthSoFar+1), maxDepthHelper(node.right, depthSoFar+1));
    }
}
