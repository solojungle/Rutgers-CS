package app;

import java.io.*;
import java.util.*;
import java.util.regex.*;

import structures.Stack;

public class Expression {

    public static String delims = " \t*+-/()[]";

    /**
     * Populates the vars list with simple variables, and arrays lists with arrays
     * in the expression. For every variable (simple or array), a SINGLE instance is created
     * and stored, even if it appears more than once in the expression.
     * At this time, values for all variables and all array items are set to
     * zero - they will be loaded from a file in the loadVariableValues method.
     *
     * @param expr   The expression
     * @param vars   The variables array list - already created by the caller
     * @param arrays The arrays array list - already created by the caller
     */
    public static void
    makeVariableLists(String expr, ArrayList<Variable> vars, ArrayList<Array> arrays) {
        /** COMPLETE THIS METHOD **/
        /** DO NOT create new vars and arrays - they are already created before being sent in
         ** to this method - you just need to fill them in.
         **/
        StringTokenizer tokenizer = new StringTokenizer(expr, delims, true);
        String temp;
        String scopeTemp = "";
        // Uses Tokenizer which divides string into Tokens.
        while (tokenizer.hasMoreTokens()) {
            temp = tokenizer.nextToken();
            // Adds all variables (non-digit, & non-delimiter) to Simple Variable Stack.
            if (temp.matches("[a-zA-Z]*")) {
                vars.add(new Variable(temp));
            }
            // Adds only variables that are succeeded by '['
            if (temp.equals("[")) {
                arrays.add(new Array(scopeTemp));
                vars.remove(vars.size() - 1);
            }
            // Just in case test case includes space between array and '[', e.g. "A   []"
            if (!temp.matches("\\s")){ scopeTemp = temp; }
        }
    }

    /**
     * Loads values for variables and arrays in the expression
     *
     * @param sc     Scanner for values input
     * @param vars   The variables array list, previously populated by makeVariableLists
     * @param arrays The arrays array list - previously populated by makeVariableLists
     * @throws IOException If there is a problem with the input
     */
    public static void
    loadVariableValues(Scanner sc, ArrayList<Variable> vars, ArrayList<Array> arrays)
            throws IOException {
        while (sc.hasNextLine()) {
            StringTokenizer st = new StringTokenizer(sc.nextLine().trim());
            int numTokens = st.countTokens();
            String tok = st.nextToken();
            Variable var = new Variable(tok);
            Array arr = new Array(tok);
            int vari = vars.indexOf(var);
            int arri = arrays.indexOf(arr);
            if (vari == -1 && arri == -1) {
                continue;
            }
            int num = Integer.parseInt(st.nextToken());
            if (numTokens == 2) { // scalar symbol
                vars.get(vari).value = num;
            } else { // array symbol
                arr = arrays.get(arri);
                arr.values = new int[num];
                // following are (index,val) pairs
                while (st.hasMoreTokens()) {
                    tok = st.nextToken();
                    StringTokenizer stt = new StringTokenizer(tok, " (,)");
                    int index = Integer.parseInt(stt.nextToken());
                    int val = Integer.parseInt(stt.nextToken());
                    arr.values[index] = val;
                }
            }
        }
    }

    /**
     * Evaluates the expression.
     *
     * @param vars   The variables array list, with values for all variables in the expression
     * @param arrays The arrays array list, with values for all array items
     * @return Result of evaluation
     */
    public static float
    evaluate(String expr, ArrayList<Variable> vars, ArrayList<Array> arrays) {
        /** COMPLETE THIS METHOD **/
        // following line just a placeholder for compilation

        expr = parenthesis(expr, vars, arrays);
        expr = arrayChecker(expr, vars, arrays);
        expr = pemdas(expr, vars, arrays);

        return Float.parseFloat(expr);
    }

    // Finds subexpressions and cuts them down.
    private static String parenthesis(String expr, ArrayList<Variable> vars, ArrayList<Array> arrays) {
        Stack<Integer> pStack = new Stack<>();
        for (int i = 0; i < expr.length(); i++) {
            if (expr.charAt(i) == '(') {
                if (pStack.isEmpty()) {
                    pStack.push(i);
                } else {
                    pStack.pop();
                    pStack.push(i);
                }
            } else if (expr.charAt(i) == ')') {
                // Cut down expressions into smaller chunks.
                // Recursively call evaluate.
                return expr.substring(0, pStack.peek()) + evaluate(expr.substring(pStack.peek()+1, i), vars, arrays) + expr.substring(i+1);
            }
        }
        return expr;
    }

    // Finds arrays and strikes them down.
    private static String arrayChecker(String expr, ArrayList<Variable> vars, ArrayList<Array> arrays) {
        expr = parenthesis(expr, vars, arrays);
        Stack<String> aStack = new Stack<>();
        StringTokenizer tokenizer = new StringTokenizer(expr, delims, true);
        String temp;
        String arrayTemp;
        String scopeTemp = "";

        while(tokenizer.hasMoreTokens()){
            temp = tokenizer.nextToken();
            if (temp.equals("[")) {
                if (aStack.isEmpty()) {
                    aStack.push(scopeTemp);
                } else {
                    aStack.pop();
                    aStack.push(scopeTemp);
                }
            } else if(temp.equals("]")) {
                String arrayName = aStack.peek();
                arrayTemp = expr.substring(expr.indexOf(arrayName));
                int i = 0;
                while(i < arrays.size() && !arrays.get(i).name.equals(arrayName)){ i++; }

                // Split up in order to debug better.
                String first = expr.substring(0, expr.indexOf(arrayName));
                String end = expr.substring(expr.indexOf(arrayName) + arrayTemp.indexOf("]")+1);
                float preMid = evaluate(arrayTemp.substring(arrayTemp.indexOf("[")+1, arrayTemp.indexOf("]")), vars, arrays);
                if(arrays.get(i).values != null){
                    int mid = arrays.get(i).values[(int)preMid];
                    return first + mid + end;
                }
                else {
                    return null;
                }
            }
            if (!temp.matches("\\s")){ scopeTemp = temp; }
        }
        return expr;
    }

