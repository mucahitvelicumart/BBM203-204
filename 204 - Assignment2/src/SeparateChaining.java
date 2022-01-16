import java.io.IOException;
import java.io.PrintWriter;

public class SeparateChaining {
    private static LinkedList.Node[] buckets;
    private static int size;
    public  SeparateChaining(int M){    // creating an empty table
        buckets=new LinkedList.Node[M];
        for (int i=0;i<M;++i){
            buckets[i]=null;
        }
        size=M;
    }
    public static void insert(int key,LinkedList.Node employee){
        int pos=Hash(key);
        LinkedList.Node temp= new LinkedList.Node(employee.newEmp);
        if (buckets[pos] == null) {
            buckets[pos]=temp;
            buckets[pos].key=key;
        }
        else{
            LinkedList.Node last=buckets[pos];
            while (last.next!=null){
                last=last.next;

            }
            last.next=temp;
            last.next.key=key;
        }
    }
    public static int Hash(int key){
        int code= key%size;
        return code;
    }
    public static void printHashTable( PrintWriter output) throws IOException {
        output.println("PART1");
        for (int i=0;i<buckets.length;++i){
            output.print("[Chain "+i+"]: ");
            LinkedList.Node temp=buckets[i];
            if (buckets[i]==null){
                output.println("Null");
            }
            else{
                output.print(temp.newEmp.phone);
                while (temp.next!=null){
                    output.print("---->"+temp.next.newEmp.phone);
                    temp=temp.next;
                }
                output.println();
            }
        }
    }
    public static void search( int key, PrintWriter output){
        long start=System.nanoTime();
        int pos = Hash(key);
        int comparison=0;
        boolean found=false;
        LinkedList.Node temp=buckets[pos];
        while (temp!=null){
            comparison++;
            if (temp.key==key){
                found=true;
                break;
            }
            temp=temp.next;
        }
        long finish=System.nanoTime();
        if (found){
            output.println("SEPARATE CHAINING:\n" +
                    "Key found with "+comparison+" comparisons\n"+
                    "CPU time taken to search = "+(float)(finish-start)+" ns");
        }
        else{

            output.println("SEPARATE CHAINING:\n"+"Key didn't found with "+comparison+" comparisons\n"+
                    "Cpu time taken to search = "+(float)(finish-start)+" ns");
        }

    }
}
