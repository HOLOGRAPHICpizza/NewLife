package org.peak15.newlife;

/**
 * Creates tagged tokens from an input stream.
 * 
 * @author Michael Craft <mcraft@peak15.org>
 */
public class Tokenizer {
	public enum TokenType {
		KEYWORD,
		IDENTIFIER,
		CONDITION,
		WHITESPACE,
		COMMENT,
		ERROR,
		EOF_TOKEN
	}
	
	
}