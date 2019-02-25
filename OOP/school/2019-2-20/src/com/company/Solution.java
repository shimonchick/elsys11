import java.util.*;
class Solution {

    public static void main(String []argh)
    {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNext()) {
            String input=sc.next();
            Stack<String> stack = new Stack<String>();
            for(int i = 0; i < input.size(); i++){

                if(input.get(i).equals("{") || input.get(i).equals("(") || input.get(i).equals("[")){
                    stack.addElement(input.get(i));
                }
                else if(input.get(i).equals("}")|| input.get(i).equals(")") || input.get(i).equals("]")){
                    if(!stack.empty()){
                        stack.pop();
                    }
                }

            }
            System.out.println(stack.isEmpty());
        }

    }
}

