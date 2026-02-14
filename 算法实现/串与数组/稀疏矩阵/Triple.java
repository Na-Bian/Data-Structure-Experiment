//表示非零元素的三元组类
public record Triple(int row, int col, int value) implements Comparable<Triple> {
    //重写compareTo方法，按照行优先的顺序进行比较
    @Override
    public int compareTo(Triple o) {
        if (this.row < o.row) {
            return -1;
        } else if (this.row > o.row) {
            return 1;
        } else if (this.col < o.col) { //如果行索引相同，则按照列索引进行比较
            return -1;
        } else if (this.col > o.col) {
            return 1;
        } else
            //行索引和列索引都相同
            return Integer.compare(this.value, o.value);
    }
}
