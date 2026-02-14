import java.util.*;

public class SparseMatrix {
    private int rows; //稀疏矩阵的行数
    private int cols; //稀疏矩阵的列数
    private ArrayList<Triple> elements; //非零元素的三元组列表

    //三元组列表去重
    private ArrayList<Triple> dropDuplicates(ArrayList<Triple> elements) {
        if (elements.isEmpty()) return elements;
        Collections.sort(elements);
        ArrayList<Triple> newElements = new ArrayList<>();
        int index = 0;
        while (index < elements.size()) {
            int row = elements.get(index).row();
            int col = elements.get(index).col();
            int value = elements.get(index).value();
            index++;
            while (index < elements.size() && elements.get(index).row() == row && elements.get(index).col() == col) {
                value += elements.get(index).value();
                index++;
            }
            if (value != 0) {
                //去除值为0的三元组
                newElements.add(new Triple(row, col, value));
            }
        }
        return newElements;
    }

    //创建稀疏矩阵的构造方法
    public SparseMatrix(int rows, int cols, Triple[] elements) {
        if (rows < 0 || cols < 0) {
            throw new IllegalArgumentException("矩阵维度不能为负数");
        }
        //三元组数组
        this.rows = rows;
        this.cols = cols;
        ArrayList<Triple> myElements = dropDuplicates(new ArrayList<>(Arrays.asList(elements)));
        //检查索引范围
        for (Triple t : myElements) {
            if (t.row() < 0 || t.row() >= rows || t.col() < 0 || t.col() >= cols) {
                throw new IllegalArgumentException("三元组的行列索引超出矩阵的范围");
            }
        }
        this.elements = myElements;
    }

    public SparseMatrix(int rows, int cols, List<Triple> elements) {
        if (rows < 0 || cols < 0) {
            throw new IllegalArgumentException("矩阵维度不能为负数");
        }
        //三元组数组
        this.rows = rows;
        this.cols = cols;
        ArrayList<Triple> myElements = dropDuplicates(new ArrayList<>(elements));
        //检查索引范围
        for (Triple t : myElements) {
            if (t.row() < 0 || t.row() >= rows || t.col() < 0 || t.col() >= cols) {
                throw new IllegalArgumentException("三元组的行列索引超出矩阵的范围");
            }
        }
        this.elements = myElements;
    }

    //私有构造方法，直接使用已经去重和排序的三元组列表
    private SparseMatrix(int rows, int cols, List<Triple> elements, boolean skipDedup) {
        this.rows = rows;
        this.cols = cols;
        this.elements = new ArrayList<>(elements);
    }

    //公共getter方法
    public int getRows() {
        return rows;
    }

    public int getCols() {
        return cols;
    }

    public List<Triple> getElements() {
        return Collections.unmodifiableList(elements); //返回不可修改的三元组列表
    }

    //修改稀疏矩阵的大小
    public void setSize(int newRows, int newCols) {
        if (newRows < 0 || newCols < 0) {
            throw new IllegalArgumentException("矩阵的行数和列数必须为非负整数");
        }
        //删除超出新大小范围的三元组
        elements.removeIf(t -> t.row() >= newRows || t.col() >= newCols);
        this.rows = newRows;
        this.cols = newCols;
    }

