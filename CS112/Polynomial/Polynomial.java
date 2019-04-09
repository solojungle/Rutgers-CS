package poly;

import java.io.IOException;
import java.util.Scanner;

/**
 * This class implements evaluate, add and multiply for polynomials.
 * 
 * @author runb-cs112
 *
 */
public class Polynomial {
	
	/**
	 * Reads a polynomial from an input stream (file or keyboard). The storage format
	 * of the polynomial is:
	 * <pre>
	 *     <coeff> <degree>
	 *     <coeff> <degree>
	 *     ...
	 *     <coeff> <degree>
	 * </pre>
	 * with the guarantee that degrees will be in descending order. For example:
	 * <pre>
	 *      4 5
	 *     -2 3
	 *      2 1
	 *      3 0
	 * </pre>
	 * which represents the polynomial:
	 * <pre>
	 *      4*x^5 - 2*x^3 + 2*x + 3 
	 * </pre>
	 * 
	 * @param sc Scanner from which a polynomial is to be read
	 * @throws IOException If there is any input error in reading the polynomial
	 * @return The polynomial linked list (front node) constructed from coefficients and
	 *         degrees read from scanner
	 */
	public static Node read(Scanner sc) 
	throws IOException {
		Node poly = null;
		while (sc.hasNextLine()) {
			Scanner scLine = new Scanner(sc.nextLine());
			poly = new Node(scLine.nextFloat(), scLine.nextInt(), poly);
			scLine.close();
		}
		return poly;
	}
	
	/**
	 * Returns the sum of two polynomials - DOES NOT change either of the input polynomials.
	 * The returned polynomial MUST have all new nodes. In other words, none of the nodes
	 * of the input polynomials can be in the result.
	 * 
	 * @param poly1 First input polynomial (front of polynomial linked list)
	 * @param poly2 Second input polynomial (front of polynomial linked list
	 * @return A new polynomial which is the sum of the input polynomials - the returned node
	 *         is the front of the result polynomial
	 */
	
	private static Node addToBack(float coeff, int degree, Node front){
		if(front == null) {
			Node node = new Node(coeff, degree, front);
			return node;
		} else {
			Node p = front;
			while(p.next != null){
				p = p.next;
			}
			Node node = new Node(coeff, degree, null);
			p.next = node;
		}
			return front;
	}

	public static Node add(Node poly1, Node poly2) {
		/** COMPLETE THIS METHOD **/
		// FOLLOWING LINE IS A PLACEHOLDER TO MAKE THIS METHOD COMPILE
		// CHANGE IT AS NEEDED FOR YOUR IMPLEMENTATION
		Node p = poly1;
		Node q = poly2;
		Node result = null;

		if(p == null){return q;}
		else if(q == null){return p;}
		else {
			while(p!=null || q!=null){
				while(q!=null && p!=null){
					if(q.term.degree == p.term.degree){
						float sum = q.term.coeff + p.term.coeff;
						if(sum != 0) {
							result = addToBack(sum, q.term.degree, result);
						}
						p = p.next;
						q = q.next;
					} else if(q.term.degree > p.term.degree){
						result = addToBack(p.term.coeff, p.term.degree, result);
						p = p.next;
					} else if(q.term.degree < p.term.degree) {
						result = addToBack(q.term.coeff, q.term.degree, result);
						q = q.next;
					}
				}
				if(p != null){
					result = addToBack(p.term.coeff, p.term.degree, result);
					p = p.next;
				} else if (q != null) {
					result = addToBack(q.term.coeff, q.term.degree, result);
					q = q.next;
				}
			}
		}
		return result;
	}
	
	/**
	 * Returns the product of two polynomials - DOES NOT change either of the input polynomials.
	 * The returned polynomial MUST have all new nodes. In other words, none of the nodes
	 * of the input polynomials can be in the result.
	 * 
	 * @param poly1 First input polynomial (front of polynomial linked list)
	 * @param poly2 Second input polynomial (front of polynomial linked list)
	 * @return A new polynomial which is the product of the input polynomials - the returned node
	 *         is the front of the result polynomial
	 */
	public static Node multiply(Node poly1, Node poly2) {
		/** COMPLETE THIS METHOD **/
		// FOLLOWING LINE IS A PLACEHOLDER TO MAKE THIS METHOD COMPILE
		// CHANGE IT AS NEEDED FOR YOUR IMPLEMENTATION
		Node p = poly1;
		Node q = poly2;
		Node result = null;
		Node instance = null;
		float coeffSum;
		int degAdd;

			while (p != null) {
				while (q != null) {
					//Create Multiplied Linked List.
					coeffSum = q.term.coeff * p.term.coeff;
					degAdd = q.term.degree + p.term.degree;
					instance = addToBack(coeffSum,degAdd,instance);
					// Move pointer
					q = q.next;
				}
				// Add to total sum.
				result = add(result, instance);
				instance = null;
				// Move and reset pointers
				q = poly2;
				p = p.next;
			}
		return result;
	}
		
	/**
	 * Evaluates a polynomial at a given value.
	 * 
	 * @param poly Polynomial (front of linked list) to be evaluated
	 * @param x Value at which evaluation is to be done
	 * @return Value of polynomial p at x
	 */
	public static float evaluate(Node poly, float x) {
		/** COMPLETE THIS METHOD **/
		// FOLLOWING LINE IS A PLACEHOLDER TO MAKE THIS METHOD COMPILE
		// CHANGE IT AS NEEDED FOR YOUR IMPLEMENTATION
		Node p = poly;
		float sum = 0;
		while (p != null){
			sum += p.term.coeff * (float)(Math.pow(x,p.term.degree));
			p = p.next;
		}
		return sum;
	}
	
	/**
	 * Returns string representation of a polynomial
	 * 
	 * @param poly Polynomial (front of linked list)
	 * @return String representation, in descending order of degrees
	 */
	public static String toString(Node poly) {
		if (poly == null) {
			return "0";
		} 
		
		String retval = poly.term.toString();
		for (Node current = poly.next ; current != null ;
		current = current.next) {
			retval = current.term.toString() + " + " + retval;
		}
		return retval;
	}	
}
