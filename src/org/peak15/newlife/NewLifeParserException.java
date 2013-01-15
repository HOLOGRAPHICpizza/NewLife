package org.peak15.newlife;

/**
 * Usually thrown by parsers in the event of syntax errors.
 * May also be a wrapped error from deeper in the parser.
 */
public class NewLifeParserException extends Exception {
	
	private static final long serialVersionUID = -3344793698526867475L;

	public NewLifeParserException(String message) {
		super(message);
	}
	
	public NewLifeParserException(String message, Throwable e) {
		super(message, e);
	}
	
	public NewLifeParserException(Throwable e) {
		super(e);
	}
	
	/**
	 * Checks the specified condition, and throws an exception if it is false.
	 * 
	 * @param expectedTrueCond condition expected to be true
	 * @param failMsg Message to print if the condition is false.
	 * @throws NewLifeParserException If the condition is false.
	 */
	public static void assertCode(boolean expectedTrueCond, String failMsg)
			throws NewLifeParserException {
		if(!expectedTrueCond)
			throw new NewLifeParserException(failMsg);
	}
}
