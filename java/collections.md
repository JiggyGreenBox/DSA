## int array, arraylist
```java
import java.util.ArrayList;
import java.util.List;

class Main {
    public static void main(String[] args) {
        
        // List<Integer> l = new ArrayList<>();
        // l.add(5);
        // l.add(2);
        // l.add(3);
        
        int[] cars = {1,2,3};
        for(int x: cars){
            System.out.println(x);
        }
        
        System.out.println("\n");
        
        for(int i=0; i<cars.length; i++){
            System.out.println(cars[i]);
        }
        
        System.out.println("\n");
        
        List<Integer> list = new ArrayList<>();
        list.add(5);
        list.add(4);
        list.add(3);
        
        for(int x : list) {
            System.out.println(x);
        }
    }
}
```

## map, set, treemap, tree set
```java
import java.util.HashMap; // Import the HashMap class
import java.util.Map; // Import the Map class

class Main {
    public static void main(String[] args) {
        
        HashMap<String, String> capitalCities = new HashMap<>();
        
        // Add keys and values (Country, City)
        capitalCities.put("England", "London");
        capitalCities.put("India", "New Dehli");
        capitalCities.put("Austria", "Wien");
        capitalCities.put("Norway", "Oslo");
        capitalCities.put("Norway", "Oslo"); // Duplicate
        capitalCities.put("USA", "Washington DC");
    
        System.out.println(capitalCities);
        
        
        String result = capitalCities.get("England");
        
        System.out.println(result);
        
        System.out.println(capitalCities.size());
        System.out.println("\n");
        
        // print keys
        for(String i : capitalCities.keySet()) {
            System.out.println(i);
        }
        
        // Print values
        for (String i : capitalCities.values()) {
          System.out.println(i);
        }
        
        for (Map.Entry<String, String> entry : capitalCities.entrySet()) {
            System.out.println("Key: " + entry.getKey() + ", Value: " + entry.getValue());
        }
    }
}
```