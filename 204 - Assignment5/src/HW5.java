import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
@SuppressWarnings("unchecked")
public class HW5 {
    private static int C, D, E, S;

    public static void main(String[] args) throws InterruptedException {

        String[] content = readFile(args[0]);
        String[] infos = content[0].split(" ");

        C = Integer.parseInt(infos[0]);//Carrier type
        D = Integer.parseInt(infos[1]);//number of nodes
        E = Integer.parseInt(infos[2]);//number of edges
        S = Integer.parseInt(infos[3]);//destination node
        EdgeWeightedDigraph graph = new EdgeWeightedDigraph(D + 1, E);//construct edge weighted  digraph
        for (int i = 1; i < content.length; i++) {
            String[] line = content[i].split(" ");
            graph.addEdge(new DirectedEge(Integer.parseInt(line[0]), Integer.parseInt(line[1]), Integer.parseInt(line[2])));
        }
        if (C == 1 || C == 2) {
            carrier1(graph, 1, S);
        }
        else if(C==3){
            carrier3(graph,1,S);
        }
        else if(C==4){
            carrier4(graph,1,S);
        }



    }

    public static void carrier4(EdgeWeightedDigraph G,int src,int dest){

        int start=src;
        boolean condition=true;
        double totalCost=0;
        ArrayList<Integer> path=new ArrayList<>();
        ArrayList<DirectedEge> set=new ArrayList<>();
        path.add(start);
        try {
            while (condition){
                double cost=Double.POSITIVE_INFINITY;
                DirectedEge temp=null;
                for (DirectedEge e:G.adj(start)){
                    if(set.contains(e)){
                        continue;
                    }
                    if(e.weigth<=cost){
                        temp=e;
                        cost=e.weigth;
                    }
                }
                set.add(temp);
                start=temp.other(start);
                totalCost+=temp.weigth;
                path.add(start);
                if(start==dest){
                    break;
                }
            }
            System.out.println((int)totalCost);
            System.out.println(path.toString().replace("[","").replace("]","").replace(", ","->"));

        }catch (Exception exception){
            System.out.println(-1);
        }
    }


    public static void carrier1(EdgeWeightedDigraph G, int src, int dest) {
        EagerPrimMST prims = new EagerPrimMST(G);
        DirectedEge[] path = prims.findMST(G);
        ArrayList<DirectedEge> mst=new ArrayList<>();
        for (DirectedEge e : path) {
            if (e != null) {
                mst.add(e);
            }
        }
        Vector<Integer> shortest = new Vector<>();
        findUtil(G, mst, src, dest, shortest);

    }

    private static boolean findUtil(EdgeWeightedDigraph G, ArrayList<DirectedEge> mst, int src, int dest, Vector<Integer> path) { // Finds minimum path//

        if (src == dest) {
            path.add(src);
            double totalCost=0;
            double maxCost=0;
            StringJoiner str=new StringJoiner("->");
            for(int i=0;i<path.size()-1;i++){
                Double res1=G.weight(path.get(i),path.get(i+1));
                Double res2=G.weight(path.get(i+1),path.get(i));
                str.add(path.get(i).toString());
                totalCost+=res1;
                totalCost+=res2;
                if(res1>maxCost)
                    maxCost=res1;
                if(res2>maxCost)
                    maxCost=res2;
            }
            str.add(String.valueOf(src));
            switch (C){
                case 1:
                    System.out.println((int)totalCost);
                    System.out.println(str.toString());
                    break;
                case 2:
                    System.out.println((int)maxCost);
                    break;
            }
            return true;
        }

        for (DirectedEge e:mst){
            if(e.to()==src && !path.contains(e.from())){
                path.add(src);
                findUtil(G,mst,e.from(),dest,path);
            }
            if(e.from()==src && !path.contains(e.to())){
                path.add(src);
                findUtil(G,mst,e.to(),dest,path);
            }
            else{
                path.remove((Integer) src);
            }
        }
        return false;

    }
    public static void carrier3(EdgeWeightedDigraph G,int src, int dest)
    {
        boolean[] beingVisited = new boolean[G.V];
        Vector path = new Vector();
        path.add(src);
        dfs(G,src, dest, beingVisited, path);
    }

