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
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		
		if(!(obj instanceof Token)) {
			return false;
		}
		
		Token t = (Token) obj;
		
		return	t.getType() == this.getType() &&
				t.getText().equals(this.getText());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.getType().hashCode();
		result = 1327 * result + this.getText().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("(%s, \"%s\")", this.getType().toString(), this.getText());
	}
}
