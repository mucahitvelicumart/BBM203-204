
import java.util.Map;
import java.util.TreeMap;

public class TST  {
    private Node root;
    public TST(){
        this.root = null;
    }
    private Node insert(String key,int pos,Node node,String mode){
        char s[] = key.toCharArray();
        if(node == null){
            node = new Node(s[pos],false);
        }
        if(s[pos]<node.data){
            node.left = insert(key,pos,node.left,mode);
        }else if(s[pos]>node.data){
            node.right = insert(key,pos,node.right,mode);
        }else{
            if(pos+1 == key.length()){
                node.isEnd = true;
                if (mode=="legitimate"){
                    node.legitimate_occurence++;
                }
                else if (mode=="phishing"){

                    node.phish_occurence++;
                }

            }else{
                node.center = insert(key,pos+1,node.center,mode);
            }
        }
        return node;
    }
    public void insert(String key,String mode){
        if(key.isEmpty()) throw  new IllegalArgumentException();
        this.root = insert(key,0,this.root,mode);
    }
    public int isContainsKey(String key){
        if(key == null || key.equals("")) throw  new IllegalArgumentException();
        int pos = 0;
        Node node = this.root;
        char s[] = key.toCharArray();
        while (node != null){
            if(s[pos]< node.data){
                node = node.left;
            }else if(s[pos]>node.data){
                node = node.right;
            }else{
                if(++pos == key.length()) return node.phish_occurence;
                node = node.center;
            }
        }
        return  -1;
    }
    public int isContainsKey2(String key){
        if(key == null || key.equals("")) throw  new IllegalArgumentException();
        int pos = 0;
        Node node = this.root;
        char s[] = key.toCharArray();
        while (node != null){
            if(s[pos]< node.data){
                node = node.left;
            }else if(s[pos]>node.data){
                node = node.right;
            }else{
                if(++pos == key.length()) return node.legitimate_occurence;
                node = node.center;
            }
        }
        return  -1;
    }
    private void TraverseTST(Node node,char res[],int depth){
        if(node != null){
            TraverseTST(node.left,res,depth);
            res[depth] = node.data;
            if(node.isEnd){
                for(int i = 0 ; i < depth+1;i++){
                    System.out.print(res[i]);
                }
                System.out.println();
            }
            TraverseTST(node.center,res,depth+1);
            TraverseTST(node.right,res,depth);
        }
    }
    public void delete(String word)
    {
        delete(root, word.toCharArray(), 0);
    }
    private void delete(Node r, char[] word, int ptr) {
        if (r == null)
            return;
        if (word[ptr] < r.data)
            delete(r.left, word, ptr);
        else if (word[ptr] > r.data)
            delete(r.right, word, ptr);
        else
        {
            if (r.isEnd && ptr == word.length - 1) {
                r.isEnd = false;
                r.legitimate_occurence = 0;
                r.phish_occurence = 0;
            }
            else if (ptr + 1 < word.length)
                delete(r.center, word, ptr + 1);
        }
    }
}

class Node{
    char data;
    boolean isEnd;
    int phish_occurence=0,legitimate_occurence=0;
    float weight=0;
    Node left,center,right;
    public Node(char data, boolean isEnd) {
        this.data = data;
        this.isEnd = isEnd;
        left = right = center = null;
    }
}