    private static String pemdas(String expr, ArrayList<Variable> vars, ArrayList<Array> arrays) {
        expr = parenthesis(expr, vars, arrays);
        expr = arrayChecker(expr, vars, arrays);
        Stack<Character> operators = new Stack<>();
        ArrayList<String> numExp = new ArrayList<>();
        float sum;
        String numberExpression = "";

        StringTokenizer tokenizer = new StringTokenizer(expr, delims, true);
        String temp;

        // Find variable values.
        while (tokenizer.hasMoreTokens()) {
            temp = tokenizer.nextToken();
            if(temp.matches("[-+]?[0-9]*\\.?[0-9]+")){ numberExpression += temp; }
            else {
                // Case where, no vars caused loop not to check for operators.
                if (temp.matches("[*+-/]*")) { numberExpression += temp; }
                else {
                    for (int i = 0; i < vars.size(); i++) {
                        if (vars.get(i).name.equals(temp)) {
                            numberExpression += vars.get(i).value;
                            break;
                        } else if (temp.matches("[0-9]*") || temp.matches("[*+-/]*")) {
                            numberExpression += temp;
                            break;
                        }
                    }
                }
            }
        }

        // Have numbered expression.
        tokenizer = new StringTokenizer(numberExpression, delims, true);
        while (tokenizer.hasMoreTokens()){
            temp = tokenizer.nextToken();
            switch (temp) {
                case "*":
                    if(operators.isEmpty() || operators.peek() != '*'){ operators.push('*'); }
                    else {
                        operators.pop();
                        operators.push('*');
                        sum = Float.parseFloat(numExp.get(numExp.size()-2)) * Float.parseFloat(numExp.get(numExp.size()-1));
                        numExp.remove(numExp.size()-1);
                        numExp.remove(numExp.size()-1);
                        numExp.add(Float.toString(sum));
                    }
                    break;
                case "/":
                    if(operators.isEmpty() || operators.peek() != '*' && operators.peek() != '/'){ operators.push('/'); }
                    else {
                        if(operators.peek().equals('*')){
                            operators.pop();
                            operators.push('/');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) * Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                        else {
                            operators.pop();
                            operators.push('/');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) / Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                    }
                    break;
                case "+":
                    if(operators.isEmpty() || operators.peek() == '-'){  operators.push('+'); }
                    else {
                        if(operators.peek().equals('*')){
                            operators.pop();
                            operators.push('+');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) * Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                        else if(operators.peek().equals('/')){
                            operators.pop();
                            operators.push('+');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) / Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                        else {
                            operators.pop();
                            operators.push('+');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) + Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                    }
                    break;
                case "-":
                    if(operators.isEmpty()){ operators.push('-'); }
                    else {
                        if(operators.peek().equals('*')){
                            operators.pop();
                            operators.push('-');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) * Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                        else if(operators.peek().equals('/')){
                            operators.pop();
                            operators.push('-');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) / Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                        else if(operators.peek().equals('+')){
                            operators.pop();
                            operators.push('-');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) + Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                        else {
                            operators.pop();
                            operators.push('-');
                            sum = Float.parseFloat(numExp.get(numExp.size()-2)) - Float.parseFloat(numExp.get(numExp.size()-1));
                            numExp.remove(numExp.size()-1);
                            numExp.remove(numExp.size()-1);
                            numExp.add(Float.toString(sum));
                        }
                    }
                    break;
                default:
                    if(temp.matches("[-+]?[0-9]*\\.?[0-9]+")){
                        numExp.add(temp);
                    }
                    break;
            }
        }
        // If expression is over, but operators left in stack.
        // Clears stack
        while(!operators.isEmpty()){
            if(operators.peek().equals('*')){
                operators.pop();
                sum = Float.parseFloat(numExp.get(numExp.size()-2)) * Float.parseFloat(numExp.get(numExp.size()-1));
                numExp.remove(numExp.size()-1);
                numExp.remove(numExp.size()-1);
                numExp.add(Float.toString(sum));
            }
            else if(operators.peek().equals('/')){
                operators.pop();
                sum = Float.parseFloat(numExp.get(numExp.size()-2)) / Float.parseFloat(numExp.get(numExp.size()-1));
                numExp.remove(numExp.size()-1);
                numExp.remove(numExp.size()-1);
                numExp.add(Float.toString(sum));
            }
            else if(operators.peek().equals('+')){
                operators.pop();
                sum = Float.parseFloat(numExp.get(numExp.size()-2)) + Float.parseFloat(numExp.get(numExp.size()-1));
                numExp.remove(numExp.size()-1);
                numExp.remove(numExp.size()-1);
                numExp.add(Float.toString(sum));
            }
            else if(operators.peek().equals('-')) {
                operators.pop();
                sum = Float.parseFloat(numExp.get(numExp.size()-2)) - Float.parseFloat(numExp.get(numExp.size()-1));
                numExp.remove(numExp.size()-1);
                numExp.remove(numExp.size()-1);
                numExp.add(Float.toString(sum));
            }
        }

        // Single number exception.
        if(numExp.isEmpty()){ return expr; }
        return numExp.get(0);
    }
}

