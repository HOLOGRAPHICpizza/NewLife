package org.peak15.newlife.types;

/**
 * One nicely packaged unit of source code!
 * 
 * Immutable.
 */
public final class Token {

	public enum TokenType {
		KEYWORD,
		IDENTIFIER,
		CONDITION,
		COMMENT,
		ERROR,
		EOF_TOKEN
	}
	
	private final TokenType type;
	private final String text;
	
	public Token(TokenType type, String text) {
		this.type = type;
		this.text = text;
	}
	
	/**
	 * @return the type of the token
	 */
	public TokenType getType() {
		return type;
	}

	/**
	 * @return the token's text
	 */
	public String getText() {
		return text;
	}
}
