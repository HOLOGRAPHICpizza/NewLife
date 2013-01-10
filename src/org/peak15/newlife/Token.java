package org.peak15.newlife;

/**
 * One nicely packaged unit of source code!
 */
public final class Token {

	public enum TokenType {
		KEYWORD,
		IDENTIFIER,
		CONDITION,
		WHITESPACE,
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
