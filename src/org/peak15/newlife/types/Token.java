package org.peak15.newlife.types;

/**
 * One nicely packaged unit of source code!
 * 
 * Immutable.
 */
public final class Token {
	
	/*
	 * Though best practices deprecate "type" enums in favor of class hierarchies,
	 * this is the simplest way to pair an item of text with its category.
	 * A class hierarchy would unnecessarily complicate things.
	 * I can think of no method that would accept only a single type of Token.
	 */
	
	public static enum Type {
		KEYWORD,
		IDENTIFIER,
		CONDITION,
		EOF_TOKEN
	}
	
	private final Type type;
	private final String text;
	
	public Token(Type type, String text) {
		if(type == null || text == null) {
			throw new NullPointerException("No parameters may be null.");
		}
		
		this.type = type;
		this.text = text;
	}
	
	/**
	 * @return the type of the token
	 */
	public Type type() {
		return type;
	}

	/**
	 * @return the token's text
	 */
	public String text() {
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
		
		return	t.type() == this.type() &&
				t.text().equals(this.text());
	}
	
	@Override
	public int hashCode() {
		int result = 9001;
		result = 1327 * result + this.type().hashCode();
		result = 1327 * result + this.text().hashCode();
		return result;
	}
	
	@Override
	public String toString() {
		return String.format("(%s, \"%s\")", this.type().toString(), this.text());
	}
}
