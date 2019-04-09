package structures;

import java.util.*;

/**
 * This class implements an HTML DOM Tree. Each node of the tree is a TagNode, with fields for
 * tag/text, first child and sibling.
 * 
 */
public class Tree {
	
	/**
	 * Root node
	 */
	TagNode root=null;
	
	/**
	 * Scanner used to read input HTML file when building the tree
	 */
	Scanner sc;
	
	/**
	 * Initializes this tree object with scanner for input HTML file
	 * 
	 * @param sc Scanner for input HTML file
	 */
	public Tree(Scanner sc) {
		this.sc = sc;
		root = null;
	}
	
	/**
	 * Builds the DOM tree from input HTML file, through scanner passed
	 * in to the constructor and stored in the sc field of this object. 
	 * 
	 * The root of the tree that is built is referenced by the root field of this object.
	 */
	public void build() {
		/** COMPLETE THIS METHOD **/
		this.root = domBuilder();
	}

	private TagNode domBuilder(){
		String currentLine;
		// Null exception
		if(sc.hasNextLine()){ currentLine = sc.nextLine(); }
		else { return null; }

		// Check if open/closing tag exists in statement
		if(currentLine.charAt(0) == '<') {
			// Remove contents of the tag, also remove ending '>'
			currentLine = currentLine.substring(1, currentLine.length() - 1);
			// Found closing-tag
			if (currentLine.charAt(0) == '/') {
				return null;
			}
			TagNode node = new TagNode(currentLine, null, null);

        /*
        * Tagged elements may have children and/or siblings,
        * therefore we must recursively call domBuilder() to
        * ensure that all elements are picked off the .html
        * */
			node.firstChild = domBuilder();
			node.sibling = domBuilder();

			return node;
		}
		// Create the leaf-node
		TagNode node = new TagNode(currentLine, null, null);

    /*
    * Non-tag elements of the DOM tree do not have children nodes.
    * However, they may have sibling nodes, and therefore need to
    * recursively call domBuilder().
    * */
		node.sibling = domBuilder();
		return node;
	}

	/**
	 * Replaces all occurrences of an old tag in the DOM tree with a new tag
	 * 
	 * @param oldTag Old tag
	 * @param newTag Replacement tag
	 */
	public void replaceTag(String oldTag, String newTag) {
		/** COMPLETE THIS METHOD **/
		recursiveReplace(oldTag, newTag, root);
	}

	private void recursiveReplace(String oldTag, String newTag, TagNode node){
		// Null exception
		if(node == null){ return; }

    /*
    * Simple recursion, creates multiple threads of siblings
    * then dives into child nodes.
    * */
		if(node.tag.equals(oldTag)){ node.tag = newTag; }
		if(node.sibling != null) { recursiveReplace(oldTag, newTag, node.sibling); }
		if(node.firstChild != null) { recursiveReplace(oldTag, newTag, node.firstChild); }
	}
	
	/**
	 * Boldfaces every column of the given row of the table in the DOM tree. The boldface (b)
	 * tag appears directly under the td tag of every column of this row.
	 * 
	 * @param row Row to bold, first row is numbered 1 (not 0).
	 */
	public void boldRow(int row) {
		/** COMPLETE THIS METHOD **/
		// Null exception
		if(root == null){ return; }
		// Determine if table exists
		TagNode node = findFirstTagOccurrence("table", root);
		if(node != null){
			node = node.firstChild; // Table -> 'tr'
			for(int i = 1;i < row && node != null; i++){
				node = node.sibling;
			}
			if(node != null){
				// Found correct 'tr'
				recursiveBoldRow(node.firstChild);
			}
			else { return; }
		} else { return; }
	}

	private void recursiveBoldRow(TagNode node) {
		if(node == null) return;
		recursiveBoldRow(node.sibling);
		node.firstChild = new TagNode("b", node.firstChild, node.firstChild.sibling);
	}

	private TagNode findFirstTagOccurrence(String tag, TagNode node) {
		TagNode sibling, child;
		if(node == null) return null;
		if(node.tag.equals(tag)){ return node; }
		else {
			sibling = findFirstTagOccurrence(tag, node.sibling);
			child = findFirstTagOccurrence(tag, node.firstChild);
			if(child != null){ return child;}
			if(sibling != null){ return sibling;}
		}
		return null;
	}
	
	/**
	 * Remove all occurrences of a tag from the DOM tree. If the tag is p, em, or b, all occurrences of the tag
	 * are removed. If the tag is ol or ul, then All occurrences of such a tag are removed from the tree, and, 
	 * in addition, all the li tags immediately under the removed tag are converted to p tags. 
	 * 
	 * @param tag Tag to be removed, can be p, em, b, ol, or ul
	 */
	public void removeTag(String tag) {
		/** COMPLETE THIS METHOD **/
		if(tag.equals("p") || tag.equals("em") || tag.equals("b")){
			recursiveRemove(tag, null, root);
		}
		else if(tag.equals("ol") || tag.equals("ul")){
			TagNode node;
			if(tag.equals("ol")){
				while(findFirstTagOccurrence("ol", root) != null){
					node = findFirstTagOccurrence("ol",root);
					node = node.firstChild;
					while(node != null){
						if(node.tag.equals("li")){ node.tag = "p"; }
						node = node.sibling;
					}
					recursiveRemove("ol", null, root);
				}
			}
			else {
				while(findFirstTagOccurrence("ul", root) != null){
					node = findFirstTagOccurrence("ul",root);
					node = node.firstChild;
					while(node != null){
						if(node.tag.equals("li")){ node.tag = "p"; }
						node = node.sibling;
					}
					recursiveRemove("ul", null, root);
				}
			}
		}
		else { return; }
	}