    //修改稀疏矩阵的元素
    public void setElement(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw new IllegalArgumentException("行列索引超出矩阵的范围");
        }
        //二分查找是否已经存在该位置的三元组
        int low = 0, high = elements.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            Triple t = elements.get(mid);
            if (t.row() == row && t.col() == col) {
                if (value != 0) {
                    //如果新值不为零，则更新三元组的值
                    elements.set(mid, new Triple(row, col, value));
                } else {
                    //如果新值为零，则删除该三元组
                    elements.remove(mid);
                }
                return;
            } else if (t.row() < row || t.row() == row && t.col() < col) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        //如果没有找到该位置的三元组，并且新值不为零，则添加一个新的三元组
        if (value != 0) {
            elements.add(low, new Triple(row, col, value));
        }
    }

    //输出稀疏矩阵的内容
    public void printSMatrix() {
        System.out.println("row" + "\t\t" + "col" + "\t\t" + "value");
        for (Triple t : elements) {
            System.out.println(t.row() + "\t\t" + t.col() + "\t\t" + t.value());
        }
    }

    //将稀疏矩阵转换为稠密矩阵
    public int[][] toDenseMatrix() {
        int[][] dense = new int[rows][cols];
        for (Triple t : elements) {
            dense[t.row()][t.col()] = t.value();
        }
        return dense;
    }

    //复制稀疏矩阵
    public SparseMatrix copySMatrix() {
        ArrayList<Triple> newElements = new ArrayList<>();
        //深拷贝
        for (Triple t : elements) {
            newElements.add(new Triple(t.row(), t.col(), t.value()));
        }
        return new SparseMatrix(rows, cols, newElements, true);
    }

    //稀疏矩阵相加或相减的辅助方法
    private SparseMatrix addORsub(SparseMatrix N, boolean isAdd) {
        if (rows != N.rows || cols != N.cols) {
            if (isAdd) {
                throw new IllegalArgumentException("矩阵维度不匹配，无法相加");
            } else {
                throw new IllegalArgumentException("矩阵维度不匹配，无法相减");
            }
        }
        int indexM = 0, indexN = 0;
        ArrayList<Triple> newElements = new ArrayList<>();
        while (indexM < elements.size() && indexN < N.elements.size()) {
            int rowM = elements.get(indexM).row();
            int colM = elements.get(indexM).col();
            int rowN = N.elements.get(indexN).row();
            int colN = N.elements.get(indexN).col();
            //归并两个三元组列表
            if (rowM == rowN && colM == colN) {
                //行列索引相同，值相加或相减
                if (isAdd) {
                    int val = elements.get(indexM).value() + N.elements.get(indexN).value();
                    if (val != 0) {
                        newElements.add(new Triple(elements.get(indexM).row(), elements.get(indexM).col(), val));
                    }
                } else {
                    int val = elements.get(indexM).value() - N.elements.get(indexN).value();
                    if (val != 0) {
                        newElements.add(new Triple(elements.get(indexM).row(), elements.get(indexM).col(), val));
                    }
                }
                //更新索引
                indexM++;
                indexN++;
            } else if (rowM < rowN || rowM == rowN && colM < colN) {
                //M的三元组在N的三元组之前，直接添加到新列表中
                newElements.add(new Triple(rowM, colM, elements.get(indexM).value()));
                //只更新M的索引
                indexM++;
            } else {
                //N的三元组在M的三元组之前，直接添加到新列表中
                int val = isAdd ? N.elements.get(indexN).value() : -N.elements.get(indexN).value(); // 减法时取反
                newElements.add(new Triple(rowN, colN, val));
                //只更新N的索引
                indexN++;
            }
        }
        //将剩余的三元组添加到新列表中
        for (; indexM < elements.size(); indexM++) {
            Triple t = elements.get(indexM);
            newElements.add(new Triple(t.row(), t.col(), t.value()));
        }
        for (; indexN < N.elements.size(); indexN++) {
            Triple t = N.elements.get(indexN);
            int val = isAdd ? t.value() : -t.value(); // 减法时取反
            newElements.add(new Triple(t.row(), t.col(), val));
        }
        return new SparseMatrix(rows, cols, newElements, true);
    }

    //稀疏矩阵相加
    public static SparseMatrix addSMatrix(SparseMatrix M, SparseMatrix N) {
        return M.addORsub(N, true);
    }

    //稀疏矩阵相减
    public static SparseMatrix subSMatrix(SparseMatrix M, SparseMatrix N) {
        return M.addORsub(N, false);
    }

    //稀疏矩阵转置
    public SparseMatrix transpose() {
        //1.求出每一列的非零元素个数
        int[] colCounts = new int[cols];
        for (Triple t : elements) {
            colCounts[t.col()]++;
        }
        //2.求出每一列的第一个非零元素在转置后的三元组列表中的起始位置
        int[] position = new int[cols];
        position[0] = 0;
        for (int i = 1; i < cols; i++) {
            position[i] = position[i - 1] + colCounts[i - 1];
        }
        //3.构造转置后的三元组列表
        Triple[] newElements = new Triple[elements.size()];
        for (Triple t : elements) {
            //每次处理一个三元组，将其放到转置后的三元组列表中正确的位置，并更新该列的起始位置
            newElements[position[t.col()]++] = new Triple(t.col(), t.row(), t.value());
        }
        return new SparseMatrix(cols, rows, new ArrayList<>(Arrays.asList(newElements)), true);
    }

    //稀疏矩阵乘法M x N
    public SparseMatrix multSMatrix(SparseMatrix N) {
        if (cols != N.rows) {
            throw new IllegalArgumentException("矩阵维度不匹配，无法相乘");
        }
        if (elements.isEmpty() || N.elements.isEmpty()) {
            //如果其中一个矩阵是零矩阵，则结果也是零矩阵
            return new SparseMatrix(rows, N.cols, new ArrayList<>());
        }
        ArrayList<Triple> tempElements = new ArrayList<>();
        //构建rowStart数组，记录N中每一行在elements列表中的起始位置
        int[] num = new int[N.rows]; //记录N中每一行的非零元素个数
        for (Triple t : N.elements) {
            num[t.row()]++;
        }
        int[] rowStart = new int[N.rows];
        rowStart[0] = 0;
        for (int i = 1; i < N.rows; i++) {
            rowStart[i] = rowStart[i - 1] + num[i - 1];
        }
        //遍历M，在N中找到所有行数与M的列数相同的三元组，计算乘积添加到临时列表中
        for (Triple tM : elements) {
            for (int index = rowStart[tM.col()]; index < rowStart[tM.col()] + num[tM.col()]; index++) {
                Triple tN = N.elements.get(index);
                int var = tM.value() * tN.value();
                tempElements.add(new Triple(tM.row(), tN.col(), var));
            }
        }
        //构造时自动去重和排序
        return new SparseMatrix(rows, N.cols, dropDuplicates(tempElements), true);
    }

    @Override
    public String toString() {
        return "SparseMatrix{" + "rows=" + rows + ", cols=" + cols + ", num_elems=" + elements.size() + '}';
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof SparseMatrix other)) {
            return false;
        }
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        return elements.equals(other.elements);
    }

    @Override
    public int hashCode() {
        return Objects.hash(rows, cols, elements);
    }
}
