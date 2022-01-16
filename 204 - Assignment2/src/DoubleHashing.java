import java.io.PrintWriter;
public class DoubleHashing {
    private static int[] keys;
    private static Employee[] buckets;
    private static int size;
    public  DoubleHashing(int M){
        keys=new int[M];
        buckets=new Employee[M];
        size=M;
        for (int i=0;i<M;++i){
            buckets[i]=null;
            keys[i]=-1;
        }

    }
    public static void insert( int key,Employee newEmployee){
        int hashval=Hash(key);
        int step=Hash2(key);
        while (buckets[hashval] !=null){
            hashval+=step;
            hashval%=buckets.length;
        }
        keys[hashval]=key;
        buckets[hashval]=newEmployee;
    }
    public static int Hash(int key){
        return key%size;
    }
    public static int Hash2(int key){
        return 1 + (key % (size - 1));
    }
    public static void printHashTable( PrintWriter output) {
        output.println("Hashtable for Double Hashing");
        for (int i = 0; i < buckets.length; i++){
            output.print("["+i+"]--->");
            if (buckets[i] == null){
                output.println("null");
            }
            else {
                output.println(buckets[i].phone);
            }
        }
    }
    public static void search( int key, PrintWriter output){
        long start=System.nanoTime();
        int hashval=Hash(key);
        int step=Hash2(key);
        int comparison=0;
        boolean found=false;
        while (keys[hashval]!=-1){
            comparison++;
            if (keys[hashval]==key){
                found=true;
                break;
            }
            hashval+=step;
            hashval%=buckets.length;

        }
        long finish= System.nanoTime();
        if (found==false){
            output.println("DOUBLE HASHING:\n" +
                    "Key didn't found with " +comparison+ " comparisons\n"+
                    "CPU time taken to search = "+(float)(finish-start)+" ns");
        }
        else{
            output.println("DOUBLE HASHING:\n" +
                    "Key found with " +comparison+ " comparisons\n"+
                    "CPU time taken to search = "+(float)(finish-start)+" ns");
        }

    }
}
