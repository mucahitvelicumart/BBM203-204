import java.io.*;
public class main {
    private static BufferedReader fileReading(String fileName) throws IOException {
        File file = new File(fileName);
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);
        return br;
    }
    public static void main(String[] args) throws IOException {
        LinkedList list = new LinkedList();
        BufferedReader openFile=fileReading(args[0]);
        PrintWriter printwriter= new PrintWriter("output.txt");
        openFile.readLine();
        int total_employee=0; // Count of Employees(size of array)
        float loadFactor1=Float.parseFloat(args[1]);// LF1
        float loadFactor2=Float.parseFloat(args[2]);// LF2
        int key =Integer.parseInt(args[3]);
        String lineofFile;
        // Read text file line by line and assign the employees to a Linked List
        while((lineofFile=openFile.readLine())!=null	){
            String[] splited=lineofFile.split(" ");
            Employee newEmployee= new Employee(Integer.parseInt(splited[2]),splited[0],splited[1]);
            list=LinkedList.insert(list,newEmployee);
            total_employee++;
        }
        int totalBucket=(int) (total_employee/loadFactor1);// Total bucket for SeparateChaining
        int totalBucket2=(int) (total_employee/loadFactor2);// Total bucket for LinearProbing&DoubleHashing
        new SeparateChaining(totalBucket); // Creating empty table for SeparateChaining
        new LinearProbing(totalBucket2);// Creating empty table for Linear Probing
        new DoubleHashing(totalBucket2);// Creating empty table for DoubleHashing
        LinkedList temp=list;
        while (temp.head!=null){      // Hashing with SeparateChaining and putting to the array of linked lists
            SeparateChaining.insert(temp.head.key,temp.head);
            LinearProbing.insert(temp.head.key,temp.head.newEmp);
            DoubleHashing.insert(temp.head.key,temp.head.newEmp);
            temp.head=temp.head.next;
        }
        String[] text=args[0].split("\\.txt");
        printwriter.println(text[0]+",LF1="+Math.round(loadFactor1)+",LF2="+loadFactor2+","+key);
        SeparateChaining.printHashTable(printwriter);
        LinearProbing.printHashTable(printwriter);
        DoubleHashing.printHashTable(printwriter);
        SeparateChaining.search(key,printwriter);
        LinearProbing.search(key,printwriter);
        DoubleHashing.search(key,printwriter);
        openFile.close();
        printwriter.close();
    }
}
