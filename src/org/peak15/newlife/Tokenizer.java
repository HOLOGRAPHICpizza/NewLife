package org.peak15.newlife;

import java.io.InputStream;

/**
 * Creates tagged tokens from an input stream.
 * 
 * @author Michael Craft <mcraft@peak15.org>
 */
public class Tokenizer {
	
	private enum BufferState {
		EMPTY_BS,
		ID_KW_COND_BS,
		WHITESPACE_BS,
		COMMENT_BS,
		ERROR_BS
	}
	
	private BufferState bufferState = BufferState.EMPTY_BS;
	private final StringBuilder buffer = new StringBuilder();
	
	private final InputStream ins;
	
	public Tokenizer(InputStream ins) {
		this.ins = ins;
	}
	
	public Token nextToken() {
		return null;
	}
	
	// hasNextToken?
}