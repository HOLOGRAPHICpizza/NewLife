package org.peak15.newlife;

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
