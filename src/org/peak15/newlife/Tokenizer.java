package org.peak15.newlife;

import java.io.IOException;
import java.io.Reader;

import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.TokenType;

/**
 * Creates tagged tokens from an input stream.
 */
public final class Tokenizer {
	
	private enum BufferState {
		EMPTY_BS,
		ID_KW_COND_BS,
		WHITESPACE_BS,
		COMMENT_BS,
		ERROR_BS
	}
	
	private BufferState bufferState = BufferState.EMPTY_BS;
	private final StringBuilder buffer = new StringBuilder();
	
	private boolean tokenReady, EOFReached;
	private Token tokenBuffer = null;
	
	private final Reader reader;
	
	/**
	 * The given reader is not buffered,
	 * you should buffer it yourself if you want that.
	 * 
	 * @param ins reader to read from
	 */
	public Tokenizer(Reader ins) {
		this.reader = ins;
	}
	
	/**
	 * Pulls the next token from the input stream,
	 * whitespace is ignored, returns EOF_TOKEN on end of stream.
	 * 
	 * @return the next token from the input stream
	 * @throws IOException in the event of an input error
	 */
	public Token nextToken() throws IOException {
		Token t;
		
		if(tokenBuffer == null) {
			t = pullNextToken();
		}
		else {
			t = tokenBuffer;
			tokenBuffer = null;
		}
		
		return t;
	}
	
	/**
	 * The same as nextToken, except the state of the tokenizer is not changed.
	 * The token is not pulled out, future calls to nextToken are unaffected.
	 * 
	 * @return the next token
	 */
	public Token peekNextToken() throws IOException {
		if(tokenBuffer == null) {
			tokenBuffer = pullNextToken();
		}
		
		return tokenBuffer;
	}
	
	private Token pullNextToken() throws IOException {
		// read characters until the token is ready
		while(!tokenReady && !EOFReached) {
			processNextChar();
		}
		
		Token t;
		
		if(EOFReached) {
			// does the buffer still have crap in it?
			if(buffer.length() > 0) {
				t = new Token(tokenType(bufferState, buffer.toString()), buffer.toString());
				buffer.setLength(0);
			}
			else {
				t = new Token(TokenType.EOF_TOKEN, "");
			}
		}
		else {
			// the token is now all but the last char in the buffer
			String tokenText = buffer.substring(0, buffer.length() - 1);
			t = new Token(tokenType(bufferState, tokenText), tokenText);
			
			// set the new buffer and buffer state
			buffer.delete(0, buffer.length() - 1);
			bufferState = newBufferState(buffer.toString());
			tokenReady = false;
		}
		
		return t;
	}
	
	private void processNextChar() throws IOException {
		int r = reader.read();
		
		// have we not reached EOF?
		if(r != -1) {
			char c = (char) r;
			
			buffer.append(c);
			
			switch(bufferState) {
			
			case EMPTY_BS:
				// pick a new buffer state
				bufferState = newBufferState(buffer.toString());
				break;
				
			case ID_KW_COND_BS:
				// if this is not an identifier char we have reached token end
				if(!isIdentifierChar(c))
					tokenReady = true;
				break;

			case WHITESPACE_BS:
				// if this is not whitespace we have reached end
				if(!Character.isWhitespace(c)) {
					// flush the buffer, we kill all whitespace!!
					// set the new buffer and buffer state
					//TODO: Test this math.
					buffer.delete(0, buffer.length() - 1);
					bufferState = newBufferState(buffer.toString());
				}
				break;

			case COMMENT_BS:
				// if this is newline we have reached end
				if(c == '\n')
					tokenReady = true;
				break;

			case ERROR_BS:
				// if this is a valid starting char, end token
				if(canStartToken(c))
					tokenReady = true;
				break;	
			}
		}
		else {
			EOFReached = true;
		}
	}
	
	private static boolean canStartToken(char c) {
		return Character.isLetter(c) || Character.isWhitespace(c) || c == '#';
	}

	private static boolean isIdentifierChar(char c) {
		return Character.isLetterOrDigit(c) || c == '-';
	}

	/**
	 * @return the type of the token based on the given text and buffer state
	 */
	private static TokenType tokenType(BufferState bufferState, String tokenText) {
		TokenType ret = TokenType.ERROR;

		switch (bufferState) {

		case ID_KW_COND_BS:
			ret = idKwOrCond(tokenText);
			break;

		case COMMENT_BS:
			ret = TokenType.COMMENT;
			break;
			
		default:
			break;
		}

		return ret;
	}
	
	private static TokenType idKwOrCond(String t) {
		TokenType result;

		if (t.equals("IF") || t.equals("THEN") || t.equals("ELSE") || t.equals("END")
				|| t.equals("WHILE") || t.equals("DO") || t.equals("INSTRUCTION")
				|| t.equals("PROGRAM") || t.equals("BEGIN") || t.equals("IS")) {
			result = TokenType.KEYWORD;
		}

		else if (t.equals("true") || t.equals("random") || t.equals("next-is-empty")
				|| t.equals("next-is-not-empty") || t.equals("next-is-wall")
				|| t.equals("next-is-not-wall") || t.equals("next-is-friend")
				|| t.equals("next-is-not-friend") || t.equals("next-is-enemy")
				|| t.equals("next-is-not-enemy")) {
			result = TokenType.CONDITION;
		}

		else {
			result = TokenType.IDENTIFIER;
		}

		return result;
	}

	/**
	 * @param buffer the contents of a buffer
	 * @return the appropriate buffer state for this buffer contents
	 */
	private static BufferState newBufferState(String buffer) {
		BufferState ret;

		// alphabetic character?
		if(Character.isLetter(buffer.charAt(0))) {
			ret = BufferState.ID_KW_COND_BS;
		}

		// whitespace?
		else if(Character.isWhitespace(buffer.charAt(0))) {
			ret = BufferState.WHITESPACE_BS;
		}

		// comment?
		else if(buffer.charAt(0) == '#') {
			ret = BufferState.COMMENT_BS;
		}

		// other crap
		else {
			ret = BufferState.ERROR_BS;
		}

		return ret;
	}
}