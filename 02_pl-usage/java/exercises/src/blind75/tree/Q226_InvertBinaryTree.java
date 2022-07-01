package blind75.tree;

public class Q226_InvertBinaryTree {
    public TreeNode invertTree(TreeNode root) {
        if (root == null) {
            return null;
        }
        TreeNode tmpLeft = root.left;
        root.left = invertTree(root.right);
        root.right = invertTree(tmpLeft);
        return root;
    }
}
