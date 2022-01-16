import java.io.PrintWriter;
public class LinearProbing {
    private static int[] keys;
    private static Employee[] buckets;
    private static int size;
    public  LinearProbing(int M){
        size=M;
        keys=new int[M];
        buckets=new Employee[M];
        for (int i=0;i<M;++i){
            keys[i]=-1;
            buckets[i]=null;
        }
    }
    public static void insert( int key,Employee newEmployee){
        int tmp=Hash(key);
        int i=tmp;
        Employee temp=new Employee(newEmployee.phone,newEmployee.employeeCode,newEmployee.NRIC);
        do
        {
            if (buckets[i] == null)
            {
                buckets[i] =temp;
                keys[i]=key;
                return;
            }
            i = (i + 1) % buckets.length;
        } while (i != tmp);
    }
    public static int Hash(int key){
        int code= key%size;
        return code;
    }
    public static void printHashTable(PrintWriter output) {
        output.println("PART2\n" +
                "Hashtable for Linear Probing");
        for (int i = 0; i < buckets.length; i++) {
            output.print("[" + i + "]--->");
            if (buckets[i] == null) {

                output.println("null");
            }
            else {

                output.println(buckets[i].phone);
            }
    }
}
    public static void search( int key, PrintWriter output){
        long start=System.nanoTime();
        int tmp=Hash(key);
        int i = tmp;
        int comparison=0;
        boolean found=false;
        do {
            comparison++;
            if (keys[i]==-1){
                break;
            }
            if(keys[i]==key){
                found=true;
                break;
            }
            i=(i+1)%(buckets.length);
        }
        while (i!=tmp);
        long finish=System.nanoTime();
        if (found==true){
            output.println("LINEAR PROBING:\n"+
                    "Key found with "+ comparison+ " comparisons\n"+
                    "CPU time taken to search = "+(float)(finish-start)+" ns");
        }
        else{

            output.println("LINEAR PROBING:\n"+
                    "Key didn't found with "+ comparison+ " comparisons\n"+
                    "CPU time taken to search = "+(float)(finish-start)+" ns");
        }

    }
}
