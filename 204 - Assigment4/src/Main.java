import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class Main {
    private static BufferedReader fileReading(String fileName) throws IOException {
        File file = new File(fileName);
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);
        return br;
    }
	private static Map<String, Integer> sortByValue( Map<String, Integer> wordCounts) {
		return wordCounts.entrySet()
				.stream()
				.sorted((Map.Entry.<String, Integer>comparingByValue().reversed()))
				.collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e1, LinkedHashMap::new));
	}
	private static Map<String, Float> sortByValue2( Map<String, Float> wordCounts) {
		return wordCounts.entrySet()
				.stream()
				.sorted((Map.Entry.<String, Float>comparingByValue().reversed()))
				.collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (e1, e2) -> e1, LinkedHashMap::new));
	}
	private static void strongFeatures(String mode,Map<String,Integer> map,int count2) throws FileNotFoundException {
		if (mode=="phishing"){
			PrintWriter printwriter= new PrintWriter("strong_phishing_features.txt");
			printwriter.println("Most important phishing n_grams");
			int count=1;
			for (String key:map.keySet()){
				if (count>count2)
					break;
				printwriter.println(count+". "+key+" - freq: "+map.get(key));
				count++;
			}
			printwriter.close();
		}
		else if (mode=="legitimate"){
			PrintWriter printwriter= new PrintWriter("strong_legitimate_features.txt");
			printwriter.println("Most important legitimate n_grams");
			int count=1;
			for (String key:map.keySet()){
				if (count>count2)
					break;
				printwriter.println(count+". "+key+" - freq: "+map.get(key));
				count++;
			}
			printwriter.close();

		}

	}
	private static int all_features_map(Map<String,Integer> phishing,Map<String,Integer> legitimate,Map<String,Float> map,int feature_size) throws FileNotFoundException {
    	int i=0;
    	for (String key: phishing.keySet()){
    		i++;
    		if (legitimate.containsKey(key)){
    			if (phishing.get(key)>legitimate.get(key)){
					float b=Math.min(phishing.get(key),legitimate.get(key));
					float c=Math.max(phishing.get(key),legitimate.get(key));
					float weight=(b/c);
    				map.put(key,weight);
				}
    			else if (phishing.get(key)<legitimate.get(key)){
					float b=Math.min(phishing.get(key),legitimate.get(key));
					float c=Math.max(phishing.get(key),legitimate.get(key));
					float weight=-(b/c);
					map.put(key,weight);
				}
    			else{
    				float weight=(float) 0 ;
    				map.put(key,weight);
				}
			}
    		else{
    			float weight=(float) 1;
    			map.put(key,weight);
			}
		}
    	for (String key: legitimate.keySet()){
    		if (phishing.containsKey(key)){
    			continue;
			}
    		else{
    			i++;
    			float weight=(float)(-1);
    			map.put(key,weight);
			}
		}
    	map=sortByValue2(map);
    	PrintWriter printWriter=new PrintWriter("all_feature_weights.txt");
    	printWriter.println("All N-Gram Weights");
    	for (String key : map.keySet()){
			printWriter.println(key+" - weight: "+map.get(key));
		}
    	printWriter.close();
    	return i;
	}
	private static void createlist(Map<String,Integer>map,List<String> list,int N){
		int count=0;
		for (String key: map.keySet()){
			count++;
			if (count>N){
				break;
			}
			if (list.contains(key))
				continue;
			list.add(key);
		}
	}
    public static void main(String[] args) throws IOException {
		BufferedReader phishing_train=fileReading("phishing-train.txt");
		BufferedReader legitimate_train=fileReading("legitimate-train.txt");
		int N=Integer.parseInt(args[0]);
		int TP=0,FN=0,TN=0,FP=0,UP=0,UL=0;
		int feature_size=Integer.parseInt(args[1]);
		TST tst=new TST(); // Ternary Search Tree for N_grams
		Map<String,Integer> map=new HashMap<String, Integer>();
		Map<String,Integer> map2=new HashMap<String, Integer>();
		String lineoffile;
		int phishing_count=0,legitimate_count=0;
		//Inserting n_grams to TST in Phishing Train
		while ((lineoffile=phishing_train.readLine())!=null){
			phishing_count++;
			lineoffile=lineoffile.replace("https","");
			lineoffile=lineoffile.replace("http","");
			lineoffile=lineoffile.replace("www","");
			lineoffile=lineoffile.toLowerCase(Locale.ENGLISH);
			if (lineoffile.length()<N){
				continue;
			}
			else{
				for (int i=0;i<lineoffile.length()-N+1;i++){
					tst.insert(lineoffile.substring(i,i+N),"phishing");
				}
			}
    	}
		//Inserting n_grams to TST in Legitimate Train
		while ((lineoffile=legitimate_train.readLine())!=null){
			legitimate_count++;
			lineoffile=lineoffile.replace("https","");
			lineoffile=lineoffile.replace("http","");
			lineoffile=lineoffile.replace("www","");
			lineoffile=lineoffile.toLowerCase(Locale.ENGLISH);
			if (lineoffile.length()<N){
				continue;
			}
			else{
				for (int i=0;i<lineoffile.length()-N+1;i++){
					tst.insert(lineoffile.substring(i,i+N),"legitimate");
				}
			}
		}
		phishing_train.close();
		phishing_train=fileReading("phishing-train.txt");
		legitimate_train.close();
		legitimate_train=fileReading("legitimate-train.txt");
		while ((lineoffile=phishing_train.readLine())!=null){
			lineoffile=lineoffile.replace("https","");
			lineoffile=lineoffile.replace("http","");
			lineoffile=lineoffile.replace("www","");
			lineoffile=lineoffile.toLowerCase(Locale.ENGLISH);
			for (int i=0;i<lineoffile.length()-N+1;i++){
				map.put(lineoffile.substring(i,i+N),tst.isContainsKey(lineoffile.substring(i,i+N)));// Mapping for sorting phishing n_grams
			}
		}
		while ((lineoffile=legitimate_train.readLine())!=null){
			lineoffile=lineoffile.replace("https","");
			lineoffile=lineoffile.replace("http","");
			lineoffile=lineoffile.replace("www","");
			lineoffile=lineoffile.toLowerCase(Locale.ENGLISH);
			if (lineoffile.length()<N){
				continue;
			}
			else{
				for (int i=0;i<lineoffile.length()-N+1;i++){
					map2.put(lineoffile.substring(i,i+N),tst.isContainsKey2(lineoffile.substring(i,i+N)));// Mapping for sorting legitimate n_grams
				}
			}
		}
		Map<String,Float> map3=new HashMap<String, Float>();
		map=sortByValue(map);
		map2=sortByValue(map2);
		int total_ngrams=all_features_map(map,map2,map3,feature_size);
		map3=sortByValue2(map3);                  // Map for All_feature_weights
		strongFeatures("phishing",map,feature_size);
		strongFeatures("legitimate",map2,feature_size);
		List<String> list=new LinkedList<String>();
		createlist(map,list,feature_size);
		createlist(map2,list,feature_size);
		for (String key: map.keySet()){
			if (list.contains(key))
				continue;
			tst.delete(key);
		}
		for (String key: map2.keySet()){
			if (list.contains(key))
				continue;
			tst.delete(key);
		}
		BufferedReader phishing_test=fileReading("phishing-test.txt");
		BufferedReader legitimate_test=fileReading("legitimate-test.txt");
		int phishing_count2=0;
		//Testing the Phishing
		while ((lineoffile=phishing_test.readLine())!=null){
			phishing_count2++;
			lineoffile=lineoffile.replace("https","");
			lineoffile=lineoffile.replace("http","");
			lineoffile=lineoffile.replace("www","");
			lineoffile=lineoffile.toLowerCase(Locale.ENGLISH);
			if (lineoffile.length()<N){
				continue;
			}
			else{
				float total=0;
				for (int i=0;i<lineoffile.length()-N+1;i++){
					if (!(list.contains(lineoffile.substring(i,i+N)))){
						continue;
					}
					else if (map3.containsKey(lineoffile.substring(i,i+N))){
						float temp= map3.get(lineoffile.substring(i,i+N));
						total= total+temp;
					}

				}
				if (total==0){
					UP++;
				}
				else if(total<0){
					FN++;
				}
				else if(total>0){
					TP++;
				}
			}
		}
		int legitimate_count2=0;
		//Testing the Phishing
		while ((lineoffile=legitimate_test.readLine())!=null){
			legitimate_count2++;
			lineoffile=lineoffile.replace("https","");
			lineoffile=lineoffile.replace("http","");
			lineoffile=lineoffile.replace("www","");
			lineoffile=lineoffile.toLowerCase(Locale.ENGLISH);
			if (lineoffile.length()<N){
				continue;
			}
			else{
				float total=0;
				for (int i=0;i<lineoffile.length()-N+1;i++){
					if (!(list.contains(lineoffile.substring(i,i+N)))){
						continue;
					}
					else if (map3.containsKey(lineoffile.substring(i,i+N))){
						float temp=map3.get(lineoffile.substring(i,i+N));
						total=total+temp;
					}

				}
				if (total==0){
					UL++;
				}
				else if(total<0){
					TN++;
				}
				else if(total>0){
					FP++;
				}
			}
		}
		int temp=TP+TN;
		int temp2=TP+TN+FP+FN+UP+UL;
		float accuracy= (float) temp/temp2;
		System.out.println("n-gram based phishing detection via TST\n" +
				"feat_size: "+feature_size+"\n" +
				"n_gram_size: "+N+"\n" +
				"\n" +
				"Legitimate training file has been loaded with ["+legitimate_count+"] instances\n" +
				"Legitimate test file has been loaded with ["+legitimate_count2+"] instances\n" +
				"Phishing training file has been loaded with ["+phishing_count+"] instances\n" +
				"Phishing test file has been loaded with ["+phishing_count2+"] instances\n" +
				"TST has been loaded with "+legitimate_count+" n-grams\n" +
				"TST has been loaded with "+phishing_count+" n-grams\n" +
				feature_size+" strong phishing n-grams have been saved to the file\"strong_phishing_features.txt\"\n" +
				feature_size+" strong legitimate n-grams have been saved to the file \"strong_legitimate_features.txt\"\n" +
				(total_ngrams)+" n-grams + weights have been saved to the file \"all_feature_weights.txt\"\n" +
				(total_ngrams-list.size())+" insignificant n-grams have been removed from the TST\n" +
				"TP:"+TP+" FN:"+FN+" TN:"+TN+" FP:"+FP+" Unpredictable Phishing:"+UP+" Unpredictable Legitimate:"+UL+"\n" +
				"Accuracy: "+accuracy);

		legitimate_test.close();
		legitimate_train.close();
		phishing_test.close();
		phishing_train.close();
    }

}
