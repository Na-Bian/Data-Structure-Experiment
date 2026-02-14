public class Test {
    public static void main(String[] args) {
        SparseMatrix matrix = new SparseMatrix(7, 8, new Triple[]{
                new Triple(5, 0, 15),
                new Triple(3, 2, 24),
                new Triple(0, 1, 12),
                new Triple(2, 0, -3),
                new Triple(4, 1, 18),
                new Triple(2, 5, 14),
                new Triple(0, 2, 9),
        });

        System.out.println("toString方法输出：");
        System.out.println(matrix);

        System.out.println("\nprintSMatrix方法输出：");
        matrix.printSMatrix();

        int[][] denseMatrix = matrix.toDenseMatrix();
        System.out.println("\n稠密矩阵：");
        for (int[] row : denseMatrix) {
            for (int value : row) {
                System.out.print(value + "\t");
            }
            System.out.println();
        }

        SparseMatrix copy = matrix.copySMatrix();
        System.out.println("\n复制矩阵Matrix：");
        copy.printSMatrix();

        System.out.println("\n添加元素(5,3,-7)：");
        matrix.setElement(5, 3, -7);
        matrix.printSMatrix();

        System.out.println("\n更改维度(6,7)：");
        matrix.setSize(6, 7);
        denseMatrix = matrix.toDenseMatrix();
        for (int[] row : denseMatrix) {
            for (int value : row) {
                System.out.print(value + "\t");
            }
            System.out.println();
        }

        SparseMatrix trans = matrix.transpose();
        System.out.println("\n转置矩阵：");
        trans.printSMatrix();

        SparseMatrix sum = SparseMatrix.addSMatrix(trans, trans);
        System.out.println("\n转置矩阵与自身相加：");
        sum.printSMatrix();

        SparseMatrix mul = trans.multSMatrix(matrix);
        System.out.println("\n转置矩阵与原矩阵相乘：");
        mul.printSMatrix();
    }
}
