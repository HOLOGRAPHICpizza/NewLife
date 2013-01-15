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
}
