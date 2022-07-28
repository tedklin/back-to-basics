package blind75.tree;

import java.util.*;

public class Q102_LevelOrderTraversal {
    private class TreeNodeWithLevel {
        public TreeNode node;
        public int level;

        public TreeNodeWithLevel(TreeNode node, int level) {
            this.node = node;
            this.level = level;
        }
    }

    public List<List<Integer>> levelOrder(TreeNode root) {
        if (root == null) {
            return new ArrayList<List<Integer>>();
        }

        List<List<Integer>> result = new ArrayList<>();

        Queue<TreeNodeWithLevel> queue = new LinkedList<>();
        queue.add(new TreeNodeWithLevel(root, 0));

        while (!queue.isEmpty()){
            TreeNodeWithLevel nodeWithLevel = queue.remove();
            int level = nodeWithLevel.level;
            if (level >= result.size()) {
                result.add(new ArrayList<>());
            }
            result.get(level).add(nodeWithLevel.node.val);

            if (nodeWithLevel.node.left != null) {
                queue.add(new TreeNodeWithLevel(nodeWithLevel.node.left, level + 1));
            }
            if (nodeWithLevel.node.right != null) {
                queue.add(new TreeNodeWithLevel(nodeWithLevel.node.right, level + 1));
            }
        }

        return result;
    }
}