    private static void dfs(EdgeWeightedDigraph G,int src, int dest, boolean[] viseted, Vector<Integer> currentPath)// Searching minimum path //
    {
        viseted[src] = true;
        double cost=0;
        if (src==dest) {
            StringJoiner str=new StringJoiner("->");
            for (int i = 0; i <currentPath.size() ; i++) {
                str.add(currentPath.get(i).toString());
            }
            System.out.println(currentPath.size()-1);
            System.out.println(str.toString());
            return;
        }

        for (DirectedEge e : G.adj(src))
        {
            int i=e.other(src);
            if (!viseted[i])
            {
                currentPath.add(i);
                dfs(G,i, dest, viseted, currentPath);
                currentPath.remove((Object)i);
            }
        }

        viseted[src] = false;
    }
    public static String[] readFile(String path) {
        try {
            int i = 0;
            int length = Files.readAllLines(Paths.get(path)).size();
            String[] result = new String[length];
            for (String line : Files.readAllLines(Paths.get(path))) {
                result[i++] = line;

            }
            return result;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    private static class EagerPrimMST {
        private final DirectedEge[] edgeTo;//edges on the mst
        private final double[] distTo;//distance each vertex
        private final boolean[] marked;//controller array
        private final IndexedMinPQ<Double> pq;//indexed  priority queue to implement our EagerPrimsMst

        public EagerPrimMST(EdgeWeightedDigraph G) {
            edgeTo = new DirectedEge[G.V];
            marked = new boolean[G.V];
            distTo = new double[G.V];
            pq = new IndexedMinPQ<Double>(G.V);
        }

        public DirectedEge[] findMST(EdgeWeightedDigraph G) {
            for (int v = 0; v < G.V; v++)
                distTo[v] = Double.POSITIVE_INFINITY;

            for (int v = 0; v < G.V; v++) {
                if (!marked[v])
                    condition_check(G, v);
            }
            return edgeTo;
        }

        private void condition_check(EdgeWeightedDigraph G, int s) {//Finding Minimum Spannig Tree//
            distTo[s] = 0.0;
            pq.insert(s, distTo[s]);
            while (!pq.isEmpty()) {
                int v = pq.delMin();
                marked[v] = true;
                for (DirectedEge e : G.adj(v)) {
                    int w = e.other(v);
                    if (marked[w])
                        continue;
                    if (e.weight() < distTo[w]) {
                        distTo[w] = e.weight();
                        edgeTo[w] = e;
                        if (pq.contains(w)) pq.decreaseKey(w, distTo[w]);
                        else pq.insert(w, distTo[w]);
                    }
                }
            }
        }
    }

    private static class EdgeWeightedDigraph {
        private final Bag<DirectedEge>[] adj;
        private final int V;
        private final int E;

        public EdgeWeightedDigraph(int v, int e) {
            V = v;
            E = e;
            adj = (Bag<DirectedEge>[]) new Bag[v];
            for (int i = 0; i < v; i++) {
                adj[i] = new Bag<DirectedEge>();
            }
        }

        public void addEdge(DirectedEge e) {
            int v = e.from(), w = e.to();
            adj[v].add(e);
            adj[w].add(e);
        }

        public double weight(int s, int d) {
            for (DirectedEge e : adj(s)) {
                if (e.to() == d) {
                    return e.weigth;
                }
            }
            return 0;
        }

        public Iterable<DirectedEge> adj(int v) {
            return adj[v];
        }
    }

    private static class IndexedMinPQ<Key extends Comparable<Key>> {
        private int maxN;
        private int n;
        private int[] priorityQ;
        private int[] tempq;
        private Key[] keys;

        public IndexedMinPQ(int maxN) {
            if (maxN < 0)
                return;
            this.maxN = maxN;
            n = 0;
            keys = (Key[]) new Comparable[maxN + 1];
            priorityQ = new int[maxN + 1];
            tempq = new int[maxN + 1];
            for (int i = 0; i <= maxN; i++)
                tempq[i] = -1;
        }

        public boolean contains(int i) {
            return tempq[i] != -1;
        }

        public void insert(int i, Key key) {
            if (contains(i))
                return;
            n++;
            tempq[i] = n;
            priorityQ[n] = i;
            keys[i] = key;
            swim(n);
        }

        public int delMin() {
            if (n == 0)
                return -1;
            int min = priorityQ[1];
            exch(1, n--);
            sink(1);
            assert min == priorityQ[n + 1];
            tempq[min] = -1;
            keys[min] = null;
            priorityQ[n + 1] = -1;
            return min;
        }

        public void decreaseKey(int i, Key key) {
            if (keys[i].compareTo(key) == 0)
                return;
            if (keys[i].compareTo(key) < 0)
                return;
            keys[i] = key;
            swim(tempq[i]);
        }

        private boolean greater(int i, int j) {
            return keys[priorityQ[i]].compareTo(keys[priorityQ[j]]) > 0;
        }

        public boolean isEmpty() {
            return n == 0;
        }

        private void exch(int i, int j) {
            int swap = priorityQ[i];
            priorityQ[i] = priorityQ[j];
            priorityQ[j] = swap;
            tempq[priorityQ[i]] = i;
            tempq[priorityQ[j]] = j;
        }

        private void swim(int num) {
            while (num > 1 && greater(num / 2, num)) {
                exch(num, num / 2);
                num = num / 2;
            }
        }

        private void sink(int k) {
            while (2 * k <= n) {
                int j = 2 * k;
                if (j < n && greater(j, j + 1)) j++;
                if (!greater(k, j)) break;
                exch(k, j);
                k = j;
            }
        }
    }

    private static class Bag<Item> implements Iterable<Item> {
        private Node<Item> first;
        private int n;

        public Bag() {
            first = null;
            n = 0;
        }

        public void add(Item item) {
            Node<Item> oldfirst = first;
            first = new Node<Item>();
            first.item = item;
            first.next = oldfirst;
            n++;
        }

        public Iterator<Item> iterator() {
            return new LinkedIterator(first);
        }

        private static class Node<Item> {
            private Item item;
            private Node<Item> next;
        }

        private class LinkedIterator implements Iterator<Item> {
            private Node<Item> current;

            public LinkedIterator(Node<Item> first) {
                current = first;
            }

            public boolean hasNext() {
                return current != null;
            }

            public Item next() {
                if (!hasNext())
                    return null;
                Item item = current.item;
                current = current.next;
                return item;
            }
        }
    }

    private static class DirectedEge implements Comparable<DirectedEge> {
        private final int v, w;
        private final double weigth;

        public DirectedEge(int v, int w, double weigth) {
            this.w = w;
            this.v = v;
            this.weigth = weigth;
        }

        public int from() {
            return v;
        }

        public int other(int vertex) {
            if (vertex == v) return w;
            else if (vertex == w) return v;
            return 0;
        }

        public int to() {
            return w;
        }

        public double weight() {
            return weigth;
        }

        @Override
        public String toString() {
            return v + "-->" + w;
        }

        @Override
        public int compareTo(DirectedEge o) {
            if (this.weigth < o.weigth) return -1;
            else if (this.weigth > o.weigth) return +1;
            else return 0;
        }
    }
}