	private void fixTree(TagNode node, TagNode prev){
		if(node.sibling == null && node.firstChild == null){
			if(prev.sibling != null){
				node.sibling = prev.sibling;
			}
			return;
		}
		else if(node.sibling != null && node.firstChild != null){
			fixTree(node.firstChild, node);
			if(node.firstChild.sibling == node.sibling){ node.sibling = prev.sibling; return;}
		}
		else if(node.sibling != null){
			node.firstChild = node.sibling;
			node.sibling = null;
		}
		fixTree(node.firstChild, node);
	}

	private void recursiveRemove(String tag, TagNode prev, TagNode node){
		if(node == null){ return; }
		if(node.tag.equals(tag)){
			// Family node
			if(node.sibling != null && node.firstChild != null){

				// Root node exception
				if(prev == null){
					if(node.firstChild.sibling == null){
						node.firstChild.sibling = node.sibling;
						root = node.firstChild;
						return;
					}
					else {
						fixTree(node.firstChild, node);
						node.firstChild.sibling = node.sibling;
						root = node.firstChild;
					}
				}
				else if(prev.firstChild == node){
					fixTree(node.firstChild, node);
					node.firstChild.sibling = node.sibling;
					prev.firstChild = node.firstChild;
				}
				else {
					// prev.sibling == node
					fixTree(node.firstChild, node);
					node.firstChild.sibling = node.sibling;
					prev.sibling = node.firstChild;
				}
			}
			// Lonely node
			else if(node.sibling == null && node.firstChild == null){
				// Root node exception
				if(prev == null){
					root = null;
					return;
				}
				else if(prev.firstChild == node){
					prev.firstChild = null;
				}
				else {
					prev.sibling = null;
				}
			}
			// Parent node
			else if(node.sibling == null){
				// Root node exception
				if(prev == null){
					root = node.firstChild;
					return;
				}
				else if(prev.firstChild == node){
					prev.firstChild = node.firstChild;
				}
				else {
					prev.sibling = node.firstChild;
				}
			}
			// Sibling node
			else {
				// Root node exception
				if(prev == null){
					root = node.sibling;
					return;
				}
				else if(prev.firstChild == node){
					prev.firstChild = node.sibling;
				}
				else {
					prev.sibling = node.sibling;
				}
			}
			removeTag(tag);
		}
		else {
			recursiveRemove(tag, node, node.sibling);
			recursiveRemove(tag, node, node.firstChild);
		}
	}
	
	/**
	 * Adds a tag around all occurrences of a word in the DOM tree.
	 * 
	 * @param word Word around which tag is to be added
	 * @param tag Tag to be added
	 */
	public void addTag(String word, String tag) {
		/** COMPLETE THIS METHOD **/
		if(tag.equals("em") || tag.equals("b")){
			recursiveAddTag(word, tag, root);
		}
	}

	private void recursiveAddTag(String word, String tag, TagNode node) {
		if (node.sibling != null) { recursiveAddTag(word, tag, node.sibling); }
		if (node.firstChild != null) { recursiveAddTag(word, tag, node.firstChild); }
		if (node.tag.matches("(?i)"+word+"[,.!?;:]?")) {
			TagNode copyOfCurrentNode = new TagNode(node.tag, node.firstChild, null);
			node.tag = tag;
			node.firstChild = copyOfCurrentNode;
		}
	}
	
	/**
	 * Gets the HTML represented by this DOM tree. The returned string includes
	 * new lines, so that when it is printed, it will be identical to the
	 * input file from which the DOM tree was built.
	 * 
	 * @return HTML string, including new lines. 
	 */
	public String getHTML() {
		StringBuilder sb = new StringBuilder();
		getHTML(root, sb);
		return sb.toString();
	}
	
	private void getHTML(TagNode root, StringBuilder sb) {
		for (TagNode ptr=root; ptr != null;ptr=ptr.sibling) {
			if (ptr.firstChild == null) {
				sb.append(ptr.tag);
				sb.append("\n");
			} else {
				sb.append("<");
				sb.append(ptr.tag);
				sb.append(">\n");
				getHTML(ptr.firstChild, sb);
				sb.append("</");
				sb.append(ptr.tag);
				sb.append(">\n");	
			}
		}
	}
	
	/**
	 * Prints the DOM tree. 
	 *
	 */
	public void print() {
		print(root, 1);
	}
	
	private void print(TagNode root, int level) {
		for (TagNode ptr=root; ptr != null;ptr=ptr.sibling) {
			for (int i=0; i < level-1; i++) {
				System.out.print("      ");
			};
			if (root != this.root) {
				System.out.print("|---- ");
			} else {
				System.out.print("      ");
			}
			System.out.println(ptr.tag);
			if (ptr.firstChild != null) {
				print(ptr.firstChild, level+1);
			}
		}
	}
}
